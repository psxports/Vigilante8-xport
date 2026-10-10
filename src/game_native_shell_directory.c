#include "psx.h"
#include "xport_trace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void directory_pending(const char *name)
{
    fprintf(stderr, "V8: Shell directory TODO %s\n", name);
    abort();
}

uint32 v8_native_bios_allocate_file(void)
{
    uint32 descriptor;
    for (descriptor = 0x8648u; descriptor < 0x8908u; descriptor += 44u)
        if (r_u32(descriptor) == 0u) return descriptor;
    directory_pending("3060 exhausted descriptor diagnostic 2FC8");
    return 0u;
}

static uint32 directory_find_device(const char *name)
{
    uint32 node = 0x6EE0u, count = r_u32(0x7200u), pointer;
    if (count != 0u)
    {
        do
        {
            pointer = r_u32(node);
            if (pointer != 0u && strcmp((const char *)xport_guest_cptr(pointer, 1u), name) == 0)
                return node;
            node += 80u;
            count = r_u32(0x7200u);
        } while (node < 0x6EE0u + count * 80u);
    }
    w_u32(0x890Cu, 0u);
    directory_pending("3108 missing device diagnostics and 3DAC error handler");
    return 0u;
}

static sint32 directory_uppercase(sint32 character)
{
    uint32 byte = (uint32)character & 0xFFu;
    if ((r_u8(0xBFC0DDB1u + byte) & 2u) != 0u)
        return (sint8)(byte - 0x20u);
    return (sint8)character;
}

const char *v8_native_bios_parse_host_path(const char *path, uint32 *device, uint32 *unit)
{
    char name[36];
    uint32 length = 0u, number_start, position;
    const char *tail;
    while ((sint8)*path == 0x20) ++path;
    *unit = 0u;
    tail = path;
    while (*tail != ':' && *tail != 0)
    {
        name[length++] = *tail;
        ++tail;
    }
    name[length] = 0;
    if (*tail != 0)
    {
        if (length == 0u)
            directory_pending("31E8 empty device prefix original frame alias");
        ++tail;
        number_start = length;
        while (number_start != 0u &&
            (r_u8(0x73D1u + (uint8)name[number_start - 1u]) & 0x44u) != 0u)
            --number_start;
        if (number_start == 0u)
            directory_pending("31E8 all-number prefix original frame alias");
        for (position = number_start; name[position] != 0; ++position)
        {
            sint32 uppercase = directory_uppercase((sint8)name[position]);
            uint32 base = (r_u8(0x73D1u + (uint8)name[position]) & 4u) != 0u ? 0x30u : 0x37u;
            *unit = (*unit << 4) + (uint32)uppercase - base;
        }
        name[number_start] = 0;
    }
    *device = directory_find_device(name);
    return *device != 0u ? tail : NULL;
}

uint32 v8_native_bios_parse_path(uint32 path, uint32 *device, uint32 *unit)
{
    const char *host = (const char *)xport_guest_cptr(path, 1u);
    const char *tail = v8_native_bios_parse_host_path(host, device, unit);
    return tail != NULL ? path + (uint32)(tail - host) : 0xFFFFFFFFu;
}

void v8_native_bios_card_clear_events(void);
uint32 v8_native_bios_card_load_wait(uint32 channel);

static uint32 directory_pattern_matches(uint32 name, uint32 pattern)
{
    sint32 character = (sint8)r_u8(name), expected;
    while (character != 0)
    {
        expected = (sint8)r_u8(pattern);
        if (expected != '?' && expected != character) return 0u;
        ++pattern;
        ++name;
        character = (sint8)r_u8(name);
    }
    expected = (sint8)r_u8(pattern);
    return expected == character || expected == '?' ? 1u : 0u;
}

static uint32 directory_find_record(uint32 channel, uint32 start, uint32 pattern)
{
    sint32 port = (sint32)channel / 16;
    uint32 entry, index = start, state, wanted;
    if ((sint32)index >= 15) return 0xFFFFFFFFu;
    do
    {
        entry = 0xA000BA88u + (uint32)port * 480u + (index << 5);
        wanted = r_u32(0x8644u) != 0u ? 0xA1u : 0x51u;
        state = r_u32(entry);
        if (state == wanted && r_u8(entry + 10u) != 0u &&
            directory_pattern_matches(entry + 10u, pattern) != 0u)
        {
            w_u32(0xA0009F8Cu, index);
            return index;
        }
        ++index;
    } while ((sint32)index < 15);
    return 0xFFFFFFFFu;
}

static void directory_record_word(uint8 *record, uint32 offset, uint32 value)
{
    record[offset] = (uint8)value;
    record[offset + 1u] = (uint8)(value >> 8);
    record[offset + 2u] = (uint8)(value >> 16);
    record[offset + 3u] = (uint8)(value >> 24);
}

