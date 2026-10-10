#include "psx.h"
#include "xport_trace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32 sub_8001178C(uint32 count, uint32 size);
sint32 sub_80052384(uint32 first, uint32 second, uint32 count);
void sub_80045088(uint32 allocation);
uint8 *v8_native_bios_firstfile(uint32 module_base, const char *path, uint8 *record);
uint8 *v8_native_bios_nextfile(uint32 module_base, uint8 *record);
void v8_native_shell_10C00(uint32 module_base, uint32 function);
void v8_native_shell_10768(uint32 module_base);
sint32 v8_native_shell_100F4(uint32 module_base, uint32 mode, uint32 *command, uint32 *result);
uint32 sub_80044080(uint32 enabled, uint32 volume, uint32 setting);

static void shell_menu_pending(const char *name)
{
    fprintf(stderr, "V8: Shell menu TODO %s\n", name);
    abort();
}

static uint32 shell_event_module_base;

static sint32 shell_event_0(void) { w_u32(shell_event_module_base + 0x13530u, 1u); return 0; }
static sint32 shell_event_1(void) { w_u32(shell_event_module_base + 0x13534u, 1u); return 0; }
static sint32 shell_event_2(void) { w_u32(shell_event_module_base + 0x13538u, 1u); return 0; }
static sint32 shell_event_3(void) { w_u32(shell_event_module_base + 0x1353Cu, 1u); return 0; }
static sint32 shell_event_4(void) { w_u32(shell_event_module_base + 0x13540u, 1u); return 0; }
static sint32 shell_event_5(void) { w_u32(shell_event_module_base + 0x13544u, 1u); return 0; }
static sint32 shell_event_6(void) { w_u32(shell_event_module_base + 0x13548u, 1u); return 0; }
static sint32 shell_event_7(void) { w_u32(shell_event_module_base + 0x1354Cu, 1u); return 0; }

static void shell_10768_interrupt(void)
{
    v8_native_shell_10768(shell_event_module_base);
}

static void shell_11080(uint32 module_base)
{
    uint32 index;
    for (index = 0u; index < 8u; ++index)
        (void)TestEvent(r_u32(module_base + 0x13510u + 4u * index));
    w_u32(module_base + 0x1353Cu, 0u);
    w_u32(module_base + 0x13538u, r_u32(module_base + 0x1353Cu));
    w_u32(module_base + 0x13534u, r_u32(module_base + 0x13538u));
    w_u32(module_base + 0x13530u, r_u32(module_base + 0x13534u));
    w_u32(module_base + 0x1354Cu, 0u);
    w_u32(module_base + 0x13548u, r_u32(module_base + 0x1354Cu));
    w_u32(module_base + 0x13544u, r_u32(module_base + 0x13548u));
    w_u32(module_base + 0x13540u, r_u32(module_base + 0x13544u));
}

static void shell_10DD0(uint32 module_base)
{
    static const sint32 specifications[4] = { 4, 0x8000, 0x100, 0x2000 };
    static const PsxEventCallback callbacks[8] = {
        shell_event_0, shell_event_1, shell_event_2, shell_event_3,
        shell_event_4, shell_event_5, shell_event_6, shell_event_7
    };
    sint32 critical;
    uint32 index, handle, event_class;
    critical = EnterCriticalSectionPSX();
    shell_event_module_base = module_base;
    for (index = 0u; index < 8u; ++index)
    {
        event_class = index < 4u ? 0xF4000001u : 0xF0000011u;
        handle = (uint32)OpenEvent(event_class, specifications[index & 3u],
            0x1000, callbacks[index]);
        w_u32(module_base + 0x13510u + index * 4u, handle);
    }
    for (index = 0u; index < 8u; ++index)
        (void)EnableEvent(r_u32(module_base + 0x13510u + index * 4u));
    shell_11080(module_base);
    if (critical == 1) ExitCriticalSection();
}

static void shell_EEAC(uint32 module_base)
{
    /* Original 10BF0 resets the directory operation stack */
    w_u32(module_base + 0x13354u, 0xFFFFFFFFu);
    w_u32(module_base + 0x13438u, 0u);
    w_u32(module_base + 0x1343Cu, 0u);
    w_u32(module_base + 0x13440u, 0u);
    w_u32(module_base + 0x13448u, 0xFFFFFFFFu);
    shell_10DD0(module_base);
    (void)InterruptCallback(7, shell_10768_interrupt);
}

