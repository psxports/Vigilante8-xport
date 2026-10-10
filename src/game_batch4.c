#include "psx.h"
uint32 v8_native_object_callback3(uint32 callback, uint32 object, uint32 mode, uint32 value);
void v8_native_16E64(MATRIX *input);
uint32 v8_native_1BE5C(uint32 model, const MATRIX *matrix, uint32 ordering_table);

#include "xport_trace.h"
#include <string.h>

uint32 sub_800118B4(uint32 payload);
uint32 sub_8001A994(uint32 object);
uint32 sub_80016678(uint32 mode);
uint32 sub_80016024(uint32 mode);
uint32 sub_80016364(void);
uint32 sub_800116F4(uint32 bytes);
uint32 sub_8001178C(uint32 count,uint32 bytes);
uint32 sub_80011834(void);
void sub_80017E0C(void);
uint32 sub_8001884C(uint32 reference);
uint32 sub_80044EFC(uint32 destination,uint32 value,uint32 count);
void sub_8004D524(uint32 x,uint32 y);
void sub_8004D544(uint32 projection);
uint32 sub_80011A10(void);
uint32 sub_80044C44(uint32 destination,uint32 source,uint32 count);
sint32 sub_8004F1E8(void);
uint32 xport_guest_call_known_registers_post_sdk(uint32 target,uint32 *registers,uint32 known_register_mask);
void xport_gte_complete_rtps(void);
uint32 sub_800187E4(uint32 image, uint32 destination, uint32 incoming_s1);
uint32 sub_80018D00(uint32 packet, uint32 image, uint32 output, uint32 x, uint32 y);
uint32 sub_80018C3C(uint32 packet, uint32 texture);
uint32 sub_8001B36C(uint32 object, uint32 index, uint32 incoming_s1);
uint32 sub_8001AB98(uint32 object, uint32 index);
uint64 sub_800171D4(uint32 first_vector, uint32 second_vector);
uint32 sub_80016A20(uint32 vector);
uint32 sub_80043C34(uint32 command, uint32 response);
sint32 sub_80049534(uint32 position);
uint32 sub_8001FCB4(uint32 object, uint32 time);
uint32 sub_8001F9CC(uint32 object, uint32 time);
uint32 sub_8001FC38(uint32 object, uint32 time);
uint32 sub_80044C44(uint32 destination, uint32 source, uint32 count);
void xport_mips_overflow_exception(uint32 pc);
uint32 sub_8001B36C(uint32 descriptors, uint32 index, uint32 incoming_s1);
uint32 sub_8001D708(uint32 object);
uint32 sub_80043864(uint32 left, uint32 right, uint32 destination);
uint32 sub_80016E64(uint32 matrix);
uint32 sub_8001BE5C(uint32 model, uint32 matrix, uint32 ordering_table);
uint32 sub_8001DCC8(uint32 object, uint32 parent_matrix);
uint32 xport_guest_call_known_registers(uint32 target, uint32 *registers, uint32 known_register_mask);


uint32 sub_800118B4(uint32 payload)
{
    uint32 node, index, head, tail;
    FUNCTION_MARKER(0x800118B4u, "SLUS_005.10");
    node = sub_800116F4(12u);
    index = r_u32(0x80065308u);
    w_u32(node + 8u, payload);
    head = 0x8006ECA0u + index * 12u;
    tail = r_u32(head + 8u);
    w_u32(head + 8u, node);
    head += 4u;
    w_u32(tail, node);
    w_u32(node + 4u, tail);
    w_u32(node, head);
    return node;
}


uint32 sub_8001A994(uint32 object)
{
    uint32 root, count, index = 0u, offset = 12u, value;
    FUNCTION_MARKER(0x8001A994u, "SLUS_005.10");
    root = r_u32(object);
    if (root == 0u) return 0u;
    count = r_u32(root + 16u);
    if ((sint32)count <= 0) return count;
    do
    {
        (void)sub_8001884C(object + offset);
        root = r_u32(object);
        count = r_u32(root + 16u);
        index += 1u;
        value = (uint32)((sint32)index < (sint32)count);
        offset += 12u;
    } while (value != 0u);
    return value;
}


uint32 sub_80016678(uint32 mode)
{
    uint32 state, callback;
    FUNCTION_MARKER(0x80016678u, "SLUS_005.10");
    sub_80017E0C();
    (void)sub_80011834();
    state = sub_80016024(mode);
    w_u32(0x800659C0u, state);
    callback = VSyncCallbackPSX(0x80016364u);
    state = r_u32(0x800659C0u);
    w_u32(state + 0x5DD0u, callback);
    w_u8(0x8006F27Cu, 1u);
    w_u8(0x8006F220u, 1u);
    return 0x8006F208u;
}


