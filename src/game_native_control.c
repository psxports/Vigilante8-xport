#include "psx.h"
#include <stdio.h>
#include <stdlib.h>

void sub_80045088(uint32 allocation);
uint32 sub_800116F4(uint32 bytes);
uint32 sub_8001FFD4(uint32 list, uint32 kind);
uint32 sub_80020120(uint32 list, uint32 mask);
uint32 sub_80020190(uint32 list, uint32 mask, uint32 index);
uint32 sub_80015368(uint32 text);
uint32 sub_80016AAC(uint32 first, uint32 second);
uint32 sub_8002EA94(uint32 object, uint32 clear);
uint32 sub_8004410C(void);
uint32 sub_80017160(void);
void sub_8004483C(uint32 voice, uint32 table, uint32 sample, uint32 position);
uint32 sub_8004445C(uint32 voice, uint32 table, uint32 sample);
uint32 sub_800447E8(uint32 voice, uint32 table, uint32 sample, uint32 position);
uint32 sub_8001D708(uint32 object);
uint32 sub_800446DC(uint32 position);
void sub_80044574(uint32 voice, uint32 volume);
uint32 v8_native_terrain_call3(uint32 callback, uint32 object, uint32 mode, uint32 value);
void v8_native_4352C(uint32 matrix, const sint32 *source, sint32 *destination);
uint32 v8_native_17594(uint32 object, const sint32 *impulse, uint32 point);
void sub_800441C8(uint32 voice);
uint32 sub_800443C8(uint32 voice, uint32 table, uint32 sample, uint32 volume, uint32 incoming_v0);

static sint32 control_product(sint32 first, sint32 second)
{
    return (sint32)((uint32)first * (uint32)second);
}

static void control_missing(const char *name)
{
    fprintf(stderr, "Missing vehicle control dependency %s\n", name);
    abort();
}

uint32 sub_80012068(uint32 lane, uint32 strength, uint32 secondary, uint32 duration)
{
    uint32 base = 0x80065940u + (lane << 3);
    FUNCTION_MARKER(0x80012068u, "SLUS_005.10");
    w_u8(base + 5u, strength);
    w_u8(base + 6u, secondary);
    w_u8(base + 7u, duration);
    return 0x80065940u;
}

uint32 sub_80022E38(uint32 object)
{
    uint32 weapon, callback;
    FUNCTION_MARKER(0x80022E38u, "SLUS_005.10");
    if ((sint32)r_u32(0x80065310u) >= 61) w_u8(object + 8u, 1u);
    weapon = r_u32(object + 268u);
    w_u16(object + 164u, 0u);
    w_u16(object + 166u, 60u);
    callback = r_u32(weapon + 100u);
    return callback != 0u ? v8_native_terrain_call3(callback, weapon, 11u, object) : 0u;
}

void sub_8002D054(uint32 object)
{
    uint32 flags = r_u32(object), volume, voice, input;
    uint32 base = 0x1F801BF0u + ((uint32)(sint32)(sint8)r_u8(object + 5u) << 4);
    sint32 pitch, direction, delta, gain, dot, speed;
    int special = (flags & 0x08000000u) != 0u;
    FUNCTION_MARKER(0x8002D054u, "SLUS_005.10");
    if (special) {
        sub_80044574((uint32)(sint32)(sint8)r_u8(object + 5u), sub_800446DC(object + 36u));
    } else {
        if ((flags & 0x100000u) != 0u) {
            direction = (sint8)r_u8(object + 178u);
            pitch = control_product((sint32)r_u32(object + 140u),
                r_u16(0x8005EC68u + 2u * (uint32)(direction + 1))) / 4096;
            if (pitch < 768 && direction >= 2) w_u8(object + 178u, r_u8(object + 178u) - 1u);
            if (pitch >= 2049 && r_u8(object + 178u) < 3u) w_u8(object + 178u, r_u8(object + 178u) + 1u);
            if (pitch < 768) pitch = 768;
        } else pitch = (sint16)r_u16(object + 166u) > 0 ? 2048 : 768;
        delta = (sint32)((uint32)pitch - (uint32)(sint32)(sint16)r_u16(object + 212u));
        if (delta < -128) delta = -128;
        if (delta > 128) delta = 128;
        pitch = r_u16(object + 212u) + delta;
        w_u16(object + 212u, pitch);
        w_u16(base + 4u, pitch);
        input = 0x80065C28u + 24u * ~(uint32)(sint32)(sint16)r_u16(object + 6u);
        gain = (sint16)r_u16(object + 214u);
        if ((r_u32(input + 8u) & 0x100u) != 0u) {
            gain += 128;
            if (gain > 4096) gain = 4096;
        } else {
            gain -= 128;
            if (gain < 2048) gain = 2048;
        }
        w_u16(object + 214u, gain);
        volume = sub_800446DC(object + 36u);
        gain = (sint16)r_u16(object + 214u);
        w_u16(base, control_product(volume & 0xFFFFu, gain) / 4096);
        w_u16(base + 2u, control_product((sint32)volume >> 16, gain) / 4096);
    }
    if ((r_u32(object) & 0x400000u) != 0u) {
        voice = sub_8004410C();
        sub_8004483C(voice, r_u32(0x800658FCu), (sint16)r_u16(object + 24u) > 0 ? 29u : 30u, object + 36u);
        (void)sub_80012068(~(uint32)(sint32)(sint16)r_u16(object + 6u), 192u, 0u, 64u);
    }
    flags = r_u32(object);
    speed = (sint32)r_u32(object + 140u);
    if ((flags & 0x100000u) == 0u || speed < 3052) {
        w_u32(object, flags & ~0x80000u);
    } else {
        dot = (sint32)((uint32)control_product((sint32)r_u32(object + 128u) / 128, (sint16)r_u16(object + 20u)) +
            (uint32)control_product((sint32)r_u32(object + 132u) / 128, (sint16)r_u16(object + 26u)) +
            (uint32)control_product((sint32)r_u32(object + 136u) / 128, (sint16)r_u16(object + 32u)));
        if (dot < 0) dot = (sint32)(0u - (uint32)dot);
        if (dot < control_product(3072, speed)) {
            if ((flags & 0x80000u) == 0u) {
                w_u32(object, flags | 0x80000u);
                voice = sub_8004410C();
                sub_8004483C(voice, r_u32(0x800658FCu), (sub_80017160() & 1u) != 0u ? 25u : 26u, object + 36u);
            }
        } else w_u32(object, r_u32(object) & ~0x80000u);
    }
    voice = r_u8(object + 211u);
    if (voice != 0u) {
        base = 0x1F801BF0u + (voice << 4);
        pitch = (sint32)r_u32(object + 140u) / 2;
        if (pitch < 768) w_u32(base, 0u);
        else {
            if (pitch > 3072) pitch = 3072;
            w_u16(base + 4u, pitch);
            /* TODO Resolve the incoming carried volume for the special drive path */
            if (special) control_missing("8002D054 special drive carried volume");
            w_u32(base, volume);
        }
    }
}

