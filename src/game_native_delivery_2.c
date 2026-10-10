#include "psx.h"
#include "xport.h"
#include "xport_trace.h"
#include <stdio.h>
#include <stdlib.h>

uint32 sub_800116F4(uint32 bytes);
void sub_80045088(uint32 address);
uint32 sub_80045134(uint32 address, uint32 bytes);
void sub_80044394(uint32 sound);
void sub_8001AA0C(uint32 object);
uint32 sub_8001F9CC(uint32 object, uint32 tick);
uint32 sub_80015A20(uint32 destination, uint32 bytes);
uint32 sub_80022524(uint32 *header, uint32 *remaining);
uint32 sub_8001B3D4(uint32 object, uint32 index, uint32 primitive_context);
uint32 sub_80022D54(uint32 object);
uint32 sub_8002305C(uint32 object);
uint32 sub_8002346C(uint32 object);
uint32 sub_80022E38(uint32 object);
uint32 sub_8002F998(uint32 object);
uint32 sub_8002D82C(uint32 object, uint32 update);
void sub_80042F5C(uint32 object);
void sub_8002EFE0(uint32 object, uint32 player_state);
void sub_8002D494(uint32 object, uint32 player_state);
void sub_8002D054(uint32 object);
void sub_8002D44C(uint32 object);
void sub_800129E8(uint32 player, const char *message);
void sub_80020890(uint32 object, uint32 mode);
uint32 sub_800447E8(uint32 channel, uint32 sound, uint32 mode, uint32 position);
uint32 sub_800446DC(uint32 position);
void xport_mips_overflow_exception(uint32 pc);
uint32 sub_80025400(uint32 x, uint32 z);
uint32 sub_800255F4(uint32 x, uint32 z);
uint32 sub_8001F51C(uint32 object, uint32 height, const sint32 *point, sint16 *normal);
uint32 sub_8001B1F8(uint32 object);
uint32 sub_80043FF0(uint32 enabled, uint32 mask);
uint32 sub_8002A350(uint32 source, uint32 output, uint32 index, uint32 table);

uint32 sub_8001D564(uint32 object)
{
    uint32 parent, sibling, first;
    FUNCTION_MARKER(0x8001D564u, "SLUS_005.10");
    parent = r_u32(object + 60u);
    first = r_u32(parent + 56u);
    sibling = r_u32(object + 52u);
    if (first == object)
        w_u32(parent + 56u, sibling);
    else
        w_u32(parent + 52u, sibling);
    if (sibling != 0u)
        w_u32(sibling + 60u, parent);
    w_u32(object + 52u, 0u);
    w_u32(object + 60u, 0u);
    return object;
}

uint32 sub_8001AFA0(uint32 table, uint32 index, uint32 kind)
{
    uint32 entry;
    FUNCTION_MARKER(0x8001AFA0u, "SLUS_005.10");
    index &= 0xFFFFu;
    kind &= 0xFFFFu;
    if (index == 0xFFFFu)
        return 0u;
    for (;;)
    {
        entry = table + 28u * index + 28u;
        if (r_u16(entry) == kind)
            return entry;
        index = r_u16(entry + 24u);
        if (index == 0xFFFFu)
            return 0u;
    }
}

uint32 sub_8001AFFC(uint32 object, uint32 index, uint32 kind)
{
    uint32 table, next;
    FUNCTION_MARKER(0x8001AFFCu, "SLUS_005.10");
    table = r_u32(object);
    next = r_u16(table + 28u * (index & 0xFFFFu) + 54u);
    return sub_8001AFA0(table, next, kind & 0xFFFFu);
}

uint32 sub_8003E254(uint32 object, sint32 x, sint32 z)
{
    uint32 result;
    FUNCTION_MARKER(0x8003E254u, "SLUS_005.10");
    result = sub_800116F4(44u);
    w_u32(result, object);
    w_u32(result + 36u, (uint32)(x / 16));
    w_u32(result + 40u, (uint32)(z / 16));
    return result;
}

