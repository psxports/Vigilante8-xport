#include "psx.h"
sint32 v8_native_3E80C(uint32 object, uint32 mode);
#include "xport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32 sub_80015F80(uint32 path);
uint32 v8_native_11ADC_host(const char *path);
uint32 v8_native_21B80(uint32 callback, uint32 asset, uint32 kind, uint32 flags);
uint32 sub_8001D470(uint32 bytes);
uint32 v8_native_find_file(const char *path);
sint32 sub_8001570C(sint32 sector);
uint32 sub_800225D4(uint32 *header, uint32 *remaining);
uint32 sub_80019034(uint32 asset, uint32 size);
uint32 sub_800190A8(uint32 object);
void sub_80019960(uint32 object, uint32 text, uint32 x, uint32 y);
void sub_80045088(uint32 allocation);
uint32 v8_native_19370(uint32 object, uint8 *packet, uint32 character, uint32 x, uint32 y);
void v8_native_shell_DC18(uint32 base, uint32 asset, uint32 x, uint32 y, uint32 flags);
uint32 sub_800251FC(uint32 mode);
uint32 sub_8001178C(uint32 count, uint32 size);
uint32 sub_8002263C(uint32 bytes, uint32 prepare);
void v8_native_187E4(uint32 image, uint8 *output);
uint32 sub_80018124(uint32 width, uint32 height, uint32 wa, uint32 ha, uint32 mw, uint32 mh);
void sub_80017E0C(void);
uint32 sub_80015A00(void);
MATRIX *v8_native_16DA8(MATRIX *matrix);
void v8_native_1D404(uint32 light, uint32 vector, uint32 color);
uint32 sub_80044C44(uint32 destination, uint32 source, uint32 bytes);
uint32 sub_8001BDDC(uint32 object, uint32 incoming_v0);
void sub_8003E2C4(uint32 object);
void sub_800204DC(uint32 object);
uint32 sub_8001DC1C(uint32 object);
uint32 sub_8001B49C(uint32 object, uint32 kind, uint32 incoming_s1);
uint32 sub_8001D708(uint32 object);
uint32 sub_8001FE50(uint32 list, uint32 object);
uint32 sub_80022C54(uint32 object);
uint32 sub_8001EC48(uint32 object);
uint32 sub_8003FC94(uint32 object);
uint32 sub_8001AC44(uint32 asset, uint32 kind, uint32 bytes, uint32 flags);
uint32 sub_8001D4F0(uint32 parent, uint32 child);
void sub_80044484(uint32 voice, uint32 table, uint32 sample, uint32 volume);
uint32 sub_800447E8(uint32 voice, uint32 table, uint32 sample, uint32 position);
void sub_800441C8(uint32 voice);
uint32 sub_8001BDA0(uint32 asset, uint32 index, uint32 incoming_s1);
void sub_8003E598(uint32 object, uint32 model);
uint32 v8_native_terrain_call3(uint32 callback, uint32 object, uint32 mode, uint32 value);
uint32 sub_800443C8(uint32 voice, uint32 table, uint32 sample, uint32 volume, uint32 incoming_v0);
uint32 sub_80025400(uint32 x, uint32 z);
uint32 sub_8002A3E8(uint32 object, uint32 mode, uint32 kind);
uint32 sub_8002A4E4(uint32 object, uint32 mode, uint32 kind);
sint16 *sub_80025800(sint32 x, sint32 z, sint16 *output);
uint32 sub_80017160(void);
uint32 sub_800116F4(uint32 bytes);
uint32 sub_80043CE0(uint32 track);
uint32 sub_8001859C(uint32 clut);
uint32 sub_8001A91C(uint32 object);
void v8_native_435C0(uint32 matrix, const sint32 *source, sint32 *destination);
uint32 sub_800446DC(uint32 position);
uint32 sub_80023D00(void);
uint32 sub_8001D9C0(uint32 source, uint32 projection);
uint32 sub_8001D624(uint32 object);
uint32 sub_80020890(uint32 object, uint32 delay);
void sub_80044574(uint32 channel, uint32 volume);
uint32 sub_8002E2BC(uint32 object, uint32 reason, uint32 update);
void v8_native_4352C(uint32 matrix, const sint32 *source, sint32 *destination);
typedef void (*V8LoadColorCallback)(uint32 base, uint32 color, uint32 primitive, uint32 vertex, uint32 normal);
static uint32 ski_module;

uint32 v8_native_terrain_point_noop(uint32 target, uint32 event)
{
    if (ski_module == 0u || target != ski_module + 0x974u || event != 9u)
        return 0u;
    return r_u32(ski_module + 0x78u + event * 4u) == ski_module + 0x1020u;
}

void sub_8001DB24(uint32 object, sint32 height)
{
    uint32 matrix;
    FUNCTION_MARKER(0x8001DB24u, "SLUS_005.10");
    matrix = sub_8001D624(object);
    (void)sub_8001D9C0(matrix, (uint32)height);
}

static void load_ai_map(uint32 source, uint32 bytes)
{
    uint32 destination = sub_800116F4(bytes);
    w_u32(0x800659F0u, destination);
    (void)sub_80044C44(destination, source, bytes);
    w_u32(0x800659E8u, bytes);
}

static void load_zone_map(uint32 source)
{
    uint32 row, column, zone, destination, lower, upper, old;
    w_u32(0x80065B3Cu, 0x08000000u);
    w_u32(0x80065B34u, 0x08000000u);
    w_u32(0x80065B40u, 0u);
    w_u32(0x80065B38u, 0u);
    for (row = 0u; row < 32u; ++row)
    {
        for (column = 0u; column < 32u; ++column)
        {
            zone = r_u16(source);
            zone = (zone >> 8u) | ((zone & 255u) << 8u);
            destination = r_u32(0x8007A8A0u + zone * 4u);
            source += 2u;
            w_u32(0x800911A0u + row * 4u + column * 128u, destination);
            if (zone != 0u)
            {
                old = r_u32(0x80065B34u);
                lower = column << 22u;
                if ((sint32)old < (sint32)lower)
                    lower = old;
                old = r_u32(0x80065B38u);
                upper = (column + 1u) << 22u;
                if ((sint32)upper < (sint32)old)
                    upper = old;
                w_u32(0x80065B34u, lower);
                old = r_u32(0x80065B3Cu);
                lower = row << 22u;
                w_u32(0x80065B38u, upper);
                if ((sint32)old < (sint32)lower)
                    lower = old;
                old = r_u32(0x80065B40u);
                upper = (row + 1u) << 22u;
                w_u32(0x80065B3Cu, lower);
                if ((sint32)upper < (sint32)old)
                    upper = old;
                w_u32(0x80065B40u, upper);
            }
        }
    }
}

static void load_zone(uint32 source)
{
    uint32 slot = 0u, row, column, destination, value;
    while (slot < 64u && r_u32(0x8007A8A0u + slot * 4u) != 0u)
        ++slot;
    destination = sub_800116F4(0x3000u);
    w_u32(0x8007A8A0u + slot * 4u, destination);
    for (row = 0u; row < 64u; ++row)
    {
        for (column = 0u; column < 64u; ++column)
        {
            value = r_u8(source + 2u) >> 3u;
            destination = r_u32(0x8007A8A0u + slot * 4u);
            value = (((r_u16(source) >> 8u) | ((r_u16(source) & 255u) << 8u)) - 512u) | (value << 11u);
            w_u16(destination + row * 128u + column * 2u, value);
            destination = r_u32(0x8007A8A0u + slot * 4u);
            source += 4u;
            w_u8(destination + 0x2000u + row * 64u + column, r_u8(source - 1u));
        }
    }
}

uint32 v8_native_load_create_camera(uint32 owner, uint32 mode)
{
    uint32 object = sub_8001D470(212u), flags = r_u32(object), split;
    w_u32(object + 100u, 0x8003D214u);
    w_u32(object + 128u, owner);
    w_u16(object + 138u, mode);
    w_u32(object, flags | 0x10000u);
    split = r_u32(0x80065314u);
    w_u16(object + 140u, split == 1u ? 0xFF60u : 0xFF00u);
    w_u16(object + 144u, split == 1u ? 80u : 160u);
    owner = r_u32(object + 128u);
    w_u16(object + 142u, 0u);
    flags = r_u32(owner + 84u);
    w_u16(object + 146u, 0x2CB4u);
    w_u32(object + 152u, 0x32000u);
    w_u32(object + 148u, flags + 0x1E000u);
    return object;
}

uint32 v8_native_load_insert_camera(uint32 camera)
{
    w_u32(camera, r_u32(camera) | 128u);
    return sub_8001FE50(0x80065A60u, camera);
}

void v8_native_load_position_camera(uint32 camera)
{
    SVECTOR angles;
    MATRIX rotation;
    uint32 owner, value, x, z, desired, terrain;
    angles.vx = (sint16)r_u16(camera + 140u);
    owner = r_u32(camera + 128u);
    angles.vy = (sint16)(r_u16(owner + 66u) + r_u16(camera + 142u));
    angles.vz = 0;
    (void)RotMatrix(&angles, &rotation);
    value = (uint32)(sint32)rotation.m[0][2] * r_u32(camera + 148u);
    owner = r_u32(camera + 128u);
    x = r_u32(owner + 36u) - (uint32)((sint32)value / 4096);
    w_u32(camera + 72u, x);
    value = (uint32)(sint32)rotation.m[2][2] * r_u32(camera + 148u);
    owner = r_u32(camera + 128u);
    z = r_u32(owner + 44u) - (uint32)((sint32)value / 4096);
    w_u32(camera + 80u, z);
    value = (uint32)(sint32)rotation.m[1][2] * r_u32(camera + 148u);
    owner = r_u32(camera + 128u);
    desired = r_u32(owner + 40u) - (uint32)((sint32)value / 4096);
    terrain = sub_80025400(r_u32(camera + 72u), z) - 0x8000u;
    if ((sint32)desired < (sint32)terrain)
        terrain = desired;
    w_u32(camera + 76u, terrain);
    (void)sub_8001D708(camera);
}

static uint32 load_allocate_voice(void)
{
    uint32 clock = r_u32(0x8005FFB4u), index;
    for (index = 0u; index < 24u; ++index)
    {
        /* The original loop reloads the mask before each test */
        if ((r_u32(0x80065C00u) & 1u) == 0u && r_u16(0x1F801C0Cu + index * 16u) == 0u &&
            ((clock - r_u8(0x800A2FF0u + index)) & 255u) >= 2u)
            return index + 1u;
    }
    return 0u;
}

static void load_set_vehicle_health(uint32 object, uint32 value)
{
    uint32 index, part;
    w_u16(object + 14u, value);
    w_u16(object + 12u, value);
    for (index = 0u; index < 3u; ++index)
    {
        part = r_u32(object + 236u + index * 4u);
        w_u16(part + 12u, value);
    }
}

static uint32 load_insert_active_object(uint32 object)
{
    if ((r_u32(object) & 4u) != 0u)
        (void)sub_8001FE50(0x80065A80u, object);
    if ((r_u32(object) & 128u) != 0u)
        (void)sub_8001FE50(0x80065A60u, object);
    return sub_8001FE50(0x80065A18u, object);
}

static uint32 load_activate_object(uint32 object, uint32 incoming_s1)
{
    uint32 callback, result = 0u, model;
    (void)sub_8001D708(object);
    (void)sub_8001DC1C(object);
    callback = r_u32(object + 100u);
    if (callback != 0u)
        result = v8_native_terrain_call3(callback, object, 1u, 0u);
    if ((sint32)result < 0)
        return 0u;
    if ((r_u32(object) & 8u) != 0u && r_u32(object + 112u) == 0u)
    {
        model = sub_8001BDA0(r_u32(0x800737D4u), 13u, incoming_s1);
        sub_8003E598(object, model);
    }
    return load_insert_active_object(object);
}
static uint32 load_length(const sint32 *vector);

uint32 v8_native_find_object_node(uint32 list, sint32 identifier, uint32 excluded)
{
    uint32 node = r_u32(list), next = r_u32(node), object;
    while (next != 0u)
    {
        object = r_u32(node + 8u);
        if (object != excluded && (sint32)(sint16)r_u16(object + 6u) == identifier)
            return node;
        node = next;
        next = r_u32(node);
    }
    return 0u;
}

uint32 v8_native_find_object(uint32 list, sint32 identifier)
{
    uint32 node = v8_native_find_object_node(list, identifier, 0u);
    return node != 0u ? r_u32(node + 8u) : 0u;
}

static uint32 load_build_collision_model(uint32 object)
{
    uint32 asset = r_u32(object + 88u), table, index, descriptor, type, value;
    if (asset != 0u)
    {
        table = r_u32(asset);
        index = r_u16(table + r_u16(object + 10u) * 28u + 54u);
        while (index != 65535u)
        {
            descriptor = table + index * 28u;
            type = r_u16(descriptor + 28u);
            if ((type & 0xF000u) == 0xC000u)
            {
                if ((type & 0x800u) != 0u)
                    w_u32(object, r_u32(object) | 0x1000u);
                value = sub_8001B49C(asset, type & 0x7FFu, object);
                w_u32(object + 104u, value);
                value = r_u16(descriptor + 50u);
                if (value != 0u)
                    value <<= 16u;
                else
                    value = r_u32(object + 84u) * (uint32)(sint32)(sint16)r_u16(0x800658E8u);
                value *= r_u8(0x800659D3u);
                w_u32(object + 108u, (uint32)((sint32)value / 256));
                return 1u;
            }
            index = r_u16(descriptor + 52u);
        }
    }
    w_u32(object + 104u, 0u);
    w_u32(object + 108u, 0u);
    return 0u;
}

uint32 v8_native_clone_vehicle(uint32 source)
{
    uint32 object, first, second, flags, child, words[3], rotation, index;
    object = v8_native_21B80(r_u32(source + 100u), r_u32(source + 88u), r_u16(source + 10u),
                           (r_u32(source) << 1u) & 8u);
    first = r_u16(source + 12u);
    second = r_u16(source + 14u);
    flags = r_u32(object);
    w_u32(object + 100u, r_u32(source + 100u));
    flags |= r_u32(source);
    w_u32(object, flags);
    w_u16(object + 6u, r_u16(source + 6u));
    w_u8(object + 8u, r_u8(source + 8u));
    for (index = 0u; index < 3u; ++index)
        words[index] = r_u32(source + 72u + index * 4u);
    for (index = 0u; index < 3u; ++index)
        w_u32(object + 72u + index * 4u, words[index]);
    rotation = r_u32(source + 64u);
    flags = r_u16(source + 68u);
    w_u32(object + 64u, rotation);
    w_u16(object + 68u, flags);
    w_u8(object + 9u, r_u8(source + 9u));
    if (first != 0u || second != 0u)
    {
        child = r_u32(object + 56u);
        w_u16(object + 12u, first);
        w_u16(object + 14u, second);
        while (child != 0u)
        {
            w_u16(child + 12u, first);
            child = r_u32(child + 52u);
        }
    }
    (void)sub_8001DC1C(object);
    (void)load_build_collision_model(object);
    return object;
}

static uint32 load_nearest_vehicle(uint32 position)
{
    uint32 current = r_u32(0x80065A50u), next = r_u32(current), object;
    uint32 best = 0xFFFFFFFFu, distance, result = 0u, index;
    sint32 delta[3];
    while (next != 0u)
    {
        object = r_u32(current + 8u);
        if ((uint32)(r_u16(object + 6u) - 1u) < 31u)
        {
            for (index = 0u; index < 3u; ++index)
                delta[index] = (sint32)(r_u32(position + index * 4u) - r_u32(object + 72u + index * 4u));
            distance = load_length(delta);
            if (distance < best)
            {
                best = distance;
                result = object;
            }
        }
        current = next;
        next = r_u32(current);
    }
    return result;
}

static uint32 load_vehicle_type(uint32 source, sint32 kind)
{
    uint32 object, value;
    w_u32(source + 100u, r_u32(0x8005EC34u + (uint32)kind * 4u));
    value = r_u32(0x800737A0u + (uint32)kind * 4u);
    w_u16(source + 10u, 0u);
    w_u32(source + 88u, value);
    object = v8_native_clone_vehicle(source);
    if ((sint16)r_u16(source + 6u) > 0)
    {
        value = (uint32)(sint32)(sint16)r_u16(object + 20u) * 4577u;
        w_u32(object + 128u, (uint32)((sint32)value / 32));
        w_u32(object + 132u, 0u);
        value = (uint32)(sint32)(sint16)r_u16(object + 32u) * 4577u;
        w_u32(object + 136u, (uint32)((sint32)value / 32));
    }
    return object;
}

uint32 v8_native_load_spawn_record(uint32 record)
{
    uint32 source, object;
    sint32 identifier = (sint16)r_u16(record + 2u), kind;
    if (identifier != 0)
        source = v8_native_find_object(0x80065A50u, identifier);
    else
        source = load_nearest_vehicle(r_u32(0x80065AD4u) + 36u);
    if (source == 0u)
        return 0u;
    w_u16(source + 12u, r_u16(record + 4u));
    kind = (sint8)r_u8(record);
    if (kind < 0)
        kind = (sint8)r_u8(0x80065674u + ~(uint32)kind);
    object = load_vehicle_type(source, kind);
    w_u32(object, r_u32(object) | ((uint32)r_u8(record + 1u) << 24u));
    return object;
}

uint32 v8_native_load_spawn_player(sint32 identifier)
{
    uint32 source = v8_native_find_object(0x80065A50u, identifier);
    uint32 index;
    if (source == 0u)
        return 0u;
    index = identifier < 0 ? ~(uint32)identifier : (uint32)identifier + 1u;
    return load_vehicle_type(source, (sint8)r_u8(0x80065674u + index));
}

uint32 sub_8001B038(uint32 object, uint32 kind);
uint32 sub_8001B2FC(uint32 parent, uint32 descriptor, uint32 child);
uint32 sub_80015368(uint32 text);

uint32 sub_8003D1E8(uint32 kind)
{
    return kind < 13u ? r_u32(0x8005ECB0u + kind * 4u) : 0u;
}

uint32 sub_8003D188(uint32 object, uint32 weapon)
{
    uint32 callback = r_u32(weapon + 100u);
    uint32 descriptor = callback != 0u ? v8_native_terrain_call3(callback, weapon, 14u, 0u) : 0u;
    return descriptor != 0u ? sub_8001B038(object, descriptor & 65535u) : 0u;
}

uint32 sub_8002CCE8(uint32 object, uint32 mask)
{
    uint32 index, table, child, callback, descriptor, slot, value;
    FUNCTION_MARKER(0x8002CCE8u, "SLUS_005.10");
    for (index = 0u; index < 7u; ++index)
    {
        if (((mask >> index) & 1u) == 0u)
            continue;
        table = 0x80010534u + index * 8u;
        if (index >= 6u)
        {
            descriptor = sub_8001B038(object, 0x801Fu);
            child = sub_8001AC44(r_u32(object + 88u), r_u16(descriptor + 26u), 128u, 8u);
            callback = sub_8003D1E8(r_u8(object + 208u));
        }
        else
        {
            child = sub_8001AC44(r_u32(0x800737DCu), r_u16(table), 128u, 8u);
            callback = r_u32(table + 4u);
        }
        w_u32(child + 100u, callback);
        w_u16(child + 6u, 0u);
        if (callback != 0u)
            (void)v8_native_terrain_call3(callback, child, 1u, 0u);
        descriptor = sub_8003D188(object, child);
        if (descriptor == 0u)
        {
            (void)sub_80015368(0x80010564u);
            continue;
        }
        (void)sub_8001B2FC(object, descriptor, child);
        slot = 8u;
        if (index != 0u)
        {
            slot = 0u;
            if (r_u32(object + 272u) != 0u)
            {
                while (slot < 4u)
                {
                    value = r_u32(object + 276u + slot * 4u);
                    ++slot;
                    if (value == 0u) break;
                }
            }
            slot += 9u;
        }
        w_u32(object + 236u + slot * 4u, child);
    }
    return 0u;
}

static void load_prepare_road_segment(uint32 record);
static void load_finalize_road_packets(uint32 terrain);

static void load_finalize_terrain(void)
{
    uint32 group = 0u, object, index, record, terrain;
    while ((sint32)group < (sint32)r_u32(0x80065BC4u))
    {
        object = r_u32(r_u32(0x80065BD8u) + group * 4u);
        index = 0u;
        while ((sint32)index < (sint32)(sint16)r_u16(object + 18u))
        {
            record = r_u32(object + 28u + index * 4u);
            if (r_u32(record) == object)
            {
                terrain = r_u32(0x80065BD4u) + r_u16(record + 10u) * 52u;
                if (r_u16(terrain) != 0u)
                {
                    load_prepare_road_segment(record);
                }
            }
            ++index;
        }
        ++group;
    }
    index = 0u;
    while ((sint32)index < (sint32)r_u32(0x80065BC0u))
    {
        terrain = r_u32(0x80065BD4u) + index * 52u;
        if (r_u16(terrain) != 0u)
        {
            load_finalize_road_packets(terrain);
        }
        ++index;
    }
}

static void load_release_object(uint32 object)
{
    uint32 model = r_u32(object + 104u);
    if (model != 0u)
        (void)sub_8001BDDC(model, 0u);
    if ((r_u32(object) & 8u) != 0u)
        sub_8003E2C4(r_u32(object + 112u));
    sub_800204DC(object);
}

static uint32 load_release_list(uint32 list)
{
    uint32 node, previous, next, tail;
    while (r_u32(list + 8u) != list)
    {
        node = r_u32(list);
        load_release_object(r_u32(node + 8u));
        previous = r_u32(node + 4u);
        next = r_u32(node);
        w_u32(next + 4u, previous);
        w_u32(previous, next);
        tail = r_u32(0x80065A78u);
        w_u32(0x80065A78u, node);
        w_u32(tail, node);
        w_u32(node + 4u, tail);
        w_u32(node, 0x80065A74u);
        w_u32(node + 8u, 0u);
    }
    return r_u32(list + 8u);
}

static uint32 load_sign_bits(uint32 value)
{
    uint32 count = 0u, bits = (value & 0x80000000u) != 0u ? ~value : value;
    while (count < 32u && (bits & 0x80000000u) == 0u)
    {
        bits <<= 1u;
        ++count;
    }
    return count;
}

static sint32 load_divide(sint32 numerator, sint32 denominator)
{
    if (denominator == 0)
        return numerator < 0 ? 1 : -1;
    if ((uint32)numerator == 0x80000000u && denominator == -1)
        return numerator;
    return numerator / denominator;
}

static uint32 load_length(const sint32 *vector)
{
    uint64 pair = 0u;
    uint32 index, low, high, scale, shift, shifted, normalized;
    for (index = 0u; index < 3u; ++index)
        pair += (uint64)((sint64)vector[index] * vector[index]);
    low = (uint32)pair;
    high = (uint32)(pair >> 32u);
    scale = (uint32)((sint32)(35u - load_sign_bits(high)) >> 1);
    shift = scale << 1u;
    shifted = shift << 26u;
    if ((sint32)shifted < 0)
        normalized = (uint32)((sint32)high >> (shift & 31u));
    else
    {
        normalized = low >> (shift & 31u);
        if (shifted != 0u)
            normalized |= high << ((0u - shift) & 31u);
    }
    return (uint32)SquareRoot0((sint32)normalized) << (scale & 31u);
}

static uint32 load_road_lerp(uint32 first, uint32 second, uint32 fraction)
{
    sint64 value = (sint64)(sint32)first * (65536u - fraction) +
                  (sint64)(sint32)second * fraction;
    return (uint32)(value / 65536);
}

static void load_adjust_road_points(uint32 *points, uint32 endpoint, sint32 displacement)
{
    uint32 left[12], right[12], middle[3], lower = 0u, upper = 65536u;
    uint32 fraction = 32768u, axis, origin;
    uint64 distance, threshold = (uint64)((sint64)displacement * displacement);
    sint32 dx, dz;
    do
    {
        memcpy(left, points, 3u * sizeof(uint32));
        memcpy(right + 9u, points + 9u, 3u * sizeof(uint32));
        for (axis = 0u; axis < 3u; ++axis)
        {
            middle[axis] = axis == 1u ? 0u : load_road_lerp(points[3u + axis], points[6u + axis], fraction);
            left[3u + axis] = axis == 1u ? 0u : load_road_lerp(points[axis], points[3u + axis], fraction);
            left[6u + axis] = axis == 1u ? 0u : load_road_lerp(left[3u + axis], middle[axis], fraction);
            right[6u + axis] = axis == 1u ? 0u : load_road_lerp(points[6u + axis], points[9u + axis], fraction);
            right[3u + axis] = axis == 1u ? 0u : load_road_lerp(middle[axis], right[6u + axis], fraction);
            left[9u + axis] = axis == 1u ? load_road_lerp(points[1u], points[10u], fraction) :
                                                   load_road_lerp(left[6u + axis], right[3u + axis], fraction);
            right[axis] = left[9u + axis];
        }
        origin = endpoint == 0u ? 0u : 9u;
        dx = (sint32)(left[9u] - points[origin]);
        dz = (sint32)(left[11u] - points[origin + 2u]);
        distance = (uint64)((sint64)dx * dx) + (uint64)((sint64)dz * dz);
        if (endpoint != 0u ? (sint64)distance <= (sint64)threshold : (sint64)distance > (sint64)threshold)
            upper = fraction;
        else
            lower = fraction;
        fraction = (lower + upper) / 2u;
    } while ((sint32)(upper - lower) >= 2);
    memcpy(points, endpoint != 0u ? left : right, 12u * sizeof(uint32));
}

