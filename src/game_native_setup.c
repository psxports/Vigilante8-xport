#include "psx.h"
uint32 v8_native_terrain_call3(uint32 callback, uint32 object, uint32 mode, uint32 value);
void sub_800290D8(void);
uint32 sub_8001D370(void);
void sub_80041FD4(void);
void sub_800206F0(uint32 list);
void sub_80021460(void);
void sub_80029750(void);
void sub_80022CD0(uint32 object, uint32 light, uint32 ordering);

void sub_800290B4(void)
{
    FUNCTION_MARKER(0x800290B4u, "SLUS_005.10");
    sub_800290D8();
}

void sub_800215D0(void)
{
    FUNCTION_MARKER(0x800215D0u, "SLUS_005.10");
    sub_800206F0(0x80065A18u);
    sub_80021460();
}

void sub_80021600(void)
{
    uint32 object, callback;
    FUNCTION_MARKER(0x80021600u, "SLUS_005.10");
    sub_800290B4();
    (void)sub_8001D370();
    sub_80041FD4();
    sub_800215D0();
    sub_80029750();
    object = r_u32(0x800659FCu);
    callback = r_u32(0x80065A34u);
    (void)v8_native_terrain_call3(callback, object, 16u, 0u);
    object = r_u32(0x80065ADCu);
    if (object != 0u)
        sub_80022CD0(object, 0x80065AB0u, r_u32(0x80065910u) + 0xFFCu);
}

uint32 sub_80021394(uint32 time)
{
    uint32 node, object, next, previous, tail, callback;
    FUNCTION_MARKER(0x80021394u, "SLUS_005.10");
    while (r_u32(0x80065AC8u) != 0x80065AC0u) {
        node = r_u32(0x80065AC0u);
        if (time < r_u32(node + 12u)) return 1u;
        object = r_u32(node + 8u);
        w_u32(object, r_u32(object) & ~1u);
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
        callback = r_u32(object + 100u);
        if (callback != 0u) (void)v8_native_terrain_call3(callback, object, 2u, 0u);
    }
    return 0x80065AC0u;
}
#include <stdio.h>
#include <stdlib.h>

uint32 v8_native_1BE5C(uint32 model, const MATRIX *matrix, uint32 ordering_table);
void sub_80022CD0(uint32 object, uint32 light, uint32 ordering)
{
    uint32 index;
    FUNCTION_MARKER(0x80022CD0u, "SLUS_005.10");
    for (index = 0u; index < 5u; ++index)
        xport_gte_write_control(index, r_u32(0x8006F680u + index * 4u));
    xport_gte_write_data(0u, r_u32(light));
    xport_gte_write_data(1u, r_u32(light + 4u));
    xport_gte_execute(0x00486012u);
    for (index = 0u; index < 3u; ++index)
        w_u32(0x8005E958u + index * 4u, xport_gte_read_data(25u + index) << 6u);
    (void)v8_native_1BE5C(r_u32(object + 48u),
        (const MATRIX *)psx_addr(0x8005E944u, sizeof(MATRIX)), ordering);
}

uint32 sub_8001DB54(uint32 position, uint32 bound);
uint32 v8_native_1DE08(uint32 object);
void sub_800206F0(uint32 list)
{
    uint32 node, next;
    FUNCTION_MARKER(0x800206F0u, "SLUS_005.10");
    node = r_u32(list);
    next = r_u32(node);
    while (next != 0u) {
        (void)v8_native_1DE08(r_u32(node + 8u));
        node = next;
        next = r_u32(next);
    }
}

void sub_800209CC(uint32 node, sint32 min_x, sint32 max_x, sint32 min_z, sint32 max_z)
{
    uint32 kind = r_u32(node);
    sint32 split;
    FUNCTION_MARKER(0x800209CCu, "SLUS_005.10");
    if (kind == 0u) {
        sub_800206F0(node + 4u);
    } else if (kind == 1u || kind == 2u) {
        split = (sint32)r_u32(node + 4u);
        if ((kind == 1u ? min_x : min_z) < split)
            sub_800209CC(r_u32(node + 8u), min_x, max_x, min_z, max_z);
        if (split < (kind == 1u ? max_x : max_z))
            sub_800209CC(r_u32(node + 12u), min_x, max_x, min_z, max_z);
    }
}

static void scene_rotate_direction(SVECTOR *direction)
{
    FUNCTION_MARKER(0x8004316Cu, "SLUS_005.10");
    xport_gte_write_data(0u, (uint16)direction->vx | ((uint32)(uint16)direction->vy << 16));
    xport_gte_write_data(1u, (uint16)direction->vz);
    xport_gte_execute(0x486012u);
    direction->vx = (sint16)xport_gte_read_data(9u);
    direction->vy = (sint16)xport_gte_read_data(10u);
    direction->vz = (sint16)xport_gte_read_data(11u);
}

void sub_80021460(void)
{
    SVECTOR left, right;
    uint32 width = r_u32(0x800659DCu), distance = r_u16(0x800659D8u), rotation[5], i;
    sint32 minimum, maximum;
    uint32 base_x, base_z, min_x, max_x, min_z, max_z, root;
    FUNCTION_MARKER(0x80021460u, "SLUS_005.10");
    left.vx = (sint16)((sint32)(0u - width) / 2); left.vy = 0; left.vz = (sint16)distance;
    right.vx = (sint16)((sint32)width / 2); right.vy = 0; right.vz = (sint16)distance;
    (void)VectorNormalSS(&left, &left);
    (void)VectorNormalSS(&right, &right);
    for (i = 0u; i < 5u; ++i) rotation[i] = r_u32(0x8006F6E0u + i * 4u);
    for (i = 0u; i < 5u; ++i) xport_gte_write_control(i, rotation[i]);
    scene_rotate_direction(&left);
    scene_rotate_direction(&right);
    root = r_u32(0x80065A00u);
    base_x = r_u32(0x8006F6F4u);
    minimum = left.vx < right.vx ? left.vx : right.vx;
    maximum = left.vx > right.vx ? left.vx : right.vx;
    min_x = base_x + ((uint32)(minimum < 0 ? minimum : 0) << 10);
    max_x = base_x + ((uint32)(maximum > 0 ? maximum : 0) << 10);
    base_z = r_u32(0x8006F6FCu);
    minimum = left.vz < right.vz ? left.vz : right.vz;
    maximum = left.vz > right.vz ? left.vz : right.vz;
    min_z = base_z + ((uint32)(minimum < 0 ? minimum : 0) << 10);
    max_z = base_z + ((uint32)(maximum > 0 ? maximum : 0) << 10);
    sub_800209CC(root, (sint32)min_x, (sint32)max_x, (sint32)min_z, (sint32)max_z);
}

static sint32 scene_divide_product(uint32 first, uint32 second, sint32 divisor)
{
    sint32 product = (sint32)(first * second);
    if (divisor == 0) return product < 0 ? 1 : -1;
    return (sint32)((sint64)product / divisor);
}

static void scene_background_link(uint32 primitive)
{
    uint32 ordering = r_u32(0x80065910u) + 0x3FFCu, head = r_u32(ordering);
    w_u32(ordering, primitive & 0xFFFFFFu);
    w_u32(primitive, ((uint32)r_u8(primitive + 3u) << 24) | head);
}

void sub_80029750(void)
{
    MATRIX matrix, inverse;
    uint32 index, horizon, backdrop, i, high[3], input[3], yaw_word, pitch_word;
    sint32 yaw, pitch, angle, center_x, center_y, direction_x, direction_z, first, second;
    uint32 width, height;
    FUNCTION_MARKER(0x80029750u, "SLUS_005.10");
    index = r_u32(0x80065308u);
    for (i = 0u; i < 8u; ++i)
        xport_store_le32((uint8 *)&matrix + i * 4u, r_u32(0x8006F740u + i * 4u));
    horizon = 0x800910C0u + index * 48u;
    backdrop = 0x80091020u + index * 80u;
    yaw = (sint16)ratan2(matrix.m[0][2], matrix.m[2][2]);
    (void)RotMatrixY(-yaw, &matrix);
    angle = (sint16)(0u - (uint32)ratan2(matrix.m[1][2], matrix.m[2][2]));
    pitch_word = (uint32)angle;
    if ((angle < 0 ? -angle : angle) > 1024) pitch_word = 2048u - pitch_word;
    pitch = -(sint32)(sint16)pitch_word;
    (void)RotMatrixX(pitch, &matrix);
    yaw_word = ((uint32)yaw & 0xFFFu) * 5u;
    matrix.t[0] = (sint32)(yaw_word - (yaw_word & 0xF000u));
    matrix.t[1] = pitch * 5;
    matrix.t[2] = -3328;
    (void)TransposeMatrix(&matrix, &inverse);
    for (i = 0u; i < 5u; ++i)
        xport_gte_write_control(i, xport_load_le32((uint8 *)&inverse + i * 4u));
    for (i = 0u; i < 3u; ++i) {
        input[i] = (uint32)matrix.t[i];
        xport_gte_write_data(9u + i, (uint32)((sint32)input[i] >> 15));
    }
    xport_gte_execute(0x41E012u);
    for (i = 0u; i < 3u; ++i) high[i] = xport_gte_read_data(25u + i);
    for (i = 0u; i < 3u; ++i) xport_gte_write_data(9u + i, input[i] & 0x7FFFu);
    xport_gte_execute(0x49E012u);
    for (i = 0u; i < 3u; ++i)
        inverse.t[i] = (sint32)(0u - (xport_gte_read_data(25u + i) + (high[i] << 3)));
    for (i = 0u; i < 5u; ++i)
        xport_gte_write_control(i, xport_load_le32((uint8 *)&inverse + i * 4u));
    for (i = 0u; i < 3u; ++i) xport_gte_write_control(5u + i, (uint32)inverse.t[i]);
    for (i = 0u; i < 6u; ++i) xport_gte_write_data(i, r_u32(0x8005E9B4u + i * 4u));
    xport_gte_execute(0x280030u);
    scene_background_link(backdrop);
    w_u32(backdrop + 8u, xport_gte_read_data(12u));
    w_u32(backdrop + 16u, xport_gte_read_data(13u));
    w_u32(backdrop + 56u, xport_gte_read_data(14u));
    w_u32(backdrop + 48u, xport_gte_read_data(13u));
    for (i = 0u; i < 6u; ++i) xport_gte_write_data(i, r_u32(0x8005E9CCu + i * 4u));
    xport_gte_execute(0x280030u);
    scene_background_link(backdrop + 40u);
    w_u32(backdrop + 24u, xport_gte_read_data(12u));
    w_u32(backdrop + 32u, xport_gte_read_data(13u));
    w_u32(backdrop + 72u, xport_gte_read_data(14u));
    w_u32(backdrop + 64u, xport_gte_read_data(13u));
    center_x = ((sint32)(sint16)r_u16(backdrop + 16u) + (sint16)r_u16(backdrop + 32u)) / 2;
    center_y = ((sint32)(sint16)r_u16(backdrop + 18u) + (sint16)r_u16(backdrop + 34u)) / 2;
    direction_x = (sint16)xport_load_le16((uint8 *)&inverse);
    direction_z = (sint16)xport_load_le16((uint8 *)&inverse + 6u);
    if (direction_x >= 2897 || direction_x < -2896) {
        first = scene_divide_product(0u - (uint32)center_x, (uint32)direction_z, direction_x);
        second = scene_divide_product(r_u32(0x800659DCu) - (uint32)center_x, (uint32)direction_z, direction_x);
        height = r_u16(0x800659E0u); width = r_u16(0x800659DCu);
        w_u16(horizon + 22u, direction_x >= 2897 ? 0u : height);
        w_u16(horizon + 18u, direction_x >= 2897 ? 0u : height);
        w_u16(horizon + 46u, direction_x >= 2897 ? height : 0u);
        w_u16(horizon + 42u, direction_x >= 2897 ? height : 0u);
        w_u16(horizon + 16u, 0u); w_u16(horizon + 8u, 0u);
        w_u16(horizon + 40u, 0u); w_u16(horizon + 32u, 0u);
        w_u16(horizon + 20u, width); w_u16(horizon + 12u, width);
        w_u16(horizon + 44u, width); w_u16(horizon + 36u, width);
        w_u16(horizon + 34u, (uint32)center_y + (uint32)first);
        w_u16(horizon + 10u, (uint32)center_y + (uint32)first);
        w_u16(horizon + 38u, (uint32)center_y + (uint32)second);
        w_u16(horizon + 14u, (uint32)center_y + (uint32)second);
    } else {
        first = scene_divide_product(0u - (uint32)center_y, (uint32)direction_x, direction_z);
        second = scene_divide_product(r_u32(0x800659E0u) - (uint32)center_y, (uint32)direction_x, direction_z);
        width = r_u16(0x800659DCu); height = r_u16(0x800659E0u);
        w_u16(horizon + 20u, direction_z > 0 ? width : 0u);
        w_u16(horizon + 16u, direction_z > 0 ? width : 0u);
        w_u16(horizon + 44u, direction_z > 0 ? 0u : width);
        w_u16(horizon + 40u, direction_z > 0 ? 0u : width);
        w_u16(horizon + 18u, 0u); w_u16(horizon + 10u, 0u);
        w_u16(horizon + 42u, 0u); w_u16(horizon + 34u, 0u);
        w_u16(horizon + 22u, height); w_u16(horizon + 14u, height);
        w_u16(horizon + 46u, height); w_u16(horizon + 38u, height);
        w_u16(horizon + 32u, (uint32)center_x + (uint32)first);
        w_u16(horizon + 8u, (uint32)center_x + (uint32)first);
        w_u16(horizon + 36u, (uint32)center_x + (uint32)second);
        w_u16(horizon + 12u, (uint32)center_x + (uint32)second);
    }
    scene_background_link(horizon);
}
void v8_native_43408(uint32 matrix, uint32 vector, uint32 *destination);
uint32 v8_native_1BE5C(uint32 model, const MATRIX *matrix, uint32 ordering_table);
static void scene_near_quad(uint32 model, uint32 vertex, uint32 ordering_base);

