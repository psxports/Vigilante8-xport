#include "psx.h"
#include "xport.h"
#include "xport_trace.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Keep the attached BIOS bytes alive for the whole native process */
static uint8 v8_bios_image[0x80000];

/* Preserve the BIOS InitCARD2 producer before the SDK card patches */
static void v8_bios_card_irq_initializer(void)
{
    uint32 index;
    w_u32(0x75C0u, 0u);
    for (index = 0u; index < 4u; ++index)
        w_u32(0xCF0u + 4u * index, r_u32(0x6408u + 4u * index));
    FlushCache();
}

sint32 v8_native_load_bios_image(void)
{
    const char *path = "../tools/duckstation/data/user/bios/ps-30e.bin";
    const char *identity = "1faaa18fa820a0225e488d9f086296b8e6c46df739666093987ff7d8fd352c09";
    char digest[65];
    size_t file_size, read_size;

    if (!xport_file_size(path, &file_size) || file_size != sizeof(v8_bios_image) ||
        !xport_file_read(path, v8_bios_image, sizeof(v8_bios_image), &read_size) ||
        read_size != sizeof(v8_bios_image) ||
        !xport_journal_file_sha256(path, digest) || strcmp(digest, identity) != 0)
    {
        fprintf(stderr, "V8: configured BIOS image is missing or differs from its reviewed identity\n");
        return 0;
    }
    if (!xport_guest_copy(xport_guest_ref(0xA0000500u),
                          xport_host_ref(v8_bios_image + 0x10000u), 0x8BF0u))
    {
        fprintf(stderr, "V8: cannot initialize the reviewed BIOS kernel RAM payload\n");
        return 0;
    }
    xport_memory_bind_bios(v8_bios_image, sizeof(v8_bios_image));
    psx_bios_bind_card_irq_initializer(v8_bios_card_irq_initializer);
    return 1;
}


uint32 v8_native_bios_allocate_file(void);
uint32 v8_native_bios_parse_path(uint32 path, uint32 *device, uint32 *unit);

/* Preserve the original no-effect ROM callback rather than inventing a result */
static uint32 v8_bios_device_callback(uint32 target)
{
    if (target == 0xBFC06FDCu)
        return 0u;
    fprintf(stderr, "V8: pending native BIOS device callback %08X\n", target);
    abort();
}

static uint32 v8_bios_add_driver(uint32 descriptor)
{
    uint32 node = 0x6EE0u;
    uint32 end = node + r_u32(0x7200u) * 80u;
    uint32 index;
    if (end < 0x6EE1u)
        return 0u;
    while (node < end)
    {
        if (r_u32(node) == 0u)
        {
            for (index = 0u; index < 80u; ++index)
                w_u8(node + index, r_u8(descriptor + index));
            FlushCache();
            (void)v8_bios_device_callback(r_u32(node + 16u));
            return 1u;
        }
        node += 80u;
    }
    return 0u;
}

static sint32 v8_bios_guest_strcmp(uint32 first, uint32 second)
{
    uint8 a, b;
    do
    {
        a = r_u8(first++);
        b = r_u8(second++);
        if (a != b)
            return (sint32)a - (sint32)b;
    } while (a != 0u);
    return 0;
}

static uint32 v8_bios_delete_driver(uint32 name)
{
    uint32 node = 0x6EE0u;
    uint32 end = node + r_u32(0x7200u) * 80u;
    if (end < 0x6EE1u)
        return 0u;
    while (node < end)
    {
        uint32 candidate = r_u32(node);
        if (candidate != 0u && v8_bios_guest_strcmp(name, candidate) == 0)
        {
            (void)v8_bios_device_callback(r_u32(node + 72u));
            w_u32(node, 0u);
            return 1u;
        }
        node += 80u;
        end = 0x6EE0u + r_u32(0x7200u) * 80u;
    }
    return 0u;
}

uint32 v8_native_bios_close(uint32 descriptor)
{
    uint32 file, device, result;
    if ((sint32)descriptor < 0 || (sint32)descriptor >= 16)
        file = 0u;
    else
        file = 0x8648u + descriptor * 44u;
    if (file == 0u || r_u32(file) == 0u)
    {
        w_u32(0x8640u, 9u);
        return 0xFFFFFFFFu;
    }
    device = r_u32(file + 28u);
    result = v8_bios_device_callback(r_u32(device + 28u));
    w_u32(file, 0u);
    if (result != 0u)
    {
        w_u32(0x8640u, r_u32(file + 24u));
        return 0xFFFFFFFFu;
    }
    return descriptor;
}

static uint32 v8_bios_open(uint32 path, uint32 mode)
{
    uint32 file = v8_native_bios_allocate_file();
    uint32 device, unit, tail, result, descriptor;
    if (file == 0u)
    {
        w_u32(0x8640u, 24u);
        return 0xFFFFFFFFu;
    }
    tail = v8_native_bios_parse_path(path, &device, &unit);
    if (tail == 0xFFFFFFFFu)
    {
        w_u32(0x8640u, 19u);
        w_u32(file, 0u);
        return 0xFFFFFFFFu;
    }
    w_u32(file, mode);
    w_u32(file + 4u, unit);
    w_u32(file + 28u, device);
    w_u32(file + 20u, r_u32(device + 4u));
    result = v8_bios_device_callback(r_u32(device + 20u));
    if (result != 0u)
    {
        w_u32(0x8640u, r_u32(file + 24u));
        w_u32(file, 0u);
        return 0xFFFFFFFFu;
    }
    descriptor = (uint32)((sint32)(file - 0x8648u) / 44);
    w_u32(file + 16u, 0u);
    w_u32(file + 40u, descriptor);
    return descriptor;
}