static void load_finalize_road_packets(uint32 terrain)
{
    uint32 first, second, stride, primary_count, split_count, index, part, packet, next;
    uint32 x0, x1, xm, y0, y1, ym, flags, width, height;
    first = (uint32)((sint32)r_u32(terrain + 40u) >> 8u);
    second = (uint32)((sint32)r_u32(terrain + 36u) >> 8u);
    w_u16(terrain + 48u, (uint16)((uint32)SquareRoot0((sint32)(first * first + second * second)) - 128u));
    w_u32(terrain + 32u, 0u);
    flags = r_u16(terrain + 44u);
    w_u32(terrain + 24u, 0u);
    stride = (flags & 2u) != 0u ? 52u : 40u;
    primary_count = r_u32(terrain + 20u);
    first = sub_800116F4(primary_count * stride);
    w_u32(terrain + 12u, first);
    split_count = r_u32(terrain + 28u);
    second = sub_800116F4(split_count * stride * 4u);
    w_u32(terrain + 16u, second);
    width = r_u16(terrain + 2u);
    height = r_u16(terrain + 4u);
    x0 = r_u16(terrain + 6u) & 255u;
    x1 = (x0 + width - 1u) & 255u;
    y0 = ((r_u16(terrain + 6u) >> 8u) + height - 1u) & 255u;
    y1 = r_u16(terrain + 6u) >> 8u;
    xm = (x0 + x1) / 2u;
    ym = (y0 + y1) / 2u;
    /* The renderer writes dynamic fields before submitting packets */
    for (index = 0u; (sint32)index < (sint32)primary_count; ++index)
    {
        packet = first + index * stride;
        w_u8(packet + 3u, stride == 52u ? 12u : 9u);
        w_u8(packet + 7u, (stride == 52u ? 0x3Cu : 0x2Cu) | ((flags & 256u) != 0u ? 2u : 0u));
        w_u16(packet + 14u, r_u16(terrain + 10u));
        w_u16(packet + (stride == 52u ? 26u : 22u), r_u16(terrain + 8u));
        w_u16(packet + 12u, (uint16)(x0 | (y0 << 8u)));
        w_u16(packet + (stride == 52u ? 24u : 20u), (uint16)(x1 | (y0 << 8u)));
        w_u16(packet + (stride == 52u ? 36u : 28u), (uint16)(x0 | (y1 << 8u)));
        w_u16(packet + (stride == 52u ? 48u : 36u), (uint16)(x1 | (y1 << 8u)));
    }
    for (index = 0u; (sint32)index < (sint32)split_count; ++index)
    {
        for (part = 0u; part < 4u; ++part)
        {
            packet = second + (index * 4u + part) * stride;
            w_u8(packet + 3u, stride == 52u ? 12u : 9u);
            w_u8(packet + 7u, (stride == 52u ? 0x3Cu : 0x2Cu) | ((flags & 256u) != 0u ? 2u : 0u));
            w_u16(packet + 14u, r_u16(terrain + 10u));
            w_u16(packet + (stride == 52u ? 26u : 22u), r_u16(terrain + 8u));
            w_u16(packet + 12u, (uint16)(((part & 1u) != 0u ? xm : x0) | (((part & 2u) != 0u ? ym : y0) << 8u)));
            w_u16(packet + (stride == 52u ? 24u : 20u), (uint16)(((part & 1u) != 0u ? x1 : xm) | (((part & 2u) != 0u ? ym : y0) << 8u)));
            w_u16(packet + (stride == 52u ? 36u : 28u), (uint16)(((part & 1u) != 0u ? xm : x0) | (((part & 2u) != 0u ? y1 : ym) << 8u)));
            w_u16(packet + (stride == 52u ? 48u : 36u), (uint16)(((part & 1u) != 0u ? x1 : xm) | (((part & 2u) != 0u ? y1 : ym) << 8u)));
            if (part < 3u)
            {
                next = packet + stride;
                w_u32(packet, (r_u32(packet) & 0xFF000000u) | (next & 0xFFFFFFu));
            }
        }
    }
}

static uint32 load_road_extent(const uint32 *points)
{
    sint32 min_x = (sint32)points[0], max_x = min_x;
    sint32 min_z = (sint32)points[2], max_z = min_z;
    uint32 index, x, z;
    for (index = 1u; index < 3u; ++index)
    {
        if ((sint32)points[index * 3u] < min_x) min_x = (sint32)points[index * 3u];
        if ((sint32)points[index * 3u] > max_x) max_x = (sint32)points[index * 3u];
        if ((sint32)points[index * 3u + 2u] < min_z) min_z = (sint32)points[index * 3u + 2u];
        if ((sint32)points[index * 3u + 2u] > max_z) max_z = (sint32)points[index * 3u + 2u];
    }
    x = (uint32)max_x - (uint32)min_x;
    z = (uint32)max_z - (uint32)min_z;
    return (sint32)z < (sint32)x ? x : z;
}

static uint32 load_road_half(uint32 first, uint32 second)
{
    uint32 sum = first + second;
    sum += sum >> 31u;
    return (uint32)((sint32)sum >> 1u);
}

static uint32 load_allocate_road_mesh(uint32 count)
{
    uint32 mesh = sub_800116F4(count * 16u + 48u);
    w_u32(mesh + 28u, count);
    return mesh;
}

static uint32 load_road_truncate(uint32 value, uint32 shift)
{
    if ((sint32)value < 0) value += (1u << shift) - 1u;
    return (uint32)((sint32)value >> shift);
}

static uint32 load_road_vertex_squared(uint32 vertex)
{
    uint32 axis;
    for (axis = 0u; axis < 3u; ++axis)
        xport_gte_write_data(9u + axis, r_u16(vertex + axis * 2u));
    xport_gte_execute(0x00A00428u);
    return xport_gte_read_data(25u) + xport_gte_read_data(26u) + xport_gte_read_data(27u);
}

static uint32 load_road_radius_seed(uint32 mesh)
{
    /* User-authorized initialization of the undefined original radius seed */
    return 0u;
}

static uint32 load_construct_road_mesh(const uint32 *points, uint32 terrain, uint32 flags)
{
    uint32 coefficient[2][3], axis, offset, parameter = 0u, count = 0u;
    uint32 square, derivative[2], length, mesh, x, z, cube, center[2], edge[2][2];
    uint32 sample, side, address, coordinate[2], tile, color;
    SVECTOR normal;
    sint64 height;
    sint32 lighting;
    uint32 radius, squared;
    for (axis = 0u; axis < 2u; ++axis)
    {
        offset = axis * 2u;
        coefficient[axis][0] = load_road_truncate(3u * points[offset + 3u] - points[offset] -
                                                 3u * points[offset + 6u] + points[offset + 9u], 4u);
        coefficient[axis][1] = load_road_truncate(3u * points[offset] - 6u * points[offset + 3u] +
                                                 3u * points[offset + 6u], 4u);
        coefficient[axis][2] = load_road_truncate(3u * points[offset + 3u] - 3u * points[offset], 4u);
    }
    if ((flags & 1u) != 0u)
    {
        sub_80025800((sint32)points[0], (sint32)points[1], &normal.vx);
        VectorNormalSS(&normal, &normal);
    }
    do
    {
        square = load_road_truncate(parameter * parameter, 12u);
        for (axis = 0u; axis < 2u; ++axis)
        {
            derivative[axis] = load_road_truncate(3u * coefficient[axis][0] * square +
                                                 2u * coefficient[axis][1] * parameter, 12u);
            derivative[axis] = load_road_truncate(derivative[axis] + coefficient[axis][2], 8u);
        }
        length = (uint32)SquareRoot0((sint32)(derivative[0] * derivative[0] + derivative[1] * derivative[1]));
        parameter += (uint32)load_divide((sint32)r_u32(terrain + 40u), (sint32)length);
        ++count;
    } while ((sint32)parameter < 4096);
    w_u32(terrain + 20u, r_u32(terrain + 20u) + count * 2u);
    mesh = load_allocate_road_mesh(count);
    x = load_road_half(points[0], points[9]);
    w_u32(mesh + 12u, x);
    z = load_road_half(points[2], points[11]);
    w_u32(mesh + 20u, z);
    w_u32(mesh + 16u, sub_80025400(x, z));
    w_u32(mesh + 8u, terrain);
    parameter = 0u;
    for (sample = 0u; (sint32)sample <= (sint32)count; ++sample)
    {
        square = load_road_truncate(parameter * parameter, 12u);
        cube = load_road_truncate(square * parameter, 12u);
        for (axis = 0u; axis < 2u; ++axis)
        {
            center[axis] = load_road_truncate(coefficient[axis][0] * cube +
                                             coefficient[axis][1] * square + coefficient[axis][2] * parameter, 8u)
                           + points[axis * 2u];
            derivative[axis] = load_road_truncate(3u * coefficient[axis][0] * square +
                                                 2u * coefficient[axis][1] * parameter, 12u);
            derivative[axis] = load_road_truncate(derivative[axis] + coefficient[axis][2], 8u);
        }
        length = (uint32)SquareRoot0((sint32)(derivative[0] * derivative[0] + derivative[1] * derivative[1]));
        for (axis = 0u; axis < 2u; ++axis)
        {
            uint32 width = load_road_half(derivative[1u - axis] * r_u32(terrain + 36u), 0u);
            width = (uint32)load_divide((sint32)width, (sint32)length);
            edge[0][axis] = axis == 0u ? center[axis] - width : center[axis] + width;
            edge[1][axis] = axis == 0u ? center[axis] + width : center[axis] - width;
        }
        for (side = 0u; side < 2u; ++side)
        {
            address = mesh + 32u + sample * 16u + side * 8u;
            w_u16(address, (uint16)((sint32)(edge[side][0] - r_u32(mesh + 12u)) >> 8u));
            if ((flags & 1u) != 0u)
            {
                height = ((sint64)(sint32)points[1] * (4096u - parameter) +
                          (sint64)(sint32)points[10] * parameter) / 4096;
                w_u16(address + 2u, (uint16)((sint32)((uint32)height - r_u32(mesh + 16u)) >> 8u));
            }
            else
                w_u16(address + 2u, (uint16)((sint32)(sub_80025400(edge[side][0], edge[side][1]) - r_u32(mesh + 16u)) >> 8u));
            w_u16(address + 4u, (uint16)((sint32)(edge[side][1] - r_u32(mesh + 20u)) >> 8u));
            if ((flags & 1u) != 0u)
            {
                lighting = (sint32)((uint32)((sint32)normal.vx * (sint16)r_u16(0x80065AB0u)) +
                                   (uint32)((sint32)normal.vy * (sint16)r_u16(0x80065AB2u)) +
                                   (uint32)((sint32)normal.vz * (sint16)r_u16(0x80065AB4u)));
                if (lighting < 0) lighting = 0;
                color = (uint32)(lighting >> 17u) + 32u;
                if (color > 128u) color = 128u;
            }
            else
            {
                for (axis = 0u; axis < 2u; ++axis)
                    coordinate[axis] = load_road_truncate(edge[side][axis], 16u);
                tile = r_u32(0x800911A0u + (coordinate[1] >> 6u) * 4u + (coordinate[0] >> 6u) * 128u);
                color = (r_u16(tile + (coordinate[1] & 63u) * 2u + (coordinate[0] & 63u) * 128u) >> 11u) << 2u;
            }
            w_u16(address + 6u, (uint16)color);
        }
        squared = load_road_vertex_squared(mesh + 32u + sample * 16u);
        if (sample == 0u)
            radius = load_road_radius_seed(mesh);
        if ((sint32)squared < (sint32)radius)
            squared = radius;
        radius = load_road_vertex_squared(mesh + 40u + sample * 16u);
        if ((sint32)radius < (sint32)squared)
            radius = squared;
        if (sample == count - 1u)
            parameter = 4096u;
        else
            parameter += (uint32)load_divide((sint32)r_u32(terrain + 40u), (sint32)length);
    }
    w_u32(mesh + 24u, (uint32)SquareRoot0((sint32)radius) << 8u);
    return mesh;
}

static void load_emit_road_geometry(const uint32 *points, uint32 terrain, uint32 flags)
{
    uint32 left[12], right[12], middle[3], axis;
    if ((sint32)load_road_extent(points) <= 0xFFFFF)
    {
        uint32 mesh = load_construct_road_mesh(points, terrain, flags);
        uint32 tail = r_u32(0x80065BD0u);
        w_u32(0x80065BD0u, mesh);
        w_u32(tail, mesh);
        w_u32(mesh + 4u, tail);
        w_u32(mesh, 0x80065BCCu);
        return;
    }
    memcpy(left, points, 3u * sizeof(uint32));
    memcpy(right + 9u, points + 9u, 3u * sizeof(uint32));
    for (axis = 0u; axis < 3u; ++axis)
    {
        middle[axis] = axis == 1u ? 0u : load_road_half(points[3u + axis], points[6u + axis]);
        left[3u + axis] = axis == 1u ? 0u : load_road_half(points[axis], points[3u + axis]);
        left[6u + axis] = axis == 1u ? 0u : load_road_half(left[3u + axis], middle[axis]);
        right[6u + axis] = axis == 1u ? 0u : load_road_half(points[6u + axis], points[9u + axis]);
        right[3u + axis] = axis == 1u ? 0u : load_road_half(right[6u + axis], middle[axis]);
        left[9u + axis] = axis == 1u ? load_road_half(points[1u], points[10u]) :
                                               load_road_half(left[6u + axis], right[3u + axis]);
        right[axis] = left[9u + axis];
    }
    load_emit_road_geometry(left, terrain, flags);
    load_emit_road_geometry(right, terrain, flags);
}

static void load_prepare_road_segment(uint32 record)
{
    uint32 points[12], endpoint, junction, model, entry, link, angle, index;
    uint32 direction[3], candidate[3], best[3], product, maximum, adjacent;
    sint32 sine, cosine, score, displacement;
    uint64 dot;
    for (endpoint = 0u; endpoint < 2u; ++endpoint)
    {
        junction = r_u32(record + endpoint * 4u);
        index = endpoint == 0u ? 0u : 9u;
        points[index] = r_u32(junction);
        points[index + 1u] = r_u32(junction + 4u);
        points[index + 2u] = r_u32(junction + 8u);
        index = endpoint == 0u ? 3u : 6u;
        points[index] = r_u32(junction) + r_u32(record + 16u + endpoint * 8u);
        points[index + 1u] = 0u;
        points[index + 2u] = r_u32(junction + 8u) + r_u32(record + 20u + endpoint * 8u);
    }
    for (endpoint = 0u; endpoint < 2u; ++endpoint)
    {
        junction = r_u32(record + endpoint * 4u);
        if (r_u32(junction + 24u) != 0u)
        {
            model = r_u32(r_u32(junction + 12u));
            best[0] = r_u32(record + 16u + endpoint * 8u);
            best[1] = 0u;
            best[2] = r_u32(record + 20u + endpoint * 8u);
            memcpy(direction, best, sizeof(direction));
            link = r_u16(model + (uint32)(sint32)(sint16)r_u16(junction + 20u) * 28u + 54u);
            angle = (r_u16(junction + 22u) & 4095u) * 4u + 0x800607B4u;
            sine = (sint16)r_u16(angle);
            cosine = (sint16)r_u16(angle + 2u);
            maximum = 0u;
            while (link != 65535u)
            {
                entry = model + link * 28u;
                product = (uint32)cosine * r_u32(entry + 32u) + (uint32)sine * r_u32(entry + 40u);
                if ((sint32)product < 0) product += 4095u;
                candidate[0] = (uint32)((sint32)product >> 12u);
                candidate[1] = 0u;
                product = (0u - (uint32)sine) * r_u32(entry + 32u) + (uint32)cosine * r_u32(entry + 40u);
                if ((sint32)product < 0) product += 4095u;
                candidate[2] = (uint32)((sint32)product >> 12u);
                dot = 0u;
                for (index = 0u; index < 3u; ++index)
                    dot += (uint64)((sint64)(sint32)candidate[index] * (sint32)direction[index]);
                product = load_length((const sint32 *)candidate);
                if ((sint32)product < 0) product += 4095u;
                product = (uint32)((sint32)product >> 12u) * load_length((const sint32 *)direction);
                if (product == 0u)
                {
                    /* TODO Preserve the original division exception route */
                    fprintf(stderr, "TODO Load4550 signed64 division by zero\n");
                    abort();
                }
                score = (sint32)((sint64)dot / (sint32)product);
                if ((sint32)maximum < score)
                {
                    maximum = (uint32)score;
                    memcpy(best, candidate, sizeof(best));
                }
                link = r_u16(entry + 52u);
            }
            index = endpoint * 9u;
            points[index] = r_u32(junction) + best[0];
            points[index + 2u] = r_u32(junction + 8u) + best[2];
            points[index + 1u] = sub_80025400(points[index], points[index + 2u]);
        }
        else if ((r_u16(junction + 16u) & 1u) == 0u &&
                 (r_u16(record + 12u) & (2u << endpoint)) == 0u)
        {
            displacement = 0;
            for (index = 0u; (sint32)index < (sint32)(sint16)r_u16(junction + 18u); ++index)
            {
                adjacent = r_u32(junction + 28u + index * 4u);
                if (r_u16(adjacent + 8u) < r_u16(record + 8u))
                {
                    product = r_u32(r_u32(0x80065BD4u) + r_u16(adjacent + 10u) * 52u + 36u);
                    product += product >> 31u;
                    score = (sint32)product >> 1u;
                    if (score > displacement) displacement = score;
                }
            }
            if (displacement != 0)
            {
                load_adjust_road_points(points, endpoint, displacement);
            }
        }
    }
    load_emit_road_geometry(points, r_u32(0x80065BD4u) + r_u16(record + 10u) * 52u,
                           r_u16(record + 12u));
}

static void load_transform_position(uint32 position, sint32 *output)
{
    uint32 words[3], high[3], index;
    for (index = 0u; index < 3u; ++index)
        words[index] = r_u32(position + index * 4u);
    for (index = 0u; index < 3u; ++index)
        xport_gte_write_data(9u + index, (uint32)((sint32)words[index] >> 15));
    xport_gte_execute(0x0041E012u);
    for (index = 0u; index < 3u; ++index)
        high[index] = xport_gte_read_data(25u + index) << 3u;
    for (index = 0u; index < 3u; ++index)
        xport_gte_write_data(9u + index, words[index] & 32767u);
    xport_gte_execute(0x00498012u);
    for (index = 0u; index < 3u; ++index)
        output[index] = (sint32)(xport_gte_read_data(25u + index) + high[index]);
}

void v8_native_load_choose_target(uint32 player, uint32 force)
{
    uint32 matrix = 0x8006F680u, current, next, candidate, index, nearest = 0u;
    uint32 selected = 0u, best = 0xFFFFFFFFu, distance, part, callback;
    sint32 position[3], delta[3], horizontal, vertical, depth, best_horizontal = 0, best_depth = 0;
    if (r_u32(0x80065314u) != 0u && (sint16)r_u16(player + 6u) == -1)
        matrix = 0x8006F6A0u;
    for (index = 0u; index < 8u; ++index)
        xport_gte_write_control(index, r_u32(matrix + index * 4u));
    current = r_u32(0x80065A18u);
    next = r_u32(current);
    while (next != 0u)
    {
        candidate = r_u32(current + 8u);
        if (candidate != player && r_u8(candidate + 4u) != 3u && (r_u32(candidate) & 0x4000u) != 0u &&
            ((sint16)r_u16(candidate + 6u) > 0 || (sint8)r_u8(0x80065319u) == 3))
        {
            load_transform_position(candidate + 72u, position);
            vertical = position[1] >> 10;
            if (vertical < 0)
                vertical = (sint32)(0u - (uint32)vertical);
            horizontal = position[0] >> 10;
            if (horizontal < 0)
                horizontal = (sint32)(0u - (uint32)horizontal);
            if (vertical < horizontal)
                vertical = horizontal;
            depth = position[2] >> 10;
            if (vertical < depth && (selected == 0u ||
                (sint32)((uint32)best_depth * (uint32)vertical) < (sint32)((uint32)depth * (uint32)best_horizontal)))
            {
                selected = candidate;
                best_horizontal = vertical;
                best_depth = depth;
            }
            else if (selected == 0u)
            {
                for (index = 0u; index < 3u; ++index)
                    delta[index] = (sint32)(r_u32(player + 36u + index * 4u) - r_u32(candidate + 72u + index * 4u));
                distance = load_length(delta);
                if (distance < best)
                {
                    best = distance;
                    nearest = candidate;
                }
            }
        }
        current = next;
        next = r_u32(current);
    }
    if (selected == 0u)
        selected = nearest;
    if (selected != r_u32(player + 228u) && (selected != 0u || force != 0u))
    {
        w_u32(player + 228u, selected);
        index = r_u8(player + 179u);
        w_u16(player + 188u, 0u);
        part = r_u32(player + 236u + (index + 9u) * 4u);
        if (part != 0u)
        {
            callback = r_u32(part + 100u);
            if (callback != 0u)
                (void)v8_native_terrain_call3(callback, part, 10u, 0u);
        }
    }
}

static sint32 load_dot(const sint16 *first, const sint16 *second)
{
    uint32 value = 0u, index;
    for (index = 0u; index < 3u; ++index)
        value += (uint32)((sint32)first[index] * second[index]);
    return (sint32)value;
}

static uint32 load_light_weight(uint32 light, const sint32 *vertex, const sint16 *normal)
{
    sint16 axis[3], normalized[3];
    sint32 delta[3], facing, cosine, factor, angular;
    uint32 index, distance, length, shift, denominator, maximum, outer, inner, weight;
    for (index = 0u; index < 3u; ++index)
        axis[index] = (sint16)r_u16(light + 0x12u + index * 6u);
    facing = load_dot(normal, axis);
    if (facing >= 0)
        return 0u;
    outer = r_u16(0x800607B4u + (r_u16(light + 0x8Eu) & 4095u) * 4u + 2u);
    inner = r_u16(0x800607B4u + (r_u16(light + 0x8Cu) & 4095u) * 4u + 2u);
    for (index = 0u; index < 3u; ++index)
        delta[index] = (sint32)((uint32)vertex[index] - r_u32(light + 0x48u + index * 4u));
    distance = load_length(delta);
    length = load_length(delta);
    if (length == 0u)
        memset(normalized, 0, sizeof(normalized));
    else
    {
        shift = load_sign_bits(length) - 1u;
        if ((sint32)shift > 12)
            shift = 12u;
        denominator = (uint32)((sint32)length >> ((12u - shift) & 31u));
        for (index = 0u; index < 3u; ++index)
            normalized[index] = (sint16)load_divide((sint32)((uint32)delta[index] << (shift & 31u)), (sint32)denominator);
    }
    cosine = load_dot(normalized, axis) / 4096;
    maximum = r_u32(light + 0x88u);
    if (distance >= maximum || (sint32)outer >= cosine)
        return 0u;
    factor = (sint32)(0u - (uint32)facing) / 4096;
    denominator = (maximum - r_u32(light + 0x84u)) >> 12u;
    weight = denominator == 0u ? 0xFFFFFFFFu : (maximum - distance) / denominator;
    if ((sint32)weight > 4096)
        weight = 4096u;
    factor = (sint32)((uint32)factor * weight) / 4096;
    angular = load_divide((sint32)((outer - (uint32)cosine) << 12u), (sint32)(outer - inner));
    if (angular > 4096)
        angular = 4096;
    factor = (sint32)((uint32)factor * (uint32)angular) / 4096;
    factor = (sint32)((uint32)factor * r_u16(light + 0x90u)) / 4096;
    return (uint32)factor & 65535u;
}

