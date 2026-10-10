#include "psx.h"
#include "psx_stream.h"
#include "psx_press.h"
#include "psx_spu.h"
#include "xport_trace.h"
#include <stdio.h>
#include <stdlib.h>

uint32 v8_native_find_file(const char *path);
uint32 sub_800116F4(uint32 bytes);
uint32 sub_8001178C(uint32 count, uint32 size);
void sub_80045088(uint32 allocation);
uint32 sub_80017D5C(void);
uint32 sub_800120D4(void);

static uint32 video_callback_module;

static uint32 video_state(uint32 base) { return base + 0x133C0u; }
static uint32 *video_words(uint32 address) { return (uint32 *)psx_addr(address, 4u); }

static void video_output_callback(void)
{
    uint32 state = video_state(video_callback_module);
    uint32 slot, destination, mode, next, display, address;
    sint32 x, width, height, words;
    PSX_RECT rectangle;
    if (r_u32(state + 76u) != 0u && StCdIntrFlag != 0)
    {
        StCdInterrupt();
        StCdIntrFlag = 0;
    }
    slot = r_u32(state + 36u);
    destination = r_u32(state + 28u + slot * 4u);
    rectangle.x = (sint16)r_u16(state + 60u);
    rectangle.y = (sint16)r_u16(state + 62u);
    rectangle.w = (sint16)r_u16(state + 64u);
    rectangle.h = (sint16)r_u16(state + 66u);
    (void)LoadImagePSX(&rectangle, video_words(destination));
    slot = r_u32(state + 36u);
    x = (sint16)(r_u16(state + 60u) + r_u16(state + 64u));
    width = (sint16)r_u16(state + 64u);
    display = r_u32(state + 56u);
    next = 1u - slot;
    w_u32(state + 36u, next);
    w_u16(state + 60u, (uint16)x);
    address = state + display * 8u;
    if (x < (sint32)(sint16)r_u16(address + 40u) + (sint32)(sint16)r_u16(address + 44u))
    {
        height = ((sint32)(sint16)r_u16(state + 66u) + 15) & ~15;
        words = (width * height) >> 1;
        mode = r_u32(state + 28u + next * 4u);
        DecDCTout(video_words(mode), words);
    }
    else
        w_u32(state + 68u, 1u);
}

static sint32 video_next_frame(uint32 base)
{
    uint32 state = video_state(base), count = 200000u;
    uint32 *data = NULL, *header = NULL;
    uint32 frame, width, slot;
    while (StGetNext(&data, &header) != 0u)
        if (--count == 0u)
            return -1;
    frame = xport_load_le32((uint8 *)header + 8u);
    if (frame < r_u32(state + 72u))
        return 0;
    width = xport_load_le16((uint8 *)header + 16u);
    if (r_u32(state + 76u) != 0u)
        width = (width * 3u) >> 1;
    w_u16(state + 52u, (uint16)width);
    w_u16(state + 44u, (uint16)width);
    width = xport_load_le16((uint8 *)header + 18u);
    w_u16(state + 66u, (uint16)width);
    w_u16(state + 54u, (uint16)width);
    w_u16(state + 46u, (uint16)width);
    slot = 1u - r_u32(state + 24u);
    w_u32(state + 24u, slot);
    w_u32(state + 72u, frame);
    (void)DecDCTvlc2(data, video_words(r_u32(state + 8u + slot * 4u)),
                   (uint16 *)psx_addr(r_u32(state), 69632u));
    (void)StFreeRing(data);
    return (sint32)r_u32(state + 72u);
}

static void video_start_read(const CdlLOC *location)
{
    uint8 mode = 0x80u;
    for (;;)
    {
        while (CdControl(2u, (uint8 *)location, NULL) == 0) {}
        while (CdControl(14u, &mode, NULL) == 0) {}
        (void)VSync(3);
        if (CdRead2(0x1E0) != 0)
            return;
    }
}