void sub_8002CE68(uint32 object, uint32 firing)
{
    uint32 weapon = r_u32(object + 272u + 4u * r_u8(object + 179u)), callback, delay, product;
    FUNCTION_MARKER(0x8002CE68u, "SLUS_005.10");
    if (weapon == 0u) return;
    if (firing != 0u && r_u16(weapon + 12u) != 0u && r_u16(weapon + 6u) == 0u) {
        callback = r_u32(weapon + 100u);
        w_u16(weapon + 6u, callback != 0u ? v8_native_terrain_call3(callback, weapon, 11u, object) : 0u);
        if ((sint16)r_u16(object + 6u) > 0 && (r_u32(weapon) & 0x40000u) == 0u) {
            delay = (2u - (uint32)(sint32)(sint8)r_u8(0x8006531Au)) <<
                    ((r_u32(object) & 0x40000u) != 0u ? 5u : 6u);
            product = sub_80017160() * delay;
            w_u16(weapon + 6u, r_u16(weapon + 6u) + delay + (uint32)((sint32)product >> 15));
        }
    } else {
        callback = r_u32(weapon + 100u);
        if (callback != 0u) (void)v8_native_terrain_call3(callback, weapon, 0u, object);
    }
}

uint32 sub_8002CF90(uint32 object, uint32 direction);
uint32 sub_8002ED34(uint32 object, uint32 previous);

void sub_8002D494(uint32 object, uint32 input)
{
    uint32 buttons = r_u32(input + 8u), flags = r_u32(object), reversed, target, camera, callback;
    uint32 weapon, voice, counter, i, result;
    FUNCTION_MARKER(0x8002D494u, "SLUS_005.10");
    reversed = (buttons & 0x40u) != 0u ? 0x20000000u : 0u;
    if ((flags & 0x20000000u) != reversed) {
        w_u32(object, flags ^ 0x20000000u);
        target = r_u32(object + 248u);
        w_u16(target + 66u, reversed != 0u ? 2048u : 0u);
        camera = r_u32(object + 224u);
        w_u16(camera + 142u, reversed != 0u ? 2048u : 0u);
        camera = r_u32(object + 224u);
        w_u32(camera + 152u, 0u - r_u32(camera + 152u));
        (void)sub_8001D708(r_u32(object + 248u));
    }
    if ((buttons & 0x180000u) != 0u) {
        result = sub_8002CF90(object, (buttons & 0x80000u) != 0u ? 1u : 0xFFFFFFFFu);
        w_u32(object, r_u32(object) & ~0x10000000u);
        voice = sub_8004410C();
        (void)sub_8004445C(voice, r_u32(0x800658FCu), result != 0u ? 22u : 21u);
        if (result != 0u) {
            weapon = r_u32(object + 272u + r_u8(object + 179u) * 4u);
            callback = r_u32(weapon + 100u);
            if (callback != 0u) (void)v8_native_terrain_call3(callback, weapon, 10u, object);
        }
    }
    if ((r_u32(object) & 0x10000000u) == 0u &&
        ((r_u32(0x80065310u) - r_u8(object + 9u)) & 63u) == 0u) {
        (void)sub_8002EA94(object, 0u);
    }
    if ((buttons & 0x200000u) != 0u) {
        target = 0u;
        if ((r_u32(object) & 0x10000000u) != 0u && r_s16(object + 188u) < 256)
            target = r_u32(object + 228u);
        w_u32(object + 228u, sub_8002ED34(object, target));
        w_u16(object + 188u, 0u);
        w_u32(object, r_u32(object) | 0x10000000u);
        voice = sub_8004410C();
        (void)sub_8004445C(voice, r_u32(0x800658FCu), 22u);
    }
    if ((buttons & 0x40000u) != 0u) {
        weapon = r_u32(object + 272u + r_u8(object + 179u) * 4u);
        if (weapon == 0u || r_u16(weapon + 6u) != 0u) {
            voice = sub_8004410C();
            (void)sub_8004445C(voice, r_u32(0x800658FCu), 21u);
        }
    }
    sub_8002CE68(object, buttons & 4u);
    counter = r_u16(object + 174u);
    if (counter != 0u) w_u16(object + 174u, counter - 1u);
    else if ((buttons & 0x20000u) != 0u && (sint32)r_u32(input + 4u) >= 257) {
        for (i = 0u; i < 3u; ++i) {
            weapon = r_u32(object + 272u + i * 4u);
            if (weapon == 0u || r_u16(weapon + 12u) == 0u) continue;
            callback = r_u32(weapon + 100u);
            result = callback != 0u ? v8_native_terrain_call3(callback, weapon, 9u, r_u32(input + 4u)) : 0u;
            if (result == 0u) continue;
            voice = sub_8004410C();
            (void)sub_800447E8(voice, r_u32(0x800658FCu), (sint32)result < 0 ? 21u : 42u, object + 36u);
            if ((sint32)result > 0) w_u16(object + 174u, result);
            w_u32(input + 4u, 0u);
            break;
        }
    }
    target = r_u32(object + 268u);
    callback = r_u32(target + 100u);
    if (callback != 0u) (void)v8_native_terrain_call3(callback, target, (buttons & 2u) != 0u ? 11u : 4u, object);
    counter = r_u16(object + 188u);
    if ((sint16)counter < 256) w_u16(object + 188u, counter + 8u);
}

void sub_8002EE94(uint32 object, uint32 controls)
{
    uint32 voice, sample, counter;
    FUNCTION_MARKER(0x8002EE94u, "SLUS_005.10");
    if ((controls & 0xFFFFu) != 0u) {
        if ((controls & 0xFFFF0000u) != 0u && (r_u32(object) & 0x100000u) != 0u) {
            if ((sint8)r_u8(object + 181u) > 0 && (sint32)r_u32(object + 140u) < 8392 &&
                (sint8)r_u8(object + 178u) > 0) {
                (void)v8_native_17594(object,
                    (const sint32 *)psx_addr(0x80065748u, 12u), 0x80065754u);
                w_u8(object + 181u, (uint8)-39);
                voice = sub_8004410C();
                sample = (sub_80017160() & 1u) != 0u ? 28u : 27u;
                sub_8004483C(voice, r_u32(0x800658FCu), sample, object + 36u);
            }
            if ((sint32)r_u32(object + 140u) < 2288) {
                voice = sub_8004410C();
                sample = (sub_80017160() & 1u) != 0u ? 28u : 27u;
                sub_8004483C(voice, r_u32(0x800658FCu), sample, object + 36u);
            }
        }
        counter = (sint8)r_u8(object + 181u) < -1 ? r_u8(object + 181u) + 1u : 15u;
    } else {
        counter = r_u8(object + 181u) - 1u;
        if ((sint8)r_u8(object + 181u) <= 0) return;
    }
    w_u8(object + 181u, counter);
}

