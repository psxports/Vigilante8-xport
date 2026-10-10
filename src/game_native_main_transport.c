#include "psx.h"
#include "xport.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32 sub_80011ADC(uint32 path);
void sub_80045088(uint32 address);
uint32 sub_8001FE50(uint32 list, uint32 object);
void v8_native_module_entry3(uint32 module, const char *filename, uint32 text, uint32 flags);
void v8_native_level_callback3(uint32 callback, uint32 object, uint32 mode, uint32 value);

uint32 sub_80022C54(uint32 object)
{
    uint32 node = r_u32(0x80065A70u);
    uint32 next = r_u32(node);
    w_u32(next + 4u, 0x80065A70u);
    w_u32(0x80065A70u, next);
    w_u32(node + 8u, object);
    return node;
}

uint32 sub_8003FC94(uint32 object)
{
    uint32 table = r_u32(r_u32(object + 88u));
    uint32 index = r_u16(object + 10u), entry, kind, count = 0u;
    index = r_u16(table + index * 28u + 54u);
    while (index != 0xFFFFu) {
        entry = table + index * 28u;
        kind = r_u16(entry + 28u);
        if ((kind >> 8u) == 255u && kind != 0xFFFFu) {
            index = r_u16(entry + 54u);
            ++count;
        } else
            index = r_u16(entry + 52u);
    }
    return count;
}

uint32 sub_8001EC48(uint32 object)
{
    uint32 child = r_u32(object + 56u), result = 0u;
    while (child != 0u) {
        uint32 child_result = sub_8001EC48(child);
        child = r_u32(child + 52u);
        result |= child_result;
    }
    if (result != 0u)
        w_u32(object, r_u32(object) | 0x800u);
    return result | (r_u32(object + 92u) != 0u);
}

uint32 sub_8001FE50(uint32 list, uint32 object)
{
    uint32 node = r_u32(0x80065A70u), previous, tail;
    previous = r_u32(node);
    w_u32(previous + 4u, 0x80065A70u);
    w_u32(0x80065A70u, previous);
    w_u32(node + 8u, object);
    tail = r_u32(list + 8u);
    w_u32(list + 8u, node);
    w_u32(tail, node);
    w_u32(node + 4u, tail);
    w_u32(node, list + 4u);
    return node;
}

static void v8_main_transport_pending(const char *name)
{
    fprintf(stderr, "V8: native main transport TODO %s\n", name);
    abort();
}

static void hud_text(uint32 font, const char *text, sint32 x, sint32 y, uint32 *ordering);
uint32 v8_native_19D10(uint32 message, uint32 font, uint32 *ordering, uint32 ticks)
{
    sint32 lifetime = (sint16)r_u16(message), remaining;
    uint32 position, first, second, intensity;
    if (lifetime == 0) return 0u;
    intensity = lifetime * 2 < 128 ? (uint32)(lifetime * 2) : 128u;
    position = message + (uint32)((sint16)r_u16(message + 2u) / 4) + 8u;
    first = r_u8(position); second = r_u8(position + 1u);
    w_u8(position, (r_u16(message + 2u) & 2u) != 0u ? 95u : 0u);
    w_u8(position + 1u, 0u);
    w_u8(font + 4u, intensity); w_u8(font + 5u, intensity); w_u8(font + 6u, intensity);
    hud_text(font, (const char *)psx_addr(message + 8u, 1u),
             (sint16)r_u16(message + 4u), (sint16)r_u16(message + 6u), ordering);
    w_u8(position, first); w_u8(position + 1u, second);
    remaining = (sint32)((uint32)(sint32)(sint16)r_u16(message) - ticks);
    w_u16(message + 2u, r_u16(message + 2u) + ticks);
    w_u16(message, remaining > 0 ? remaining : 0);
    return 1u;
}

void v8_native_18F7C(uint32 overlay, uint32 *ordering)
{
    v8_main_transport_pending("v8_native_18F7C");
}

static sint32 hud_divide(sint32 value, sint32 denominator)
{
    if (denominator == 0) return value < 0 ? 1 : -1;
    if (value == (-2147483647 - 1) && denominator == -1) return value;
    return value / denominator;
}

static void hud_add_packet(uint32 *ordering, uint32 packet)
{
    uint32 tag = r_u32(packet);
    w_u32(packet, (tag & 0xFF000000u) | (*ordering & 0xFFFFFFu));
    *ordering = (*ordering & 0xFF000000u) | (packet & 0xFFFFFFu);
}

