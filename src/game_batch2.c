#include "psx.h"

uint32 sub_80015A20(uint32 destination, uint32 bytes);
uint32 sub_800466F4(uint32 source, uint32 bytes);
uint32 sub_80015A00(void);
void sub_80017E0C(void);
uint32 sub_80017DB4(uint32 node);
uint32 sub_800156D4(void);
void sub_80015798(void);
uint32 sub_80044C44(uint32 destination, uint32 source, uint32 bytes);
void sub_80045088(uint32 address);
uint32 sub_8001A8FC(uint32 asset);
uint32 sub_8001A640(uint32 asset, uint32 opaque);
uint32 sub_80044360(uint32 path);
uint32 sub_800159B4(uint32 path);
uint32 sub_800441F8(void);
uint32 sub_800116F4(uint32 bytes);
uint32 sub_800157D4(uint32 path);
sint32 sub_8001570C(sint32 sector);
uint32 sub_80015368(uint32 path);
uint32 xport_guest_buffer_address(void *host_buffer, size_t bytes);
uint32 xport_guest_nonlocal_transfer(uint32 owner_entry, uint32 source_pc, uint32 target, uint32 known_gpr_mask, const uint32 *known_gpr_values);
uint32 sub_8001A24C(uint32 rectangle);
void sub_800126F0(void);
uint32 sub_8001A2AC(uint32 rectangle, uint32 x, uint32 y);
uint32 sub_8004445C(uint32 voice, uint32 table, uint32 sample);
uint32 sub_800443C8(uint32 voice, uint32 table, uint32 sample, uint32 volume, uint32 incoming_v0);
uint32 sub_80043FF0(uint32 enabled, uint32 mask);
uint32 sub_80018124(uint32 width, uint32 height, uint32 width_alignment, uint32 height_alignment, uint32 max_width, uint32 max_height);
uint32 sub_800120D4(void);

uint32 sub_8001A8FC(uint32 asset)
{
    FUNCTION_MARKER(0x8001A8FCu, "SLUS_005.10");
    return sub_8001A640(asset, 0u);
}

uint32 sub_8001A640(uint32 asset, uint32 opaque)
{
    uint32 allocation, count, offset, table, index, slot, part, rel4, rel12, rel20, primitive_count, primitive, primitive_index;
    uint32 flags, converted, first, second, third, type, target, saved_primitive, step, output;
    FUNCTION_MARKER(0x8001A640u, "SLUS_005.10");
    count = r_u32(asset + 16u);
    allocation = sub_800116F4(((count << 1u) + count) * 4u + 12u);
    w_u32(allocation, asset);
    w_u32(allocation + 4u, opaque);
    w_u32(allocation + 8u, 0u);
    offset = r_u32(asset + 4u);
    count = r_u32(asset);
    w_u32(asset + 4u, asset + offset);
    index = 0u;
    while ((sint32)index < (sint32)count)
    {
        table = r_u32(asset + 4u);
        slot = table + (index << 2u);
        offset = r_u32(slot);
        part = table + offset;
        w_u32(slot, part);
        rel4 = r_u32(part + 4u);
        rel12 = r_u32(part + 12u);
        rel20 = r_u32(part + 20u);
        primitive_count = r_u16(part + 16u);
        primitive = part + rel20;
        w_u32(part + 4u, part + rel4);
        w_u32(part + 12u, part + rel12);
        w_u32(part + 20u, primitive);
        primitive_index = 0u;
        while (primitive_index < primitive_count)
        {
            flags = r_u8(primitive + 3u);
            saved_primitive = primitive;
            converted = ((flags & 15u) << 2u) | ((flags & 0x80u) ? 0x40u : 0u);
            if ((flags & 0x10u) != 0u) converted |= 2u;
            if ((flags & 0x40u) != 0u) converted |= 0x80u;
            first = r_u16(primitive + 4u);
            second = r_u16(primitive + 6u);
            third = r_u16(primitive + 8u);
            w_u8(primitive + 3u, converted);
            type = (converted >> 2u) & 15u;
            w_u16(primitive + 4u, first << 3u);
            w_u16(primitive + 6u, second << 3u);
            w_u16(primitive + 8u, third << 3u);
            target = 0x8001A810u;
            if (type - 1u < 15u)
                target = r_u32(0x80010448u + ((type - 1u) << 2u));
            switch (target)
            {
                case 0x8001A798u:
                    w_u8(primitive + 27u, 0x34u);
                    w_u8(primitive + 23u, 0x34u);
                    break;
                case 0x8001A7A4u:
                    w_u8(primitive + 19u, 0x30u);
                    w_u8(primitive + 15u, 0x30u);
                    break;
                case 0x8001A7B0u:
                    first = r_u16(primitive + 10u);
                    w_u16(primitive + 10u, first << 3u);
                    break;
                case 0x8001A7C4u:
                    first = r_u16(primitive + 10u);
                    second = r_u16(primitive + 12u);
                    third = r_u16(primitive + 14u);
                    w_u16(primitive + 10u, first << 3u);
                    w_u16(primitive + 12u, second << 3u);
                    w_u16(primitive + 14u, third << 3u);
                    break;
                case 0x8001A7ECu:
                    first = r_u8(saved_primitive + 3u);
                    w_u8(saved_primitive + 3u, first | 1u);
                    break;
                case 0x8001A800u:
                    first = r_u16(primitive + 10u);
                    primitive += first << 2u;
                    break;
                case 0x8001A810u:
                    break;
                default:
                {
                    uint32 known_registers[32];
                    known_registers[0] = 0u;
                    known_registers[2] = target;
                    known_registers[3] = type - 1u;
                    known_registers[4] = second << 3u;
                    known_registers[5] = third << 3u;
                    known_registers[6] = primitive;
                    known_registers[7] = converted;
                    known_registers[8] = part;
                    known_registers[9] = index;
                    known_registers[10] = saved_primitive;
                    known_registers[11] = primitive_index;
                    known_registers[12] = allocation;
                    known_registers[13] = 0x30u;
                    known_registers[14] = 0x34u;
                    known_registers[15] = 0x800568FCu;
                    known_registers[16] = 0x80010448u;
                    known_registers[17] = asset;
                    known_registers[28] = 0x80065304u;
                    known_registers[31] = 0x8001A670u;
                    return xport_guest_nonlocal_transfer(0x8001A640u, 0x8001A790u, target, 0x9003FFFDu, known_registers);
                }
            }
            flags = r_u8(saved_primitive + 3u);
            step = r_u16(0x800568FCu + (flags & 0x3Cu));
            primitive_count = r_u16(part + 16u);
            primitive_index += 1u;
            primitive += step;
        }
        count = r_u32(asset);
        index += 1u;
    }
    offset = r_u32(asset + 12u);
    count = r_u32(asset + 8u);
    w_u32(asset + 12u, asset + offset);
    index = 0u;
    while ((sint32)index < (sint32)count)
    {
        table = r_u32(asset + 12u);
        slot = table + (index << 2u);
        offset = r_u32(slot);
        w_u32(slot, table + offset);
        count = r_u32(asset + 8u);
        index += 1u;
    }
    offset = r_u32(asset + 20u);
    count = r_u32(asset + 16u);
    w_u32(asset + 20u, asset + offset);
    index = 0u;
    output = allocation;
    while ((sint32)index < (sint32)count)
    {
        table = r_u32(asset + 20u);
        slot = table + (index << 2u);
        offset = r_u32(slot);
        w_u32(slot, table + offset);
        w_u16(output + 12u, 0u);
        count = r_u32(asset + 16u);
        index += 1u;
        output += 12u;
    }
    return allocation;
}