void v8_native_2C59C(uint32 object, uint32 controls)
{
    uint32 counter, voice, value, table;
    FUNCTION_MARKER(0x8002C59Cu, "SLUS_005.10");
    if ((controls & 0xFFFFu) == 0u) {
        sub_800441C8((uint32)(sint32)(sint8)r_u8(object + 5u));
        return;
    }
    counter = (r_u16(object + 176u) - 1u) & 0xFFFFu;
    w_u16(object + 166u, 0u);
    w_u16(object + 176u, counter);
    if (counter == 0xFFFFu) {
        voice = (uint32)(sint32)(sint8)r_u8(object + 5u);
        w_u32(object, r_u32(object) & ~0x08000000u);
        if (voice == 0u) {
            value = sub_8004410C();
            w_u8(object + 5u, value);
            voice = (uint32)(sint32)(sint8)value;
        }
        value = r_u32(0x800737A0u + ((15u - (uint32)(sint32)(sint16)r_u16(object + 6u)) << 2));
        table = r_u32(value + 8u);
        (void)sub_800443C8(voice, table, 0u, 0u, value);
        voice = sub_8004410C();
        (void)sub_800447E8(voice, r_u32(0x800658FCu), 31u, object + 36u);
    } else if ((controls & 0xFFFF0000u) != 0u) {
        value = sub_80017160();
        w_u16(object + 176u, ((sint32)(value * 5u) >> 15) != 0 ? 300u : 19u);
        voice = (uint32)(sint32)(sint8)r_u8(object + 5u);
        if (voice == 0u) {
            value = sub_8004410C();
            w_u8(object + 5u, value);
            value <<= 24;
            voice = (uint32)((sint32)value >> 24);
        }
        (void)sub_800443C8(voice, r_u32(0x800658FCu), 33u, 0u, value);
    }
}

void sub_8002EFE0(uint32 object, uint32 input)
{
    sint32 type = (sint16)r_u16(input), steer, direction, speed, amount, factor, delta, value;
    uint32 buttons = r_u32(input + 8u), forward, reverse, controls, flags, flipped = 0u, camera;
    FUNCTION_MARKER(0x8002EFE0u, "SLUS_005.10");
    if (type != 2 && type != 3 && type != 4 && type != 5) return;
    if (type == 2) {
        direction = (sint8)r_u8(object + 178u);
        forward = direction < 0 ? 512u : 256u;
        reverse = direction < 0 ? 256u : 512u;
        if ((buttons & reverse) != 0u) {
            if ((sint32)r_u32(object + 140u) < 474)
                w_u8(object + 178u, direction < 0 ? 1u : 255u);
            else w_u16(object + 166u, 0u - r_u16(object + 172u));
        } else {
            controls = buttons & (forward | (forward << 16));
            if ((r_u32(object) & 0x08000000u) != 0u) {
                v8_native_2C59C(object, controls);
            } else {
                if ((r_u32(input + 12u) & 0xF0000000u) != 0u) controls &= 0xFFFFu;
                sub_8002EE94(object, controls);
                if ((controls & 0xFFFFu) != 0u) w_u16(object + 166u, r_u16(object + 172u));
                else w_u16(object + 166u, (sint16)r_u16(object + 166u) < 0 ? 0u : r_u16(object + 166u) - 2u);
            }
        }
        if ((buttons & 0x1800u) == 0u) {
            amount = control_product((sint16)r_u16(object + 164u), (sint32)r_u32(object + 140u)) / 32768;
            w_u16(object + 164u, r_u16(object + 164u) - (uint32)amount);
            if ((buttons & 0x400u) != 0u) w_u16(object + 166u, 0u - 2u * r_u16(object + 172u));
            return;
        }
        if ((sint16)r_u16(object + 24u) <= 0) {
            if ((buttons & 0x08000000u) != 0u) w_u32(object + 152u, r_u32(object + 152u) - 0x4000u);
            else if ((buttons & 0x10000000u) != 0u) w_u32(object + 152u, r_u32(object + 152u) + 0x4000u);
            return;
        }
        direction = (sint8)r_u8(object + 178u);
        flags = r_u32(object);
        if (direction > 0) w_u32(object, flags & ~0x40000000u);
        else {
            if ((buttons & 0x18000000u) != 0u) {
                flags &= ~0x40000000u;
                if (direction < 0) {
                    amount = (sint32)((uint32)control_product((sint16)r_u16(object + 20u), (sint32)r_u32(object + 128u) / 128) +
                                     (uint32)control_product((sint16)r_u16(object + 32u), (sint32)r_u32(object + 136u) / 128));
                    if ((buttons & forward) != 0u || amount < -4997120) flags |= 0x40000000u;
                }
                w_u32(object, flags);
            }
            flipped = (r_u32(object) >> 30) & 1u;
        }
        steer = (sint16)r_u16(object + 164u);
        if ((buttons & 0x400u) != 0u) {
            if ((buttons & 0x800u) != 0u) {
                steer -= 32; if (steer < -682) steer = -682;
                delta = flipped != 0u ? 1280 : -1280;
            } else {
                steer += 32; if (steer > 682) steer = 682;
                delta = flipped == 0u ? 1280 : -1280;
            }
            w_u16(object + 164u, steer);
            w_u32(object + 148u, r_u32(object + 148u) + (uint32)delta);
            return;
        }
        if ((buttons & 0x800u) != 0u) {
            steer = steer - 16 - (steer < 0 ? steer / 64 : 0);
            if (steer < -682) steer = -682;
        } else {
            steer = steer + 16 - (steer > 0 ? steer / 64 : 0);
            if (steer > 682) steer = 682;
        }
        w_u16(object + 164u, steer);
        steer = (sint16)steer;
        if (((buttons & 0x800u) != 0u && steer >= 0) || ((buttons & 0x800u) == 0u && steer <= 0)) return;
        factor = (sint32)((uint32)(sint32)(sint16)r_u16(object + 168u) +
                         (uint32)(control_product((sint32)r_u32(object + 140u), (sint16)r_u16(object + 170u)) / 4096));
        if (factor < 0) factor = 0;
        delta = control_product(control_product((sint32)(2u * flipped - 1u), steer), factor) / 16;
        w_u32(object + 148u, r_u32(object + 148u) - (uint32)delta);
        return;
    }
    if (type == 3) {
        w_u16(object + 164u, 5 * ((sint32)r_u8(input + 16u) - 128));
        value = r_u8(input + 17u);
        controls = (uint32)(value >= 129);
        if ((sint8)r_u8(input + 21u) >= 0) controls |= 0x10000u;
        if ((r_u32(object) & 0x08000000u) != 0u) v8_native_2C59C(object, controls);
        else {
            direction = (sint8)r_u8(object + 178u);
            if (direction < 0 && value >= 17) w_u8(object + 178u, 1u);
            else if ((buttons & 0x100u) != 0u) w_u8(object + 178u, 255u);
            amount = r_u16(object + 172u);
            if ((sint8)r_u8(object + 178u) >= 0) {
                steer = (sint16)r_u16(object + 164u); if (steer < 0) steer = -steer;
                if (r_u8(input + 18u) < 241u || steer < 170) value -= r_u8(input + 18u);
                amount = control_product(value, amount) / 256;
            } else if ((buttons & 0x100u) == 0u) amount = 0;
            w_u16(object + 166u, amount);
            sub_8002EE94(object, controls);
        }
    } else {
        camera = r_u32(object + 224u);
        value = (sint32)r_u8(input + 18u) - 128;
        if (value >= 33 || value <= -33) w_u16(camera + 142u, r_u16(camera + 142u) - (uint32)(value / 4));
        value = (sint32)r_u8(input + 19u) - 128;
        if (value >= 33 || value <= -33) {
            delta = (sint32)(r_u32(camera + 148u) + (uint32)(3051 * value / 128));
            amount = (sint32)(r_u32(object + 84u) * 2u);
            if (delta >= amount) amount = delta > 1310720 ? 1310720 : delta;
            w_u32(camera + 148u, (uint32)amount);
        }
        value = (sint32)r_u8(input + 16u) - 128;
        w_u16(object + 164u, value * (value < 0 ? -value : value) / 24);
        value = r_u8(input + 17u);
        controls = buttons & 0x01000100u;
        if (value < 64) controls |= 1u;
        if (value <= 64 && r_u8(input + 21u) >= 65u) controls |= 0x10000u;
        if ((r_u32(object) & 0x08000000u) != 0u) v8_native_2C59C(object, controls);
        else {
            direction = (sint8)r_u8(object + 178u) < 0 ? -1 : 1;
            amount = (buttons & 0x100u) != 0u ? r_u16(object + 172u) :
                     control_product(128 - value, r_u16(object + 172u)) / 128;
            w_u16(object + 166u, control_product(direction, amount));
            if ((sint32)r_u32(object + 140u) < 474 && (sint16)r_u16(object + 166u) < -16)
                w_u8(object + 178u, (sint8)r_u8(object + 178u) < 0 ? 1u : 255u);
            sub_8002EE94(object, controls);
        }
    }
    if ((sint16)r_u16(object + 24u) < 0) {
        delta = (sint32)r_u8(input + 16u) - (sint32)r_u8(input + 20u);
        w_u32(object + 152u, r_u32(object + 152u) + ((uint32)delta << 8));
        return;
    }
    steer = (sint16)r_u16(object + 164u);
    if ((buttons & 0x400u) != 0u || (type == 3 && r_u8(input + 18u) >= 241u)) {
        if (steer > -170 && steer < 170) w_u16(object + 166u, 0u - 2u * r_u16(object + 172u));
        delta = steer * ((sint8)r_u8(object + 178u) < 0 ? -2 : 2);
    } else {
        speed = (sint32)r_u32(object + 140u);
        factor = (sint32)((uint32)(sint32)(sint16)r_u16(object + 168u) +
                         (uint32)(control_product(speed, (sint16)r_u16(object + 170u)) / 4096));
        if (factor < 0) factor = 0;
        if ((sint8)r_u8(object + 178u) < 0) factor = (sint32)(0u - (uint32)factor);
        delta = control_product(steer, factor) / 16;
    }
    w_u32(object + 148u, r_u32(object + 148u) + (uint32)delta);
}