void v8_native_2AD30(uint32 player, uint32 *ordering, sint32 x, sint32 y)
{
    uint32 node = r_u32(0x80065A18u), next = r_u32(node);
    while (next != 0u) {
        uint32 object = r_u32(node + 8u);
        if (object != player && r_u8(object + 4u) != 3u && (r_u32(object) & 0x4000u) != 0u) {
            sint32 dx = (sint32)(r_u32(object + 72u) - r_u32(player + 36u));
            sint32 dz = (sint32)(r_u32(object + 80u) - r_u32(player + 44u));
            sint32 distance, tx, ty;
            uint32 cursor = (r_u32(0x800656C0u) + 1u) & 63u;
            uint32 packet = 0x800A2BB8u + cursor * 16u, color;
            w_u32(0x800656C0u, cursor);
            dx /= 131072;
            dz /= 131072;
            distance = (sint32)((uint32)dx * (uint32)dx + (uint32)dz * (uint32)dz);
            if (distance >= 730) {
                sint32 scale = hud_divide(110592, SquareRoot0(distance));
                dx = (sint32)((uint32)dx * (uint32)scale) / 4096;
                dz = (sint32)((uint32)dz * (uint32)scale) / 4096;
            }
            color = r_u32(player + 228u) == object ? 0x6000FF00u : 0x600000FFu;
            if (r_u32(player + 228u) != object && (sint16)r_u16(object + 6u) < 0 &&
                (sint8)r_u8(0x80065319u) == 4)
                color = 0x60808080u;
            w_u32(packet + 4u, color);
            tx = (sint32)((uint32)(sint32)(sint16)r_u16(player + 16u) * (uint32)dx +
                         (uint32)(sint32)(sint16)r_u16(player + 28u) * (uint32)dz);
            ty = (sint32)((uint32)(sint32)(sint16)r_u16(player + 20u) * (uint32)dx +
                         (uint32)(sint32)(sint16)r_u16(player + 32u) * (uint32)dz);
            w_u16(packet + 8u, (uint32)x + (uint32)(tx / 4096));
            w_u16(packet + 10u, (uint32)y - (uint32)(ty / 4096));
            hud_add_packet(ordering, packet);
        }
        node = next;
        next = r_u32(next);
    }
}

static uint32 hud_health(uint32 object, uint32 scale)
{
    uint32 health = r_u16(object + 12u), numerator, denominator;
    if (r_u8(object + 208u) == 12u) {
        numerator = scale * health;
        denominator = r_u16(object + 14u);
    } else {
        numerator = scale * (r_u16(r_u32(object + 236u) + 12u) +
            r_u16(r_u32(object + 240u) + 12u) + r_u16(r_u32(object + 244u) + 12u));
        denominator = 3u * health;
    }
    return (uint32)hud_divide((sint32)numerator, (sint32)denominator);
}

static void hud_sprite(uint32 packet, uint32 sprite)
{
    w_u32(packet + 4u, (r_u16(sprite + 8u) & 0x9FFu) | 0xE1000400u);
    w_u16(packet + 22u, r_u16(sprite + 10u));
    w_u16(packet + 24u, r_u16(sprite + 2u));
    w_u16(packet + 26u, r_u16(sprite + 4u));
    w_u16(packet + 20u, r_u16(sprite + 6u));
}

uint32 sub_800116F4(uint32 bytes);
uint32 sub_800118B4(uint32 allocation);

static uint32 hud_text_width(uint32 font, const uint8 *text)
{
    uint32 table = r_u32(font), width = 0u;
    while (*text >= 32u) {
        uint32 index = (uint32)*text++ - r_u8(table + 5u);
        width += r_u8(table + index * 5u + 11u);
    }
    return width;
}

static void hud_text_append(uint32 *tail, uint32 packet)
{
    uint32 words = r_u8(*tail + 3u) + r_u8(packet + 3u) + 1u;
    if (words < 17u) {
        w_u8(*tail + 3u, words);
        w_u32(packet, 0u);
    } else {
        w_u32(*tail, (r_u32(*tail) & 0xFF000000u) | (packet & 0xFFFFFFu));
        *tail = packet;
    }
}

