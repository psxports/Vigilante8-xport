#include "psx.h"
uint32 v8_native_21B80(uint32 callback, uint32 asset, uint32 kind, uint32 flags);
#include "xport_trace.h"

uint32 sub_8001178C(uint32 count, uint32 size);
uint32 sub_8001D708(uint32 node);
uint32 sub_8001B49C(uint32 object, uint32 index, uint32 incoming_s1);
uint32 sub_8001BE5C(uint32 model, uint32 matrix, uint32 ordering_table);
uint32 sub_8004366C(uint32 matrix);
uint32 sub_8002A350(uint32 object, uint32 mode, uint32 kind, uint32 table);
uint32 sub_80021B80(uint32 callback, uint32 object, uint32 kind, uint32 value);
uint32 sub_80016A20(uint32 vector);
uint32 sub_80043358(uint32 matrix, uint32 vector, uint32 destination);
sint32 sub_8001D748(uint32 object, const sint32 *point, sint16 *normal, uint32 *surface);
uint32 v8_native_173FC(uint32 object, const sint32 *force, const sint32 *torque);
void v8_native_4352C(uint32 matrix, const sint32 *source, sint32 *destination);
void v8_native_435C0(uint32 matrix, const sint32 *source, sint32 *destination);
uint32 v8_native_1BE5C(uint32 model, const MATRIX *matrix, uint32 ordering_table);
uint32 v8_native_point_callback(uint32 target, uint32 object, uint32 event, const sint32 *point);

uint32 sub_8001D4F0(uint32 parent, uint32 child)
{
    uint32 node;
    uint32 next;

    FUNCTION_MARKER(0x8001D4F0u, "SLUS_005.10");
    node = r_u32(parent + 56u);
    if (node == 0u)
    {
        w_u32(parent + 56u, child);
        w_u32(child + 60u, parent);
        return 0u;
    }
    next = r_u32(node + 52u);
    while (next != 0u)
    {
        node = r_u32(node + 52u);
        next = r_u32(node + 52u);
    }
    w_u32(node + 52u, child);
    w_u32(child + 60u, node);
    return next;
}

uint32 sub_8001B2FC(uint32 parent, uint32 descriptor, uint32 node)
{
    uint32 packed, angle, address, offset, x, y, z;
    FUNCTION_MARKER(0x8001B2FCu, "SLUS_005.10");
    address = descriptor + 19u;
    offset = address & 3u;
    packed = r_u32(address & ~3u) << (8u * (3u - offset));
    address = descriptor + 16u;
    offset = address & 3u;
    packed = (packed & (offset == 0u ? 0u : 0xFFFFFFFFu << (8u * (4u - offset)))) | (r_u32(address & ~3u) >> (8u * offset));
    angle = (uint32)(sint32)(sint16)r_u16(descriptor + 20u);
    address = node + 67u;
    offset = address & 3u;
    w_masked_u32(address & ~3u, packed >> (8u * (3u - offset)), (1u << (offset + 1u)) - 1u);
    address = node + 64u;
    offset = address & 3u;
    w_masked_u32(address & ~3u, packed << (8u * offset), (15u << offset) & 15u);
    w_u16(node + 68u, angle);
    x = r_u32(descriptor + 4u);
    y = r_u32(descriptor + 8u);
    z = r_u32(descriptor + 12u);
    w_u32(node + 72u, x);
    w_u32(node + 76u, y);
    w_u32(node + 80u, z);
    (void)sub_8001D708(node);
    return sub_8001D4F0(parent, node);
}

uint32 sub_8001BDA0(uint32 object, uint32 index, uint32 incoming_s1)
{
    uint32 base;
    uint32 kind;

    FUNCTION_MARKER(0x8001BDA0u, "SLUS_005.10");
    base = r_u32(object);
    kind = r_u16(base + 28u * (index & 0xFFFFu) + 28u) & 0x7FFu;
    return sub_8001B49C(object, kind, incoming_s1);
}

uint32 sub_8001D470(uint32 bytes)
{
    FUNCTION_MARKER(0x8001D470u, "SLUS_005.10");
    return sub_8001178C(bytes, 1u);
}

void v8_native_43408(uint32 matrix, uint32 vector, uint32 *destination)
{
    uint32 rotation[5];
    uint32 translation[3];
    uint32 input[3];
    uint32 high[3];
    uint32 low[3];
    uint32 i;

    FUNCTION_MARKER(0x80043408u, "SLUS_005.10");
    for (i = 0u; i < 5u; ++i)
        rotation[i] = r_u32(matrix + 4u * i);
    for (i = 0u; i < 5u; ++i)
        xport_gte_write_control(i, rotation[i]);
    for (i = 0u; i < 3u; ++i)
        input[i] = r_u32(vector + 4u * i);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_data(9u + i, (uint32)((sint32)input[i] >> 15));
    xport_gte_execute(0x0041E012u);
    for (i = 0u; i < 3u; ++i)
        translation[i] = r_u32(matrix + 20u + 4u * i);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_control(5u + i, translation[i]);
    for (i = 0u; i < 3u; ++i)
        high[i] = xport_gte_read_data(25u + i);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_data(9u + i, input[i] & 0x7FFFu);
    xport_gte_execute(0x00498012u);
    for (i = 0u; i < 3u; ++i)
        low[i] = xport_gte_read_data(25u + i);
    for (i = 0u; i < 3u; ++i)
        destination[i] = low[i] + (high[i] << 3);
}