void sub_80041C5C(uint32 object)
{
    MATRIX matrix;
    uint32 model, bound, output[3], words[8], i;
    FUNCTION_MARKER(0x80041C5Cu, "SLUS_005.10");
    model = r_u32(object + 24u);
    bound = (uint32)r_u16(model + 36u) << ((16u - r_u16(model + 38u)) & 31u);
    if (sub_8001DB54(object, bound) == 0u) return;
    v8_native_43408(0x8006F680u, object, output);
    if ((sint32)output[2] > 0x1FFFFF) return;
    for (i = 0u; i < 8u; ++i) words[i] = r_u32(0x8006F680u + i * 4u);
    words[5] = output[0]; words[6] = output[1]; words[7] = output[2];
    for (i = 0u; i < 8u; ++i) xport_store_le32((uint8 *)&matrix + i * 4u, words[i]);
    (void)v8_native_1BE5C(r_u32(object + 24u), &matrix, r_u32(0x80065910u));
}

static void scene_project_vertex(uint32 vertex)
{
    xport_gte_write_data(0u, r_u32(vertex));
    xport_gte_write_data(1u, r_u32(vertex + 4u));
    xport_gte_execute(0x180001u);
}

void sub_80040E5C(uint32 object)
{
    uint32 model, ordering_base, palette, threshold, quad, stride, primitive;
    uint32 vertex, iteration = 0u, ordering, head, i, color, offset;
    FUNCTION_MARKER(0x80040E5Cu, "SLUS_005.10");
    model = r_u32(object + 8u);
    ordering_base = r_u32(0x80065910u) + 64u;
    palette = r_u16(model + 10u);
    threshold = r_u16(model + 46u);
    scene_project_vertex(object + 32u);
    scene_project_vertex(object + 40u);
    if ((sint32)(r_u32(model + 24u) + r_u32(object + 28u)) >= (sint32)r_u32(model + 20u))
        w_u32(model + 24u, 0u);
    quad = (r_u16(model + 44u) & 2u) != 0u;
    stride = quad ? 52u : 40u;
    primitive = r_u32(model + 12u) + stride * r_u32(model + 24u);
    vertex = object + 56u;
    while ((sint32)iteration < (sint32)r_u32(object + 28u)) {
        scene_project_vertex(vertex - 8u);
        xport_gte_execute(0x1400006u);
        if ((sint32)xport_gte_read_data(24u) >= 0) {
            scene_project_vertex(vertex);
        } else if ((sint32)xport_gte_read_data(18u) < (sint32)threshold) {
            if (quad) {
                scene_near_quad(model, vertex, ordering_base);
                ++iteration;
                vertex += 16u;
                continue;
            }
            /* TODO Translate complete near subdivision routes 80040F88 and 800416E0 */
            fprintf(stderr, "TODO object subdivision 80040E5C object=%08X model=%08X quad=%u vertex=%08X\n",
                object, model, quad, vertex);
            abort();
        } else if ((sint32)xport_gte_read_flag() >= 0) {
            if (quad) {
                w_u32(primitive + 8u, xport_gte_read_data(12u));
                w_u32(primitive + 20u, xport_gte_read_data(13u));
                w_u32(primitive + 32u, xport_gte_read_data(14u));
            } else {
                w_u32(primitive + 8u, xport_gte_read_data(12u));
                w_u32(primitive + 16u, xport_gte_read_data(13u));
                w_u32(primitive + 24u, xport_gte_read_data(14u));
            }
            scene_project_vertex(vertex);
            for (i = 0u; i < (quad ? 4u : 1u); ++i) {
                color = r_u16(vertex - 18u + i * 8u);
                offset = primitive + 4u + i * 12u;
                w_u8(offset, color);
                w_u8(offset + 1u, color);
                w_u8(offset + 2u, color);
            }
            w_u32(primitive + (quad ? 44u : 32u), xport_gte_read_data(14u));
            xport_gte_execute(0x168002Eu);
            w_u16(primitive + 14u, palette + ((xport_gte_read_data(8u) >> 8) << 6));
            ordering = ordering_base + ((xport_gte_read_data(7u) >> 1) << 2);
            head = r_u32(ordering);
            w_u32(ordering, primitive & 0xFFFFFFu);
            w_u32(primitive, head | (quad ? 0x0C000000u : 0x09000000u));
            primitive += stride;
            w_u32(model + 24u, r_u32(model + 24u) + 1u);
        }
        ++iteration;
        vertex += 16u;
    }
}

void sub_80040E38(uint32 object)
{
    FUNCTION_MARKER(0x80040E38u, "SLUS_005.10");
    sub_80040E5C(object);
}

void sub_80041FD4(void)
{
    uint32 object, next, position, i, output[3], rotation[5];
    FUNCTION_MARKER(0x80041FD4u, "SLUS_005.10");
    object = r_u32(0x80065BC8u);
    next = r_u32(object);
    while (next != 0u) {
        position = object + 12u;
        if (sub_8001DB54(position, r_u32(object + 24u)) != 0u) {
            v8_native_43408(0x8006F680u, position, output);
            if ((sint32)output[2] <= 0x1FFFFF) {
                for (i = 0u; i < 5u; ++i)
                    rotation[i] = r_u32(0x8006F680u + i * 4u);
                for (i = 0u; i < 5u; ++i)
                    xport_gte_write_control(i, rotation[i]);
                for (i = 0u; i < 3u; ++i)
                    xport_gte_write_control(5u + i, (uint32)((sint32)output[i] >> 8));
                sub_80040E38(object);
            }
        }
        object = next;
        next = r_u32(next);
    }
    i = 0u;
    while ((sint32)i < (sint32)r_u32(0x80065BC4u)) {
        object = r_u32(r_u32(0x80065BD8u) + i * 4u);
        if (r_u32(object + 24u) != 0u) sub_80041C5C(object);
        ++i;
    }
}

static void scene_average_vertex(uint32 slot, uint32 first, uint32 second)
{
    sint32 x = ((sint32)(sint16)r_u16(first) + (sint16)r_u16(second)) / 2;
    sint32 y = ((sint32)(sint16)r_u16(first + 2u) + (sint16)r_u16(second + 2u)) / 2;
    sint32 z = ((sint32)(sint16)r_u16(first + 4u) + (sint16)r_u16(second + 4u)) / 2;
    xport_gte_write_data(slot * 2u, (uint16)x | ((uint32)(uint16)y << 16));
    xport_gte_write_data(slot * 2u + 1u, (uint32)z);
}

static void scene_mid_color(uint32 pool, uint32 first, uint32 second, const uint32 *offsets, uint32 count)
{
    sint32 value = ((sint32)(sint16)r_u16(first + 6u) + (sint16)r_u16(second + 6u)) / 2;
    uint32 color = (((uint32)value << 8) + (uint32)value);
    uint32 i;
    color = ((color << 8) + (uint32)value) | 0x3C000000u;
    for (i = 0u; i < count; ++i) w_u32(pool + offsets[i], color);
}