uint32 sub_80044360(uint32 path)
{
    uint32 result;
    FUNCTION_MARKER(0x80044360u, "SLUS_005.10");
    (void)sub_800159B4(path);
    result = sub_800441F8();
    sub_80015A00();
    return result;
}

uint32 sub_800159B4(uint32 path)
{
    uint32 entry, sector;
    FUNCTION_MARKER(0x800159B4u, "SLUS_005.10");
    entry = sub_800157D4(path);
    if (entry == 0u)
        return sub_80015368(path);
    sector = r_u32(entry + 12u);
    (void)sub_8001570C((sint32)sector);
    w_u32(0x800659B0u, 0u);
    return 1u;
}

uint32 sub_800441F8(void)
{
    uint8 local_frame[1072];
    uint32 frame, header, count, spu_address, descriptor, cursor, value, base, index, remaining, chunk;
    FUNCTION_MARKER(0x800441F8u, "SLUS_005.10");
    frame = xport_guest_buffer_address(local_frame, sizeof(local_frame));
    header = frame + 0x10u;
    (void)sub_80015A20(header, 4u);
    value = r_u16(header + 2u);
    spu_address = (uint32)SpuMalloc((sint32)(((value << 3u) + 63u) & 0xFFFFFFC0u));
    if (spu_address == 0u)
        (void)sub_80015368(0x800658BCu);
    count = (uint32)(sint32)(sint16)r_u16(header);
    descriptor = sub_800116F4((count << 2u) + 4u);
    w_u16(descriptor + 2u, spu_address >> 3u);
    value = r_u16(header);
    w_u16(descriptor, value);
    count = (uint32)(sint32)(sint16)r_u16(header);
    (void)sub_80015A20(descriptor + 4u, count << 2u);
    count = (uint32)(sint32)(sint16)r_u16(header);
    index = 0u;
    cursor = descriptor;
    while ((sint32)index < (sint32)count)
    {
        value = r_u16(cursor + 4u);
        base = r_u16(descriptor + 2u);
        w_u16(cursor + 4u, value + base);
        count = (uint32)(sint32)(sint16)r_u16(header);
        index += 1u;
        cursor += 4u;
    }
    (void)SpuSetTransferMode(0);
    (void)SpuSetTransferStartAddr(spu_address);
    remaining = r_u16(header + 2u) << 3u;
    while (remaining != 0u)
    {
        chunk = ((sint32)remaining < 1024) ? remaining : 1024u;
        (void)sub_80015A20(frame + 0x18u, chunk);
        (void)SpuSetTransferStartAddr(spu_address);
        (void)sub_800466F4(frame + 0x18u, chunk);
        while (SpuIsTransferCompleted(0) == 0)
            continue;
        remaining -= chunk;
        spu_address += chunk;
    }
    return descriptor;
}