void v8_native_load_color(uint32 base, uint32 destination, uint32 primitive, uint32 vertex, uint32 normal)
{
    sint32 transformed_vertex[3];
    sint16 transformed_normal[3];
    uint32 index, rgb, current, next, light, weight, totals[3];
    xport_gte_write_data(0u, r_u32(vertex));
    xport_gte_write_data(1u, r_u32(vertex + 4u));
    xport_gte_execute(0x00480012u);
    for (index = 0u; index < 3u; ++index)
        transformed_vertex[index] = (sint32)xport_gte_read_data(25u + index);
    xport_gte_write_data(0u, r_u32(normal));
    xport_gte_write_data(1u, r_u32(normal + 4u));
    xport_gte_execute(0x00486012u);
    for (index = 0u; index < 3u; ++index)
        transformed_normal[index] = (sint16)xport_gte_read_data(9u + index);
    xport_gte_write_data(0u, (uint16)transformed_normal[0] | ((uint32)(uint16)transformed_normal[1] << 16u));
    xport_gte_write_data(1u, (uint16)transformed_normal[2]);
    xport_gte_write_data(6u, r_u32(primitive));
    xport_gte_execute(0x0308041Bu);
    rgb = xport_gte_read_data(22u);
    for (index = 0u; index < 3u; ++index)
        totals[index] = (rgb >> (index * 8u)) & 255u;
    current = r_u32(base + 0x7D90u);
    next = r_u32(current);
    while (next != 0u)
    {
        light = r_u32(current + 8u);
        weight = load_light_weight(light, transformed_vertex, transformed_normal);
        if (weight != 0u)
            for (index = 0u; index < 3u; ++index)
                totals[index] += (uint32)((sint32)(weight * r_u8(light + 0x80u + index)) / 4096);
        current = next;
        next = r_u32(current);
    }
    for (index = 0u; index < 3u; ++index)
        w_u8(destination + index, (sint32)totals[index] < 255 ? totals[index] : 255u);
}

void v8_native_load_process_packets(uint32 base, uint32 model, V8LoadColorCallback callback)
{
    uint32 primitive = r_u32(model + 24u), packet = r_u32(model + 28u);
    uint32 index = 0u, old_primitive, kind, target, vertex, normal, destination, count;
    while ((sint32)index < (sint32)r_u32(model + 20u))
    {
        old_primitive = primitive;
        kind = ((r_u8(primitive + 3u) >> 2u) & 15u) - 4u;
        if (kind < 8u)
        {
            target = r_u32(base + 0x28u + kind * 4u) - base;
            if (target == 0x145Cu)
            {
                count = r_u16(primitive + 10u);
                primitive += count * 4u;
                packet += count * 40u;
            }
            else if (target == 0x13A4u || target == 0x13BCu || target == 0x13D4u ||
                     target == 0x13ECu || target == 0x1484u)
            {
                count = 1u;
                if (target == 0x13ECu)
                {
                    w_u8(packet + 23u, r_u8(packet + 7u));
                    w_u8(packet + 15u, r_u8(packet + 7u));
                    count = 3u;
                }
                else if (target == 0x1484u)
                {
                    w_u8(packet + 31u, r_u8(packet + 7u));
                    w_u8(packet + 19u, r_u8(packet + 7u));
                    count = 3u;
                }
                for (destination = 0u; destination < count; ++destination)
                {
                    vertex = r_u32(model + 8u) + r_u16(primitive + 4u + destination * 2u);
                    normal = r_u32(model + 16u) + r_u16(primitive + 10u + destination * 2u);
                    callback(base, packet + 4u + destination * (target == 0x1484u ? 12u : 8u), primitive, vertex, normal);
                }
            }
            else if (target != 0x1500u)
            {
                fprintf(stderr, "TODO modified Load131C packet dispatch %08X\n", target);
                abort();
            }
        }
        kind = r_u8(old_primitive + 3u) & 60u;
        packet += r_u16(0x800568FCu + kind + 2u);
        primitive += r_u16(0x800568FCu + kind);
        ++index;
    }
    destination = r_u32(model + 32u);
    if (destination != 0u)
    {
        vertex = r_u32(model + 28u);
        (void)sub_80044C44(destination, vertex, packet - vertex);
    }
}

void v8_native_load_prepare_objects(uint32 base, uint32 object, const MATRIX *parent, V8LoadColorCallback callback)
{
    MATRIX composed;
    uint32 model, flags, child;
    do
    {
        (void)CompMatrixLV((MATRIX *)parent, (MATRIX *)psx_addr(object + 16u, sizeof(MATRIX)), &composed);
        SetRotMatrix(&composed);
        SetTransMatrix(&composed);
        model = r_u32(object + 48u);
        if (model != 0u && (r_u16(model) & 1u) != 0u)
        {
            v8_native_load_process_packets(base, model, callback);
            model = r_u32(object + 48u);
            flags = r_u16(model);
            w_u16(model, (flags & 0xFFFEu) | 4u);
        }
        model = r_u32(object + 104u);
        if (model != 0u && (r_u16(model) & 1u) != 0u)
        {
            v8_native_load_process_packets(base, model, callback);
            model = r_u32(object + 104u);
            flags = r_u16(model);
            w_u16(model, (flags & 0xFFFEu) | 4u);
        }
        child = r_u32(object + 56u);
        if (child != 0u)
            v8_native_load_prepare_objects(base, child, &composed, callback);
        object = r_u32(object + 52u);
    } while (object != 0u);
}


void v8_native_load_insert_object(uint32 tree, uint32 node)
{
    uint32 kind = r_u32(tree), object, previous, threshold, coordinate;
    if (kind == 0u)
    {
        previous = r_u32(tree + 12u);
        w_u32(tree + 12u, node);
        w_u32(previous, node);
        w_u32(node + 4u, previous);
        w_u32(node, tree + 8u);
    }
    else if (kind == 1u || kind == 2u)
    {
        object = r_u32(node + 8u);
        coordinate = r_u32(object + (kind == 1u ? 72u : 80u));
        threshold = r_u32(tree + 4u);
        tree = r_u32(tree + ((sint32)threshold < (sint32)coordinate ? 12u : 8u));
        v8_native_load_insert_object(tree, node);
    }
}


static void load_set_light(uint32 light, const uint16 *vector, uint32 color)
{
    uint32 destination = 0x8006F720u + light * 6u;
    w_u16(destination, vector[0]);
    w_u16(destination + 2u, vector[1]);
    w_u16(destination + 4u, vector[2]);
    destination = 0x8006F760u + light * 2u;
    w_u16(destination, (color & 255u) << 4u);
    w_u16(destination + 6u, (color >> 4u) & 0xFF0u);
    w_u16(destination + 12u, (color >> 12u) & 0xFF0u);
}


static void load_tinf(uint32 base, uint32 source)
{
    uint32 group, corner, pointer, value, record, destination, x, y, flags;
    uint32 table, uv, page, context, bitmap, mode, index;
    for (group = 0u; group < 8u; ++group)
    {
        for (corner = 0u; corner < 4u; ++corner)
        {
            pointer = base + 0x6DBCu + group * 8u + corner * 2u;
            value = r_u8(pointer) != 0u ? r_u8(0x80065B30u) - 1u : 0u;
            w_u8(pointer, value);
            value = r_u8(pointer + 1u) != 0u ? r_u8(0x80065B30u) - 1u : 0u;
            w_u8(pointer + 1u, value);
        }
    }
    for (record = 0u; record < 256u; ++record, source += 40u)
    {
        destination = 0x8008F020u + record * 32u;
        x = (r_u8(source + 2u) << 8u) | r_u8(source + 3u);
        y = (r_u8(source + 4u) << 8u) | r_u8(source + 5u);
        flags = (r_u8(source + 6u) << 8u) | r_u8(source + 7u);
        table = base + 0x6DBCu + (flags & 7u) * 8u;
        for (corner = 0u; corner < 4u; ++corner)
        {
            uv = (r_u8(table + corner * 2u) + (x & 127u)) |
                 ((r_u8(table + corner * 2u + 1u) + y) << 8u);
            w_u16(destination + corner * 4u, r_u16(0x80065B4Eu) + uv);
        }
        page = 0u;
        if ((r_u16(source) & 0x1000u) == 0u)
        {
            context = r_u32(0x80065AFCu);
            bitmap = r_u32(context + 12u);
            mode = r_u32(context);
            value = (uint32)(sint32)(sint16)r_u16(bitmap) + ((x >> 7u) << ((mode & 3u) + 5u));
            page = GetTPage((sint32)mode, 0, (sint32)value, (sint16)r_u16(bitmap + 2u));
        }
        w_u16(destination + 14u, page);
        w_u16(destination + 10u, page);
        w_u16(destination + 6u, page);
        w_u16(destination + 2u, page);
        w_u16(destination + 30u, (flags >> 3u) & 1u);
        for (index = 0u; index < 7u; ++index)
            w_u16(destination + 16u + index * 2u,
                  (r_u8(source + 8u + index * 2u) << 8u) | r_u8(source + 9u + index * 2u));
    }
}


static void load_palette(uint32 source, sint32 count, uint16 *output, uint32 blend)
{
    sint32 index;
    uint32 color, rgb, channel, packed, shaded;
    for (index = 0; index < count; ++index)
    {
        color = r_u16(source + (uint32)index * 2u);
        if (color == 0u)
        {
            output[index] = 0u;
            continue;
        }
        rgb = 0u;
        for (channel = 0u; channel < 3u; ++channel)
            rgb |= ((((color >> (channel * 5u)) & 31u) * 255u) / 31u) << (channel * 8u);
        xport_gte_write_data(6u, rgb);
        xport_gte_write_data(8u, blend);
        xport_gte_execute(0x00780010u);
        shaded = xport_gte_read_data(22u);
        packed = color & 0x8000u;
        for (channel = 0u; channel < 3u; ++channel)
            packed |= (((((shaded >> (channel * 8u)) & 255u) * 31u) + 128u) / 255u) << (channel * 5u);
        output[index] = (uint16)packed;
    }
}

static void load_xbmp(uint32 image)
{
    uint32 palette, width, allocation, index;
    PSX_RECT rectangle;
    uint16 colors[256 * 17] = {0};
    v8_native_187E4(image, (uint8 *)psx_addr(0x80065B48u, 12u));
    palette = r_u32(0x8006F62Cu);
    width = (uint32)(sint32)(sint16)r_u16(palette + 4u);
    w_u32(0x80065AFCu, 0x8006F628u);
    allocation = sub_80018124(width, 17u, 16u, 1u, width, 1u);
    memcpy(&rectangle, psx_addr(allocation, sizeof(rectangle)), sizeof(rectangle));
    w_u16(0x80065B04u, GetClut(rectangle.x, rectangle.y));
    SetFarColor(r_u8(0x80065B2Cu), r_u8(0x80065B2Du), r_u8(0x80065B2Eu));
    for (index = 0u; index < 16u; ++index)
    {
        palette = r_u32(r_u32(0x80065AFCu) + 4u);
        width = (uint32)(sint32)(sint16)r_u16(palette + 4u);
        load_palette(r_u32(r_u32(0x80065AFCu) + 8u), (sint32)width, colors, index * index * 16u);
        (void)LoadImagePSX(&rectangle, (uint32 *)colors);
        rectangle.y = (sint16)((uint16)rectangle.y + 1u);
    }
    (void)LoadImagePSX(&rectangle, (uint32 *)colors);
}


static void load_cols(uint32 source)
{
    uint32 first[3], second[3], low, high, last, component;
    w_u32(0x80065B58u, r_u32(source));
    first[0] = r_u8(0x80065B58u);
    w_u32(0x80065B00u, r_u32(source + 4u));
    second[0] = r_u8(0x80065B00u);
    w_u32(0x80065B2Cu, r_u32(source + 8u));
    w_u32(0x80065B54u, r_u32(source + 12u));
    low = r_u8(0x80065B54u);
    w_u32(0x80065B08u, r_u32(source + 16u));
    w_u32(0x80065B10u, r_u32(source + 20u));
    last = r_u32(source + 24u);
    first[1] = r_u8(0x80065B59u); first[2] = r_u8(0x80065B5Au);
    second[1] = r_u8(0x80065B01u); second[2] = r_u8(0x80065B02u);
    high = r_u8(0x80065B08u);
    w_u8(0x80065B2Fu, 48u);
    for (component = 0u; component < 3u; ++component)
        w_u8(0x800910C4u + component, first[component]);
    for (component = 0u; component < 3u; ++component)
        w_u8(0x800910DCu + component, second[component]);
    for (component = 0u; component < 3u; ++component)
        w_u8(0x800910F4u + component, first[component]);
    for (component = 0u; component < 3u; ++component)
        w_u8(0x8009110Cu + component, second[component]);
    w_u32(0x80065AF8u, last);
    w_u16(0x8005E994u, (high - low) << 4u);
    high = r_u8(0x80065B09u); low = r_u8(0x80065B55u);
    first[0] = r_u8(0x80065B0Au); second[0] = r_u8(0x80065B56u);
    w_u16(0x8005E99Au, (high - low) << 4u);
    w_u16(0x8005E9A0u, (first[0] - second[0]) << 4u);
}


static sint32 load_fixed_multiply(sint32 left, uint32 right)
{
    uint32 product = (uint32)left * right;
    return (sint32)product / 4096;
}

static void load_suna(uint32 source, uint32 bytes)
{
    uint32 angle0, angle1, scale, table0, table1;
    sint32 cosine, value;
    angle0 = (r_u8(source) << 8u) | r_u8(source + 1u);
    angle1 = (r_u8(source + 2u) << 8u) | r_u8(source + 3u);
    scale = (sint32)bytes < 13 ? 4096u : (r_u8(source + 12u) << 8u) | r_u8(source + 13u);
    table0 = 0x800607B4u + (angle0 & 4095u) * 4u;
    table1 = 0x800607B4u + (angle1 & 4095u) * 4u;
    cosine = (sint16)r_u16(table0 + 2u);
    value = load_fixed_multiply((sint16)r_u16(table1), (uint32)cosine);
    w_u16(0x80065AB0u, (uint32)load_fixed_multiply(value, scale));
    value = -(sint32)(sint16)r_u16(table0);
    w_u16(0x80065AB2u, (uint32)load_fixed_multiply(value, scale));
    value = load_fixed_multiply((sint16)r_u16(table1 + 2u), (uint32)cosine);
    w_u16(0x80065AB4u, (uint32)load_fixed_multiply(value, scale));
}


static void load_text(uint32 source, uint32 bytes)
{
    char buffer[256];
    uint32 index, destination;
    if ((sint8)r_u8(0x80065319u) == 0)
        return;
    memcpy(buffer, psx_addr(source, bytes), bytes);
    buffer[bytes] = '\0';
    destination = 0x8006EEF0u;
    index = 0u;
    do
    {
        w_u8(destination + 8u + index, (uint8)buffer[index]);
    } while (buffer[index++] != '\0');
    w_u16(destination + 2u, 0u);
    w_u16(destination, 512u);
    w_u16(destination + 4u, 16u);
    w_u16(destination + 6u, 144u);
}


static void load_xobf(uint32 bytes)
{
    uint32 index = 18u, object;
    while (r_u32(0x800737A0u + index * 4u) != 0u)
        ++index;
    object = sub_8002263C(bytes, 1u);
    w_u32(0x800737A0u + index * 4u, object);
}

static uint32 load_read_be16(uint32 *cursor)
{
    uint32 high = r_u8((*cursor)++);
    return (high << 8u) | r_u8((*cursor)++);
}

static void load_head(uint32 cursor, uint32 bytes)
{
    uint32 mode, object_count, index_count, index, value;
    sint32 count;
    mode = load_read_be16(&cursor);
    object_count = load_read_be16(&cursor);
    index_count = load_read_be16(&cursor);
    (void)load_read_be16(&cursor);
    (void)load_read_be16(&cursor);
    count = (sint32)(bytes - 10u) / 2;
    for (index = 0u; (sint32)index < count; ++index)
        w_u16(0x800658E8u + index * 2u, load_read_be16(&cursor));
    value = (uint32)(sint32)(sint16)r_u16(0x800658EEu) << 1u;
    value = (uint32)((sint32)value >> (r_u8(0x8006531Au) & 31u));
    w_u16(0x800658EEu, value);
    (void)sub_800251FC(mode);
    w_u32(0x80065BC8u, 0x80065BCCu);
    w_u32(0x80065BCCu, 0u);
    w_u32(0x80065BD0u, 0x80065BC8u);
    w_u32(0x80065BC0u, object_count);
    w_u32(0x80065BD4u, sub_8001178C(object_count, 52u));
    w_u32(0x80065BC4u, index_count);
    w_u32(0x80065BD8u, sub_8001178C(index_count, 4u));
}

static uint32 load_wrap_text(uint32 object, uint32 input, uint8 *output, uint32 width)
{
    uint8 *last_space = NULL;
    uint32 resume = 0u, advance = 0u, lines = 1u, character, font, index;
    for (;;)
    {
        character = r_u8(input++);
        if (character == 0u)
        {
            *output = 0u;
            return lines;
        }
        if (character == 1u)
        {
            *output++ = 1u;
            for (index = 0u; index < 3u; ++index)
                *output++ = r_u8(input++);
            continue;
        }
        if (character == 10u)
        {
            advance = 0u;
            ++lines;
        }
        else
        {
            if (character == 32u)
            {
                last_space = output;
                resume = input;
            }
            font = r_u32(object);
            advance += r_u8(font + (character - r_u8(font + 5u)) * 5u + 11u);
            if ((sint32)width < (sint32)advance)
            {
                --input;
                if (last_space != NULL)
                {
                    output = last_space;
                    input = resume;
                }
                character = r_u8(input);
                advance = 0u;
                ++lines;
                while (character == 32u)
                    character = r_u8(++input);
                character = 10u;
            }
        }
        *output++ = (uint8)character;
    }
}

static void load_draw_text(uint32 object, const uint8 *text, uint32 x, uint32 y)
{
    uint32 start = x, character, packet[8];
    while ((character = *text++) != 0u)
    {
        if (character == 10u)
        {
            x = start;
            y += r_u8(r_u32(object) + 7u);
        }
        else if (character == 1u)
        {
            w_u8(object + 4u, *text++);
            w_u8(object + 5u, *text++);
            w_u8(object + 6u, *text++);
        }
        else
        {
            (void)DrawSync(0);
            x = v8_native_19370(object, (uint8 *)packet, character, x, y);
            (void)DrawPrim(packet);
        }
    }
}

static uint32 load_default_damage(uint32 object, uint32 damage)
{
    uint32 health;
    if ((r_u32(object) & 0x8000u) != 0u)
        return 0u;
    health = r_u16(object + 12u);
    if (health >= damage) {
        w_u16(object + 12u, health - damage);
        return 0u;
    }
    w_u16(object + 12u, r_u16(object + 14u));
    /* TODO Translate the complete model transition dependency */
    fprintf(stderr, "TODO native object damage sub_8003FC50 object=%08X\n", object);
    abort();
}

static uint32 load_default_object_callback(uint32 object, uint32 mode, uint32 value)
{
    uint32 result = 0u, other;
    if (mode == 3u) {
        other = r_u32(value);
        if (r_u8(other + 4u) == 7u)
            result = load_default_damage(object, r_u16(other + 12u)) != 0u;
    } else if (mode == 8u)
        result = load_default_damage(object, value);
    else if (mode == 1u) {
        result = sub_8003FC94(object);
        w_u32(0x800659F8u, r_u32(0x800659F8u) + r_u16(object + 12u) * result);
        return 0u;
    }
    if (result != 0u)
        w_u32(0x80065A0Cu, r_u32(0x80065A0Cu) + r_u16(object + 14u));
    return 0u;
}

static uint32 load_random_pickup(uint32 flags, uint32 incoming_v1)
{
    uint32 attempts = (uint32)(2 - (sint32)(sint8)r_u8(0x8006531Au));
    uint32 index = incoming_v1;
    if (attempts == 0xFFFFFFFFu)
        return index;
    for (;;) {
        index = (sub_80017160() * 12u) >> 15u;
        if ((sint16)r_u16(0x8005EC84u + index * 2u) < 0)
            continue;
        if ((flags & (1u << ((index + 19u) & 31u))) == 0u)
            continue;
        if (index == 11u)
            return index;
        --attempts;
        if ((flags & 0x40000000u) == 0u || attempts == 0xFFFFFFFFu)
            return index;
    }
}

uint32 sub_800202F4(uint32 object)
{
    FUNCTION_MARKER(0x800202F4u, "SLUS_005.10");
    if ((r_u32(object) & 4u) != 0u)
        (void)sub_8001FE50(0x80065A80u, object);
    if ((r_u32(object) & 0x80u) != 0u)
        (void)sub_8001FE50(0x80065A60u, object);
    return sub_8001FE50(0x80065A18u, object);
}

void sub_8003E730(uint32 object, uint32 incoming_s1)
{
    uint32 model;
    FUNCTION_MARKER(0x8003E730u, "SLUS_005.10");
    model = sub_8001BDA0(r_u32(0x800737D4u), 13u, incoming_s1);
    sub_8003E598(object, model);
}

uint32 sub_8002036C(uint32 object, uint32 incoming_s1)
{
    uint32 callback, result;
    FUNCTION_MARKER(0x8002036Cu, "SLUS_005.10");
    (void)sub_8001D708(object);
    (void)sub_8001DC1C(object);
    callback = r_u32(object + 100u);
    result = callback != 0u ? v8_native_terrain_call3(callback, object, 1u, 0u) : 0u;
    if ((sint32)result < 0)
        return 0u;
    if ((r_u32(object) & 8u) != 0u && r_u32(object + 112u) == 0u)
        sub_8003E730(object, incoming_s1);
    return sub_800202F4(object);
}

uint32 sub_8003CF90(uint32 mask, uint32 source, uint32 incoming_v1)
{
    uint32 index, flags, special = 0u, object;
    FUNCTION_MARKER(0x8003CF90u, "SLUS_005.10");
    if (source == 0u)
        return 0u;
    mask &= r_u32(source);
    if (mask == 0u)
        return 0u;
    index = load_random_pickup(mask, incoming_v1);
    if (index == 3u)
        w_u32(0x800659ECu, r_u32(0x800659ECu) + 1u);
    if ((sint32)index >= 5) {
        flags = r_u32(source);
        if ((flags & 0x40000000u) != 0u)
            special = (flags & 0x3F000000u) != 0u;
    }
    w_u8(source + 8u, (uint8)special);
    w_u16(source + 10u, special != 0u ? 13u : r_u16(0x8005EC84u + index * 2u));
    object = v8_native_clone_vehicle(source);
    w_u16(object + 10u, r_u16(0x8005EC84u + index * 2u));
    return object;
}

uint32 sub_8003D080(uint32 mask, uint32 source, uint32 incoming_v1)
{
    uint32 object;
    FUNCTION_MARKER(0x8003D080u, "SLUS_005.10");
    object = sub_8003CF90(mask, source, incoming_v1);
    if (object != 0u) {
        w_u32(source, r_u32(source) | 0x8000u);
        (void)sub_8002036C(object, source);
    }
    return object;
}

static void load_lift_station_insert(uint32 object)
{
    uint32 node = sub_80022C54(object);
    uint32 position = r_u32(r_u32(0x800659FCu) + 128u);
    uint32 next = r_u32(position), previous;
    while (next != 0u) {
        if ((sint32)r_u32(r_u32(position + 8u) + 80u) >= (sint32)r_u32(object + 80u))
            break;
        position = next;
        next = r_u32(position);
    }
    previous = r_u32(position + 4u);
    w_u32(previous, node);
    w_u32(position + 4u, node);
    w_u32(node, position);
    w_u32(node + 4u, previous);
}

static sint32 load_sound_divide(sint32 numerator, sint32 denominator)
{
    if (denominator == 0)
        return numerator < 0 ? 1 : -1;
    if ((uint32)numerator == 0x80000000u && denominator == -1)
        return numerator;
    return numerator / denominator;
}

static uint32 load_sound_length(const sint32 *vector)
{
    uint64 pair = 0u;
    uint32 high, low, scale, shift, shifted, normalized, i;
    for (i = 0u; i < 3u; ++i)
        pair += (uint64)((sint64)vector[i] * vector[i]);
    low = (uint32)pair;
    high = (uint32)(pair >> 32);
    xport_gte_write_data(30u, high);
    scale = (uint32)((sint32)(35u - xport_gte_read_data(31u)) >> 1);
    shift = scale << 1;
    shifted = shift << 26;
    if ((sint32)shifted < 0)
        normalized = (uint32)((sint32)high >> (shift & 31u));
    else {
        normalized = low >> (shift & 31u);
        if (shifted != 0u)
            normalized |= high << ((0u - shift) & 31u);
    }
    return (uint32)SquareRoot0((sint32)normalized) << (scale & 31u);
}

uint32 v8_native_vector_length_host(const sint32 *vector)
{
    return load_sound_length(vector);
}