static void control_transform_position(uint32 position, sint32 *output)
{
    uint32 values[3], high[3], i;
    for (i = 0u; i < 3u; ++i)
        values[i] = r_u32(position + 4u * i);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_data(9u + i, (uint32)((sint32)values[i] >> 15));
    xport_gte_execute(0x41E012u);
    for (i = 0u; i < 3u; ++i)
        high[i] = xport_gte_read_data(25u + i) << 3;
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_data(9u + i, values[i] & 0x7FFFu);
    xport_gte_execute(0x498012u);
    for (i = 0u; i < 3u; ++i)
        output[i] = (sint32)(high[i] + xport_gte_read_data(25u + i));
}

uint32 sub_8002EA94(uint32 object, uint32 clear)
{
    uint32 matrix, i, node, next, candidate, nearest = 0u, selected = 0u;
    uint32 minimum = 0xFFFFFFFFu, result, distance, weapon, callback;
    sint32 selected_depth = 0, selected_span = 0, transformed[3];
    FUNCTION_MARKER(0x8002EA94u, "SLUS_005.10");
    matrix = r_u32(0x80065314u) != 0u && r_s16(object + 6u) == -1
        ? 0x8006F6A0u : 0x8006F680u;
    for (i = 0u; i < 8u; ++i)
        xport_gte_write_control(i, r_u32(matrix + 4u * i));
    node = r_u32(0x80065A18u);
    next = r_u32(node);
    while (next != 0u) {
        sint32 span, horizontal, depth;
        candidate = r_u32(node + 8u);
        if (candidate != object && r_u8(candidate + 4u) != 3u &&
            (r_u32(candidate) & 0x4000u) != 0u &&
            (r_s16(candidate + 6u) > 0 || r_s8(0x80065319u) == 3)) {
            control_transform_position(candidate + 72u, transformed);
            span = transformed[1] >> 10;
            if (span < 0) span = (sint32)(0u - (uint32)span);
            horizontal = transformed[0] >> 10;
            if (horizontal < 0) horizontal = (sint32)(0u - (uint32)horizontal);
            if (span < horizontal) span = horizontal;
            depth = transformed[2] >> 10;
            if (span < depth && (selected == 0u ||
                control_product(selected_depth, span) < control_product(depth, selected_span))) {
                selected = candidate;
                selected_span = span;
                selected_depth = depth;
            } else if (selected == 0u) {
                distance = sub_80016AAC(object + 36u, candidate + 72u);
                if (distance < minimum) {
                    minimum = distance;
                    nearest = candidate;
                }
            }
        }
        node = next;
        next = r_u32(next);
    }
    if (selected == 0u) selected = nearest;
    result = r_u32(object + 228u);
    if (selected != result && (selected != 0u || clear != 0u)) {
        w_u32(object + 228u, selected);
        i = r_u8(object + 179u);
        w_u16(object + 188u, 0u);
        result = object + ((i + 9u) << 2);
        weapon = r_u32(result + 236u);
        if (weapon != 0u) {
            result = r_u32(weapon + 100u);
            callback = result;
            if (callback != 0u)
                result = v8_native_terrain_call3(callback, weapon, 10u, 0u);
        }
    }
    return result;
}

uint32 sub_800244C4(uint32 x, uint32 z)
{
    uint32 tree = r_u32(0x800659F0u), quadrant, entry;
    FUNCTION_MARKER(0x800244C4u, "SLUS_005.10");
    x <<= 5; z <<= 5;
    for (;;) {
        quadrant = (x >> 31) | ((sint32)z < 0 ? 2u : 0u);
        entry = r_u16(tree + 2u + 2u * quadrant);
        if (entry == 0u || (entry & 0x8000u) != 0u)
            return entry;
        tree += entry * 10u;
        x <<= 1; z <<= 1;
    }
}

uint32 sub_80024748(uint32 head, uint32 node)
{
    uint32 previous = 0u, current = head;
    sint32 cost = (sint32)r_u32(node + 20u);
    FUNCTION_MARKER(0x80024748u, "SLUS_005.10");
    while (current != 0u && (sint32)r_u32(current + 20u) < cost) {
        previous = current;
        current = r_u32(current);
    }
    w_u32(node, current);
    if (previous == 0u) return node;
    w_u32(previous, node);
    return head;
}

uint32 sub_80023394(uint32 list, uint32 mask, uint32 position)
{
    uint32 link = r_u32(list), next = r_u32(link), selected = 0u;
    uint32 minimum = 0xFFFFFFFFu, object, distance, flags;
    FUNCTION_MARKER(0x80023394u, "SLUS_005.10");
    while (next != 0u) {
        object = r_u32(link + 8u);
        link = next;
        if (r_s16(object + 6u) >= 32) {
            flags = r_u32(object);
            if ((flags & 0x4000u) != 0u && (flags & mask) != 0u) {
                distance = sub_80016AAC(position, object + 72u);
                if (distance < minimum) {
                    minimum = distance;
                    selected = object;
                }
            }
        }
        next = r_u32(next);
    }
    return selected;
}