static uint32 hud_text_generate(uint32 font, const uint8 *text, uint32 x, uint32 y)
{
    uint32 table = r_u32(font), color = r_u32(font + 4u), length = (uint32)strlen((const char *)text);
    uint32 allocation = sub_800116F4(length * 20u + 12u), tail = allocation + 4u;
    uint32 packet = allocation + 12u, startx = x, starty = y, character;
    w_u8(allocation + 7u, 1u);
    w_u32(allocation + 8u, ((r_u16(font + 16u) | 32u) & 0x9FFu) | 0xE1000400u);
    while ((character = *text++) != 0u) {
        uint32 first = r_u8(table + 5u), code = character;
        if (character >= first) {
            code = (character - first) & 255u;
            if (code < r_u8(table + 4u)) {
                uint32 glyph = table + 8u + code * 5u;
                w_u32(packet, 0x04000000u);
                w_u32(packet + 4u, color);
                w_u16(packet + 8u, x + (sint8)r_u8(glyph + 4u));
                w_u16(packet + 10u, y);
                w_u16(packet + 12u, r_u16(font + 14u) + r_u16(glyph));
                w_u16(packet + 14u, r_u16(font + 18u));
                w_u16(packet + 16u, r_u8(glyph + 2u));
                w_u16(packet + 18u, r_u8(table + 6u));
                hud_text_append(&tail, packet);
                packet += 20u;
                x += r_u8(glyph + 3u);
                continue;
            }
        }
        switch (code) {
            case 1u:
                color = (color & 0xFF000000u) | text[0] | ((uint32)text[1] << 8u) | ((uint32)text[2] << 16u);
                text += 3u; break;
            case 2u: x += *text++; break;
            case 3u: y += *text++; break;
            case 4u:
                w_u32(packet, 0x03000000u);
                w_u32(packet + 4u, (color & 0x03FFFFFFu) | 0x40000000u);
                w_u16(packet + 8u, x); w_u16(packet + 10u, y);
                w_u16(packet + 12u, x + *text++); w_u16(packet + 14u, y);
                hud_text_append(&tail, packet); packet += 16u; break;
            case 5u: x -= hud_text_width(font, text) >> 1u; break;
            case 6u: x -= hud_text_width(font, text); break;
            case 7u: x = startx + *text++; break;
            case 8u: y = starty + *text++; break;
            case 9u: x = startx + ((x - startx + 64u) & 0xFFFFFFC0u); break;
            case 10u: x = startx; y += r_u8(table + 7u); break;
            default: break;
        }
    }
    w_u32(allocation, tail);
    return allocation;
}

static void hud_text(uint32 font, const char *text, sint32 x, sint32 y, uint32 *ordering)
{
    uint32 allocation = hud_text_generate(font, (const uint8 *)text, (uint32)x, (uint32)y);
    uint32 tail = r_u32(allocation), old = *ordering;
    *ordering = (allocation + 4u) & 0xFFFFFFu;
    w_u32(tail, ((uint32)r_u8(tail + 3u) << 24u) | old);
    (void)sub_800118B4(allocation);
}