void v8_native_shell_EEFC(uint32 module_base);
static void shell_EEFC(uint32 module_base)
{
    v8_native_shell_EEFC(module_base);
}

static void shell_100F4(uint32 module_base, uint32 mode, uint32 *first, uint32 *second);

static uint8 *shell_10BE0_firstfile(uint32 module_base, const char *path, uint8 *record)
{
    return v8_native_bios_firstfile(module_base, path, record);
}

static uint8 *shell_10940(uint32 module_base, const char *path, uint8 *record)
{
    uint32 table, bytes, end, cursor, name, prefix_offset = 0u;
    while ((sint8)path[prefix_offset] >= 0x3B)
    {
        w_u8(module_base + 0x13498u + prefix_offset, (uint8)path[prefix_offset]);
        ++prefix_offset;
    }
    w_u8(module_base + 0x13498u + prefix_offset, 0u);
    bytes = r_u32(0x154u);
    table = r_u32(0x150u);
    cursor = table;
    end = table + (bytes / 80u) * 80u;
    if (cursor >= end) return 0u;
    for (;;)
    {
        name = r_u32(cursor);
        if (name != 0u && strcmp((const char *)xport_guest_cptr(name, 1u),
            (const char *)xport_guest_cptr(module_base + 0x13498u, 1u)) == 0)
        {
            w_u32(module_base + 0x13490u, r_u32(cursor + 0x34u));
            break;
        }
        cursor += 80u;
        if (cursor >= end) return 0u;
    }
    /* Original re-reads both table fields before the patch pass */
    bytes = r_u32(0x154u);
    table = r_u32(0x150u);
    cursor = table;
    end = table + (bytes / 80u) * 80u;
    while (cursor < end)
    {
        name = r_u32(cursor);
        if (name != 0u && strcmp((const char *)xport_guest_cptr(name, 1u),
            (const char *)xport_guest_cptr(module_base + 0x13498u, 1u)) == 0)
        {
            w_u32(cursor + 0x34u, module_base + 0x10ADCu);
            break;
        }
        cursor += 80u;
    }
    return shell_10BE0_firstfile(module_base, path, record);
}

static uint8 *shell_10920(uint32 module_base, uint8 *record)
{
    return v8_native_bios_nextfile(module_base, record);
}

static void shell_10C00(uint32 module_base, uint32 callback)
{
    v8_native_shell_10C00(module_base, callback);
}

static uint32 shell_10714(uint32 status)
{
    if (status == 1u) return 2u;
    if ((sint32)status < 2)
        return status == 0u ? 0u : status | 0x8000u;
    if (status == 2u) return 1u;
    return status == 4u ? 3u : status | 0x8000u;
}

static uint32 shell_11260(uint32 module_base)
{
    uint32 flags;
    do
    {
        flags = r_u32(module_base + 0x13540u) +
            (r_u32(module_base + 0x13544u) << 1) +
            (r_u32(module_base + 0x13548u) << 2) +
            (r_u32(module_base + 0x1354Cu) << 3);
    } while (flags == 0u);
    (void)TestEvent(r_u32(module_base + 0x13510u));
    (void)TestEvent(r_u32(module_base + 0x13514u));
    (void)TestEvent(r_u32(module_base + 0x13518u));
    (void)TestEvent(r_u32(module_base + 0x1351Cu));
    w_u32(module_base + 0x1354Cu, 0u);
    w_u32(module_base + 0x13548u, r_u32(module_base + 0x1354Cu));
    w_u32(module_base + 0x13544u, r_u32(module_base + 0x13548u));
    w_u32(module_base + 0x13540u, r_u32(module_base + 0x13544u));
    return (uint32)((sint32)flags >> 1);
}

static uint32 shell_100E0(uint32 module_base, uint32 value)
{
    uint32 previous = r_u32(module_base + 0x13478u);
    w_u32(module_base + 0x13478u, value);
    return previous;
}

