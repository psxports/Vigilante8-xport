#include "psx.h"
#include "xport_trace.h"
#include <stdio.h>
#include <stdlib.h>

void sub_8001D994(uint32, uint32, uint32, uint32);
uint32 sub_80011F0C(void);
void sub_800126F0(void);
uint32 sub_80015FB4(void);
void sub_800165CC(uint32);
uint32 sub_80015F80(uint32);
uint32 sub_8001A8FC(uint32);
uint32 sub_80044360(uint32);
uint32 sub_8004445C(uint32, uint32, uint32);
uint32 sub_80016678(uint32);
uint32 sub_80011BE4(uint32);
uint32 sub_80011C58(uint32);
uint32 sub_80011834(void);
void sub_8001AA38(uint32);
void sub_80045088(uint32);
void sub_80044394(uint32);
void v8_native_44394(uint32 sound);

/* Each unrecorded dependency stops before its unresolved original body */
static uint32 v8_shell_untranslated(uint32 module_base, uint32 offset)
{
    fprintf(stderr, "Untranslated Shell dependency: base=%08X offset=%08X\n",
        module_base, offset);
    abort();
}

uint32 v8_native_shell_12F8(uint32 module_base);
static uint32 v8_shell_12F8(uint32 module_base)
{ return v8_native_shell_12F8(module_base); }
void v8_native_shell_238C(uint32 module_base);
static void v8_shell_238C(uint32 module_base)
{ v8_native_shell_238C(module_base); }
uint32 v8_native_shell_24BC(uint32 module_base);
static uint32 v8_shell_24BC(uint32 module_base)
{ return v8_native_shell_24BC(module_base); }
uint32 v8_native_shell_266C(uint32 module_base);
static uint32 v8_shell_266C(uint32 module_base)
{ return v8_native_shell_266C(module_base); }
static uint32 v8_shell_2BDC(uint32 module_base, uint32 selection)
{ (void)selection; return v8_shell_untranslated(module_base, 0x2BDCu); }
uint32 v8_shell_3544(uint32 module_base, uint32 character);
uint32 v8_shell_4D24(uint32 module_base, uint32 selection, uint32 mode);
static uint32 v8_shell_5660(uint32 module_base, uint32 selection)
{ (void)selection; return v8_shell_untranslated(module_base, 0x5660u); }
static uint32 v8_shell_63E4(uint32 module_base, uint32 selection)
{ (void)selection; return v8_shell_untranslated(module_base, 0x63E4u); }
void v8_native_shell_AD7C(uint32 module_base);
static void v8_shell_AD7C(uint32 module_base)
{ v8_native_shell_AD7C(module_base); }
static void v8_shell_C1C4(uint32 module_base)
{ (void)v8_shell_untranslated(module_base, 0xC1C4u); }
void v8_shell_C690(uint32 module_base);
uint32 v8_native_shell_D354(uint32 module_base, const char *text, uint32 mode, uint32 mask);
static void v8_shell_D354(uint32 module_base, const char *text, uint32 mode, uint32 mask)
{
    (void)v8_native_shell_D354(module_base, text, mode, mask);
}
static uint32 v8_shell_E134(uint32 module_base, uint32 flags)
{ (void)flags; return v8_shell_untranslated(module_base, 0xE134u); }
uint32 v8_native_shell_EE60(uint32 module_base, uint32 mode);
static void v8_shell_EE60(uint32 module_base, uint32 mode)
{ (void)v8_native_shell_EE60(module_base, mode); }

/* Host text preserves the addressable original format buffer */
static void v8_shell_video(uint32 module_base, uint32 offset, uint32 mask)
{
    const char *text = (const char *)psx_addr(module_base + offset, 1u);
    v8_shell_D354(module_base, text, 1u, mask);
}