uint32 sub_80015A20(uint32 destination, uint32 bytes)
{
    uint32 position, offset, chunk, source, target, end, left, right, address, shift, index;
    uint32 words[4];
    FUNCTION_MARKER(0x80015A20u, "SLUS_005.10");
    position = r_u32(0x800659B0u);
    offset = position & 2047u;
    if (offset != 0u)
    {
        chunk = (0u - position) & 2047u;
        if ((sint32)bytes < (sint32)chunk)
            chunk = bytes;
        source = r_u32(0x800659A0u);
        (void)sub_80044C44(destination, source + offset, chunk);
        position = r_u32(0x800659B0u);
        destination += chunk;
        bytes -= chunk;
        w_u32(0x800659B0u, position + chunk);
    }
    while ((sint32)bytes >= 2048)
    {
        source = sub_800156D4();
        target = destination;
        end = source + 2048u;
        if (((source | destination) & 3u) != 0u)
        {
            do
            {
                for (index = 0u; index != 4u; ++index)
                {
                    address = source + index * 4u;
                    shift = (3u - ((address + 3u) & 3u)) * 8u;
                    left = r_u32((address + 3u) & ~3u) << shift;
                    shift = (address & 3u) * 8u;
                    right = r_u32(address & ~3u);
                    words[index] = (left & ~(0xFFFFFFFFu >> shift)) | (right >> shift);
                }
                for (index = 0u; index != 4u; ++index)
                {
                    address = target + index * 4u;
                    shift = (3u - ((address + 3u) & 3u)) * 8u;
                    (void)xport_memory_write((address + 3u) & ~3u, 4u, words[index] >> shift, (1u << (((address + 3u) & 3u) + 1u)) - 1u);
                    shift = (address & 3u) * 8u;
                    (void)xport_memory_write(address & ~3u, 4u, words[index] << shift, (15u << (address & 3u)) & 15u);
                }
                source += 16u;
                target += 16u;
            } while (source != end);
        }
        else
        {
            do
            {
                words[0] = r_u32(source);
                words[1] = r_u32(source + 4u);
                words[2] = r_u32(source + 8u);
                words[3] = r_u32(source + 12u);
                w_u32(target, words[0]);
                w_u32(target + 4u, words[1]);
                w_u32(target + 8u, words[2]);
                w_u32(target + 12u, words[3]);
                source += 16u;
                target += 16u;
            } while (source != end);
        }
        position = r_u32(0x800659B0u);
        destination += 2048u;
        bytes -= 2048u;
        w_u32(0x800659B0u, position + 2048u);
    }
    if (bytes != 0u)
    {
        source = sub_800156D4();
        w_u32(0x800659A0u, source);
        (void)sub_80044C44(destination, source, bytes);
        position = r_u32(0x800659B0u);
        w_u32(0x800659B0u, position + bytes);
    }
    return 1u;
}

uint32 sub_800466F4(uint32 source, uint32 bytes)
{
    uint32 count = bytes;
    FUNCTION_MARKER(0x800466F4u, "SLUS_005.10");
    if (count > 0x7EFF0u)
        count = 0x7EFF0u;
    (void)_spu_Fw(source, count);
    if (r_u32(0x8005EE0Cu) == 0u)
        w_u32(0x8005EE08u, 0u);
    return count;
}

uint32 sub_80015A00(void)
{
    FUNCTION_MARKER(0x80015A00u, "SLUS_005.10");
    sub_80015798();
    return 1u;
}

void sub_80017E0C(void)
{
    uint32 root;
    FUNCTION_MARKER(0x80017E0Cu, "SLUS_005.10");
    root = r_u32(0x800659C8u);
    if (root != 0u)
    {
        w_u32(0x800659CCu, 0u);
        (void)sub_80017DB4(root);
        w_u32(0x800659C8u, 0u);
    }
    return;
}

uint32 sub_80017DB4(uint32 node)
{
    uint32 result, child;
    FUNCTION_MARKER(0x80017DB4u, "SLUS_005.10");
    result = (uint32)((r_u32(node + 8u) - 2u) < 2u);
    if (result != 0u)
    {
        child = r_u32(node + 16u);
        (void)sub_80017DB4(child);
        child = r_u32(node + 20u);
        result = sub_80017DB4(child);
    }
    sub_80045088(node);
    return result;
}

uint32 sub_8001A24C(uint32 rectangle)
{
    uint32 width, height, node, x, y;
    FUNCTION_MARKER(0x8001A24Cu, "SLUS_005.10");
    width = (uint32)(sint32)(sint16)r_u16(rectangle + 4u);
    height = (uint32)(sint32)(sint16)r_u16(rectangle + 6u);
    node = sub_80018124(width, height, 1u, 1u, 1u, 1u);
    x = (uint32)(sint32)(sint16)r_u16(node);
    y = (uint32)(sint32)(sint16)r_u16(node + 2u);
    (void)MoveImage((PSX_RECT *)psx_addr(rectangle, sizeof(PSX_RECT)), (sint32)x, (sint32)y);
    return node;
}