uint32 sub_8003D988(uint32 object, uint32 x, uint32 y, uint32 z)
{
    sint32 dx = (sint32)(x - r_u32(object + 72u));
    sint32 dy = (sint32)(y - r_u32(object + 76u));
    sint32 dz = (sint32)(z - r_u32(object + 80u));
    uint32 first, second, shift, square, angle;
    FUNCTION_MARKER(0x8003D988u, "SLUS_005.10");
    w_u16(object + 66u, ratan2(dx, dz));
    xport_gte_write_data(30u, (uint32)dx);
    first = xport_gte_read_data(31u);
    xport_gte_write_data(30u, (uint32)dz);
    second = xport_gte_read_data(31u);
    if (first < second) second = first;
    if (second < 18u) {
        shift = (18u - second) & 31u;
        dx >>= shift; dy >>= shift; dz >>= shift;
    }
    square = (uint32)dx * (uint32)dx + (uint32)dz * (uint32)dz;
    angle = ratan2((sint32)(0u - (uint32)dy), SquareRoot0((sint32)square));
    w_u16(object + 64u, angle);
    return angle;
}

uint32 sub_8003D214(uint32 object, uint32 mode)
{
    uint32 flags, owner, i, range_word, old_range;
    sint32 offset[3], step, limit, range, half, height;
    sint64 ratio = 0;
    SVECTOR direction;
    FUNCTION_MARKER(0x8003D214u, "SLUS_005.10");
    if (mode != 0u) {
        if (mode == 2u) w_u32(object, r_u32(object) & 0xFFEBFFFFu);
        return 0u;
    }
    flags = r_u32(object);
    if ((flags & 0x100000u) != 0u) {
        /* TODO Translate camera scripted path 8003DFFC and 8003DFD8 */
        fprintf(stderr, "Missing camera scripted path 8003DFFC\n"); abort();
    }
    if ((flags & 0x40000u) != 0u) {
        for (i = 0u; i < 3u; ++i)
            w_u32(object + 72u + 4u * i, r_u32(object + 72u + 4u * i) +
                (uint32)(sint32)(sint16)r_u16(object + 132u + 2u * i));
    } else {
        old_range = r_u32(object + 152u);
        direction.vx = (sint16)r_u16(0x800607B4u + 4u * (r_u16(object + 142u) & 4095u));
        direction.vy = (sint16)(0u - r_u16(0x800607B4u + 4u * (r_u16(object + 140u) & 4095u)));
        direction.vz = (sint16)r_u16(0x800607B6u + 4u * (r_u16(object + 142u) & 4095u));
        direction.pad = 0;
        if ((flags & 0x20000u) != 0u) {
            range_word = r_u32(object + 148u) + 2288u;
            if ((sint32)range_word >= 1433600) range_word = 1433600u;
            w_u32(object + 148u, range_word);
            w_u16(object + 142u, r_u16(object + 142u) + 8u);
        } else ApplyMatrixSV((MATRIX *)psx_addr(r_u32(object + 128u) + 16u, sizeof(MATRIX)), &direction, &direction);
        owner = r_u32(object + 128u);
        for (i = 0u; i < 3u; ++i) {
            sint32 component = i == 0u ? direction.vx : i == 1u ? direction.vy : direction.vz;
            uint32 displacement = (uint32)(((sint64)component * (sint32)r_u32(object + 148u)) >> 12);
            offset[i] = (sint32)(r_u32(owner + 36u + 4u * i) - displacement - r_u32(object + 72u + 4u * i));
        }
        range = (sint32)load_sound_length(offset);
        half = (sint32)old_range / 2;
        if (half < 0) half = -half;
        if (range > half) ratio = ((sint64)(range - half) * 4096) / range;
        if (ratio >= 257 && (r_u32(object) & 0x80000u) == 0u) {
            for (i = 0u; i < 3u; ++i)
                w_u32(object + 72u + 4u * i, r_u32(object + 72u + 4u * i) +
                    (uint32)(((sint64)offset[i] * ratio) >> 12));
        } else {
            if (ratio < 257) w_u32(object, r_u32(object) & ~0x80000u);
            for (i = 0u; i < 3u; ++i) {
                step = offset[i] / (i == 1u ? 16 : 8);
                limit = (sint16)r_u16(object + 146u);
                if (step < -limit) step = -limit;
                else if (step > limit) step = limit;
                w_u32(object + 72u + 4u * i, r_u32(object + 72u + 4u * i) + (uint32)step);
            }
        }
    }
    owner = r_u32(object + 128u);
    if ((sint32)r_u32(owner + 76u) < (sint32)sub_80025400(r_u32(owner + 72u), r_u32(owner + 80u))) {
        height = (sint32)(sub_80025400(r_u32(object + 72u), r_u32(object + 80u)) - 0x8000u);
        if ((sint32)r_u32(object + 76u) < height) height = (sint32)r_u32(object + 76u);
        w_u32(object + 76u, (uint32)height);
    }
    owner = r_u32(object + 128u);
    (void)sub_8003D988(object, r_u32(owner + 36u), r_u32(owner + 40u), r_u32(owner + 44u));
    w_u16(object + 64u, r_u16(object + 64u) + r_u16(object + 144u));
    (void)sub_8001D708(object);
    return 0u;
}

static void load_transform_input(uint32 matrix, uint32 position, const sint32 *host_input, sint32 *output)
{
    uint32 input[3], high[3], i;
    for (i = 0u; i < 5u; ++i)
        xport_gte_write_control(i, r_u32(matrix + i * 4u));
    for (i = 0u; i < 3u; ++i) {
        input[i] = host_input != NULL ? (uint32)host_input[i] : r_u32(position + i * 4u);
        xport_gte_write_data(9u + i, (uint32)((sint32)input[i] >> 15));
    }
    xport_gte_execute(0x0041E012u);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_control(5u + i, r_u32(matrix + 20u + i * 4u));
    for (i = 0u; i < 3u; ++i)
        high[i] = xport_gte_read_data(25u + i);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_data(9u + i, input[i] & 0x7FFFu);
    xport_gte_execute(0x00498012u);
    for (i = 0u; i < 3u; ++i)
        output[i] = (sint32)(xport_gte_read_data(25u + i) + (high[i] << 3));
}

static void load_sound_transform(uint32 matrix, uint32 position, sint32 *output)
{
    load_transform_input(matrix, position, NULL, output);
}

static sint32 load_sound_attenuation(uint32 length)
{
    sint32 denominator = (sint32)(length + 0x200000u) / 4096;
    sint32 numerator = (sint32)((uint32)(sint32)(sint16)r_u16(0x80065BE8u) << 9);
    return load_sound_divide(numerator, denominator);
}

static sint16 load_sound_mono(const sint32 *vector)
{
    return (sint16)load_sound_attenuation(load_sound_length(vector));
}

static uint32 load_sound_stereo(const sint32 *vector)
{
    uint32 length = load_sound_length(vector);
    sint32 volume = load_sound_attenuation(length), shift, pan = 0, left, right;
    xport_gte_write_data(30u, length);
    shift = (sint32)(xport_gte_read_data(31u) - 1u);
    if (shift > 12)
        shift = 12;
    if (length != 0u)
        pan = load_sound_divide((sint32)((uint32)vector[0] << ((uint32)shift & 31u)),
                                (sint32)length >> ((12u - (uint32)shift) & 31u));
    left = (sint32)((4096u - (uint32)pan) * (uint32)volume) / 8192;
    right = (sint32)(((uint32)pan + 4096u) * (uint32)volume) / 8192;
    return (uint32)left | ((uint32)right << 16);
}

uint32 sub_800446DC(uint32 position)
{
    sint32 first[3], second[3], left, right, limit;
    FUNCTION_MARKER(0x800446DCu, "SLUS_005.10");
    load_sound_transform(0x8006F680u, position, first);
    if (r_u32(0x80065314u) == 0u) {
        if (r_u8(0x800658ACu) == 0u)
            return load_sound_stereo(first);
        left = load_sound_mono(first);
        return ((uint32)left << 16) + (uint32)left;
    }
    load_sound_transform(0x8006F6A0u, position, second);
    left = load_sound_mono(first);
    right = load_sound_mono(second);
    if (r_u8(0x800658ACu) != 0u) {
        limit = (sint16)r_u16(0x80065BE8u);
        if (left + right < limit)
            limit = left + right;
        return ((uint32)limit << 16) + (uint32)limit;
    }
    return ((uint32)left << 16) | (uint32)right;
}

static sint16 load_ambient_mono(const sint32 *vector)
{
    sint32 delta = (sint32)(0x200000u - load_sound_length(vector)), product;
    if (delta < 0) return 0;
    product = (sint32)((uint32)(delta >> 12) * (uint32)(sint32)(sint16)r_u16(0x80065BE8u));
    if (product < 0) product = (sint32)((uint32)product + 511u);
    return (sint16)((sint32)((uint32)product << 7) >> 16);
}

static uint32 load_ambient_stereo(const sint32 *vector)
{
    sint32 length = (sint32)load_sound_length(vector), delta, volume, pan, left, right;
    if (length > 0x1FFFFF) return 0u;
    delta = (sint32)(0x200000u - (uint32)length) / 4096;
    volume = (sint32)((uint32)delta * (uint32)(sint32)(sint16)r_u16(0x80065BE8u)) / 512;
    pan = length != 0 ? load_sound_divide((sint32)((uint32)vector[0] << 12), length) : 0;
    left = (sint32)((4096u - (uint32)pan) * (uint32)volume) / 8192;
    right = (sint32)(((uint32)pan + 4096u) * (uint32)volume) / 8192;
    return (uint32)left | ((uint32)right << 16);
}

uint32 sub_800449BC(uint32 position)
{
    sint32 first[3], second[3], left, right, limit;
    FUNCTION_MARKER(0x800449BCu, "SLUS_005.10");
    load_sound_transform(0x8006F680u, position, first);
    if (r_u32(0x80065314u) == 0u) {
        if (r_u8(0x800658ACu) == 0u) return load_ambient_stereo(first);
        left = load_ambient_mono(first);
        return ((uint32)left << 16) + (uint32)left;
    }
    load_sound_transform(0x8006F6A0u, position, second);
    if (r_u8(0x800658ACu) != 0u) {
        left = load_ambient_mono(first); right = load_ambient_mono(second);
        limit = (sint16)r_u16(0x80065BE8u);
        if (left + right < limit) limit = left + right;
        return ((uint32)limit << 16) + (uint32)limit;
    }
    left = load_ambient_mono(first); right = load_ambient_mono(second);
    return ((uint32)left << 16) | (uint32)right;
}

uint32 sub_8001FF58(uint32 list, uint32 kind, uint32 excluded)
{
    uint32 node = r_u32(list), next = r_u32(node), object;
    while (next != 0u) {
        object = r_u32(node + 8u);
        if (object != excluded && (uint32)(sint32)(sint16)r_u16(object + 6u) == kind)
            return node;
        node = next;
        next = r_u32(node);
    }
    return 0u;
}

uint32 sub_8001FFD4(uint32 list, uint32 kind)
{
    uint32 node = sub_8001FF58(list, kind, 0u);
    return node != 0u ? r_u32(node + 8u) : 0u;
}

uint32 sub_8001D5A0(uint32 object)
{
    uint32 parent = r_u32(object + 60u);
    while (parent != 0u && r_u32(parent + 56u) != object) {
        object = parent;
        parent = r_u32(object + 60u);
    }
    return parent;
}

uint32 sub_8001D624(uint32 object)
{
    uint32 matrix = object + 16u, parent;
    while ((parent = sub_8001D5A0(object)) != 0u) {
        CompMatrixLV((MATRIX *)psx_addr(parent + 16u, sizeof(MATRIX)),
                     (MATRIX *)psx_addr(matrix, sizeof(MATRIX)),
                     (MATRIX *)psx_addr(0x8006F640u, sizeof(MATRIX)));
        object = parent;
        matrix = 0x8006F640u;
    }
    return matrix;
}

uint32 sub_8004410C(void)
{
    uint32 tick = r_u32(0x8005FFB4u), mask = r_u32(0x80065C00u), index;
    for (index = 0u; index < 24u; ++index) {
        if ((mask & 1u) == 0u && r_u16(0x1F801C0Cu + index * 16u) == 0u &&
            ((tick - r_u8(0x800A2FF0u + index)) & 255u) >= 2u)
            return index + 1u;
        mask = (uint32)((sint32)mask >> 1);
    }
    return 0u;
}

void sub_8004483C(uint32 voice, uint32 table, uint32 sample, uint32 position)
{
    uint32 volume = sub_800446DC(position);
    sub_80044484(voice, table, sample, volume);
}

uint32 sub_8003C538(uint32 object, uint32 value);
uint32 sub_80032E48(uint32 weapon, uint32 vehicle, uint32 kind);
uint32 sub_80016AAC(uint32 first, uint32 second);
uint32 sub_80020744(uint32 object);
uint32 sub_800207C4(uint32 object);

uint32 sub_8003302C(uint32 object, uint32 mode, uint32 value)
{
    uint32 target, projectile, vehicle, descriptor, voice, health;
    FUNCTION_MARKER(0x8003302Cu, "SLUS_005.10");
    if (mode >= 15u) return 0u;
    target = r_u32(0x80010640u + mode * 4u);
    switch (target) {
    case 0x8003306Cu:
        (void)sub_8003C538(object, value);
        return 0u;
    case 0x8003325Cu:
        target = r_u32(object);
        w_u16(object + 12u, 12u);
        w_u8(object + 8u, 2u);
        w_u32(object, target | 0x4000u);
        return 0u;
    case 0x80033080u: return 2u;
    case 0x80033224u: return 0x8012u;
    case 0x80033278u: return 0u;
    case 0x8003322Cu:
        return sub_80016AAC(value + 72u, r_u32(value + 228u) + 72u) - 1024001u <= 0x2EDFFEu;
    case 0x80033088u:
        projectile = sub_80032E48(object, value, 21u);
        if ((r_u32(0x80065908u) & 0x400u) != 0u)
            health = r_u16(value + 284u) != 0u ? 300u : 150u;
        else
            health = r_u16(value + 284u) != 0u ? 120u : 60u;
        w_u16(projectile + 12u, health);
        voice = sub_8004410C();
        (void)sub_800447E8(voice, r_u32(0x800658FCu), 46u, projectile + 72u);
        return 90u;
    case 0x800330FCu:
        value &= 0xFFFu;
        if (value == 0x444u) {
            if (r_u16(object + 12u) < 2u) return 0xFFFFFFFFu;
            projectile = sub_8001AC44(r_u32(object + 88u), 19u, 128u, 8u);
            w_u32(projectile + 100u, 0x80032C60u);
            vehicle = sub_8001D5A0(object);
            w_u32(projectile + 120u, vehicle);
            w_u16(projectile + 6u, 120u);
            descriptor = sub_8001B038(object, 0x8001u);
            (void)sub_8001B2FC(object, descriptor, projectile);
            (void)sub_80020744(projectile);
            (void)sub_800207C4(projectile);
            w_u16(object + 12u, r_u16(object + 12u) - 2u);
            return 240u;
        }
        if (value != 0x442u) return 0u;
        if (r_u16(object + 12u) < 2u) return 0xFFFFFFFFu;
        w_u16(object + 12u, r_u16(object + 12u) - 1u);
        vehicle = sub_8001D5A0(object);
        projectile = sub_80032E48(object, vehicle, 32u);
        target = r_u32(projectile);
        w_u32(projectile + 132u, vehicle);
        w_u32(projectile, target | 0x1010000u);
        w_u32(vehicle, r_u32(vehicle) | 0x800000u);
        voice = sub_8004410C();
        (void)sub_800447E8(voice, r_u32(0x800658FCu), 59u, projectile + 72u);
        return 120u;
    default:
        fprintf(stderr, "TODO weapon3302C unknown table target %08X\n", target);
        abort();
    }
}
uint32 sub_800346CC(uint32 weapon, uint32 vehicle, uint32 kind, uint32 effect, uint32 damage);
uint32 sub_8002CB7C(uint32 weapon);

uint32 sub_80034920(uint32 object, uint32 mode, uint32 value)
{
    uint32 target, projectile, vehicle, count, flags;
    sint32 remaining;
    FUNCTION_MARKER(0x80034920u, "SLUS_005.10");
    if (mode >= 15u) return 0u;
    target = r_u32(0x800106C0u + mode * 4u);
    switch (target) {
    case 0x80034958u:
        (void)sub_8003C538(object, value);
        return 0u;
    case 0x80034B2Cu:
        flags = r_u32(object);
        w_u16(object + 12u, 10u);
        w_u8(object + 8u, 4u);
        w_u32(object, flags | 0x4000u);
        return 0u;
    case 0x8003496Cu: return 4u;
    case 0x80034AF4u: return 0x8014u;
    case 0x80034B48u: return 0u;
    case 0x80034AFCu:
        return sub_80016AAC(value + 72u, r_u32(value + 228u) + 72u) + 0xFFE0BFFFu <= 0x1F3FFEu;
    case 0x80034974u:
        (void)sub_800346CC(object, value, 16u, 8u, r_u16(value + 284u) != 0u ? 150u : 75u);
        w_u16(object + 12u, r_u16(object + 12u) - 1u);
        break;
    case 0x800349C0u:
        value &= 0xFFFu;
        if (value != 0x222u && value != 0x224u) return 0u;
        if (r_u16(object + 12u) < 2u) return 0xFFFFFFFFu;
        vehicle = sub_8001D5A0(object);
        if (value == 0x222u) {
            projectile = sub_800346CC(object, vehicle, 36u, 28u, 37u);
            flags = r_u32(projectile);
            w_u8(projectile + 8u, 1u);
            w_u32(projectile, flags | 0x1000000u);
            w_u16(object + 12u, r_u16(object + 12u) - 2u);
        } else {
            count = r_u16(object + 12u);
            if (count > 5u) count = 5u;
            projectile = sub_800346CC(object, vehicle, 37u, 35u, count * 75u);
            flags = r_u32(projectile);
            w_u8(projectile + 8u, 2u);
            w_u32(projectile, flags | 0x1000020u);
            remaining = (sint32)r_u16(object + 12u) - 5;
            w_u16(object + 12u, remaining > 0 ? (uint32)remaining : 0u);
        }
        break;
    default:
        fprintf(stderr, "TODO weapon34920 unknown table target %08X\n", target);
        abort();
    }
    if (r_u16(object + 12u) == 0u) (void)sub_8002CB7C(object);
    return 120u;
}
uint32 sub_8003351C(uint32 weapon, uint32 vehicle, uint32 kind, uint32 damage);
uint32 sub_800170C8(uint32 low, uint32 high);
uint32 sub_80031300(uint32 owner, uint32 weapon, uint32 kind, uint32 bytes, uint32 effect);
uint32 sub_8002CB7C(uint32 weapon);

uint32 sub_800336FC(uint32 object, uint32 mode, uint32 value)
{
    uint32 target, parent, vehicle, projectile, matrix, position, voice, i, j;
    sint32 delta[3], yaw, pitch, range, quotient, gravity, original_pitch, original_yaw;
    uint64 squared;
    FUNCTION_MARKER(0x800336FCu, "SLUS_005.10");
    if (mode >= 15u) return 0u;
    target = r_u32(0x80010680u + mode * 4u);
    switch (target) {
    case 0x80033754u:
        if (sub_8003C538(object, value) == 0u) return 0u;
        if (r_u32(value + 228u) == 0u) return 0u;
        parent = r_u32(object + 56u);
        matrix = sub_8001D624(object);
        position = r_u32(value + 228u);
        for (j = 0u; j < 3u; ++j)
            delta[j] = (sint32)(r_u32(position + 72u + j * 4u) - r_u32(matrix + 20u + j * 4u));
        v8_native_4352C(matrix, delta, delta);
        yaw = (sint32)((uint32)ratan2(delta[0], delta[2]) << 20) >> 20;
        squared = (uint64)((sint64)delta[0] * delta[0]) + (uint64)((sint64)delta[2] * delta[2]);
        range = (sint32)sub_800170C8((uint32)squared, (uint32)(squared >> 32));
        if (range == 0) {
            fprintf(stderr, "Missing __divdi3 zero denominator trap at weapon336FC\n");
            abort();
        }
        quotient = (sint32)(uint32)((sint64)24576 * delta[1] / range);
        gravity = (sint32)((uint32)range * 56u) / 49152;
        pitch = (sint32)((0u - (uint32)ratan2((sint32)((uint32)quotient - (uint32)gravity), 24576)) << 20) >> 20;
        if (pitch > 256) pitch = 256;
        if (pitch < -128) pitch = -128;
        w_u16(parent + 66u, r_u16(parent + 66u) + (uint32)((yaw - r_s16(parent + 66u)) / 4));
        w_u16(parent + 64u, r_u16(parent + 64u) + (uint32)((pitch - r_s16(parent + 64u)) / 4));
        (void)sub_8001D708(parent);
        return 0u;
    case 0x80033C28u:
        target = r_u32(object);
        w_u16(object + 12u, 12u);
        w_u8(object + 8u, 3u);
        w_u32(object, target | 0x4000u);
        return 0u;
    case 0x80033928u: return 3u;
    case 0x80033BE8u: return 0x8013u;
    case 0x80033C44u: return 0u;
    case 0x80033BF0u:
        if ((sint32)sub_80016AAC(value + 72u, r_u32(value + 228u) + 72u) > 4095999) return 0u;
        return (sint32)r_u32(value + 140u) < 4577;
    case 0x80033930u:
        voice = sub_8004410C();
        matrix = sub_8001D624(object);
        sub_8004483C(voice, r_u32(0x800658FCu), 43u, matrix + 20u);
        return 0u;
    case 0x80033960u:
        (void)sub_8003351C(object, value, 6u, r_u16(value + 284u) != 0u ? 150u : 75u);
        return 60u;
    case 0x8003398Cu:
        value &= 0xFFFu;
        if (value != 0x242u && value != 0x244u) return 0u;
        if (r_u16(object + 12u) < 2u) return 0xFFFFFFFFu;
        if (value == 0x242u) {
            w_u16(object + 12u, r_u16(object + 12u) - 1u);
            vehicle = sub_8001D5A0(object);
            projectile = sub_8003351C(object, vehicle, 35u, 40u);
            target = r_u32(projectile);
            w_u8(projectile + 8u, 1u);
            w_u32(projectile, target | 0x1000000u);
            return 120u;
        }
        vehicle = sub_8001D5A0(object);
        parent = r_u32(object + 56u);
        original_pitch = r_s16(parent + 64u);
        original_yaw = r_s16(parent + 66u);
        projectile = sub_8003351C(object, vehicle, 6u, 75u);
        w_u32(projectile, r_u32(projectile) | 0x1000000u);
        for (i = 1u; i < 6u && r_u16(object + 12u) != 0u; ++i) {
            w_u16(parent + 64u, (uint32)original_pitch + (uint32)((sint32)(192u * sub_80017160()) >> 15) - 96u);
            w_u16(parent + 66u, (uint32)original_yaw + (uint32)((sint32)(192u * sub_80017160()) >> 15) - 96u);
            (void)sub_8001D708(parent);
            projectile = sub_80031300(vehicle, parent, 6u, 152u, 0u);
            w_u32(projectile, 0x1800094u);
            w_u16(projectile + 12u, 75u);
            w_u32(projectile + 100u, 0x80033290u);
            (void)sub_800202F4(projectile);
            w_u16(projectile + 148u, 60u);
            for (j = 0u; j < 3u; ++j)
                w_u32(projectile + 136u + j * 4u, (uint32)((sint32)r_u32(vehicle + 128u + j * 4u) / 128) +
                    (uint32)(6 * r_s16(projectile + 20u + j * 6u)));
            w_u16(object + 12u, r_u16(object + 12u) - 1u);
        }
        w_u16(parent + 64u, (uint32)original_pitch);
        w_u16(parent + 66u, (uint32)original_yaw);
        (void)sub_8001D708(parent);
        if (r_u16(object + 12u) == 0u) (void)sub_8002CB7C(object);
        return 120u;
    default:
        fprintf(stderr, "TODO weapon336FC unknown table target %08X\n", target);
        abort();
    }
}
uint32 sub_8001D68C(uint32 destination, uint32 object, uint32 descriptor)
{
    uint32 parent = sub_8001D624(object);
    SVECTOR angles;
    VECTOR translation;
    MATRIX *local = (MATRIX *)psx_addr(destination, sizeof(MATRIX));
    FUNCTION_MARKER(0x8001D68Cu, "SLUS_005.10");
    angles.vx = (sint16)r_u16(descriptor + 16u);
    angles.vy = (sint16)r_u16(descriptor + 18u);
    angles.vz = (sint16)r_u16(descriptor + 20u); angles.pad = 0;
    RotMatrix(&angles, local);
    translation.vx = (sint32)r_u32(descriptor + 4u);
    translation.vy = (sint32)r_u32(descriptor + 8u);
    translation.vz = (sint32)r_u32(descriptor + 12u);
    TransMatrix(local, &translation);
    CompMatrixLV((MATRIX *)psx_addr(parent, sizeof(MATRIX)), local, local);
    return destination;
}

uint32 sub_800207C4(uint32 object)
{
    FUNCTION_MARKER(0x800207C4u, "SLUS_005.10");
    w_u32(object, r_u32(object) | 4u);
    return sub_8001FE50(0x80065A80u, object);
}