uint32 sub_8001A91C(uint32 object)
{
    uint32 header, index, count, bytes;
    FUNCTION_MARKER(0x8001A91Cu, "SLUS_005.10");
    header = r_u32(object);
    count = r_u32(header + 16u);
    index = 0u;
    if ((sint32)count > 0)
        do
        {
            sub_8001B3D4(object, index & 0xFFFFu, header);
            count = r_u32(header + 16u);
            ++index;
        } while ((sint32)index < (sint32)count);
    bytes = r_u32(header + 20u);
    return sub_80045134(header, bytes - header);
}

uint32 sub_8001FC38(uint32 object, uint32 tick)
{
    uint32 next, child, result;
    FUNCTION_MARKER(0x8001FC38u, "SLUS_005.10");
    tick &= 0xFFFFu;
    do
    {
        result = r_u32(object);
        next = r_u32(object + 52u);
        result &= 4u;
        if (result == 0u)
        {
            result = sub_8001F9CC(object, tick);
            if ((sint32)result >= 0)
            {
                child = r_u32(object + 56u);
                if (child != 0u)
                    result = sub_8001FC38(child, tick);
            }
        }
        object = next;
    } while (object != 0u);
    return result;
}

uint32 sub_800225D4(uint32 *header, uint32 *remaining)
{
    uint32 bytes, output;
    FUNCTION_MARKER(0x800225D4u, "SLUS_005.10");
    bytes = sub_80022524(header, remaining);
    if (bytes == 0xFFFFFFFFu)
        return 0u;
    output = sub_800116F4(bytes != 0u ? bytes : 4u);
    sub_80015A20(output, bytes);
    return output;
}

void sub_8001AA38(uint32 object)
{
    uint32 value;
    FUNCTION_MARKER(0x8001AA38u, "SLUS_005.10");
    value = r_u32(object);
    if (value != 0u)
        sub_80045088(value);
    value = r_u32(object + 4u);
    if (value != 0u)
        sub_80045088(value);
    value = r_u32(object + 8u);
    if (value != 0u)
        sub_80044394(value);
    sub_8001AA0C(object);
}

uint32 sub_8004366C(uint32 matrix)
{
    uint32 first, second, third, fourth, last, result;
    FUNCTION_MARKER(0x8004366Cu, "SLUS_005.10");
    first = r_u32(matrix);
    second = r_u32(matrix + 4u);
    third = r_u32(matrix + 8u);
    xport_gte_write_control(0u, (first & 0xFFFFu) | (second & 0xFFFF0000u));
    fourth = r_u32(matrix + 12u);
    xport_gte_write_control(3u, (second & 0xFFFFu) | (third & 0xFFFF0000u));
    result = (first & 0xFFFF0000u) | (fourth & 0xFFFFu);
    fourth = (fourth & 0xFFFF0000u) | (third & 0xFFFFu);
    last = r_u32(matrix + 16u);
    xport_gte_write_control(1u, result);
    xport_gte_write_control(2u, fourth);
    xport_gte_write_control(4u, last);
    return result;
}

uint32 sub_8002A3E8(uint32 source, uint32 output, uint32 index)
{
    FUNCTION_MARKER(0x8002A3E8u, "SLUS_005.10");
    return sub_8002A350(source, output, index, 0x8005EA60u);
}

uint32 sub_8002A430(uint32 source, uint32 output, uint32 index)
{
    FUNCTION_MARKER(0x8002A430u, "SLUS_005.10");
    return sub_8002A350(source, output, index, 0x8005EAA8u);
}

uint32 sub_8002A4E4(uint32 source, uint32 output, uint32 index)
{
    FUNCTION_MARKER(0x8002A4E4u, "SLUS_005.10");
    return sub_8002A350(source, output, index, 0x8005EB5Cu);
}

static uint32 native2_tile_pointer(uint32 x, uint32 z)
{
    return r_u32(0x800911A0u + ((z >> 6) << 2) + ((x >> 6) << 7));
}

static uint32 native2_tile_height(uint32 pointer, uint32 x, uint32 z)
{
    return r_u16(pointer + ((z & 63u) << 1) + ((x & 63u) << 7)) & 0x7FFu;
}