static uint32 shell_FE88(uint32 module_base, uint32 port, uint32 pattern,
    uint32 records, uint32 *result, uint32 start, uint32 count)
{
    char path[32];
    uint8 record[40];
    uint32 attempt = 0u, entry = 0u, copied = 0u, offset = 0u;
    uint32 status = 0u, previous, byte;
    uint8 *pointer;
    sint32 quotient, port_signed = (sint32)port;
    if (r_u32(module_base + 0x13438u) != 0u)
    {
        printf("%s", (const char *)xport_guest_cptr(module_base + 0x124Cu, 1u));
        return 0xFFFFFFFFu;
    }
    /* Original 107EC generates the BIOS device prefix without guest stack addresses */
    for (byte = 0u; byte < 6u; ++byte)
        path[byte] = (char)r_u8(module_base + 0x126Cu + byte);
    quotient = port_signed / 16;
    path[2] = (char)(quotient + 0x30);
    path[3] = (char)((uint32)port_signed - ((uint32)quotient << 4) + 0x30u);
    strcat(path, (const char *)xport_guest_cptr(pattern, 1u));
    w_u32(module_base + 0x13434u, r_u32(module_base + 0x13434u) |
        (1u << (r_u32(module_base + 0x13444u) & 31u)));
    if ((sint32)(start + count) > 0)
    {
        for (;;)
        {
            if (entry == 0u)
            {
                do
                {
                    shell_11080(module_base);
                    pointer = shell_10940(module_base, path, record);
                    if (pointer != 0u) break;
                    status = shell_10714(shell_11260(module_base));
                    if (status == 0u) break;
                    ++attempt;
                } while (attempt < 4u);
                if (pointer == 0u)
                {
                    previous = shell_100E0(module_base, 0u);
                    w_u32(module_base + 0x1348Cu, previous);
                    if (r_u32(module_base + 0x13438u) != 0u)
                        printf("%s", (const char *)xport_guest_cptr(module_base + 0x10E4u, 1u));
                    else
                    {
                        w_u32(module_base + 0x13438u, 2u);
                        w_u32(module_base + 0x1343Cu, 0u);
                        w_u32(module_base + 0x13440u, 0u);
                        w_u32(module_base + 0x13444u, port);
                        shell_10C00(module_base, module_base + 0xF1E0u);
                    }
                    shell_100F4(module_base, 0u, NULL, &status);
                    (void)shell_100E0(module_base, r_u32(module_base + 0x1348Cu));
                    return status;
                }
            }
            else if (shell_10920(module_base, record) == 0u) break;
            if ((sint32)entry >= (sint32)start && records != 0u)
            {
                for (byte = 0u; byte < 40u; byte += 4u)
                    w_u32(records + offset + byte, (uint32)record[byte] |
                        ((uint32)record[byte + 1u] << 8) |
                        ((uint32)record[byte + 2u] << 16) |
                        ((uint32)record[byte + 3u] << 24));
                offset += 40u;
                ++copied;
            }
            ++entry;
            if ((sint32)entry >= (sint32)(start + count)) break;
        }
    }
    if (result != NULL) *result = copied;
    return 0u;
}

static void shell_FA48(uint32 module_base, uint32 port, uint32 record,
    uint8 *output, uint32 offset, uint32 size)
{
    (void)module_base; (void)port; (void)record;
    (void)output; (void)offset; (void)size;
    shell_menu_pending("FA48 read selected card record");
}

static void shell_100F4(uint32 module_base, uint32 mode, uint32 *first, uint32 *second)
{
    (void)v8_native_shell_100F4(module_base, mode, first, second);
}

static void shell_A614(uint32 module_base)
{
    uint32 records, blocks, result_first, result_second;
    shell_EEAC(module_base);
    w_u8(module_base + 0x133B1u, 0u);
    w_u8(module_base + 0x133B0u, 0u);
    records = sub_8001178C(40u, 32u);
    w_u32(module_base + 0x133A0u, records);
    blocks = sub_8001178C(512u, 32u);
    w_u32(module_base + 0x133A4u, blocks);
    shell_FE88(module_base, 0u, module_base + 0xD18u,
        r_u32(module_base + 0x133A0u), &result_first, 0u, 15u);
    shell_FE88(module_base, 16u, module_base + 0xD18u,
        r_u32(module_base + 0x133A0u) + 0x280u, &result_second, 0u, 15u);
}

static void shell_A6C4(uint32 module_base)
{
    shell_EEFC(module_base);
    sub_80045088(r_u32(module_base + 0x133A0u));
    sub_80045088(r_u32(module_base + 0x133A4u));
}