uint32 v8_native_shell_entry(uint32 module_base)
{
    char video_name[64];
    uint32 first, second, asset, character, flags, previous_flags;
    uint32 selection, target, bit, stages, destination, result;
    sint32 index, state;

    w_u32(0x8006532Cu, 1u);
    sub_8001D994(320u, 240u, 160u, 120u);
    if ((sint8)r_u8(0x80065318u) == 0)
    {
        for (index = 11; index >= 0; --index)
            w_u8(0x80065950u + (uint32)index, 1u);
        v8_shell_EE60(module_base, 0u);
        (void)sub_80011F0C();
        v8_shell_AD7C(module_base);
        v8_shell_video(module_base, 0x1000u, 0x08400000u);
        first = r_u32(0x80065930u);
        second = r_u32(0x80065934u);
        if (((first | second) & 0x08000000u) != 0u)
            w_u8(0x80065318u, 3u);
        else
        {
            v8_shell_238C(module_base);
            index = 0;
            first = r_u32(0x80065930u);
            second = r_u32(0x80065934u);
            if (((first | second) & 0x08400000u) == 0u)
            {
                do
                {
                    ++index;
                    sub_800126F0();
                    (void)VSync(0);
                    if (index >= 120)
                        break;
                    first = r_u32(0x80065930u);
                    second = r_u32(0x80065934u);
                } while (((first | second) & 0x08400000u) == 0u);
            }
            (void)sub_80015FB4();
            first = r_u32(0x80065930u);
            second = r_u32(0x80065934u);
            if (((first | second) & 0x08000000u) != 0u)
                w_u8(0x80065318u, 3u);
        }
    }
    state = (sint8)r_u8(0x80065318u);
    if (state < 2)
    {
        sub_800165CC(0u);
        v8_shell_video(module_base, 0x1014u, 0x08400000u);
    }
    else if (state == 2)
    {
        sub_800165CC(0u);
        v8_shell_video(module_base, 0x1014u, 0xFFFFFFFFu);
        first = r_u32(0x80065930u);
        if (first != 0u || r_u32(0x80065934u) != 0u)
            w_u8(0x80065318u, 4u);
    }

    state = (sint8)r_u8(0x80065318u);
    asset = sub_80015F80(module_base + 0x1024u);
    w_u32(module_base + 0x13388u, asset);
    asset = sub_80015F80(module_base + 0x1038u);
    asset = sub_8001A8FC(asset);
    w_u32(module_base + 0x13390u, asset);
    asset = sub_80044360(module_base + 0x104Cu);
    w_u32(module_base + 0x1338Cu, asset);
    if (state < 4)
    {
        sub_800165CC(0u);
        index = 0;
        while (v8_shell_24BC(module_base) == 0u)
        {
            sprintf(video_name, (const char *)psx_addr(module_base + 0x1060u, 1u), index + 0x31);
            v8_shell_D354(module_base, video_name, 1u, 0xFFFFFFFFu);
            index = (index + 1) % 5;
        }
        asset = r_u32(module_base + 0x1338Cu);
        (void)sub_8004445C(1u, asset, 8u);
        (void)sub_80015FB4();
    }

    if ((sint8)r_u8(0x80065318u) == 4 && (sint8)r_u8(0x80065319u) == 0)
    {
        if (r_u32(0x80065328u) != 0u)
        {
            character = (uint32)(sint32)(sint8)r_u8(0x80065674u);
            previous_flags = r_u8(0x80065950u + character);
            state = (sint8)r_u8(0x80065904u);
            result = v8_shell_E134(module_base, previous_flags);
            if ((uint32)state == 31u - result)
            {
                character = (uint32)(sint32)(sint8)r_u8(0x80065674u);
                bit = (uint32)(sint32)(sint8)r_u8(0x80065904u) & 31u;
                flags = (previous_flags & ~(1u << bit)) | (2u << bit);
                w_u8(0x80065950u + character, (uint8)flags);
                character = (uint32)(sint32)(sint8)r_u8(0x80065674u);
                asset = r_u32(0x8006590Cu);
                stages = r_u32(asset + (character << 3) + 4u);
                flags = r_u8(0x80065950u + character);
                if ((sint32)flags >= (sint32)(1u << (stages & 31u)))
                {
                    sub_800165CC(0u);
                    character = (uint32)(sint32)(sint8)r_u8(0x80065674u);
                    asset = r_u32(module_base + 0x11C68u + character * 20u + 4u);
                    v8_shell_D354(module_base, (const char *)psx_addr(asset, 1u), 1u, 0x08400000u);
                }
            }
            if (r_u32(0x80065924u) != 0u)
            {
                character = (uint32)(sint32)(sint8)r_u8(0x80065674u);
                bit = (uint32)(sint32)(sint8)r_u8(0x80065904u) & 31u;
                destination = 0x80065950u + character;
                flags = r_u8(destination);
                w_u8(destination, (uint8)(flags | (1u << bit)));
            }
            character = (uint32)(sint32)(sint8)r_u8(0x80065674u);
            flags = r_u8(0x80065950u + character);
            if (flags != previous_flags)
            {
                asset = r_u32(0x8006590Cu);
                stages = r_u32(asset + (character << 3) + 4u);
                if (flags == (2u << (stages & 31u)) - 1u)
                    w_u8(0x80065319u, 0xFFu);
            }
        }
        if ((sint8)r_u8(0x80065319u) == 0)
        {
            character = (uint32)(sint32)(sint8)r_u8(0x80065674u);
            result = v8_shell_3544(module_base, character);
            w_u8(0x800658F8u, (uint8)result);
            (void)sub_80016678(1u);
            v8_shell_C690(module_base);
            if ((r_u32(0x80065930u) & 0x08400000u) != 0u)
                goto cleanup;
        }
    }

    result = v8_shell_12F8(module_base);
    w_u32(module_base + 0x133B4u, result);
    (void)sub_80011BE4(0x80065968u);
menu:
    (void)sub_80011C58(0x80065968u);
    selection = v8_shell_266C(module_base);
    (void)sub_80016678(1u);
    if (selection >= 5u)
        goto menu_finish;
    target = r_u32(module_base + 0x1078u + (selection << 2));
    if (target == module_base + 0xCD04u)
        goto character_menu;
    if (target == module_base + 0xCD7Cu)
        goto single_menu;
    if (target == module_base + 0xCDFCu)
        goto versus_menu;
    if (target == module_base + 0xCE80u)
        goto cooperative_menu;
    if (target == module_base + 0xCF04u)
        goto options_menu;
    fprintf(stderr, "Untranslated Shell table target: %08X\n", target);
    abort();

character_menu:
    asset = r_u32(module_base + 0x133B4u);
    w_u8(0x80065319u, 0u);
    result = v8_shell_4D24(module_base, asset | 0x1000u, 0u);
    w_u8(0x80065674u, (uint8)result);
    w_u8(0x80065675u, 0xFFu);
    (void)sub_80016678(1u);
    if ((r_u32(0x80065930u) & 0x00900000u) != 0u)
        goto menu_finish;
    character = (uint32)(sint32)(sint8)r_u8(0x80065674u);
    result = v8_shell_3544(module_base, character);
    w_u8(0x800658F8u, (uint8)result);
    (void)sub_80016678(1u);
    v8_shell_C690(module_base);
    if ((r_u32(0x80065930u) & 0x00100000u) != 0u)
        goto character_menu;
    goto menu_finish;

single_menu:
    asset = r_u32(module_base + 0x133B4u);
    w_u8(0x80065319u, 1u);
    result = v8_shell_2BDC(module_base, asset);
    w_u8(0x800658F8u, (uint8)result);
    (void)sub_80016678(1u);
    first = r_u32(0x80065930u);
    second = r_u32(0x80065934u);
    if (((first | second) & 0x00900000u) != 0u)
        goto menu_finish;
    asset = r_u32(module_base + 0x133B4u);
    result = v8_shell_4D24(module_base, asset, 1u);
    w_u8(0x80065674u, (uint8)result);
    w_u8(0x80065675u, 0xFFu);
    (void)sub_80016678(1u);
    if ((r_u32(0x80065930u) & 0x00100000u) != 0u)
        goto single_menu;
    goto menu_finish;

versus_menu:
    asset = r_u32(module_base + 0x133B4u);
    w_u8(0x80065319u, 3u);
    result = v8_shell_2BDC(module_base, asset);
    w_u8(0x800658F8u, (uint8)result);
    (void)sub_80016678(1u);
    first = r_u32(0x80065930u);
    second = r_u32(0x80065934u);
    if (((first | second) & 0x00900000u) != 0u)
        goto menu_finish;
    asset = r_u32(module_base + 0x133B4u);
    result = v8_shell_5660(module_base, asset);
    w_u16(0x80065674u, (uint16)result);
    (void)sub_80016678(1u);
    first = r_u32(0x80065930u);
    second = r_u32(0x80065934u);
    if (((first | second) & 0x00100000u) != 0u)
        goto versus_menu;
    goto menu_finish;

cooperative_menu:
    asset = r_u32(module_base + 0x133B4u);
    w_u8(0x80065319u, 4u);
    result = v8_shell_2BDC(module_base, asset);
    w_u8(0x800658F8u, (uint8)result);
    (void)sub_80016678(1u);
    first = r_u32(0x80065930u);
    second = r_u32(0x80065934u);
    if (((first | second) & 0x00900000u) != 0u)
        goto menu_finish;
    asset = r_u32(module_base + 0x133B4u);
    result = v8_shell_63E4(module_base, asset);
    w_u16(0x80065674u, (uint16)result);
    (void)sub_80016678(1u);
    first = r_u32(0x80065930u);
    second = r_u32(0x80065934u);
    if (((first | second) & 0x00100000u) != 0u)
        goto cooperative_menu;
    goto menu_finish;

options_menu:
    v8_shell_C1C4(module_base);
    (void)sub_80016678(1u);
menu_finish:
    (void)sub_80011834();
    first = r_u32(0x80065930u);
    second = r_u32(0x80065934u);
    if (((first | second) & 0x00900000u) != 0u)
        goto menu;
    if ((sint32)selection >= 0)
    {
        w_u32(0x8006597Cu, 0u);
        w_u32(0x80065978u, 0u);
    }
cleanup:
    sub_8001AA38(r_u32(module_base + 0x13390u));
    sub_80045088(r_u32(module_base + 0x13388u));
    v8_native_44394(r_u32(module_base + 0x1338Cu));
    character = (uint32)(sint32)(sint8)r_u8(0x800658F8u);
    w_u32(0x8006532Cu, 0u);
    w_u8(0x80065318u, 4u);
    return r_u32(module_base + 0x11BA0u + character * 20u + 16u);
}