static void scene_near_quad(uint32 model, uint32 vertex, uint32 ordering_base)
{
    uint32 pool, cursor, i, xy, depth, delta_b, delta_c, depths[4], ordering, head;
    uint32 a = vertex - 24u, b = vertex - 16u, c = vertex - 8u, d = vertex;
    sint32 minimum, maximum, x;
    const uint32 ab[2] = {56u, 16u}, ac[2] = {108u, 28u};
    const uint32 cd[2] = {184u, 144u}, bd[2] = {172u, 92u};
    const uint32 bc[4] = {160u, 120u, 80u, 40u};
    if ((sint32)xport_gte_read_data(17u) <= 0 &&
        (sint32)xport_gte_read_data(18u) <= 0 && (sint32)xport_gte_read_data(19u) <= 0) return;
    cursor = r_u32(model + 32u);
    pool = r_u32(model + 16u) + cursor * 208u;
    minimum = maximum = (sint16)xport_gte_read_data(12u);
    for (i = 0u; i < 3u; ++i) {
        xy = xport_gte_read_data(12u + i);
        w_u32(pool + 8u + i * 64u, xy);
        x = (sint16)xy;
        if (x < minimum) minimum = x;
        if (x > maximum) maximum = x;
    }
    depth = xport_gte_read_data(17u);
    delta_b = xport_gte_read_data(18u) - depth;
    delta_c = xport_gte_read_data(19u) - depth;
    depth = (depth << 2) + delta_b + delta_c;
    xport_gte_write_data(0u, r_u32(d));
    xport_gte_write_data(1u, r_u32(d + 4u));
    scene_average_vertex(1u, a, b);
    scene_average_vertex(2u, a, c);
    xport_gte_execute(0x280030u);
    for (i = 0u; i < 4u; ++i) {
        uint32 color = r_u16(a + i * 8u + 6u);
        w_u8(pool + 4u + i * 64u, color);
        w_u8(pool + 5u + i * 64u, color);
        w_u8(pool + 6u + i * 64u, color);
    }
    x = (sint16)xport_gte_read_data(12u);
    if ((minimum < x ? minimum : x) < 320 && (maximum > x ? maximum : x) >= 0) {
        w_u32(pool + 200u, xport_gte_read_data(12u));
        xy = xport_gte_read_data(13u);
        w_u32(pool + 60u, xy); w_u32(pool + 20u, xy);
        xy = xport_gte_read_data(14u);
        w_u32(pool + 112u, xy); w_u32(pool + 32u, xy);
        depths[0] = depth;
        depths[1] = depth + (delta_b << 1);
        depths[2] = depth + (delta_c << 1);
        depths[3] = depth + (delta_b << 1) + (delta_c << 1);
        for (i = 0u; i < 4u; ++i) {
            ordering = ordering_base + ((uint32)((sint32)depths[i] >> 5) << 2);
            head = r_u32(ordering);
            w_u32(ordering, (pool + i * 52u) & 0xFFFFFFu);
            w_u32(pool + i * 52u, head | 0x0C000000u);
        }
        scene_average_vertex(0u, b, d);
        scene_average_vertex(1u, c, d);
        scene_average_vertex(2u, b, c);
        xport_gte_execute(0x280030u);
        scene_mid_color(pool, a, b, ab, 2u);
        scene_mid_color(pool, a, c, ac, 2u);
        scene_mid_color(pool, c, d, cd, 2u);
        scene_mid_color(pool, b, d, bd, 2u);
        scene_mid_color(pool, b, c, bc, 4u);
        xy = xport_gte_read_data(12u);
        w_u32(pool + 176u, xy); w_u32(pool + 96u, xy);
        xy = xport_gte_read_data(13u);
        w_u32(pool + 188u, xy); w_u32(pool + 148u, xy);
        xy = xport_gte_read_data(14u);
        w_u32(pool + 164u, xy); w_u32(pool + 124u, xy);
        w_u32(pool + 84u, xy); w_u32(pool + 44u, xy);
        cursor = r_u32(model + 32u) + 1u;
        w_u32(model + 32u, cursor == r_u32(model + 28u) ? 0u : cursor);
    }
    xport_gte_write_data(0u, r_u32(b)); xport_gte_write_data(1u, r_u32(b + 4u));
    xport_gte_write_data(2u, r_u32(c)); xport_gte_write_data(3u, r_u32(c + 4u));
    xport_gte_write_data(4u, r_u32(d)); xport_gte_write_data(5u, r_u32(d + 4u));
    xport_gte_execute(0x280030u);
}

static void terrain_gte_vertex(uint32 slot, const SVECTOR *vertex)
{
    xport_gte_write_data(slot * 2u, (uint32)(uint16)vertex->vx | ((uint32)(uint16)vertex->vy << 16));
    xport_gte_write_data(slot * 2u + 1u, (uint16)vertex->vz);
}

static uint32 terrain_triangle_depth(void)
{
    uint32 first = xport_gte_read_data(16u), second = xport_gte_read_data(17u);
    uint32 third = xport_gte_read_data(18u);
    if ((sint32)second < (sint32)first) second = first;
    return (sint32)third < (sint32)second ? second : third;
}

static void terrain_triangle_xy(uint32 primitive)
{
    w_u32(primitive + 8u, xport_gte_read_data(12u));
    w_u32(primitive + 20u, xport_gte_read_data(13u));
    w_u32(primitive + 32u, xport_gte_read_data(14u));
}

static void terrain_triangle_link(uint32 primitive, uint32 depth, uint32 palette_shift)
{
    uint32 palette = r_u16(0x80065B04u), ordering = r_u32(0x1F800000u), head;
    ordering += (depth >> 3) << 2;
    w_u16(primitive + 14u, palette + palette_shift);
    head = r_u32(ordering);
    w_u32(ordering, primitive & 0xFFFFFFu);
    w_u32(primitive, head | 0x09000000u);
    w_u32(primitive + 4u, xport_gte_read_data(20u));
    w_u32(primitive + 16u, xport_gte_read_data(21u));
    w_u32(primitive + 28u, xport_gte_read_data(22u));
}

void v8_native_25B20(SVECTOR *output, const SVECTOR *first, const SVECTOR *second,
    uint32 output_uv, uint32 first_uv, uint32 second_uv, uint32 factor)
{
    FUNCTION_MARKER(0x80025B20u, "SLUS_005.10");
    (void)LoadAverageShort12((SVECTOR *)first, (SVECTOR *)second, (sint32)(4096u - factor), (sint32)factor, output);
    (void)LoadAverageByte((uint8 *)psx_addr(first_uv, 2u), (uint8 *)psx_addr(second_uv, 2u),
        (sint32)(4096u - factor), (sint32)factor, (uint8 *)psx_addr(output_uv, 2u));
    (void)LoadAverageCol((uint8 *)psx_addr(first_uv - 8u, 3u), (uint8 *)psx_addr(second_uv - 8u, 3u),
        (sint32)(4096u - factor), (sint32)factor, (uint8 *)psx_addr(output_uv - 8u, 3u));
}

static uint32 terrain_clip_factor(uint32 first, uint32 second)
{
    sint32 numerator = (sint32)((144u - first) << 12);
    sint32 denominator = (sint32)(second - first);
    if (denominator == 0) return numerator < 0 ? 1u : 0xFFFFFFFFu;
    return (uint32)((int64_t)numerator / denominator);
}

static void terrain_clip_copy(uint32 output, uint32 input)
{
    w_u16(output, r_u16(input));
    w_u32(output - 8u, r_u32(input - 8u));
}

void v8_native_25BC0(uint32 primitive, const SVECTOR *a, const SVECTOR *b,
    const SVECTOR *c, uint32 winding)
{
    SVECTOR q[4];
    uint32 da = xport_gte_read_data(17u), db = xport_gte_read_data(18u);
    uint32 dc = xport_gte_read_data(19u), quad = r_u32(0x1F80001Cu);
    uint32 output = primitive, depth, ordering, head, is_quad = 0u;
    FUNCTION_MARKER(0x80025BC0u, "SLUS_005.10");
    w_u32(primitive + 4u, xport_gte_read_data(20u));
    w_u32(primitive + 16u, xport_gte_read_data(21u));
    w_u32(primitive + 28u, xport_gte_read_data(22u));
    if ((sint32)da < 144) {
        if ((sint32)db < 144) {
            if ((sint32)dc < 144) return;
            q[2] = *c;
            v8_native_25B20(q, a, c, primitive + 12u, primitive + 12u, primitive + 36u, terrain_clip_factor(da, dc));
            v8_native_25B20(q + 1, b, c, primitive + 24u, primitive + 24u, primitive + 36u, terrain_clip_factor(db, dc));
        } else if ((sint32)dc < 144) {
            q[1] = *b;
            v8_native_25B20(q, a, b, primitive + 12u, primitive + 12u, primitive + 24u, terrain_clip_factor(da, db));
            v8_native_25B20(q + 2, c, b, primitive + 36u, primitive + 36u, primitive + 24u, terrain_clip_factor(dc, db));
        } else {
            is_quad = 1u;
            q[3] = *c;
            terrain_clip_copy(quad + 48u, primitive + 36u);
            v8_native_25B20(q + 2, a, c, quad + 36u, primitive + 12u, primitive + 36u, terrain_clip_factor(da, dc));
            v8_native_25B20(q, a, b, quad + 12u, primitive + 12u, primitive + 24u, terrain_clip_factor(da, db));
            q[1] = *b;
            terrain_clip_copy(quad + 24u, primitive + 24u);
        }
    } else if ((sint32)db < 144) {
        if ((sint32)dc < 144) {
            q[0] = *a;
            v8_native_25B20(q + 1, b, a, primitive + 24u, primitive + 24u, primitive + 12u, terrain_clip_factor(db, da));
            v8_native_25B20(q + 2, c, a, primitive + 36u, primitive + 36u, primitive + 12u, terrain_clip_factor(dc, da));
        } else {
            is_quad = 1u;
            v8_native_25B20(q + 3, c, b, quad + 48u, primitive + 36u, primitive + 24u, terrain_clip_factor(dc, db));
            v8_native_25B20(q + 1, b, a, quad + 24u, primitive + 24u, primitive + 12u, terrain_clip_factor(db, da));
            q[0] = *a;
            terrain_clip_copy(quad + 12u, primitive + 12u);
            q[2] = *c;
            terrain_clip_copy(quad + 36u, primitive + 36u);
        }
    } else {
        is_quad = 1u;
        v8_native_25B20(q + 3, b, c, quad + 48u, primitive + 24u, primitive + 36u, terrain_clip_factor(db, dc));
        v8_native_25B20(q + 2, c, a, quad + 36u, primitive + 36u, primitive + 12u, terrain_clip_factor(dc, da));
        q[0] = *a;
        terrain_clip_copy(quad + 12u, primitive + 12u);
        q[1] = *b;
        terrain_clip_copy(quad + 24u, primitive + 24u);
    }
    terrain_gte_vertex(0u, q);
    terrain_gte_vertex(1u, q + 1);
    terrain_gte_vertex(2u, q + 2);
    xport_gte_execute(0x280030u);
    if (is_quad) {
        output = quad;
        w_u8(quad + 7u, 0x3Cu);
        w_u16(quad + 26u, r_u16(primitive + 26u));
    }
    if ((xport_gte_read_flag() & 0x7F85E000u) != 0u) return;
    xport_gte_execute(0x1400006u);
    if ((sint32)(xport_gte_read_data(24u) ^ winding) <= 0) return;
    depth = terrain_triangle_depth();
    terrain_triangle_xy(output);
    if (is_quad) {
        terrain_gte_vertex(0u, q + 3);
        xport_gte_execute(0x180001u);
    }
    w_u16(output + 14u, r_u16(0x80065B04u));
    if (is_quad) w_u32(output + 44u, xport_gte_read_data(14u));
    ordering = r_u32(0x1F800000u) + ((uint32)((sint32)depth / 8) << 2);
    head = r_u32(ordering);
    w_u32(ordering, output & 0xFFFFFFu);
    w_u32(output, head | (is_quad ? 0x0C000000u : 0x09000000u));
    if (is_quad) w_u32(0x1F80001Cu, r_u32(0x1F80001Cu) + 52u);
}

