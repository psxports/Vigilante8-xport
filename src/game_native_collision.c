#include "psx.h"
#include "xport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32 sub_800255F4(uint32 x, uint32 z);

uint32 v8_native_terrain_call3(uint32 callback, uint32 object, uint32 mode, uint32 value);
uint32 sub_80016A20(uint32 vector);
uint32 sub_8002B940(uint32 object);
void sub_8002C018(uint32 object);
void sub_8002BC18(uint32 object);
uint32 sub_8003FEA8(uint32 position, uint32 color);
void sub_8002D44C(uint32 object);
void sub_800129E8(uint32 player, const char *message);
uint32 sub_8002C6FC(uint32 object, sint32 damage, uint32 point, uint32 mode);
uint32 sub_8002C958(uint32 object, sint32 damage, uint32 point, uint32 mode);
uint32 sub_8004410C(void);
void sub_8004483C(uint32 voice, uint32 table, uint32 sample, uint32 position);
uint32 sub_80012068(uint32 lane, uint32 strength, uint32 secondary, uint32 duration);
void v8_native_43408(uint32 matrix, uint32 vector, uint32 *destination);
void v8_native_435C0(uint32 matrix, const sint32 *source, sint32 *destination);

sint64 v8_native_17240(const sint32 *vector, uint32 normal)
{
    uint32 packed;
    FUNCTION_MARKER(0x80017240u, "SLUS_005.10");
    packed = r_u32(normal);
    return (sint64)vector[0] * (sint16)packed +
        (sint64)vector[1] * (sint16)(packed >> 16) +
        (sint64)vector[2] * (sint16)r_u16(normal + 4u);
}

static void collision_transform_long(sint32 *vector)
{
    uint32 input[3], high[3], i;
    for (i = 0u; i < 3u; ++i) {
        input[i] = (uint32)vector[i];
        xport_gte_write_data(9u + i, (uint32)(vector[i] >> 15));
    }
    xport_gte_execute(0x41E012u);
    for (i = 0u; i < 3u; ++i) high[i] = xport_gte_read_data(25u + i) << 3;
    for (i = 0u; i < 3u; ++i) xport_gte_write_data(9u + i, input[i] & 0x7FFFu);
    xport_gte_execute(0x49E012u);
    for (i = 0u; i < 3u; ++i) vector[i] = (sint32)(xport_gte_read_data(25u + i) + high[i]);
}

static uint32 collision_absolute_pair(uint32 value)
{
    if ((sint32)value < 0) value = 0u - value;
    if ((value & 0x8000u) != 0u) value ^= 0xFFFFu;
    return value;
}

uint32 v8_native_1E1C0(uint32 first_box, const uint32 *first_matrix,
    uint32 second_box, const uint32 *second_matrix)
{
    uint32 relative[5], column[3][3], i, j, value;
    sint32 delta[3], center[3], extent[3];
    FUNCTION_MARKER(0x8001E1C0u, "SLUS_005.10");
    for (i = 0u; i < 3u; ++i) {
        delta[i] = (sint32)(second_matrix[5u + i] - first_matrix[5u + i]);
        value = r_u32(second_box + i * 4u) + r_u32(second_box + 12u + i * 4u);
        center[i] = (sint32)value / 2;
        value = r_u32(second_box + 12u + i * 4u) - r_u32(second_box + i * 4u);
        extent[i] = (sint32)value / 2;
    }
    xport_gte_write_control(0u, (first_matrix[0] & 0xFFFFu) | (first_matrix[1] & 0xFFFF0000u));
    xport_gte_write_control(3u, (first_matrix[1] & 0xFFFFu) | (first_matrix[2] & 0xFFFF0000u));
    xport_gte_write_control(1u, (first_matrix[0] & 0xFFFF0000u) | (first_matrix[3] & 0xFFFFu));
    xport_gte_write_control(2u, (first_matrix[3] & 0xFFFF0000u) | (first_matrix[2] & 0xFFFFu));
    xport_gte_write_control(4u, first_matrix[4]);
    collision_transform_long(delta);
    for (i = 0u; i < 3u; ++i) {
        uint32 xy, z;
        if (i == 0u) {
            xy = (second_matrix[0] & 0xFFFFu) | (second_matrix[1] & 0xFFFF0000u);
            z = second_matrix[3];
        } else if (i == 1u) {
            xy = (second_matrix[0] >> 16) | (second_matrix[2] << 16);
            z = (uint32)(sint32)(sint16)(second_matrix[3] >> 16);
        } else {
            xy = (second_matrix[1] & 0xFFFFu) | (second_matrix[2] & 0xFFFF0000u);
            z = second_matrix[4];
        }
        xport_gte_write_data(0u, xy);
        xport_gte_write_data(1u, z);
        xport_gte_execute(0x486012u);
        for (j = 0u; j < 3u; ++j) column[i][j] = xport_gte_read_data(9u + j);
    }
    relative[0] = (column[0][0] & 0xFFFFu) | (column[1][0] << 16);
    relative[1] = (column[2][0] & 0xFFFFu) | (column[0][1] << 16);
    relative[2] = (column[1][1] & 0xFFFFu) | (column[2][1] << 16);
    relative[3] = (column[0][2] & 0xFFFFu) | (column[1][2] << 16);
    relative[4] = column[2][2];
    for (i = 0u; i < 5u; ++i) xport_gte_write_control(i, relative[i]);
    collision_transform_long(center);
    for (i = 0u; i < 3u; ++i) center[i] = (sint32)((uint32)center[i] + (uint32)delta[i]);
    for (i = 0u; i < 4u; ++i) xport_gte_write_control(i, collision_absolute_pair(relative[i]));
    value = (uint32)(sint32)(sint16)relative[4];
    if ((sint32)value < 0) value = 0u - value;
    xport_gte_write_control(4u, value);
    collision_transform_long(extent);
    for (i = 0u; i < 3u; ++i) {
        if ((sint32)r_u32(first_box + 12u + i * 4u) < (sint32)((uint32)center[i] - (uint32)extent[i]) ||
            (sint32)((uint32)center[i] + (uint32)extent[i]) < (sint32)r_u32(first_box + i * 4u)) return 0u;
    }
    return 1u;
}