uint32 sub_80016024(uint32 mode)
{
    uint32 state, x, y, buffer, cursor, value, edge_x, edge_y, page, index;
    DISPENV display;
    DRAWENV draw;
    uint32 primitive_words[10];
    uint8 *primitive = (uint8 *)primitive_words;
    FUNCTION_MARKER(0x80016024u, "SLUS_005.10");
    SetDefDispEnv(&display, 640, 0, 320, 240);
    x = (uint32)(sint32)(sint8)r_u8(0x8006531Cu);
    y = (uint32)(sint32)(sint8)r_u8(0x8006531Du);
    xport_store_le16((uint8 *)&display + 8u, (uint16)x);
    xport_store_le16((uint8 *)&display + 10u, (uint16)y);
    if (mode != 0u)
    {
        SetDefDrawEnv(&draw, 640, 0, 320, 240);
        xport_store_u8((uint8 *)&draw + 24u, 1u);
        (void)PutDrawEnv(&draw);
        xport_store_u8(primitive + 3u, 9u);
        xport_store_u8(primitive + 7u, 0x2Du);
        for (x = 0u; x < 320u; x += 64u)
        {
            page = (x >> 5u) & 15u;
            xport_store_le16(primitive + 22u, (uint16)(page | 0x100u));
            xport_store_u8(primitive + 12u, 0u);
            xport_store_u8(primitive + 13u, 0u);
            xport_store_u8(primitive + 20u, 128u);
            xport_store_u8(primitive + 21u, 0u);
            xport_store_u8(primitive + 28u, 0u);
            xport_store_u8(primitive + 29u, 255u);
            xport_store_u8(primitive + 36u, 128u);
            xport_store_u8(primitive + 37u, 255u);
            xport_store_le16(primitive + 8u, (uint16)x);
            xport_store_le16(primitive + 10u, 0u);
            xport_store_le16(primitive + 16u, (uint16)(x + 64u));
            xport_store_le16(primitive + 18u, 0u);
            xport_store_le16(primitive + 24u, (uint16)x);
            xport_store_le16(primitive + 26u, 128u);
            xport_store_le16(primitive + 32u, (uint16)(x + 64u));
            xport_store_le16(primitive + 34u, 128u);
            (void)DrawPrim(primitive + 0u);
            xport_store_u8(primitive + 29u, 224u);
            xport_store_u8(primitive + 37u, 224u);
            xport_store_le16(primitive + 22u, (uint16)(page | 0x110u));
            xport_store_u8(primitive + 12u, 0u);
            xport_store_u8(primitive + 13u, 0u);
            xport_store_u8(primitive + 20u, 128u);
            xport_store_u8(primitive + 21u, 0u);
            xport_store_u8(primitive + 28u, 0u);
            xport_store_u8(primitive + 36u, 128u);
            xport_store_le16(primitive + 8u, (uint16)x);
            xport_store_le16(primitive + 10u, 128u);
            xport_store_le16(primitive + 16u, (uint16)(x + 64u));
            xport_store_le16(primitive + 18u, 128u);
            xport_store_le16(primitive + 24u, (uint16)x);
            xport_store_le16(primitive + 26u, 240u);
            xport_store_le16(primitive + 32u, (uint16)(x + 64u));
            xport_store_le16(primitive + 34u, 240u);
            (void)DrawPrim(primitive + 0u);
        }
    }
    else MoveImage((PSX_RECT *)psx_addr(0x80065660u, 8u), 640, 0);
    state = sub_8001178C(1u, 0x5DD4u);
    cursor = state;
    for (buffer = 0u; buffer < 2u; ++buffer)
        for (y = 0u; y < 240u; y += 16u)
            for (x = 0u; x < 320u; x += 16u)
            {
                w_u8(cursor + 3u, 9u);
                w_u8(cursor + 7u, 0x2Cu);
                value = (((x + 640u) & 1023u) >> 6u) | 0x100u;
                w_u16(cursor + 22u, (uint16)value);
                w_u8(cursor + 4u, 128u);
                w_u8(cursor + 5u, 128u);
                w_u8(cursor + 6u, 128u);
                w_u8(cursor + 12u, (uint8)(x & 63u));
                w_u8(cursor + 13u, (uint8)y);
                edge_x = (x & 63u) + (x == 304u ? 15u : 16u);
                w_u8(cursor + 20u, (uint8)edge_x);
                w_u8(cursor + 21u, (uint8)y);
                w_u8(cursor + 28u, (uint8)(x & 63u));
                edge_y = y + (y == 240u || y == 224u ? 15u : 16u);
                w_u8(cursor + 29u, (uint8)edge_y);
                edge_x = (x & 63u) + (x == 304u ? 15u : 16u);
                w_u8(cursor + 36u, (uint8)edge_x);
                edge_y = y + (y == 240u || y == 224u ? 15u : 16u);
                w_u8(cursor + 37u, (uint8)edge_y);
                w_u16(cursor + 8u, (uint16)x);
                w_u16(cursor + 10u, (uint16)y);
                w_u16(cursor + 16u, (uint16)(x + 16u));
                w_u16(cursor + 18u, (uint16)y);
                w_u16(cursor + 24u, (uint16)x);
                w_u16(cursor + 26u, (uint16)(y + 16u));
                w_u16(cursor + 32u, (uint16)(x + 16u));
                w_u16(cursor + 34u, (uint16)(y + 16u));
                cursor += 40u;
            }
    sub_8004D524(160u, 120u);
    sub_8004D544(256u);
    (void)PutDispEnv(&display);
    index = r_u32(0x80065308u);
    (void)PutDrawEnv((DRAWENV *)psx_addr(0x8006F208u + index * 92u, 92u));
    return state;
}


