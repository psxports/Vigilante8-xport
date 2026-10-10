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
    uint32 packed;
    uint16 angle;
    uint32 x, y, z;

    FUNCTION_MARKER(0x8001B2FCu, "SLUS_005.10");
    packed = r_u32(descriptor + 16u);
    angle = r_u16(descriptor + 20u);
    w_u32(node + 64u, packed);
    w_u16(node + 68u, angle);
    x = r_u32(descriptor + 4u);
    y = r_u32(descriptor + 8u);
    z = r_u32(descriptor + 12u);
    w_u32(node + 72u, x);
    w_u32(node + 76u, y);
    w_u32(node + 80u, z);
    sub_8001D708(node);
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
    uint32 output[3], i;
    v8_native_43408(matrix, vector, output);
    for (i = 0u; i < 3u; ++i)
        w_u32(destination + 4u * i, output[i]);
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
    MATRIX matrix;
    uint32 object;
    uint32 ordering_table;

    FUNCTION_MARKER(0x8003E520u, "SLUS_005.10");
    CompMatrixLV((MATRIX *)psx_addr(0x8006F680u, sizeof(MATRIX)),
        (MATRIX *)psx_addr(model + 4u, sizeof(MATRIX)), &matrix);
    object = r_u32(model);
    ordering_table = r_u32(0x80065910u);
    return v8_native_1BE5C(object, &matrix, ordering_table);
}