uint32 v8_native_1E408(uint32 box, const uint32 *box_matrix,
    uint32 plane, const uint32 *plane_matrix)
{
    sint16 normal[3];
    sint32 local_normal[3], coordinate, distance;
    sint64 dot = 0;
    uint32 i, center, product, projection = 0u;
    FUNCTION_MARKER(0x8001E408u, "SLUS_005.10");
    for (i = 0u; i < 5u; ++i) xport_gte_write_control(i, plane_matrix[i]);
    xport_gte_write_data(0u, r_u32(plane));
    xport_gte_write_data(1u, r_u32(plane + 4u));
    xport_gte_execute(0x486012u);
    for (i = 0u; i < 3u; ++i) normal[i] = (sint16)xport_gte_read_data(9u + i);
    for (i = 0u; i < 3u; ++i) {
        center = r_u32(box + i * 4u) + r_u32(box + 12u + i * 4u);
        coordinate = (sint32)(box_matrix[5u + i] + (uint32)((sint32)center / 2) - plane_matrix[5u + i]);
        dot += (sint64)normal[i] * coordinate;
    }
    distance = (sint32)((uint32)(dot >> 12) - r_u32(plane + 8u));
    if (distance < 0) return 1u;
    xport_gte_write_data(0u, (uint32)(uint16)normal[0] | ((uint32)(uint16)normal[1] << 16));
    xport_gte_write_data(1u, (uint32)(uint16)normal[2]);
    xport_gte_write_control(0u, (box_matrix[0] & 0xFFFFu) | (box_matrix[1] & 0xFFFF0000u));
    xport_gte_write_control(3u, (box_matrix[1] & 0xFFFFu) | (box_matrix[2] & 0xFFFF0000u));
    xport_gte_write_control(1u, (box_matrix[0] & 0xFFFF0000u) | (box_matrix[3] & 0xFFFFu));
    xport_gte_write_control(2u, (box_matrix[3] & 0xFFFF0000u) | (box_matrix[2] & 0xFFFFu));
    xport_gte_write_control(4u, box_matrix[4]);
    xport_gte_execute(0x486012u);
    for (i = 0u; i < 3u; ++i) local_normal[i] = (sint32)xport_gte_read_data(9u + i);
    for (i = 0u; i < 3u; ++i) {
        product = (uint32)local_normal[i] * (r_u32(box + 12u + i * 4u) - r_u32(box + i * 4u));
        if ((sint32)product < 0) product = 0u - product;
        projection += product;
    }
    return ((uint32)distance - (uint32)((sint32)projection / 8192)) >> 31;
}

uint32 v8_native_1E9A0(uint32 first, uint32 second, const uint32 *first_matrix,
    const uint32 *second_matrix)
{
    uint32 first_shape = r_u32(first + 92u), second_shape;
    uint32 first_kind, second_kind, index, count, intersects;
    FUNCTION_MARKER(0x8001E9A0u, "SLUS_005.10");
    if (first_shape == 0u || r_u32(second + 92u) == 0u) return 0u;
    while ((first_kind = r_u16(first_shape)) != 0u) {
        second_shape = r_u32(second + 92u);
        if (first_kind != 1u && first_kind != 2u) continue;
        while ((second_kind = r_u16(second_shape)) != 0u) {
            intersects = 0u;
            if (first_kind == 1u && second_kind == 1u) {
                intersects = v8_native_1E1C0(first_shape + 4u, first_matrix, second_shape + 4u, second_matrix);
                if (intersects != 0u)
                    intersects = v8_native_1E1C0(second_shape + 4u, second_matrix, first_shape + 4u, first_matrix);
                if (intersects == 0u) second_shape += 28u;
            } else if (first_kind == 1u && second_kind == 2u) {
                count = r_u16(second_shape + 2u);
                intersects = 1u;
                for (index = 0u; index < count; ++index) {
                    if (v8_native_1E408(first_shape + 4u, first_matrix,
                        second_shape + 4u + index * 12u, second_matrix) == 0u) {
                        intersects = 0u;
                        break;
                    }
                }
                if (intersects == 0u) second_shape += r_u16(second_shape + 2u) * 12u + 4u;
            } else if (first_kind == 2u && second_kind == 1u) {
                count = r_u16(first_shape + 2u);
                intersects = 1u;
                for (index = 0u; index < count; ++index) {
                    if (v8_native_1E408(second_shape + 4u, second_matrix,
                        first_shape + 4u + index * 12u, first_matrix) == 0u) {
                        intersects = 0u;
                        break;
                    }
                }
                if (intersects == 0u) second_shape += 28u;
            } else if (first_kind == 2u && second_kind == 2u) {
                second_shape += r_u16(second_shape + 2u) * 12u + 4u;
            }
            if (intersects != 0u) {
                w_u32(0x1F800004u, first_shape);
                w_u32(0x1F800008u, second_shape);
                w_u32(0x1F80000Cu, first);
                w_u32(0x1F800010u, second);
                return 0x1F800000u;
            }
        }
        first_shape += first_kind == 1u ? 28u : r_u16(first_shape + 2u) * 12u + 4u;
    }
    return 0u;
}