uint32 sub_800447E8(uint32 voice, uint32 table, uint32 sample, uint32 position)
{
    uint32 volume;
    FUNCTION_MARKER(0x800447E8u, "SLUS_005.10");
    volume = sub_800446DC(position);
    return sub_800443C8(voice, table, sample, volume, volume);
}

uint32 sub_80031300(uint32 owner, uint32 weapon, uint32 kind, uint32 bytes, uint32 effect)
{
    uint32 descriptor, projectile, matrix, words[4], i, group;
    FUNCTION_MARKER(0x80031300u, "SLUS_005.10");
    descriptor = sub_8001B038(weapon, 0x8000u);
    projectile = (kind & 0x8000u) != 0u ? sub_8001D470(bytes) :
        sub_8001AC44(r_u32(weapon + 88u), kind & 0xFFFFu, bytes, 8u);
    w_u32(projectile + 128u, owner);
    w_u32(projectile, 0x800000u);
    w_u8(projectile + 4u, 7u);
    w_u16(projectile + 6u, r_u16(owner + 6u));
    if (descriptor != 0u) (void)sub_8001D68C(projectile + 16u, weapon, descriptor);
    else {
        matrix = sub_8001D624(weapon);
        for (group = 0u; group < 2u; ++group) {
            for (i = 0u; i < 4u; ++i) words[i] = r_u32(matrix + group * 16u + i * 4u);
            for (i = 0u; i < 4u; ++i) w_u32(projectile + 16u + group * 16u + i * 4u, words[i]);
        }
    }
    for (i = 0u; i < 3u; ++i) words[i] = r_u32(projectile + 36u + i * 4u);
    for (i = 0u; i < 3u; ++i) w_u32(projectile + 72u + i * 4u, words[i]);
    if (effect != 0u) (void)sub_8001B2FC(weapon, descriptor, effect);
    return projectile;
}

uint32 sub_8003FD24(uint32 position, uint32 kind)
{
    uint32 effect, child, coordinates[3], i;
    FUNCTION_MARKER(0x8003FD24u, "SLUS_005.10");
    effect = sub_8001AC44(r_u32(0x800737D8u), kind & 0xFFFFu, 128u, 8u);
    w_u8(effect + 4u, 1u);
    w_u32(effect, 52u);
    for (i = 0u; i < 3u; ++i) coordinates[i] = r_u32(position + 4u * i);
    for (i = 0u; i < 3u; ++i) w_u32(effect + 72u + 4u * i, coordinates[i]);
    child = r_u32(effect + 56u);
    w_u32(effect + 100u, 0x8003E80Cu);
    while (child != 0u) {
        w_u32(child + 100u, 0x8003E7B4u);
        child = r_u32(child + 52u);
    }
    (void)sub_8002036C(effect, effect);
    return effect;
}

uint32 sub_8001FF0C(uint32 list, uint32 object)
{
    uint32 node = r_u32(list), next = r_u32(node);
    FUNCTION_MARKER(0x8001FF0Cu, "SLUS_005.10");
    while (next != 0u) {
        if (r_u32(node + 8u) == object) return node;
        node = next;
        next = r_u32(node);
    }
    return 0u;
}

uint32 sub_800210A4(uint32 tree, uint32 object)
{
    uint32 kind, result;
    FUNCTION_MARKER(0x800210A4u, "SLUS_005.10");
    for (;;) {
        kind = r_u32(tree);
        if (kind == 0u) return sub_8001FF0C(tree + 4u, object);
        if (kind >= 3u) return 0u;
        result = sub_800210A4(r_u32(tree + 8u), object);
        if (result != 0u) return result;
        tree = r_u32(tree + 12u);
    }
}

uint32 sub_8002179C(uint32 object)
{
    uint32 node;
    FUNCTION_MARKER(0x8002179Cu, "SLUS_005.10");
    node = sub_8001FF0C(0x80065A18u, object);
    return node != 0u ? node : sub_800210A4(r_u32(0x80065A00u), object);
}

void sub_80020540(uint32 object, uint32 incoming_v0)
{
    uint32 resource;
    FUNCTION_MARKER(0x80020540u, "SLUS_005.10");
    resource = r_u32(object + 104u);
    if (resource != 0u) (void)sub_8001BDDC(resource, incoming_v0);
    if ((r_u32(object) & 8u) != 0u) sub_8003E2C4(r_u32(object + 112u));
    sub_800204DC(object);
}

void sub_800205A0(uint32 node)
{
    uint32 previous, next, object, tail;
    FUNCTION_MARKER(0x800205A0u, "SLUS_005.10");
    if (node == 0u) return;
    previous = r_u32(node + 4u);
    next = r_u32(node);
    object = r_u32(node + 8u);
    w_u32(next + 4u, previous);
    w_u32(previous, next);
    tail = r_u32(0x80065A78u);
    w_u32(0x80065A78u, node);
    w_u32(tail, node);
    w_u32(node + 4u, tail);
    w_u32(node, 0x80065A74u);
    w_u32(node + 8u, 0u);
    sub_80020540(object, 0x80065A74u);
}

void sub_800205F8(uint32 object)
{
    FUNCTION_MARKER(0x800205F8u, "SLUS_005.10");
    sub_800205A0(sub_8002179C(object));
}

uint32 sub_80031634(uint32 object, uint32 mode, uint32 value)
{
    uint32 target = 0u, effect, voice, sample, kind, i, coordinates[3];
    FUNCTION_MARKER(0x80031634u, "SLUS_005.10");
    if (mode == 0u) {
        if ((sint32)sub_80025400(r_u32(object + 72u), r_u32(object + 80u)) >= (sint32)r_u32(object + 76u)) {
            w_u32(object + 72u, r_u32(object + 72u) + r_u32(object + 136u));
            coordinates[2] = r_u32(object + 80u);
            w_u32(object + 76u, r_u32(object + 76u) + r_u32(object + 140u));
            w_u32(object + 80u, coordinates[2] + r_u32(object + 144u));
            for (i = 0u; i < 3u; ++i) coordinates[i] = r_u32(object + 72u + 4u * i);
            for (i = 0u; i < 3u; ++i) w_u32(object + 36u + 4u * i, coordinates[i]);
            w_u16(object + 148u, r_u16(object + 148u) - 1u);
            if (r_u16(object + 148u) != 0u) return 0u;
        } else {
            effect = sub_8003FD24(object + 72u, 1u);
            w_u16(effect + 68u, sub_80017160());
            (void)sub_8001D708(effect);
            voice = sub_8004410C();
            sample = (sub_80017160() & 3u) == 0u ? 64u : 61u;
            sub_8004483C(voice, r_u32(0x800658FCu), sample, object + 72u);
        }
    } else if (mode == 3u) {
        target = r_u32(value);
        if (r_u8(target + 4u) == 3u) return 0u;
        effect = sub_8003FD24(object + 72u, 1u);
        w_u32(effect, r_u32(effect) | 0x400u);
        w_u16(effect + 68u, sub_80017160());
        (void)sub_8001D708(effect);
        if (r_u8(target + 4u) != 2u || r_u16(target + 286u) == 0u) {
            voice = sub_8004410C();
            sample = 64u;
            if ((sub_80017160() & 3u) != 0u) {
                sample = 62u;
                if (r_u8(target + 4u) != 2u) {
                    kind = r_u16(target + 6u);
                    if (kind - 96u < 32u) sample = 62u;
                    else if (kind - 64u < 32u || kind - 129u < 31u) sample = 63u;
                    else sample = 61u;
                }
            }
            sub_8004483C(voice, r_u32(0x800658FCu), sample, object + 72u);
        }
    } else return 0u;
    sub_800205F8(object);
    return 0xFFFFFFFFu;
}

uint32 sub_80031864(uint32 object, uint32 mode, uint32 value)
{
    sint32 interval;
    uint8 countdown;
    FUNCTION_MARKER(0x80031864u, "SLUS_005.10");
    if (mode == 1u) {
        w_u16(object + 12u, 1280u);
        return 0u;
    }
    if (mode == 4u) {
        interval = (sint32)r_u16(object + 12u) - 64;
        w_u16(object + 12u, interval > 1280 ? (uint16)interval : 1280u);
        w_u8(object + 5u, 0u);
        w_u8(object + 8u, 0u);
        return 0u;
    }
    if (mode == 14u)
        return 0x8010u;
    if (mode == 12u) {
        sint32 source[3], transformed[3], angle;
        uint32 position = r_u32(value + 228u) + 36u, i;
        for (i = 0u; i < 3u; ++i)
            source[i] = (sint32)r_u32(position + 4u * i);
        v8_native_435C0(value + 16u, source, transformed);
        angle = (sint32)((uint32)ratan2(transformed[0], transformed[2]) << 20u) >> 20;
        if (angle < 0)
            angle = -angle;
        return angle < 113 && transformed[2] <= 511999 ? 1u : 0u;
    }
    if (mode == 11u) {
        uint32 effect, projectile, i, voice;
        countdown = (uint8)(r_u8(object + 8u) - 1u);
        w_u8(object + 8u, countdown);
        if ((sint8)countdown != -1)
            return 0u;
        effect = sub_8001AC44(r_u32(0x800737D8u), 3u, 128u, 8u);
        projectile = sub_80031300(value, object, 4u, 152u, effect);
        w_u32(projectile, 640u);
        w_u16(projectile + 12u, r_u16(value + 284u) != 0u ? 14u : 7u);
        w_u32(projectile + 100u, 0x80031634u);
        for (i = 0u; i < 3u; ++i)
            w_u32(projectile + 136u + 4u * i, (uint32)((sint32)r_u32(value + 128u + 4u * i) / 128) +
                4u * (uint32)(sint32)(sint16)r_u16(projectile + 20u + 6u * i));
        w_u16(projectile + 148u, 45u);
        (void)sub_800202F4(projectile);
        w_u32(effect + 100u, 0x8003E80Cu);
        if ((r_u32(value) & 4u) == 0u) (void)sub_800207C4(effect);
        voice = (uint32)(sint32)(sint8)r_u8(object + 5u);
        if (voice == 0u) {
            voice = sub_8004410C();
            w_u8(object + 5u, voice);
            voice = (uint32)(sint32)(sint8)voice;
        }
        (void)sub_800447E8(voice, r_u32(0x800658FCu), 36u, projectile + 72u);
        w_u8(object + 8u, r_u16(object + 12u) >> 8);
        w_u16(object + 12u, r_u16(object + 12u) + 32u);
        return 0u;
    }
    if (mode == 0u || mode == 11u) {
        /* TODO Translate projectile creation and update dependencies */
        fprintf(stderr, "Missing weapon callback 80031864 mode %u value %08X\n", mode, value);
        abort();
    }
    return 0u;
}

static void load_ski_place(uint32 object, uint32 position)
{
    uint32 level = r_u32(0x800659FCu), first, second, node, next, key, fraction, i;
    sint32 start[3], end[3], midpoint[3], angle, extent;
    w_u16(object + 70u, (uint16)position);
    if ((position & 0x7FFFu) < 0x7000u) {
        uint32 parameter = (uint32)(sint32)(sint16)position;
        if ((sint16)position < 0)
            parameter = 0u - parameter - 0x1000u;
        node = r_u32(level + 128u);
        next = r_u32(node);
        while (next != 0u && r_u32(next + 12u) < parameter) {
            node = next;
            next = r_u32(node);
        }
        first = r_u32(node + 8u);
        second = r_u32(next + 8u);
        fraction = r_u32(next + 12u) - r_u32(node + 12u);
        fraction = fraction != 0u ? ((parameter - r_u32(node + 12u)) << 8) / fraction : 0xFFFFFFFFu;
        angle = (sint16)r_u16(first + 66u);
        if (angle < 0) angle = -angle;
        key = angle > 1024 ? 0x8001u : 0x8000u;
        if ((sint16)position >= 0) key ^= 1u;
        key = sub_8001B038(first, key);
        load_sound_transform(first + 16u, key + 4u, start);
        angle = (sint16)r_u16(second + 66u);
        if (angle < 0) angle = -angle;
        key = angle > 1024 ? 0x8001u : 0x8000u;
        if ((sint16)position >= 0) key ^= 1u;
        key = sub_8001B038(second, key);
        load_sound_transform(second + 16u, key + 4u, end);
        for (i = 0u; i < 3u; ++i)
            w_u32(object + 72u + i * 4u, (uint32)start[i] +
                  (uint32)((sint32)(((uint32)end[i] - (uint32)start[i]) * fraction) / 256));
    }
    else {
        node = r_u32(level + ((position & 0xFFFFu) > 0xEFFFu ? 128u : 136u));
        first = r_u32(node + 8u);
        key = sub_8001B038(first, 0x8000u);
        next = sub_8001B038(first, 0x8001u);
        extent = (sint32)(r_u32(next + 4u) - r_u32(key + 4u));
        for (i = 0u; i < 3u; ++i) {
            uint32 sum = r_u32(key + 4u + i * 4u) + r_u32(next + 4u + i * 4u);
            midpoint[i] = (sint32)(sum + (sum >> 31)) >> 1;
        }
        load_transform_input(first + 16u, 0u, midpoint, midpoint);
        angle = (sint32)(0u - (uint32)(sint32)(sint16)position);
        angle = (sint32)((uint32)angle + ((uint32)angle >> 31)) >> 1;
        if ((position & 0xFFFFu) <= 0xEFFFu) angle += 2048;
        w_u16(object + 66u, (uint16)angle);
        key = 0x800607B4u + ((uint32)angle & 0xFFFu) * 4u;
        w_u32(object + 72u, (uint32)midpoint[0] +
              (uint32)((sint32)((uint32)(sint32)(sint16)r_u16(key + 2u) * (uint32)extent) / 8192));
        w_u32(object + 76u, (uint32)midpoint[1]);
        w_u32(object + 80u, (uint32)midpoint[2] -
              (uint32)((sint32)((uint32)(sint32)(sint16)r_u16(key) * (uint32)extent) / 8192));
    }
    (void)sub_8001D708(object);
}

static void load_ski_line_limit(uint32 packet)
{
    uint32 axis;
    for (axis = 0u; axis < 2u; ++axis) {
        sint32 limit = axis == 0u ? 1024 : 512;
        for (;;) {
            sint32 a = (sint16)r_u16(packet + 8u + axis * 2u);
            sint32 b = (sint16)r_u16(packet + 12u + axis * 2u);
            sint32 delta = a - b;
            uint32 end;
            if (delta < 0) delta = -delta;
            if (delta < limit) break;
            end = (a < 0 ? -a : a) > (b < 0 ? -b : b) ? 8u : 12u;
            w_u16(packet + end, ((sint16)r_u16(packet + 8u) + (sint16)r_u16(packet + 12u)) / 2);
            w_u16(packet + end + 2u, ((sint16)r_u16(packet + 10u) + (sint16)r_u16(packet + 14u)) / 2);
        }
    }
}

static void load_ski_line_clip(uint32 destination, const sint32 *a, const sint32 *b)
{
    uint32 axis;
    for (axis = 0u; axis < 2u; ++axis) {
        sint32 product = (sint32)((uint32)(b[axis] - (uint32)a[axis]) * (128u - (uint32)a[2]));
        sint32 denominator = (sint32)((uint32)b[2] - (uint32)a[2]);
        sint32 quotient = load_sound_divide(product, denominator);
        uint32 center = xport_gte_read_screen_offset(axis) >> 16u;
        w_u16(destination + axis * 2u, center + (((uint32)a[axis] + (uint32)quotient) << 1u));
    }
}

static void load_ski_cables(uint32 object)
{
    uint32 head = r_u32(object + 128u), node = head, next = r_u32(node);
    uint32 packet = r_u32(object + 140u + r_u32(0x80065308u) * 4u), following = packet + 24u;
    sint32 previous[2][3] = {{0}}, current[2][3];
    while (next != 0u) {
        uint32 point = r_u32(node + 8u), vertex[2], side, axis;
        sint32 angle = (sint16)r_u16(point + 66u);
        MATRIX composed;
        if (angle < 0) angle = -angle;
        vertex[0] = sub_8001B038(point, angle <= 1024 ? 0xFFFF8000u : 0xFFFF8001u);
        vertex[1] = sub_8001B038(point, angle <= 1024 ? 0xFFFF8001u : 0xFFFF8000u);
        CompMatrixLV((MATRIX *)psx_addr(0x8006F680u, sizeof(MATRIX)),
                     (MATRIX *)psx_addr(point + 16u, sizeof(MATRIX)), &composed);
        SetRotMatrix(&composed);
        for (axis = 0u; axis < 3u; ++axis)
            xport_gte_write_control(5u + axis, (uint32)(composed.t[axis] >> 8));
        for (side = 0u; side < 2u; ++side) {
            uint32 x = (uint32)((sint32)r_u32(vertex[side] + 4u) >> 8);
            uint32 y = (uint32)((sint32)r_u32(vertex[side] + 8u) >> 8);
            xport_gte_write_data(0u, (x & 65535u) + (y << 16u));
            xport_gte_write_data(1u, (uint32)((sint32)r_u32(vertex[side] + 12u) >> 8));
            xport_gte_execute(0x00180001u);
            for (axis = 0u; axis < 3u; ++axis)
                current[side][axis] = (sint32)xport_gte_read_data(9u + axis);
        }
        if (node != head) {
            for (side = 0u; side < 2u; ++side) {
                sint32 za = previous[side][2], zb = current[side][2];
                if (za > 128 || zb > 128) {
                    uint32 ot, tag;
                    w_u32(following - 12u, xport_gte_read_data(13u + side));
                    if (za < 128 || zb < 128)
                        load_ski_line_clip(packet + (za < 128 ? 8u : 12u), previous[side], current[side]);
                    load_ski_line_limit(packet);
                    ot = r_u32(0x80065910u) + ((uint32)((za > zb ? za : zb) >> 3) << 2u);
                    tag = r_u32(ot);
                    w_u32(ot, packet & 0xFFFFFFu);
                    w_u32(packet, tag | 0x03000000u);
                }
                following += 16u;
                packet += 16u;
            }
        }
        w_u32(following - 16u, xport_gte_read_data(13u));
        w_u32(following, xport_gte_read_data(14u));
        memcpy(previous, current, sizeof(previous));
        node = next;
        next = r_u32(next);
    }
}

uint32 sub_8001DB54(uint32 position, uint32 bound);
void sub_8002C99C(uint32 object, uint32 slot);
uint32 sub_8001FE8C(uint32 list, uint32 object);
uint32 sub_8003C288(uint32 object, uint32 descriptor);
uint32 sub_800354E0(uint32 weapon, uint32 vehicle, uint32 kind, uint32 callback);
uint32 sub_8002CA94(uint32 object, uint32 slot);
uint32 sub_80016A20(uint32 vector);
uint32 sub_800244C4(uint32 x, uint32 z);
uint32 sub_8001D564(uint32 object);
uint32 sub_8001AF48(uint32 object, uint32 incoming_v0);

uint32 sub_8004042C(uint32 object, uint32 mode)
{
    uint32 result;
    FUNCTION_MARKER(0x8004042Cu, "SLUS_005.10");
    if (mode != 5u) return 0u;
    result = sub_8001D564(object);
    sub_8001AF48(object, result);
    return 0xFFFFFFFFu;
}

uint32 sub_8003C288(uint32 object, uint32 descriptor)
{
    sint32 delta[3], absolute[3], maximum;
    uint32 i, coordinate[3], parent, weapon, callback, count, voice, matrix;
    FUNCTION_MARKER(0x8003C288u, "SLUS_005.10");
    for (i = 0u; i < 3u; ++i)
        delta[i] = (sint32)(r_u32(descriptor + 4u + i * 4u) - r_u32(object + 72u + i * 4u));
    if ((sint8)r_u8(object + 8u) >= 0) {
        for (i = 0u; i < 3u; ++i)
            absolute[i] = delta[i] < 0 ? (sint32)(0u - (uint32)delta[i]) : delta[i];
        maximum = absolute[1] < absolute[0] ? absolute[0] : absolute[1];
        if (absolute[2] >= maximum) maximum = absolute[2];
        if (maximum < 2049) return 1u;
    }
    w_u32(object + 72u, r_u32(object + 72u) + (uint32)(delta[0] / 32) + (uint32)(delta[2] / 8));
    w_u32(object + 76u, r_u32(object + 76u) + (uint32)(delta[1] / 16));
    w_u32(object + 80u, r_u32(object + 80u) + (uint32)(delta[2] / 32) - (uint32)(delta[0] / 8));
    for (i = 0u; i < 3u; ++i) coordinate[i] = r_u32(object + 72u + i * 4u);
    for (i = 0u; i < 3u; ++i) w_u32(object + 36u + i * 4u, coordinate[i]);
    if ((sint8)r_u8(object + 8u) >= 0 || ((r_u32(0x80065310u) - r_u8(object + 9u)) & 3u) != 0u)
        return 0u;
    parent = sub_8001D5A0(object);
    for (i = 0u; i < 3u; ++i) {
        weapon = r_u32(parent + 272u + i * 4u);
        if ((sint8)r_u8(weapon + 8u) != -(sint32)(sint8)r_u8(object + 8u)) continue;
        callback = r_u32(weapon + 100u);
        if (callback != 0u && v8_native_terrain_call3(callback, weapon, 15u, object) != 0u) continue;
        weapon = r_u32(parent + 272u + i * 4u);
        count = r_u16(weapon + 12u);
        if (count < 99u) w_u16(weapon + 12u, count + 1u);
    }
    count = (r_u16(object + 12u) - 1u) & 0xFFFFu;
    w_u16(object + 12u, count);
    if (count != 0u) return 0u;
    voice = sub_8004410C();
    matrix = sub_8001D624(object);
    sub_8004483C(voice, r_u32(0x800658FCu), 40u, matrix + 20u);
    sub_8001D564(object);
    sub_800204DC(object);
    return 0xFFFFFFFFu;
}

uint32 sub_80020778(uint32 object)
{
    FUNCTION_MARKER(0x80020778u, "SLUS_005.10");
    if ((r_u32(object) & 0x80u) == 0u) return 0u;
    w_u32(object, r_u32(object) & ~0x80u);
    return sub_8001FE8C(0x80065A60u, object);
}

uint32 sub_8003C538(uint32 object, uint32 value)
{
    uint32 voice, matrix, descriptor, coordinate[3], i;
    FUNCTION_MARKER(0x8003C538u, "SLUS_005.10");
    if ((r_u32(object) & 0x10000u) == 0u) return 1u;
    if (value <= 0x80000000u && sub_8003C288(object, r_u32(object + 128u)) == 0u) return 0u;
    voice = sub_8004410C();
    matrix = sub_8001D624(object);
    sub_8004483C(voice, r_u32(0x800658FCu), 44u, matrix + 20u);
    descriptor = r_u32(object + 128u);
    w_u32(object, r_u32(object) & ~0x10000u);
    for (i = 0u; i < 3u; ++i) coordinate[i] = r_u32(descriptor + 4u + i * 4u);
    for (i = 0u; i < 3u; ++i) w_u32(object + 72u + i * 4u, coordinate[i]);
    for (i = 0u; i < 3u; ++i) coordinate[i] = r_u32(object + 72u + i * 4u);
    for (i = 0u; i < 3u; ++i) w_u32(object + 36u + i * 4u, coordinate[i]);
    sub_80020778(object);
    return 0u;
}

uint32 sub_8002CB7C(uint32 weapon)
{
    uint32 object, slot;
    FUNCTION_MARKER(0x8002CB7Cu, "SLUS_005.10");
    object = sub_8001D5A0(weapon);
    if (object == 0u) return 0u;
    for (slot = 0u; slot < 3u; ++slot)
        if (r_u32(object + 272u + slot * 4u) == weapon) return sub_8002CA94(object, slot);
    return 0u;
}

static uint32 load_host_vector_length(const sint32 *vector)
{
    uint64 square = 0u;
    uint32 i, high, low, scale, shift, shifted, normalized;
    for (i = 0u; i < 3u; ++i) square += (uint64)((sint64)vector[i] * vector[i]);
    low = (uint32)square;
    high = (uint32)(square >> 32);
    xport_gte_write_data(30u, high);
    scale = (uint32)((sint32)(35u - xport_gte_read_data(31u)) >> 1);
    shift = scale << 1;
    shifted = shift << 26;
    if ((sint32)shifted < 0) normalized = (uint32)((sint32)high >> (shift & 31u));
    else {
        normalized = low >> (shift & 31u);
        if (shifted != 0u) normalized |= high << ((0u - shift) & 31u);
    }
    return (uint32)SquareRoot0((sint32)normalized) << (scale & 31u);
}