void sub_800126F0(void)
{
    FUNCTION_MARKER(0x800126F0u, "SLUS_005.10");
    (void)sub_800120D4();
}

uint32 sub_8001A2AC(uint32 rectangle, uint32 x, uint32 y)
{
    FUNCTION_MARKER(0x8001A2ACu, "SLUS_005.10");
    return (uint32)MoveImage((PSX_RECT *)psx_addr(rectangle, sizeof(PSX_RECT)), (sint32)x, (sint32)y);
}

uint32 sub_8004445C(uint32 voice, uint32 table, uint32 sample)
{
    uint32 volume, incoming_v0;
    FUNCTION_MARKER(0x8004445Cu, "SLUS_005.10");
    volume = (uint32)(sint32)(sint16)r_u16(0x80065BE8u);
    incoming_v0 = volume << 16u;
    return sub_800443C8(voice, table, sample, incoming_v0 + volume, incoming_v0);
}

uint32 sub_800443C8(uint32 voice, uint32 table, uint32 sample, uint32 volume, uint32 incoming_v0)
{
    uint32 entry, channel, value;
    FUNCTION_MARKER(0x800443C8u, "SLUS_005.10");
    if (voice != 0u)
    {
        entry = table + (sample << 2u);
        value = r_u16(entry + 6u);
        channel = voice - 1u;
        SpuSetVoicePitch((sint32)channel, (uint16)value);
        SpuSetVoiceVolume((sint32)channel, (sint16)volume, (sint16)(volume >> 16u));
        value = r_u16(entry + 4u);
        SpuSetVoiceStartAddr((sint32)channel, value << 3u);
        (void)sub_80043FF0(1u, 1u << (channel & 31u));
        value = r_u8(0x8005FFB4u);
        w_u8(0x800A2FF0u + channel, value);
        incoming_v0 = 0x800A2FF0u;
    }
    return incoming_v0;
}

uint32 sub_80043FF0(uint32 enabled, uint32 mask)
{
    uint32 shadow, low;
    FUNCTION_MARKER(0x80043FF0u, "SLUS_005.10");
    if (enabled != 0u)
    {
        shadow = r_u32(0x800658B8u);
        w_u16(0x1F801D88u, mask);
        w_u16(0x1F801D8Au, mask >> 16u);
        shadow |= mask;
        w_u32(0x800658B8u, shadow);
        return shadow;
    }
    shadow = r_u32(0x800658B8u);
    shadow &= ~mask;
    w_u32(0x800658B8u, shadow);
    low = r_u16(0x800658B8u);
    shadow = (~shadow) >> 16u;
    w_u16(0x1F801D8Eu, shadow);
    w_u16(0x1F801D8Cu, ~low);
    return shadow;
}

uint32 sub_8001D9C0(uint32 source, uint32 projection);
uint32 sub_80016DFC(uint32 source, uint32 destination);
uint32 sub_80043358(uint32 matrix, uint32 vector, uint32 destination);
void sub_8004D544(uint32 projection);
uint32 sub_8001D898(uint32 matrix);
uint32 sub_80016E64(uint32 matrix);
uint32 sub_80044EFC(uint32 destination, uint32 value, uint32 bytes);
uint32 VectorNormalSS(SVECTOR *source, SVECTOR *destination);
void xport_gte_write_control(uint32 register_index, uint32 value);
void xport_gte_execute(uint32 command);
uint32 sub_80011BE4(uint32 destination);
uint32 sub_80011C58(uint32 source);
uint32 sub_80016DA8(uint32 destination);
uint32 sub_8004D314(uint32 matrix, uint32 translation);
uint32 sub_8001D3D8(void);
uint32 sub_8001D370(void);
uint32 sub_8001A1E8(uint32 x, uint32 y, uint32 width, uint32 height);
uint32 sub_80043CE0(uint32 track);
uint32 sub_8001AC44(uint32 object, uint32 index, uint32 allocation_bytes, uint32 flags);
uint32 sub_8001AAA8(uint32 object, uint32 descriptor, uint32 allocation_bytes);
uint32 sub_80018124(uint32 width, uint32 height, uint32 width_alignment, uint32 height_alignment, uint32 max_width, uint32 max_height);
uint32 sub_8001178C(uint32 bytes, uint32 clear);
uint32 sub_8001AB98(uint32 object, uint32 index);
uint32 sub_8001B49C(uint32 object, uint32 index, uint32 incoming_s1);
uint32 sub_8001D708(uint32 node);
sint32 sub_80049534(uint32 position);
uint32 xport_guest_buffer_address(void *host_buffer, size_t bytes);
const uint32 xport_cd_sync_callback_address = 0x80060080u;

uint32 sub_80011BE4(uint32 destination)
{
    uint32 value, index;
    FUNCTION_MARKER(0x80011BE4u, "SLUS_005.10");
    value = r_u8(0x80065319u);
    w_u8(destination, value);
    value = r_u8(0x800658F8u);
    w_u8(destination + 1u, value);
    index = 0u;
    do
    {
        value = r_u8(0x80065674u + index);
        w_u8(destination + index + 2u, value);
        index += 1u;
    } while (index < 6u);
    index = 0u;
    do
    {
        value = r_u8(0x8006567Cu + index);
        w_u8(destination + index + 8u, value);
        index += 1u;
    } while (index < 4u);
    return 0x80065680u;
}