uint32 sub_80043408(uint32 matrix, uint32 vector, uint32 destination)
{
    uint32 words[5], values[3], translation[3], high[3], low[3], i;
    FUNCTION_MARKER(0x80043408u, "SLUS_005.10");
    for (i = 0u; i < 5u; ++i)
        words[i] = r_u32(matrix + 4u * i);
    for (i = 0u; i < 5u; ++i)
        xport_gte_write_control(i, words[i]);
    for (i = 0u; i < 3u; ++i)
        values[i] = r_u32(vector + 4u * i);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_data(9u + i, (uint32)((sint32)values[i] >> 15));
    xport_gte_execute(0x0041E012u);
    for (i = 0u; i < 3u; ++i)
        translation[i] = r_u32(matrix + 20u + 4u * i);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_control(5u + i, translation[i]);
    for (i = 0u; i < 3u; ++i)
        high[i] = xport_gte_read_data(25u + i);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_data(9u + i, values[i] & 0x7FFFu);
    xport_gte_execute(0x00498012u);
    for (i = 0u; i < 3u; ++i)
        low[i] = xport_gte_read_data(25u + i);
    for (i = 0u; i < 3u; ++i)
        w_u32(destination + 4u * i, low[i] + (high[i] << 3));
    return destination;
}

uint32 sub_800434D0(uint32 matrix, uint32 vector, uint32 destination)
{
    uint32 result;

    FUNCTION_MARKER(0x800434D0u, "SLUS_005.10");
    xport_gte_write_data(0u, r_u32(vector));
    xport_gte_write_data(1u, r_u32(vector + 4u));
    result = sub_8004366C(matrix);
    xport_gte_execute(0x00486012u);
    w_u32(destination, xport_gte_read_data(9u));
    w_u32(destination + 4u, xport_gte_read_data(10u));
    w_u32(destination + 8u, xport_gte_read_data(11u));
    return result;
}

uint32 sub_8002A454(uint32 object, uint32 mode, uint32 kind)
{
    FUNCTION_MARKER(0x8002A454u, "SLUS_005.10");
    return sub_8002A350(object, mode, kind, 0x8005EACCu);
}

uint32 sub_8002A508(uint32 object, uint32 mode, uint32 kind)
{
    FUNCTION_MARKER(0x8002A508u, "SLUS_005.10");
    return sub_8002A350(object, mode, kind, 0x8005EB80u);
}

uint32 sub_8003E520(uint32 model)
{
    uint32 frame, object, ordering_table, result;
    FUNCTION_MARKER(0x8003E520u, "SLUS_005.10");
    frame = xport_guest_frame_acquire(56u);
    (void)CompMatrixLV((MATRIX *)psx_addr(0x8006F680u, sizeof(MATRIX)),
        (MATRIX *)psx_addr(model + 4u, sizeof(MATRIX)),
        (MATRIX *)psx_addr(frame + 16u, sizeof(MATRIX)));
    object = r_u32(model);
    ordering_table = r_u32(0x80065910u);
    result = sub_8001BE5C(object, frame + 16u, ordering_table);
    xport_guest_frame_release(frame, 56u);
    return result;
}

uint32 sub_80021C20(uint32 index)
{
    uint32 sub_80021B80(uint32 callback, uint32 asset, uint32 kind, uint32 flags);
    uint32 offset;
    uint32 callback;
    uint32 object;

    FUNCTION_MARKER(0x80021C20u, "SLUS_005.10");
    offset = (index & 0xFFFFu) << 2;
    callback = r_u32(0x8005EC34u + offset);
    object = r_u32(0x800737A0u + offset);
    return sub_80021B80(callback, object, 0u, 0u);
}

static sint32 v8_physics_add(sint32 left, sint32 right)
{
    return (sint32)((uint32)left + (uint32)right);
}

static sint32 v8_physics_sub(sint32 left, sint32 right)
{
    return (sint32)((uint32)left - (uint32)right);
}

static sint32 v8_physics_mul(sint32 left, sint32 right)
{
    return (sint32)((uint32)left * (uint32)right);
}

static sint32 v8_physics_neg(sint32 value)
{
    return (sint32)(0u - (uint32)value);
}

static sint32 v8_physics_div(sint32 numerator, sint32 denominator)
{
    if (denominator == 0)
        return numerator < 0 ? 1 : -1;
    if ((uint32)numerator == 0x80000000u && denominator == -1)
        return numerator;
    return numerator / denominator;
}

static sint32 v8_physics_clip(sint32 value, sint32 low, sint32 high)
{
    if (value < low)
        return low;
    return value > high ? high : value;
}

typedef struct V8PhysicsVectors
{
    sint32 torque[3];
    sint32 force[3];
    sint32 velocity[3];
    sint32 offset[3];
    sint32 correction[3];
    sint32 lever[3];
    sint32 contact[3];
    sint32 local_contact[3];
    sint32 wheel_velocity[3];
    sint16 normal[4];
    sint32 rotated_normal[3];
    uint32 surface;
} V8PhysicsVectors;

