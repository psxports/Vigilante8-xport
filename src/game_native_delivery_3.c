#include "psx.h"
#include "xport.h"
#include "xport_trace.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

uint32 sub_8002E630(uint32 asset, uint32 index, uint32 table);
uint32 sub_8003E2FC(uint32 object);
uint32 sub_8002263C(uint32 bytes, uint32 prepare);
uint32 sub_800173FC(uint32 object, uint32 delta, uint32 spin);
uint32 sub_80025400(uint32 x, uint32 z);
uint32 sub_80021B80(uint32 callback, uint32 asset, uint32 kind, uint32 flags);
void sub_80044484(uint32 voice, uint32 table, uint32 index, uint32 volume);
uint32 sub_8002A350(uint32 object, uint32 mode, uint32 kind, uint32 table);
uint32 sub_80022524(uint32 *header, uint32 *remaining);
uint32 sub_800225D4(uint32 *header, uint32 *remaining);
uint32 sub_800159B4(uint32 path);
uint32 sub_80015A00(void);
void sub_80044F64(uint32 destination, uint32 count);
uint32 sub_80045134(uint32 address, uint32 bytes);
uint32 sub_80015F80(uint32 path);
uint32 sub_80019034(uint32 asset, uint32 size);
uint32 sub_8001BDA0(uint32 object, uint32 index, uint32 incoming_s1);
void v8_native_187E4(uint32 image, uint8 *output);
uint32 v8_native_18C3C(uint8 *packet, const uint8 *texture);
uint32 v8_native_terrain_call3(uint32 callback, uint32 object, uint32 mode, uint32 value);
void sub_80017E0C(void);
uint32 sub_80017E3C(uint32 parent, uint32 type, uint32 x, uint32 y, uint32 width, uint32 height);
uint32 sub_80017EC4(uint32 node, uint32 split);
uint32 sub_80017F4C(uint32 node, uint32 split);
uint32 sub_80043754(uint32 matrix, uint32 scale, uint32 output);
void sub_8001D490(uint32 object);
uint32 sub_8001B1F8(uint32 object);
uint32 sub_800435C0(uint32 matrix, uint32 input, uint32 output);
uint32 sub_8004352C(uint32 matrix, uint32 input, uint32 output);
void sub_8003E2C4(uint32 object);
void sub_8001AA0C(uint32 object);
uint32 sub_8001B038(uint32 object, uint32 kind);
uint32 sub_800255F4(uint32 x, uint32 z);
void sub_80044550(uint32 voice, uint32 table, uint32 index, uint32 volume);
uint32 sub_8002A40C(uint32 object, uint32 mode, uint32 kind);
uint32 sub_8002A4C0(uint32 object, uint32 mode, uint32 kind);
uint32 sub_8002A52C(uint32 object, uint32 mode, uint32 kind);

uint32 sub_8001AC44(uint32, uint32, uint32, uint32);
uint32 sub_8001AFFC(uint32, uint32, uint32);
uint32 sub_8001AFA0(uint32, uint32, uint32);
uint32 sub_8001A640(uint32, uint32);
uint32 sub_8001A91C(uint32);
uint32 sub_8001A994(uint32);
uint32 sub_8001AF48(uint32, uint32);
uint32 sub_8001BDDC(uint32, uint32);
void sub_80045088(uint32);
uint32 sub_800116F4(uint32);
uint32 sub_80015A20(uint32, uint32);
uint32 sub_80015BE4(void);
uint32 sub_80015BF0(uint32, uint32);
uint32 v8_native_15BF0(uint32 position, uint32 relative);
uint32 sub_800156D4(void);
uint32 sub_800441F8(void);
uint32 sub_80017160(void);
uint32 sub_8003FC94(uint32);
uint32 sub_8002CCE8(uint32, uint32);
uint32 sub_8001B2FC(uint32, uint32, uint32);
uint32 sub_8001D470(uint32);
uint32 sub_8001D4F0(uint32, uint32);
uint32 sub_8001D708(uint32);
uint32 sub_8001B270(uint32, uint32);
uint32 sub_80044EFC(uint32, uint32, uint32);
uint32 sub_80046C94(uint32, uint32);
uint32 sub_80046C14(uint32, sint32, sint32);
uint32 sub_80046D04(uint32, uint32);
uint32 sub_80043FF0(uint32, uint32);
void sub_800439B8(uint32, uint32, uint32, uint32);
uint32 sub_8004C934(uint32, uint32);
uint32 sub_8001F51C(uint32, uint32, const sint32 *, sint16 *);
sint16 *sub_80025800(sint32, sint32, sint16 *);
uint32 xport_guest_call4_with_registers(uint32, uint32 *);

static sint32 native3_div(sint32 dividend, sint32 divisor)
{
    if (divisor == 0)
        return dividend < 0 ? 1 : -1;
    if (dividend == (sint32)0x80000000u && divisor == -1)
        return dividend;
    return dividend / divisor;
}

static uint32 native3_swap32(uint32 value)
{
    return (value >> 24) | ((value >> 8) & 0xFF00u) | ((value << 8) & 0xFF0000u) | (value << 24);
}

void v8_native_stream_read_host(void *destination, uint32 bytes)
{
    uint8 *out = (uint8 *)destination;
    uint32 position, offset, chunk, source, i;
    position = r_u32(0x800659B0u);
    offset = position & 2047u;
    if (offset != 0u)
    {
        chunk = (0u - position) & 2047u;
        if ((sint32)bytes < (sint32)chunk)
            chunk = bytes;
        source = r_u32(0x800659A0u) + offset;
        for (i = 0u; i < chunk; ++i)
            out[i] = r_u8(source + i);
        position = r_u32(0x800659B0u);
        out += chunk;
        bytes -= chunk;
        w_u32(0x800659B0u, position + chunk);
    }
    while ((sint32)bytes >= 2048)
    {
        source = sub_800156D4();
        for (i = 0u; i < 2048u; ++i)
            out[i] = r_u8(source + i);
        position = r_u32(0x800659B0u);
        out += 2048u;
        bytes -= 2048u;
        w_u32(0x800659B0u, position + 2048u);
    }
    if (bytes != 0u)
    {
        source = sub_800156D4();
        w_u32(0x800659A0u, source);
        for (i = 0u; i < bytes; ++i)
            out[i] = r_u8(source + i);
        position = r_u32(0x800659B0u);
        w_u32(0x800659B0u, position + bytes);
    }
}