uint32 sub_80021C20(uint32 index)
{
    uint32 offset;
    uint32 callback;
    uint32 object;

    FUNCTION_MARKER(0x80021C20u, "SLUS_005.10");
    offset = (index & 0xFFFFu) << 2;
    callback = r_u32(0x8005EC34u + offset);
    object = r_u32(0x800737A0u + offset);
    return v8_native_21B80(callback, object, 0u, 0u);
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
    V8PhysicsVectors vectors;
    uint32 matrix = object + 16u;
    uint32 properties = object + 164u;
    uint32 wheel, table, surface, scratch, node, flags, callback, packed;
    uint32 i, j, bounds;
    uint16 heading, countdown;
    sint32 cosine, sine, radius, height, limit, ground;
    sint32 normal_speed, lateral_speed, longitudinal_speed;
    sint32 load, friction_limit, friction, lateral, stiffness;
    sint32 value, delta, damping, result;
    sint32 camera_target[3], camera_position[3], camera_step;
    uint64 dot;

    FUNCTION_MARKER(0x8002F9BCu, "SLUS_005.10");
    w_u32(object, r_u32(object) & 0xFF8FFFFFu);
    for (i = 0u; i < 3u; ++i)
    {
        vectors.torque[i] = 0;
        vectors.force[i] = 0;
    }
    wheel = r_u32(object + 252u);
    node = r_u32(object + 256u);
    heading = r_u16(object + 164u);
    w_u16(node + 66u, heading);
    w_u16(wheel + 66u, heading);
    value = (sint32)sub_80016A20(object + 128u);
    limit = (sint16)r_u16(object + 24u);
    w_u32(object + 140u, (uint32)(value / 128));
    if (limit > 0)
    {
        v8_native_4352C(matrix, (const sint32 *)psx_addr(object + 128u, 12u), vectors.velocity);
        for (i = 0u; i < 4u; ++i)
        {
            wheel = r_u32(object + 252u + 4u * i);
            vectors.offset[0] = (sint32)r_u32(wheel + 72u);
            vectors.offset[1] = v8_physics_add((sint32)r_u32(wheel + 76u), (sint32)r_u32(wheel + 144u));
            vectors.offset[2] = (sint32)r_u32(wheel + 80u);
            scratch = 0x1F800000u + 24u * i;
            v8_physics_transform(matrix, vectors.offset, (sint32 *)psx_addr(scratch, 12u), 1u);
            ground = sub_8001D748(object, (const sint32 *)psx_addr(scratch, 12u),
                (sint16 *)psx_addr(scratch + 16u, 6u), (uint32 *)psx_addr(scratch + 12u, 4u));
            w_u32(scratch + 4u, (uint32)ground);
        }
        for (i = 0u; i < 4u; ++i)
        {
            wheel = r_u32(object + 252u + 4u * i);
            table = 0x800607B4u + 4u * (r_u16(wheel + 66u) & 0xFFFu);
            cosine = (sint16)r_u16(table);
            sine = (sint16)r_u16(table + 2u);
            vectors.lever[0] = (sint32)r_u32(wheel + 72u);
            vectors.lever[1] = v8_physics_add((sint32)r_u32(wheel + 76u), (sint32)r_u32(wheel + 144u));
            vectors.lever[2] = (sint32)r_u32(wheel + 80u);
            radius = (sint32)r_u32(object + 148u);
            value = v8_physics_mul(radius, (sint32)r_u32(wheel + 80u));
            vectors.wheel_velocity[0] = v8_physics_add(vectors.velocity[0], value / 4096);
            vectors.wheel_velocity[1] = vectors.velocity[1];
            radius = (sint32)r_u32(object + 148u);
            value = v8_physics_mul(radius, (sint32)r_u32(wheel + 72u));
            vectors.wheel_velocity[2] = v8_physics_sub(vectors.velocity[2], value / 4096);
            scratch = 0x1F800000u + 24u * i;
            for (j = 0u; j < 3u; ++j)
                vectors.contact[j] = (sint32)r_u32(scratch + 4u * j);
            packed = r_u32(scratch + 16u);
            vectors.normal[0] = (sint16)(uint16)packed;
            vectors.normal[1] = (sint16)(uint16)(packed >> 16);
            packed = r_u32(scratch + 20u);
            vectors.normal[2] = (sint16)(uint16)packed;
            vectors.normal[3] = (sint16)(uint16)(packed >> 16);
            surface = r_u32(scratch + 12u);
            v8_native_435C0(matrix, vectors.contact, vectors.local_contact);
            vectors.local_contact[1] = v8_physics_sub(vectors.local_contact[1], (sint32)r_u32(wheel + 144u));
            limit = (sint32)r_u32(wheel + 132u);
            if (vectors.local_contact[1] >= limit)
                w_u32(wheel + 76u, (uint32)limit);
            else
            {
                flags = r_u32(object);
                w_u32(object, flags | (surface == 0u ? 0x100000u : 0x300000u));
                value = (sint32)r_u32(object + 128u);
                dot = (uint64)((sint64)vectors.normal[0] * value);
                value = (sint32)r_u32(object + 132u);
                dot += (uint64)((sint64)vectors.normal[1] * value);
                value = (sint32)r_u32(object + 136u);
                dot += (uint64)((sint64)vectors.normal[2] * value);
                normal_speed = (sint32)((sint64)dot >> 15);
                v8_physics_transform_normal(matrix, vectors.normal, vectors.rotated_normal);
                delta = v8_physics_sub((sint32)r_u32(wheel + 72u), vectors.local_contact[0]);
                if (delta >= 0)
                    delta = 0;
                value = v8_physics_mul(v8_physics_neg(vectors.rotated_normal[0]), normal_speed);
                vectors.correction[0] = v8_physics_sub(value / 4096, delta);
                delta = v8_physics_sub((sint32)r_u32(wheel + 80u), vectors.local_contact[2]);
                if (delta >= 0)
                    delta = 0;
                value = v8_physics_mul(v8_physics_neg(vectors.rotated_normal[2]), normal_speed);
                vectors.correction[2] = v8_physics_sub(value / 4096, delta);
                height = (sint32)r_u32(wheel + 128u);
                if (height < vectors.local_contact[1])
                    height = vectors.local_contact[1];
                value = v8_physics_sub((sint32)r_u32(wheel + 132u), height);
                value = v8_physics_mul(value, (sint16)r_u16(wheel + 140u));
                value = (sint32)((uint32)value << 7);
                vectors.correction[1] = v8_physics_div(value, vectors.rotated_normal[1]);
                height = (sint32)r_u32(wheel + 128u);
                if (height >= vectors.local_contact[1] && (sint32)r_u32(wheel + 76u) >= vectors.local_contact[1])
                {
                    delta = v8_physics_sub(vectors.local_contact[1], (sint32)r_u32(wheel + 76u));
                    vectors.correction[1] = v8_physics_add(vectors.correction[1], (sint32)((uint32)delta << 4));
                    w_u32(object, r_u32(object) | 0x400000u);
                }
                else
                {
                    delta = v8_physics_sub(vectors.local_contact[1], (sint32)r_u32(wheel + 76u));
                    value = v8_physics_mul(delta, (sint16)r_u16(wheel + 142u));
                    vectors.correction[1] = v8_physics_add(vectors.correction[1], value / 32);
                }
                w_u32(wheel + 76u, (uint32)vectors.local_contact[1]);
                stiffness = surface == 0u ? 0 : (sint16)r_u16(surface + 16u);
                if (stiffness != 0)
                {
                    value = v8_physics_mul(v8_physics_neg(vectors.correction[1]), v8_physics_sub(256, stiffness));
                    load = value >> 7;
                }
                else
                    load = (sint32)((uint32)v8_physics_neg(vectors.correction[1]) << 1);
                if ((r_u32(wheel) & 0x20000u) != 0u)
                {
                    dot = (uint64)((sint64)vectors.wheel_velocity[0] * sine);
                    dot -= (uint64)((sint64)vectors.wheel_velocity[2] * cosine);
                    lateral_speed = (sint32)((sint64)dot >> 17);
                    dot = (uint64)((sint64)vectors.velocity[0] * cosine);
                    dot += (uint64)((sint64)vectors.velocity[2] * sine);
                    longitudinal_speed = (sint32)((sint64)dot >> 14);
                }
                else
                {
                    lateral_speed = vectors.wheel_velocity[0] >> 5;
                    longitudinal_speed = vectors.velocity[2] >> 2;
                }
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
                    else if ((sint8)r_u8(properties + 14u) <= 0)
                        friction = v8_physics_neg(friction);
                    else
                    {
                        value = v8_physics_neg(longitudinal_speed) >> 2;
                        if (friction_limit < value)
                            friction = value;
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
                stiffness = surface == 0u ? 0 : (sint16)r_u16(surface + 18u);
                if (stiffness != 0)
                {
                    value = longitudinal_speed >> 8;
                    delta = value < 0 ? v8_physics_neg(value) : value;
                    delta = v8_physics_mul(v8_physics_mul(value, delta), stiffness) >> 12;
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
                value = v8_physics_add(v8_physics_mul(cosine, friction), v8_physics_mul(sine, lateral));
                vectors.correction[0] = v8_physics_add(vectors.correction[0], value >> 12);
                value = v8_physics_sub(v8_physics_mul(sine, friction), v8_physics_mul(cosine, lateral));
                vectors.correction[2] = v8_physics_add(vectors.correction[2], value >> 12);
                xport_gte_write_control(0u, (uint32)(vectors.lever[0] >> 3));
                xport_gte_write_control(2u, (uint32)(vectors.lever[1] >> 3));
                xport_gte_write_control(4u, (uint32)(vectors.lever[2] >> 3));
                for (j = 0u; j < 3u; ++j)
                    xport_gte_write_data(9u + j, (uint32)v8_physics_clip(vectors.correction[j] >> 3, -32768, 32767));
                xport_gte_execute(0x0178000Cu);
                v8_physics_accumulate(&vectors);
                if (surface != 0u)
                {
                    value = (sint16)r_u16(surface + 22u);
                    if (value != 0 && value != 7)
                    {
                        callback = r_u32(0x80065A34u);
                        /* Pass the addressable host point to the terrain callback */
                        v8_native_point_callback(callback, wheel, 9u, vectors.contact);
                    }
                }
            }
            value = v8_physics_add(v8_physics_mul(cosine, vectors.wheel_velocity[0]), v8_physics_mul(sine, vectors.wheel_velocity[2]));
            value /= 4096;
            delta = v8_physics_mul(value, (sint32)r_u32(wheel + 148u));
            w_u32(wheel + 152u, (uint32)value);
            heading = r_u16(wheel + 64u);
            w_u16(wheel + 64u, (uint16)((uint32)heading - (uint32)(delta / 0x80000)));
        }
        for (i = 0u; i < 4u; ++i)
            sub_8001D708(r_u32(object + 252u + 4u * i));
        v8_physics_transform(matrix, vectors.force, vectors.force, 0u);
    }
    else
    {
        bounds = r_u32(object + 92u) + 4u;
        for (i = 0u; i < 8u; ++i)
        {
            vectors.wheel_velocity[0] = (sint32)r_u32(bounds + ((i & 1u) != 0u ? 0u : 12u));
            vectors.wheel_velocity[1] = (sint32)r_u32(bounds + ((i & 2u) != 0u ? 4u : 16u));
            vectors.wheel_velocity[2] = (sint32)r_u32(bounds + ((i & 4u) != 0u ? 8u : 20u));
            v8_physics_transform(matrix, vectors.wheel_velocity, vectors.wheel_velocity, 1u);
            ground = sub_8001D748(object, vectors.wheel_velocity, NULL, &vectors.surface);
            if (v8_physics_sub(vectors.wheel_velocity[1], ground) > 0)
            {
                value = v8_physics_neg((sint32)r_u32(object + 128u));
                vectors.correction[0] = v8_physics_clip(value / 4, -2880, 2880);
                value = v8_physics_neg((sint32)r_u32(object + 136u));
                vectors.correction[2] = v8_physics_clip(value / 4, -2880, 2880);
                vectors.correction[1] = v8_physics_sub(ground, vectors.wheel_velocity[1]);
                value = (sint32)r_u32(object + 132u);
                if (value > 0)
                    vectors.correction[1] = v8_physics_sub(vectors.correction[1], value >> 2);
                for (j = 0u; j < 3u; ++j)
                {
                    delta = v8_physics_sub(vectors.wheel_velocity[j], (sint32)r_u32(object + 72u + 4u * j));
                    xport_gte_write_control(2u * j, (uint32)(delta >> 3));
                }
                for (j = 0u; j < 3u; ++j)
                    xport_gte_write_data(9u + j, (uint32)(vectors.correction[j] >> 3));
                xport_gte_execute(0x0178000Cu);
                v8_physics_accumulate(&vectors);
                surface = vectors.surface;
                if (surface != 0u)
                {
                    value = (sint16)r_u16(surface + 22u);
                    if (value != 0 && value != 7)
                    {
                        callback = r_u32(0x80065A34u);
                        /* Pass the addressable host point to the terrain callback */
                        v8_native_point_callback(callback, object, 9u, vectors.wheel_velocity);
                    }
                }
                if ((sint32)r_u32(object + 132u) >= 19457)
                    w_u32(object, r_u32(object) | 0x400000u);
            }
        }
        v8_native_4352C(matrix, vectors.torque, vectors.torque);
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
    vectors.force[1] = v8_physics_add(vectors.force[1], (sint32)r_u32(0x80065334u));
    value = (sint32)r_u32(object + 140u);
    delta = (sint32)r_u32(object + 220u);
    damping = v8_physics_mul(value, delta);
    for (i = 0u; i < 3u; ++i)
    {
        value = (sint32)r_u32(object + 128u + 4u * i);
        delta = (sint32)(((sint64)value * damping) >> 32);
        vectors.force[i] = v8_physics_sub(vectors.force[i], delta);
    }
    v8_native_173FC(object, vectors.force, vectors.torque);
    for (i = 0u; i < 3u; ++i)
    {
        value = (sint32)r_u32(object + 144u + 4u * i);
        w_u32(object + 144u + 4u * i, (uint32)v8_physics_sub(value, value / 32));
    }
    for (i = 0u; i < 3u; ++i)
    {
        node = r_u32(object + 272u + 4u * i);
        if (node != 0u)
        {
            countdown = r_u16(node + 6u);
            if (countdown != 0u)
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
        return (uint32)result;
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
        for (i = 0u; i < 3u; ++i)
            vectors.offset[i] = (sint32)r_u32(object + 36u + 4u * i);
        for (i = 0u; i < 3u; ++i)
            w_u32(object + 72u + 4u * i, (uint32)vectors.offset[i]);
    }
    return (uint32)result;
}

uint32 sub_8002F998(uint32 object)
{
    FUNCTION_MARKER(0x8002F998u, "SLUS_005.10");
    return sub_8002F9BC(object);
}