static uint32 control_area_leaf(uint32 list, sint32 minimum, sint32 maximum, const sint32 *bounds)
{
    uint32 link = r_u32(list), next = r_u32(link), object;
    sint32 kind, x, z;
    FUNCTION_MARKER(0x80021978u, "SLUS_005.10");
    while (next != 0u) {
        object = r_u32(link + 8u);
        link = next;
        kind = r_s16(object + 6u);
        if (kind >= minimum && kind <= maximum) {
            x = (sint32)r_u32(object + 72u);
            if (bounds[0] < x && x < bounds[1]) {
                z = (sint32)r_u32(object + 80u);
                if (bounds[2] < z && z < bounds[3]) return object;
            }
        }
        next = r_u32(next);
    }
    return 0u;
}

static uint32 control_area_tree(uint32 tree, sint32 minimum, sint32 maximum, const sint32 *bounds)
{
    uint32 kind = r_u32(tree), result, axis;
    sint32 split;
    FUNCTION_MARKER(0x80021A30u, "SLUS_005.10");
    if (kind == 0u) return control_area_leaf(tree + 4u, minimum, maximum, bounds);
    if (kind != 1u && kind != 2u) return 2u;
    axis = kind == 1u ? 0u : 2u;
    split = (sint32)r_u32(tree + 4u);
    if (bounds[axis] < split) {
        result = control_area_tree(r_u32(tree + 8u), minimum, maximum, bounds);
        if (result != 0u) return result;
    }
    if (split < bounds[axis + 1u])
        return control_area_tree(r_u32(tree + 12u), minimum, maximum, bounds);
    return 0u;
}

uint32 sub_80022E90(uint32 object)
{
    uint32 weapon, candidate, original, callback, index, delta, result;
    sint32 bounds[4];
    FUNCTION_MARKER(0x80022E90u, "SLUS_005.10");
    if (r_u8(0x80065319u) != 0u || r_u8(object + 208u) < 6u) return 0u;
    weapon = r_u32(object + 272u + 4u * r_u8(object + 179u));
    if (weapon == 0u || (sint8)r_u8(weapon + 8u) != 4) return 0u;
    bounds[0] = (sint32)(r_u32(object + 36u) - 1024000u);
    bounds[1] = (sint32)(r_u32(object + 36u) + 1024000u);
    bounds[2] = (sint32)(r_u32(object + 44u) - 1024000u);
    bounds[3] = (sint32)(r_u32(object + 44u) + 1024000u);
    candidate = control_area_tree(r_u32(0x80065A00u), r_s16(0x800659F4u), r_s16(0x80065AE0u), bounds);
    if (candidate == 0u) return 0u;
    original = r_u32(object + 228u);
    for (index = 0u; index < 3u; ++index) {
        delta = r_u32(candidate + 36u + index * 4u) - r_u32(original + 36u + index * 4u);
        if ((sint32)delta < 0) delta = 0u - delta;
        if ((sint32)delta > 1023999) return 0u;
    }
    w_u32(object + 228u, candidate);
    callback = r_u32(weapon + 100u);
    result = callback != 0u ? v8_native_terrain_call3(callback, weapon, 11u, object) : 0u;
    delta = sub_80017160() << 7;
    delta *= 2u - (uint32)(sint32)(sint8)r_u8(0x8006531Au);
    w_u16(weapon + 6u, result + (uint32)((sint32)delta >> 15));
    w_u32(object + 228u, original);
    return 1u;
}

uint32 sub_8002CF90(uint32 object, uint32 direction)
{
    uint32 step = direction + 3u, attempts = 0u, slot;
    sint32 remainder;
    FUNCTION_MARKER(0x8002CF90u, "SLUS_005.10");
    remainder = (sint32)(r_u8(object + 179u) + step) % 3;
    w_u8(object + 179u, (uint32)remainder);
    slot = r_u8(object + 179u);
    if (r_u32(object + 4u * (slot + 9u) + 236u) == 0u) {
        attempts = 1u;
        while (attempts < 3u) {
            remainder = (sint32)(r_u8(object + 179u) + step) % 3;
            w_u8(object + 179u, (uint32)remainder);
            slot = r_u8(object + 179u);
            ++attempts;
            if (r_u32(object + 4u * (slot + 9u) + 236u) != 0u) {
                --attempts;
                break;
            }
        }
    }
    return attempts < 2u;
}

void sub_8002479C(uint32 head)
{
    FUNCTION_MARKER(0x8002479Cu, "SLUS_005.10");
    while (head != 0u) {
        uint32 cell = r_u32(head + 8u) + 2u * r_u8(head + 16u) + 2u;
        w_u16(cell, r_u16(cell) & 0x9FFFu);
        head = r_u32(head);
    }
}

uint32 sub_80024CC0(uint32 node, sint16 target_x, sint16 target_z)
{
    uint32 size = 1u << (r_u8(node + 17u) & 31u);
    sint32 half = (sint32)(size + (size >> 31)) >> 1;
    uint32 dx = r_u16(node + 12u) + (uint32)half - (uint32)(sint32)target_x;
    uint32 dz = r_u16(node + 14u) + (uint32)half - (uint32)(sint32)target_z;
    FUNCTION_MARKER(0x80024CC0u, "SLUS_005.10");
    return SquareRoot0((sint32)(dx * dx + dz * dz)) << 7;
}

uint32 sub_800247DC(uint32 x, uint32 z)
{
    uint32 node = r_u32(0x80065AF0u), tree, quadrant, entry, mask;
    uint32 bits_x = x << 21, bits_z = z << 21, depth = 11u;
    FUNCTION_MARKER(0x800247DCu, "SLUS_005.10");
    if (node == 0u) return 0u;
    w_u32(0x80065AF0u, r_u32(node));
    tree = r_u32(0x800659F0u);
    for (;;) {
        --depth;
        quadrant = (bits_x >> 31) | ((sint32)bits_z < 0 ? 2u : 0u);
        entry = r_u16(tree + 2u + quadrant * 2u);
        if (entry == 0u) break;
        bits_x <<= 1;
        if ((entry & 0x8000u) != 0u) break;
        bits_z <<= 1;
        tree += entry * 10u;
    }
    mask = 0xFFFFFFFFu << (depth & 31u);
    w_u32(node + 8u, tree);
    w_u8(node + 16u, quadrant);
    w_u8(node + 17u, depth);
    w_u16(node + 12u, x & mask);
    w_u16(node + 14u, z & mask);
    return node;
}

uint32 sub_80024888(uint32 origin, uint32 x, uint32 z)
{
    uint32 node = r_u32(0x80065AF0u), tree, depth, bits_x, bits_z;
    uint32 quadrant, entry, mask;
    sint32 difference;
    FUNCTION_MARKER(0x80024888u, "SLUS_005.10");
    if (node == 0u) return 0u;
    w_u32(0x80065AF0u, r_u32(node));
    depth = r_u8(origin + 17u);
    tree = r_u32(origin + 8u);
    difference = (sint32)((r_u16(origin + 12u) ^ x) |
        (r_u16(origin + 14u) ^ z)) >> (depth & 31u);
    difference >>= 1;
    ++depth;
    while (difference != 0) {
        ++depth;
        entry = r_u16(tree);
        if (entry == 0u) return 0u;
        difference >>= 1;
        tree -= r_u16(tree) * 10u;
    }
    bits_x = x << ((32u - depth) & 31u);
    bits_z = z << ((32u - depth) & 31u);
    for (;;) {
        --depth;
        quadrant = (bits_x >> 31) | ((sint32)bits_z < 0 ? 2u : 0u);
        entry = r_u16(tree + 2u + quadrant * 2u);
        if (entry == 0u) break;
        bits_x <<= 1;
        if ((entry & 0x8000u) != 0u) break;
        bits_z <<= 1;
        tree += entry * 10u;
    }
    mask = 0xFFFFFFFFu << (depth & 31u);
    w_u32(node + 8u, tree);
    w_u8(node + 16u, quadrant);
    w_u8(node + 17u, depth);
    w_u16(node + 12u, x & mask);
    w_u16(node + 14u, z & mask);
    return node;
}