uint32 sub_80022524(uint32 *header, uint32 *remaining)
{
    uint32 length, result;
    FUNCTION_MARKER(0x80022524u, "SLUS_005.10");
    v8_native_stream_read_host(header, 8u);
    length = native3_swap32(header[1]);
    header[1] = length;
    result = (length + 1u) & ~1u;
    *remaining = *remaining - 8u - result;
    if (header[0] == 0x4D524F46u)
    {
        v8_native_stream_read_host(header, 4u);
        header[1] -= 4u;
        result = 0xFFFFFFFFu;
    }
    return result;
}

uint32 sub_8002263C(uint32 bytes, uint32 prepare)
{
    uint32 asset = 0u, animation = 0u, sound = 0u, header[2], size, tag, object;
    FUNCTION_MARKER(0x8002263Cu, "SLUS_005.10");
    while (bytes != 0u)
    {
        size = sub_80022524(header, &bytes);
        tag = native3_swap32(header[0]);
        if (tag == 0x42494E20u)
        {
            asset = sub_800116F4(size);
            sub_80015A20(asset, size);
        }
        else if (tag == 0x414E4D20u)
        {
            animation = sub_800116F4(size);
            sub_80015A20(animation, size);
        }
        else if (tag == 0x534E4420u)
        {
            size += r_u32(0x800659B0u);
            sound = sub_800441F8();
            v8_native_15BF0(size, 0u);
        }
    }
    object = sub_8001A640(asset, animation);
    if (prepare != 0u)
        sub_8001A91C(object);
    if (sound != 0u)
        w_u32(object + 8u, sound);
    return object;
}

uint32 sub_80021B80(uint32 callback, uint32 asset, uint32 kind, uint32 flags)
{
    uint32 size = 128u, result, arguments[32] = {0u};
    FUNCTION_MARKER(0x80021B80u, "SLUS_005.10");
    if (callback != 0u)
    {
        arguments[4] = asset; arguments[5] = 7u; arguments[6] = kind & 0xFFFFu; arguments[7] = flags;
        result = xport_guest_call4_with_registers(callback, arguments);
        if (result != 0u)
            return result;
        arguments[4] = 0u; arguments[5] = 6u; arguments[6] = 0u;
        size = xport_guest_call4_with_registers(callback, arguments);
        if (size == 0u)
            size = 128u;
    }
    if (asset != 0u)
        return sub_8001AC44(asset, kind & 0xFFFFu, size, flags);
    return sub_8001D470(size);
}

void sub_8001AA0C(uint32 object)
{
    FUNCTION_MARKER(0x8001AA0Cu, "SLUS_005.10");
    sub_8001A994(object);
    sub_80045088(object);
}

void sub_8003E2C4(uint32 object)
{
    FUNCTION_MARKER(0x8003E2C4u, "SLUS_005.10");
    if (object != 0u)
    {
        sub_8001BDDC(r_u32(object), 0u);
        sub_80045088(object);
    }
}

void sub_8001D490(uint32 object)
{
    uint32 child;
    FUNCTION_MARKER(0x8001D490u, "SLUS_005.10");
    child = r_u32(object + 104u);
    if (child != 0u)
        sub_8001BDDC(child, 0u);
    if ((r_u32(object) & 8u) != 0u)
        sub_8003E2C4(r_u32(object + 112u));
    sub_8001AF48(object, 0u);
}

uint32 sub_8001B038(uint32 object, uint32 kind)
{
    uint32 table, index;
    FUNCTION_MARKER(0x8001B038u, "SLUS_005.10");
    table = r_u32(r_u32(object + 88u));
    index = r_u16(object + 10u);
    return sub_8001AFA0(table, r_u16(table + 28u * index + 54u), kind & 0xFFFFu);
}

uint32 sub_8001B1F8(uint32 object)
{
    uint32 table, index, node;
    FUNCTION_MARKER(0x8001B1F8u, "SLUS_005.10");
    table = r_u32(r_u32(object + 88u));
    index = r_u16(table + 28u * r_u16(object + 10u) + 54u);
    while (index != 0xFFFFu)
    {
        node = table + 28u * index + 28u;
        if ((r_u16(node) >> 12) == 11u)
            return node;
        index = r_u16(node + 24u);
    }
    return 0u;
}

uint32 sub_8002A350(uint32 object, uint32 mode, uint32 kind, uint32 table)
{
    uint32 position, flags;
    FUNCTION_MARKER(0x8002A350u, "SLUS_005.10");
    if (mode == 7u)
        return sub_8002E630(object, kind & 0xFFFFu, table);
    if (mode == 1u)
    {
        flags = r_u32(object);
        position = r_u32(object + 76u);
        w_u32(object, flags | 0x88u);
        flags = r_u8(object + 3u);
        w_u32(object + 100u, 0x8002E2BCu);
        position -= 0x8000u;
        w_u32(object + 76u, position);
        w_u32(object + 40u, position);
        sub_8002CCE8(object, flags | 1u);
        flags = r_u16(object);
        position = r_u32(0x80065AD4u);
        w_u32(object, flags);
        w_u32(object + 228u, position);
    }
    return 0u;
}

uint32 sub_8002A40C(uint32 object, uint32 mode, uint32 kind)
{
    FUNCTION_MARKER(0x8002A40Cu, "SLUS_005.10");
    return sub_8002A350(object, mode, kind, 0x8005EA84u);
}
uint32 sub_8002A4C0(uint32 object, uint32 mode, uint32 kind)
{
    FUNCTION_MARKER(0x8002A4C0u, "SLUS_005.10");
    return sub_8002A350(object, mode, kind, 0x8005EB38u);
}
uint32 sub_8002A52C(uint32 object, uint32 mode, uint32 kind)
{
    FUNCTION_MARKER(0x8002A52Cu, "SLUS_005.10");
    return sub_8002A350(object, mode, kind, 0x8005EBA4u);
}