static uint8 *directory_bu_nextfile(uint32 descriptor, uint8 *record)
{
    uint32 channel = r_u32(descriptor + 4u), index, entry, byte;
    sint32 port = (sint32)channel / 16;
    if (r_u32(0xA0009F20u + (uint32)port * 4u) != 0u)
    {
        w_u32(descriptor + 0x18u, 16u);
        return NULL;
    }
    v8_native_bios_card_clear_events();
    index = directory_find_record(channel, r_u32(0xA0009F8Cu) + 1u, 0xA0009F98u);
    if (index == 0xFFFFFFFFu)
    {
        w_u32(descriptor + 0x18u, 2u);
        return NULL;
    }
    entry = 0xA000BA88u + (uint32)port * 480u + (index << 5);
    directory_record_word(record, 0x14u, r_u32(entry) & 0xF0u);
    directory_record_word(record, 0x20u, (index << 6) + 0x40u);
    directory_record_word(record, 0x18u, r_u32(entry + 4u));
    byte = 0u;
    do
    {
        record[byte] = r_u8(entry + 10u + byte);
    } while (record[byte++] != 0u);
    w_u32(descriptor + 0x18u, 0u);
    return record;
}

static uint8 *directory_bu_firstfile(uint32 module_base, uint32 descriptor,
    const char *filename, uint8 *record)
{
    uint32 channel = r_u32(descriptor + 4u), pattern = 0xA0009F98u, position = 0u;
    sint32 port = (sint32)channel / 16;
    w_u32(descriptor + 0x18u, 16u);
    if (r_u32(0xA0009F20u + (uint32)port * 4u) != 0u) return NULL;
    v8_native_bios_card_clear_events();
    if (v8_native_bios_card_load_wait(channel) == 0u) return NULL;
    if (filename == NULL || filename[0] == 0)
    {
        while (position < 20u) w_u8(pattern + position++, '?');
    }
    else
    {
        while (filename[position] != 0 && filename[position] != '*')
        {
            w_u8(pattern + position, (uint8)filename[position]);
            ++position;
        }
        if (filename[position] == '*')
            while (position < 20u) w_u8(pattern + position++, '?');
    }
    w_u8(pattern + position, 0u);
    w_u32(0xA0009F8Cu, 0xFFFFFFFFu);
    return directory_bu_nextfile(descriptor, record);
}

uint8 *v8_native_shell_10ADC(uint32 module_base, uint32 descriptor,
    const char *filename, uint8 *record)
{
    uint32 bytes, node, end, pointer, saved;
    if (r_u32(descriptor) == 0u) w_u32(descriptor, 1u);
    bytes = r_u32(0x154u);
    node = r_u32(0x150u);
    saved = r_u32(module_base + 0x13490u);
    end = node + (bytes / 80u) * 80u;
    while (node < end)
    {
        pointer = r_u32(node);
        if (pointer != 0u && strcmp((const char *)xport_guest_cptr(pointer, 1u),
            (const char *)xport_guest_cptr(module_base + 0x13498u, 1u)) == 0)
        {
            w_u32(node + 0x34u, saved);
            break;
        }
        node += 80u;
    }
    pointer = r_u32(module_base + 0x13490u);
    if (pointer == 0xBFC0A5E4u)
        return directory_bu_firstfile(module_base, descriptor, filename, record);
    fprintf(stderr, "V8: unsupported saved device firstfile target %08X\n", pointer);
    abort();
    return NULL;
}

uint8 *v8_native_bios_firstfile(uint32 module_base, const char *path, uint8 *record)
{
    uint32 descriptor = r_u32(0x7480u), device, unit, target;
    const char *filename;
    if (descriptor == 0u)
    {
        descriptor = v8_native_bios_allocate_file();
        w_u32(0x7480u, descriptor);
        if (descriptor == 0u) { w_u32(0x8640u, 24u); return NULL; }
    }
    filename = v8_native_bios_parse_host_path(path, &device, &unit);
    if (filename == NULL)
    {
        w_u32(0x8640u, 19u);
        w_u32(r_u32(0x7480u), 0u);
        return NULL;
    }
    descriptor = r_u32(0x7480u);
    w_u32(descriptor + 4u, unit);
    w_u32(descriptor + 0x1Cu, device);
    target = r_u32(device + 0x34u);
    if (target == module_base + 0x10ADCu)
        return v8_native_shell_10ADC(module_base, descriptor, filename, record);
    if (target == 0xBFC0A5E4u)
        return directory_bu_firstfile(module_base, descriptor, filename, record);
    fprintf(stderr, "V8: unsupported BIOS firstfile target %08X\n", target);
    abort();
    return NULL;
}

uint8 *v8_native_bios_nextfile(uint32 module_base, uint8 *record)
{
    uint32 descriptor = r_u32(0x7480u);
    uint32 device = r_u32(descriptor + 0x1Cu);
    uint32 target = r_u32(device + 0x38u);
    if (target != 0xBFC0A4B4u)
        directory_pending("Unknown BIOS nextfile device target");
    return directory_bu_nextfile(descriptor, record);
}