uint32 sub_80024998(uint32 origin)
{
    uint32 cell = r_u32(origin + 8u) + 2u * r_u8(origin + 16u) + 2u;
    uint32 flags = r_u16(cell), head = 0u, node, limit, next, offset;
    FUNCTION_MARKER(0x80024998u, "SLUS_005.10");
    if (flags == 0u) flags = 0xF00u;
    limit = r_u16(origin + 14u) + (1u << (r_u8(origin + 17u) & 31u));
    if ((flags & 0x100u) != 0u) {
        node = sub_80024888(origin, r_u16(origin + 12u) - 1u, r_u16(origin + 14u));
        while (node != 0u) {
            cell = r_u32(node + 8u) + 2u * r_u8(node + 16u) + 2u;
            if (r_u16(cell) != 0u) { w_u32(node, head); head = node; }
            next = r_u16(node + 14u) + (1u << (r_u8(node + 17u) & 31u));
            if ((sint32)next >= (sint32)limit) break;
            node = sub_80024888(node, r_u16(origin + 12u) - 1u, next);
        }
    }
    if ((flags & 0x200u) != 0u) {
        node = sub_80024888(origin, r_u16(origin + 12u) +
            (1u << (r_u8(origin + 17u) & 31u)), r_u16(origin + 14u));
        while (node != 0u) {
            cell = r_u32(node + 8u) + 2u * r_u8(node + 16u) + 2u;
            if (r_u16(cell) != 0u) { w_u32(node, head); head = node; }
            next = r_u16(node + 14u) + (1u << (r_u8(node + 17u) & 31u));
            if ((sint32)next >= (sint32)limit) break;
            node = sub_80024888(node, r_u16(node + 12u), next);
        }
    }
    limit = r_u16(origin + 12u) + (1u << (r_u8(origin + 17u) & 31u));
    if ((flags & 0x800u) != 0u) {
        node = sub_80024888(origin, r_u16(origin + 12u), r_u16(origin + 14u) - 1u);
        while (node != 0u) {
            cell = r_u32(node + 8u) + 2u * r_u8(node + 16u) + 2u;
            if (r_u16(cell) != 0u) { w_u32(node, head); head = node; }
            next = r_u16(node + 12u) + (1u << (r_u8(node + 17u) & 31u));
            if ((sint32)next >= (sint32)limit) break;
            node = sub_80024888(node, next, r_u16(origin + 14u) - 1u);
        }
    }
    if ((flags & 0x400u) != 0u) {
        node = sub_80024888(origin, r_u16(origin + 12u), r_u16(origin + 14u) +
            (1u << (r_u8(origin + 17u) & 31u)));
        while (node != 0u) {
            cell = r_u32(node + 8u) + 2u * r_u8(node + 16u) + 2u;
            if (r_u16(cell) != 0u) { w_u32(node, head); head = node; }
            next = r_u16(node + 12u) + (1u << (r_u8(node + 17u) & 31u));
            if ((sint32)next >= (sint32)limit) break;
            node = sub_80024888(node, next, r_u16(node + 14u));
        }
    }
    if ((flags & 0x1000u) != 0u) {
        offset = r_u32(origin + 8u) + 10u + 2u * r_u8(origin + 16u);
        node = sub_80024888(origin, r_u16(origin + 12u) + (uint32)(sint32)(sint8)r_u8(offset + 2u),
            r_u16(origin + 14u) + (uint32)(sint32)(sint8)r_u8(offset + 3u));
        cell = r_u32(node + 8u) + 2u * r_u8(node + 16u) + 2u;
        if (r_u16(cell) != 0u) { w_u32(node, head); head = node; }
    }
    return head;
}

uint32 sub_80015010(void)
{
    FUNCTION_MARKER(0x80015010u, "SLUS_005.10");
    return (uint32)GetRCnt(0xF2000002u) | ((uint32)r_u16(0x800102F2u) << 16);
}

static uint32 control_path_cell(uint32 node)
{
    return r_u32(node + 8u) + 2u * r_u8(node + 16u) + 2u;
}

uint32 sub_80024D54(uint32 source, uint32 target, uint32 range, uint32 flags)
{
    uint32 started, pool = 0x800738A0u, destination, open, closed = 0u;
    uint32 current, node, neighbors, cell, entry, previous, found, cost, improvement;
    uint32 count, path, cursor, parent, size, half, index;
    int expired;
    FUNCTION_MARKER(0x80024D54u, "SLUS_005.10");
    started = sub_80015010();
    w_u32(0x80065AF0u, pool);
    for (index = 0u; index < 1023u; ++index) {
        w_u32(pool, pool + 28u);
        pool += 28u;
    }
    w_u32(pool, 0u);
    destination = sub_800247DC((uint32)r_s16(target + 2u), (uint32)r_s16(target + 10u));
    if (r_u16(control_path_cell(destination)) == 0u) {
        node = sub_80024998(destination);
        if (node == 0u) return 0u;
        w_u32(destination, r_u32(0x80065AF0u));
        w_u32(0x80065AF0u, destination);
        destination = node;
    }
    open = sub_800247DC((uint32)r_s16(source + 2u), (uint32)r_s16(source + 10u));
    if (r_u16(control_path_cell(open)) == 0u) {
        node = sub_80024998(open);
        if (node == 0u) return 0u;
        w_u32(open, r_u32(0x80065AF0u));
        w_u32(0x80065AF0u, open);
        open = node;
    }
    w_u32(open + 24u, 0u);
    /* The original initial heuristic reads the final pool record */
    w_u32(open + 20u, sub_80024CC0(pool, r_s16(destination + 12u), r_s16(destination + 14u)));
    w_u32(open, 0u);
    w_u32(open + 4u, 0u);
    while (open != 0u) {
        expired = range < sub_80015010() - started;
        current = open;
        if (expired && flags != 0u) break;
        open = r_u32(open);
        if (expired || (r_u32(current + 8u) == r_u32(destination + 8u) &&
            r_u8(current + 16u) == r_u8(destination + 16u))) {
            cell = control_path_cell(current);
            w_u16(cell, r_u16(cell) & 0x9FFFu);
            count = 0u;
            for (parent = r_u32(current + 4u); parent != 0u; parent = r_u32(parent + 4u)) ++count;
            count -= count != 0u;
            path = sub_800116F4((count + 2u) * 4u);
            cursor = path + count * 4u;
            w_u16(cursor + 6u, 0u);
            w_u16(cursor + 4u, 0u);
            w_u16(cursor, r_u16(target + 2u));
            w_u16(cursor + 2u, r_u16(target + 10u));
            while (count != 0u) {
                --count;
                current = r_u32(current + 4u);
                cursor = path + count * 4u;
                size = 1u << (r_u8(current + 17u) & 31u);
                half = (uint32)((sint32)(size + (size >> 31)) >> 1);
                w_u16(cursor, r_u16(current + 12u) + half);
                size = 1u << (r_u8(current + 17u) & 31u);
                half = (uint32)((sint32)(size + (size >> 31)) >> 1);
                w_u16(cursor + 2u, r_u16(current + 14u) + half);
            }
            sub_8002479C(open);
            sub_8002479C(closed);
            return path;
        }
        neighbors = sub_80024998(current);
        while (neighbors != 0u) {
            node = neighbors;
            neighbors = r_u32(neighbors);
            cell = control_path_cell(node);
            cost = r_u32(current + 24u) + ((uint32)r_u8(cell) << (r_u8(node + 17u) & 31u));
            w_u32(node + 24u, cost);
            entry = r_u16(cell);
            previous = 0u;
            if ((entry & 0x4000u) != 0u) {
                found = (entry & 0x2000u) != 0u ? closed : open;
                while (r_u32(node + 8u) != r_u32(found + 8u) ||
                    r_u8(node + 16u) != r_u8(found + 16u)) {
                    previous = found;
                    found = r_u32(found);
                }
                w_u32(node, r_u32(0x80065AF0u));
                improvement = r_u32(found + 24u) - r_u32(node + 24u);
                w_u32(0x80065AF0u, node);
                if ((sint32)improvement <= 0) continue;
                if (previous != 0u) w_u32(previous, r_u32(found));
                else if ((entry & 0x2000u) != 0u) closed = r_u32(found);
                else open = r_u32(found);
                w_u16(control_path_cell(found), entry & 0xDFFFu);
                cost = r_u32(node + 24u);
                w_u32(found + 4u, current);
                w_u32(found + 24u, cost);
                w_u32(found + 20u, r_u32(found + 20u) - improvement);
            } else {
                w_u16(cell, entry | 0x4000u);
                cost = sub_80024CC0(node, r_s16(destination + 12u), r_s16(destination + 14u));
                found = node;
                w_u32(node + 4u, current);
                w_u32(node + 20u, r_u32(node + 24u) + cost);
            }
            open = sub_80024748(open, found);
        }
        w_u32(current, closed);
        closed = current;
        cell = control_path_cell(current);
        w_u16(cell, r_u16(cell) | 0x6000u);
    }
    sub_8002479C(open);
    sub_8002479C(closed);
    return 0u;
}