static uint32 native2_multiply(uint32 a, uint32 b)
{
    return (uint32)((sint64)(sint32)a * (sint64)(sint32)b);
}

static uint32 native2_truncate16(uint32 value)
{
    if ((sint32)value < 0)
        value += 0xFFFFu;
    return (uint32)((sint32)value >> 16);
}

sint16 *sub_80025648(uint32 x, uint32 z, sint16 *output)
{
    uint32 ix, iz, first, second, base, adjacent, third;
    FUNCTION_MARKER(0x80025648u, "SLUS_005.10");
    ix = x >> 16;
    iz = z >> 16;
    if ((x & 0xFFFFu) + (z & 0xFFFFu) <= 0xFFFFu)
    {
        first = native2_tile_pointer(ix, iz);
        second = native2_tile_pointer(ix + 1u, iz);
        base = native2_tile_height(first, ix, iz);
        adjacent = native2_tile_height(second, ix + 1u, iz);
        output[1] = -32;
        output[0] = (sint16)(adjacent - base);
        third = native2_tile_pointer(ix, iz + 1u);
        output[2] = (sint16)(native2_tile_height(third, ix, iz + 1u) - base);
    }
    else
    {
        first = native2_tile_pointer(ix + 1u, iz + 1u);
        second = native2_tile_pointer(ix, iz + 1u);
        base = native2_tile_height(first, ix + 1u, iz + 1u);
        adjacent = native2_tile_height(second, ix, iz + 1u);
        output[1] = -32;
        output[0] = (sint16)(base - adjacent);
        third = native2_tile_pointer(ix + 1u, iz);
        output[2] = (sint16)(base - native2_tile_height(third, ix + 1u, iz));
    }
    return output;
}

sint16 *sub_80025800(sint32 x, sint32 z, sint16 *output)
{
    uint32 raw_x, raw_z, corrected, ix, iz, fx, fz, mx, mz;
    uint32 p00, p10, p01, p20, p11, p21, p02, p12;
    uint32 h00, h10, h01, h20, h11, h21, h02, h12;
    uint32 dx0, dx1, dz0, dz1, value;
    FUNCTION_MARKER(0x80025800u, "SLUS_005.10");
    raw_x = (uint32)x - 0x8000u;
    raw_z = (uint32)z - 0x8000u;
    corrected = (sint32)raw_x < 0 ? (uint32)x + 0x7FFFu : raw_x;
    ix = (uint32)((sint32)corrected >> 16);
    fx = raw_x - (ix << 16);
    corrected = (sint32)raw_z < 0 ? (uint32)z + 0x7FFFu : raw_z;
    iz = (uint32)((sint32)corrected >> 16);
    fz = raw_z - (iz << 16);
    p00 = native2_tile_pointer(ix, iz);
    p10 = native2_tile_pointer(ix + 1u, iz);
    h00 = native2_tile_height(p00, ix, iz);
    h10 = native2_tile_height(p10, ix + 1u, iz);
    p01 = native2_tile_pointer(ix, iz + 1u);
    h01 = native2_tile_height(p01, ix, iz + 1u);
    p20 = native2_tile_pointer(ix + 2u, iz);
    p11 = native2_tile_pointer(ix + 1u, iz + 1u);
    mx = 0x10000u - fx;
    h20 = native2_tile_height(p20, ix + 2u, iz);
    p21 = native2_tile_pointer(ix + 2u, iz + 1u);
    h11 = native2_tile_height(p11, ix + 1u, iz + 1u);
    h21 = native2_tile_height(p21, ix + 2u, iz + 1u);
    dx0 = native2_truncate16(native2_multiply(h10 - h00, mx) + native2_multiply(h20 - h10, fx));
    dx1 = native2_truncate16(native2_multiply(h11 - h01, mx) + native2_multiply(h21 - h11, fx));
    mz = 0x10000u - fz;
    value = native2_truncate16(native2_multiply(dx0, mz) + native2_multiply(dx1, fz));
    output[0] = (sint16)value;
    output[1] = -32;
    p02 = native2_tile_pointer(ix, iz + 2u);
    h02 = native2_tile_height(p02, ix, iz + 2u);
    p12 = native2_tile_pointer(ix + 1u, iz + 2u);
    h12 = native2_tile_height(p12, ix + 1u, iz + 2u);
    dz0 = native2_truncate16(native2_multiply(h01 - h00, mz) + native2_multiply(h02 - h01, fz));
    dz1 = native2_truncate16(native2_multiply(h11 - h10, mz) + native2_multiply(h12 - h11, fz));
    output[2] = (sint16)native2_truncate16(native2_multiply(dz0, mx) + native2_multiply(dz1, fx));
    return output;
}