static uint32 shell_EDF0(sint32 character)
{
    uint32 classification = r_u8(0x80065175u + ((uint32)character & 0xFFu));
    sint32 byte = (sint8)character;
    if ((classification & 4u) != 0u)
        return (uint32)(byte - 0x30);
    if ((classification & 3u) != 0u)
    {
        /* Original 80052D18 uses the mutable guest classification table */
        if ((classification & 1u) != 0u) byte += 0x20;
        return (uint32)((sint8)byte - 0x57);
    }
    return 0x0098967Fu;
}

static uint32 shell_EC60(uint32 text)
{
    uint32 sign = 1u, radix = 10u, total = 0u, digit;
    sint32 character;
    if (text == 0u) return 0u;
    while ((r_u8(0x80065175u + r_u8(text)) & 8u) != 0u) ++text;
    character = (sint8)r_u8(text);
    if (character == '-')
    {
        do
        {
            ++text;
            character = (sint8)r_u8(text);
            sign = 0u - sign;
        } while (character == '-');
    }
    if (character == '0')
    {
        ++text;
        character = (sint8)r_u8(text);
        if (character == 'X' || character == 'x') { ++text; radix = 16u; }
        else if (character == 'B' || character == 'b') { ++text; radix = 2u; }
        else radix = 8u;
    }
    for (;;)
    {
        digit = shell_EDF0((sint8)r_u8(text));
        ++text;
        if (digit >= radix) break;
        total = total * radix + digit;
    }
    return total * sign;
}

static void shell_A704(uint32 module_base, uint32 port, uint32 index)
{
    uint8 record_data[256];
    uint32 completion_first, completion_second, byte;
    uint32 record = r_u32(module_base + 0x133A0u) + (port + index) * 40u;
    uint32 enabled, volume, setting;
    shell_FA48(module_base, port, record, record_data, 512u, 256u);
    shell_100F4(module_base, 0u, &completion_first, &completion_second);
    for (byte = 0u; byte < 0x60u; byte += 4u)
        w_u32(0x80056774u + byte, (uint32)record_data[byte] |
            ((uint32)record_data[byte + 1u] << 8) |
            ((uint32)record_data[byte + 2u] << 16) |
            ((uint32)record_data[byte + 3u] << 24));
    enabled = (uint32)(sint32)(sint8)record_data[0x88u];
    volume = (uint32)record_data[0x84u] | ((uint32)record_data[0x85u] << 8);
    setting = (uint32)record_data[0x86u] | ((uint32)record_data[0x87u] << 8);
    for (byte = 0u; byte < 24u; ++byte) w_u8(0x800567D4u + byte, record_data[0x60u + byte]);
    for (byte = 0u; byte < 12u; ++byte) w_u8(0x80065950u + byte, record_data[0x78u + byte]);
    (void)sub_80044080(enabled, volume, setting);
    w_u8(0x8006531Au, record_data[0x89u]);
    w_u8(0x8006531Cu, record_data[0x8Au]);
    w_u8(0x8006531Du, record_data[0x8Bu]);
}

void v8_native_shell_AD7C(uint32 module_base)
{
    uint32 index, offset = 0u, maximum = 0u, selected = 0u, candidate;
    shell_A614(module_base);
    for (index = 0u; index < 15u; ++index)
    {
        if (sub_80052384(r_u32(module_base + 0x133A0u) + offset,
            module_base + 0xD1Cu, 12u) == 0)
        {
            candidate = shell_EC60(r_u32(module_base + 0x133A0u) + offset + 13u) + 1u;
            if (maximum < candidate) { maximum = candidate; selected = index; }
        }
        offset += 40u;
    }
    if (maximum != 0u) shell_A704(module_base, 0u, selected);
    shell_A6C4(module_base);
}

void v8_native_shell_11080(uint32 module_base)
{
    shell_11080(module_base);
}

uint32 v8_native_shell_11260(uint32 module_base)
{
    return shell_11260(module_base);
}

uint32 v8_native_shell_10714(uint32 status)
{
    return shell_10714(status);
}

uint32 v8_native_shell_100E0(uint32 module_base, uint32 value)
{
    return shell_100E0(module_base, value);
}