uint32 sub_8001E120(uint32 object, uint32 mode, uint32 contact)
{
    uint32 callback = r_u32(object + 100u);
    FUNCTION_MARKER(0x8001E120u, "SLUS_005.10");
    return callback != 0u ? v8_native_terrain_call3(callback, object, mode, contact) : 0u;
}

static void collision_read_matrix(uint32 address, uint32 *matrix)
{
    uint32 i;
    for (i = 0u; i < 8u; ++i) matrix[i] = r_u32(address + 4u * i);
}

static void collision_rotate_normal(const uint32 *matrix, const sint16 *input,
    sint16 *output, uint32 transpose)
{
    uint32 i;
    xport_gte_write_data(0u, (uint32)(uint16)input[0] | ((uint32)(uint16)input[1] << 16));
    xport_gte_write_data(1u, (uint32)(uint16)input[2]);
    if (transpose != 0u) {
        xport_gte_write_control(0u, (matrix[0] & 0xFFFFu) | (matrix[1] & 0xFFFF0000u));
        xport_gte_write_control(3u, (matrix[1] & 0xFFFFu) | (matrix[2] & 0xFFFF0000u));
        xport_gte_write_control(1u, (matrix[0] & 0xFFFF0000u) | (matrix[3] & 0xFFFFu));
        xport_gte_write_control(2u, (matrix[3] & 0xFFFF0000u) | (matrix[2] & 0xFFFFu));
        xport_gte_write_control(4u, matrix[4]);
    } else {
        for (i = 0u; i < 5u; ++i) xport_gte_write_control(i, matrix[i]);
    }
    xport_gte_execute(0x486012u);
    for (i = 0u; i < 3u; ++i) output[i] = (sint16)xport_gte_read_data(9u + i);
}

sint32 v8_native_1E6DC(uint32 box, const uint32 *box_matrix,
    const uint32 *plane, const uint32 *plane_matrix)
{
    sint16 input[3], normal[3];
    sint64 dot = 0;
    sint32 coordinate, distance;
    uint32 i, center, product, projection = 0u;
    FUNCTION_MARKER(0x8001E6DCu, "SLUS_005.10");
    input[0] = (sint16)plane[0];
    input[1] = (sint16)(plane[0] >> 16);
    input[2] = (sint16)plane[1];
    collision_rotate_normal(plane_matrix, input, normal, 0u);
    for (i = 0u; i < 3u; ++i) {
        center = r_u32(box + i * 4u) + r_u32(box + 12u + i * 4u);
        coordinate = (sint32)(box_matrix[5u + i] + (uint32)((sint32)center / 2) - plane_matrix[5u + i]);
        dot += (sint64)normal[i] * coordinate;
    }
    distance = (sint32)((uint32)(dot >> 12) - plane[2]);
    collision_rotate_normal(box_matrix, normal, normal, 1u);
    for (i = 0u; i < 3u; ++i) {
        product = (uint32)(sint32)normal[i] * (r_u32(box + 12u + i * 4u) - r_u32(box + i * 4u));
        if ((sint32)product < 0) product = 0u - product;
        projection += product;
    }
    return (sint32)((uint32)distance - (uint32)((sint32)projection / 8192));
}

uint32 sub_8001D624(uint32 object);

uint32 v8_native_1F5A0(uint32 object, uint32 contact)
{
    uint32 matrix_address, box, shape, kind, i, j, selected = 0u;
    uint32 box_matrix[8], plane_matrix[8], plane[3];
    sint16 input[3], normal[3], local_normal[3];
    sint32 depth, best = (sint32)0x80000000u;
    FUNCTION_MARKER(0x8001F5A0u, "SLUS_005.10");
    matrix_address = sub_8001D624(r_u32(contact + 16u));
    box = r_u32(contact + 4u);
    if (r_u16(box) != 1u) return contact;
    box += 4u;
    shape = r_u32(contact + 8u);
    kind = r_u16(shape);
    if (kind != 1u && kind != 2u) return contact;
    collision_read_matrix(object + 16u, box_matrix);
    collision_read_matrix(matrix_address, plane_matrix);
    if (kind == 1u) {
        for (i = 0u; i < 6u; ++i) {
            for (j = 0u; j < 3u; ++j)
                input[j] = i == j ? -4096 : (i == j + 3u ? 4096 : 0);
            plane[0] = (uint32)(uint16)input[0] | ((uint32)(uint16)input[1] << 16);
            plane[1] = (uint32)(uint16)input[2];
            plane[2] = r_u32(shape + 4u + i * 4u);
            if (i < 3u) plane[2] = 0u - plane[2];
            depth = v8_native_1E6DC(box, box_matrix, plane, plane_matrix);
            if (best < depth) { best = depth; selected = i; }
        }
        for (i = 0u; i < 3u; ++i)
            input[i] = selected == i ? -4096 : (selected == i + 3u ? 4096 : 0);
    } else {
        for (i = 0u; i < r_u16(r_u32(contact + 8u) + 2u); ++i) {
            for (j = 0u; j < 3u; ++j) plane[j] = r_u32(r_u32(contact + 8u) + 4u + i * 12u + j * 4u);
            depth = v8_native_1E6DC(box, box_matrix, plane, plane_matrix);
            if (best < depth) { best = depth; selected = i; }
        }
        shape = r_u32(contact + 8u) + 4u + selected * 12u;
        input[0] = (sint16)r_u16(shape);
        input[1] = (sint16)r_u16(shape + 2u);
        input[2] = (sint16)r_u16(shape + 4u);
    }
    collision_rotate_normal(plane_matrix, input, normal, 0u);
    for (i = 0u; i < 3u; ++i) w_u16(contact + 32u + i * 2u, (uint16)normal[i]);
    collision_rotate_normal(box_matrix, normal, local_normal, 1u);
    for (i = 0u; i < 3u; ++i) w_u16(contact + 40u + i * 2u, (uint16)local_normal[i]);
    for (i = 0u; i < 3u; ++i)
        w_u32(contact + 20u + i * 4u, r_u32(box + i * 4u + (local_normal[i] < 0 ? 12u : 0u)));
    w_u32(contact + 48u, (uint32)best);
    return contact;
}