uint32 v8_native_terrain_call3(uint32 callback, uint32 object, uint32 mode, uint32 value);
void v8_native_2AF98(uint32 player, uint32 view, uint32 *ordering)
{
    uint32 layout = 0x8005E9E4u + view * 20u;
    uint32 weapon = r_u32(player + 272u + r_u8(player + 179u) * 4u), i, packet;
    uint32 count = 0u, offset = 0u;
    sint32 bar;
    for (i = 0u; i < 4u; ++i) {
        packet = 0x800A28ACu + r_u32(0x80065308u) * 116u + i * 28u;
        w_u16(packet + 8u, r_u16(layout + i * 4u));
        w_u16(packet + 10u, r_u16(layout + i * 4u + 2u));
    }
    if (weapon != 0u) {
        char text[16];
        uint32 callback = r_u32(weapon + 100u), kind;
        snprintf(text, sizeof(text), "%02i", (int)r_u16(weapon + 12u));
        kind = callback != 0u ? v8_native_terrain_call3(callback, weapon, 13u, 0u) : 0u;
        packet = 0x800A2FB8u + r_u32(0x80065308u) * 28u;
        w_u8(packet + 21u, (r_u16(0x80065BAEu) >> 8u) + (kind << 4u));
        w_u16(packet + 16u, r_u16(layout + 8u) + 2u);
        w_u16(packet + 18u, r_u16(layout + 10u) + 12u);
        hud_add_packet(ordering, packet);
        hud_text(r_u32(0x80065B80u), text, (sint16)r_u16(layout + 8u) + 52,
                 (sint16)r_u16(layout + 10u) + 12, ordering);
    }
    for (i = 0u; i < 3u; ++i) {
        if (r_u32(player + 272u + i * 4u) != 0u) {
            packet = (i == r_u8(player + 179u) ? 0x800A2A30u : 0x800A2AD8u) + i * 56u;
            if (r_u32(0x80065308u) != 0u) packet += 28u;
            w_u16(packet + 16u, r_u16(layout + 8u) + 1u + i * 16u);
            w_u16(packet + 18u, r_u16(layout + 10u) - 2u);
            hud_add_packet(ordering, packet);
        }
    }
    for (i = 0u; i < 3u; ++i) {
        uint32 timer = r_u16(player + 284u + i * 2u);
        if (timer != 0u) {
            packet = 0x800A2990u + i * 56u + r_u32(0x80065308u) * 28u;
            offset += 24u;
            w_u16(packet + 8u, (sint32)view < 4 ? r_u16(layout) - offset : (view == 4u ? 8u : 128u));
            w_u16(packet + 10u, (sint32)view < 4 ? r_u16(layout + 2u) : 80u + count * 16u);
            ++count;
            if (timer >= 301u || (timer & 31u) >= 21u) hud_add_packet(ordering, packet - 8u);
        }
    }
    if (r_u16(player + 12u) != 0u) {
        bar = (sint32)(hud_health(player, 39u) + 3u);
        if (r_u8(player + 208u) != 12u && bar >= 42) bar = 42;
        if (bar >= 11 || (r_u32(0x80065310u) & 31u) < 20u) {
            packet = 0x800A2B80u + r_u32(0x80065308u) * 28u;
            w_u16(packet + 16u, r_u16(layout) + 4u);
            w_u16(packet + 18u, r_u16(layout + 2u) - (bar - 46));
            w_u8(packet + 21u, r_u8(0x80065B84u) - (bar - 42));
            w_u16(packet + 26u, bar);
            hud_add_packet(ordering, packet);
        }
    }
    v8_native_2AD30(player, ordering, (sint16)r_u16(layout + 4u) + 27, (sint16)r_u16(layout + 6u) + 27);
    weapon = r_u32(player + 228u);
    if (weapon != 0u && r_u32(weapon + 124u) != 0u) {
        uint32 damage = 0u;
        if (r_u8(weapon + 4u) == 2u)
            damage = r_u16(weapon + 12u) != 0u ? 32u - hud_health(weapon, 32u) : 32u;
        packet = 0x800A2828u + r_u32(0x80065308u) * 60u;
        hud_sprite(packet, r_u32(weapon + 124u));
        packet = 0x800A2828u + r_u32(0x80065308u) * 60u;
        w_u16(packet + 16u, r_u16(layout + 12u) + 3u);
        w_u16(packet + 18u, r_u16(layout + 14u) + 2u);
        w_u16(packet + 54u, r_u16(layout + 14u) + 18u);
        w_u16(packet + 38u, r_u16(layout + 14u) + 18u);
        w_u16(packet + 56u, 32u - damage);
        w_u16(packet + 40u, damage);
        w_u16(packet + 52u, r_u16(layout + 12u) + 7u);
        w_u16(packet + 36u, r_u16(layout + 12u) + 7u + 32u - damage);
        hud_add_packet(ordering, packet);
    }
    packet = 0x800A28A0u + r_u32(0x80065308u) * 116u;
    i = r_u32(packet);
    w_u32(i, ((uint32)r_u8(i + 3u) << 24u) | *ordering);
    *ordering = (packet + 4u) & 0xFFFFFFu;
}