static void terrain_split_near(const SVECTOR *vertices, const uint32 *heights, uint32 material, uint32 alternate)
{
    uint32 primitive, depth, palette_shift, flag;
    uint32 first = alternate ? 0u : 1u, second = alternate ? 1u : 3u;
    uint32 third = alternate ? 2u : 0u, fourth = alternate ? 3u : 2u;
    uint32 uv_first = alternate ? 0u : 4u, uv_second = alternate ? 4u : 12u;
    uint32 uv_third = alternate ? 8u : 0u, uv_fourth = alternate ? 12u : 8u;
    terrain_gte_vertex(0u, vertices + first);
    terrain_gte_vertex(1u, vertices + second);
    terrain_gte_vertex(2u, vertices + third);
    xport_gte_execute(0x280030u);
    primitive = r_u32(0x1F800018u);
    w_u32(0x1F800018u, primitive + 80u);
    w_u16(primitive + 12u, r_u16(material + uv_first));
    w_u32(primitive + 24u, r_u32(material + uv_second));
    w_u16(primitive + 36u, r_u16(material + uv_third));
    flag = xport_gte_read_flag();
    if ((sint32)flag >= 0) {
        xport_gte_execute(0x1400006u);
        if ((sint32)xport_gte_read_data(24u) < 0) {
            depth = terrain_triangle_depth();
            palette_shift = (xport_gte_read_data(8u) >> 8) << 6;
            terrain_triangle_xy(primitive);
            xport_gte_write_data(0u, (heights[first] >> 11) << 7);
            xport_gte_write_data(2u, (heights[second] >> 11) << 7);
            xport_gte_write_data(4u, (heights[third] >> 11) << 7);
            xport_gte_execute(0x118043Fu);
            terrain_triangle_link(primitive, depth, palette_shift);
            terrain_gte_vertex(0u, vertices + fourth);
            xport_gte_execute(0x180001u);
            primitive += 40u;
            w_u16(primitive + 12u, r_u16(material + uv_second));
            w_u32(primitive + 24u, r_u32(material + uv_third));
            w_u16(primitive + 36u, r_u16(material + uv_fourth));
            flag = xport_gte_read_flag();
            if ((sint32)flag >= 0) {
                xport_gte_execute(0x1400006u);
                if ((sint32)xport_gte_read_data(24u) > 0) {
                    depth = terrain_triangle_depth();
                    terrain_triangle_xy(primitive);
                    xport_gte_write_data(0u, (heights[fourth] >> 11) << 7);
                    xport_gte_execute(0x108041Bu);
                    terrain_triangle_link(primitive, depth, palette_shift);
                    return;
                }
            }
            if ((xport_gte_read_flag() & 0x20000u) == 0u) return;
            xport_gte_write_data(0u, (heights[fourth] >> 11) << 7);
            xport_gte_execute(0x108041Bu);
            v8_native_25BC0(primitive, vertices + second, vertices + third, vertices + fourth, 0u);
            return;
        }
    }
    if ((xport_gte_read_flag() & 0x20000u) != 0u) {
        xport_gte_write_data(0u, (heights[first] >> 11) << 7);
        xport_gte_write_data(2u, (heights[second] >> 11) << 7);
        xport_gte_write_data(4u, (heights[third] >> 11) << 7);
        xport_gte_execute(0x118043Fu);
        v8_native_25BC0(primitive, vertices + first, vertices + second, vertices + third, 0xFFFFFFFFu);
        terrain_gte_vertex(0u, vertices + second);
        terrain_gte_vertex(1u, vertices + third);
        terrain_gte_vertex(2u, vertices + fourth);
        xport_gte_execute(0x280030u);
    } else {
        terrain_gte_vertex(0u, vertices + fourth);
        xport_gte_execute(0x180001u);
    }
    primitive += 40u;
    w_u16(primitive + 12u, r_u16(material + uv_second));
    w_u32(primitive + 24u, r_u32(material + uv_third));
    w_u16(primitive + 36u, r_u16(material + uv_fourth));
    xport_gte_write_data(0u, (heights[second] >> 11) << 7);
    xport_gte_write_data(2u, (heights[third] >> 11) << 7);
    xport_gte_write_data(4u, (heights[fourth] >> 11) << 7);
    flag = xport_gte_read_flag();
    if ((sint32)flag >= 0) {
        xport_gte_execute(0x1400006u);
        if ((sint32)xport_gte_read_data(24u) > 0) {
            depth = terrain_triangle_depth();
            palette_shift = (xport_gte_read_data(8u) >> 8) << 6;
            terrain_triangle_xy(primitive);
            xport_gte_execute(0x118043Fu);
            terrain_triangle_link(primitive, depth, palette_shift);
            return;
        }
    }
    if ((xport_gte_read_flag() & 0x20000u) == 0u) return;
    xport_gte_execute(0x118043Fu);
    v8_native_25BC0(primitive, vertices + second, vertices + third, vertices + fourth, 0u);
}

static uint32 terrain_far_link(uint32 primitive)
{
    uint32 ordering, head;
    w_u32(primitive + 4u, xport_gte_read_data(20u));
    w_u32(primitive + 12u, xport_gte_read_data(21u));
    w_u32(primitive + 20u, xport_gte_read_data(22u));
    xport_gte_execute(0x158002Du);
    ordering = r_u32(0x1F800000u) + ((xport_gte_read_data(7u) >> 1) << 2);
    head = r_u32(ordering);
    w_u32(ordering, primitive & 0xFFFFFFu);
    w_u32(primitive, head | 0x06000000u);
    return primitive + 28u;
}

static void terrain_far_plain(const SVECTOR *vertices, const uint32 *heights)
{
    uint32 primitive = r_u32(0x1F800014u), i;
    const uint32 order[3] = { 2u, 0u, 3u };
    xport_gte_write_data(6u, r_u32(0x80065B2Cu));
    for (i = 0u; i < 3u; ++i) {
        terrain_gte_vertex(0u, vertices + order[i]);
        xport_gte_execute(0x180001u);
        w_u32(primitive + 8u + i * 8u, xport_gte_read_data(14u));
        xport_gte_write_data(9u, (heights[order[i]] >> 11) << 7);
        xport_gte_execute(0x1280414u);
    }
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) < 0)
        primitive = terrain_far_link(primitive);
    terrain_gte_vertex(0u, vertices + 1);
    xport_gte_execute(0x180001u);
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) > 0) {
        xport_gte_write_data(9u, (heights[1] >> 11) << 7);
        xport_gte_execute(0x1280414u);
        w_u32(primitive + 8u, xport_gte_read_data(12u));
        w_u32(primitive + 16u, xport_gte_read_data(13u));
        w_u32(primitive + 24u, xport_gte_read_data(14u));
        primitive = terrain_far_link(primitive);
    }
    w_u32(0x1F800014u, primitive);
}

static void terrain_far_left(const SVECTOR *vertices, const uint32 *heights,
    uint32 x, uint32 z, uint32 step)
{
    SVECTOR middle;
    uint32 mz = z + (step >> 1), block, height, primitive, i, depth, ordering, head;
    const SVECTOR *initial[3] = { vertices, vertices + 1, &middle };
    uint32 light[3];
    block = r_u32(0x800911A0u + ((mz >> 6) << 2) + ((x >> 6) << 7));
    height = r_u16(block + ((mz & 63u) << 1) + ((x & 63u) << 7));
    middle.vx = vertices[0].vx;
    middle.vy = (sint16)(r_u32(0x1F800008u) + ((height & 0x7FFu) << 3));
    middle.vz = (sint16)(r_u32(0x1F80000Cu) + (z << 8) + ((step << 8) >> 1));
    light[0] = heights[0]; light[1] = heights[1]; light[2] = height;
    primitive = r_u32(0x1F800014u);
    xport_gte_write_data(6u, r_u32(0x80065B2Cu));
    for (i = 0u; i < 3u; ++i) {
        terrain_gte_vertex(0u, initial[i]);
        xport_gte_execute(0x180001u);
        w_u32(primitive + 8u + i * 8u, xport_gte_read_data(14u));
        xport_gte_write_data(9u, (light[i] >> 11) << 7);
        xport_gte_execute(0x1280414u);
    }
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) < 0)
        primitive = terrain_far_link(primitive);
    terrain_gte_vertex(0u, vertices + 3);
    xport_gte_execute(0x180001u);
    (void)xport_gte_read_data(7u);
    xport_gte_write_data(9u, (heights[3] >> 11) << 7);
    xport_gte_execute(0x1280414u);
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) > 0) {
        w_u32(primitive + 8u, xport_gte_read_data(12u));
        w_u32(primitive + 16u, xport_gte_read_data(13u));
        w_u32(primitive + 24u, xport_gte_read_data(14u));
        primitive = terrain_far_link(primitive);
    }
    terrain_gte_vertex(0u, vertices + 2);
    xport_gte_execute(0x180001u);
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) < 0) {
        xport_gte_execute(0x158002Du);
        depth = xport_gte_read_data(7u);
        xport_gte_write_data(9u, (heights[2] >> 11) << 7);
        xport_gte_execute(0x1280414u);
        ordering = r_u32(0x1F800000u) + ((depth >> 1) << 2);
        head = r_u32(ordering);
        w_u32(ordering, primitive & 0xFFFFFFu);
        w_u32(primitive, head | 0x06000000u);
        w_u32(primitive + 8u, xport_gte_read_data(12u));
        w_u32(primitive + 16u, xport_gte_read_data(13u));
        w_u32(primitive + 24u, xport_gte_read_data(14u));
        w_u32(primitive + 4u, xport_gte_read_data(20u));
        w_u32(primitive + 12u, xport_gte_read_data(21u));
        w_u32(primitive + 20u, xport_gte_read_data(22u));
        primitive += 28u;
    }
    w_u32(0x1F800014u, primitive);
}

static uint32 terrain_height(uint32 x, uint32 z)
{
    uint32 block = r_u32(0x800911A0u + ((z >> 6) << 2) + ((x >> 6) << 7));
    return r_u16(block + ((z & 63u) << 1) + ((x & 63u) << 7));
}

static void terrain_far_light(uint32 height)
{
    xport_gte_write_data(9u, (height >> 11) << 7);
    xport_gte_execute(0x1280414u);
}