void sub_80044484(uint32 voice, uint32 table, uint32 index, uint32 volume)
{
    uint32 random, row, product, channel;
    FUNCTION_MARKER(0x80044484u, "SLUS_005.10");
    if (voice == 0u)
        return;
    random = sub_80017160();
    row = table + (index << 2);
    product = (uint32)(sint32)((sint16)r_u16(row + 6u)) * (random + 0x1C000u);
    channel = voice - 1u;
    sub_80046C94(channel, ((uint32)((sint32)product >> 17)) & 0xFFFFu);
    sub_80046C14(channel, (sint16)volume, (sint32)volume >> 16);
    sub_80046D04(channel, r_u16(row + 4u) << 3);
    sub_80043FF0(1u, 1u << (channel & 31u));
    w_u8(0x800A2FF0u + channel, r_u8(0x8005FFB4u));
}

void sub_80044550(uint32 voice, uint32 table, uint32 index, uint32 volume)
{
    FUNCTION_MARKER(0x80044550u, "SLUS_005.10");
    sub_80044484(voice, table, index, (volume << 16) + volume);
}

static uint32 native3_height_sample(uint32 x, uint32 z)
{
    uint32 cell = r_u32(0x800911A0u + ((z >> 6) << 2) + ((x >> 6) << 7));
    return r_u16(cell + ((z & 63u) << 1) + ((x & 63u) << 7)) & 2047u;
}

uint32 sub_80025400(uint32 x, uint32 z)
{
    uint32 xi = x >> 16, zi = z >> 16, xf = x & 65535u, zf = z & 65535u;
    uint32 height, hx, hz, accumulator;
    FUNCTION_MARKER(0x80025400u, "SLUS_005.10");
    if (xf + zf <= 65535u)
    {
        height = native3_height_sample(xi, zi);
        hx = native3_height_sample(xi + 1u, zi);
        hz = native3_height_sample(xi, zi + 1u);
    }
    else
    {
        height = native3_height_sample(xi + 1u, zi + 1u);
        hx = native3_height_sample(xi, zi + 1u);
        hz = native3_height_sample(xi + 1u, zi);
        xf = 65536u - xf;
        zf = 65536u - zf;
    }
    accumulator = (height << 16) + xf * (hx - height) + zf * (hz - height);
    return (uint32)((sint32)accumulator / 32);
}

uint32 sub_800255F4(uint32 x, uint32 z)
{
    uint32 cell;
    FUNCTION_MARKER(0x800255F4u, "SLUS_005.10");
    cell = r_u32(0x800911A0u + ((z >> 22) << 2) + ((x >> 22) << 7));
    return 0x8008F020u + ((uint32)r_u8(cell + ((z >> 16) & 63u) + ((x >> 10) & 0xFC0u) + 8192u) << 5);
}

static void native3_scale_matrix_host(uint32 matrix, const sint32 *scale, uint32 *output)
{
    uint32 packed, next, low, high, i;
    static const uint8 columns[9] = {0u, 1u, 2u, 0u, 1u, 2u, 0u, 1u, 2u};
    packed = r_u32(matrix);
    for (i = 0u; i < 4u; ++i)
    {
        next = r_u32(matrix + 4u * (i + 1u));
        low = (uint32)(sint32)(sint16)packed * (uint32)scale[columns[2u * i]];
        high = (uint32)((sint32)packed >> 16) * (uint32)scale[columns[2u * i + 1u]];
        output[i] = ((uint32)((sint32)low >> 12) & 0xFFFFu) | ((uint32)((sint32)high >> 12) << 16);
        packed = next;
    }
    low = (uint32)(sint32)(sint16)packed * (uint32)scale[2];
    output[4] = (uint32)((sint32)low >> 12);
}

uint32 sub_80043754(uint32 matrix, uint32 scale, uint32 output)
{
    sint32 scales[3];
    uint32 packed, next, low, high, i;
    static const uint8 columns[9] = {0u, 1u, 2u, 0u, 1u, 2u, 0u, 1u, 2u};
    FUNCTION_MARKER(0x80043754u, "SLUS_005.10");
    packed = r_u32(matrix);
    scales[0] = (sint32)r_u32(scale);
    scales[1] = (sint32)r_u32(scale + 4u);
    scales[2] = (sint32)r_u32(scale + 8u);
    for (i = 0u; i < 4u; ++i)
    {
        next = r_u32(matrix + 4u * (i + 1u));
        low = (uint32)(sint32)(sint16)packed * (uint32)scales[columns[2u * i]];
        high = (uint32)((sint32)packed >> 16) * (uint32)scales[columns[2u * i + 1u]];
        w_u32(output + 4u * i, ((uint32)((sint32)low >> 12) & 0xFFFFu) | ((uint32)((sint32)high >> 12) << 16));
        packed = next;
    }
    low = (uint32)(sint32)(sint16)packed * (uint32)scales[2];
    w_u32(output + 16u, (uint32)((sint32)low >> 12));
    return matrix;
}

static uint32 native3_transform_long(uint32 matrix, uint32 input, uint32 output, uint32 subtract_translation, const sint32 *host_input, sint32 *host_output)
{
    uint32 words[5], values[3], high[3], low[3], i;
    for (i = 0u; i < 5u; ++i)
        words[i] = r_u32(matrix + 4u * i);
    xport_gte_write_control(0u, (words[0] & 0xFFFFu) | (words[1] & 0xFFFF0000u));
    xport_gte_write_control(3u, (words[1] & 0xFFFFu) | (words[2] & 0xFFFF0000u));
    xport_gte_write_control(1u, (words[0] & 0xFFFF0000u) | (words[3] & 0xFFFFu));
    xport_gte_write_control(2u, (words[2] & 0xFFFFu) | (words[3] & 0xFFFF0000u));
    xport_gte_write_control(4u, words[4]);
    for (i = 0u; i < 3u; ++i)
        values[i] = host_input != NULL ? (uint32)host_input[i] : r_u32(input + 4u * i);
    if (subtract_translation != 0u)
        for (i = 0u; i < 3u; ++i)
            values[i] -= r_u32(matrix + 20u + 4u * i);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_data(9u + i, (uint32)((sint32)values[i] >> 15));
    xport_gte_execute(0x4A41E012u);
    for (i = 0u; i < 3u; ++i)
        high[i] = xport_gte_read_data(25u + i);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_data(9u + i, values[i] & 0x7FFFu);
    xport_gte_execute(0x4A49E012u);
    for (i = 0u; i < 3u; ++i)
        low[i] = xport_gte_read_data(25u + i);
    for (i = 0u; i < 3u; ++i)
    {
        if (host_output != NULL)
            host_output[i] = (sint32)(low[i] + (high[i] << 3));
        else
            w_u32(output + 4u * i, low[i] + (high[i] << 3));
    }
    return output;
}