uint32 sub_80012028(uint32 lane, uint32 period, uint32 strength, uint32 secondary, uint32 duration)
{
    uint32 base = 0x80065940u + (lane << 3);
    FUNCTION_MARKER(0x80012028u, "SLUS_005.10");
    w_u8(base + 4u, period);
    w_u8(base + 5u, strength);
    w_u8(base + 6u, secondary);
    w_u8(base + 7u, duration);
    return duration;
}

uint32 v8_native_17594(uint32 object, const sint32 *impulse, uint32 point)
{
    sint32 transformed[3], product;
    uint32 i, result = 0u;
    FUNCTION_MARKER(0x80017594u, "SLUS_005.10");
    for (i = 0u; i < 5u; ++i) xport_gte_write_control(i, r_u32(object + 16u + i * 4u));
    for (i = 0u; i < 3u; ++i) transformed[i] = impulse[i];
    collision_transform_long(transformed);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_control(i * 2u, (uint32)((sint32)r_u32(point + i * 4u) >> 4));
    for (i = 0u; i < 3u; ++i) xport_gte_write_data(9u + i, (uint32)(impulse[i] >> 3));
    xport_gte_execute(0x178000Cu);
    for (i = 0u; i < 3u; ++i)
        w_u32(object + 128u + i * 4u, r_u32(object + 128u + i * 4u) + (uint32)transformed[i]);
    for (i = 0u; i < 3u; ++i) {
        product = (sint32)(xport_gte_read_data(25u + i) * (uint32)(sint32)(sint16)r_u16(object + 156u + i * 2u));
        result = r_u32(object + 144u + i * 4u) + (uint32)(product / 64);
        w_u32(object + 144u + i * 4u, result);
    }
    return result;
}

static sint32 collision_divide(sint32 dividend, sint32 divisor)
{
    if (divisor == 0) return dividend < 0 ? 1 : -1;
    if (dividend == (sint32)0x80000000u && divisor == -1) return dividend;
    return dividend / divisor;
}

static void collision_scaled_normal(uint32 object, uint32 normal_address,
    sint32 scale, sint32 *impulse)
{
    uint32 matrix[8], i;
    sint16 input[3], normal[3];
    collision_read_matrix(object + 16u, matrix);
    for (i = 0u; i < 3u; ++i) input[i] = (sint16)r_u16(normal_address + i * 2u);
    collision_rotate_normal(matrix, input, normal, 1u);
    for (i = 0u; i < 3u; ++i) impulse[i] = (sint32)((sint64)normal[i] * scale >> 12);
}