static void terrain_far_xy(uint32 primitive)
{
    w_u32(primitive + 8u, xport_gte_read_data(12u));
    w_u32(primitive + 16u, xport_gte_read_data(13u));
    w_u32(primitive + 24u, xport_gte_read_data(14u));
}

static void terrain_far_left_bottom(const SVECTOR *vertices, const uint32 *heights,
    uint32 x, uint32 z, uint32 step)
{
    SVECTOR left, bottom;
    uint32 half = step >> 1, left_height, bottom_height, primitive, depth, ordering, head;
    left_height = terrain_height(x, z + half);
    left.vx = vertices[0].vx;
    left.vz = (sint16)(r_u32(0x1F80000Cu) + (z << 8) + ((step << 8) >> 1));
    left.vy = (sint16)(r_u32(0x1F800008u) + ((left_height & 0x7FFu) << 3));
    primitive = r_u32(0x1F800014u);
    xport_gte_write_data(6u, r_u32(0x80065B2Cu));
    terrain_gte_vertex(0u, vertices);
    xport_gte_execute(0x180001u);
    w_u32(primitive + 8u, xport_gte_read_data(14u));
    terrain_far_light(heights[0]);
    terrain_gte_vertex(0u, &left);
    xport_gte_execute(0x180001u);
    w_u32(primitive + 16u, xport_gte_read_data(14u));
    terrain_far_light(left_height);
    terrain_gte_vertex(0u, vertices + 1);
    xport_gte_execute(0x180001u);
    w_u32(primitive + 24u, xport_gte_read_data(14u));
    terrain_far_light(heights[1]);
    bottom_height = terrain_height(x + half, z + step);
    bottom.vx = (sint16)(r_u32(0x1F800004u) + (x << 8) + ((step << 8) >> 1));
    bottom.vz = vertices[2].vz;
    bottom.vy = (sint16)(r_u32(0x1F800008u) + ((bottom_height & 0x7FFu) << 3));
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) > 0)
        primitive = terrain_far_link(primitive);
    terrain_gte_vertex(0u, &bottom);
    xport_gte_execute(0x180001u);
    (void)xport_gte_read_data(7u);
    terrain_far_light(bottom_height);
    w_u32(primitive + 60u, xport_gte_read_data(20u));
    w_u32(primitive + 64u, xport_gte_read_data(12u));
    w_u32(primitive + 68u, xport_gte_read_data(22u));
    w_u32(primitive + 72u, xport_gte_read_data(14u));
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) < 0) {
        terrain_far_xy(primitive);
        (void)terrain_far_link(primitive);
    }
    terrain_gte_vertex(0u, vertices + 3);
    xport_gte_execute(0x180001u);
    (void)xport_gte_read_data(7u);
    terrain_far_light(heights[3]);
    primitive += 28u;
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) > 0) {
        terrain_far_xy(primitive);
        (void)terrain_far_link(primitive);
    }
    terrain_gte_vertex(0u, vertices + 2);
    xport_gte_execute(0x180001u);
    w_u32(primitive + 52u, xport_gte_read_data(14u));
    xport_gte_write_data(12u, r_u32(primitive + 36u));
    xport_gte_write_data(13u, r_u32(primitive + 44u));
    primitive += 28u;
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) < 0) {
        xport_gte_execute(0x158002Du);
        depth = xport_gte_read_data(7u);
        terrain_far_light(heights[2]);
        ordering = r_u32(0x1F800000u) + ((depth >> 1) << 2);
        head = r_u32(ordering);
        w_u32(ordering, primitive & 0xFFFFFFu);
        w_u32(primitive, head | 0x06000000u);
        w_u32(primitive + 20u, xport_gte_read_data(22u));
        primitive += 28u;
    }
    w_u32(0x1F800014u, primitive);
}

static void terrain_far_left_top(const SVECTOR *vertices, const uint32 *heights,
    uint32 x, uint32 z, uint32 step)
{
    SVECTOR left, top;
    uint32 half = step >> 1, left_height, top_height, primitive, depth, ordering, head;
    left_height = terrain_height(x, z + half);
    left.vx = vertices[0].vx;
    left.vz = (sint16)(r_u32(0x1F80000Cu) + (z << 8) + ((step << 8) >> 1));
    left.vy = (sint16)(r_u32(0x1F800008u) + ((left_height & 0x7FFu) << 3));
    primitive = r_u32(0x1F800014u);
    xport_gte_write_data(6u, r_u32(0x80065B2Cu));
    terrain_gte_vertex(0u, vertices + 2);
    xport_gte_execute(0x180001u);
    w_u32(primitive + 8u, xport_gte_read_data(14u));
    terrain_far_light(heights[2]);
    terrain_gte_vertex(0u, &left);
    xport_gte_execute(0x180001u);
    w_u32(primitive + 16u, xport_gte_read_data(14u));
    terrain_far_light(left_height);
    terrain_gte_vertex(0u, vertices + 3);
    xport_gte_execute(0x180001u);
    w_u32(primitive + 24u, xport_gte_read_data(14u));
    terrain_far_light(heights[3]);
    top_height = terrain_height(x + half, z);
    top.vx = (sint16)(r_u32(0x1F800004u) + (x << 8) + ((step << 8) >> 1));
    top.vz = vertices[0].vz;
    top.vy = (sint16)(r_u32(0x1F800008u) + ((top_height & 0x7FFu) << 3));
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) < 0)
        primitive = terrain_far_link(primitive);
    terrain_gte_vertex(0u, &top);
    xport_gte_execute(0x180001u);
    (void)xport_gte_read_data(7u);
    terrain_far_light(top_height);
    w_u32(primitive + 60u, xport_gte_read_data(20u));
    w_u32(primitive + 64u, xport_gte_read_data(12u));
    w_u32(primitive + 68u, xport_gte_read_data(22u));
    w_u32(primitive + 72u, xport_gte_read_data(14u));
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) > 0) {
        terrain_far_xy(primitive);
        (void)terrain_far_link(primitive);
    }
    terrain_gte_vertex(0u, vertices + 1);
    xport_gte_execute(0x180001u);
    (void)xport_gte_read_data(7u);
    terrain_far_light(heights[1]);
    primitive += 28u;
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) < 0) {
        terrain_far_xy(primitive);
        (void)terrain_far_link(primitive);
    }
    terrain_gte_vertex(0u, vertices);
    xport_gte_execute(0x180001u);
    w_u32(primitive + 52u, xport_gte_read_data(14u));
    xport_gte_write_data(12u, r_u32(primitive + 36u));
    xport_gte_write_data(13u, r_u32(primitive + 44u));
    primitive += 28u;
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) > 0) {
        xport_gte_execute(0x158002Du);
        depth = xport_gte_read_data(7u);
        terrain_far_light(heights[0]);
        ordering = r_u32(0x1F800000u) + ((depth >> 1) << 2);
        head = r_u32(ordering);
        w_u32(ordering, primitive & 0xFFFFFFu);
        w_u32(primitive, head | 0x06000000u);
        w_u32(primitive + 20u, xport_gte_read_data(22u));
        primitive += 28u;
    }
    w_u32(0x1F800014u, primitive);
}

static void terrain_far_top(const SVECTOR *vertices, const uint32 *heights,
    uint32 x, uint32 z, uint32 step)
{
    SVECTOR middle;
    uint32 height = terrain_height(x + (step >> 1), z);
    uint32 primitive = r_u32(0x1F800014u), i, depth, ordering, head;
    const SVECTOR *initial[3] = { vertices, vertices + 2, &middle };
    uint32 lights[3] = { heights[0], heights[2], height };
    middle.vx = (sint16)(r_u32(0x1F800004u) + (x << 8) + ((step << 8) >> 1));
    middle.vy = (sint16)(r_u32(0x1F800008u) + ((height & 0x7FFu) << 3));
    middle.vz = vertices[0].vz;
    xport_gte_write_data(6u, r_u32(0x80065B2Cu));
    for (i = 0u; i < 3u; ++i) {
        terrain_gte_vertex(0u, initial[i]);
        xport_gte_execute(0x180001u);
        w_u32(primitive + 8u + 8u * i, xport_gte_read_data(14u));
        terrain_far_light(lights[i]);
    }
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) > 0)
        primitive = terrain_far_link(primitive);
    terrain_gte_vertex(0u, vertices + 3);
    xport_gte_execute(0x180001u);
    (void)xport_gte_read_data(7u);
    terrain_far_light(heights[3]);
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) < 0) {
        terrain_far_xy(primitive);
        primitive = terrain_far_link(primitive);
    }
    terrain_gte_vertex(0u, vertices + 1);
    xport_gte_execute(0x180001u);
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) > 0) {
        xport_gte_execute(0x158002Du);
        depth = xport_gte_read_data(7u);
        terrain_far_light(heights[1]);
        ordering = r_u32(0x1F800000u) + ((depth >> 1) << 2);
        head = r_u32(ordering);
        w_u32(ordering, primitive & 0xFFFFFFu);
        w_u32(primitive, head | 0x06000000u);
        terrain_far_xy(primitive);
        w_u32(primitive + 4u, xport_gte_read_data(20u));
        w_u32(primitive + 12u, xport_gte_read_data(21u));
        w_u32(primitive + 20u, xport_gte_read_data(22u));
        primitive += 28u;
    }
    w_u32(0x1F800014u, primitive);
}

static void terrain_far_bottom(const SVECTOR *vertices, const uint32 *heights,
    uint32 x, uint32 z, uint32 step)
{
    SVECTOR middle;
    uint32 height = terrain_height(x + (step >> 1), z + step);
    uint32 primitive = r_u32(0x1F800014u), i, depth, ordering, head;
    const SVECTOR *initial[3] = { vertices + 2, vertices, &middle };
    uint32 lights[3] = { heights[2], heights[0], height };
    middle.vx = (sint16)(r_u32(0x1F800004u) + (x << 8) + ((step << 8) >> 1));
    middle.vy = (sint16)(r_u32(0x1F800008u) + ((height & 0x7FFu) << 3));
    middle.vz = vertices[2].vz;
    xport_gte_write_data(6u, r_u32(0x80065B2Cu));
    for (i = 0u; i < 3u; ++i) {
        terrain_gte_vertex(0u, initial[i]);
        xport_gte_execute(0x180001u);
        w_u32(primitive + 8u + 8u * i, xport_gte_read_data(14u));
        terrain_far_light(lights[i]);
    }
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) < 0)
        primitive = terrain_far_link(primitive);
    terrain_gte_vertex(0u, vertices + 1);
    xport_gte_execute(0x180001u);
    (void)xport_gte_read_data(7u);
    terrain_far_light(heights[1]);
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) > 0) {
        terrain_far_xy(primitive);
        primitive = terrain_far_link(primitive);
    }
    terrain_gte_vertex(0u, vertices + 3);
    xport_gte_execute(0x180001u);
    xport_gte_execute(0x1400006u);
    if ((sint32)xport_gte_read_data(24u) < 0) {
        xport_gte_execute(0x158002Du);
        depth = xport_gte_read_data(7u);
        terrain_far_light(heights[3]);
        ordering = r_u32(0x1F800000u) + ((depth >> 1) << 2);
        head = r_u32(ordering);
        w_u32(ordering, primitive & 0xFFFFFFu);
        w_u32(primitive, head | 0x06000000u);
        terrain_far_xy(primitive);
        w_u32(primitive + 4u, xport_gte_read_data(20u));
        w_u32(primitive + 12u, xport_gte_read_data(21u));
        w_u32(primitive + 20u, xport_gte_read_data(22u));
        primitive += 28u;
    }
    w_u32(0x1F800014u, primitive);
}