uint32 sub_80011C58(uint32 source)
{
    uint32 value, index;
    FUNCTION_MARKER(0x80011C58u, "SLUS_005.10");
    value = r_u8(source);
    w_u8(0x80065319u, value);
    value = r_u8(source + 1u);
    w_u8(0x800658F8u, value);
    index = 0u;
    do
    {
        value = r_u8(source + index + 2u);
        w_u8(0x80065674u + index, value);
        index += 1u;
    } while (index < 6u);
    index = 0u;
    do
    {
        value = r_u8(source + index + 8u);
        w_u8(0x8006567Cu + index, value);
        index += 1u;
    } while (index < 4u);
    return source + 4u;
}

uint32 sub_80016DA8(uint32 destination)
{
    uint32 first, second, third;
    FUNCTION_MARKER(0x80016DA8u, "SLUS_005.10");
    first = r_u32(0x800568B4u);
    second = r_u32(0x800568B8u);
    third = r_u32(0x800568BCu);
    w_u32(destination, first);
    w_u32(destination + 4u, second);
    w_u32(destination + 8u, third);
    first = r_u32(0x800568C0u);
    second = r_u32(0x800568C4u);
    third = r_u32(0x800568C8u);
    w_u32(destination + 12u, first);
    w_u32(destination + 16u, second);
    w_u32(destination + 20u, third);
    first = r_u32(0x800568CCu);
    second = r_u32(0x800568D0u);
    w_u32(destination + 24u, first);
    w_u32(destination + 28u, second);
    return destination;
}

uint32 sub_8004D314(uint32 matrix, uint32 translation)
{
    uint32 first, second, third;
    FUNCTION_MARKER(0x8004D314u, "SLUS_005.10");
    first = r_u32(translation);
    second = r_u32(translation + 4u);
    third = r_u32(translation + 8u);
    w_u32(matrix + 20u, first);
    w_u32(matrix + 24u, second);
    w_u32(matrix + 28u, third);
    return matrix;
}

uint32 sub_8001D3D8(void)
{
    FUNCTION_MARKER(0x8001D3D8u, "SLUS_005.10");
    return sub_80044EFC(0x8006F760u, 0u, 32u);
}

uint32 sub_8001D9C0(uint32 source, uint32 projection)
{
    uint32 first, second, third;
    FUNCTION_MARKER(0x8001D9C0u, "SLUS_005.10");
    first = r_u32(source + 0u);
    second = r_u32(source + 4u);
    third = r_u32(source + 8u);
    w_u32(0x8006F6E0u + 0u, first);
    w_u32(0x8006F6E0u + 4u, second);
    w_u32(0x8006F6E0u + 8u, third);
    first = r_u32(source + 12u);
    second = r_u32(source + 16u);
    third = r_u32(source + 20u);
    w_u32(0x8006F6E0u + 12u, first);
    w_u32(0x8006F6E0u + 16u, second);
    w_u32(0x8006F6E0u + 20u, third);
    first = r_u32(source + 24u);
    second = r_u32(source + 28u);
    w_u32(0x8006F6E0u + 24u, first);
    w_u32(0x8006F6E0u + 28u, second);
    first = r_u32(0x8006F6E0u + 0u);
    second = r_u32(0x8006F6E0u + 4u);
    w_u32(0x8006F740u + 0u, first);
    w_u32(0x8006F740u + 4u, second);
    first = r_u32(0x8006F6E0u + 8u);
    second = r_u32(0x8006F6E0u + 12u);
    w_u32(0x8006F740u + 8u, first);
    w_u32(0x8006F740u + 12u, second);
    first = r_u32(0x8006F6E0u + 16u);
    second = r_u32(0x8006F6E0u + 20u);
    w_u32(0x8006F740u + 16u, first);
    w_u32(0x8006F740u + 20u, second);
    first = r_u32(0x8006F6E0u + 24u);
    second = r_u32(0x8006F6E0u + 28u);
    w_u32(0x8006F740u + 24u, first);
    w_u32(0x8006F740u + 28u, second);
    (void)sub_80016DFC(source, 0x8006F680u);
    w_u32(0x800659D8u, projection);
    sub_8004D544(projection);
    (void)MulMatrix0((MATRIX *)psx_addr(0x8006F720u, 20u), (MATRIX *)psx_addr(source, 20u), (MATRIX *)psx_addr(0x8006F700u, 20u));
    (void)sub_8001D898(0x8006F680u);
    first = r_u32(0x8006F680u + 0u);
    second = r_u32(0x8006F680u + 4u);
    w_u32(0x8006F660u + 0u, first);
    w_u32(0x8006F660u + 4u, second);
    first = r_u32(0x8006F680u + 8u);
    second = r_u32(0x8006F680u + 12u);
    w_u32(0x8006F660u + 8u, first);
    w_u32(0x8006F660u + 12u, second);
    first = r_u32(0x8006F680u + 16u);
    second = r_u32(0x8006F680u + 20u);
    w_u32(0x8006F660u + 16u, first);
    w_u32(0x8006F660u + 20u, second);
    first = r_u32(0x8006F680u + 24u);
    second = r_u32(0x8006F680u + 28u);
    w_u32(0x8006F660u + 24u, first);
    w_u32(0x8006F660u + 28u, second);
    return sub_80016E64(0x8006F660u);
}