uint32 sub_80016364(void)
{
    uint32 frame_address, index, state, cursor, value, first, second, brightness, x, y, callback, result;
    uint32 registers[32]; PsxGteSnapshot snapshot;
    uint8 *frame;
    FUNCTION_MARKER(0x80016364u, "SLUS_005.10");
    index = r_u32(0x80065308u);
    frame_address = xport_guest_frame_acquire(80u);
    frame = (uint8 *)psx_addr(frame_address, 80u);
    state = r_u32(0x800659C0u);
    cursor = state + index * 12000u;
    (void)sub_80044EFC(frame_address + 24u, 0u, 8u);
    state = r_u32(0x800659C0u);
    value = r_u16(state + 0x5DC0u);
    xport_store_le16(frame + 24u, (uint16)value);
    value = r_u32(state + 0x5DC0u);
    xport_store_le16(frame + 26u, (uint16)(value << 1u));
    first = xport_load_le32(frame + 24u);
    second = xport_load_le32(frame + 28u);
    xport_store_le32(frame + 16u, first);
    xport_store_le32(frame + 20u, second);
    value = r_u32(state + 0x5DC4u);
    brightness = 128u - value;
    if ((sint32)brightness <= 0) brightness = 0u;
    index = r_u32(0x80065308u);
    (void)PutDrawEnv((DRAWENV *)psx_addr(0x8006F208u + index * 92u, 92u));
    index = r_u32(0x80065308u);
    (void)PutDispEnv((DISPENV *)psx_addr(0x8006F5A0u + index * 20u, sizeof(DISPENV)));
    (void)RotMatrixYXZ((SVECTOR *)(frame + 16u), (MATRIX *)(frame + 32u));
    SetRotMatrix((MATRIX *)(frame + 32u));
    state = r_u32(0x800659C0u);
    value = r_u32(state + 0x5DC4u);
    xport_gte_write_control(5u, 0u - value);
    xport_gte_write_control(6u, 0u - value);
    xport_gte_write_control(7u, (value << 2u) + 256u);
    (void)sub_80011A10();
    for (y = 0xFFFFFF88u; (sint32)y < 120; y += 16u)
        for (x = 0xFFFFFF60u; (sint32)x < 160; x += 16u)
        {
            xport_gte_write_data(0u, ((y & 65535u) << 16u) | (x & 65535u));
            xport_gte_write_data(1u, 0u);
            xport_gte_write_data(2u, ((y & 65535u) << 16u) | ((x + 16u) & 65535u));
            xport_gte_write_data(3u, 0u);
            xport_gte_write_data(4u, (((y + 16u) & 65535u) << 16u) | (x & 65535u));
            xport_gte_write_data(5u, 0u);
            xport_gte_execute(0x00280030u);
            w_u8(cursor + 4u, (uint8)brightness);
            w_u8(cursor + 5u, (uint8)brightness);
            w_u8(cursor + 6u, (uint8)brightness);
            psx_gte_snapshot(&snapshot); w_u32(cursor + 8u, (uint32)snapshot.sxy[0]);
            psx_gte_snapshot(&snapshot); w_u32(cursor + 16u, (uint32)snapshot.sxy[1]);
            psx_gte_snapshot(&snapshot); w_u32(cursor + 24u, (uint32)snapshot.sxy[2]);
            xport_gte_write_data(0u, (((y + 16u) & 65535u) << 16u) | ((x + 16u) & 65535u));
            xport_gte_write_data(1u, 0u);
            xport_gte_execute(0x00180001u);
            psx_gte_snapshot(&snapshot); w_u32(cursor + 32u, (uint32)snapshot.sxy[2]);
            first = r_u32(0x80065910u);
            second = r_u32(first);
            w_u32(first, cursor & 0xFFFFFFu);
            value = r_u8(cursor + 3u);
            w_u32(cursor, (value << 24u) | second);
            cursor += 40u;
        }
    first = r_u32(0x80065910u);
    (void)DrawOTagPSX(first);
    state = r_u32(0x800659C0u);
    value = r_u32(state + 0x5DC4u);
    first = r_u32(state + 0x5DC0u);
    callback = r_u32(state + 0x5DD0u);
    value += 1u; first += 34u;
    w_u32(state + 0x5DC4u, value);
    result = (uint32)((sint32)value >= 128);
    w_u32(state + 0x5DC0u, first);
    w_u32(state + 0x5DCCu, result);
    if (callback != 0u)
    {
        registers[0] = 0u; registers[2] = result; registers[3] = state;
        registers[4] = first; registers[5] = callback; registers[16] = frame_address + 32u;
        registers[17] = cursor; registers[18] = brightness; registers[28] = 0x80065304u;
        registers[31] = 0x800165B4u;
        result = xport_guest_call_known_registers_post_sdk(callback, registers, 0x9007003Du);
    }
    xport_guest_frame_release(frame_address, 80u);
    return result;
}


uint32 sub_80043C34(uint32 command, uint32 response)
{
    FUNCTION_MARKER(0x80043C34u, "SLUS_005.10");
    uint32 frame, position, result, flags, threshold;
    frame = xport_guest_frame_acquire(32u); position = frame + 16u; result = 1u;
    if ((command & 0xFFu) == 1u)
    {
    flags = r_u8(response + 4u);
    result = flags & 0x80u; if (result == 0u)
    {
    result = r_u8(response + 3u);
    w_u8(position, (uint8)result);
    result = r_u8(response + 4u);
    w_u8(position + 2u, 0u);
    w_u8(position + 1u, (uint8)result);
    result = (uint32)sub_80049534(position);
    threshold = r_u32(0x80065BE4u);
    if ((sint32)threshold < (sint32)result)
    {
    flags = r_u8(0x80065BE3u);
    if (flags != 0u)
    {
    (void)CdControl(9u, 0, 0);
    result = CdSyncCallbackPSX(0u);
    goto frame_return;
    }
    result = (uint32)CdControl(3u, (uint8 *)psx_addr(0x80065BE0u, 4u), 0);
    }
    }
    }
    frame_return:
    xport_guest_frame_release(frame, 32u);
    return result;
}