uint32 v8_native_shell_video_open(uint32 base, const char *path, uint32 mode,
                         uint32 x, uint32 y, uint32 second_x, uint32 second_y,
                         uint32 width, uint32 height)
{
    uint32 entry = v8_native_find_file(path);
    uint32 state = video_state(base), factor = mode != 0u ? 3u : 2u;
    uint32 frame_bytes = width * height, slice_bytes = height * (factor << 4);
    uint32 allocation;
    CdlLOC location;
    if (entry == 0u)
        return 0u;
    (void)CdIntToPos((sint32)r_u32(entry + 12u), &location);
    w_u32(state + 8u, sub_800116F4(frame_bytes));
    w_u32(state + 12u, sub_800116F4(frame_bytes));
    w_u32(state + 28u, sub_800116F4(slice_bytes));
    allocation = sub_800116F4(slice_bytes);
    w_u32(state + 68u, 0u);
    w_u32(state + 32u, allocation);
    w_u32(state + 36u, 0u);
    w_u16(state + 40u, (uint16)x);
    w_u16(state + 42u, (uint16)y);
    w_u16(state + 48u, (uint16)second_x);
    w_u32(state + 56u, 0u);
    w_u32(state + 76u, mode);
    w_u32(state + 72u, r_u32(state + 68u));
    w_u16(state + 50u, (uint16)second_y);
    w_u16(state + 64u, (uint16)(factor << 3));
    w_u32(state, sub_800116F4(0x11000u));
    w_u32(state + 4u, sub_800116F4(0x10000u));
    (void)ResetCallback();
    DecDCTReset(0);
    DecDCTvlcBuild((uint16 *)psx_addr(r_u32(state), 69632u));
    video_callback_module = base;
    (void)DecDCToutCallback(video_output_callback);
    StSetRing((uint32 *)psx_addr(r_u32(state + 4u), 65536u), 32u);
    StSetStream(mode, 1u, 0xFFFFFFFFu, NULL, NULL);
    video_start_read(&location);
    while (video_next_frame(base) < 0) {}
    return 1u;
}

sint32 v8_native_shell_video_advance(uint32 base)
{
    uint32 state = video_state(base), slot, address, count = 0x800000u;
    sint32 width, height, words, result;
    slot = 1u - r_u32(state + 56u);
    w_u32(state + 68u, 0u);
    w_u32(state + 56u, slot);
    address = state + (slot << 3);
    w_u16(state + 60u, r_u16(address + 40u));
    w_u16(state + 62u, r_u16(address + 42u));
    slot = r_u32(state + 24u);
    DecDCTin(video_words(r_u32(state + 8u + slot * 4u)), (sint32)r_u32(state + 76u));
    height = ((sint32)(sint16)r_u16(state + 66u) + 15) & ~15;
    width = (sint16)r_u16(state + 64u);
    words = (width * height) >> 1;
    slot = r_u32(state + 36u);
    DecDCTout(video_words(r_u32(state + 28u + slot * 4u)), words);
    result = video_next_frame(base);
    if (result <= 0)
        return -1;
    while (r_u32(state + 68u) == 0u && --count != 0u)
        (void)DecDCToutSync(0);
    return (sint32)r_u32(state + 56u);
}

uint32 v8_native_shell_video_close(uint32 base)
{
    uint32 state = video_state(base);
    (void)DecDCToutCallback(NULL);
    StUnSetRing();
    (void)CdControlB(9u, NULL, NULL);
    sub_80045088(r_u32(state + 4u));
    sub_80045088(r_u32(state));
    sub_80045088(r_u32(state + 8u));
    sub_80045088(r_u32(state + 12u));
    sub_80045088(r_u32(state + 28u));
    sub_80045088(r_u32(state + 32u));
    return 1u;
}

uint32 v8_native_shell_D354(uint32 base, const char *path, uint32 mode, uint32 mask)
{
    uint32 state = video_state(base), display;
    DISPENV environment;
    if (v8_native_shell_video_open(base, path, mode, 0u, 0u, 0u, 240u, 320u, 240u) == 0u)
        return 0u;
    (void)sub_80017D5C();
    for (;;)
    {
        if (mask != 0u)
        {
            (void)sub_800120D4();
            if (((r_u32(0x80065930u) | r_u32(0x80065934u)) & mask) != 0u)
                break;
        }
        (void)VSync(0);
        display = r_u32(state + 56u);
        (void)SetDefDispEnv(&environment, 0, (sint16)(display * 240u),
                           mode != 0u ? 480 : 320, 240);
        environment.isrgb24 = (uint8)mode;
        environment.disp.w = 320;
        environment.screen.x = (sint8)r_u8(0x8006531Cu);
        environment.screen.y = (sint8)r_u8(0x8006531Du);
        (void)PutDispEnv(&environment);
        (void)SetDispMask(1);
        if (v8_native_shell_video_advance(base) < 0)
            break;
    }
    (void)v8_native_shell_video_close(base);
    return 1u;
}