sint32 sub_8001D748(uint32 object, const sint32 *point, sint16 *normal, uint32 *surface_out)
{
    sint32 height;
    uint32 candidate, result;
    FUNCTION_MARKER(0x8001D748u, "SLUS_005.10");
    height = sub_80025400(point[0], point[2]);
    candidate = r_u32(object + 116u);
    if (candidate != 0u)
    {
        result = sub_8001F51C(candidate, (uint32)height, point, normal);
        if (result == 0u)
        {
            candidate = r_u32(object + 120u);
            if (candidate != 0u)
                result = sub_8001F51C(candidate, (uint32)height, point, normal);
        }
        if (result != 0u)
        {
            if (surface_out != NULL)
                *surface_out = 0u;
            return (sint32)result;
        }
    }
    if (normal != NULL)
    {
        sub_80025648((uint32)point[0], (uint32)point[2], normal);
        VectorNormalSS((SVECTOR *)normal, (SVECTOR *)normal);
    }
    if (surface_out != NULL)
        *surface_out = sub_800255F4((uint32)point[0], (uint32)point[2]);
    return height;
}

void sub_800441C8(uint32 channel)
{
    FUNCTION_MARKER(0x800441C8u, "SLUS_005.10");
    if (channel != 0u)
        sub_80043FF0(0u, 1u << ((channel - 1u) & 31u));
}

void sub_80044574(uint32 channel, uint32 volume)
{
    FUNCTION_MARKER(0x80044574u, "SLUS_005.10");
    if (channel != 0u)
        SpuSetVoiceVolume((sint32)(channel - 1u), (sint16)volume, (sint16)(volume >> 16));
}

uint32 sub_8001B270(uint32 object, uint32 primitive_context)
{
    uint32 entry, owner, table, index, data, next, first, second, result;
    FUNCTION_MARKER(0x8001B270u, "SLUS_005.10");
    entry = sub_8001B1F8(object);
    if (entry == 0u)
        return 0u;
    owner = r_u32(object + 88u);
    index = r_u16(entry);
    data = r_u32(owner);
    table = r_u32(data + 4u);
    data = r_u32(table + 4u * (index & 0xFFFu));
    next = r_u32(data + 20u);
    second = r_u16(next + 18u) & 0x3FFFu;
    first = r_u16(data + 18u);
    result = sub_8001B3D4(owner, (first + second) & 0xFFFFu, primitive_context);
    w_u16(result + 8u, r_u16(result + 8u) | 0x20u);
    return result;
}

static uint32 native2_negate(uint32 value, uint32 pc)
{
    if (value == 0x80000000u)
        xport_mips_overflow_exception(pc);
    return 0u - value;
}