sint16 *v8_native_16B08(const sint32 *vector, sint16 *normal)
{
    sint32 length, shift, divisor, dividend, quotient;
    uint32 i;
    FUNCTION_MARKER(0x80016B08u, "SLUS_005.10");
    length = (sint32)load_host_vector_length(vector);
    if (length == 0) {
        normal[2] = normal[1] = normal[0] = 0;
        return normal;
    }
    xport_gte_write_data(30u, (uint32)length);
    shift = (sint32)xport_gte_read_data(31u) - 1;
    if (shift > 12) shift = 12;
    divisor = length >> ((12u - (uint32)shift) & 31u);
    for (i = 0u; i < 3u; ++i) {
        dividend = (sint32)((uint32)vector[i] << ((uint32)shift & 31u));
        if (divisor == 0) quotient = dividend < 0 ? 1 : -1;
        else if (dividend == (sint32)0x80000000u && divisor == -1) quotient = dividend;
        else quotient = dividend / divisor;
        normal[i] = (sint16)quotient;
    }
    return normal;
}

sint16 *v8_native_16BD8(sint16 *normal, uint32 first, uint32 second)
{
    sint32 vector[3];
    uint32 i;
    FUNCTION_MARKER(0x80016BD8u, "SLUS_005.10");
    for (i = 0u; i < 3u; ++i) vector[i] = (sint32)(r_u32(second + i * 4u) - r_u32(first + i * 4u));
    return v8_native_16B08(vector, normal);
}

uint32 sub_8003565C(uint32 weapon, uint32 mode, uint32 value)
{
    uint32 target, projectile, count, used, random, vehicle, other, i, sum = 0u;
    sint32 source[3], local[3], angle, speed;
    sint16 normal[3];
    FUNCTION_MARKER(0x8003565Cu, "SLUS_005.10");
    if (mode >= 15u) return 0u;
    target = r_u32(0x80010700u + mode * 4u);
    switch (target) {
    case 0x800356A4u:
        sub_8003C538(weapon, value);
        return 0u;
    case 0x800356B4u: return 5u;
    case 0x8003598Cu: return 0x8015u;
    case 0x80035994u:
        w_u16(weapon + 12u, 6u);
        w_u8(weapon + 8u, 5u);
        return 0u;
    case 0x800356BCu:
        sub_800354E0(weapon, value, 15u, 0x80034CECu);
        count = (r_u16(weapon + 12u) - 1u) & 0xFFFFu;
        w_u16(weapon + 12u, count);
        if (count == 0u) sub_8002CB7C(weapon);
        return 60u;
    case 0x800356FCu:
        used = value & 0xFFFu;
        if (used != 306u && used != 308u) return 0u;
        if (r_u16(weapon + 12u) < 2u) return 0xFFFFFFFFu;
        vehicle = sub_8001D5A0(weapon);
        projectile = sub_800354E0(weapon, vehicle, used == 306u ? 28u : 24u,
            used == 306u ? 0x8003502Cu : 0x800352ACu);
        count = sub_80016A20(r_u32(projectile + 92u) + 16u);
        target = r_u32(projectile);
        w_u32(projectile + 84u, count);
        w_u8(projectile + 4u, 3u);
        w_u32(projectile, target | 0x1000000u);
        if (used == 308u) {
            used = r_u16(weapon + 12u);
            if (used >= 6u) used = 6u;
            w_u16(projectile + 12u, used);
        } else used = 2u;
        count = (r_u16(weapon + 12u) - used) & 0xFFFFu;
        w_u16(weapon + 12u, count);
        if (count == 0u) sub_8002CB7C(weapon);
        return 120u;
    case 0x80035830u:
        vehicle = value;
        random = sub_80017160();
        if ((random & 0x3FFu) == 0u) return 1u;
        if ((random & 0xFFu) == 0u && (sub_800244C4(r_u32(vehicle + 36u), r_u32(vehicle + 44u)) & 0xFFu) == 128u)
            return 1u;
        if ((random & 15u) != 0u) return 0u;
        other = r_u32(vehicle + 228u);
        for (i = 0u; i < 3u; ++i) source[i] = (sint32)r_u32(other + 36u + i * 4u);
        v8_native_435C0(vehicle + 16u, source, local);
        if (local[2] >= 0 || local[2] <= -614400) return 0u;
        angle = (sint32)((uint32)ratan2(local[0], local[2]) << 20) >> 20;
        if (angle < 0) angle = -angle;
        if (angle < 1707) return 0u;
        v8_native_16BD8(normal, other + 36u, vehicle + 36u);
        for (i = 0u; i < 3u; ++i)
            sum += (uint32)((sint32)r_u32(other + 128u + i * 4u) / 128) * (uint32)(sint32)normal[i];
        speed = (sint32)((uint32)((sint32)sum / 4096) * 60u);
        return (sint32)(0u - (uint32)local[2]) < speed;
    case 0x800359A4u: return 0u;
    default:
        /* TODO Translate an unknown changed weapon jump-table destination */
        fprintf(stderr, "Missing weapon3565C jump target %08X\n", target);
        abort();
        return 0u;
    }
}

uint32 sub_80020744(uint32 object)
{
    FUNCTION_MARKER(0x80020744u, "SLUS_005.10");
    w_u32(object, r_u32(object) | 0x80u);
    return sub_8001FE50(0x80065A60u, object);
}

uint32 sub_8002CBE8(uint32 object, uint32 weapon)
{
    uint32 slot = 0u, selected, result;
    FUNCTION_MARKER(0x8002CBE8u, "SLUS_005.10");
    w_u16(weapon + 6u, 0u);
    sub_8001D4F0(object, weapon);
    if (r_u32(object + 272u) != 0u) {
        while (slot < 3u) {
            if ((sint8)r_u8(r_u32(object + 272u + slot * 4u) + 8u) == (sint8)r_u8(weapon + 8u)) {
                result = 0u - r_u8(weapon + 8u);
                w_u8(weapon + 8u, result);
                return result;
            }
            ++slot;
            if (r_u32(object + 272u + slot * 4u) == 0u) break;
        }
    }
    if (slot == 3u) {
        selected = r_u8(object + 179u);
        if ((sint16)r_u16(object + 6u) > 0 &&
            (sint8)r_u8(r_u32(object + 272u + selected * 4u) + 8u) == 6)
            selected = selected != 0u ? selected - 1u : 2u;
        sub_8002C99C(object, selected);
        slot = selected;
    }
    result = object + 4u * (slot + 9u);
    w_u32(result + 236u, weapon);
    return result;
}

uint32 sub_8003EE88(uint32 object, uint32 mode, uint32 ticks)
{
    uint32 distance, factor, channel[3], progress;
    sint32 product, color;
    uint32 i;
    FUNCTION_MARKER(0x8003EE88u, "SLUS_005.10");
    if (mode != 0u || ticks == 0u) return 0u;
    distance = r_u32(object + 44u) - 128u;
    if ((sint32)distance < 0) distance = 0u - distance;
    factor = 128u - distance;
    for (i = 3u; i != 0u; --i) {
        product = (sint32)(factor * r_u8(object + 35u + i));
        color = (sint32)((uint32)r_u8(0x80065983u + i) + (uint32)(product / 128));
        channel[i - 1u] = color < 255 ? (uint32)color : 255u;
    }
    w_u32(0x80065984u, (channel[2] << 16) | (channel[1] << 8) | channel[0]);
    progress = r_u32(object + 44u) + r_u8(object + 39u) * ticks;
    w_u32(object + 44u, progress);
    if ((sint32)progress < 256) return 0u;
    sub_800205F8(object);
    return 0xFFFFFFFFu;
}

uint32 sub_8003FEA8(uint32 position, uint32 color)
{
    uint32 effect;
    FUNCTION_MARKER(0x8003FEA8u, "SLUS_005.10");
    if (r_u32(0x80065314u) != 0u || sub_8001DB54(position, 0u) == 0u) return 0u;
    effect = sub_8001D470(128u);
    w_u32(effect, 160u);
    w_u32(effect + 44u, 128u);
    w_u32(effect + 36u, color);
    w_u32(effect + 100u, 0x8003EE88u);
    sub_800202F4(effect);
    return effect;
}

uint32 sub_8003C61C(uint32 object, uint32 mode, uint32 value)
{
    uint32 vehicle, asset, kind, target, callback = 0u, key = 0u, weapon, descriptor, respawn;
    uint32 voice, sample, i, flags;
    sint32 model = -1, current, capacity, grant, remaining;
    FUNCTION_MARKER(0x8003C61Cu, "SLUS_005.10");
    if (mode == 0u) {
        w_u16(object + 66u, r_u16(object + 66u) + 68u);
        if (value != 0u) sub_8001D708(object);
        return 0u;
    }
    if (mode == 1u) {
        asset = r_u32(object + 88u);
        flags = r_u32(object);
        capacity = (sint32)r_u32(object + 108u);
        w_u32(0x80065BB8u, asset);
        w_u8(object + 4u, 3u);
        w_u32(object, (flags | 0x380u) & ~8u);
        if (capacity == 0) w_u32(object + 108u, 2048000u);
        if (r_u16(object + 10u) == 13u)
            w_u16(object + 10u, r_u16(0x8005EC84u + load_random_pickup(r_u32(object), 13u) * 2u));
        return 0u;
    }
    if (mode == 2u) {
        if (r_u8(object + 4u) == 3u) {
            sub_8003FD24(object + 72u, 23u);
            sub_800205F8(object);
        } else w_u32(object, r_u32(object) & ~0x8000u);
        return 0xFFFFFFFFu;
    }
    if (mode != 3u) return 0u;
    vehicle = r_u32(value);
    kind = r_u8(vehicle + 4u);
    if (kind != 2u) return kind == 7u;
    asset = r_u32(0x800737DCu);
    kind = (sint8)r_u8(object + 8u) != 0 && (sint16)r_u16(vehicle + 6u) > 0 ? 14u : r_u16(object + 10u);
    if (kind >= 15u) return 0u;
    target = r_u32(0x80010AD0u + kind * 4u);
    switch (target) {
    case 0x8003C6FCu:
        if (r_u8(vehicle + 208u) == 12u) {
            capacity = r_u16(vehicle + 14u);
            current = r_u16(vehicle + 12u) + 375;
            w_u16(vehicle + 12u, current < capacity ? current : capacity);
        } else {
            remaining = 500;
            for (i = 0u; i < 2u; ++i) {
                descriptor = r_u32(vehicle + 236u + i * 4u);
                current = r_u16(descriptor + 12u);
                capacity = r_u16(vehicle + 12u) - current;
                grant = capacity < remaining ? capacity : remaining;
                w_u16(descriptor + 12u, current + grant);
                remaining -= grant;
            }
            descriptor = r_u32(vehicle + 244u);
            current = r_u16(descriptor + 12u) + remaining;
            capacity = r_u16(vehicle + 12u);
            w_u16(descriptor + 12u, current < capacity ? current : capacity);
        }
        sample = 39u;
        break;
    case 0x8003C7CCu: w_u16(vehicle + 284u, 900u); sample = 38u; break;
    case 0x8003C7D8u: w_u16(vehicle + 288u, 900u); sample = 38u; break;
    case 0x8003C7E4u: w_u16(vehicle + 286u, 900u); sample = 38u; break;
    case 0x8003C86Cu: callback = 0x8003302Cu; model = 17; key = 0x8012u; goto equip;
    case 0x8003C880u: callback = 0x80031FA0u; model = 0; key = 0x8011u; goto equip;
    case 0x8003C894u: callback = 0x800336FCu; model = 7; key = 0x8013u; goto equip;
    case 0x8003C8A8u: callback = 0x80034920u; model = 10; key = 0x8014u; goto equip;
    case 0x8003C8BCu: callback = 0x8003565Cu; model = 13; key = 0x8015u; goto equip;
    case 0x8003C8D0u:
        descriptor = sub_8001B038(vehicle, 0x801Fu);
        key = 0x801Fu;
        asset = r_u32(vehicle + 88u);
        callback = sub_8003D1E8(r_u8(vehicle + 208u));
        model = descriptor != 0u && callback != 0u ? (sint16)r_u16(descriptor + 26u) : -1;
        goto equip;
    case 0x8003CB3Cu: return 0u;
    default:
        /* TODO Translate an unknown changed jump-table destination */
        fprintf(stderr, "Missing pickup jump target %08X\n", target);
        abort();
        return 0u;
    }
    voice = sub_8004410C();
    sub_8004483C(voice, r_u32(0x800658FCu), sample, object + 36u);
    if ((sint16)r_u16(vehicle + 6u) == -1) sub_8003FEA8(vehicle + 36u, 0x08404040u);
    sub_800205F8(object);
    respawn = sub_8001FFD4(0x80065A50u, (uint32)(sint32)(sint16)r_u16(object + 6u));
    if (respawn != 0u) {
        sub_80020890(respawn, 600u);
        w_u32(0x80065AACu, r_u32(0x80065AACu) - 1u);
    }
    return 0xFFFFFFFEu;
equip:
    if (model >= 0) {
        voice = sub_8004410C();
        sub_8004483C(voice, r_u32(0x800658FCu), 37u, object + 36u);
        if ((sint16)r_u16(vehicle + 6u) == -1) sub_8003FEA8(vehicle + 36u, 0x08404040u);
        weapon = sub_8001AC44(asset, (uint32)model & 0xFFFFu, 132u, 8u);
        w_u32(weapon, 0x10000u);
        w_u32(weapon + 100u, callback);
        if (callback != 0u) v8_native_terrain_call3(callback, weapon, 1u, 0u);
        w_u16(weapon + 14u, r_u16(weapon + 12u));
        if (r_u16(object + 12u) != 0u) w_u16(weapon + 12u, r_u16(object + 12u));
        descriptor = sub_8001B038(vehicle, key);
        w_u32(weapon + 128u, descriptor);
        w_u32(weapon + 64u, r_u32(descriptor + 16u));
        w_u16(weapon + 68u, r_u16(descriptor + 20u));
        for (i = 0u; i < 3u; ++i)
            w_u32(weapon + 72u + i * 4u, r_u32(object + 72u + i * 4u) - r_u32(vehicle + 72u + i * 4u));
        sub_8001D708(weapon);
        sub_80020744(weapon);
        sub_8002CBE8(vehicle, weapon);
    }
    sub_800205F8(object);
    respawn = sub_8001FFD4(0x80065A50u, (uint32)(sint32)(sint16)r_u16(object + 6u));
    if (respawn != 0u) {
        sub_80020890(respawn, 600u);
        w_u32(0x80065A10u, r_u32(0x80065A10u) - 1u);
    }
    return 0xFFFFFFFEu;
}

uint32 v8_native_terrain_call3(uint32 callback, uint32 object, uint32 mode, uint32 value)
{
    if (callback == 0x8003E80Cu)
        return (uint32)v8_native_3E80C(object, mode);
    uint32 target, result;
    if (callback == 0x8003302Cu)
        return sub_8003302C(object, mode, value);
    if (callback == 0x8002A4E4u)
        return sub_8002A4E4(object, mode, value);
    if (callback == 0x80034920u)
        return sub_80034920(object, mode, value);
    if (callback == 0x800336FCu)
        return sub_800336FC(object, mode, value);
    if (callback == 0x8003565Cu)
        return sub_8003565C(object, mode, value);
    if (callback == 0x8003EE88u)
        return sub_8003EE88(object, mode, value);
    if (callback == 0x8004042Cu)
        return sub_8004042C(object, mode);
    if (callback == 0x80031864u)
        return sub_80031864(object, mode, value);
    if (callback == 0x8002A3E8u)
        return sub_8002A3E8(object, mode, value);
    if (callback == 0x80031634u)
        return sub_80031634(object, mode, value);
    if (callback == 0x8003D214u)
        return sub_8003D214(object, mode);
    if (callback == 0x8002E2BCu)
        return sub_8002E2BC(object, mode, value);
    if (callback == 0x800223DCu)
        return load_default_object_callback(object, mode, value);
    if (callback == 0x80022CB0u) {
        if (mode == 1u) {
            w_u32(0x80065ADCu, object);
            return 0xFFFFFFFFu;
        }
        return 0u;
    }
    if (callback == 0x8003C61Cu)
        return sub_8003C61C(object, mode, value);
    if (ski_module != 0u && callback == ski_module + 0x19D8u) {
        uint32 other, x, z;
        if (mode == 3u) {
            other = r_u32(value);
            result = r_u8(other + 4u) == 7u ? load_default_damage(object, r_u16(other + 12u)) : 0u;
        } else if (mode == 8u)
            result = load_default_damage(object, value);
        else
            return 0u;
        if (result == 0u)
            return 0u;
        x = r_u32(object + 72u);
        if ((sint32)x < 0)
            x += 0xFFFFu;
        x = (uint16)((sint32)x >> 16u);
        z = r_u32(object + 80u);
        if ((sint32)z < 0)
            z += 0xFFFFu;
        z = (uint16)((sint32)z >> 16u);
        /* TODO Translate the complete terrain rectangle update */
        fprintf(stderr, "TODO SkiResrt19D8 sub_80024718 rect=(%d,%d,1,1) flags0\n",
            (int)(sint16)x, (int)(sint16)z);
        abort();
    }
    if (ski_module != 0u && callback == ski_module + 0x16ACu) {
        uint32 child, x, y, z, velocity, adjusted;
        if (mode >= 9u)
            return 0u;
        target = r_u32(ski_module + 0x118u + mode * 4u) - ski_module;
        if (target == 0x19B4u)
            return 0u;
        if (target == 0x194Cu) {
            result = r_u8(object + 9u) & 7u;
            child = r_u32(object) | 128u;
            velocity = r_u32(object + 84u);
            w_u8(object + 8u, result);
            w_u32(object, child);
            w_u32(object + 84u, (sint32)velocity > 0x40000 ? velocity : 0x40000u);
            result = load_allocate_voice();
            child = r_u32(object + 88u);
            w_u8(object + 5u, result);
            (void)sub_80044484((uint32)(sint32)(sint8)result, r_u32(child + 8u), 3u, 0u);
            return 0u;
        }
        if (target == 0x16F8u) {
            result = r_u8(object + 8u) - 1u;
            w_u8(object + 8u, result);
            if ((sint8)result == -1) {
                MATRIX local, composed;
                SVECTOR angles;
                VECTOR translation;
                uint32 parent = r_u32(object + 56u), descriptor, speed, particle, j, product;
                speed = (uint32)((sint32)(sub_80017160() << 8) >> 15) + 4096u;
                descriptor = sub_8001B038(parent, 0x8000u);
                angles.vx = (sint16)r_u16(descriptor + 16u);
                angles.vy = (sint16)r_u16(descriptor + 18u);
                angles.vz = (sint16)r_u16(descriptor + 20u); angles.pad = 0;
                RotMatrix(&angles, &local);
                translation.vx = (sint32)r_u32(descriptor + 4u);
                translation.vy = (sint32)r_u32(descriptor + 8u);
                translation.vz = (sint32)r_u32(descriptor + 12u);
                TransMatrix(&local, &translation);
                CompMatrixLV((MATRIX *)psx_addr(parent + 16u, sizeof(MATRIX)), &local, &composed);
                particle = sub_8001AC44(r_u32(0x800737D8u), 32u, 160u, 8u);
                w_u32(particle, r_u32(particle) | 0x410u);
                for (j = 0u; j < 3u; ++j) {
                    product = (uint32)(sint32)composed.m[j][2] * speed;
                    w_u32(particle + 136u + j * 4u, (uint32)((sint32)product / 4096));
                }
                angles.vx = 0; angles.vy = 0; angles.vz = (sint16)sub_80017160();
                RotMatrix(&angles, (MATRIX *)psx_addr(particle + 16u, sizeof(MATRIX)));
                for (j = 0u; j < 3u; ++j) w_u32(particle + 36u + j * 4u, (uint32)composed.t[j]);
                w_u32(particle + 100u, 0x8004042Cu);
                (void)sub_8001D4F0(object, particle);
                w_u8(object + 8u, 8u);
            }
            child = r_u32(r_u32(object + 56u) + 52u);
            while (child != 0u) {
                x = r_u32(child + 36u) + r_u32(child + 136u);
                y = r_u32(child + 40u) + r_u32(child + 140u);
                z = r_u32(child + 44u) + r_u32(child + 144u);
                velocity = r_u32(child + 136u);
                w_u32(child + 36u, x);
                w_u32(child + 40u, y);
                w_u32(child + 44u, z);
                adjusted = (sint32)velocity < 0 ? velocity + 63u : velocity;
                w_u32(child + 136u, velocity - (uint32)((sint32)adjusted >> 6u));
                velocity = r_u32(child + 144u);
                adjusted = (sint32)velocity < 0 ? velocity + 63u : velocity;
                y = r_u32(child + 140u);
                w_u32(child + 144u, velocity - (uint32)((sint32)adjusted >> 6u));
                w_u32(child + 140u, y + 56u);
                child = r_u32(child + 52u);
            }
            if (value == 0u)
                return 0u;
            result = sub_800449BC(object + 36u);
            sub_80044574((uint32)(sint32)(sint8)r_u8(object + 5u), result);
            return 0u;
        }
        if (target == 0x1908u || target == 0x191Cu) {
            if (target == 0x1908u) {
                child = r_u32(value);
                result = r_u8(child + 4u) == 7u ? load_default_damage(object, r_u16(child + 12u)) : 0u;
            } else
                result = load_default_damage(object, value);
            if (result == 0u)
                return 0u;
            /* TODO Translate original unlink and voice release dependencies */
            fprintf(stderr, "TODO SkiResrt16AC sub_80020778/sub_800441C8 object=%08X\n", object);
            abort();
        }
        /* TODO Translate voice release or a modified dispatch target */
        fprintf(stderr, "TODO SkiResrt16AC dispatch offset=%08X mode=%u\n", target, mode);
        abort();
    }
    if (ski_module != 0u && callback == ski_module + 0x1EFCu) {
        uint32 child, product, x, y, z;
        if (mode == 1u) {
            w_u32(object, r_u32(object) | 0x22u);
            return 0u;
        }
        if (mode != 9u || value != (uint32)(sint32)(sint16)r_u16(object + 6u))
            return 0u;
        target = r_u32(0x800659FCu);
        if ((sint32)r_u32(target + 148u) >= 24)
            return 0u;
        child = sub_8001AC44(r_u32(object + 88u), r_u16(object + 10u), 152u, 0u);
        (void)sub_8001DC1C(child);
        product = r_u32(child + 84u) * 2364u;
        if ((sint32)product < 0)
            product += 4095u;
        w_u32(child + 84u, (uint32)((sint32)product >> 12u));
        w_u16(child + 6u, 1000u);
        w_u8(child + 9u, sub_80017160());
        result = r_u32(child) | 0x180u;
        w_u16(child + 12u, r_u16(object + 14u));
        w_u32(child, result);
        x = r_u32(object + 72u);
        y = r_u32(object + 76u);
        z = r_u32(object + 80u);
        w_u32(child + 72u, x);
        w_u32(child + 76u, y);
        w_u32(child + 80u, z);
        product = r_u32(child + 84u);
        w_u32(child + 100u, ski_module + 0x1A94u);
        w_u32(child + 132u, 0xFFFFF415u);
        product *= 12867u;
        if ((sint32)product < 0)
            product += 4095u;
        result = (uint32)load_divide(0x1000000, (sint32)product >> 12u);
        w_u16(child + 148u, result);
        (void)sub_8001D708(child);
        (void)load_insert_active_object(child);
        target = r_u32(0x800659FCu);
        w_u32(target + 148u, r_u32(target + 148u) + 1u);
        return 0u;
    }
    if (ski_module != 0u && callback == ski_module + 0x16Cu) {
        uint32 child, index, x, y, z, dx, dy, dz, oldx, oldy, oldz;
        if (mode == 7u) {
            result = sub_8001D470(128u);
            w_u32(result + 88u, object);
            w_u16(result + 10u, value);
            return result;
        }
        if (mode == 1u) {
            if ((sint8)r_u8(0x80065319u) >= 3) {
                sub_80045088(object);
                return 0xFFFFFFFFu;
            }
            w_u32(object, r_u32(object) | 0xA0u);
            for (index = 0u; index < 64u; ++index) {
                child = sub_8001AC44(r_u32(object + 88u), r_u16(object + 10u), 128u, 0u);
                w_u32(child, r_u32(child) | 0x410u);
                result = sub_80017160() << 17u;
                w_u32(child + 72u, (uint32)((sint32)result >> 13u));
                result = sub_80017160() << 17u;
                w_u32(child + 76u, (uint32)((sint32)result >> 13u));
                result = sub_80017160() << 17u;
                w_u32(child + 80u, (uint32)((sint32)result >> 13u));
                result = sub_80017160();
                target = r_u32(child + 48u);
                w_u16(child + 68u, result);
                w_u16(target + 40u, 64u);
                (void)sub_8001D708(child);
                (void)sub_8001D4F0(object, child);
            }
            return 0u;
        }
        if (mode != 0u || value == 0u)
            return 0u;
        child = r_u32(object + 56u);
        x = r_u32(0x8006F6F4u) + ((uint32)(sint32)(sint16)r_u16(0x8006F6E4u) << 6u);
        y = r_u32(0x8006F6F8u) + ((uint32)(sint32)(sint16)r_u16(0x8006F6EAu) << 6u);
        z = r_u32(0x8006F6FCu) + ((uint32)(sint32)(sint16)r_u16(0x8006F6F0u) << 6u);
        oldx = r_u32(object + 36u);
        oldy = r_u32(object + 40u);
        oldz = r_u32(object + 44u);
        w_u32(object + 36u, x);
        dx = oldx - x;
        dy = oldy - y + value * 762u;
        dz = oldz - z;
        w_u32(object + 40u, y);
        w_u32(object + 44u, z);
        while (child != 0u) {
            x = ((r_u32(child + 36u) + dx + 0x20000u) & 0x3FFFFu) - 0x20000u;
            y = ((r_u32(child + 40u) + dy + 0x20000u) & 0x3FFFFu) - 0x20000u;
            z = ((r_u32(child + 44u) + dz + 0x20000u) & 0x3FFFFu) - 0x20000u;
            w_u32(child + 36u, x);
            w_u32(child + 40u, y);
            w_u32(child + 44u, z);
            child = r_u32(child + 52u);
        }
        return 0u;
    }
    if (ski_module != 0u && callback == ski_module + 0x1284u) {
        if (mode - 1u >= 8u)
            return 0u;
        target = r_u32(ski_module + 0xD0u + (mode - 1u) * 4u) - ski_module;
        if (target == 0x137Cu)
            return 0u;
        if (target == 0x1344u)
            return 132u;
        if (target == 0x1330u) {
            w_u32(object, r_u32(object) & ~32u);
            return 0u;
        }
        if (target == 0x134Cu) {
            result = r_u32(0x800659FCu);
            target = r_u32(result + 152u) != 0u;
            w_u32(object, r_u32(object) | 0x108u);
            w_u32(result + 152u + target * 4u, object);
            w_u16(object + 66u, target << 11u);
            return 0u;
        }
        if (target == 0x131Cu) {
            (void)load_default_damage(object, value);
            return 0u;
        }
        if (target == 0x12BCu) {
            result = r_u32(value);
            if (r_u8(result + 4u) == 3u && r_u32(object + 128u) != 0u) {
                w_u32(value, r_u32(object + 128u));
                target = r_u32(result + 100u);
                if (target != 0u)
                    (void)v8_native_terrain_call3(target, result, 3u, value);
                return 1u;
            }
            if (r_u8(result + 4u) == 7u)
                (void)load_default_damage(object, r_u16(result + 12u));
            return 0u;
        }
        /* TODO Resolve execution at a modified module dispatch target */
        fprintf(stderr, "TODO SkiResrt1284 dispatch offset=%08X mode=%u\n", target, mode);
        abort();
    }
    if (ski_module != 0u && callback == ski_module + 0x2094u) {
        result = 0u;
        if (mode == 3u) {
            target = r_u32(value);
            if (r_u8(target + 4u) == 7u)
                result = load_default_damage(object, r_u16(target + 12u)) != 0u;
        } else if (mode == 8u)
            result = load_default_damage(object, value);
        if (result == 0u)
            return 0u;
        result = sub_8003FC94(object);
        if (result != 0u)
            return result;
        result = r_u32(ski_module + 0x2154u) + 1u;
        w_u32(ski_module + 0x2154u, result);
        if ((result & 1u) == 0u)
            return 0u;
        target = ((r_u32(0x80065B34u) + r_u32(0x80065B38u)) >> 1u) < r_u32(object + 72u)
            ? 0x201u : 0x200u;
        /* TODO Translate the original gameplay event dependency */
        fprintf(stderr, "TODO SkiResrt2094 sub_80021924 event9 value=%08X\n", target);
        abort();
    }
    if (ski_module != 0u && callback == ski_module + 0x1424u) {
        if (mode == 1u) {
            load_lift_station_insert(object);
            w_u32(object + 100u, 0x800223DCu);
        }
        return 0u;
    }
    if (ski_module != 0u && callback == ski_module + 0x1464u) {
        if (mode == 1u)
            load_lift_station_insert(object);
        else if (mode == 3u && r_u16(r_u32(value + 12u) + 6u) == 0u) {
            target = r_u32(value);
            if (r_u8(target + 4u) == 2u && (sint16)r_u16(target + 6u) < 0 &&
                r_u16(r_u32(0x800659FCu) + 162u) != 0u) {
                /* TODO Translate the complete lift vehicle boarding branch */
                fprintf(stderr, "TODO SkiResrt1464 boarding object=%08X vehicle=%08X\n", object, target);
                abort();
            }
        }
        return load_default_object_callback(object, mode, value);
    }
    if (ski_module != 0u && callback == ski_module + 0x974u)
    {
        if (mode >= 18u)
            return 0u;
        target = r_u32(ski_module + 0x78u + mode * 4u);
        if (target == ski_module + 0xB2Cu) {
            load_ski_cables(object);
            return 0u;
        }
        if (target == ski_module + 0x1020u)
            return 0u;
        if (target == ski_module + 0x9D0u)
        {
            uint32 countdown = r_u16(object + 162u), phase, sled, table, i, changed = value;
            if (countdown != 0u) {
                countdown = (countdown - 1u) & 0xFFFFu;
                w_u16(object + 162u, countdown);
                if (countdown != 0u) return 0u;
                result = sub_8004410C();
                sled = r_u32(object + 152u);
                w_u8(object + 5u, result);
                table = r_u32(r_u32(sled + 88u) + 8u);
                (void)sub_800443C8((uint32)(sint32)(sint8)result, table, 0u, 0u, result);
                return 0u;
            }
            phase = r_u16(object + 160u) + 32u;
            w_u16(object + 160u, phase);
            if ((phase & 0x7FFFu) == 0u) {
                for (i = 0u; i < 2u; ++i) {
                    sled = r_u32(object + 152u + 4u * i);
                    w_u16(sled + 10u, r_u16(sled + 10u) | 0x2Cu);
                    (void)sub_8001BDDC(r_u32(sled + 48u), sled);
                    sled = r_u32(object + 152u + 4u * i);
                    table = r_u32(sled + 88u);
                    w_u16(sled + 10u, 0x2Cu);
                    result = sub_8001BDA0(table, 0x2Cu, i);
                    w_u32(r_u32(object + 152u + 4u * i) + 48u, result);
                }
                w_u16(object + 162u, 1200u);
                sub_800441C8((uint32)(sint32)(sint8)r_u8(object + 5u));
                w_u8(object + 5u, 0u);
                changed = 1u;
            }
            if (changed != 0u) {
                load_ski_place(r_u32(object + 152u), (uint32)(sint32)(sint16)r_u16(object + 160u));
                load_ski_place(r_u32(object + 156u), (uint32)(sint32)(sint16)(r_u16(object + 160u) + 0x8000u));
                result = sub_800446DC(r_u32(object + 152u) + 72u);
                result += sub_800446DC(r_u32(object + 156u) + 72u);
                sub_80044574((uint32)(sint32)(sint8)r_u8(object + 5u), result);
            }
            return 0u;
        }
        if (target == ski_module + 0xE6Cu)
        {
            uint32 head = r_u32(object + 128u), tail = r_u32(object + 136u);
            uint32 first = r_u32(head + 8u), last = r_u32(tail + 8u);
            uint32 origin = r_u32(first + 80u), next = r_u32(head), count = 0u, i, packet;
            sint32 span = (sint32)(r_u32(last + 80u) - origin) / 256;
            while (next != 0u) {
                uint32 point = r_u32(head + 8u);
                uint32 delta = r_u32(point + 80u) - origin;
                w_u32(head + 12u, (uint32)load_sound_divide((sint32)(delta * 112u), span));
                head = next;
                next = r_u32(head);
                ++count;
            }
            count <<= 1;
            packet = sub_8001178C(16u, count);
            w_u32(object + 140u, packet);
            packet = sub_8001178C(16u, count);
            w_u32(object + 144u, packet);
            for (i = 0u; (sint32)i < (sint32)count; ++i) {
                packet = r_u32(object + 140u) + i * 16u;
                w_u8(packet + 3u, 3u);
                w_u8(packet + 7u, 0x40u);
                packet = r_u32(object + 144u) + i * 16u;
                w_u8(packet + 3u, 3u);
                w_u8(packet + 7u, 0x40u);
            }
            w_u16(object + 162u, 1200u);
            w_u32(object, r_u32(object) | 0x80u);
            load_ski_place(r_u32(object + 152u), 0u);
            load_ski_place(r_u32(object + 156u), 0xFFFF8000u);
            result = sub_8001FFD4(0x80065A50u, 256u);
            result = sub_8003D080(0x7F000000u, result, result);
            w_u32(0x80065A10u, result != 0u);
            (void)sub_80023D00();
            (void)sub_80020890(object, 240u);
            return 0u;
        }
        if (target == ski_module + 0xFC0u)
        {
            (void)sub_80023D00();
            (void)sub_80020890(object, 240u);
            return 0u;
        }
        if (target == ski_module + 0xFDCu)
        {
            result = sub_8001D470(164u);
            w_u32(result + 128u, result + 132u);
            w_u32(result + 132u, 0u);
            w_u32(result + 136u, result + 128u);
            return result;
        }
        fprintf(stderr, "TODO SkiResrt callback974 branch %08X mode %u object %08X value %08X\n", target - ski_module, mode, object, value);
        abort();
    }
    fprintf(stderr, "TODO native terrain callback %08X mode %u\n", callback, mode);
    abort();
}