uint32 sub_80016DFC(uint32 source, uint32 destination)
{
    uint32 first, second, third;
    FUNCTION_MARKER(0x80016DFCu, "SLUS_005.10");
    (void)TransposeMatrix((MATRIX *)psx_addr(source, 18u), (MATRIX *)psx_addr(destination, 18u));
    (void)sub_80043358(destination, source + 20u, destination + 20u);
    first = r_u32(destination + 20u);
    second = r_u32(destination + 24u);
    third = r_u32(destination + 28u);
    w_u32(destination + 20u, 0u - first);
    w_u32(destination + 24u, 0u - second);
    w_u32(destination + 28u, 0u - third);
    return destination;
}

uint32 sub_80043358(uint32 matrix, uint32 vector, uint32 destination)
{
    uint32 words[5];
    uint32 x, y, z, high_x, high_y, high_z;
    FUNCTION_MARKER(0x80043358u, "SLUS_005.10");
    words[0] = r_u32(matrix + 0u);
    words[1] = r_u32(matrix + 4u);
    words[2] = r_u32(matrix + 8u);
    words[3] = r_u32(matrix + 12u);
    words[4] = r_u32(matrix + 16u);
    xport_gte_write_control(0u, words[0]);
    xport_gte_write_control(1u, words[1]);
    xport_gte_write_control(2u, words[2]);
    xport_gte_write_control(3u, words[3]);
    xport_gte_write_control(4u, words[4]);
    x = r_u32(vector + 0u);
    y = r_u32(vector + 4u);
    z = r_u32(vector + 8u);
    xport_gte_write_data(9u, (uint32)((sint32)x >> 15));
    xport_gte_write_data(10u, (uint32)((sint32)y >> 15));
    xport_gte_write_data(11u, (uint32)((sint32)z >> 15));
    x &= 0x7FFFu;
    y &= 0x7FFFu;
    xport_gte_execute(0x41E012u);
    z &= 0x7FFFu;
    high_x = xport_gte_read_data(25u);
    high_y = xport_gte_read_data(26u);
    high_z = xport_gte_read_data(27u);
    xport_gte_write_data(9u, x);
    xport_gte_write_data(10u, y);
    xport_gte_write_data(11u, z);
    high_x <<= 3;
    high_y <<= 3;
    xport_gte_mvmva(0x49E012u);
    high_z <<= 3;
    x = xport_gte_read_data(25u);
    y = xport_gte_read_data(26u);
    z = xport_gte_read_data(27u);
    x += high_x;
    y += high_y;
    z += high_z;
    w_u32(destination + 0u, x);
    w_u32(destination + 4u, y);
    w_u32(destination + 8u, z);
    return destination;
}

void sub_8004D544(uint32 projection)
{
    FUNCTION_MARKER(0x8004D544u, "SLUS_005.10");
    gte_write_h((uint16)projection);
    return;
}

uint32 sub_8001D898(uint32 matrix)
{
    uint8 frame[96];
    uint32 frame_address;
    uint32 projection, width, height, first, second, third, fourth;
    FUNCTION_MARKER(0x8001D898u, "SLUS_005.10");
    frame_address = xport_guest_buffer_address(frame, sizeof(frame));
    (void)sub_80044EFC(frame_address + 48u, 0u, 32u);
    projection = r_u16(0x800659D8u);
    width = r_u32(0x800659DCu);
    height = r_u32(0x800659E0u);
    width = 0u - width;
    width += width >> 31;
    width = (uint32)((sint32)width >> 1);
    xport_store_le16(frame + 48u, (uint16)projection);
    projection = 0u - projection;
    height = 0u - height;
    xport_store_le16(frame + 52u, (uint16)width);
    xport_store_le16(frame + 58u, (uint16)width);
    height += height >> 31;
    height = (uint32)((sint32)height >> 1);
    xport_store_le16(frame + 54u, (uint16)projection);
    xport_store_le16(frame + 62u, (uint16)projection);
    xport_store_le16(frame + 64u, (uint16)height);
    first = xport_load_le32(frame + 48u);
    second = xport_load_le32(frame + 52u);
    third = xport_load_le32(frame + 56u);
    fourth = xport_load_le32(frame + 60u);
    xport_store_le32(frame + 16u, first);
    xport_store_le32(frame + 20u, second);
    xport_store_le32(frame + 24u, third);
    xport_store_le32(frame + 28u, fourth);
    first = xport_load_le32(frame + 64u);
    second = xport_load_le32(frame + 68u);
    third = xport_load_le32(frame + 72u);
    fourth = xport_load_le32(frame + 76u);
    xport_store_le32(frame + 32u, first);
    xport_store_le32(frame + 36u, second);
    xport_store_le32(frame + 40u, third);
    xport_store_le32(frame + 44u, fourth);
    (void)VectorNormalSS((SVECTOR *)(frame + 16u), (SVECTOR *)(frame + 16u));
    (void)VectorNormalSS((SVECTOR *)(frame + 22u), (SVECTOR *)(frame + 22u));
    (void)VectorNormalSS((SVECTOR *)(frame + 28u), (SVECTOR *)(frame + 28u));
    (void)MulMatrix0((MATRIX *)(frame + 16u), (MATRIX *)psx_addr(matrix, 20u), (MATRIX *)psx_addr(0x8006F780u, 20u));
    return 0x8006F780u;
}