uint32 sub_80018D00(uint32 packet, uint32 image, uint32 output, uint32 x, uint32 y)
{
    FUNCTION_MARKER(0x80018D00u, "SLUS_005.10");
    uint32 result;
    (void)sub_800187E4(image, output, output);
    result = sub_80018C3C(packet, output);
    w_u16(packet + 16u, (uint16)x);
    w_u16(packet + 18u, (uint16)y);
    return result;
}


uint32 sub_80018C3C(uint32 packet, uint32 texture)
{
    FUNCTION_MARKER(0x80018C3Cu, "SLUS_005.10");
    uint32 value;
    w_u8(packet + 3u, 1u);
    value = r_u16(texture + 8u);
    w_u8(packet + 11u, 4u);
    w_u8(packet + 15u, 101u);
    w_u32(packet + 4u, (value & 0x9FFu) | 0xE1000400u);
    value = r_u16(texture + 10u);
    w_u16(packet + 22u, (uint16)value);
    value = r_u16(texture + 2u);
    w_u16(packet + 24u, (uint16)value);
    value = r_u16(texture + 4u);
    w_u16(packet + 26u, (uint16)value);
    value = r_u16(texture + 6u);
    w_u16(packet + 20u, (uint16)value);
    return (uint32)MargePrim(packet, packet + 8u);
}


uint32 sub_8001B36C(uint32 object, uint32 index, uint32 incoming_s1)
{
    FUNCTION_MARKER(0x8001B36Cu, "SLUS_005.10");
    uint32 entry = object + 12u * (index & 0xFFFFu) + 12u, base, table, image;
    if (r_u16(entry) == 0u)
    {
    base = r_u32(object);
    table = r_u32(base + 20u);
    image = r_u32(table + 4u * (index & 0xFFFFu));
    (void)sub_800187E4(image, entry, incoming_s1);
    }
    return entry;
}


uint32 sub_8001AB98(uint32 object, uint32 index)
{
    FUNCTION_MARKER(0x8001AB98u, "SLUS_005.10");
    uint32 base = r_u32(object + 4u), offset;
    if (base == 0u) return 0u;
    offset = r_u32(base + 4u * (index & 0xFFFFu) + 4u);
    if (offset == 0u) return 0u;
    return base + offset;
}


static uint32 v8_native_count_sign_bits(uint32 value)
{
    uint32 count = 0u;
    uint32 bits = (value & 0x80000000u) != 0u ? ~value : value;
    while (count < 32u && (bits & 0x80000000u) == 0u)
    {
        bits <<= 1;
        ++count;
    }
    return count;
}

uint32 sub_80016A20(uint32 vector)
{
    FUNCTION_MARKER(0x80016A20u, "SLUS_005.10");
    uint64 pair; uint32 low, high, leading, scale, shift, shifted, normalized;
    pair = sub_800171D4(vector, vector);
    low = (uint32)pair; high = (uint32)(pair >> 32);
    leading = v8_native_count_sign_bits(high);
    scale = (uint32)((sint32)(35u - leading) >> 1);
    shift = scale << 1; shifted = shift << 26;
    if ((sint32)shifted < 0)
    {
    normalized = (uint32)((sint32)high >> (shift & 31u));
    }
    else
    {
    normalized = low >> (shift & 31u);
    if (shifted != 0u) normalized |= high << ((0u - shift) & 31u);
    }
    low = SquareRoot0((sint32)normalized);
    return low << (scale & 31u);
}


uint64 sub_800171D4(uint32 first_vector, uint32 second_vector)
{
    sint32 left, right; uint64 first, second, third;
    FUNCTION_MARKER(0x800171D4u, "SLUS_005.10");
    left = (sint32)r_u32(first_vector);
    right = (sint32)r_u32(second_vector);
    first = (uint64)((sint64)left * (sint64)right);
    left = (sint32)r_u32(first_vector + 4u);
    right = (sint32)r_u32(second_vector + 4u);
    second = (uint64)((sint64)left * (sint64)right);
    left = (sint32)r_u32(first_vector + 8u);
    right = (sint32)r_u32(second_vector + 8u);
    third = (uint64)((sint64)left * (sint64)right);
    return first + second + third;
}