uint32 sub_8004352C(uint32 matrix, uint32 input, uint32 output)
{
    FUNCTION_MARKER(0x8004352Cu, "SLUS_005.10");
    return native3_transform_long(matrix, input, output, 0u, NULL, NULL);
}

uint32 sub_800435C0(uint32 matrix, uint32 input, uint32 output)
{
    FUNCTION_MARKER(0x800435C0u, "SLUS_005.10");
    return native3_transform_long(matrix, input, output, 1u, NULL, NULL);
}

uint32 sub_800173FC(uint32 object, uint32 delta, uint32 spin)
{
    uint32 value, previous, product, i;
    sint32 angles[3];
    FUNCTION_MARKER(0x800173FCu, "SLUS_005.10");
    value = r_u32(object + 128u) + r_u32(delta);
    w_u32(object + 128u, value);
    value = r_u32(object + 132u);
    previous = r_u32(object + 136u);
    value += r_u32(delta + 4u);
    w_u32(object + 132u, value);
    w_u32(object + 136u, previous + r_u32(delta + 8u));
    for (i = 0u; i < 3u; ++i)
    {
        product = r_u32(spin + 4u * i) * (uint32)(sint32)((sint16)r_u16(object + 156u + 2u * i));
        value = r_u32(object + 144u + 4u * i) + (uint32)((sint32)product / 64);
        w_u32(object + 144u + 4u * i, value);
    }
    for (i = 0u; i < 3u; ++i)
        angles[i] = (sint32)r_u32(object + 144u + 4u * i) / 128;
    sub_800439B8(object + 16u, angles[0], angles[1], angles[2]);
    for (i = 0u; i < 3u; ++i)
    {
        value = r_u32(object + 36u + 4u * i) + (uint32)((sint32)r_u32(object + 128u + 4u * i) / 128);
        w_u32(object + 36u + 4u * i, value);
    }
    return sub_8004C934(object + 16u, object + 16u);
}

static uint32 native3_compose_matrix_host(const uint32 *left, const uint32 *right, uint32 output)
{
    uint32 i, first[3], second[3], last[2];
    for (i = 0u; i < 5u; ++i)
        xport_gte_write_control(i, left[i]);
    xport_gte_write_data(0u, (right[0] & 0xFFFFu) | (right[1] & 0xFFFF0000u));
    xport_gte_write_data(1u, right[3]);
    xport_gte_execute(0x4A486012u);
    for (i = 0u; i < 3u; ++i)
        first[i] = xport_gte_read_data(9u + i);
    xport_gte_write_data(0u, (right[0] >> 16) | (right[2] << 16));
    xport_gte_write_data(1u, (uint32)((sint32)right[3] >> 16));
    xport_gte_execute(0x4A486012u);
    for (i = 0u; i < 3u; ++i)
        second[i] = xport_gte_read_data(9u + i);
    xport_gte_write_data(0u, (right[1] & 0xFFFFu) | (right[2] & 0xFFFF0000u));
    xport_gte_write_data(1u, right[4]);
    xport_gte_execute(0x4A486012u);
    w_u32(output, (first[0] & 0xFFFFu) | (second[0] << 16));
    w_u32(output + 12u, (first[2] & 0xFFFFu) | (second[2] << 16));
    last[0] = xport_gte_read_data(9u);
    last[1] = xport_gte_read_data(10u);
    w_u32(output + 4u, (last[0] & 0xFFFFu) | (first[1] << 16));
    w_u32(output + 8u, (second[1] & 0xFFFFu) | (last[1] << 16));
    w_u32(output + 16u, xport_gte_read_data(11u));
    return output;
}

uint32 sub_8003E2FC(uint32 object)
{
    uint32 transform, height, result = 0u, overlay;
    sint16 normal[3];
    sint32 scale[3];
    uint32 slope[5] = {0u}, scaled[5];
    FUNCTION_MARKER(0x8003E2FCu, "SLUS_005.10");
    transform = r_u32(object + 112u);
    height = sub_80025400(r_u32(object + 36u), r_u32(object + 44u));
    w_u32(transform + 24u, r_u32(object + 36u));
    w_u32(transform + 32u, r_u32(object + 44u));
    overlay = r_u32(object + 116u);
    if (overlay != 0u)
    {
        result = sub_8001F51C(overlay, height,
            (const sint32 *)psx_addr(object + 36u, 12u), normal);
        if (result == 0u)
        {
            overlay = r_u32(object + 120u);
            if (overlay != 0u)
                result = sub_8001F51C(overlay, height,
                    (const sint32 *)psx_addr(object + 36u, 12u), normal);
        }
    }
    if (result != 0u)
        w_u32(transform + 28u, result);
    else
    {
        w_u32(transform + 28u, height);
        sub_80025800((sint32)r_u32(object + 36u), (sint32)r_u32(object + 44u), normal);
    }
    if ((r_u16(r_u32(transform)) & 8u) != 0u)
    {
        w_u16(transform + 4u, 4096u);
        w_u16(transform + 20u, 4096u);
        w_u16(transform + 18u, 0u);
        w_u16(transform + 16u, 0u);
        w_u16(transform + 12u, 0u);
        w_u16(transform + 8u, 0u);
        w_u16(transform + 6u, 0u);
        result = (uint32)(native3_div(-4096 * (sint32)normal[0], normal[1]));
        w_u16(transform + 10u, (uint16)result);
        result = (uint32)(native3_div(-4096 * (sint32)normal[2], normal[1]));
        w_u16(transform + 14u, (uint16)result);
        return result;
    }
    slope[0] = 4096u;
    slope[4] = 4096u;
    result = normal[1] != 0 ? (uint32)(native3_div(-4096 * (sint32)normal[0], normal[1])) : (uint32)(-16 * (sint32)normal[0]);
    slope[1] = (result & 0xFFFFu) << 16;
    result = normal[1] != 0 ? (uint32)(native3_div(-4096 * (sint32)normal[2], normal[1])) : (uint32)(-16 * (sint32)normal[2]);
    slope[2] = (result & 0xFFFFu) << 16;
    scale[0] = (sint32)r_u32(transform + 36u);
    if (((sint16)r_u16(object + 24u)) <= 0)
        scale[0] = (sint32)(0u - (uint32)scale[0]);
    scale[1] = 0;
    scale[2] = (sint32)r_u32(transform + 40u);
    native3_scale_matrix_host(object + 16u, scale, scaled);
    return native3_compose_matrix_host(slope, scaled, transform + 4u);
}