uint32 sub_8002D82C(uint32 object, uint32 contact)
{
    uint32 other, kind, owner, flags, i, count, product, callback, voice, sample;
    sint32 velocity[3], impulse[3], point[3], impact, transfer, damage, scale, player_kind;
    uint32 world_point[3];
    char message[64];
    FUNCTION_MARKER(0x8002D82Cu, "SLUS_005.10");
    other = r_u32(contact);
    if (r_u8(r_u32(contact + 16u) + 4u) == 3u) return 0u;
    v8_native_1F5A0(object, contact);
    kind = r_u8(other + 4u);
    if (kind == 7u) {
        if (r_u16(object + 286u) != 0u) { sub_8002C018(object); return 0u; }
        if ((r_u32(other) & 0x800000u) != 0u) {
            owner = r_u32(other + 128u);
            if (r_u8(owner + 182u) != 0u && (sint16)r_u16(object + 6u) == (sint8)r_u8(owner + 183u) &&
                r_u16(other + 10u) != r_u8(owner + 184u)) {
                count = (r_u8(owner + 185u) + 1u) & 0xFFu;
                w_u8(owner + 185u, count);
                w_u8(owner + 182u, 30u);
                product = r_u16(other + 12u) * (count + 1u);
                w_u16(other + 12u, product < 0xFFFFu ? product : 0xFFFFu);
            } else {
                w_u8(owner + 182u, r_u8(owner + 185u) != 0u ? 1u : 30u);
                w_u8(owner + 183u, r_u8(object + 6u));
            }
            w_u8(owner + 184u, r_u8(other + 10u));
            flags = r_u32(other) & 0xFF7FFFFFu;
            w_u32(other, flags);
            if (r_u16(object + 12u) == 0u && (flags & 0x1000000u) != 0u) {
                if ((sint16)r_u16(owner + 6u) < 0) {
                    uint32 name = sub_8002B940(object);
                    sprintf(message, (const char *)psx_addr(0x8006572Cu, 1u), (const char *)psx_addr(name, 1u));
                    sub_800129E8(r_u32(0x80065314u) != 0u ? 0u - (uint32)(sint32)(sint16)r_u16(owner + 6u) : 0u, message);
                }
                sub_8002BC18(object);
                sub_8003FEA8(object + 36u, 0x080000FFu);
                w_u32(object + 148u, 50000u);
                w_u32(object + 132u, r_u32(object + 132u) - 976512u);
                sub_8002D44C(owner);
                w_u8(owner + 187u, r_u8(owner + 187u) + 1u);
            }
        }
        sub_8002C6FC(object, -(sint32)r_u16(other + 12u), contact + 20u, 1u);
        return 0u;
    }
    if (kind == 1u) {
        product = (r_u32(other) & 0x10000u) != 0u ? r_u32(other + 132u) : sub_80016A20(other + 136u);
        damage = (sint32)(product * (uint32)((sint32)r_u32(other + 84u) / 256)) / 4096;
        if (damage > (sint32)(r_u16(object + 12u) >> 2)) damage = r_u16(object + 12u) >> 2;
        w_u32(other, r_u32(other) | 0x20u);
        sub_8002C958(object, (sint32)(0u - (uint32)damage), contact + 20u, 0u);
        return 0u;
    }
    if (kind == 2u) {
        for (i = 0u; i < 3u; ++i)
            velocity[i] = (sint32)(r_u32(object + 128u + i * 4u) * (r_u16(object + 162u) >> 6) -
                r_u32(other + 128u + i * 4u) * (r_u16(other + 162u) >> 6));
        impact = (sint32)(v8_native_17240(velocity, contact + 32u) >> 13);
        if (impact < 0) {
            transfer = collision_divide(impact, r_u16(object + 162u) >> 6);
            scale = (sint32)(0u - (r_u32(contact + 48u) * 2u + (uint32)transfer));
            collision_scaled_normal(object, contact + 32u, scale, impulse);
            v8_native_17594(object, impulse, contact + 20u);
            damage = transfer / 8192;
            if (damage < -8) {
                sub_8002C958(object, damage, contact + 20u, 1u);
                player_kind = (sint16)r_u16(object + 6u);
                if (player_kind < 0) sub_80012028(~(uint32)player_kind, 10u, 192u, 0u, 64u);
            }
            v8_native_43408(object + 16u, contact + 20u, world_point);
            for (i = 0u; i < 3u; ++i) w_u32(contact + 20u + i * 4u, world_point[i]);
            for (i = 0u; i < 3u; ++i) point[i] = (sint32)r_u32(contact + 20u + i * 4u);
            v8_native_435C0(other + 16u, point, point);
            for (i = 0u; i < 3u; ++i) w_u32(contact + 20u + i * 4u, (uint32)point[i]);
            transfer = collision_divide(impact, r_u16(other + 162u) >> 6);
            scale = (sint32)(r_u32(contact + 48u) * 2u + (uint32)transfer);
            collision_scaled_normal(other, contact + 32u, scale, impulse);
            v8_native_17594(other, impulse, contact + 20u);
            damage = transfer / 8192;
            if (damage < -8) {
                sub_8002C958(other, damage, contact + 20u, 1u);
                player_kind = (sint16)r_u16(other + 6u);
                if (player_kind < 0) sub_80012028(~(uint32)player_kind, 10u, 192u, 0u, 64u);
            }
            if ((r_u32(object) & 0x8000u) == 0u && (sint32)r_u32(object + 140u) >= 458) {
                voice = sub_8004410C();
                sub_8004483C(voice, r_u32(0x800658FCu), 30u, other + 72u);
            }
        }
        w_u32(object, r_u32(object) | 0x18000u);
        return 1u;
    }
    if ((r_u32(object + 116u) == other || r_u32(object + 120u) == other) &&
        (sint16)r_u16(contact + 34u) < -2048) return 0u;
    for (i = 0u; i < 3u; ++i) velocity[i] = (sint32)r_u32(object + 128u + i * 4u);
    impact = (sint32)(v8_native_17240(velocity, contact + 32u) >> 13);
    if (impact >= 0) return 0u;
    transfer = (sint32)(0u - (uint32)impact) / 16384;
    transfer = (sint32)((uint32)transfer * r_u16(object + 162u)) / 4096;
    callback = r_u32(other + 100u);
    if (callback != 0u && v8_native_terrain_call3(callback, other, 8u, (uint32)transfer) != 0u) return 0u;
    scale = (sint32)(0u - (r_u32(contact + 48u) + (uint32)impact));
    collision_scaled_normal(object, contact + 32u, scale, impulse);
    v8_native_17594(object, impulse, contact + 20u);
    if ((r_u32(object) & 0x8000u) == 0u) {
        damage = -(sint32)r_u16(other + 12u);
        if (damage < impact / 16384) damage = impact / 16384;
        sub_8002C958(object, damage, contact + 20u, 0u);
        player_kind = (sint16)r_u16(object + 6u);
        if (player_kind < 0) sub_80012068(~(uint32)player_kind, 255u, 0u, 64u);
        if ((sint32)r_u32(object + 140u) >= 458) {
            sample = r_u16(other + 6u) >> 4;
            if (sample >= 11u) sample = 11u;
            sample = r_u8(0x8001057Cu + sample);
            if (sample != 255u) {
                voice = sub_8004410C();
                sub_8004483C(voice, r_u32(0x800658FCu), sample, other + 36u);
            }
        }
    }
    w_u32(object, r_u32(object) | 0x18000u);
    return 0u;
}