void sub_8002623C(uint32 detail, sint32 x, sint32 z, uint32 flags)
{
    uint32 step, camera_x, camera_z, sector, next_x, next_z;
    uint32 base_x, base_z, block, adjacent_x, adjacent_z, diagonal;
    uint32 heights[4], local_x, local_z, offset_x, offset_z, material;
    SVECTOR vertices[4];
    FUNCTION_MARKER(0x8002623Cu, "SLUS_005.10");
    step = 1u << (detail & 31u);
    camera_x = r_u32(0x1F800004u);
    base_z = ((uint32)z >> 6) << 2;
    camera_z = r_u32(0x1F80000Cu);
    base_x = ((uint32)x >> 6) << 7;
    sector = 0x80091120u + base_z + base_x;
    block = r_u32(sector + 128u);
    next_x = (uint32)x + step;
    adjacent_x = r_u32(0x800911A0u + base_z + ((next_x >> 6) << 7));
    local_x = ((uint32)x & 63u) << 7;
    local_z = ((uint32)z & 63u) << 1;
    heights[0] = r_u16(block + local_z + local_x);
    offset_x = (next_x & 63u) << 7;
    next_z = (uint32)z + step;
    heights[1] = r_u16(adjacent_x + local_z + offset_x);
    diagonal = r_u32(0x800911A0u + ((next_z >> 6) << 2) + ((next_x >> 6) << 7));
    adjacent_z = r_u32(0x800911A0u + ((next_z >> 6) << 2) + base_x);
    offset_z = (next_z & 63u) << 1;
    heights[3] = r_u16(diagonal + offset_z + offset_x);
    heights[2] = r_u16(adjacent_z + offset_z + local_x);
    offset_x = ((uint32)x << 8) + camera_x;
    offset_z = ((uint32)z << 8) + camera_z;
    camera_x = r_u32(0x1F800008u);
    vertices[0].vx = vertices[2].vx = (sint16)offset_x;
    vertices[1].vx = vertices[3].vx = (sint16)(offset_x + (step << 8));
    vertices[0].vz = vertices[1].vz = (sint16)offset_z;
    vertices[2].vz = vertices[3].vz = (sint16)(offset_z + (step << 8));
    vertices[0].vy = (sint16)(camera_x + ((heights[0] & 0x7FFu) << 3));
    vertices[1].vy = (sint16)(camera_x + ((heights[1] & 0x7FFu) << 3));
    vertices[2].vy = (sint16)(camera_x + ((heights[2] & 0x7FFu) << 3));
    vertices[3].vy = (sint16)(camera_x + ((heights[3] & 0x7FFu) << 3));
    if (detail == 0u) {
        block = r_u32(sector + 128u);
        material = 0x8008F020u + ((uint32)r_u8(block + 0x2000u +
            (((uint32)x & 63u) << 6) + ((uint32)z & 63u)) << 5);
        if (r_u16(material + 2u) == 0u) return;
        xport_gte_write_data(6u, 0x34808080u);
        terrain_split_near(vertices, heights, material, r_u16(material + 30u) == 0u);
        return;
    }
    if (flags == 0u) {
        terrain_far_plain(vertices, heights);
        return;
    }
    if (flags == 1u) {
        terrain_far_left(vertices, heights, (uint32)x, (uint32)z, step);
        return;
    }
    if (flags == 5u) {
        terrain_far_left_bottom(vertices, heights, (uint32)x, (uint32)z, step);
        return;
    }
    if (flags == 4u) {
        terrain_far_bottom(vertices, heights, (uint32)x, (uint32)z, step);
        return;
    }
    if (flags == 8u) {
        terrain_far_top(vertices, heights, (uint32)x, (uint32)z, step);
        return;
    }
    if (flags == 9u) {
        terrain_far_left_top(vertices, heights, (uint32)x, (uint32)z, step);
        return;
    }
    material = 0u;
    /* TODO Translate far terrain seam cases at 80026EC4 */
    fprintf(stderr, "TODO terrain primitives detail=%u x=%d z=%d flags=%08X material=%08X vertex=%d,%d,%d\n",
        detail, x, z, flags, material, vertices[0].vx, vertices[0].vy, vertices[0].vz);
    abort();
}

void sub_800288FC(uint32 detail, sint32 start, sint32 end, sint32 row, uint32 flags)
{
    uint32 step = 1u << (detail & 31u);
    FUNCTION_MARKER(0x800288FCu, "SLUS_005.10");
    if ((flags & 2u) != 0u) {
        sint32 last = (sint32)((uint32)end - step);
        sub_800288FC(detail, start, last, row, flags & ~2u);
        if (start < end) sub_8002623C(detail, last, row, flags);
    } else {
        while (start < end) {
            sub_8002623C(detail, start, row, flags);
            start = (sint32)((uint32)start + step);
            flags &= ~1u;
        }
    }
}

static sint32 terrain_scan_align(uint32 fixed, uint32 mask)
{
    return (sint32)((uint32)((sint32)fixed >> 16) & mask);
}

void sub_800289D8(uint32 detail, sint16 *bounds)
{
    uint32 step = 1u << (detail & 31u), mask = 0u - step;
    uint32 edge_mask = detail == 2u ? mask : mask << 1;
    uint32 left = 0u, right = 0u, previous_left, previous_right;
    uint32 left_x = 0u, right_x = 0u, left_delta = 0u, right_delta = 0u;
    sint32 row = 0x7FFFFFFF, limit = (sint32)0x80000001u;
    sint32 left_rows = 0, right_rows = 0, inner_min, inner_max;
    uint32 orientation, i, scanned = 0u;
    FUNCTION_MARKER(0x800289D8u, "SLUS_005.10");
    inner_min = bounds[1] < bounds[3] ? bounds[1] : bounds[3];
    inner_max = bounds[1] > bounds[3] ? bounds[1] : bounds[3];
    orientation = ((bounds[3] < bounds[1]) ? 2u : 0u) | (bounds[2] < bounds[0]);
    for (i = 0u; i < 4u; ++i) {
        sint32 z = bounds[i * 2u + 1u];
        if (z < row) { row = z; left = i; }
        if (limit < z) limit = z;
    }
    right = left;
    previous_left = previous_right = (uint32)(sint32)bounds[left * 2u] << 16;
    if (detail != 0u && bounds[1] == bounds[3]) limit = (sint32)((uint32)limit - step);
    while (row < limit) {
        sint32 start, end, first, second;
        uint32 flags = 0u, fixed;
        scanned = 1u;
        if (left_rows <= 0) {
            do {
                left_x = (uint32)(sint32)bounds[left * 2u] << 16;
                left = (left + 1u) & 3u;
                left_rows = (sint32)((uint32)(sint32)bounds[left * 2u + 1u] - (uint32)row) >>
                    ((detail + (detail != 2u && left == 3u)) & 31u);
            } while (left_rows <= 0);
            fixed = ((uint32)(sint32)bounds[left * 2u] << 16) - left_x;
            left_delta = (uint32)((sint64)(sint32)fixed / left_rows);
        }
        if (right_rows <= 0) {
            do {
                right_x = (uint32)(sint32)bounds[right * 2u] << 16;
                right = (right + 3u) & 3u;
                right_rows = (sint32)((uint32)(sint32)bounds[right * 2u + 1u] - (uint32)row) >>
                    ((detail + (detail != 2u && right == 2u)) & 31u);
            } while (right_rows <= 0);
            fixed = ((uint32)(sint32)bounds[right * 2u] << 16) - right_x;
            right_delta = (uint32)((sint64)(sint32)fixed / right_rows);
        }
        if (detail == 0u || row < inner_min || inner_max < row) {
            start = terrain_scan_align(left_x, left == 3u ? edge_mask : mask);
            end = terrain_scan_align(right_x, right == 2u ? edge_mask : mask);
        } else if (orientation == 0u) {
            uint32 next = left_x + left_delta;
            fixed = (sint32)right_x < (sint32)next ? right_x : next;
            first = terrain_scan_align(left_x, mask);
            second = terrain_scan_align(fixed, mask);
            sub_800288FC(detail, first, second, row, 5u);
            start = terrain_scan_align(next, mask);
            end = terrain_scan_align(right_x, right == 2u ? edge_mask : mask);
            flags = first >= second;
        } else if (orientation == 1u) {
            fixed = (sint32)right_x < (sint32)previous_left ? right_x : previous_left;
            first = terrain_scan_align(left_x, mask);
            second = terrain_scan_align(fixed, mask);
            sub_800288FC(detail, first, second, row, 9u);
            start = terrain_scan_align(left_x - left_delta, mask);
            end = terrain_scan_align(right_x, right == 2u ? edge_mask : mask);
            flags = first >= second;
        } else if (orientation == 2u) {
            fixed = right_x + right_delta;
            if ((sint32)fixed < (sint32)left_x) fixed = left_x;
            first = terrain_scan_align(fixed, mask);
            second = terrain_scan_align(right_x, mask);
            sub_800288FC(detail, first, second, row, 6u);
            start = terrain_scan_align(left_x, left == 3u ? edge_mask : mask);
            fixed = right_x + right_delta;
            if ((sint32)fixed < (sint32)left_x) fixed = left_x;
            end = terrain_scan_align(fixed, mask);
            flags = first < second ? 0u : 2u;
        } else {
            fixed = (sint32)previous_right < (sint32)left_x ? left_x : previous_right;
            first = terrain_scan_align(fixed, mask);
            second = terrain_scan_align(right_x, mask);
            sub_800288FC(detail, first, second, row, 10u);
            start = terrain_scan_align(left_x, left == 3u ? edge_mask : mask);
            fixed = right_x - right_delta;
            if ((sint32)fixed < (sint32)left_x) fixed = left_x;
            end = terrain_scan_align(fixed, mask);
            flags = first < second ? 0u : 2u;
        }
        sub_800288FC(detail, start, end, row, flags);
        previous_left = left_x;
        previous_right = right_x;
        if (detail == 2u || left != 3u || ((uint32)row & step) != 0u) {
            left_x += left_delta; --left_rows;
        }
        if (detail == 2u || right != 2u || ((uint32)row & step) != 0u) {
            right_x += right_delta; --right_rows;
        }
        row = (sint32)((uint32)row + step);
    }
    if (detail != 0u && bounds[1] == bounds[3] && scanned == 0u) {
        /* TODO Resolve original carried edge values for a degenerate empty scan */
        fprintf(stderr, "TODO terrain 800289D8 empty scan detail=%u\n", detail);
        abort();
    }
    if (detail != 0u && bounds[1] == bounds[3])
        sub_800288FC(detail, terrain_scan_align(left_x, mask), terrain_scan_align(right_x, mask), row, 4u);
}