uint32 sub_8002E630(uint32 asset, uint32 index, uint32 table)
{
    uint32 object, child, node, part, definition, source, j, kind, value, flags, slot;
    sint32 denominator;
    FUNCTION_MARKER(0x8002E630u, "SLUS_005.10");
    index &= 0xFFFFu;
    object = sub_8001AC44(asset, index, 292u, r_u32(asset + 4u) != 0u ? 8u : 0u);
    flags = r_u32(object);
    w_u16(object + 6u, 0u);
    w_u8(object + 4u, 2u);
    w_u32(object, flags | 0x6000u);
    w_u16(object + 12u, r_u16(table + 28u));
    value = r_u8(table + 13u);
    w_u16(object + 212u, 1024u);
    w_u8(object + 208u, (uint8)value);
    w_u32(object + 220u, r_u32(table + 16u));
    if (r_u32(asset + 4u) != 0u)
        w_u32(object, r_u32(object) | 4u);
    value = r_u32(object + 76u);
    w_u32(object + 100u, 0x8002E2BCu);
    w_u32(object + 216u, 0u - value);
    for (j = 0u; j < 12u; ++j)
        w_u32(object + 280u - 4u * j, 0u);
    for (child = r_u32(object + 56u); child != 0u; child = r_u32(child + 52u))
    {
        if (r_u16(child + 6u) < 4u)
        {
            w_u8(child + 8u, (uint8)(sub_8003FC94(child) + 1u));
            slot = (uint32)(sint32)((sint16)r_u16(child + 6u));
            value = r_u16(table + 28u);
            w_u16(child + 12u, (uint16)value);
            w_u32(object + 236u + (slot << 2), child);
        }
    }
    for (j = 0u; j < 4u; ++j)
    {
        kind = 9u;
        if ((r_u32(0x80065908u) & 1u) == 0u)
            kind = r_u16(table + 2u * (j >> 1));
        part = sub_8001AC44(r_u32(0x800737D4u), kind, 156u, 0u);
        w_u8(part + 4u, 8u);
        definition = r_u32(r_u32(0x800737D4u)) + 28u * kind + 28u;
        node = sub_8001AFFC(asset, index, j + 0x8000u);
        sub_8001B2FC(object, node, part);
        w_u32(object + 236u + 4u * (j + 4u), part);
        source = r_u16(node + 26u);
        value = source == 0xFFFFu ? 0u : r_u32(r_u32(asset) + 28u * source + 36u);
        source = r_u32(part + 76u);
        w_u32(part + 128u, value);
        w_u32(part + 136u, source);
        w_u32(part + 132u, source);
        source = table + 2u * (j >> 1);
        w_u16(part + 140u, r_u16(source + 4u));
        w_u16(part + 142u, r_u16(source + 8u));
        value = 0u - r_u32(definition + 8u);
        denominator = (sint32)(value * 25734u) / 4096;
        w_u32(part + 144u, value);
        /* MIPS DIV returns minus one for this positive dividend and zero divisor */
        value = denominator != 0 ? (uint32)(16777216 / denominator) : 0xFFFFFFFFu;
        w_u32(part + 148u, value);
        value = sub_80017160();
        w_u32(part + 64u, value & 0xFFFFu);
        w_u16(part + 68u, (uint16)((j & 1u) << 11));
        value = r_u8(table + 12u);
        flags = r_u32(part);
        value = (((value >> j) & 1u) << 16) | (j << 19);
        if (j < 2u)
            value |= 0x20000u;
        w_u32(part, flags | value);
        sub_8001D708(part);
    }
    child = sub_8001D470(128u);
    w_u32(object + 248u, child);
    node = sub_8001AFFC(asset, index, 0x8100u);
    if (node != 0u)
        sub_8001B2FC(object, node, child);
    else
    {
        w_u32(child + 76u, 0xFFFFAAABu);
        sub_8001D708(child);
        sub_8001D4F0(object, child);
    }
    value = r_u32(table + 20u);
    source = (uint32)(sint32)((sint16)r_u16(table + 24u));
    w_u32(object + 156u, value);
    w_u16(object + 160u, (uint16)source);
    value = r_u16(table + 26u);
    w_u16(object + 162u, (uint16)value);
    sub_80044EFC(object + 144u, 0u, 12u);
    value = r_u32(object + 144u);
    source = r_u32(object + 148u);
    flags = r_u32(object + 152u);
    w_u32(object + 128u, value);
    w_u32(object + 132u, source);
    w_u32(object + 136u, flags);
    w_u32(object + 120u, 0u);
    w_u32(object + 116u, 0u);
    sub_80044EFC(object + 164u, 0u, 28u);
    w_u8(object + 178u, 1u);
    w_u16(object + 172u, r_u8(table + 14u));
    w_u16(object + 168u, (uint16)(sint16)(sint8)r_u8(table + 30u));
    w_u16(object + 170u, (uint16)(sint16)(sint8)r_u8(table + 31u));
    value = r_u8(table + 15u);
    w_u8(object + 180u, (uint8)value);
    /* The last original S1 value is the allocated child used by primitive creation */
    w_u32(object + 124u, sub_8001B270(object, part));
    return object;
}