uint32 v8_native_11A38_host(uint32 table, const char *name)
{
    uint32 candidate, index;
    while (r_u32(table) != 0u)
    {
        candidate = r_u32(table);
        index = 0u;
        while (r_u8(candidate + index) == (uint8)name[index])
        {
            if (name[index] == '\0')
                return r_u32(table + 4u);
            ++index;
        }
        table += 8u;
    }
    return 0u;
}

uint32 v8_native_11AA8_host(uint32 slot, const char *name)
{
    return v8_native_11A38_host(r_u32(0x8001006Cu + (slot << 2u)), name);
}

static void load_185CC(uint32 image, uint32 parsed[5])
{
    uint32 flags = r_u32(image + 4u);
    parsed[0] = flags;
    if ((flags & 8u) != 0u)
    {
        parsed[1] = image + 12u;
        parsed[2] = image + 20u;
        image += r_u32(image + 8u);
    }
    else
    {
        parsed[2] = 0u;
        parsed[1] = 0u;
    }
    parsed[3] = image + 12u;
    parsed[4] = image + 20u;
}

void v8_native_19F44(uint32 x0, uint32 y0, uint32 x1, uint32 y1, uint32 color)
{
    uint32 packet[4];
    uint8 *bytes = (uint8 *)packet;
    bytes[3] = 3u;
    bytes[7] = 64u;
    xport_store_le16(bytes + 8u, (uint16)x0);
    xport_store_le16(bytes + 10u, (uint16)y0);
    xport_store_le16(bytes + 12u, (uint16)x1);
    xport_store_le16(bytes + 14u, (uint16)y1);
    bytes[4] = (uint8)color;
    bytes[5] = (uint8)(color >> 8u);
    bytes[6] = (uint8)(color >> 16u);
    (void)DrawPrim(packet);
}

static uint32 load_read_be32(uint32 *cursor)
{
    uint32 high = load_read_be16(cursor);
    return (high << 16u) | load_read_be16(cursor);
}

static void load_object_strength(uint32 object, uint32 source, uint32 bytes)
{
    uint32 cursor = source, first = load_read_be32(&cursor), second, factor;
    second = (sint32)bytes >= 5 ? load_read_be32(&cursor) : first;
    if (r_u8(object + 4u) == 5u && (sint16)r_u16(object + 6u) >= 0)
    {
        factor = (uint32)((sint32)(sint8)r_u8(0x8006531Au) + 2);
        first = (uint32)((sint32)(first * factor) / 4);
        second = (uint32)((sint32)(second * factor) / 4);
    }
    w_u16(object + 12u, first);
    w_u16(object + 14u, second);
    object = r_u32(object + 56u);
    while (object != 0u)
    {
        if (r_u16(object + 12u) == 0u)
            w_u16(object + 12u, first);
        object = r_u32(object + 52u);
    }
}

static void load_object_light(uint32 object, uint32 source)
{
    uint32 cursor = source, value;
    value = load_read_be32(&cursor);
    w_u32(object + 128u, value);
    value = load_read_be32(&cursor);
    w_u32(object + 132u, value);
    value = load_read_be32(&cursor);
    w_u32(object + 136u, value);
    value = load_read_be16(&cursor);
    w_u16(object + 140u, value);
    value = load_read_be16(&cursor);
    w_u16(object + 142u, value);
    value = load_read_be16(&cursor);
    w_u16(object + 144u, value);
}

static uint32 load_object_head(uint32 base, uint32 source, uint32 bytes)
{
    uint32 cursor = source, identity, type, identifier, flags, x, y, z;
    uint32 rotation0, rotation1, rotation2, asset_index, variant, strength;
    uint32 callback, target, asset, object, child, value, node, next, previous;
    char name[64];
    identity = r_u8(cursor++);
    type = r_u8(cursor++);
    identifier = load_read_be16(&cursor);
    flags = load_read_be32(&cursor) & 0xFFF867FEu;
    x = load_read_be32(&cursor);
    y = load_read_be32(&cursor) - 0x100000u;
    z = load_read_be32(&cursor);
    rotation0 = load_read_be16(&cursor);
    rotation1 = load_read_be16(&cursor);
    rotation2 = load_read_be16(&cursor);
    asset_index = (uint32)((sint32)(sint16)load_read_be16(&cursor) + 18);
    variant = load_read_be16(&cursor);
    strength = load_read_be32(&cursor);
    if (bytes < 34u || bytes - 34u >= sizeof(name)) {
        /* TODO Resolve original local-name overflow effects */
        fprintf(stderr, "TODO Load6F0 HEAD name extent bytes=%u\n", bytes);
        abort();
    }
    for (value = 0u; value < bytes - 34u; ++value)
        name[value] = (char)r_u8(cursor + value);
    name[value] = 0;
    callback = v8_native_11AA8_host(0u, name);
    if (callback == 0u)
        callback = v8_native_11A38_host(r_u32(r_u32(0x80065A38u) + 4u), name);
    if (callback == 0u)
        callback = 0x800223DCu;
    if ((flags & 4u) != 0u) {
        value = sub_80017160();
        asset = r_u32(0x800737A0u + asset_index * 4u);
        value *= r_u32(r_u32(asset + 4u));
        w_u16(0x800659D0u, (uint32)((sint32)value >> 15));
    }
    if (type >= 7u)
        return 0u;
    target = r_u32(base + 8u + type * 4u) - base;
    if (target == 0x8ACu || target == 0xA08u) {
        asset = r_u32(0x800737A0u + asset_index * 4u);
        object = v8_native_21B80(callback, asset, variant & 0xFFFFu, (flags << 1u) & 8u);
    } else if (target == 0xAD4u) {
        object = sub_8001D470(128u);
        w_u32(object + 100u, callback);
        asset = r_u32(0x800737A0u + asset_index * 4u);
        w_u16(object + 10u, variant);
        w_u32(object, flags);
        w_u8(object + 4u, type);
        w_u16(object + 6u, identifier);
        w_u8(object + 8u, identity);
        w_u32(object + 88u, asset);
    } else if (target == 0xC70u)
        object = sub_8001D470(148u);
    else {
        /* TODO Resolve execution at modified dispatch targets */
        fprintf(stderr, "TODO Load6F0 dispatch offset=%08X\n", target);
        abort();
    }
    if (target != 0xAD4u) {
        w_u32(object, flags);
        w_u8(object + 4u, type);
        w_u16(object + 6u, identifier);
        w_u8(object + 8u, identity);
    }
    w_u32(object + 72u, x);
    w_u32(object + 76u, y);
    w_u32(object + 80u, z);
    w_u32(object + 64u, rotation0 | (rotation1 << 16u));
    w_u16(object + 68u, rotation2);
    if (target == 0xC70u) {
        w_u8(object + 9u, sub_80017160());
        (void)sub_8001D708(object);
        (void)sub_8001FE50(base + 0x7D90u, object);
        return object;
    }
    value = strength;
    if (target == 0xAD4u && (sint16)identifier >= 0) {
        value *= (uint32)((sint32)(sint8)r_u8(0x8006531Au) + 2);
        if ((sint32)value < 0)
            value += 3u;
        value >>= 2u;
    }
    w_u16(object + 14u, value);
    w_u16(object + 12u, value);
    if (target == 0xA08u) {
        child = r_u32(object + 56u);
        while (child != 0u) {
            w_u16(child + 14u, strength);
            w_u16(child + 12u, strength);
            child = r_u32(child + 52u);
        }
    }
    w_u8(object + 9u, sub_80017160());
    if (target != 0xAD4u)
        w_u32(object + 100u, callback);
    (void)sub_8001D708(object);
    if (target == 0xAD4u) {
        node = r_u32(0x80065A50u);
        next = r_u32(node);
        while (next != 0u) {
            child = r_u32(node + 8u);
            if ((sint16)r_u16(child + 6u) >= (sint16)identifier)
                break;
            node = next;
            next = r_u32(node);
        }
        if (next != 0u && r_u16(r_u32(node + 8u) + 6u) == (uint16)identifier) {
            child = r_u32(node + 8u);
            while (r_u32(child + 52u) != 0u)
                child = r_u32(child + 52u);
            w_u32(child + 52u, object);
            w_u32(object + 60u, child);
        } else {
            value = sub_80022C54(object);
            previous = r_u32(node + 4u);
            w_u32(previous, value);
            w_u32(node + 4u, value);
            w_u32(value, node);
            w_u32(value + 4u, previous);
        }
        return object;
    }
    (void)sub_8001DC1C(object);
    callback = r_u32(object + 100u);
    value = callback != 0u ? v8_native_terrain_call3(callback, object, 1u, 0u) : 0u;
    if ((sint32)value < 0)
        return 0u;
    if (target == 0x8ACu)
        (void)load_build_collision_model(object);
    if ((r_u32(object) & 8u) != 0u && r_u32(object + 112u) == 0u) {
        /* Carry the addressable local through the native x86 ABI */
        value = sub_8001BDA0(r_u32(0x800737D4u), 13u, (uint32)(uintptr_t)name);
        sub_8003E598(object, value);
    }
    if (target == 0xA08u) {
        value = load_insert_active_object(object);
        if (value == 0u)
            return 0u;
        (void)load_build_collision_model(object);
    } else {
        if ((r_u32(object) & 4u) != 0u)
            (void)sub_8001FE50(0x80065A80u, object);
        if ((r_u32(object) & 128u) != 0u)
            (void)sub_8001FE50(0x80065A60u, object);
        (void)sub_8001EC48(object);
        (void)sub_8001FE50(base + 0x7DA0u, object);
    }
    return object;
}

static void load_objects(uint32 base, uint32 bytes)
{
    uint32 remaining = bytes, header[2], object = 0u, chunk, tag;
    if (remaining == 0u)
        return;
    do {
        chunk = sub_800225D4(header, &remaining);
        tag = (header[0] >> 24u) | ((header[0] >> 8u) & 0xFF00u) |
              ((header[0] & 0xFF00u) << 8u) | (header[0] << 24u);
        if (tag == 0x48454144u)
            object = load_object_head(base, chunk, header[1]);
        else if (tag == 0x5354524Eu && object != 0u)
            load_object_strength(object, chunk, header[1]);
        else if (tag == 0x4C474854u && object != 0u)
            load_object_light(object, chunk);
        sub_80045088(chunk);
    } while (remaining != 0u);
}

static uint32 load_bsp_node(uint32 *cursor)
{
    uint32 kind = load_read_be16(cursor), node, value;
    if (kind == 0u) {
        node = sub_800116F4(16u);
        w_u32(node + 4u, node + 8u);
        w_u32(node, 0u);
        w_u32(node + 8u, 0u);
        w_u32(node + 12u, node + 4u);
        return node;
    }
    if (kind >= 3u)
        return 0u;
    node = sub_800116F4(16u);
    w_u32(node, kind);
    value = load_read_be32(cursor);
    w_u32(node + 4u, value);
    value = load_bsp_node(cursor);
    w_u32(node + 8u, value);
    value = load_bsp_node(cursor);
    w_u32(node + 12u, value);
    return node;
}

static void load_road_segment(uint32 source, uint32 bytes)
{
    uint32 cursor = source, segment = sub_800116F4(32u), value, junction;
    if (bytes == 22u) {
        value = r_u8(cursor++);
        w_u16(segment + 10u, value);
        value = r_u8(cursor++);
        w_u16(segment + 8u, value);
        w_u16(segment + 12u, 0u);
    } else {
        value = load_read_be16(&cursor);
        w_u16(segment + 10u, value);
        value = load_read_be16(&cursor);
        w_u16(segment + 8u, value);
        value = load_read_be16(&cursor);
        w_u16(segment + 12u, value);
    }
    value = load_read_be16(&cursor);
    w_u32(segment, r_u32(r_u32(0x80065BD8u) + value * 4u));
    value = load_read_be16(&cursor);
    w_u32(segment + 4u, r_u32(r_u32(0x80065BD8u) + value * 4u));
    value = load_read_be32(&cursor);
    w_u32(segment + 16u, value);
    value = load_read_be32(&cursor);
    w_u32(segment + 20u, value);
    value = load_read_be32(&cursor);
    w_u32(segment + 24u, value);
    value = load_read_be32(&cursor);
    w_u32(segment + 28u, value);
    junction = r_u32(segment);
    while (r_u32(junction + 28u) != 0u)
        junction += 4u;
    w_u32(junction + 28u, segment);
    junction = r_u32(segment + 4u);
    while (r_u32(junction + 28u) != 0u)
        junction += 4u;
    w_u32(junction + 28u, segment);
}

static void load_junction_color(uint32 base, uint32 destination, uint32 primitive, uint32 vertex, uint32 normal)
{
    uint32 x, z, zone, value;
    xport_gte_write_data(0u, r_u32(vertex));
    xport_gte_write_data(1u, r_u32(vertex + 4u));
    xport_gte_execute(0x00480012u);
    x = (uint32)((sint32)xport_gte_read_data(25u) / 65536);
    z = (uint32)((sint32)xport_gte_read_data(27u) / 65536);
    zone = r_u32(0x800911A0u + (z >> 6u) * 4u + (x >> 6u) * 128u);
    value = (r_u16(zone + (z & 63u) * 2u + (x & 63u) * 128u) >> 11u) << 2u;
    w_u8(destination + 2u, value);
    w_u8(destination + 1u, value);
    w_u8(destination, value);
}

static void load_junction(uint32 base, uint32 source, uint32 bytes)
{
    uint32 cursor = source, x, z, kind, count, junction, index, value, model, input, output, shift, table;
    uint32 angle, sine, cosine, first, second, height;
    MATRIX identity;
    x = load_read_be32(&cursor);
    z = load_read_be32(&cursor);
    kind = r_u8(cursor++);
    count = r_u8(cursor++);
    junction = sub_800116F4(count * 4u + 28u);
    w_u16(junction + 16u, kind);
    w_u32(junction, x);
    w_u32(junction + 8u, z);
    w_u16(junction + 18u, count);
    if ((kind & 2u) != 0u)
    {
        value = load_read_be32(&cursor);
        w_u32(junction + 4u, value - 0x100000u);
        bytes -= 4u;
    }
    else
        w_u32(junction + 4u, sub_80025400(x, z));
    for (index = 0u; index < count; ++index)
        w_u32(junction + 28u + index * 4u, 0u);
    if ((sint32)bytes >= 11)
    {
        (void)v8_native_16DA8(&identity);
        SetRotMatrix(&identity);
        value = r_u32(junction + 4u);
        xport_gte_write_control(5u, x);
        xport_gte_write_control(6u, value);
        xport_gte_write_control(7u, z);
        value = load_read_be16(&cursor);
        w_u32(junction + 12u, r_u32(0x800737A0u + (value + 18u) * 4u));
        value = load_read_be16(&cursor);
        w_u16(junction + 20u, value);
        value = load_read_be16(&cursor);
        w_u16(junction + 22u, value);
        model = sub_8001BDA0(r_u32(junction + 12u), r_u16(junction + 20u), junction);
        w_u32(junction + 24u, model);
        w_u16(model + 40u, 16u);
        model = r_u32(junction + 24u);
        shift = 16u - r_u16(model + 38u);
        input = r_u32(model + 8u);
        output = sub_800116F4(r_u32(model + 4u) * 8u);
        w_u32(r_u32(junction + 24u) + 8u, output);
        index = 0u;
        while ((sint32)index < (sint32)r_u32(r_u32(junction + 24u) + 4u))
        {
            angle = r_u16(junction + 22u) & 4095u;
            cosine = (uint32)(sint32)(sint16)r_u16(0x800607B6u + angle * 4u);
            sine = (uint32)(sint32)(sint16)r_u16(0x800607B4u + angle * 4u);
            first = cosine * (uint32)(sint32)(sint16)r_u16(input);
            second = sine * (uint32)(sint32)(sint16)r_u16(input + 4u);
            w_u16(output, (uint32)((sint32)(first + second) / 4096));
            angle = r_u16(junction + 22u) & 4095u;
            sine = (uint32)(sint32)(sint16)r_u16(0x800607B4u + angle * 4u);
            cosine = (uint32)(sint32)(sint16)r_u16(0x800607B6u + angle * 4u);
            first = (0u - sine) * (uint32)(sint32)(sint16)r_u16(input);
            second = cosine * (uint32)(sint32)(sint16)r_u16(input + 4u);
            value = (uint32)((sint32)(first + second) / 4096);
            first = (uint32)(sint32)(sint16)r_u16(output);
            w_u16(output + 4u, value);
            x = r_u32(junction);
            z = r_u32(junction + 8u);
            value = (uint32)(sint32)(sint16)value;
            height = sub_80025400(x + (first << (shift & 31u)), z + (value << (shift & 31u)));
            height -= r_u32(junction + 4u);
            w_u16(output + 2u, (uint32)((sint32)height >> (shift & 31u)));
            input += 8u;
            output += 8u;
            ++index;
        }
        v8_native_load_process_packets(base, r_u32(junction + 24u), load_junction_color);
        model = r_u32(junction + 24u);
        w_u16(model, (r_u16(model) & 0xFFFEu) | 4u);
    }
    else
        w_u32(junction + 24u, 0u);
    table = r_u32(0x80065BD8u);
    index = 0u;
    while (r_u32(table + index * 4u) != 0u)
        ++index;
    w_u32(r_u32(0x80065BD8u) + index * 4u, junction);
}