void v8_native_shell_bitmap_draw_rect(uint32 base, uint32 asset, const PSX_RECT *source_rect,
                                     const PSX_RECT *destination_rect, uint32 flags)
{
    uint32 workspace, rle, buffers[2], index = 0u;
    uint32 double_buffer = ((flags >> 2) ^ 1u) & 1u;
    uint32 rgb24 = flags & 1u, factor = rgb24 + 2u;
    uint32 bytes, skip_bytes, previous, destination, column, row, source;
    sint32 source_y, source_height, destination_y, destination_bottom;
    sint32 bottom, rounded_height, skip, x, width, right, words;
    PSX_RECT rectangle;
    destination_y = (sint16)xport_load_le16((const uint8 *)destination_rect + 2u);
    source_y = (sint16)xport_load_le16((const uint8 *)source_rect + 2u);
    source_height = (sint16)xport_load_le16((const uint8 *)source_rect + 6u);
    destination_bottom = destination_y + (sint16)xport_load_le16((const uint8 *)destination_rect + 6u);
    bottom = source_y + source_height;
    if (destination_bottom < bottom)
        bottom = destination_bottom;
    rounded_height = (source_height + 15) & ~15;
    workspace = sub_800116F4(0x11000u);
    rle = sub_8001178C((uint32)DecDCTBufSize(video_words(asset)) + 64u, 4u);
    destination_y = (sint16)xport_load_le16((const uint8 *)destination_rect + 2u);
    source_y = (sint16)xport_load_le16((const uint8 *)source_rect + 2u);
    skip = destination_y - source_y;
    if (skip <= 0)
        skip = 0;
    skip_bytes = (uint32)(skip * (sint32)(factor << 4));
    skip_bytes = (uint32)((sint32)skip_bytes / 4) << 2;
    (void)ResetCallback();
    DecDCTReset(0);
    bytes = (uint32)(rounded_height * (sint32)(factor << 4));
    DecDCTvlcBuild((uint16 *)psx_addr(workspace, 69632u));
    (void)DecDCTvlc2(video_words(asset), video_words(rle),
                   (uint16 *)psx_addr(workspace, 69632u));
    sub_80045088(workspace);
    DecDCTin(video_words(rle), (sint32)(flags & 3u));
    buffers[0] = sub_800116F4(bytes);
    buffers[1] = double_buffer != 0u ? sub_800116F4(bytes) : 0u;
    if (rgb24 != 0u)
        x = ((sint32)(sint16)xport_load_le16((const uint8 *)source_rect) / 2) * 3;
    else
        x = xport_load_le16((const uint8 *)source_rect);
    rectangle.x = (sint16)x;
    source_y = (sint16)xport_load_le16((const uint8 *)source_rect + 2u);
    destination_y = (sint16)xport_load_le16((const uint8 *)destination_rect + 2u);
    rectangle.y = (sint16)(source_y < destination_y ? destination_y : source_y);
    rectangle.w = (sint16)(factor << 3);
    rectangle.h = (sint16)(bottom - rectangle.y);
    if (rgb24 != 0u)
        width = ((sint32)(sint16)xport_load_le16((const uint8 *)source_rect + 4u) / 2) * 3;
    else
        width = (sint16)xport_load_le16((const uint8 *)source_rect + 4u);
    right = (sint32)rectangle.x + width;
    words = (rounded_height * (sint32)(factor << 3)) / 2;
    do
    {
        (void)DecDCToutSync(0);
        DecDCTout(video_words(buffers[index & 1u]), words);
        if (double_buffer != 0u)
        {
            ++index;
            if (index == 1u)
                continue;
        }
        else
            (void)DecDCToutSync(0);
        (void)DrawSync(0);
        (void)LoadImagePSX(&rectangle, video_words(buffers[index & 1u] + skip_bytes));
        rectangle.x = (sint16)((uint16)rectangle.x + (uint16)rectangle.w);
    } while ((sint32)rectangle.x < right - (sint32)rectangle.w);
    (void)DecDCToutSync(0);
    if (right - (sint32)rectangle.x == (sint32)rectangle.w)
    {
        previous = buffers[(~index) & double_buffer];
        (void)LoadImagePSX(&rectangle, video_words(previous + skip_bytes));
    }
    else
    {
        previous = buffers[(~index) & 1u] + skip_bytes;
        destination = buffers[index & 1u];
        rectangle.w = 1;
        column = previous;
        while ((sint32)rectangle.x < right)
        {
            source = column;
            column += 2u;
            for (row = 0u; (sint32)row < (sint32)rectangle.h; ++row)
            {
                w_u16(destination + row * 2u, r_u16(source));
                source += 32u;
            }
            (void)LoadImagePSX(&rectangle, video_words(destination));
            rectangle.x = (sint16)((uint16)rectangle.x + 1u);
        }
    }
    (void)DrawSync(0);
    sub_80045088(rle);
    sub_80045088(buffers[0]);
    sub_80045088(buffers[1]);
}

void v8_native_shell_bitmap_draw(uint32 base,uint32 asset,uint32 source_rect,uint32 destination_rect,uint32 flags)
{
    v8_native_shell_bitmap_draw_rect(base,asset,
        (const PSX_RECT *)psx_addr(source_rect,sizeof(PSX_RECT)),
        (const PSX_RECT *)psx_addr(destination_rect,sizeof(PSX_RECT)),flags);
}

void v8_native_shell_DC18(uint32 base,uint32 asset,uint32 x,uint32 y,uint32 flags)
{
    PSX_RECT rectangle;
    rectangle.x=(sint16)x;
    rectangle.y=(sint16)y;
    rectangle.w=(sint16)r_u16(asset);
    rectangle.h=(sint16)r_u16(asset+2u);
    v8_native_shell_bitmap_draw_rect(base,asset+4u,&rectangle,&rectangle,flags);
}