uint32 v8_native_173FC(uint32 object, const sint32 *force, const sint32 *torque)
{
    uint32 value, previous, product, i;
    sint32 angles[3];
    value = r_u32(object + 128u) + (uint32)force[0];
    w_u32(object + 128u, value);
    value = r_u32(object + 132u);
    previous = r_u32(object + 136u);
    value += (uint32)force[1];
    w_u32(object + 132u, value);
    w_u32(object + 136u, previous + (uint32)force[2]);
    for (i = 0u; i < 3u; ++i)
    {
        product = (uint32)torque[i] * (uint32)(sint32)((sint16)r_u16(object + 156u + 2u * i));
        value = r_u32(object + 144u + 4u * i) + (uint32)((sint32)product / 64);
        w_u32(object + 144u + 4u * i, value);
    }
    for (i = 0u; i < 3u; ++i)
        angles[i] = (sint32)r_u32(object + 144u + 4u * i) / 128;
    sub_800439B8(object + 16u, angles[0], angles[1], angles[2]);
    for (i = 0u; i < 3u; ++i)
    {
        value = r_u32(object + 36u + 4u * i) + (uint32)((sint32)r_u32(object + 128u + 4u * i) / 128);
        w_u32(object + 36u + 4u * i, value);
    }
    return sub_8004C934(object + 16u, object + 16u);
}


void v8_native_4352C(uint32 matrix, const sint32 *source, sint32 *destination)
{
    (void)native3_transform_long(matrix, 0u, 0u, 0u, source, destination);
}
void v8_native_435C0(uint32 matrix, const sint32 *source, sint32 *destination)
{
    (void)native3_transform_long(matrix, 0u, 0u, 1u, source, destination);
}

uint32 sub_8002A3E8(uint32 object, uint32 mode, uint32 kind);

uint32 v8_native_21B80(uint32 callback, uint32 asset, uint32 kind, uint32 flags)
{
    uint32 size = 128u, result;
    if (callback != 0u)
    {
        result = callback == 0x8002A3E8u ? sub_8002A3E8(asset, 7u, kind & 0xFFFFu) :
            v8_native_terrain_call3(callback, asset, 7u, kind & 0xFFFFu);
        if (result != 0u)
            return result;
        size = callback == 0x8002A3E8u ? sub_8002A3E8(0u, 6u, 0u) :
            v8_native_terrain_call3(callback, 0u, 6u, 0u);
        if (size == 0u)
            size = 128u;
    }
    if (asset != 0u)
        return sub_8001AC44(asset, kind & 0xFFFFu, size, flags);
    return sub_8001D470(size);
}

void v8_native_4454C(uint32 voice, uint32 table, uint32 index)
{
    uint32 volume = (uint32)(sint32)(sint16)r_u16(0x80065BE8u);
    sub_80044484(voice, table, index, (volume << 16) + volume);
}

void v8_native_44394(uint32 sound)
{
    SpuFree(r_u16(sound + 2u) << 3u);
    sub_80045088(sound);
}

void v8_native_29DEC(void)
{
    uint32 buffer,index,packet;
    for(buffer=0u;buffer<2u;++buffer)
    {
        packet=0x800A1E24u+buffer*0x504u;
        for(index=0u;index<16u;++index)
        {
            w_u8(packet+3u,2u);
            w_u8(packet+7u,0x68u);
            w_u8(packet+4u,255u);
            w_u8(packet+5u,255u);
            w_u8(packet+6u,255u);
            packet+=20u;
        }
    }
}

uint32 v8_native_15BF0(uint32 position, uint32 relative)
{
    uint32 sectors, result = 0xFFFFFFFFu;
    if (relative != 0u)
        position += r_u32(0x800659B0u);
    sectors = (position >> 11) - (uint32)((sint32)r_u32(0x800659B0u) >> 11) - 1u;
    while (sectors != 0xFFFFFFFFu)
    {
        --sectors;
        result = sub_800156D4();
        w_u32(0x800659A0u, result);
    }
    w_u32(0x800659B0u, position);
    return result;
}

void v8_native_227A4(uint32 mask)
{
    const uint32 gp = 0x80065304u;
    uint32 node = 0x8006F7A0u, output = 0x800737A0u;
    uint32 index, previous, word, byte, allocation, header[2], remaining = 0u;
    w_u32(gp + 0x76Cu, 0x80065A74u);
    w_u32(gp + 0x770u, 0u);
    w_u32(0x80065A78u, 0x80065A70u);
    for (index = 0u; index < 1023u; ++index)
    {
        previous = r_u32(gp + 0x76Cu);
        w_u32(gp + 0x76Cu, node);
        w_u32(previous + 4u, node);
        w_u32(node, previous);
        w_u32(node + 4u, 0x80065A70u);
        node += 16u;
    }
    word = r_u32(0x8006567Cu);
    byte = r_u8(0x80065680u);
    w_u32(0x80065A04u, word);
    w_u8(0x80065A08u, byte);
    w_u8(0x80065A09u, r_u8(0x80065681u));
    w_u32(gp + 0x74Cu, 0x80065A54u);
    w_u32(gp + 0x750u, 0u);
    w_u32(0x80065A58u, 0x80065A50u);
    w_u32(gp + 0x714u, 0x80065A1Cu);
    w_u32(gp + 0x718u, 0u);
    w_u32(0x80065A20u, 0x80065A18u);
    w_u32(gp + 0x77Cu, 0x80065A84u);
    w_u32(gp + 0x780u, 0u);
    w_u32(0x80065A88u, 0x80065A80u);
    w_u32(gp + 0x75Cu, 0x80065A64u);
    w_u32(gp + 0x760u, 0u);
    w_u32(0x80065A68u, 0x80065A60u);
    w_u32(gp + 0x7BCu, 0x80065AC4u);
    w_u32(gp + 0x7C0u, 0u);
    w_u32(0x80065AC8u, 0x80065AC0u);
    w_u32(gp + 0x79Cu, 0x80065AA4u);
    w_u32(gp + 0x7A0u, 0u);
    w_u32(0x80065AA8u, 0x80065AA0u);
    w_u32(gp + 0x78Cu, 0x80065A94u);
    w_u32(gp + 0x7D8u, 0u);
    w_u32(gp + 0x790u, 0u);
    w_u32(0x80065A98u, 0x80065A90u);
    w_u32(gp + 0x734u, 0u);
    sub_80044F64(output, 256u);
    mask &= 0xFFFFu;
    if (mask != 0u)
    {
        (void)sub_800159B4(0x80065684u);
        (void)sub_800225D4(header, &remaining);
        remaining = header[1];
        do
        {
            allocation = sub_800225D4(header, &remaining);
            if (allocation != 0u)
                (void)sub_80045088(allocation);
            else if (native3_swap32(header[0]) == 0x584F4246u)
            {
                if ((mask & 1u) != 0u)
                    w_u32(output, sub_8002263C(header[1], 0u));
                else
                    (void)v8_native_15BF0(header[1], 1u);
                output += 4u;
                mask >>= 1;
            }
        } while (mask != 0u);
        (void)sub_80015A00();
    }
    w_u32(gp + 0x7D4u, 0u);
    w_u32(gp + 0x7D0u, 0u);
    w_u32(gp + 0x6F8u, 0u);
    w_u32(gp + 0x6ECu, 0u);
    w_u32(gp + 0x6F4u, 0u);
    w_u32(gp + 0x708u, 0u);
    w_u32(gp + 0x758u, 0u);
    w_u32(gp + 0x6E8u, 0u);
    w_u32(gp + 0x7A8u, 0u);
    w_u32(gp + 0x70Cu, 0u);
}