static void load_road_texture(uint32 source, uint32 bytes)
{
    uint32 record = r_u32(0x80065BD4u), cursor = source, high, low, value, parsed[5], allocation, index;
    sint32 first, second, width;
    PSX_RECT rectangle;
    uint16 colors[256];
    while (r_u32(record + 36u) != 0u)
        record += 52u;
    high = load_read_be16(&cursor);
    low = load_read_be16(&cursor);
    w_u32(record + 36u, (high << 16u) | low);
    high = load_read_be16(&cursor);
    low = load_read_be16(&cursor);
    w_u32(record + 40u, (high << 16u) | low);
    w_u32(record + 28u, load_read_be16(&cursor));
    w_u16(record + 44u, load_read_be16(&cursor));
    w_u32(record + 20u, 0u);
    w_u32(record + 12u, 0u);
    w_u32(record + 16u, 0u);
    first = (sint32)r_u32(record + 36u) / 256;
    second = (sint32)r_u32(record + 40u) / 256;
    value = (uint32)((sint32)((uint32)first * (uint32)second) / 128);
    w_u16(record + 46u, value);
    if ((sint32)r_u32(record + 28u) < 16)
        w_u32(record + 28u, 32u);
    if ((sint32)bytes >= 13)
    {
        v8_native_187E4(cursor, (uint8 *)psx_addr(record, 12u));
        /* The original returns its shared TIM context from 187E4 */
        parsed[1] = r_u32(0x8006F62Cu);
        parsed[2] = r_u32(0x8006F630u);
        (void)sub_8001859C(r_u16(record + 10u));
        width = (sint16)r_u16(parsed[1] + 4u);
        allocation = sub_80018124((uint32)width, 17u, 16u, 1u, (uint32)width, 1u);
        memcpy(&rectangle, psx_addr(allocation, sizeof(rectangle)), sizeof(rectangle));
        rectangle.h = 1;
        w_u16(record + 10u, GetClut(rectangle.x, rectangle.y));
        SetFarColor(r_u8(0x80065B2Cu), r_u8(0x80065B2Du), r_u8(0x80065B2Eu));
        for (index = 0u; index < 16u; ++index)
        {
            load_palette(parsed[2], rectangle.w, colors, index * 256u);
            (void)LoadImagePSX(&rectangle, (uint32 *)colors);
            rectangle.y = (sint16)((uint16)rectangle.y + 1u);
        }
        (void)LoadImagePSX(&rectangle, (uint32 *)colors);
    }
}

static void load_background(uint32 source)
{
    uint32 parsed[5], rectangle, value, index, packet, copy[3];
    const uint32 texture = 0x80065B18u;
    v8_native_187E4(source, (uint8 *)psx_addr(texture, 12u));
    load_185CC(source, parsed);
    rectangle = parsed[3];
    value = ((uint32)(sint32)(sint16)r_u16(rectangle + 2u) -
             (uint32)(sint32)(sint16)r_u16(rectangle + 6u)) << 4u;
    w_u16(0x8005E9C6u, value);
    w_u16(0x8005E9BEu, value);
    w_u16(0x8005E9B6u, value);
    value = (uint32)(sint32)(sint16)r_u16(rectangle + 2u) << 4u;
    w_u16(0x8005E9DEu, value);
    w_u16(0x8005E9D6u, value);
    w_u16(0x8005E9CEu, value);
    for (index = 0u; index < 2u; ++index)
    {
        packet = 0x80091020u + index * 80u;
        w_u8(packet + 3u, 9u);
        w_u8(packet + 7u, 44u);
        w_u8(packet + 43u, 9u);
        w_u8(packet + 47u, 44u);
        w_u8(packet + 7u, r_u8(packet + 7u) | 1u);
        w_u8(packet + 47u, r_u8(packet + 47u) | 1u);
        value = r_u16(texture + 10u);
        w_u16(packet + 54u, value);
        w_u16(packet + 14u, value);
        value = r_u16(texture + 8u);
        w_u16(packet + 62u, value);
        w_u16(packet + 22u, value);
        /* Write both packet UV groups in original order */
        w_u8(packet + 12u, r_u8(texture + 6u));
        w_u8(packet + 13u, r_u16(texture + 6u) >> 8u);
        w_u8(packet + 20u, r_u8(texture + 2u) + r_u8(texture + 6u) + 255u);
        w_u8(packet + 21u, r_u16(texture + 6u) >> 8u);
        w_u8(packet + 28u, r_u8(texture + 6u));
        w_u8(packet + 29u, r_u8(texture + 4u) + (r_u16(texture + 6u) >> 8u) + 255u);
        w_u8(packet + 36u, r_u8(texture + 2u) + r_u8(texture + 6u) + 255u);
        w_u8(packet + 37u, r_u8(texture + 4u) + (r_u16(texture + 6u) >> 8u) + 255u);
        w_u8(packet + 52u, r_u8(texture + 6u));
        w_u8(packet + 53u, r_u16(texture + 6u) >> 8u);
        w_u8(packet + 60u, r_u8(texture + 2u) + r_u8(texture + 6u) + 255u);
        w_u8(packet + 61u, r_u16(texture + 6u) >> 8u);
        w_u8(packet + 68u, r_u8(texture + 6u));
        w_u8(packet + 69u, r_u8(texture + 4u) + (r_u16(texture + 6u) >> 8u) + 255u);
        w_u8(packet + 76u, r_u8(texture + 2u) + r_u8(texture + 6u) + 255u);
        w_u8(packet + 77u, r_u8(texture + 4u) + (r_u16(texture + 6u) >> 8u) + 255u);
    }
    if (r_u16(0x80065A28u) == 0u)
    {
        value = r_u8(texture + 4u);
        copy[0] = r_u32(texture);
        copy[1] = r_u32(texture + 4u);
        w_u32(0x80065A28u, copy[0]);
        w_u32(0x80065A2Cu, copy[1]);
        copy[2] = r_u32(texture + 8u);
        w_u32(0x80065A30u, copy[2]);
        w_u8(0x800659D2u, value);
    }
    (void)DrawSync(0);
}

void v8_native_load_167C(uint32 base, const char *filename, uint32 text, uint32 flags)
{
    uint32 resource, parsed[5], list, module, callback;
    char path[64], *separator;
    const char *name;
    DISPENV display;
    DRAWENV draw;
    uint32 progress[4];
    uint32 entry, header[2], remaining = 0u, total, chunk, tag, font, lines, value;
    uint8 wrapped[256];
    uint16 light_vector[3];
    MATRIX level_matrix;
    uint32 player_context = 0x80065AB0u;
    uint8 *tile = (uint8 *)progress;
    resource = sub_80015F80(base + 0x48u);
    w_u32(0x80065328u, 0u);
    list = base + 0x7DA0u;
    w_u32(list, list + 4u);
    w_u32(list + 4u, 0u);
    w_u32(list + 8u, list);
    list = base + 0x7D90u;
    w_u32(list, list + 4u);
    w_u32(list + 4u, 0u);
    w_u32(list + 8u, list);
    (void)SetDefDispEnv(&display, 0, 0, 320, 240);
    (void)SetDefDrawEnv(&draw, 0, 0, 320, 240);
    display.screen.x = (sint8)r_u8(0x8006531Cu);
    display.screen.y = (sint8)r_u8(0x8006531Du);
    (void)PutDrawEnv(&draw);
    (void)PutDispEnv(&display);
    tile[3] = 3u;
    tile[7] = 96u;
    tile[4] = 255u;
    xport_store_le16(tile + 10u, 194u);
    tile[5] = 0u;
    tile[6] = 0u;
    xport_store_le16(tile + 8u, 0u);
    xport_store_le16(tile + 14u, 12u);
    load_185CC(resource + r_u32(resource + 12u), parsed);
    w_u16(parsed[3], 221u);
    w_u16(parsed[3] + 2u, 182u);
    (void)LoadImagePSX((PSX_RECT *)psx_addr(parsed[3], sizeof(PSX_RECT)),
                       (uint32 *)psx_addr(parsed[4], 4u));
    v8_native_19F44(0u, 185u, 219u, 185u, 0x525252u);
    v8_native_19F44(0u, 186u, 219u, 186u, 0x2988u);
    v8_native_19F44(0u, 213u, 226u, 213u, 0x2988u);
    v8_native_19F44(0u, 214u, 227u, 214u, 0x525252u);
    w_u32(0x80065310u, 0u);
    strcpy(path, filename);
    separator = strrchr(path, '.');
    xport_store_le32(separator, r_u32(base + 0x58u));
    separator[4] = (char)r_u8(base + 0x5Cu);
    module = v8_native_11ADC_host(path);
    w_u32(0x80065A38u, module);
    separator = strrchr(filename, '\\');
    name = separator != NULL ? separator + 1u : filename;
    strcpy(path, name);
    separator = strrchr(path, '.');
    if (separator == NULL)
        separator = path + strlen(path);
    *separator = '\0';
    if (strcmp(path, "SkiResrt") == 0)
        ski_module = module;
    callback = v8_native_11AA8_host(0u, path);
    if (callback == 0u)
    {
        callback = v8_native_11A38_host(r_u32(module + 4u), path);
        if (callback == 0u)
            callback = 0x800222A8u;
    }
    w_u32(0x80065A34u, callback);
    module = v8_native_21B80(callback, 0u, 0u, 0u);
    callback = r_u32(0x80065A34u);
    w_u32(0x800659FCu, module);
    w_u32(module + 0x64u, callback);
    entry = v8_native_find_file(filename);
    if (entry == 0u)
    {
        fprintf(stderr, "Missing terrain stream %s\n", filename);
        abort();
    }
    (void)sub_8001570C((sint32)r_u32(entry + 12u));
    w_u32(0x800659B0u, 0u);
    (void)sub_800225D4(header, &remaining);
    total = header[1];
    remaining = total;
    if (total != 0u)
    {
        do
        {
        chunk = sub_800225D4(header, &remaining);
        xport_store_le16(tile + 12u, ((total - remaining) * 218u) / total);
        (void)DrawPrim(progress);
        tag = (header[0] >> 24u) | ((header[0] >> 8u) & 0xFF00u) |
              ((header[0] & 0xFF00u) << 8u) | (header[0] << 24u);
        if (chunk == 0u && tag == 0x4F424A20u)
        {
            load_objects(base, header[1]);
            continue;
        }
        if (chunk == 0u && tag == 0x584F4246u)
        {
            load_xobf(header[1]);
            continue;
        }
        if (chunk != 0u)
        {
            (void)DrawSync(0);
            if (tag == 0x42535020u)
            {
                uint32 cursor = chunk, tree = load_bsp_node(&cursor);
                w_u32(0x80065A00u, tree);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x52534547u)
            {
                load_road_segment(chunk, header[1]);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x4A554E43u)
            {
                load_junction(base, chunk, header[1]);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x504C5458u)
            {
                for (value = 0u; value < 16u; ++value)
                {
                    font = r_u32(0x800737A0u + value * 4u);
                    if (font != 0u)
                        (void)sub_8001A91C(font);
                }
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x58525450u)
            {
                load_road_texture(chunk, header[1]);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x5842474Du)
            {
                load_background(chunk);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x41494D50u)
            {
                load_ai_map(chunk, header[1]);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x5A4D4150u)
            {
                load_zone_map(chunk);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x5A4F4E45u)
            {
                load_zone(chunk);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x54494E46u)
            {
                load_tinf(base, chunk);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x58424D50u)
            {
                load_xbmp(chunk);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x434F4C53u)
            {
                load_cols(chunk);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x53554E41u)
            {
                load_suna(chunk, header[1]);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x54455854u)
            {
                load_text(chunk, header[1]);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x48454144u)
            {
                load_head(chunk, header[1]);
                sub_80045088(chunk);
                continue;
            }
            if (tag == 0x584C5343u)
            {
                if (r_u8(chunk + 3u) == flags)
                {
                    font = sub_80019034(resource + r_u32(resource + 8u), 67u);
                    w_u8(font + 4u, 64u); w_u8(font + 5u, 64u); w_u8(font + 6u, 64u);
                    v8_native_shell_DC18(base, chunk + 4u, 0u, 10u, 0u);
                    value = r_u32(base + 0x6D94u + (uint32)(sint32)(sint8)r_u8(0x800658F8u) * 4u);
                    sub_80019960(font, value, 19u, 14u);
                    w_u8(font + 7u, (34u & 3u) ^ 101u);
                    w_u16(font + 16u, (r_u16(font + 16u) & 0xFF9Fu) | (34u & 96u));
                    w_u8(font + 4u, 128u); w_u8(font + 5u, 128u); w_u8(font + 6u, 128u);
                    value = r_u32(base + 0x6D94u + (uint32)(sint32)(sint8)r_u8(0x800658F8u) * 4u);
                    sub_80019960(font, value, 16u, 11u);
                    (void)sub_800190A8(font);
                    font = sub_80019034(resource + r_u32(resource + 4u), 1u);
                    w_u8(font + 4u, 96u); w_u8(font + 5u, 96u); w_u8(font + 6u, 40u);
                    lines = load_wrap_text(font, text, wrapped, 288u);
                    value = 64u - lines * r_u8(r_u32(font) + 7u);
                    value = (uint32)((sint32)value / 2) + 115u;
                    load_draw_text(font, wrapped, 16u, value);
                    (void)sub_800190A8(font);
                    sub_80045088(resource);
                }
                sub_80045088(chunk);
                continue;
            }
        }
        /* TODO Translate remaining chunk dispatch branches and the rest of the entry */
        fprintf(stderr, "TODO Load.dll chunk dispatch from19CC, tag=%08X chunk=%08X bytes=%u remaining=%u\n",
                tag, chunk, header[1], remaining);
        abort();
        } while (remaining != 0u);
    }
    (void)sub_80015A00();
    sub_80017E0C();
    light_vector[0] = (uint16)(((sint32)(sint16)r_u16(0x80065AB0u) * 6144) >> 12);
    light_vector[1] = (uint16)(((sint32)(sint16)r_u16(0x80065AB2u) * 6144) >> 12);
    light_vector[2] = (uint16)(((sint32)(sint16)r_u16(0x80065AB4u) * 6144) >> 12);
    w_u16(0x800659D0u, 0u);
    load_set_light(0u, light_vector, r_u32(0x80065B08u));
    v8_native_1D404(1u, base + 0xE8u, r_u32(0x80065AF8u));
    light_vector[0] = (uint16)(0u - r_u16(0x80065AB0u));
    light_vector[2] = (uint16)(0u - r_u16(0x80065AB4u));
    light_vector[1] = (uint16)r_u16(0x80065AB2u);
    load_set_light(2u, light_vector, r_u32(0x80065B10u));
    (void)v8_native_16DA8(&level_matrix);
    SetColorMatrix((MATRIX *)psx_addr(0x8006F760u, sizeof(MATRIX)));
    SetLightMatrix((MATRIX *)psx_addr(0x8006F720u, sizeof(MATRIX)));
    SetBackColor(64, 64, 64);
    {
        uint32 list = base + 0x7DA0u, node = r_u32(list), count = 0u, pending, next;
        if (r_u32(node) != 0u)
        {
            do
            {
                node = r_u32(node);
                ++count;
            } while (r_u32(node) != 0u);
        }
        pending = count;
        tile[4] = 0u;
        tile[5] = 255u;
        tile[6] = 0u;
        while (r_u32(list + 8u) != list)
        {
            player_context = list;
            node = r_u32(list);
            next = r_u32(node);
            w_u32(next + 4u, list);
            w_u32(list, next);
            v8_native_load_prepare_objects(base, r_u32(node + 8u), &level_matrix, v8_native_load_color);
            v8_native_load_insert_object(r_u32(0x80065A00u), node);
            --pending;
            xport_store_le16(tile + 12u, (uint16)load_divide((sint32)((count - pending) * 218u), (sint32)count));
            (void)DrawPrim(progress);
        }
    }
    (void)load_release_list(base + 0x7D90u);
    load_finalize_terrain();
    if ((sint8)r_u8(0x80065319u) == 0)
    {
        uint32 stage, record, count = 0u, index = 0u, object, word, half;
        sint32 kind;
        stage = r_u32(r_u32(0x8006590Cu) + (uint32)(sint32)(sint8)r_u8(0x80065674u) * 8u + 8u);
        stage += (uint32)(sint32)(sint8)r_u8(0x80065904u) * 16u;
        record = r_u32(stage + 8u);
        player_context = record;
        w_u8(0x80065ACCu, 0u);
        do
        {
            stage = r_u32(r_u32(0x8006590Cu) + (uint32)(sint32)(sint8)r_u8(0x80065674u) * 8u + 8u);
            stage += (uint32)(sint32)(sint8)r_u8(0x80065904u) * 16u;
            if ((sint32)index >= (sint32)r_u16(stage + 6u))
                break;
            kind = (sint8)r_u8(record);
            if (kind == -1)
            {
                if (r_u32(0x80065AD4u) == 0u)
                {
                    object = v8_native_load_spawn_record(record);
                    w_u32(0x80065AD4u, object);
                    w_u16(object + 6u, (uint32)kind);
                    (void)load_activate_object(object, record);
                }
            }
            else if (((uint32)kind & 128u) != 0u)
            {
                word = r_u32(record);
                half = r_u16(record + 4u);
                w_u32(0x80065ACCu, word);
                w_u16(0x80065AD0u, half);
            }
            else
            {
                object = v8_native_load_spawn_record(record);
                if (object != 0u)
                {
                    w_u8(object + 8u, 4u);
                    ++count;
                    w_u16(object + 6u, count);
                    if ((sint8)r_u8(0x8006531Au) == 0)
                        load_set_vehicle_health(object, r_u16(object + 12u) >> 1u);
                    (void)load_activate_object(object, record);
                }
            }
            ++index;
            record += 6u;
            player_context = record;
        } while ((sint32)count < 6);
    }
    if (r_u32(0x80065AD4u) == 0u)
    {
        value = v8_native_load_spawn_player(-1);
        w_u32(0x80065AD4u, value);
        (void)load_activate_object(value, player_context);
    }
    if ((sint8)r_u8(0x80065319u) >= 3 && r_u32(0x80065AD8u) == 0u)
    {
        value = v8_native_load_spawn_player(-2);
        w_u32(0x80065AD8u, value);
        (void)load_activate_object(value, player_context);
    }
    value = load_allocate_voice();
    w_u8(r_u32(0x80065AD4u) + 5u, value);
    (void)sub_800443C8((uint32)(sint32)(sint8)value, r_u32(r_u32(0x800737E0u) + 8u), 0u, 0u, value);
    value = sub_80017160();
    value *= r_u8(0x80065BFCu);
    (void)sub_80043CE0((uint32)((sint32)value >> 15));
    v8_native_load_choose_target(r_u32(0x80065AD4u), 1u);
    value = v8_native_load_create_camera(r_u32(0x80065AD4u), 256u);
    w_u32(r_u32(0x80065AD4u) + 224u, value);
    (void)v8_native_load_insert_camera(value);
    v8_native_load_position_camera(r_u32(r_u32(0x80065AD4u) + 224u));
    if ((sint8)r_u8(0x8006531Au) < 2)
    {
        value = r_u16(r_u32(0x80065AD4u) + 12u);
        if ((sint8)r_u8(0x8006531Au) == 0)
            value <<= 1u;
        else
            value = (uint32)((sint32)(value * 3u) >> 1);
        load_set_vehicle_health(r_u32(0x80065AD4u), value);
    }
    if (r_u32(0x80065AD8u) != 0u)
    {
        uint32 first, second;
        v8_native_load_choose_target(r_u32(0x80065AD8u), 1u);
        value = v8_native_load_create_camera(r_u32(0x80065AD8u), 256u);
        w_u32(r_u32(0x80065AD8u) + 224u, value);
        (void)v8_native_load_insert_camera(value);
        v8_native_load_position_camera(r_u32(r_u32(0x80065AD8u) + 224u));
        first = r_u32(0x80065AD4u);
        second = r_u32(0x80065AD8u);
        w_u32(first + 228u, second);
        w_u32(second + 228u, first);
        value = load_allocate_voice();
        w_u8(r_u32(0x80065AD8u) + 5u, value);
        (void)sub_800443C8((uint32)(sint32)(sint8)value, r_u32(r_u32(0x800737E4u) + 8u), 0u, 0u, value);
        if ((sint8)r_u8(0x8006531Au) < 2)
        {
            second = r_u32(0x80065AD8u);
            value = r_u16(second + 12u) << 1u;
            load_set_vehicle_health(second, value);
        }
    }
    w_u8(0x80065980u, 0u);
}

uint32 sub_8001D564(uint32 object);
uint32 sub_8001FE8C(uint32 list, uint32 object);
uint32 v8_native_terrain_call3(uint32 callback, uint32 object, uint32 mode, uint32 value);

sint32 v8_native_3E80C(uint32 object, uint32 mode)
{
    FUNCTION_MARKER(0x8003E80Cu, "SLUS_005.10");
    if (mode != 5u)
        return 0;
    if (r_u32(object + 60u) != 0u)
        sub_800204DC(sub_8001D564(object));
    else
        sub_800205F8(object);
    return -1;
}

uint32 v8_native_object_callback3(uint32 callback, uint32 object, uint32 mode, uint32 value)
{
    if (callback == 0x8003E80Cu)
        return (uint32)v8_native_3E80C(object, mode);
    return v8_native_terrain_call3(callback, object, mode, value);
}

uint32 sub_800203FC(uint32 object)
{
    uint32 callback = r_u32(object + 100u);
    FUNCTION_MARKER(0x800203FCu, "SLUS_005.10");
    if (callback != 0u)
        (void)v8_native_object_callback3(callback, object, 4u, 0u);
    if ((r_u32(object) & 0x80u) != 0u)
        (void)sub_8001FE8C(0x80065A60u, object);
    if ((r_u32(object) & 4u) != 0u)
        (void)sub_8001FE8C(0x80065A80u, object);
    if ((r_u32(object) & 1u) != 0u)
        (void)sub_8001FE8C(0x80065AC0u, object);
    return object;
}

void sub_800204DC(uint32 object)
{
    FUNCTION_MARKER(0x800204DCu, "SLUS_005.10");
    while (object != 0u) {
        uint32 current = object;
        uint32 carried = sub_800203FC(object);
        (void)sub_8001BDDC(r_u32(object + 48u), carried);
        sub_800204DC(r_u32(object + 56u));
        object = r_u32(object + 52u);
        sub_80045088(current);
    }
}

uint32 sub_800170C8(uint32 low, uint32 high)
{
    uint32 scale, shift, upper_shift, normalized;
    FUNCTION_MARKER(0x800170C8u, "SLUS_005.10");
    xport_gte_write_data(30u, high);
    scale = (uint32)((sint32)(35u - xport_gte_read_data(31u)) >> 1);
    shift = scale << 1;
    upper_shift = shift << 26;
    if ((sint32)upper_shift < 0) {
        normalized = (uint32)((sint32)high >> (shift & 31u));
    } else {
        normalized = low >> (shift & 31u);
        if (upper_shift != 0u) normalized |= high << ((0u - shift) & 31u);
    }
    xport_gte_write_data(30u, normalized);
    return SquareRoot0((sint32)normalized) << (scale & 31u);
}