/* Replace the POST diagnostic port with a host diagnostic while retaining RAM writes */
static void v8_bios_write_post(uint32 value)
{
    uint32 index;
    fprintf(stderr, "V8: BIOS device POST %u\n", value & 255u);
    for (index = 0u; index < 4u; ++index)
        w_u32(0x863Cu, 0u);
}

uint32 v8_native_bios_initialize_devices(uint32 boot_choice)
{
    uint32 index, result;
    if (boot_choice != 0u)
    {
        fprintf(stderr, "V8: pending original BIOS serial TTY boot choice %u\n", boot_choice);
        abort();
    }
    w_u32(0x8908u, boot_choice);
    w_u32(0xA0000140u, 0x8648u);
    w_u32(0xA0000144u, 704u);
    w_u32(0xA0000150u, 0x6EE0u);
    w_u32(0xA0000154u, r_u32(0x7200u) * 80u);
    for (index = 0u; index < 704u; ++index)
        w_u8(0x8648u + index, 0u);
    v8_bios_write_post(1u);
    v8_bios_write_post(3u);
    w_u32(0x8910u, 0u);
    w_u32(0x890Cu, 0u);
    (void)v8_bios_delete_driver(0x6DC0u);
    v8_bios_write_post(4u);
    (void)v8_bios_add_driver(0xBFC0E350u);
    v8_bios_write_post(5u);
    (void)v8_native_bios_close(0u);
    (void)v8_native_bios_close(1u);
    if (v8_bios_open(0x6DC4u, 1u) == 0u)
        (void)v8_bios_open(0x6DCCu, 2u);
    v8_bios_write_post(6u);
    v8_bios_write_post(2u);
    w_u32(0x7480u, 0u);
    w_u32(0x8644u, 0u);
    (void)v8_bios_add_driver(0xBFC0E2F0u);
    result = v8_bios_add_driver(0xBFC0E3E4u);
    return result;
}


void UnDeliverEvent(uint32 event_class, uint32 spec);
uint32 psx_bios_card_read_guest(uint32 channel, uint32 sector, uint32 buffer);
void psx_bios_card_poll(void);

void v8_native_bios_card_clear_events(void)
{
    uint32 index;
    w_u32(0xA000B9D0u, 0u);
    for (index = 0u; index < 4u; ++index)
        w_u32(0xA000B9D4u + index * 4u, 0u);
    UnDeliverEvent(0xF4000001u, 4u);
    UnDeliverEvent(0xF4000001u, 0x8000u);
    UnDeliverEvent(0xF4000001u, 0x2000u);
    UnDeliverEvent(0xF4000001u, 0x100u);
}

static uint32 v8_bios_card_wait_event(void)
{
    uint32 index;
    for (;;)
    {
        /* Advance the actual submitted native card operation */
        psx_bios_card_poll();
        for (index = 0u; index < 5u; ++index)
        {
            if (r_u32(0xA000B9D0u + index * 4u) == 1u)
            {
                v8_native_bios_card_clear_events();
                return index;
            }
        }
    }
}

uint32 v8_native_bios_card_load_wait(uint32 channel)
{
    sint32 port = (sint32)channel / 16;
    uint32 port_word = (uint32)port;
    uint32 buffer = 0xA000BE48u + (port_word << 7);
    uint32 event, table, recovery, index, byte;
    if (psx_bios_card_read_guest(channel, 0u, buffer) == 1u)
    {
        event = v8_bios_card_wait_event();
        if (event == 0u)
        {
            if (r_u8(buffer) == 0x4Du && r_u8(buffer + 1u) == 0x43u)
                return 1u;
            if (r_u32(0xA0009F90u) == 1u)
            {
                fprintf(stderr, "V8: pending full BIOS card format BFC0B170 channel=%08X\n", channel);
                abort();
            }
        }
        else if (event == 3u)
        {
            fprintf(stderr, "V8: pending full BIOS new-card directory load BFC08B3C channel=%08X\n", channel);
            abort();
        }
        else
            return 0u;
    }
    table = 0xA000BA88u + port_word * 480u;
    for (index = 0u; index < 15u; ++index)
        for (byte = 0u; byte < 32u; ++byte)
            w_u8(table + index * 32u + byte, 0u);
    recovery = 0xA000B9E8u + port_word * 80u;
    for (index = 0u; index < 20u; index += 4u)
    {
        w_u32(recovery + index * 4u, 0xFFFFFFFFu);
        w_u32(recovery + index * 4u + 4u, 0xFFFFFFFFu);
        w_u32(recovery + index * 4u + 8u, 0xFFFFFFFFu);
        w_u32(recovery + index * 4u + 12u, 0xFFFFFFFFu);
    }
    return 0u;
}