static sint32 terrain_truncate_shift(uint32 value, uint32 shift)
{
    if ((sint32)value < 0) value += (1u << shift) - 1u;
    return (sint32)value >> shift;
}

static sint16 terrain_project_extent(sint16 value, uint32 projection)
{
    sint32 numerator = (sint32)value * 80;
    if (projection == 0u) return (sint16)(numerator < 0 ? 1 : -1);
    return (sint16)((sint64)numerator / (sint32)projection);
}

static void terrain_rotate_extent(SVECTOR *vector)
{
    uint32 x, y, z;
    xport_gte_write_data(0u, xport_load_le32((uint8 *)vector));
    xport_gte_write_data(1u, xport_load_le32((uint8 *)vector + 4u));
    xport_gte_mvmva(0x486012u);
    x = xport_gte_read_data(9u);
    y = xport_gte_read_data(10u);
    z = xport_gte_read_data(11u);
    vector->vx = (sint16)x;
    vector->vy = (sint16)y;
    vector->vz = (sint16)z;
}

void sub_800290D8(void)
{
    SVECTOR left, right;
    sint16 bounds[8];
    sint32 camera_x, camera_z, extent, shift, detail;
    uint32 value, frame, count, first, second, third;
    FUNCTION_MARKER(0x800290D8u, "SLUS_005.10");
    camera_x = terrain_truncate_shift(r_u32(0x8006F6F4u), 16u);
    camera_z = terrain_truncate_shift(r_u32(0x8006F6FCu), 16u);
    value = r_u32(0x800659DCu);
    if ((sint16)r_u16(0x8006F6E8u) > 0)
        extent = (sint32)((uint32)terrain_truncate_shift(value, 1u) + 16u);
    else
        extent = (sint32)((uint32)terrain_truncate_shift(0u - value, 1u) - 16u);
    right.vx = (sint16)extent;
    left.vx = (sint16)(0u - (uint32)extent);
    value = r_u32(0x800659E0u);
    if ((sint16)r_u16(0x8006F6E6u) >= 0) value = 0u - value;
    value = (value + (value >> 31)) >> 1;
    right.vy = (sint16)value;
    left.vy = (sint16)(0u - value);
    left.vz = right.vz = (sint16)r_u16(0x800659D8u);
    left.pad = right.pad = 0;
    SetRotMatrix((MATRIX *)psx_addr(0x8006F6E0u, 20u));
    terrain_rotate_extent(&left);
    terrain_rotate_extent(&right);
    value = r_u32(0x800659D8u);
    left.vx = terrain_project_extent(left.vx, value);
    left.vz = terrain_project_extent(left.vz, value);
    right.vx = terrain_project_extent(right.vx, value);
    right.vz = terrain_project_extent(right.vz, value);
    w_u32(0x1F800004u, (uint32)terrain_truncate_shift(0u - r_u32(0x8006F6F4u), 8u));
    w_u32(0x1F800008u, (uint32)terrain_truncate_shift(0u - r_u32(0x8006F6F8u), 8u));
    w_u32(0x1F80000Cu, (uint32)terrain_truncate_shift(0u - r_u32(0x8006F6FCu), 8u));
    SetRotMatrix((MATRIX *)psx_addr(0x8006F680u, 20u));
    xport_gte_write_control(5u, 0u);
    xport_gte_write_control(6u, 0u);
    xport_gte_write_control(7u, 0u);
    SetColorMatrix((MATRIX *)psx_addr(0x8005E994u, 20u));
    SetLightMatrix((MATRIX *)psx_addr(0x8005E974u, 20u));
    SetBackColor(r_u8(0x80065B54u), r_u8(0x80065B55u), r_u8(0x80065B56u));
    SetFarColor(r_u8(0x80065B00u), r_u8(0x80065B01u), r_u8(0x80065B02u));
    value = r_u32(0x80065910u);
    frame = r_u32(0x80065308u);
    w_u32(0x1F800000u, value + 256u);
    w_u32(0x1F800014u, 0x80092220u + frame * 32256u);
    w_u32(0x1F800018u, 0x8007A9A0u + frame * 40960u);
    w_u32(0x1F80001Cu, 0x8008E9A0u + frame * 832u);
    bounds[0] = (sint16)((uint32)camera_x + (right.vz > 0 ? 2u : 0xFFFFFFFFu));
    bounds[1] = (sint16)((uint32)camera_z + (right.vx < 0 ? 2u : 0xFFFFFFFFu));
    bounds[2] = (sint16)((uint32)camera_x + (left.vz < 0 ? 2u : 0xFFFFFFFFu));
    bounds[3] = (sint16)((uint32)camera_z + (left.vx > 0 ? 2u : 0xFFFFFFFFu));
    bounds[4] = (sint16)(((uint32)camera_x + (uint32)(left.vx >> 2) + (left.vz < 0 ? 2u : 0u)) & 0xFFFEu);
    bounds[5] = (sint16)(((uint32)camera_z + (uint32)(left.vz >> 2) + (left.vx > 0 ? 2u : 0u)) & 0xFFFEu);
    bounds[6] = (sint16)(((uint32)camera_x + (uint32)(right.vx >> 2) + (right.vz > 0 ? 2u : 0u)) & 0xFFFEu);
    bounds[7] = (sint16)(((uint32)camera_z + (uint32)(right.vz >> 2) + (right.vx < 0 ? 2u : 0u)) & 0xFFFEu);
    (void)SetFogNearFar(1280, 4096, (sint32)r_u32(0x800659D8u));
    sub_800289D8(0u, bounds);
    (void)SetFogNearFar(10240, 20480, (sint32)r_u32(0x800659D8u));
    shift = 1;
    for (detail = 1; detail < 3; ++detail, --shift) {
        uint32 mask = 0u - (2u << detail), increment = 1u << (detail + 1);
        bounds[2] = bounds[4]; bounds[3] = bounds[5];
        bounds[0] = bounds[6]; bounds[1] = bounds[7];
        bounds[4] = (sint16)(((uint32)camera_x + (uint32)(left.vx >> shift) + (left.vz < 0 ? increment : 0u)) & mask);
        bounds[5] = (sint16)(((uint32)camera_z + (uint32)(left.vz >> shift) + (left.vx > 0 ? increment : 0u)) & mask);
        bounds[6] = (sint16)(((uint32)camera_x + (uint32)(right.vx >> shift) + (right.vz > 0 ? increment : 0u)) & mask);
        bounds[7] = (sint16)(((uint32)camera_z + (uint32)(right.vz >> shift) + (right.vx < 0 ? increment : 0u)) & mask);
        sub_800289D8((uint32)detail, bounds);
    }
    first = r_u32(0x1F800014u);
    frame = r_u32(0x80065308u);
    second = r_u32(0x1F800018u);
    third = r_u32(0x1F80001Cu);
    count = (uint32)((sint32)((first - 0x80092220u - frame * 32256u) * 0xB6DB6DB7u) >> 2);
    if ((sint32)r_u32(0x80065B0Cu) < (sint32)count) w_u32(0x80065B0Cu, count);
    count = (uint32)((sint32)((second - 0x8007A9A0u - frame * 40960u) * 0xCCCCCCCDu) >> 3);
    if ((sint32)r_u32(0x80065B24u) < (sint32)count) w_u32(0x80065B24u, count);
    count = (uint32)((sint32)((third - 0x8008E9A0u - frame * 832u) * 0xC4EC4EC5u) >> 2);
    if ((sint32)r_u32(0x80065B28u) < (sint32)count) w_u32(0x80065B28u, count);
}

uint32 sub_800255F4(uint32 x, uint32 z);
uint32 v8_native_vector_length_host(const sint32 *vector);
uint32 sub_80017160(void);
uint32 sub_8003CF90(uint32 mask, uint32 source, uint32 incoming_v1);
uint32 sub_8002036C(uint32 object, uint32 incoming_s1);
void sub_80045088(uint32 address);
uint32 sub_8001FCB4(uint32 object, uint32 time);
uint32 v8_native_terrain_call3(uint32 callback, uint32 object, uint32 mode, uint32 value);

void sub_8002131C(uint32 ticks)
{
    uint32 node = r_u32(0x80065A60u), next = r_u32(node), object, callback;
    FUNCTION_MARKER(0x8002131Cu, "SLUS_005.10");
    while (next != 0u) {
        object = r_u32(node + 8u);
        if (object == 0u) break;
        callback = r_u32(object + 100u);
        if (callback != 0u) (void)v8_native_terrain_call3(callback, object, 0u, ticks);
        node = next; next = r_u32(node);
    }
}

void sub_80012980(void)
{
    uint32 resource;
    FUNCTION_MARKER(0x80012980u, "SLUS_005.10");
    resource = r_u32(0x8006590Cu);
    if (resource != 0u) {
        sub_80045088(resource);
        w_u32(0x8006590Cu, 0u);
    }
}

void sub_800212C4(uint32 time)
{
    uint32 node = r_u32(0x80065A80u), next = r_u32(node);
    FUNCTION_MARKER(0x800212C4u, "SLUS_005.10");
    while (next != 0u) {
        (void)sub_8001FCB4(r_u32(node + 8u), time & 0xFFFFu);
        node = next; next = r_u32(node);
    }
}

uint32 sub_8001FE8C(uint32 list, uint32 object)
{
    uint32 node = r_u32(list), next = r_u32(node), previous, free_tail;
    FUNCTION_MARKER(0x8001FE8Cu, "SLUS_005.10");
    while (next != 0u) {
        if (r_u32(node + 8u) == object) {
            previous = r_u32(node + 4u); next = r_u32(node);
            w_u32(next + 4u, previous); w_u32(previous, next);
            free_tail = r_u32(0x80065A78u);
            w_u32(0x80065A78u, node); w_u32(free_tail, node);
            w_u32(node + 4u, free_tail); w_u32(node, 0x80065A74u);
            w_u32(node + 8u, 0u);
            return 1u;
        }
        node = next; next = r_u32(node);
    }
    return 0u;
}