void v8_native_43408(uint32 matrix, uint32 vector, uint32 *destination);
uint32 v8_native_1BE5C_host_ordering(uint32 model, const MATRIX *matrix, uint32 *ordering);
static void hud_target_marker(uint32 position, uint32 radius, uint32 model,
                              uint32 matrix, sint32 scale, uint32 *ordering)
{
    uint32 transformed[3], axis, trig;
    sint32 x, y, z, boundx, boundy, cosine, sine;
    MATRIX marker;
    v8_native_43408(matrix, position, transformed);
    for (axis = 0u; axis < 3u; ++axis)
        marker.t[axis] = (sint32)(transformed[axis] * (uint32)scale) >> 8;
    x = marker.t[0]; y = marker.t[1]; z = marker.t[2];
    boundx = (sint32)((uint32)z * 160u);
    boundy = (sint32)((uint32)z * 120u);
    if ((sint32)(((uint32)x - radius) << 8u) >= boundx ||
        (sint32)(0u - (uint32)boundx) >= (sint32)(((uint32)x + radius) << 8u) ||
        (sint32)(((uint32)y - radius) << 8u) >= boundy ||
        (sint32)(0u - (uint32)boundy) >= (sint32)(((uint32)y + radius) << 8u)) return;
    trig = 0x800607B4u + (((uint32)scale << 5u) & 0x3FE0u);
    cosine = (sint32)((uint32)(sint32)(sint16)r_u16(trig + 2u) * radius) / 1048576;
    sine = (sint32)((uint32)(sint32)(sint16)r_u16(trig) * radius) / 1048576;
    marker.m[0][0] = (sint16)cosine; marker.m[0][1] = (sint16)-sine; marker.m[0][2] = 0;
    marker.m[1][0] = (sint16)sine; marker.m[1][1] = (sint16)cosine; marker.m[1][2] = 0;
    marker.m[2][0] = 0; marker.m[2][1] = 0; marker.m[2][2] = 4096; 
    (void)v8_native_1BE5C_host_ordering(model, &marker, ordering);
}

void v8_native_2B7BC(uint32 player, uint32 matrix, uint32 *ordering)
{
    uint32 target = r_u32(player + 228u);
    if (target != 0u) {
        uint32 weapon = r_u32(player + 272u + r_u8(player + 179u) * 4u);
        uint32 model, position;
        if (r_u16(target + 288u) != 0u) {
            position = target + 72u;
            model = r_u32(0x80065B78u);
        } else {
            uint32 kind = weapon != 0u && (r_u32(weapon) & 0x4000u) != 0u;
            position = target + 36u;
            model = r_u32(0x80065B70u + kind * 4u);
        }
        hud_target_marker(position, r_u32(target + 84u), model, matrix,
                          (sint16)r_u16(player + 188u), ordering);
    }
    if (r_u16(player + 288u) != 0u)
        hud_target_marker(player + 72u, r_u32(player + 84u), r_u32(0x80065B7Cu),
                          matrix, 256, ordering);
    hud_add_packet(ordering, 0x80065B60u + r_u32(0x80065308u) * 8u);
}

static sint32 hud_product(sint32 a, sint32 b)
{
    return (sint32)((uint32)a * (uint32)b);
}

static void hud_flare(uint32 effect, uint32 *ordering)
{
    uint32 packet = r_u32(effect + 16u), descriptor = r_u32(effect + 12u), i;
    sint32 cx = (sint32)xport_gte_read_screen_offset(0u) >> 16;
    sint32 cy = (sint32)xport_gte_read_screen_offset(1u) >> 16;
    sint32 dx = (sint16)r_u16(effect + 8u) - cx, dy = (sint16)r_u16(effect + 10u) - cy;
    sint32 distance = SquareRoot0((sint32)((uint32)hud_product(dx, dx) + (uint32)hud_product(dy, dy)));
    sint32 nx = 4096, ny = 0;
    if (distance < 64 && (r_u32(descriptor) & 0xFFFFFFu) != 0u) {
        uint32 rgb = 0u;
        for (i = 0u; i < 3u; ++i) {
            uint32 component = r_u8(0x80065984u + i) + (((64u - distance) * r_u8(descriptor + i)) >> 6u);
            if (component > 255u) component = 255u;
            rgb |= component << (i * 8u);
        }
        w_u32(0x80065984u, rgb);
    }
    if (distance != 0) {
        nx = hud_divide((sint32)(((uint32)dx << 12u) + distance / 2), distance);
        ny = hud_divide((sint32)(((uint32)dy << 12u) + distance / 2), distance);
    }
    for (i = 0u; i < r_u16(r_u32(effect + 12u) + 10u); ++i) {
        sint32 factor = (sint16)r_u16(r_u32(effect + 12u) + 12u + i * 4u);
        sint32 x = cx + hud_product(dx, factor) / 4096, y = cy + hud_product(dy, factor) / 4096;
        sint32 w = ((sint32)r_u8(packet + 20u) - r_u8(packet + 12u)) / 2;
        sint32 h = ((sint32)r_u8(packet + 29u) - r_u8(packet + 13u)) / 2;
        sint32 ax = hud_product(nx, w), ay = hud_product(ny, w);
        sint32 bx = hud_product(ny, h), by = hud_product(nx, h);
        sint32 offsets[4][2] = {{-ax + bx, -ay - by}, {ax + bx, ay - by}, {-ax - bx, -ay + by}, {ax - bx, ay + by}};
        uint32 corner;
        w_u32(packet, ((packet + 40u) & 0xFFFFFFu) | 0x09000000u);
        for (corner = 0u; corner < 4u; ++corner) {
            w_u16(packet + 8u + corner * 8u, x + offsets[corner][0] / 4096);
            w_u16(packet + 10u + corner * 8u, y + offsets[corner][1] / 4096);
        }
        packet += 40u;
    }
    i = *ordering;
    *ordering = r_u32(effect + 16u) & 0xFFFFFFu;
    w_u32(packet - 40u, i | 0x09000000u);
}