uint32 v8_native_1ECC4(uint32 first, uint32 second, const uint32 *matrix)
{
    uint32 child = r_u32(second + 56u), child_matrix[8], result;
    MATRIX composed;
    FUNCTION_MARKER(0x8001ECC4u, "SLUS_005.10");
    while (child != 0u) {
        if (r_u32(child + 92u) != 0u && (r_u32(child) & 0x20u) == 0u) {
            uint32 first_matrix[8];
            collision_read_matrix(child + 16u, child_matrix);
            CompMatrixLV((MATRIX *)matrix, (MATRIX *)child_matrix, &composed);
            collision_read_matrix(first + 16u, first_matrix);
            result = v8_native_1E9A0(first, child, first_matrix, (const uint32 *)&composed);
            if (result != 0u) return result;
            if ((r_u32(child) & 0x800u) != 0u) {
                result = v8_native_1ECC4(first, child, (const uint32 *)&composed);
                if (result != 0u) return result;
            }
        } else if ((r_u32(child) & 0x800u) != 0u) {
            collision_read_matrix(child + 16u, child_matrix);
            CompMatrixLV((MATRIX *)matrix, (MATRIX *)child_matrix, &composed);
            result = v8_native_1ECC4(first, child, (const uint32 *)&composed);
            if (result != 0u) return result;
        }
        child = r_u32(child + 52u);
    }
    return 0u;
}

uint32 sub_8001EDB4(uint32 first, uint32 second)
{
    sint32 radius, distance;
    uint32 i, contact = 0u, result, first_matrix[8], second_matrix[8], fields[4];
    FUNCTION_MARKER(0x8001EDB4u, "SLUS_005.10");
    if (r_u16(first + 6u) == r_u16(second + 6u)) return 0u;
    radius = (sint32)(r_u32(first + 84u) + r_u32(second + 84u));
    for (i = 0u; i < 3u; ++i) {
        distance = (sint32)(r_u32(first + 36u + 4u * i) - r_u32(second + 36u + 4u * i));
        if (distance < 0) distance = (sint32)(0u - (uint32)distance);
        if (distance >= radius) return 0u;
    }
    if ((r_u32(second) & 0x40u) != 0u)
        w_u32(first + (r_u32(first + 116u) != 0u ? 120u : 116u), second);
    collision_read_matrix(second + 16u, second_matrix);
    if ((r_u32(second) & 0x800u) != 0u)
        contact = v8_native_1ECC4(first, second, second_matrix);
    if (contact == 0u) {
        collision_read_matrix(first + 16u, first_matrix);
        collision_read_matrix(second + 16u, second_matrix);
        contact = v8_native_1E9A0(first, second, first_matrix, second_matrix);
    }
    if (contact == 0u) return 0u;
    w_u32(contact, second);
    result = sub_8001E120(first, 3u, contact);
    if (result != 0u && result != 0xFFFFFFFFu) return result >> 31;
    for (i = 0u; i < 4u; ++i) fields[i] = r_u32(contact + 4u + i * 4u);
    w_u32(contact, first);
    w_u32(contact + 4u, fields[1]);
    w_u32(contact + 8u, fields[0]);
    w_u32(contact + 12u, fields[3]);
    w_u32(contact + 16u, fields[2]);
    result >>= 31;
    if ((sint32)sub_8001E120(second, 3u, contact) < 0) result |= 2u;
    return result;
}

uint32 sub_80020F14(uint32 tree, uint32 object)
{
    uint32 kind = r_u32(tree), node, next, other, coordinate, radius;
    FUNCTION_MARKER(0x80020F14u, "SLUS_005.10");
    if (kind == 0u) {
        node = r_u32(tree + 4u);
        next = r_u32(node);
        while (next != 0u) {
            other = r_u32(node + 8u);
            if ((r_u32(other) & 0x20u) == 0u && sub_8001EDB4(object, other) != 0u) return 0u;
            node = next;
            next = r_u32(next);
        }
        return 1u;
    }
    if (kind != 1u && kind != 2u) return 2u;
    coordinate = kind == 1u ? 36u : 44u;
    radius = r_u32(object + 84u);
    if ((sint32)(r_u32(object + coordinate) - radius) < (sint32)r_u32(tree + 4u) &&
        sub_80020F14(r_u32(tree + 8u), object) == 0u) return 0u;
    if ((sint32)r_u32(tree + 4u) < (sint32)(r_u32(object + coordinate) + r_u32(object + 84u)) &&
        sub_80020F14(r_u32(tree + 12u), object) == 0u) return 0u;
    return 1u;
}

void sub_8002169C(void)
{
    uint32 node = r_u32(0x80065A18u), next = r_u32(node), object, candidate, following, other;
    FUNCTION_MARKER(0x8002169Cu, "SLUS_005.10");
    while (next != 0u) {
        object = r_u32(node + 8u);
        if ((r_u32(object) & 0x20u) == 0u) {
            w_u32(object + 120u, 0u);
            w_u32(object + 116u, 0u);
            candidate = next;
            following = r_u32(candidate);
            while (following != 0u) {
                other = r_u32(candidate + 8u);
                if ((r_u32(other) & 0x20u) == 0u &&
                    (r_u32(other) & r_u32(object) & 0x200u) == 0u &&
                    sub_8001EDB4(object, other) != 0u) return;
                candidate = following;
                following = r_u32(following);
            }
            if ((r_u32(object) & 0x100u) == 0u) (void)sub_80020F14(r_u32(0x80065A00u), object);
        }
        node = next;
        next = r_u32(next);
    }
}