void sub_800439B8(uint32 matrix, uint32 x, uint32 y, uint32 z)
{
    uint32 a, b, c, d, e, first, second, third, negative_z;
    FUNCTION_MARKER(0x800439B8u, "SLUS_005.10");
    a = r_u32(matrix); b = r_u32(matrix + 4u); c = r_u32(matrix + 8u);
    d = r_u32(matrix + 12u); e = r_u32(matrix + 16u);
    xport_gte_write_control(0u, a); xport_gte_write_control(1u, b);
    xport_gte_write_control(2u, c); xport_gte_write_control(3u, d); xport_gte_write_control(4u, e);
    xport_gte_write_data(9u, 4096u); xport_gte_write_data(10u, z);
    xport_gte_write_data(11u, native2_negate(y, 0x800439ECu));
    negative_z = native2_negate(z, 0x800439F4u);
    xport_gte_mvmva(0x49E012u);
    first = xport_gte_read_data(9u); second = xport_gte_read_data(10u); third = xport_gte_read_data(11u);
    xport_gte_write_data(9u, negative_z); xport_gte_write_data(10u, 4096u); xport_gte_write_data(11u, x);
    xport_gte_mvmva(0x49E012u);
    w_u16(matrix, first); w_u16(matrix + 6u, second); w_u16(matrix + 12u, third);
    a = native2_negate(x, 0x80043A28u);
    first = xport_gte_read_data(9u); second = xport_gte_read_data(10u); third = xport_gte_read_data(11u);
    xport_gte_write_data(9u, y); xport_gte_write_data(10u, a); xport_gte_write_data(11u, 4096u);
    xport_gte_mvmva(0x49E012u);
    w_u16(matrix + 2u, first); w_u16(matrix + 8u, second); w_u16(matrix + 14u, third);
    first = xport_gte_read_data(9u); second = xport_gte_read_data(10u); third = xport_gte_read_data(11u);
    w_u16(matrix + 4u, first); w_u16(matrix + 10u, second); w_u16(matrix + 16u, third);
}

uint32 sub_80023940(uint32 object)
{
    uint32 kind, target;
    FUNCTION_MARKER(0x80023940u, "SLUS_005.10");
    kind = (uint32)r_s8(object + 8u);
    if (kind >= 5u)
        return 0x80010000u;
    target = r_u32(0x800104E0u + 4u * kind);
    switch (target)
    {
    case 0x80023978u: return sub_80022D54(object);
    case 0x80023988u: return sub_8002305C(object);
    case 0x80023998u: return sub_8002346C(object);
    case 0x800239A8u: return sub_80022E38(object);
    case 0x800239B0u: return target;
    default:
        /* TODO Translate execution at an unknown modified dispatch target */
        fprintf(stderr, "Unresolved 80023940 dispatch target=%08X kind=%u\n", target, kind);
        abort();
    }
}