static void v8_physics_transform(uint32 matrix, const sint32 *source, sint32 *destination, uint32 translate)
{
    uint32 rotation[5], translation[3], input[3], high[3], low[3];
    uint32 i;

    for (i = 0u; i < 5u; ++i)
        rotation[i] = r_u32(matrix + 4u * i);
    for (i = 0u; i < 5u; ++i)
        xport_gte_write_control(i, rotation[i]);
    for (i = 0u; i < 3u; ++i)
        input[i] = (uint32)source[i];
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_data(9u + i, (uint32)((sint32)input[i] >> 15));
    xport_gte_execute(0x0041E012u);
    if (translate != 0u)
    {
        for (i = 0u; i < 3u; ++i)
            translation[i] = r_u32(matrix + 20u + 4u * i);
        for (i = 0u; i < 3u; ++i)
            xport_gte_write_control(5u + i, translation[i]);
    }
    for (i = 0u; i < 3u; ++i)
        high[i] = xport_gte_read_data(25u + i);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_data(9u + i, input[i] & 0x7FFFu);
    xport_gte_execute(translate != 0u ? 0x00498012u : 0x0049E012u);
    for (i = 0u; i < 3u; ++i)
        low[i] = xport_gte_read_data(25u + i);
    for (i = 0u; i < 3u; ++i)
        destination[i] = (sint32)(low[i] + (high[i] << 3));
}

static void v8_physics_transform_normal(uint32 matrix, const sint16 *source, sint32 *destination)
{
    uint32 result;

    xport_gte_write_data(0u, (uint32)(uint16)source[0] | ((uint32)(uint16)source[1] << 16));
    xport_gte_write_data(1u, (uint32)(uint16)source[2] | ((uint32)(uint16)source[3] << 16));
    result = sub_8004366C(matrix);
    (void)result;
    xport_gte_execute(0x00486012u);
    destination[0] = (sint32)xport_gte_read_data(9u);
    destination[1] = (sint32)xport_gte_read_data(10u);
    destination[2] = (sint32)xport_gte_read_data(11u);
}

static void v8_physics_accumulate(V8PhysicsVectors *vectors)
{
    uint32 i;
    for (i = 0u; i < 3u; ++i)
        vectors->force[i] = v8_physics_add(vectors->force[i], vectors->correction[i]);
    for (i = 0u; i < 3u; ++i)
        vectors->torque[i] = v8_physics_add(vectors->torque[i], (sint32)xport_gte_read_data(25u + i));
}

