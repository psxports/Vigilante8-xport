#include "psx.h"
#include "xport_trace.h"
#include <stdio.h>
#include <stdlib.h>

void sub_80019E7C(uint32 flags);
uint32 sub_80015F80(uint32 path);
uint32 sub_80019034(uint32 asset, uint32 size);
void sub_8001A0AC(uint32 rectangle, uint32 color);
uint32 sub_80017160(void);
void sub_80019A58(uint32 object, uint32 text, uint32 rectangle, uint32 flags, uint32 incoming_s2, uint32 incoming_s3);
uint32 sub_800120D4(void);
uint32 sub_800190D8(uint32 object);
uint32 v8_native_shell_video_open(uint32 base, const char *path, uint32 mode, uint32 x, uint32 y, uint32 second_x, uint32 second_y, uint32 width, uint32 height);
sint32 v8_native_shell_video_advance(uint32 base);
uint32 v8_native_shell_video_close(uint32 base);

static void shell_intro_223C(uint32 base)
{
    sub_8001A0AC(base + 0x43Cu, 0u);
}

void v8_native_shell_238C(uint32 base)
{
    uint32 asset, object, random, index, text, first, second;
    SetDispMask(0);
    (void)sub_80019E7C(0u);
    asset = sub_80015F80(base + 0x588u);
    object = sub_80019034(asset, 0u);
    shell_intro_223C(base);
    random = sub_80017160();
    index = (random * 11u) >> 15u;
    text = r_u32(base + 0x11D6Cu + (index << 2u));
    /* Flags2 overwrite both coordinate carriers before their first use */
    sub_80019A58(object, text, base + 0x59Cu, 2u, object, 0u);
    if (v8_native_shell_video_open(base, (const char *)psx_addr(base + 0x5A4u, 1u),
        0u, 96u, 112u, 96u, 112u, 448u, 160u) != 0u)
    {
        SetDispMask(1);
        for (;;)
        {
            (void)sub_800120D4();
            first = r_u32(0x80065930u);
            second = r_u32(0x80065934u);
            if (((first | second) & 0x840u) != 0u)
                break;
            if (v8_native_shell_video_advance(base) < 0)
                break;
        }
        (void)v8_native_shell_video_close(base);
    }
    (void)sub_800190D8(object);
}

void sub_80045088(uint32 allocation);
uint32 sub_8001A24C(uint32 rectangle);
uint32 sub_8001A2AC(uint32 rectangle, uint32 x, uint32 y);
uint32 sub_800190A8(uint32 object);
void sub_800126F0(void);
void v8_native_shell_bitmap_draw(uint32 base, uint32 asset, uint32 source_rectangle, uint32 destination_rectangle, uint32 flags);

static void v8_prompt_input_trace(uint32 cycle, uint32 frame, uint32 first, uint32 second)
{
    static uint32 previous_first = 0xFFFFFFFFu, previous_second = 0xFFFFFFFFu, rows;
    const char *path = getenv("V8_PROMPT_INPUT_TRACE");
    FILE *file;
    if (!path || !path[0] || rows >= 128u || (first == previous_first && second == previous_second))
        return;
    previous_first = first;
    previous_second = second;
    ++rows;
    file = fopen(path, "a");
    if (!file)
        return;
    fprintf(file, "cycle=%u frame=%u first=%08X second=%08X host=%08X old=%08X producer=%u consumer=%u accept=%u\n",
        cycle, frame, first, second, xport_input_read(0), r_u32(0x800658D8u),
        r_u8(0x80065905u), r_u8(0x80065918u), ((first | second) & 0x08000000u) != 0u);
    fclose(file);
}

uint32 v8_native_shell_24BC(uint32 base)
{
    uint32 asset, saved_rectangle, cycle, object, font, first, second, frames;
    asset = sub_80015F80(base + 0x5B8u);
    SetDispMask(0);
    (void)sub_80019E7C(0u);
    v8_native_shell_bitmap_draw(base, asset, base + 0x108Cu, base + 0x108Cu, 0u);
    SetDispMask(1);
    sub_80045088(asset);
    saved_rectangle = sub_8001A24C(base + 0x11D98u);
    for (cycle = 0u; cycle < 30u; ++cycle)
    {
        font = r_u32(base + 0x13388u);
        asset = r_u32(font + 4u);
        object = sub_80019034(font + asset, 1u);
        w_u8(object + 4u, 0x7Cu);
        w_u8(object + 5u, 0x60u);
        w_u8(object + 6u, 0u);
        /* Flags4446 assign both coordinate carriers before use */
        sub_80019A58(object, base + 0x5C8u, base + 0x11D98u, 0x4446u, cycle, 0x80060000u);
        (void)sub_800190A8(object);
        for (frames = 0u; frames < 45u; ++frames)
        {
            (void)VSync(0);
            sub_800126F0();
            first = r_u32(0x80065930u);
            second = r_u32(0x80065934u);
            v8_prompt_input_trace(cycle, frames, first, second);
            if (((first | second) & 0x08000000u) != 0u)
                return 1u;
        }
        first = (uint32)(sint32)(sint16)r_u16(base + 0x11D98u);
        second = (uint32)(sint32)(sint16)r_u16(base + 0x11D9Au);
        (void)sub_8001A2AC(saved_rectangle, first, second);
        for (frames = 0u; frames < 15u; ++frames)
        {
            (void)VSync(0);
            sub_800126F0();
            first = r_u32(0x80065930u);
            second = r_u32(0x80065934u);
            v8_prompt_input_trace(cycle, frames, first, second);
            if (((first | second) & 0x08000000u) != 0u)
                return 1u;
        }
    }
    return 0u;
}