void sub_80021678(void)
{
    FUNCTION_MARKER(0x80021678u, "SLUS_005.10");
    sub_8002169C();
}

uint32 sub_8003FC50(uint32 object);
uint32 sub_8002BD84(uint32 object);
uint32 sub_8002BE84(uint32 object);

uint32 sub_8002C6FC(uint32 object, sint32 damage, uint32 point, uint32 mode)
{
    uint32 shape, index, health, part, part_health, before, after;
    sint32 remaining, multiplier;
    FUNCTION_MARKER(0x8002C6FCu, "SLUS_005.10");
    shape = r_u32(object + 92u) + 4u;
    if ((sint32)r_u32(shape + 20u) / 2 < (sint32)r_u32(point + 8u)) index = 0u;
    else index = (sint32)r_u32(point + 8u) < (sint32)r_u32(shape + 8u) / 2 ? 2u : 1u;
    health = r_u16(object + 12u);
    if (damage >= 0 || health == 0u) return 0u;
    if ((r_u32(0x80065908u) & 8u) != 0u && r_s16(object + 6u) < 0) return 0u;
    remaining = (sint32)(health + (uint32)damage);
    if (r_u8(object + 208u) == 12u) {
        if (remaining > 0 || mode == 0u) {
            w_u16(object + 12u, remaining > 0 ? (uint32)remaining : 1u);
            return 0u;
        }
    } else {
        if (r_u32(object + 236u + index * 4u) == 0u) return 0u;
        for (;;) {
            part = r_u32(object + 236u + index * 4u);
            part_health = r_u16(part + 12u);
            multiplier = r_s8(part + 8u);
            before = part_health * (uint32)multiplier + (health >> 1);
            remaining = (sint32)(part_health + (uint32)damage);
            after = (uint32)remaining * (uint32)multiplier + (health >> 1);
            if ((sint32)before / (sint32)health != (sint32)after / (sint32)health)
                (void)sub_8003FC50(part);
            if (remaining >= 0) {
                w_u16(part + 12u, (uint32)remaining);
                return 0u;
            }
            w_u16(part + 12u, 0u);
            damage = remaining;
            index = index == 1u ? (r_u16(r_u32(object + 236u) + 12u) == 0u ? 2u : 0u) : 1u;
            if (r_u16(r_u32(object + 236u) + 12u) == 0u &&
                r_u16(r_u32(object + 240u) + 12u) == 0u &&
                r_u16(r_u32(object + 244u) + 12u) == 0u) {
                if (mode == 0u) return 0u;
                break;
            }
            if (r_u32(object + 236u + index * 4u) == 0u) return 0u;
        }
    }
    if (remaining < -20) {
        (void)sub_8002BD84(object);
        return 1u;
    }
    (void)sub_8002BE84(object);
    return 0u;
}

uint32 sub_8002C958(uint32 object, sint32 damage, uint32 point, uint32 mode)
{
    FUNCTION_MARKER(0x8002C958u, "SLUS_005.10");
    if (r_u16(object + 286u) == 0u) return sub_8002C6FC(object, damage, point, mode);
    sub_8002C018(object);
    return 0u;
}

static void collision_height_rotate(const uint32 *matrix, sint32 *vector, uint32 transpose)
{
    uint32 i;
    if (transpose != 0u) {
        xport_gte_write_control(0u, (matrix[0] & 0xFFFFu) | (matrix[1] & 0xFFFF0000u));
        xport_gte_write_control(1u, (matrix[0] & 0xFFFF0000u) | (matrix[3] & 0xFFFFu));
        xport_gte_write_control(2u, (matrix[3] & 0xFFFF0000u) | (matrix[2] & 0xFFFFu));
        xport_gte_write_control(3u, (matrix[1] & 0xFFFFu) | (matrix[2] & 0xFFFF0000u));
        xport_gte_write_control(4u, matrix[4]);
    } else {
        for (i = 0u; i < 5u; ++i) xport_gte_write_control(i, matrix[i]);
    }
    collision_transform_long(vector);
}