void v8_native_17FD4(uint32 clear)
{
    uint32 root, left, leaf;
    DRAWENV environment;
    if (clear != 0u)
    {
        (void)SetDefDrawEnv(&environment, 0, 0, 1024, 512);
        environment.isbg = 1u;
        environment.dfe = 1u;
        (void)PutDrawEnv(&environment);
        (void)VSync(0);
        (void)PutDrawEnv(&environment);
    }
    if (r_u32(0x800659C8u) != 0u)
        sub_80017E0C();
    root = sub_80017E3C(0u, 0u, 0u, 0u, 1024u, 512u);
    w_u32(0x800659C8u, root);
    (void)sub_80017EC4(root, 320u);
    root = r_u32(0x800659C8u);
    left = r_u32(root + 16u);
    (void)sub_80017F4C(left, 480u);
    root = r_u32(0x800659C8u);
    left = r_u32(root + 16u);
    leaf = r_u32(left + 16u);
    w_u32(leaf + 8u, 1u);
    (void)sub_80017F4C(r_u32(root + 20u), 256u);
}

uint32 v8_native_1910C(uint32 object)
{
    uint32 block = r_u32(object);
    return sub_80045134(block, r_u32(block));
}

static void v8_hud_copy(uint32 destination, uint32 source, uint32 bytes)
{
    uint32 offset = 0u, a, b, c, d;
    while (bytes >= 16u)
    {
        a = r_u32(source + offset);
        b = r_u32(source + offset + 4u);
        c = r_u32(source + offset + 8u);
        d = r_u32(source + offset + 12u);
        w_u32(destination + offset, a);
        w_u32(destination + offset + 4u, b);
        w_u32(destination + offset + 8u, c);
        w_u32(destination + offset + 12u, d);
        offset += 16u;
        bytes -= 16u;
    }
    if (bytes == 12u)
    {
        a = r_u32(source + offset);
        b = r_u32(source + offset + 4u);
        c = r_u32(source + offset + 8u);
        w_u32(destination + offset, a);
        w_u32(destination + offset + 4u, b);
        w_u32(destination + offset + 8u, c);
    }
    else if (bytes == 4u)
        w_u32(destination + offset, r_u32(source + offset));
}

static void v8_hud_18D64(uint32 packets, uint32 count)
{
    uint32 cursor = packets + 4u, next, index, limit = count - 1u;
    for (index = 0u; (sint32)index < (sint32)limit; ++index)
    {
        next = cursor + (r_u8(cursor + 3u) << 2u) + 4u;
        if (MargePrim(cursor, next) < 0)
        {
            w_u32(cursor, (r_u32(cursor) & 0xFF000000u) | (next & 0xFFFFFFu));
            cursor = next;
        }
    }
    w_u32(packets, cursor);
}

static void v8_hud_18BD0(uint32 packet)
{
    w_u8(packet + 3u, 1u);
    w_u8(packet + 11u, 4u);
    w_u32(packet + 4u, 0xE1000400u);
    w_u8(packet + 15u, 101u);
    (void)MargePrim(packet, packet + 8u);
}