uint32 sub_80042E78(uint32 state, uint32 path)
{
    uint32 previous = r_u32(state + 4u);
    FUNCTION_MARKER(0x80042E78u, "SLUS_005.10");
    if (previous != 0u) sub_80045088(previous);
    w_u32(state + 4u, path);
    w_u16(state + 2u, 0u);
    w_u16(state, path != 0u);
    if (path != 0u) {
        w_u32(state + 8u, (uint32)r_s16(path) << 16);
        w_u32(state + 12u, (uint32)r_s16(path + 2u) << 16);
    }
    return (uint32)r_s16(state);
}

uint32 sub_80042EF0(uint32 state, uint32 source, uint32 target, uint32 range, uint32 flags)
{
    uint32 result;
    FUNCTION_MARKER(0x80042EF0u, "SLUS_005.10");
    result = sub_80042E78(state, sub_80024D54(source, target, range, flags));
    if (result == 0u) {
        result = r_u32(target);
        w_u32(state + 8u, result);
        result = r_u32(target + 8u);
        w_u32(state + 12u, result);
    }
    return result;
}

uint32 sub_80042F98(uint32 object, uint32 state, uint32 distance)
{
    uint32 delta, index, point;
    sint32 vector[3], angle;
    FUNCTION_MARKER(0x80042F98u, "SLUS_005.10");
    delta = r_u32(state + 8u) - r_u32(object + 36u);
    if ((sint32)delta < 0) delta = 0u - delta;
    if ((sint32)delta < (sint32)distance) {
        delta = r_u32(state + 12u) - r_u32(object + 44u);
        if ((sint32)delta < 0) delta = 0u - delta;
        if ((sint32)delta < (sint32)distance) {
            point = 0u;
            if (r_s16(state) > 0) {
                index = r_u16(state + 2u) + 1u;
                w_u16(state + 2u, index);
                index = (uint32)((sint32)(index << 16) >> 14);
                point = r_u32(r_u32(state + 4u) + index);
            }
            if (point != 0u) {
                w_u32(state + 8u, point << 16);
                w_u32(state + 12u, point & 0xFFFF0000u);
            } else {
                w_u16(state, 0xFFFFu);
            }
        }
    }
    vector[0] = (sint32)(r_u32(state + 8u) - r_u32(object + 36u));
    vector[1] = 0;
    vector[2] = (sint32)(r_u32(state + 12u) - r_u32(object + 44u));
    v8_native_4352C(object + 16u, vector, vector);
    angle = (sint32)((uint32)ratan2(vector[0], vector[2]) << 20) >> 20;
    return (uint32)angle;
}

uint32 sub_8002346C(uint32 object)
{
    uint32 selected, mask, random, count, weapon, primary, callback, firing, mode = 4u;
    uint32 delta, target, index;
    sint32 angle, steering, gain, speed, throttle, limit;
    FUNCTION_MARKER(0x8002346Cu, "SLUS_005.10");
    if (((r_u32(0x80065310u) - r_u8(object + 9u)) & 0x7Fu) == 0u &&
        (r_s16(object + 192u) <= 0 || (r_u32(object) & 0x200000u) != 0u)) {
        selected = 0u;
        if (r_u16(object + 232u) != 0u)
            selected = sub_8001FFD4(0x80065A18u, (uint32)r_s16(object + 232u));
        if (selected == 0u) {
            count = r_u16(r_u32(object + 236u) + 12u) +
                r_u16(r_u32(object + 240u) + 12u) + r_u16(r_u32(object + 244u) + 12u);
            if (count < r_u16(object + 12u)) {
                selected = sub_80023394(0x80065A18u, 0x100000u, object + 36u);
                mask = 0x400000u;
                if (selected == 0u) selected = sub_80023394(0x80065A18u, mask, object + 36u);
            } else if (r_u32(object + 276u) == 0u) {
                selected = sub_80023394(0x80065A18u, 0x7F000000u, object + 36u);
            }
            if (selected == 0u) selected = sub_80023394(0x80065A18u, 0x7F780000u, object + 36u);
            if (selected != 0u) {
                w_u16(object + 232u, r_u16(selected + 6u));
            } else {
                random = sub_80017160();
                count = sub_80020120(0x80065A50u, 0x7F780000u);
                selected = sub_80020190(0x80065A50u, 0x7F780000u,
                    (uint32)((sint32)(random * count) >> 15));
            }
            if (selected == 0u) (void)sub_80015368(0x800656B0u);
        }
        (void)sub_80042EF0(object + 192u, object + 36u, selected + 72u, 141120u, 0u);
    }
    w_u8(object + 178u, 1u);
    angle = (sint16)sub_80042F98(object, object + 192u, (r_u32(object + 140u) << 5) + 65536u);
    steering = angle > -682 ? angle : -682;
    if (steering >= 682) steering = 682;
    w_u16(object + 164u, (uint32)steering);
    gain = (sint32)((uint32)r_s16(object + 168u) +
        (uint32)(control_product((sint32)r_u32(object + 140u), r_s16(object + 170u)) / 4096));
    if (gain <= 0) gain = 0;
    w_u32(object + 148u, r_u32(object + 148u) + (uint32)(control_product(steering, gain) / 16));
    if (angle < 0) angle = -angle;
    speed = (sint32)r_u32(object + 140u);
    throttle = r_s16(object + 166u);
    limit = r_u16(object + 172u);
    if (angle >= 342 && speed >= 3052) {
        throttle = (throttle < 0 ? throttle : 0) - 1;
        if (throttle < -limit) throttle = -limit;
    } else if (speed >= 6867) {
        --throttle;
        if (throttle < -limit) throttle = -limit;
    } else {
        throttle = (throttle > 0 ? throttle : 0) + 1;
        if (throttle >= limit) throttle = limit;
    }
    w_u16(object + 166u, (uint32)throttle);
    weapon = r_u32(object + 272u + 4u * r_u8(object + 179u));
    primary = r_u32(object + 268u);
    if (weapon != 0u && r_u16(weapon + 6u) == 0u && sub_80022E90(object) == 0u) {
        target = r_u32(object + 228u);
        for (index = 0u; index < 3u; ++index) {
            delta = r_u32(object + 36u + index * 4u) - r_u32(target + 36u + index * 4u);
            if ((sint32)delta < 0) delta = 0u - delta;
            if ((sint32)delta > 1228799) break;
        }
        if (index == 3u) {
            callback = r_u32(weapon + 100u);
            firing = callback != 0u ? v8_native_terrain_call3(callback, weapon, 12u, object) : 0u;
            sub_8002CE68(object, firing);
            if (firing == 0u || (sub_80017160() & 7u) == 0u) (void)sub_8002CF90(object, 1u);
            if ((sint8)r_u8(primary + 8u) != 0) {
                mode = 11u;
            } else if (firing == 0u) {
                callback = r_u32(primary + 100u);
                if (callback != 0u && v8_native_terrain_call3(callback, primary, 12u, object) != 0u)
                    mode = 11u;
            }
        }
    }
    callback = r_u32(primary + 100u);
    return callback != 0u ? v8_native_terrain_call3(callback, primary, mode, object) : 0u;
}