static uint32 collision_height_geometry(uint32 shape, const uint32 *matrix,
    sint32 height, const sint32 *point, sint16 *normal)
{
    sint32 delta[3], local[3], plane_normal[3], lower, upper, candidate, world, floor;
    sint16 best_normal[3];
    sint64 quotient;
    uint64 numerator;
    uint32 i, kind, count, plane, have_normal;
    if (shape == 0u) return 0u;
    for (i = 0u; i < 3u; ++i) delta[i] = (sint32)((uint32)point[i] - matrix[5u + i]);
    while ((kind = r_u16(shape)) != 0u) {
        if (kind == 1u) {
            for (i = 0u; i < 3u; ++i) local[i] = delta[i];
            collision_height_rotate(matrix, local, 1u);
            floor = (sint32)r_u32(shape + 8u);
            if (local[0] < (sint32)r_u32(shape + 16u) && (sint32)r_u32(shape + 4u) < local[0] &&
                local[2] < (sint32)r_u32(shape + 24u) && (sint32)r_u32(shape + 12u) < local[2] &&
                local[1] < (sint32)r_u32(shape + 20u) &&
                local[1] < (sint32)((uint32)floor + 10240u) &&
                (sint32)((uint32)floor - 10240u) < local[1]) {
                world = (sint32)(matrix[6] + (uint32)floor);
                if (world < height || (sint32)((uint32)height + 65536u) < point[1] ||
                    r_u16(sub_800255F4((uint32)point[0], (uint32)point[2]) + 2u) == 0u) {
                    if (normal != NULL) {
                        normal[0] = (sint16)(0u - (matrix[0] >> 16));
                        normal[1] = (sint16)(0u - matrix[2]);
                        normal[2] = (sint16)(0u - (matrix[3] >> 16));
                    }
                    local[1] = (sint32)r_u32(shape + 8u);
                    collision_height_rotate(matrix, local, 0u);
                    return matrix[6] + (uint32)local[1];
                }
            }
            shape += 28u;
        } else if (kind == 2u) {
            for (i = 0u; i < 5u; ++i) xport_gte_write_control(i, matrix[i]);
            lower = (sint32)0x80010000u;
            upper = 0x7FFF0000;
            have_normal = 0u;
            count = r_u16(shape + 2u);
            for (i = 0u; i < count; ++i) {
                plane = shape + 4u + 12u * i;
                xport_gte_write_data(0u, r_u32(plane));
                xport_gte_write_data(1u, r_u32(plane + 4u));
                xport_gte_execute(0x486012u);
                plane_normal[0] = (sint32)xport_gte_read_data(9u);
                plane_normal[1] = (sint32)xport_gte_read_data(10u);
                plane_normal[2] = (sint32)xport_gte_read_data(11u);
                numerator = (uint64)((sint64)(sint32)r_u32(plane + 8u) * 4096);
                numerator -= (uint64)((sint64)plane_normal[0] * delta[0]);
                numerator -= (uint64)((sint64)plane_normal[2] * delta[2]);
                if (plane_normal[1] != 0) {
                    quotient = (sint64)numerator / plane_normal[1];
                    candidate = (sint32)(uint32)quotient;
                    if (plane_normal[1] < 0) {
                        if (lower < candidate) {
                            lower = candidate;
                            best_normal[0] = (sint16)plane_normal[0];
                            best_normal[1] = (sint16)plane_normal[1];
                            best_normal[2] = (sint16)plane_normal[2];
                            have_normal = 1u;
                        }
                    } else {
                        if (candidate < delta[1]) break;
                        if (candidate < upper) upper = candidate;
                    }
                } else if ((sint64)numerator < 0) break;
            }
            if (i == count && lower < upper) {
                world = (sint32)((uint32)lower + matrix[6]);
                if (world < height && (sint32)((uint32)point[1] - 10240u) < world) {
                    /* TODO Resolve original uninitialized normal slots when no lower plane wins */
                    if (have_normal == 0u) {
                        fprintf(stderr, "Unresolved 8001EF74 normal without winning lower plane\n");
                        abort();
                    }
                    if (best_normal[1] >= -2048) {
                        shape += 4u + 12u * r_u16(shape + 2u);
                        continue;
                    }
                    if (normal != NULL) {
                        normal[0] = best_normal[0];
                        normal[1] = best_normal[1];
                        normal[2] = best_normal[2];
                    }
                    return matrix[6] + (uint32)lower;
                }
            }
            shape += 4u + 12u * r_u16(shape + 2u);
        }
    }
    return 0u;
}

static uint32 collision_height_children(uint32 object, const uint32 *matrix,
    sint32 height, const sint32 *point, sint16 *normal)
{
    uint32 child = r_u32(object + 56u), composed[8], result, shape, dot;
    MATRIX local;
    while (child != 0u) {
        shape = r_u32(child + 92u);
        if (shape != 0u || (r_u32(child) & 0x800u) != 0u) {
            CompMatrixLV((MATRIX *)matrix, (MATRIX *)psx_addr(child + 16u, sizeof(MATRIX)), &local);
            memcpy(composed, &local, sizeof(composed));
            if (shape != 0u) {
                dot = (uint32)(sint32)(sint16)(composed[0] >> 16) * (uint32)(sint32)(sint16)r_u16(object + 18u);
                dot += (uint32)(sint32)(sint16)composed[2] * (uint32)(sint32)(sint16)r_u16(object + 24u);
                dot += (uint32)(sint32)(sint16)(composed[3] >> 16) * (uint32)(sint32)(sint16)r_u16(object + 30u);
                if ((sint16)composed[2] > 0 || (sint32)dot >= 2049) {
                    result = collision_height_geometry(r_u32(child + 92u), composed, height, point, normal);
                    if (result != 0u) return result;
                }
            }
            if ((r_u32(child) & 0x800u) != 0u) {
                result = collision_height_children(child, composed, height, point, normal);
                if (result != 0u) return result;
            }
        }
        child = r_u32(child + 52u);
    }
    return 0u;
}

uint32 sub_8001F51C(uint32 object, uint32 height, const sint32 *point, sint16 *normal)
{
    uint32 matrix[8], result, i;
    FUNCTION_MARKER(0x8001F51Cu, "SLUS_005.10");
    for (i = 0u; i < 8u; ++i) matrix[i] = r_u32(object + 16u + 4u * i);
    if ((r_u32(object) & 0x800u) != 0u) {
        result = collision_height_children(object, matrix, (sint32)height, point, normal);
        if (result != 0u) return result;
    }
    return collision_height_geometry(r_u32(object + 92u), matrix, (sint32)height, point, normal);
}