uint32 sub_8002F9BC(uint32 object)
{
    uint32 sub_8004352C(uint32 matrix, uint32 source, uint32 destination);
    uint32 sub_800435C0(uint32 matrix, uint32 source, uint32 destination);
    uint32 sub_80043408(uint32 matrix, uint32 source, uint32 destination);
    uint32 sub_800434D0(uint32 matrix, uint32 source, uint32 destination);
    uint32 sub_800173FC(uint32 object, uint32 force, uint32 torque);
    uint32 frame, first, second, third, registers[32] = {0u};
    sint32 correction_x, correction_z, position_x, position_y, position_z;
    sint32 normal_x, normal_y, normal_z, normal_x_velocity_sign, drag_context;
    uint32 normal_pointer, velocity_pointer, normal_y_velocity_sign;
    uint32 x_high, z_high, x_cross, y_cross, y_velocity;
    uint64 x_product, y_product, z_product;
    sint32 gte_x, gte_y, gte_z, position_z_word, force_y, contact_y, correction_y;
    uint32 matrix = object + 16u;
    uint32 properties = object + 164u;
    uint32 wheel, table, surface, scratch, node, flags, callback;
    uint32 i, bounds;
    uint16 heading, countdown;
    sint32 cosine, sine, radius, height, limit, ground;
    sint32 normal_speed, lateral_speed, longitudinal_speed;
    sint32 load, friction_limit, friction, lateral, stiffness;
    sint32 value, delta, damping, result;
    sint32 camera_target[3], camera_position[3], camera_step;
    uint64 dot;

    FUNCTION_MARKER(0x8002F9BCu, "SLUS_005.10");
    frame = 0x1F8002C8u;
    w_u32(object, r_u32(object) & 0xFF8FFFFFu);
    for (i = 0u; i < 3u; ++i)
        w_u32(frame + 16u + 4u * i, 0u);
    for (i = 0u; i < 3u; ++i)
        w_u32(frame + 32u + 4u * i, 0u);
    wheel = r_u32(object + 252u);
    node = r_u32(object + 256u);
    heading = r_u16(object + 164u);
    w_u16(node + 66u, heading);
    w_u16(wheel + 66u, heading);
    w_u32(frame + 188u, properties);
    value = (sint32)sub_80016A20(object + 128u);
    limit = (sint16)r_u16(object + 24u);
    w_u32(object + 140u, (uint32)(value / 128));
    if (limit > 0)
    {
        sub_8004352C(matrix, object + 128u, frame + 48u);
        for (i = 0u; i < 4u; ++i)
        {
            wheel = r_u32(object + 252u + 4u * i);
            w_u32(frame + 64u, (uint32)((sint32)r_u32(wheel + 72u)));
            first = r_u32(wheel + 76u);
            second = r_u32(wheel + 144u);
            w_u32(frame + 68u, first + second);
            w_u32(frame + 72u, (uint32)((sint32)r_u32(wheel + 80u)));
            scratch = 0x1F800000u + 24u * i;
            sub_80043408(matrix, frame + 64u, scratch);
            ground = sub_8001D748(object, (const sint32 *)psx_addr(scratch, 12u),
                (sint16 *)psx_addr(scratch + 16u, 6u), (uint32 *)psx_addr(scratch + 12u, 4u));
            w_u32(scratch + 4u, (uint32)ground);
        }
        w_u32(frame + 196u, frame + 144u);
        w_u32(frame + 200u, frame + 160u);
        w_u32(frame + 204u, object + 128u);
        for (i = 0u; i < 4u; ++i)
        {
            wheel = r_u32(object + 252u + 4u * i);
            table = 0x800607B4u + 4u * (r_u16(wheel + 66u) & 0xFFFu);
            cosine = (sint16)r_u16(table);
            sine = (sint16)r_u16(table + 2u);
            first = r_u32(wheel + 72u);
            w_u32(frame + 192u, (uint32)sine);
            w_u32(frame + 96u, first);
            first = r_u32(wheel + 76u);
            second = r_u32(wheel + 144u);
            w_u32(frame + 100u, first + second);
            w_u32(frame + 104u, (uint32)((sint32)r_u32(wheel + 80u)));
            radius = (sint32)r_u32(object + 148u);
            value = v8_physics_mul(radius, (sint32)r_u32(wheel + 80u));
            first = r_u32(frame + 48u);
            second = r_u32(frame + 52u);
            third = r_u32(frame + 196u);
            w_u32(frame + 144u, first + (uint32)(value / 4096));
            w_u32(third + 4u, second);
            radius = (sint32)r_u32(object + 148u);
            value = v8_physics_mul(radius, (sint32)r_u32(wheel + 72u));
            first = r_u32(frame + 56u);
            third = r_u32(frame + 196u);
            w_u32(third + 8u, first - (uint32)(value / 4096));
            scratch = 0x1F800000u + 24u * i;
            first = r_u32(scratch);
            second = r_u32(scratch + 4u);
            third = r_u32(scratch + 8u);
            w_u32(frame + 112u, first);
            w_u32(frame + 116u, second);
            w_u32(frame + 120u, third);
            first = r_u32(scratch + 16u);
            second = r_u32(scratch + 20u);
            w_u32(frame + 160u, first);
            w_u32(frame + 164u, second);
            surface = r_u32(scratch + 12u);
            w_u32(frame + 208u, surface);
            sub_800435C0(matrix, frame + 112u, frame + 128u);
            height = r_s32(frame + 132u);
            value = r_s32(wheel + 144u);
            height = v8_physics_sub(height, value);
            w_u32(frame + 132u, (uint32)height);
            limit = r_s32(wheel + 132u);
            if (height >= limit)
                w_u32(wheel + 76u, (uint32)limit);
            else
            {
                surface = r_u32(frame + 208u);
                flags = r_u32(object);
                w_u32(object, flags | (surface == 0u ? 0x100000u : 0x300000u));
                normal_x = r_s16(frame + 160u);
                value = r_s32(object + 128u);
                normal_pointer = r_u32(frame + 200u);
                velocity_pointer = r_u32(frame + 204u);
                normal_x_velocity_sign = value >> 31;
                x_product = (uint64)(uint32)normal_x * (uint32)value;
                normal_y = r_s16(normal_pointer + 2u);
                y_velocity = r_u32(velocity_pointer + 4u);
                y_product = (uint64)(uint32)normal_y * y_velocity;
                normal_z = r_s16(normal_pointer + 4u);
                w_u32(frame + 216u, (uint32)y_product);
                w_u32(frame + 220u, (uint32)(y_product >> 32));
                third = r_u32(velocity_pointer + 8u);
                z_product = (uint64)(uint32)normal_z * third;
                x_cross = (uint32)v8_physics_mul(normal_x, normal_x_velocity_sign);
                x_high = (uint32)(x_product >> 32) + x_cross
                    + (uint32)v8_physics_mul(value, normal_x >> 31);
                normal_y_velocity_sign = (uint32)v8_physics_mul(normal_y, (sint32)y_velocity >> 31);
                y_cross = (uint32)v8_physics_mul((sint32)y_velocity, normal_y >> 31);
                z_high = (uint32)(z_product >> 32)
                    + (uint32)v8_physics_mul(normal_z, (sint32)third >> 31)
                    + (uint32)v8_physics_mul((sint32)third, normal_z >> 31);
                w_u32(frame + 232u, x_cross);
                first = r_u32(frame + 220u) + normal_y_velocity_sign;
                w_u32(frame + 220u, first);
                first += y_cross;
                w_u32(frame + 220u, first);
                first = r_u32(frame + 216u);
                second = r_u32(frame + 220u);
                dot = ((uint64)x_high << 32) | (uint32)x_product;
                dot += ((uint64)second << 32) | first;
                dot += ((uint64)z_high << 32) | (uint32)z_product;
                normal_speed = (sint32)((sint64)dot >> 15);
                normal_pointer = r_u32(frame + 200u);
                sub_800434D0(matrix, normal_pointer, frame + 168u);
                value = v8_physics_mul(v8_physics_neg(r_s32(frame + 168u)), normal_speed);
                first = r_u32(wheel + 72u);
                second = r_u32(frame + 128u);
                delta = (sint32)(first - second);
                if (delta >= 0)
                    delta = 0;
                w_u32(frame + 80u, (uint32)(v8_physics_sub(value / 4096, delta)));
                value = v8_physics_mul(v8_physics_neg(r_s32(frame + 176u)), normal_speed);
                first = r_u32(wheel + 80u);
                second = r_u32(frame + 136u);
                delta = (sint32)(first - second);
                if (delta >= 0)
                    delta = 0;
                w_u32(frame + 88u, (uint32)(v8_physics_sub(value / 4096, delta)));
                height = r_s32(wheel + 128u);
                contact_y = r_s32(frame + 132u);
                if (height < contact_y)
                    height = contact_y;
                value = r_s32(wheel + 132u);
                stiffness = r_s16(wheel + 140u);
                value = v8_physics_mul(v8_physics_sub(value, height), stiffness);
                value = (sint32)((uint32)value << 7);
                correction_y = v8_physics_div(value, r_s32(frame + 172u));
                w_u32(frame + 84u, (uint32)correction_y);
                height = r_s32(wheel + 128u);
                if (height < contact_y)
                {
                    value = r_s32(wheel + 76u);
                    stiffness = r_s16(wheel + 142u);
                    value = v8_physics_mul(v8_physics_sub(contact_y, value), stiffness);
                    correction_y = v8_physics_add(correction_y, value / 32);
                    w_u32(frame + 84u, (uint32)correction_y);
                }
                else
                {
                    value = r_s32(wheel + 76u);
                    delta = v8_physics_sub(contact_y, value);
                    if (value < contact_y)
                    {
                        value = r_s32(wheel + 76u);
                        stiffness = r_s16(wheel + 142u);
                        value = v8_physics_mul(v8_physics_sub(contact_y, value), stiffness);
                        correction_y = v8_physics_add(correction_y, value / 32);
                        w_u32(frame + 84u, (uint32)correction_y);
                    }
                    else
                    {
                        correction_y = v8_physics_add(correction_y, (sint32)((uint32)delta << 4));
                        w_u32(frame + 84u, (uint32)correction_y);
                        w_u32(object, r_u32(object) | 0x400000u);
                    }
                }
                contact_y = r_s32(frame + 132u);
                w_u32(wheel + 76u, (uint32)contact_y);
                surface = r_u32(frame + 208u);
                stiffness = surface == 0u ? 0 : (sint16)r_u16(surface + 16u);
                if (stiffness != 0)
                {
                    value = v8_physics_mul(v8_physics_neg(r_s32(frame + 84u)), v8_physics_sub(256, stiffness));
                    load = value >> 7;
                }
                else
                    load = (sint32)((uint32)v8_physics_neg(r_s32(frame + 84u)) << 1);
                if ((r_u32(wheel) & 0x20000u) != 0u)
                {
                    first = r_u32(frame + 144u);
                    sine = r_s32(frame + 192u);
                    dot = (uint64)((sint64)(sint32)first * sine);
                    first = r_u32(frame + 152u);
                    dot -= (uint64)((sint64)(sint32)first * cosine);
                    first = r_u32(frame + 48u);
                    lateral_speed = (sint32)((sint64)dot >> 17);
                    dot = (uint64)((sint64)(sint32)first * cosine);
                    first = r_u32(frame + 56u);
                    z_product = (uint64)((sint64)(sint32)first * sine);
                    w_u32(frame + 224u, (uint32)z_product);
                    w_u32(frame + 228u, (uint32)(z_product >> 32));
                    dot += z_product;
                    longitudinal_speed = (sint32)((sint64)dot >> 14);
                }
                else
                {
                    lateral_speed = r_s32(frame + 144u) >> 5;
                    longitudinal_speed = r_s32(frame + 56u) >> 2;
                }
                properties = r_u32(frame + 188u);
                value = (sint16)r_u16(properties + 2u);
                friction_limit = value < 0 ? v8_physics_neg(value) : value;
                friction_limit = (sint32)((uint32)friction_limit << 6);
                if (friction_limit > load)
                    friction_limit = load;
                friction = friction_limit;
                if (value >= 0)
                {
                    if ((r_u32(wheel) & 0x10000u) == 0u)
                        friction = 0;
                    else
                    {
                        properties = r_u32(frame + 188u);
                        if (r_s8(properties + 14u) <= 0)
                            friction = v8_physics_neg(friction);
                        else
                        {
                            value = v8_physics_neg(longitudinal_speed) >> 2;
                            if (friction_limit < value)
                                friction = value;
                        }
                    }
                }
                else if (longitudinal_speed <= 0)
                {
                    friction = v8_physics_neg(longitudinal_speed);
                    if (friction_limit < friction)
                        friction = friction_limit;
                }
                else
                {
                    friction = v8_physics_neg(longitudinal_speed);
                    value = v8_physics_neg(friction_limit);
                    if (friction < value)
                        friction = value;
                }
                surface = r_u32(frame + 208u);
                drag_context = (sint32)surface;
                stiffness = surface == 0u ? 0 : (sint16)r_u16(surface + 18u);
                if (stiffness != 0)
                {
                    value = longitudinal_speed >> 8;
                    delta = value < 0 ? v8_physics_neg(value) : value;
                    drag_context = v8_physics_mul(v8_physics_mul(value, delta), stiffness);
                    delta = drag_context >> 12;
                    friction = v8_physics_sub(friction, delta);
                }
                lateral = v8_physics_neg(lateral_speed);
                if (lateral_speed <= 0)
                {
                    if (load < lateral)
                        lateral = load;
                }
                else if (lateral < v8_physics_neg(load))
                    lateral = v8_physics_neg(load);
                sine = r_s32(frame + 192u);
                value = v8_physics_add(v8_physics_mul(cosine, friction), v8_physics_mul(sine, lateral));
                correction_x = r_s32(frame + 80u);
                position_x = r_s32(frame + 96u) >> 3;
                position_y = r_s32(frame + 100u) >> 3;
                position_z = r_s32(frame + 104u) >> 3;
                correction_z = r_s32(frame + 88u);
                correction_x = v8_physics_add(correction_x, value >> 12);
                w_u32(frame + 80u, (uint32)correction_x);
                value = v8_physics_sub(v8_physics_mul(sine, friction), v8_physics_mul(cosine, lateral));
                correction_z = v8_physics_add(correction_z, value >> 12);
                w_u32(frame + 88u, (uint32)correction_z);
                xport_gte_write_control(0u, (uint32)position_x);
                xport_gte_write_control(2u, (uint32)position_y);
                xport_gte_write_control(4u, (uint32)position_z);
                gte_x = v8_physics_clip(correction_x >> 3, -32768, 32767);
                value = r_s32(frame + 84u);
                gte_y = v8_physics_clip(value >> 3, -32768, 32767);
                gte_z = v8_physics_clip(correction_z >> 3, -32768, 32767);
                xport_gte_write_data(9u, (uint32)gte_x);
                xport_gte_write_data(10u, (uint32)gte_y);
                xport_gte_write_data(11u, (uint32)gte_z);
                xport_gte_execute(0x0178000Cu);
                first = r_u32(frame + 32u);
                w_u32(frame + 32u, first + (uint32)correction_x);
                first = r_u32(frame + 36u);
                second = r_u32(frame + 84u);
                third = r_u32(frame + 40u);
                w_u32(frame + 36u, first + second);
                second = r_u32(frame + 88u);
                w_u32(frame + 40u, third + second);
                value = (sint32)xport_gte_read_data(25u);
                first = r_u32(frame + 16u);
                w_u32(frame + 16u, first + (uint32)value);
                value = (sint32)xport_gte_read_data(26u);
                first = r_u32(frame + 20u);
                w_u32(frame + 20u, first + (uint32)value);
                value = (sint32)xport_gte_read_data(27u);
                first = r_u32(frame + 24u);
                surface = r_u32(frame + 208u);
                w_u32(frame + 24u, first + (uint32)value);
                if (surface != 0u)
                {
                    value = (sint16)r_u16(surface + 22u);
                    if (value != 0 && value != 7)
                    {
                        callback = r_u32(0x80065A34u);
                        registers[2] = callback;
                        registers[4] = wheel;
                        registers[5] = 9u;
                        registers[6] = frame + 112u;
                        registers[3] = (uint32)value;
                        registers[7] = (uint32)correction_z;
                        registers[16] = (uint32)friction;
                        registers[17] = (uint32)normal_x_velocity_sign;
                        registers[18] = normal_y_velocity_sign;
                        registers[19] = (uint32)(normal_x >> 31);
                        registers[20] = wheel;
                        registers[21] = i;
                        registers[22] = object;
                        registers[23] = (uint32)drag_context;
                        registers[28] = 0x80065304u;
                        registers[29] = frame;
                        registers[30] = (uint32)cosine;
                        registers[31] = 0x80030370u;
                        xport_guest_call_known_registers(callback, registers, 0xF0FF00FDu);
                    }
                }
            }
            first = r_u32(frame + 144u);
            sine = r_s32(frame + 192u);
            second = r_u32(frame + 152u);
            value = v8_physics_add(v8_physics_mul(cosine, (sint32)first), v8_physics_mul(sine, (sint32)second));
            value /= 4096;
            delta = v8_physics_mul(value, (sint32)r_u32(wheel + 148u));
            w_u32(wheel + 152u, (uint32)value);
            heading = r_u16(wheel + 64u);
            w_u16(wheel + 64u, (uint16)((uint32)heading - (uint32)(delta / 0x80000)));
        }
        for (i = 0u; i < 4u; ++i)
            sub_8001D708(r_u32(object + 252u + 4u * i));
        sub_80043358(matrix, frame + 32u, frame + 32u);
    }
    else
    {
        bounds = r_u32(object + 92u) + 4u;
        for (i = 0u; i < 8u; ++i)
        {
            w_u32(frame + 144u, (uint32)((sint32)r_u32(bounds + ((i & 1u) != 0u ? 0u : 12u))));
            (void)r_u32(frame + 144u);
            w_u32(frame + 148u, (uint32)((sint32)r_u32(bounds + ((i & 2u) != 0u ? 4u : 16u))));
            (void)r_u32(frame + 148u);
            w_u32(frame + 152u, (uint32)((sint32)r_u32(bounds + ((i & 4u) != 0u ? 8u : 20u))));
            (void)r_u32(frame + 152u);
            sub_80043408(matrix, frame + 144u, frame + 144u);
            ground = sub_8001D748(object, (const sint32 *)psx_addr(frame + 144u, 12u),
                NULL, (uint32 *)psx_addr(frame + 184u, 4u));
            height = r_s32(frame + 148u);
            delta = v8_physics_sub(height, ground);
            if (delta > 0)
            {
                value = v8_physics_neg((sint32)r_u32(object + 128u));
                w_u32(frame + 96u, (uint32)(v8_physics_clip(value / 4, -2880, 2880)));
                value = v8_physics_neg((sint32)r_u32(object + 136u));
                correction_z = v8_physics_clip(value / 4, -2880, 2880);
                w_u32(frame + 104u, (uint32)correction_z);
                correction_y = v8_physics_neg(delta);
                w_u32(frame + 100u, (uint32)correction_y);
                value = r_s32(object + 132u);
                if (value > 0)
                {
                    correction_y = v8_physics_sub(correction_y, value >> 2);
                    w_u32(frame + 100u, (uint32)correction_y);
                }
                first = r_u32(frame + 144u);
                second = r_u32(object + 72u);
                position_x = (sint32)(first - second) >> 3;
                first = r_u32(frame + 148u);
                second = r_u32(object + 76u);
                position_y = (sint32)(first - second) >> 3;
                first = r_u32(frame + 152u);
                second = r_u32(object + 80u);
                position_z_word = (sint32)second;
                position_z = (sint32)(first - second) >> 3;
                xport_gte_write_control(0u, (uint32)position_x);
                xport_gte_write_control(2u, (uint32)position_y);
                xport_gte_write_control(4u, (uint32)position_z);
                correction_x = r_s32(frame + 96u);
                value = r_s32(frame + 100u);
                xport_gte_write_data(9u, (uint32)(correction_x >> 3));
                xport_gte_write_data(10u, (uint32)(value >> 3));
                xport_gte_write_data(11u, (uint32)(correction_z >> 3));
                xport_gte_execute(0x0178000Cu);
                first = r_u32(frame + 32u);
                third = r_u32(frame + 36u);
                w_u32(frame + 32u, first + (uint32)correction_x);
                first = third;
                second = r_u32(frame + 100u);
                third = r_u32(frame + 40u);
                w_u32(frame + 36u, first + second);
                second = r_u32(frame + 104u);
                w_u32(frame + 40u, third + second);
                value = (sint32)xport_gte_read_data(25u);
                first = r_u32(frame + 16u);
                w_u32(frame + 16u, first + (uint32)value);
                value = (sint32)xport_gte_read_data(26u);
                first = r_u32(frame + 20u);
                w_u32(frame + 20u, first + (uint32)value);
                value = (sint32)xport_gte_read_data(27u);
                first = r_u32(frame + 24u);
                surface = r_u32(frame + 184u);
                w_u32(frame + 24u, first + (uint32)value);
                if (surface != 0u)
                {
                    value = (sint16)r_u16(surface + 22u);
                    if (value != 0 && value != 7)
                    {
                        callback = r_u32(0x80065A34u);
                        registers[2] = callback;
                        registers[4] = object;
                        registers[5] = 9u;
                        registers[6] = frame + 144u;
                        registers[3] = (uint32)value;
                        registers[7] = (uint32)position_z_word;
                        registers[16] = frame + 144u;
                        registers[17] = bounds;
                        registers[18] = frame + 32u;
                        registers[19] = frame + 96u;
                        registers[21] = i;
                        registers[22] = object;
                        registers[28] = 0x80065304u;
                        registers[29] = frame;
                        registers[31] = 0x800306A4u;
                        xport_guest_call_known_registers(callback, registers, 0xB06F00FDu);
                    }
                }
                if ((sint32)r_u32(object + 132u) >= 19457)
                    w_u32(object, r_u32(object) | 0x400000u);
            }
        }
        sub_8004352C(matrix, frame + 16u, frame + 16u);
        for (i = 0u; i < 4u; ++i)
        {
            wheel = r_u32(object + 252u + 4u * i);
            value = (sint32)r_u32(wheel + 152u);
            height = (sint32)r_u32(wheel + 132u);
            w_u32(wheel + 76u, (uint32)height);
            value = v8_physics_sub(value, value / 64);
            w_u32(wheel + 152u, (uint32)value);
            delta = v8_physics_mul(value / 4096, (sint32)r_u32(wheel + 148u));
            heading = r_u16(wheel + 64u);
            w_u16(wheel + 64u, (uint16)((uint32)heading - (uint32)(delta / 0x80000)));
            sub_8001D708(wheel);
        }
    }
    first = r_u32(frame + 36u);
    second = r_u32(0x80065334u);
    force_y = (sint32)(first + second);
    w_u32(frame + 36u, (uint32)force_y);
    value = (sint32)r_u32(object + 140u);
    delta = (sint32)r_u32(object + 220u);
    damping = v8_physics_mul(value, delta);
    for (i = 0u; i < 3u; ++i)
    {
        value = (sint32)r_u32(object + 128u + 4u * i);
        dot = (uint64)((sint64)value * damping);
        if (i == 1u)
            value = force_y;
        else
            value = r_s32(frame + 32u + 4u * i);
        w_u32(frame + 224u, (uint32)dot);
        w_u32(frame + 228u, (uint32)(dot >> 32));
        delta = (sint32)(uint32)(dot >> 32);
        w_u32(frame + 32u + 4u * i, (uint32)v8_physics_sub(value, delta));
    }
    sub_800173FC(object, frame + 32u, frame + 16u);
    value = r_s32(object + 144u);
    delta = r_s32(object + 148u);
    w_u32(object + 144u, (uint32)v8_physics_sub(value, value / 32));
    value = r_s32(object + 152u);
    w_u32(object + 148u, (uint32)v8_physics_sub(delta, delta / 32));
    w_u32(object + 152u, (uint32)v8_physics_sub(value, value / 32));
    for (i = 0u; i < 3u; ++i)
    {
        node = r_u32(object + 272u + 4u * i);
        if (node != 0u)
        {
            value = r_s16(node + 6u);
            countdown = r_u16(node + 6u);
            if (value != 0)
                w_u16(node + 6u, (uint16)(countdown - 1u));
        }
    }
    for (i = 0u; i < 3u; ++i)
    {
        countdown = r_u16(object + 284u + 2u * i);
        if (countdown != 0u)
            w_u16(object + 284u + 2u * i, (uint16)(countdown - 1u));
    }
    flags = r_u32(object);
    result = (sint32)(flags & 0x800000u);
    if (result != 0)
    {
        return (uint32)result;
    }
    if (r_u16(object + 288u) != 0u)
    {
        camera_target[0] = (sint32)r_u32(object + 36u);
        camera_position[0] = (sint32)r_u32(object + 72u);
        camera_step = v8_physics_sub(camera_target[0], camera_position[0]) / 32;
        camera_target[1] = (sint32)r_u32(object + 40u);
        camera_position[1] = (sint32)r_u32(object + 76u);
        w_u32(object + 72u, (uint32)v8_physics_add(camera_position[0], camera_step));
        camera_step = v8_physics_sub(camera_target[1], camera_position[1]) / 32;
        camera_target[2] = (sint32)r_u32(object + 44u);
        camera_position[2] = (sint32)r_u32(object + 80u);
        w_u32(object + 76u, (uint32)v8_physics_add(camera_position[1], camera_step));
        camera_step = v8_physics_sub(camera_target[2], camera_position[2]) / 32;
        result = v8_physics_add(camera_position[2], camera_step);
        w_u32(object + 80u, (uint32)result);
    }
    else if ((sint16)r_u16(object + 6u) < 0 || (flags & 0x40000u) != 0u)
    {
        properties = r_u32(frame + 188u);
        camera_target[0] = (sint32)r_u32(object + 36u);
        camera_position[0] = (sint32)r_u32(object + 72u);
        stiffness = 256 - r_u8(properties + 16u);
        delta = v8_physics_mul(v8_physics_sub(camera_target[0], camera_position[0]), stiffness);
        camera_step = delta / 256;
        camera_target[1] = (sint32)r_u32(object + 40u);
        camera_position[1] = (sint32)r_u32(object + 76u);
        delta = v8_physics_mul(v8_physics_sub(camera_target[1], camera_position[1]), stiffness);
        w_u32(object + 72u, (uint32)v8_physics_add(camera_position[0], camera_step));
        camera_step = delta / 256;
        camera_target[2] = (sint32)r_u32(object + 44u);
        camera_position[2] = (sint32)r_u32(object + 80u);
        delta = v8_physics_mul(v8_physics_sub(camera_target[2], camera_position[2]), stiffness);
        w_u32(object + 76u, (uint32)v8_physics_add(camera_position[1], camera_step));
        result = v8_physics_add(camera_position[2], delta / 256);
        w_u32(object + 80u, (uint32)result);
    }
    else
    {
        first = r_u32(object + 36u);
        second = r_u32(object + 40u);
        third = r_u32(object + 44u);
        w_u32(object + 72u, first);
        w_u32(object + 76u, second);
        w_u32(object + 80u, third);
    }
    return (uint32)result;
}

uint32 sub_8002F998(uint32 object, uint32 incoming_sp, uint32 incoming_ra)
{
    void abort(void);
    uint32 result, restored_sp, restored_ra;
    FUNCTION_MARKER(0x8002F998u, "SLUS_005.10");
    w_u32(0x1F8003F0u, incoming_ra);
    w_u32(0x1F8003F4u, incoming_sp);
    result = sub_8002F9BC(object);
    restored_ra = r_u32(0x1F8003F0u);
    restored_sp = r_u32(0x1F8003F4u);
    if (restored_ra != incoming_ra || restored_sp != incoming_sp)
        abort();
    return result;
}