uint32 sub_80016E64(uint32 matrix)
{
    uint32 x, z, root, reciprocal, first, second, nx, nz, a, b, result;
    FUNCTION_MARKER(0x80016E64u, "SLUS_005.10");
    x = (uint32)(sint32)(sint16)r_u16(matrix);
    z = (uint32)(sint32)(sint16)r_u16(matrix + 12u);
    root = SquareRoot0((sint32)(x * x + z * z));
    reciprocal = root == 0u ? 0xFFFFFFFFu : (uint32)((sint64)0x1000000 / (sint32)root);
    x = (uint32)(sint32)(sint16)r_u16(matrix);
    first = x * reciprocal;
    if ((sint32)first < 0) first += 4095u;
    z = (uint32)(sint32)(sint16)r_u16(matrix + 12u);
    second = z * reciprocal;
    nx = (uint32)((sint32)first >> 12);
    if ((sint32)second < 0) second += 4095u;
    w_u16(matrix + 16u, root);
    a = (uint32)(sint32)(sint16)r_u16(matrix + 6u);
    b = (uint32)(sint32)(sint16)r_u16(matrix + 10u);
    nz = (uint32)((sint32)second >> 12);
    result = nx * a - nz * b;
    w_u16(matrix + 12u, 0u);
    if ((sint32)result < 0) result += 4095u;
    b = (uint32)(sint32)(sint16)r_u16(matrix + 10u);
    first = (uint32)((sint32)result >> 12);
    result = nz * a + nx * b;
    w_u16(matrix + 6u, first);
    if ((sint32)result < 0) result += 4095u;
    x = (uint32)(sint32)(sint16)r_u16(matrix);
    z = (uint32)(sint32)(sint16)r_u16(matrix + 4u);
    first = (uint32)((sint32)result >> 12);
    result = nx * x - nz * z;
    w_u16(matrix + 10u, first);
    if ((sint32)result < 0) result += 4095u;
    w_u16(matrix, (uint32)((sint32)result >> 12));
    w_u16(matrix + 4u, 0u);
    return matrix;
}

uint32 sub_8001D370(void)
{
    uint32 offset, projection;
    FUNCTION_MARKER(0x8001D370u, "SLUS_005.10");
    offset = r_u32(0x80065308u) << 14u;
    w_u32(0x8005E93Cu, 0x8005693Cu + offset);
    w_u32(0x8005E940u, 0x8005A93Cu + offset);
    SetLightMatrix((MATRIX *)psx_addr(0x8006F760u, sizeof(MATRIX)));
    SetBackColor(64, 64, 64);
    projection = r_u32(0x800659D8u);
    return SetFogNearFar(2048, 8192, (sint32)projection);
}

uint32 sub_8001A1E8(uint32 x, uint32 y, uint32 width, uint32 height)
{
    uint8 rectangle_bytes[8];
    uint32 node, target_x, target_y, guest_rectangle;
    FUNCTION_MARKER(0x8001A1E8u, "SLUS_005.10");
    xport_store_le16(rectangle_bytes, (uint16)x);
    xport_store_le16(rectangle_bytes + 2u, (uint16)y);
    xport_store_le16(rectangle_bytes + 4u, (uint16)width);
    xport_store_le16(rectangle_bytes + 6u, (uint16)height);
    node = sub_80018124(width, height, 1u, 1u, 1u, 1u);
    target_x = (uint32)(sint32)(sint16)r_u16(node);
    target_y = (uint32)(sint32)(sint16)r_u16(node + 2u);
    guest_rectangle = xport_guest_buffer_address(rectangle_bytes, sizeof(rectangle_bytes));
    (void)MoveImage((PSX_RECT *)psx_addr(guest_rectangle, sizeof(PSX_RECT)), (sint32)target_x, (sint32)target_y);
    return node;
}

uint32 sub_80043CE0(uint32 track)
{
    uint8 parameter[8];
    uint32 state, index, source, address, shift, left, value, guest_parameter;
    sint32 position;
    FUNCTION_MARKER(0x80043CE0u, "SLUS_005.10");
    state = r_u32(0x800658B0u);
    parameter[0] = 5u;
    w_u8(0x80065BF4u, track);
    index = track + (state < 3u ? 1u : 2u);
    source = 0x800A3090u + (index << 2u);
    address = source + 3u;
    shift = (3u - (address & 3u)) * 8u;
    left = r_u32(address & ~3u) << shift;
    shift = (source & 3u) * 8u;
    value = (left & ~(0xFFFFFFFFu >> shift)) | (r_u32(source & ~3u) >> shift);
    (void)xport_memory_write(0x80065BE0u, 4u, value, 15u);
    (void)xport_memory_write(0x80065BE0u, 4u, value, 15u);
    position = sub_80049534(source + 4u);
    w_u32(0x80065BE4u, (uint32)position - 150u);
    guest_parameter = xport_guest_buffer_address(parameter, sizeof(parameter));
    (void)CdControl(14u, (uint8 *)psx_addr(guest_parameter, sizeof(parameter)), 0);
    (void)CdControl(3u, (uint8 *)psx_addr(0x80065BE0u, 4u), 0);
    return CdSyncCallbackPSX(0x80043C34u);
}