void v8_native_2A25C(sint32 x, sint32 y, uint32 *ordering)
{
    uint32 queue = r_u32(0x80065308u) != 0u ? 0x800A1E20u : 0x800A2324u, i;
    PSX_RECT rectangle;
    uint32 pixels[2];
    rectangle.w = 1; rectangle.h = 1;
    for (i = 0u; (sint32)i < (sint32)r_u32(queue); ++i) {
        uint32 effect = queue + 4u + i * 20u;
        rectangle.x = (sint16)(r_u16(effect + 8u) + (uint32)x);
        rectangle.y = (sint16)(r_u16(effect + 10u) + (uint32)y);
        (void)StoreImage(&rectangle, pixels);
        if ((uint16)pixels[0] == 0x7FFFu) hud_flare(effect, ordering);
    }
    w_u32(queue, 0u);
}

sint32 v8_native_dispatch_bios_callback(uint32 address);
void v8_native_12710(void)
{
    uint32 previous;
    w_u32(0x8006546Cu, 1u);
    (void)PutDispEnv((DISPENV *)psx_addr(r_u32(0x800658DCu), sizeof(DISPENV)));
    DrawOTag((uint32 *)psx_addr(r_u32(0x800658E0u), 4u));
    previous = r_u32(0x800658E4u);
    (void)VSyncCallbackPSX(previous);
    previous = r_u32(0x800658E4u);
    if (previous != 0u && !v8_native_dispatch_bios_callback(previous)) {
        fprintf(stderr, "TODO frame previous VBlank callback %08X\n", previous);
        abort();
    }
}

static void frame_draw_complete(void)
{
    uint32 previous;
    w_u32(0x80065470u, 1u);
    (void)DrawSyncCallback(NULL);
    previous = VSyncCallbackPSX(0x80012710u);
    w_u32(0x800658E4u, previous);
}

void v8_native_12828(uint32 display, uint32 draw, uint32 *ordering, uint32 end)
{
    uint32 packet = draw + 28u, previous;
    w_u32(0x80065470u, 0u);
    w_u32(0x800658DCu, display);
    w_u32(0x800658E0u, end);
    w_u32(0x8006546Cu, r_u32(0x80065470u));
    SetDrawEnv(psx_addr(packet, 64u), (DRAWENV *)psx_addr(draw, sizeof(DRAWENV)));
    previous = r_u32(end);
    w_u32(end, packet & 0xFFFFFFu);
    w_u32(packet, ((uint32)r_u8(draw + 31u) << 24u) | previous);
    (void)DrawSyncCallback(frame_draw_complete);
    DrawOTag(ordering);
}

void v8_native_19C64(uint32 font, uint32 text, uint32 width, uint32 rows, uint32 *ordering)
{
    v8_main_transport_pending("v8_native_19C64");
}

void v8_native_22BA8(const char *message, uint32 text, uint32 flags)
{
    uint32 module, object, callback;
    module = sub_80011ADC(0x80065690u);
    v8_native_module_entry3(module, message, text, flags);
    sub_80045088(module);
    object = r_u32(0x800659FCu);
    callback = r_u32(0x80065A34u);
    v8_native_level_callback3(callback, object, 1u, 0u);
    object = r_u32(0x800659FCu);
    if ((r_u32(object) & 0x80u) != 0u)
        (void)sub_8001FE50(0x80065A60u, object);
}


uint32 xport_libsnd_sequence_call(uint32 target, uint32 argc, const uint32 *arguments)
{
    fprintf(stderr, "TODO SDK libsnd sequence callback %08X argc=%u\n", target, argc);
    abort();
}

uint32 sub_800128BC(void)
{
    uint32 ready;
    FUNCTION_MARKER(0x800128BCu, "SLUS_005.10");
    while ((ready = r_u32(0x8006546Cu)) == 0u) {
        (void)xport_poll();
        (void)VSync(-1);
    }
    return ready;
}