uint32 sub_8002E2BC(uint32 object, uint32 reason, uint32 update)
{
    const uint32 gp = 0x80065304u;
    uint32 surface, player_state, flags, first, second, third, channel, kind;
    uint32 count, timer, value, previous, current, target, player;
    char message[64];
    FUNCTION_MARKER(0x8002E2BCu, "SLUS_005.10");
    if (reason == 2u)
    {
        sub_8002F998(object);
        return 0u;
    }
    if (reason == 3u)
        return sub_8002D82C(object, update);
    if (reason == 4u)
    {
        sub_80042F5C(object + 192u);
        return 0u;
    }
    if (reason != 0u)
        return 0u;
    if (r_s16(object + 6u) < 0)
    {
        first = r_u32(object + 36u);
        second = r_u32(object + 44u);
        surface = sub_800255F4(first, second);
        player_state = 0x80065C28u + 24u * ~(uint32)r_s16(object + 6u);
        if (r_s16(surface + 22u) == 7)
        {
            first = r_u32(object + 128u);
            second = r_u32(object + 132u);
            third = r_u32(object + 136u);
            w_u32(object + 128u, 0u - first);
            w_u32(object + 132u, 0u - second);
            w_u32(object + 136u, 0u - third);
        }
        flags = r_u32(object);
        if ((flags & 0x200000u) == 0u)
        {
            channel = r_u8(object + 211u);
            if (channel != 0u)
            {
                sub_800441C8(channel);
                w_u8(object + 210u, 0u);
                w_u8(object + 211u, 0u);
            }
        }
        else
        {
            kind = (uint32)r_s16(surface + 24u);
            current = r_u8(object + 210u);
            if (kind != current)
            {
                channel = r_u8(object + 211u);
                sub_800441C8(channel);
                kind = r_u8(surface + 24u);
                w_u8(object + 210u, kind);
                if (kind != 0u)
                {
                    target = r_u32(gp + 0x730u);
                    value = xport_guest_call3(target, object, 11u, surface);
                }
                else
                    value = 0u;
                w_u8(object + 211u, value);
            }
        }
        sub_8002EFE0(object, player_state);
        sub_8002D494(object, player_state);
        if (update != 0u)
            sub_8002D054(object);
    }
    else
    {
        count = r_u16(object + 176u);
        if (count == 0u)
            sub_80023940(object);
        else
        {
            count = (count - 1u) & 0xFFFFu;
            w_u16(object + 176u, count);
            if (count == 0u)
            {
                channel = (uint32)r_s8(object + 5u);
                value = r_u32(gp + 0x5F8u);
                sub_800447E8(channel, value, 31u, object + 36u);
                flags = r_u32(object);
                w_u8(object + 5u, 0u);
                w_u32(object, flags & 0xF7FFFFFFu);
            }
            else if (update != 0u)
            {
                value = sub_800446DC(object + 36u);
                channel = (uint32)r_s8(object + 5u);
                sub_80044574(channel, value);
            }
        }
    }
    timer = r_u8(object + 182u);
    if (timer != 0u)
    {
        timer = (timer - 1u) & 0xFFu;
        w_u8(object + 182u, timer);
        if (timer == 0u && r_u8(object + 185u) != 0u)
        {
            if (r_s16(object + 6u) < 0)
            {
                count = r_u8(object + 185u);
                sprintf(message, (const char *)psx_addr(0x80065738u, 1u), count);
                if (r_u32(gp + 16u) != 0u)
                    player = 0u - (uint32)r_s16(object + 6u);
                else
                    player = 0u;
                sub_800129E8(player, message);
                sub_8002D44C(object);
            }
            previous = r_u8(object + 186u);
            current = r_u8(object + 185u);
            w_u8(object + 182u, 30u);
            w_u8(object + 185u, 0u);
            w_u8(object + 186u, previous + current);
        }
    }
    if (update != 0u)
    {
        flags = r_u32(object);
        value = flags & 0xFFFE7FFFu;
        if ((flags & 0x10000u) != 0u)
            value |= 0x8000u;
        w_u32(object, value);
    }
    if (r_s16(object + 6u) != 0)
        sub_80020890(object, 0u);
    else
        sub_8002F998(object);
    return 0u;
}

void sub_8003E598(uint32 object, uint32 owner)
{
    uint32 cursor, opcode, i, first = 1u;
    sint32 bounds[6], value;
    FUNCTION_MARKER(0x8003E598u, "SLUS_005.10");
    cursor = r_u32(object + 92u);
    if (cursor == 0u)
        return;
    opcode = r_u16(cursor);
    while (opcode != 0u)
    {
        opcode = r_u16(cursor);
        if (opcode == 1u)
        {
            if (first != 0u)
            {
                bounds[0] = r_s32(cursor + 4u);
                bounds[1] = r_s32(cursor + 8u);
                bounds[2] = r_s32(cursor + 12u);
                bounds[3] = r_s32(cursor + 16u);
                bounds[4] = r_s32(cursor + 20u);
                bounds[5] = r_s32(cursor + 24u);
                first = 0u;
            }
            else
            {
                for (i = 0u; i < 3u; ++i)
                {
                    value = r_s32(cursor + 4u + 4u * i);
                    if (value < bounds[i])
                        bounds[i] = value;
                }
                for (i = 3u; i < 6u; ++i)
                {
                    value = r_s32(cursor + 4u + 4u * i);
                    if (bounds[i] < value)
                        bounds[i] = value;
                }
            }
            cursor += 28u;
        }
        else if (opcode == 2u)
            cursor += 12u * r_u16(cursor + 2u) + 4u;
        opcode = r_u16(cursor);
    }
    if (first != 0u)
    {
        /* Fail fast for the user-authorized undefined original bounds path */
        fprintf(stderr, "V8: bounds stream has no opcode 1 record (object %08X)\n", object);
        abort();
    }
    w_u32(object + 112u, sub_8003E254(owner, bounds[3], bounds[5]));
}