uint32 v8_native_2A598(void)
{
    const uint32 gp = 0x80065304u;
    uint32 table, index, packet, other, object, allocation, header[2], remaining = 0u;
    uint32 texture_byte;
    uint32 weapon = 0xFFFFFFFFu;
    uint8 texture[12], second[12];
    uint8 *global_texture;
    table = sub_80015F80(0x800656C4u);
    for (index = 0u; index < 4u; ++index)
    {
        v8_native_187E4(table + r_u32(table + 4u + index * 4u), texture);
        packet = 0x800A28A4u + index * 28u;
        (void)v8_native_18C3C((uint8 *)psx_addr(packet, 28u), texture);
        w_u8(packet + 15u, r_u8(packet + 15u) | 2u);
    }
    v8_hud_copy(0x800A2914u, 0x800A28A0u, 116u);
    v8_hud_18D64(0x800A28A0u, 4u);
    v8_hud_18D64(0x800A2914u, 4u);
    global_texture = (uint8 *)psx_addr(0x80065BA8u, 12u);
    v8_native_187E4(table + r_u32(table + 52u), global_texture);
    w_u16(gp + 0x8ACu, r_u16(gp + 0x8ACu) | 0x20u);
    packet = 0x800A2FB8u;
    (void)v8_native_18C3C((uint8 *)psx_addr(packet, 28u), global_texture);
    index = r_u8(packet + 15u);
    texture_byte = r_u8(gp + 0x8AAu);
    w_u16(packet + 26u, 16u);
    w_u8(packet + 15u, index | 2u);
    w_u8(packet + 20u, texture_byte);
    v8_hud_copy(packet + 28u, packet, 28u);
    global_texture = (uint8 *)psx_addr(0x80065B98u, 12u);
    v8_native_187E4(table + r_u32(table + 56u), global_texture);
    w_u16(gp + 0x89Cu, r_u16(gp + 0x89Cu) | 0x20u);
    for (index = 0u; index < 3u; ++index)
    {
        packet = 0x800A2988u + index * 56u;
        (void)v8_native_18C3C((uint8 *)psx_addr(packet, 28u), global_texture);
        w_u8(packet + 15u, r_u8(packet + 15u) | 2u);
        texture_byte = r_u8(packet + 21u);
        w_u16(packet + 26u, 16u);
        w_u8(packet + 21u, texture_byte + index * 16u);
        v8_hud_copy(packet + 28u, packet, 28u);
    }
    for (index = 0u; index < 64u; ++index)
    {
        packet = 0x800A2BB8u + index * 16u;
        w_u8(packet + 3u, 3u);
        w_u8(packet + 7u, 96u);
        w_u32(packet + 12u, 0x00020002u);
    }
    v8_native_187E4(table + r_u32(table + 28u), texture);
    v8_native_187E4(table + r_u32(table + 24u), second);
    xport_store_le16(texture + 8u, xport_load_le16(texture + 8u) | 0x20u);
    xport_store_le16(second + 8u, xport_load_le16(second + 8u) | 0x20u);
    for (index = 0u; index < 3u; ++index)
    {
        packet = 0x800A2AD8u + index * 56u;
        other = 0x800A2A30u + index * 56u;
        (void)v8_native_18C3C((uint8 *)psx_addr(packet, 28u), texture);
        (void)v8_native_18C3C((uint8 *)psx_addr(other, 28u), second);
        w_u8(packet + 15u, r_u8(packet + 15u) | 2u);
        w_u8(other + 15u, r_u8(other + 15u) | 2u);
        v8_hud_copy(packet + 28u, packet, 28u);
        v8_hud_copy(other + 28u, other, 28u);
    }
    v8_native_187E4(table + r_u32(table + 32u), texture);
    xport_store_le16(texture + 8u, xport_load_le16(texture + 8u) | 0x20u);
    packet = 0x800A2B80u;
    (void)v8_native_18C3C((uint8 *)psx_addr(packet, 28u), texture);
    index = r_u8(packet + 15u);
    texture_byte = xport_load_le16(texture + 6u) >> 8u;
    w_u8(packet + 15u, index | 2u);
    v8_hud_copy(packet + 28u, packet, 28u);
    w_u8(gp + 0x880u, texture_byte);
    (void)sub_80045088(table);
    packet = 0x800A2828u;
    v8_hud_18BD0(packet);
    texture_byte = r_u8(packet + 15u);
    w_u8(packet + 31u, 3u);
    w_u8(packet + 35u, 96u);
    w_u8(packet + 51u, 96u);
    w_u8(packet + 47u, 3u);
    w_u8(packet + 32u, 255u);
    w_u8(packet + 33u, 0u);
    w_u8(packet + 34u, 0u);
    w_u8(packet + 49u, 255u);
    w_u8(packet + 48u, 0u);
    w_u8(packet + 50u, 0u);
    w_u16(packet + 58u, 2u);
    w_u16(packet + 42u, 2u);
    w_u8(packet + 15u, texture_byte | 2u);
    (void)MargePrim(packet + 28u, packet + 44u);
    (void)MargePrim(packet, packet + 28u);
    v8_hud_copy(packet + 60u, packet, 60u);
    w_u8(gp + 0x85Fu, 1u);
    w_u32(gp + 0x860u, 0xE1000400u);
    w_u8(gp + 0x867u, 1u);
    w_u32(gp + 0x868u, 0xE1000400u);
    for (index = 0u; index < 4u; ++index)
    {
        object = sub_8001BDA0(r_u32(0x800737D4u), r_u8(0x8005EA5Cu + index), index);
        w_u32(0x80065B70u + index * 4u, object);
        w_u16(object, r_u16(object) | 2u);
    }
    object = sub_80019034(sub_80015F80(0x800656D0u), 34u);
    w_u32(gp + 0x87Cu, object);
    (void)v8_native_1910C(object);
    (void)sub_800159B4(0x800656E0u);
    (void)sub_800225D4(header, &remaining);
    remaining = header[1];
    while (remaining != 0u)
    {
        allocation = sub_800225D4(header, &remaining);
        if (allocation != 0u)
            (void)sub_80045088(allocation);
        else if (native3_swap32(header[0]) == 0x584F4246u)
        {
            ++weapon;
            if (weapon == (uint32)(sint32)(sint8)r_u8(0x80065674u))
            {
                object = sub_8002263C(header[1], 1u);
                w_u32(0x800737E0u, object);
                if ((sint8)r_u8(gp + 0x15u) < 3)
                {
                    w_u32(gp + 0x8B0u, sub_8001BDA0(object, 0u, weapon));
                    break;
                }
                (void)sub_80045088(r_u32(object));
                texture_byte = (uint32)((sint8)r_u8(gp + 0x15u) < 3);
                w_u32(object, 0u);
                if (texture_byte == 0u && weapon == (uint32)(sint32)(sint8)r_u8(0x80065675u))
                    w_u32(0x800737E4u, object);
            }
            else if ((sint8)r_u8(gp + 0x15u) >= 3 && weapon == (uint32)(sint32)(sint8)r_u8(0x80065675u))
            {
                object = sub_8002263C(header[1], 1u);
                w_u32(0x800737E4u, object);
                (void)sub_80045088(r_u32(object));
                w_u32(object, 0u);
            }
            else
                (void)v8_native_15BF0(header[1], 1u);
        }
        else
            (void)v8_native_15BF0(header[1], 1u);
    }
    return sub_80015A00();
}