uint32 sub_8001AC44(uint32 object, uint32 index, uint32 allocation_bytes, uint32 flags)
{
    uint32 base, descriptor, signed_kind, kind, value, node, child;
    FUNCTION_MARKER(0x8001AC44u, "SLUS_005.10");
    base = r_u32(object);
    descriptor = base + ((index & 65535u) * 28u) + 28u;
    signed_kind = (uint32)(sint32)(sint16)r_u16(descriptor);
    kind = r_u16(descriptor);
    if ((sint32)signed_kind < 0)
    {
        if (kind != 65535u || (flags & 4u) != 0u)
        {
            if ((flags & 1u) == 0u) return 0u;
            child = r_u16(descriptor + 24u);
            if (child == 65535u) return 0u;
            return sub_8001AC44(object, child, 128u, flags);
        }
    }
    node = sub_8001AAA8(object, descriptor, allocation_bytes);
    w_u16(node + 10u, index);
    value = r_u16(descriptor + 22u);
    w_u16(node + 6u, value);
    if ((flags & 8u) != 0u)
    {
        value = sub_8001AB98(object, index & 65535u);
        w_u32(node + 96u, value);
    }
    else
        w_u32(node + 96u, 0u);
    value = r_u16(0x800659D0u);
    w_u16(node + 70u, value);
    if ((flags & 1u) != 0u)
    {
        child = r_u16(descriptor + 24u);
        if (child != 65535u)
        {
            child = r_u16(descriptor + 24u);
            child = sub_8001AC44(object, child, 128u, flags);
            w_u32(node + 52u, child);
            w_u32(child + 60u, node);
        }
        else
            w_u32(node + 52u, 0u);
    }
    else
        w_u32(node + 52u, 0u);
    if ((flags & 2u) == 0u)
    {
        child = r_u16(descriptor + 26u);
        if (child != 65535u)
        {
            child = r_u16(descriptor + 26u);
            child = sub_8001AC44(object, child, 128u, flags | 1u);
            w_u32(node + 56u, child);
            w_u32(child + 60u, node);
        }
        else
            w_u32(node + 56u, 0u);
    }
    else
        w_u32(node + 56u, 0u);
    w_u32(node + 60u, 0u);
    return node;
}

uint32 sub_8001AAA8(uint32 object, uint32 descriptor, uint32 allocation_bytes)
{
    uint32 node, signed_kind, kind, flags, address, shift, left, value, halfword, first, second, third, base, table;
    FUNCTION_MARKER(0x8001AAA8u, "SLUS_005.10");
    node = sub_8001178C(allocation_bytes, 1u);
    signed_kind = (uint32)(sint32)(sint16)r_u16(descriptor);
    kind = r_u16(descriptor);
    flags = (sint32)signed_kind < 0 ? 0u : ((kind & 2048u) != 0u ? 16u : 0u);
    w_u32(node, flags);
    address = descriptor + 16u;
    shift = (3u - ((address + 3u) & 3u)) * 8u;
    left = r_u32((address + 3u) & ~3u) << shift;
    shift = (address & 3u) * 8u;
    value = (left & ~(0xFFFFFFFFu >> shift)) | (r_u32(address & ~3u) >> shift);
    halfword = r_u16(descriptor + 20u);
    address = node + 64u;
    shift = (3u - ((address + 3u) & 3u)) * 8u;
    (void)xport_memory_write((address + 3u) & ~3u, 4u, value >> shift, (1u << (((address + 3u) & 3u) + 1u)) - 1u);
    shift = (address & 3u) * 8u;
    (void)xport_memory_write(address & ~3u, 4u, value << shift, (15u << (address & 3u)) & 15u);
    w_u16(node + 68u, halfword);
    first = r_u32(descriptor + 4u);
    second = r_u32(descriptor + 8u);
    third = r_u32(descriptor + 12u);
    w_u32(node + 72u, first);
    w_u32(node + 76u, second);
    w_u32(node + 80u, third);
    w_u32(node + 88u, object);
    signed_kind = (uint32)(sint32)(sint16)r_u16(descriptor);
    kind = r_u16(descriptor);
    if ((sint32)signed_kind >= 0)
    {
        value = sub_8001B49C(object, kind & 2047u, descriptor);
        w_u32(node + 48u, value);
    }
    halfword = (uint32)(sint32)(sint16)r_u16(descriptor + 2u);
    if ((sint32)halfword >= 0)
    {
        base = r_u32(object);
        table = r_u32(base + 12u);
        value = r_u32(table + (halfword << 2u));
        w_u32(node + 92u, value);
    }
    sub_8001D708(node);
    return node;
}