uint32 sub_80022D54(uint32 object)
{
    uint32 weapon, callback, mode = 11u, result;
    FUNCTION_MARKER(0x80022D54u, "SLUS_005.10");
    if ((uint16)sub_800244C4(r_u32(object + 36u), r_u32(object + 44u)) != 0u) {
        (void)sub_80042EF0(object + 192u, object + 36u,
            r_u32(object + 228u) + 36u, 141120u, 0u);
        w_u8(object + 8u, 3u);
        w_u32(object, r_u32(object) & 0xFFFFFFDFu);
    }
    weapon = r_u32(object + 268u);
    w_u16(object + 164u, 0u);
    w_u16(object + 166u, 60u);
    if (r_s8(weapon + 8u) == 0) {
        callback = r_u32(weapon + 100u);
        result = callback != 0u ? v8_native_terrain_call3(callback, weapon, 12u, object) : 0u;
        if (result == 0u) mode = 4u;
    }
    callback = r_u32(weapon + 100u);
    return callback != 0u ? v8_native_terrain_call3(callback, weapon, mode, object) : 0u;
}

uint32 sub_8002305C(uint32 object)
{
    uint32 weapon, primary, callback, firing = 0u, mode = 4u, result;
    sint32 angle, steering, gain, throttle, limit, speed;
    int ready;
    FUNCTION_MARKER(0x8002305Cu, "SLUS_005.10");
    if (((r_u32(0x80065310u) - r_u8(object + 9u)) & 0x7Fu) == 0u &&
        (r_s16(object + 192u) <= 0 || (r_u32(object) & 0x200000u) != 0u)) {
        (void)sub_80042EF0(object + 192u, object + 36u,
            r_u32(object + 228u) + 36u, 141120u, 0u);
    }
    w_u8(object + 178u, 1u);
    angle = (sint16)sub_80042F98(object, object + 192u,
        (r_u32(object + 140u) << 5) + 65536u);
    steering = angle < -682 ? -682 : (angle > 682 ? 682 : angle);
    w_u16(object + 164u, (uint32)steering);
    gain = (sint32)((uint32)r_s16(object + 168u) +
        (uint32)(control_product((sint32)r_u32(object + 140u), r_s16(object + 170u)) / 4096));
    if (gain <= 0) gain = 0;
    w_u32(object + 148u, r_u32(object + 148u) + (uint32)(control_product(steering, gain) / 16));
    if (angle < 0) angle = -angle;
    speed = (sint32)r_u32(object + 140u);
    throttle = r_s16(object + 166u);
    limit = r_u16(object + 172u);
    if (angle >= 342 && speed >= 3052) {
        throttle = (throttle < 0 ? throttle : 0) - 1;
        if (throttle < -limit) throttle = -limit;
    } else if (speed >= 6867) {
        --throttle;
        if (throttle < -limit) throttle = -limit;
    } else {
        throttle = (throttle > 0 ? throttle : 0) + 1;
        if (throttle > limit) throttle = limit;
    }
    w_u16(object + 166u, (uint32)throttle);
    weapon = r_u32(object + 272u + 4u * r_u8(object + 179u));
    ready = weapon != 0u && r_u16(weapon + 6u) == 0u;
    if (ready && sub_80022E90(object) == 0u) {
        callback = r_u32(weapon + 100u);
        if (callback != 0u && v8_native_terrain_call3(callback, weapon, 12u, object) != 0u)
            firing = 1u;
    }
    sub_8002CE68(object, firing);
    primary = r_u32(object + 268u);
    if (r_s8(primary + 8u) != 0) {
        mode = 11u;
    } else if (firing == 0u) {
        callback = r_u32(primary + 100u);
        if (callback != 0u && v8_native_terrain_call3(callback, primary, 12u, object) != 0u)
            mode = 11u;
    }
    callback = r_u32(primary + 100u);
    result = callback != 0u ? v8_native_terrain_call3(callback, primary, mode, object) : 0u;
    if (ready) {
        if (firing == 0u) return sub_8002CF90(object, 1u);
        result = sub_80017160() & 7u;
        if (result == 0u) return sub_8002CF90(object, 1u);
    }
    return result;
}
uint32 sub_8002ED34(uint32 object, uint32 previous)
{
    uint32 node, next, candidate, distance, threshold;
    uint32 nearest = 0u, farther = 0u, nearest_distance = 0xFFFFFFFFu, farther_distance = 0xFFFFFFFFu;
    FUNCTION_MARKER(0x8002ED34u, "SLUS_005.10");
    threshold = previous != 0u ? sub_80016AAC(object + 36u, previous + 72u) : 0u;
    node = r_u32(0x80065A18u);
    next = r_u32(node);
    while (next != 0u) {
        candidate = r_u32(node + 8u);
        if (candidate != object && r_u8(candidate + 4u) != 3u && (r_u32(candidate) & 0x4000u) != 0u &&
            (r_s16(candidate + 6u) > 0 || r_s8(0x80065319u) == 3)) {
            distance = sub_80016AAC(object + 36u, candidate + 72u);
            if (threshold < distance && distance < farther_distance) {
                farther = candidate;
                farther_distance = distance;
            } else if (distance < nearest_distance) {
                nearest = candidate;
                nearest_distance = distance;
            }
        }
        node = next;
        next = r_u32(node);
    }
    return farther != 0u ? farther : nearest;
}