uint32 sub_80020890(uint32 object, uint32 delay)
{
    uint32 node, next, position, previous, deadline;
    FUNCTION_MARKER(0x80020890u, "SLUS_005.10");
    if ((r_u32(object) & 1u) != 0u) (void)sub_8001FE8C(0x80065AC0u, object);
    node = r_u32(0x80065A70u); next = r_u32(node);
    w_u32(next + 4u, 0x80065A70u); w_u32(0x80065A70u, next);
    w_u32(node + 8u, object);
    deadline = delay + r_u32(0x80065310u);
    w_u32(object, r_u32(object) | 1u); w_u32(node + 12u, deadline);
    position = r_u32(0x80065AC0u); next = r_u32(position);
    while (next != 0u && r_u32(position + 12u) < deadline) {
        position = next; next = r_u32(position);
    }
    previous = r_u32(position + 4u);
    w_u32(previous, node); w_u32(position + 4u, node);
    w_u32(node, position); w_u32(node + 4u, previous);
    return previous;
}

uint32 sub_80020120(uint32 list, uint32 mask)
{
    uint32 node = r_u32(list), next = r_u32(node), count = 0u, object, flags;
    FUNCTION_MARKER(0x80020120u, "SLUS_005.10");
    while (next != 0u) {
        object = r_u32(node + 8u);
        if ((sint16)r_u16(object + 6u) >= 32) {
            flags = r_u32(object);
            if ((flags & mask) != 0u && (flags & 0x8002u) == 0u) ++count;
        }
        node = next; next = r_u32(node);
    }
    return count;
}

uint32 sub_80020190(uint32 list, uint32 mask, uint32 index)
{
    uint32 node = r_u32(list), next = r_u32(node), object, flags;
    FUNCTION_MARKER(0x80020190u, "SLUS_005.10");
    while (next != 0u) {
        object = r_u32(node + 8u);
        if ((sint16)r_u16(object + 6u) >= 32) {
            flags = r_u32(object);
            if ((flags & mask) != 0u && (flags & 0x8002u) == 0u && --index == 0xFFFFFFFFu)
                return object;
        }
        node = next; next = r_u32(node);
    }
    return 0u;
}

uint32 sub_8003D0D0(uint32 mask, uint32 source)
{
    uint32 node = source, count = 0u, product, index, object;
    FUNCTION_MARKER(0x8003D0D0u, "SLUS_005.10");
    while (node != 0u) { node = r_u32(node + 52u); ++count; }
    product = sub_80017160() * count;
    index = (uint32)((sint32)product >> 15);
    node = source;
    while (index-- != 0u) node = r_u32(node + 52u);
    object = sub_8003CF90(mask, node, product);
    if (object != 0u) {
        w_u32(source, r_u32(source) | 0x8000u);
        (void)sub_8002036C(object, object);
    }
    return object;
}

uint32 sub_800239C0(uint32 mask)
{
    uint32 result, random, count, source;
    FUNCTION_MARKER(0x800239C0u, "SLUS_005.10");
    result = r_u32(0x80065A10u) < (uint32)(sint32)(sint16)r_u16(0x800658EAu);
    while (result != 0u) {
        random = sub_80017160();
        count = sub_80020120(0x80065A50u, mask);
        source = sub_80020190(0x80065A50u, mask, (uint32)((sint32)(random * count) >> 15));
        result = sub_8003D0D0(mask, source);
        if (result == 0u) break;
        count = r_u32(0x80065A10u) + 1u;
        w_u32(0x80065A10u, count);
        result = count < (uint32)(sint32)(sint16)r_u16(0x800658EAu);
    }
    return result;
}

uint32 sub_80023A60(void)
{
    uint32 result, mask, random, count, source;
    FUNCTION_MARKER(0x80023A60u, "SLUS_005.10");
    result = r_u32(0x80065AACu) < (uint32)(sint32)(sint16)r_u16(0x800658ECu);
    while (result != 0u) {
        mask = 0x780000u;
        if (((sint8)r_u8(0x80065319u) == 3 &&
             r_u32(0x800659ECu) >= (uint32)(sint32)(sint16)r_u16(0x800658EEu)) ||
            (sub_80017160() & 3u) == 0u) mask = 0x380000u;
        random = sub_80017160();
        count = sub_80020120(0x80065A50u, mask);
        source = sub_80020190(0x80065A50u, mask, (uint32)((sint32)(random * count) >> 15));
        result = sub_8003D0D0(mask, source);
        if (result == 0u) break;
        count = r_u32(0x80065AACu) + 1u;
        w_u32(0x80065AACu, count);
        result = count < (uint32)(sint32)(sint16)r_u16(0x800658ECu);
    }
    return result;
}

static void setup_missing(const char *name)
{
    fprintf(stderr, "Missing gameplay setup dependency %s\n", name);
    abort();
}

uint32 sub_80016AAC(uint32 first, uint32 second)
{
    sint32 delta[3];
    uint32 i;
    for (i = 0u; i < 3u; ++i)
        delta[i] = (sint32)(r_u32(first + i * 4u) - r_u32(second + i * 4u));
    return v8_native_vector_length_host(delta);
}

uint32 sub_80023D00(void)
{
    uint32 candidates[16][2], count = 0u, active = 0u, alive = 0u;
    uint32 mask = 0x7E000000u, needed = 0u, limit, node, next, object, i, result;
    uint32 flags, distance, target, other, state, sum, x, z;
    FUNCTION_MARKER(0x80023D00u, "SLUS_005.10");
    limit = (r_u32(0x80065908u) & 0x1000u) != 0u ? 3u :
            ((sint8)r_u8(0x8006531Au) != 0 ? 2u : 1u);
    w_u32(0x80065AE8u, r_u32(0x80065AE8u) + 1u);
    state = (uint32)(sint32)(sint8)r_u8(0x80065319u);
    if (state == 1u || state == 4u)
        setup_missing("80023B40");
    node = r_u32(0x80065A18u);
    next = r_u32(node);
    while (next != 0u) {
        object = r_u32(node + 8u);
        if (r_u8(object + 4u) != 2u)
            goto advance;
        if ((sint16)r_u16(object + 6u) < 0) {
            if (r_u32(object + 280u) == 0u) needed = 1u;
            for (i = 0u; i < 3u; ++i) {
                other = r_u32(object + 272u + i * 4u);
                if (other != 0u && r_u16(other + 12u) >= 2u * r_u16(other + 14u))
                    mask &= ~(0x01000000u << ((uint32)(sint32)(sint8)r_u8(other + 8u) & 31u));
            }
            goto advance;
        }
        flags = r_u32(object);
        if (r_u16(object + 12u) == 0u || (flags & 0x02000000u) != 0u)
            goto count_alive;
        if ((sint16)r_u16(object + 24u) < 0) {
            w_u32(object + 152u, r_u32(object + 152u) + 0x10000u);
            goto count_alive;
        }
        if ((flags & 0x200000u) != 0u) {
            x = r_u32(object + 36u); z = r_u32(object + 44u);
            if (x < r_u32(0x80065B34u) || r_u32(0x80065B38u) < x ||
                z < r_u32(0x80065B3Cu) || r_u32(0x80065B40u) < z ||
                (sint16)r_u16(sub_800255F4(x, z) + 22u) == 7) {
                if ((sint8)r_u8(object + 8u) != 1 || (r_u32(0x80065AE8u) & 3u) == 0u)
                    setup_missing("80021DB0 recovery matrix");
            }
        }
        state = (uint32)(sint32)(sint8)r_u8(object + 8u);
        if (state == 1u || state == 4u)
            goto count_alive;
        target = r_u32(0x80065AD4u);
        distance = sub_80016AAC(target + 36u, object + 36u);
        if ((sint8)r_u8(0x80065319u) == 4) {
            other = sub_80016AAC(r_u32(0x80065AD8u) + 36u, object + 36u);
            if (other < distance) {
                distance = other;
                target = r_u32(0x80065AD8u);
            }
        }
        w_u32(object + 228u, target);
        if ((sint32)(r_u16(object + 172u) * 3u / 4u) < (sint16)r_u16(object + 166u) &&
            (sint32)r_u32(object + 140u) < 457) {
            w_u8(object + 178u, 255u); w_u16(object + 164u, 0u);
            w_u8(object + 8u, 0u); w_u16(object + 166u, r_u16(object + 172u) >> 2);
            goto check_pickup;
        }
        if (state == 0u || (state == 2u && distance > 0x1F4000u)) {
            w_u8(object + 8u, 3u); w_u16(object + 232u, 0u);
            goto enqueue;
        }
        if (r_u32(object + 276u) != 0u) {
            sum = r_u16(r_u32(object + 236u) + 12u) + r_u16(r_u32(object + 240u) + 12u) +
                  r_u16(r_u32(object + 244u) + 12u);
            if ((sint32)r_u16(object + 12u) < (sint32)sum) {
                if (state == 2u) ++active;
                else goto enqueue;
                goto check_pickup;
            }
        }
        if (state == 2u) {
            w_u8(object + 8u, 3u); w_u16(object + 232u, 0u);
        }
        goto check_pickup;
enqueue:
        if (count >= 16u) setup_missing("80023D00 original candidate array overflow");
        candidates[count][0] = object; candidates[count][1] = distance; ++count;
check_pickup:
        if (r_u32(object + 272u) == 0u) needed = 1u;
count_alive:
        if ((r_u32(object) & 0x4000u) != 0u || r_u16(object + 12u) != 0u) ++alive;
advance:
        node = next; next = r_u32(node);
    }
    if (needed != 0u)
        (void)sub_800239C0(mask != 0u ? mask : 0x7F000000u);
    (void)sub_80023A60();
    result = active < limit;
    if ((uint32)(r_u8(0x80065319u) - 2u) < 2u)
        return result;
    if (active < limit) {
        uint32 swapped;
        do {
            swapped = 0u;
            for (i = 0u; i + 1u < count; ++i) {
                if (candidates[i + 1u][1] < candidates[i][1]) {
                    uint32 saved[2] = { candidates[i][0], candidates[i][1] };
                    candidates[i][0] = candidates[i + 1u][0]; candidates[i][1] = candidates[i + 1u][1];
                    candidates[i + 1u][0] = saved[0]; candidates[i + 1u][1] = saved[1];
                    swapped = 1u; break;
                }
            }
        } while (swapped != 0u);
        for (i = 0u; active < limit; ++i) {
            result = i < count;
            if (i >= count) break;
            ++active; w_u8(candidates[i][0] + 8u, 2u); result = active < limit;
        }
    }
    if (alive == 0u) {
        result = r_u32(0x80065928u);
        if (result == 0u) {
            if ((sint8)r_u8(0x80065319u) == 0 && (sint8)r_u8(0x80065ACCu) < 0) {
                w_u8(0x80065ACCu, r_u8(0x80065ACCu) & 127u);
                setup_missing("80021F30 additional opponent and announcement");
            }
            target = r_u32(r_u32(0x80065AD4u) + 224u);
            flags = r_u32(target);
            w_u32(0x80065328u, 1u); w_u32(0x80065928u, 1u);
            result = 0x20000u; w_u32(target, flags | result);
        }
    }
    return result;
}