uint32 sub_80044D9C(uint32 destination, uint32 source, uint32 count)
{
    uint32 original = destination, value, word1, word2, word3, offset, address, checked_result; int branch;
    FUNCTION_MARKER(0x80044D9Cu, "SLUS_005.10");
    if ((sint32)source >= (sint32)destination) return sub_80044C44(destination, source, count);
    branch = count == 0u;
    checked_result = destination + count;
    if ((((destination ^ checked_result) & (count ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044DACu);
    destination = checked_result;
    if (branch) return original;
    checked_result = source + count;
    if ((((source ^ checked_result) & (count ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044DB0u);
    source = checked_result;
    while ((source & 3u) != 0u)
    {
    offset = destination & 3u;
    value = r_u8(source - 1u);
    checked_result = source + 0xFFFFFFFFu;
    if ((((source ^ checked_result) & (0xFFFFFFFFu ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044DC4u);
    source = checked_result;
    w_u8(destination - 1u, value);
    checked_result = count + 0xFFFFFFFFu;
    if ((((count ^ checked_result) & (0xFFFFFFFFu ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044DCCu);
    count = checked_result;
    branch = count != 0u;
    checked_result = destination + 0xFFFFFFFFu;
    if ((((destination ^ checked_result) & (0xFFFFFFFFu ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044DD4u);
    destination = checked_result;
    if (!branch) return original;
    }
    offset = destination & 3u;
    count -= 16u;
    if (offset == 0u)
    {
    while ((sint32)count >= 0)
    {
    value = r_u32(source - 4u);
    word1 = r_u32(source - 8u);
    word2 = r_u32(source - 12u);
    word3 = r_u32(source - 16u);
    w_u32(destination - 4u, value);
    w_u32(destination - 8u, word1);
    w_u32(destination - 12u, word2);
    w_u32(destination - 16u, word3);
    checked_result = source + 0xFFFFFFF0u;
    if ((((source ^ checked_result) & (0xFFFFFFF0u ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044E10u);
    source = checked_result;
    checked_result = count + 0xFFFFFFF0u;
    if ((((count ^ checked_result) & (0xFFFFFFF0u ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044E14u);
    count = checked_result;
    branch = (sint32)count >= 0;
    checked_result = destination + 0xFFFFFFF0u;
    if ((((destination ^ checked_result) & (0xFFFFFFF0u ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044E1Cu);
    destination = checked_result;
    if (!branch) break;
    }
    count += 12u;
    while ((sint32)count >= 0)
    {
    value = r_u32(source - 4u);
    checked_result = source + 0xFFFFFFFCu;
    if ((((source ^ checked_result) & (0xFFFFFFFCu ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044E30u);
    source = checked_result;
    w_u32(destination - 4u, value);
    checked_result = count + 0xFFFFFFFCu;
    if ((((count ^ checked_result) & (0xFFFFFFFCu ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044E38u);
    count = checked_result;
    branch = (sint32)count >= 0;
    checked_result = destination + 0xFFFFFFFCu;
    if ((((destination ^ checked_result) & (0xFFFFFFFCu ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044E40u);
    destination = checked_result;
    if (!branch) break;
    }
    count += 4u;
    branch = (sint32)count <= 0;
    checked_result = source - count;
    if ((((source ^ count) & (source ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044E4Cu);
    source = checked_result;
    if (branch) return original;
    offset = source & 3u; value = r_u32(source & ~3u) >> (8u * offset);
    checked_result = destination - count;
    if ((((destination ^ count) & (destination ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044E54u);
    destination = checked_result;
    offset = destination & 3u; w_masked_u32(destination & ~3u, value << (8u * offset), (15u << offset) & 15u);
    return original;
    }
    while ((sint32)count >= 0)
    {
    value = r_u32(source - 4u);
    word1 = r_u32(source - 8u);
    word2 = r_u32(source - 12u);
    word3 = r_u32(source - 16u);
    address = destination - 4u; offset = address & 3u; w_masked_u32(address & ~3u, value << (8u * offset), (15u << offset) & 15u);
    address = destination - 1u; offset = address & 3u; w_masked_u32(address & ~3u, value >> (8u * (3u - offset)), (1u << (offset + 1u)) - 1u);
    address = destination - 8u; offset = address & 3u; w_masked_u32(address & ~3u, word1 << (8u * offset), (15u << offset) & 15u);
    address = destination - 5u; offset = address & 3u; w_masked_u32(address & ~3u, word1 >> (8u * (3u - offset)), (1u << (offset + 1u)) - 1u);
    address = destination - 12u; offset = address & 3u; w_masked_u32(address & ~3u, word2 << (8u * offset), (15u << offset) & 15u);
    address = destination - 9u; offset = address & 3u; w_masked_u32(address & ~3u, word2 >> (8u * (3u - offset)), (1u << (offset + 1u)) - 1u);
    address = destination - 16u; offset = address & 3u; w_masked_u32(address & ~3u, word3 << (8u * offset), (15u << offset) & 15u);
    address = destination - 13u; offset = address & 3u; w_masked_u32(address & ~3u, word3 >> (8u * (3u - offset)), (1u << (offset + 1u)) - 1u);
    checked_result = source + 0xFFFFFFF0u;
    if ((((source ^ checked_result) & (0xFFFFFFF0u ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044E98u);
    source = checked_result;
    checked_result = count + 0xFFFFFFF0u;
    if ((((count ^ checked_result) & (0xFFFFFFF0u ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044E9Cu);
    count = checked_result;
    branch = (sint32)count >= 0;
    checked_result = destination + 0xFFFFFFF0u;
    if ((((destination ^ checked_result) & (0xFFFFFFF0u ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044EA4u);
    destination = checked_result;
    if (!branch) break;
    }
    count += 12u;
    while ((sint32)count >= 0)
    {
    value = r_u32(source - 4u);
    checked_result = source + 0xFFFFFFFCu;
    if ((((source ^ checked_result) & (0xFFFFFFFCu ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044EB8u);
    source = checked_result;
    address = destination - 4u; offset = address & 3u; w_masked_u32(address & ~3u, value << (8u * offset), (15u << offset) & 15u);
    address = destination - 1u; offset = address & 3u; w_masked_u32(address & ~3u, value >> (8u * (3u - offset)), (1u << (offset + 1u)) - 1u);
    checked_result = count + 0xFFFFFFFCu;
    if ((((count ^ checked_result) & (0xFFFFFFFCu ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044EC4u);
    count = checked_result;
    branch = (sint32)count >= 0;
    checked_result = destination + 0xFFFFFFFCu;
    if ((((destination ^ checked_result) & (0xFFFFFFFCu ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044ECCu);
    destination = checked_result;
    if (!branch) break;
    }
    count += 4u;
    while (count != 0u)
    {
    value = (uint32)(sint32)(sint8)r_u8(source - 1u);
    checked_result = source + 0xFFFFFFFFu;
    if ((((source ^ checked_result) & (0xFFFFFFFFu ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044EE0u);
    source = checked_result;
    w_u8(destination - 1u, value);
    checked_result = count + 0xFFFFFFFFu;
    if ((((count ^ checked_result) & (0xFFFFFFFFu ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044EE8u);
    count = checked_result;
    branch = count != 0u;
    checked_result = destination + 0xFFFFFFFFu;
    if ((((destination ^ checked_result) & (0xFFFFFFFFu ^ checked_result)) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x80044EF0u);
    destination = checked_result;
    if (!branch) break;
    }
    return original;
}


uint32 sub_8001FCB4(uint32 object, uint32 time)
{
    uint32 result, child; uint32 masked_time = time & 0xFFFFu;
    FUNCTION_MARKER(0x8001FCB4u, "SLUS_005.10");
    result = sub_8001F9CC(object, masked_time);
    if ((sint32)result >= 0)
    {
    child = r_u32(object + 56u);
    if (child != 0u)
    result = sub_8001FC38(child, masked_time);
    }
    return result;
}


uint32 sub_8001F9CC(uint32 object, uint32 time)
{
    uint32 record, flags, stream, auxiliary = 0u, modified = 0u, target, value, other, third, word, offset, address;
    uint32 callback_result;
    FUNCTION_MARKER(0x8001F9CCu, "SLUS_005.10");
    record = r_u32(object + 96u);
    if (record == 0u) return 0u;
    value = r_u16(object + 70u);
    other = r_u16(record);
    if (((time - value) & 0xFFFFu) < other) return 0u;
    do
    {
    record = r_u32(object + 96u);
    flags = (uint32)(sint32)(sint16)r_u16(record + 2u);
    stream = record + 4u;
    if ((sint32)flags < 0)
    {
    value = r_u16(object + 70u);
    other = r_u16(record);
    record = r_u32(object + 96u);
    target = r_u32(object + 100u);
    value += other; record += flags;
    w_u16(object + 70u, value);
    w_u32(object + 96u, record);
    if (target != 0u)
    {
    callback_result = v8_native_object_callback3(target, object, 5u, 0u);
    value = callback_result;
    }
    else
    value = 0u;
    if ((sint32)value < 0) return 0xFFFFFFFFu;
    }
    else
    {
    if ((flags & 1u) != 0u)
    {
    address = record + 7u; offset = address & 3u; word = r_u32(address & ~3u) << (8u * (3u - offset));
    address = record + 4u; offset = address & 3u; word = (word & (offset == 0u ? 0u : 0xFFFFFFFFu << (8u * (4u - offset)))) | (r_u32(address & ~3u) >> (8u * offset));
    other = (uint32)(sint32)(sint16)r_u16(record + 8u);
    address = object + 67u; offset = address & 3u; w_masked_u32(address & ~3u, word >> (8u * (3u - offset)), (1u << (offset + 1u)) - 1u);
    address = object + 64u; offset = address & 3u; w_masked_u32(address & ~3u, word << (8u * offset), (15u << offset) & 15u);
    w_u16(object + 68u, other);
    stream = record + 12u; modified = 1u;
    }
    if ((flags & 2u) != 0u)
    {
    value = r_u32(stream);
    other = r_u32(stream + 4u);
    third = r_u32(stream + 8u);
    w_u32(object + 72u, value);
    w_u32(object + 76u, other);
    w_u32(object + 80u, third);
    stream += 12u; modified = 1u;
    }
    if ((flags & 8u) != 0u)
    {
    other = (uint32)(sint32)(sint16)r_u16(stream + 0u);
    value = r_u32(object + 72u);
    w_u32(object + 72u, value + other);
    other = (uint32)(sint32)(sint16)r_u16(stream + 2u);
    value = r_u32(object + 76u);
    w_u32(object + 76u, value + other);
    other = (uint32)(sint32)(sint16)r_u16(stream + 4u);
    value = r_u32(object + 80u);
    modified = 1u; stream += 8u;
    w_u32(object + 80u, value + other);
    }
    if ((flags & 16u) != 0u)
    {
    do
    {
    value = r_u32(object + 88u);
    record = r_u32(object + 48u);
    other = r_u16(stream + 2u);
    third = r_u16(record + 42u);
    word = r_u16(stream);
    value = sub_8001B36C(value, (third + other) & 0xFFFFu, stream);
    record = r_u32(object + 48u);
    stream += 4u;
    w_u32(record + 44u + ((word & 0x7FFFu) << 2), value);
    } while ((word & 0x8000u) == 0u);
    }
    if ((flags & 32u) != 0u)
    {
    auxiliary = stream; stream += 8u; modified = 1u;
    }
    value = stream + 4u;
    if ((flags & 64u) != 0u)
    {
    record = r_u32(object + 48u);
    w_u32(record + 8u, value);
    value = r_u32(stream);
    stream += (value << 3) + 4u;
    }
    w_u32(object + 96u, stream);
    }
    record = r_u32(object + 96u);
    value = r_u16(object + 70u);
    other = r_u16(record);
    } while (((time - value) & 0xFFFFu) >= other);
    if (modified != 0u)
    {
    (void)sub_8001D708(object);
    if (auxiliary != 0u)
    {
    (void)sub_80043864(object + 16u, auxiliary, object + 16u);
    value = r_u16(auxiliary);
    w_u16(object + 34u, value);
    }
    }
    return 0u;
}


uint32 sub_8001DCC8(uint32 object, uint32 parent_matrix)
{
    uint32 frame, matrix, result, flags, value, first, second, third, fourth, child, model;
    FUNCTION_MARKER(0x8001DCC8u, "SLUS_005.10");
    frame = xport_guest_frame_acquire(96u);
    matrix = frame + 16u;
    do
    {
    (void)CompMatrixLV((MATRIX *)psx_addr(parent_matrix, 32u), (MATRIX *)psx_addr(object + 16u, 32u), (MATRIX *)psx_addr(frame + 16u, 32u));
    flags = r_u32(object);
    result = flags & 0x400u;
    if ((flags & 16u) != 0u)
    {
    if (result != 0u)
    {
    first = r_u32(object + 16u);
    second = r_u32(object + 20u);
    third = r_u32(object + 24u);
    fourth = r_u32(object + 28u);
    w_u32(frame + 48u, first);
    w_u32(frame + 52u, second);
    w_u32(frame + 56u, third);
    w_u32(frame + 60u, fourth);
    value = (uint32)(sint32)(sint16)r_u16(object + 32u);
    w_u16(frame + 64u, value);
    first = r_u32(frame + 36u);
    second = r_u32(frame + 40u);
    third = r_u32(frame + 44u);
    w_u32(frame + 68u, first);
    w_u32(frame + 72u, second);
    w_u32(frame + 76u, third);
    matrix = frame + 48u;
    }
    else
    {
    value = (uint32)(sint32)(sint16)r_u16(object + 34u);
    result = 0x80070000u;
    if (value != 0u)
    result = sub_80016E64(matrix);
    else
    {
    first = r_u32(0x8006F660u + 0u);
    second = r_u32(0x8006F660u + 4u);
    third = r_u32(0x8006F660u + 8u);
    w_u32(frame + 16u, first);
    w_u32(frame + 20u, second);
    w_u32(frame + 24u, third);
    fourth = r_u32(0x8006F66Cu);
    value = (uint32)(sint32)(sint16)r_u16(0x8006F670u);
    w_u32(frame + 28u, fourth);
    w_u16(frame + 32u, value);
    }
    }
    }
    model = r_u32(object + 48u);
    if (model != 0u)
    {
    value = r_u32(0x80065910u);
    result = sub_8001BE5C(model, matrix, value);
    }
    child = r_u32(object + 56u);
    if (child != 0u)
    result = sub_8001DCC8(child, frame + 16u);
    object = r_u32(object + 52u);
    matrix = frame + 16u;
    } while (object != 0u);
    xport_guest_frame_release(frame, 96u);
    return result;
}

void v8_native_1DCC8(uint32 object, const MATRIX *parent_matrix)
{
    MATRIX composed, alternate_matrix;
    uint8 *primary_bytes = (uint8 *)&composed;
    uint8 *alternate_bytes = (uint8 *)&alternate_matrix;
    MATRIX *matrix = &composed;
    uint32 result, flags, value, first, second, third, fourth, child, model;
    do
    {
    (void)CompMatrixLV((MATRIX *)parent_matrix, (MATRIX *)psx_addr(object + 16u, 32u), &composed);
    flags = r_u32(object);
    result = flags & 0x400u;
    if ((flags & 16u) != 0u)
    {
    if (result != 0u)
    {
    first = r_u32(object + 16u);
    second = r_u32(object + 20u);
    third = r_u32(object + 24u);
    fourth = r_u32(object + 28u);
    xport_store_le32(alternate_bytes + 0u, first);
    xport_store_le32(alternate_bytes + 4u, second);
    xport_store_le32(alternate_bytes + 8u, third);
    xport_store_le32(alternate_bytes + 12u, fourth);
    value = (uint32)(sint32)(sint16)r_u16(object + 32u);
    xport_store_le16(alternate_bytes + 16u, (uint16)(value));
    first = xport_load_le32(primary_bytes + 20u);
    second = xport_load_le32(primary_bytes + 24u);
    third = xport_load_le32(primary_bytes + 28u);
    xport_store_le32(alternate_bytes + 20u, first);
    xport_store_le32(alternate_bytes + 24u, second);
    xport_store_le32(alternate_bytes + 28u, third);
    matrix = &alternate_matrix;
    }
    else
    {
    value = (uint32)(sint32)(sint16)r_u16(object + 34u);
    if (value != 0u)
    v8_native_16E64(matrix);
    else
    {
    first = r_u32(0x8006F660u + 0u);
    second = r_u32(0x8006F660u + 4u);
    third = r_u32(0x8006F660u + 8u);
    xport_store_le32(primary_bytes + 0u, first);
    xport_store_le32(primary_bytes + 4u, second);
    xport_store_le32(primary_bytes + 8u, third);
    fourth = r_u32(0x8006F66Cu);
    value = (uint32)(sint32)(sint16)r_u16(0x8006F670u);
    xport_store_le32(primary_bytes + 12u, fourth);
    xport_store_le16(primary_bytes + 16u, (uint16)(value));
    }
    }
    }
    model = r_u32(object + 48u);
    if (model != 0u)
    {
    value = r_u32(0x80065910u);
    (void)v8_native_1BE5C(model, matrix, value);
    }
    child = r_u32(object + 56u);
    if (child != 0u)
    v8_native_1DCC8(child, &composed);
    object = r_u32(object + 52u);
    matrix = &composed;
    } while (object != 0u);
}


void v8_native_187E4(uint32 image, uint8 *output);

uint32 v8_native_18C3C(uint8 *packet, const uint8 *texture)
{
    uint32 value, length;
    packet[3] = 1u;
    value = xport_load_le16(texture + 8u);
    packet[11] = 4u;
    packet[15] = 101u;
    xport_store_le32(packet + 4u, (value & 0x9FFu) | 0xE1000400u);
    value = xport_load_le16(texture + 10u);
    xport_store_le16(packet + 22u, (uint16)value);
    value = xport_load_le16(texture + 2u);
    xport_store_le16(packet + 24u, (uint16)value);
    value = xport_load_le16(texture + 4u);
    xport_store_le16(packet + 26u, (uint16)value);
    value = xport_load_le16(texture + 6u);
    xport_store_le16(packet + 20u, (uint16)value);
    length = (uint32)packet[3] + (uint32)packet[11] + 1u;
    if (length >= 17u) return 0xFFFFFFFFu;
    packet[3] = (uint8)length;
    xport_store_le32(packet + 8u, 0u);
    return 0u;
}

uint32 v8_native_18D00(uint8 *packet, uint32 image, uint8 *output, uint32 x, uint32 y)
{
    uint32 result;
    (void)v8_native_187E4(image, output);
    result = v8_native_18C3C(packet, output);
    xport_store_le16(packet + 16u, (uint16)x);
    xport_store_le16(packet + 18u, (uint16)y);
    return result;
}


#include <string.h>
#include <stdio.h>
#include <stdlib.h>

sint32 v8_native_dispatch_bios_callback(uint32 address);

void v8_native_16364(void)
{
    uint32 index, state, cursor, value, first, second, brightness, x, y, callback, result;
    PsxGteSnapshot snapshot;
    uint32 angle_words[2];
    SVECTOR rotation;
    MATRIX matrix;
    FUNCTION_MARKER(0x80016364u, "SLUS_005.10");
    index = r_u32(0x80065308u);
    state = r_u32(0x800659C0u);
    cursor = state + index * 12000u;
    memset(angle_words, 0, sizeof(angle_words));
    state = r_u32(0x800659C0u);
    value = r_u16(state + 0x5DC0u);
    xport_store_le16((uint8 *)angle_words, (uint16)value);
    value = r_u32(state + 0x5DC0u);
    xport_store_le16((uint8 *)angle_words + 2u, (uint16)(value << 1u));
    first = xport_load_le32((uint8 *)angle_words);
    second = xport_load_le32((uint8 *)angle_words + 4u);
    xport_store_le32((uint8 *)&rotation, first);
    xport_store_le32((uint8 *)&rotation + 4u, second);
    value = r_u32(state + 0x5DC4u);
    brightness = 128u - value;
    if ((sint32)brightness <= 0) brightness = 0u;
    index = r_u32(0x80065308u);
    (void)PutDrawEnv((DRAWENV *)psx_addr(0x8006F208u + index * 92u, 92u));
    index = r_u32(0x80065308u);
    (void)PutDispEnv((DISPENV *)psx_addr(0x8006F5A0u + index * 20u, sizeof(DISPENV)));
    (void)RotMatrixYXZ(&rotation, &matrix);
    SetRotMatrix(&matrix);
    state = r_u32(0x800659C0u);
    value = r_u32(state + 0x5DC4u);
    xport_gte_write_control(5u, 0u - value);
    xport_gte_write_control(6u, 0u - value);
    xport_gte_write_control(7u, (value << 2u) + 256u);
    (void)sub_80011A10();
    for (y = 0xFFFFFF88u; (sint32)y < 120; y += 16u)
        for (x = 0xFFFFFF60u; (sint32)x < 160; x += 16u)
        {
            xport_gte_write_data(0u, ((y & 65535u) << 16u) | (x & 65535u));
            xport_gte_write_data(1u, 0u);
            xport_gte_write_data(2u, ((y & 65535u) << 16u) | ((x + 16u) & 65535u));
            xport_gte_write_data(3u, 0u);
            xport_gte_write_data(4u, (((y + 16u) & 65535u) << 16u) | (x & 65535u));
            xport_gte_write_data(5u, 0u);
            xport_gte_execute(0x00280030u);
            w_u8(cursor + 4u, (uint8)brightness);
            w_u8(cursor + 5u, (uint8)brightness);
            w_u8(cursor + 6u, (uint8)brightness);
            psx_gte_snapshot(&snapshot); w_u32(cursor + 8u, (uint32)snapshot.sxy[0]);
            psx_gte_snapshot(&snapshot); w_u32(cursor + 16u, (uint32)snapshot.sxy[1]);
            psx_gte_snapshot(&snapshot); w_u32(cursor + 24u, (uint32)snapshot.sxy[2]);
            xport_gte_write_data(0u, (((y + 16u) & 65535u) << 16u) | ((x + 16u) & 65535u));
            xport_gte_write_data(1u, 0u);
            xport_gte_execute(0x00180001u);
            psx_gte_snapshot(&snapshot); w_u32(cursor + 32u, (uint32)snapshot.sxy[2]);
            first = r_u32(0x80065910u);
            second = r_u32(first);
            w_u32(first, cursor & 0xFFFFFFu);
            value = r_u8(cursor + 3u);
            w_u32(cursor, (value << 24u) | second);
            cursor += 40u;
        }
    first = r_u32(0x80065910u);
    DrawOTag((uint32 *)psx_addr(first, 4u));
    state = r_u32(0x800659C0u);
    value = r_u32(state + 0x5DC4u);
    first = r_u32(state + 0x5DC0u);
    callback = r_u32(state + 0x5DD0u);
    value += 1u; first += 34u;
    w_u32(state + 0x5DC4u, value);
    result = (uint32)((sint32)value >= 128);
    w_u32(state + 0x5DC0u, first);
    w_u32(state + 0x5DCCu, result);
    if (callback != 0u)
    {
        /* Retain the explicit original callback context limitation */
        if (v8_native_dispatch_bios_callback(callback) == 0)
        {
            fprintf(stderr, "Untranslated V8 callback at 800165AC: target=%08X\n", callback);
            abort();
        }
    }
    return;
}

