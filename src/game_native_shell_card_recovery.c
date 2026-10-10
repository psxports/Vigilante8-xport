#include "psx.h"
#include "xport.h"
#include "xport_trace.h"
#include <stdio.h>
#include <stdlib.h>

sint32 xport_guest_call2(uint32 guest_target, uint32 argument0, uint32 argument1);
void v8_native_shell_11080(uint32 module_base);
uint32 v8_native_shell_11260(uint32 module_base);
uint32 v8_native_shell_10714(uint32 status);
uint32 v8_native_shell_F1E0(uint32 module_base, uint32 context);

static uint32 v8_shell_recovery_todo(uint32 module_base, uint32 offset)
{
    fprintf(stderr, "Untranslated Shell card recovery: base=%08X offset=%08X\n", module_base, offset);
    abort();
}

void v8_native_shell_10C00(uint32 module_base, uint32 function)
{
    uint32 count = r_u32(module_base + 0x13354u) + 1u;
    uint32 destination, index;
    if ((sint32)count >= 4)
    {
        printf("%s", (const char *)psx_addr(module_base + 0x1274u, 1u));
        return;
    }
    destination = module_base + 0x134ACu + (count << 4u);
    w_u32(module_base + 0x13354u, count);
    w_u32(module_base + 0x134E0u + (count << 2u), function);
    for (index = 0u; index < 4u; ++index)
    {
        w_u32(destination, 0u);
        destination -= 4u;
    }
}

static uint32 v8_shell_recovery_11338(uint32 module_base)
{
    uint32 second = r_u32(module_base + 0x13534u);
    uint32 first = r_u32(module_base + 0x13530u);
    uint32 third = r_u32(module_base + 0x13538u);
    uint32 fourth;
    first += second << 1u;
    fourth = r_u32(module_base + 0x1353Cu);
    first += third << 2u;
    return first + (fourth << 3u);
}

static uint32 v8_shell_recovery_11188(uint32 module_base)
{
    uint32 flags;
    do
    {
        flags = v8_shell_recovery_11338(module_base);
    } while (flags == 0u);
    (void)TestEvent(r_u32(module_base + 0x13520u));
    (void)TestEvent(r_u32(module_base + 0x13524u));
    (void)TestEvent(r_u32(module_base + 0x13528u));
    (void)TestEvent(r_u32(module_base + 0x1352Cu));
    w_u32(module_base + 0x1353Cu, 0u);
    w_u32(module_base + 0x13538u, r_u32(module_base + 0x1353Cu));
    w_u32(module_base + 0x13534u, r_u32(module_base + 0x13538u));
    w_u32(module_base + 0x13530u, r_u32(module_base + 0x13534u));
    return (uint32)((sint32)flags >> 1);
}

uint32 v8_native_shell_EFA4(uint32 module_base, uint32 context)
{
    uint32 state = r_u32(context);
    uint32 value, result, port, mask;
    if (state == 0u)
    {
        w_u32(module_base + 0x13424u, 0u);
        w_u32(module_base + 0x13420u, 0u);
        w_u32(context, 10u);
        state = 10u;
    }
    if (state == 10u)
    {
        v8_native_shell_11080(module_base);
        port = r_u32(module_base + 0x13444u);
        (void)_card_info((sint32)port);
        state = r_u32(context);
        w_u32(context, state + 1u);
        return 0u;
    }
    if (state != 11u)
        return 0u;
    if (v8_shell_recovery_11338(module_base) == 0u)
        return 0u;
    result = v8_shell_recovery_11188(module_base);
    w_u32(module_base + 0x13424u, result);
    if (result == 4u)
    {
        w_u32(module_base + 0x1343Cu, v8_native_shell_10714(4u));
        return 1u;
    }
    if (result == 0u)
    {
        port = r_u32(module_base + 0x13444u);
        mask = r_u32(module_base + 0x13434u);
        if ((mask & (1u << (port & 31u))) == 0u)
            w_u32(module_base + 0x13424u, 4u);
        result = r_u32(module_base + 0x13424u);
        w_u32(module_base + 0x1343Cu, v8_native_shell_10714(result));
        return 1u;
    }
    if (result == 1u || result == 2u)
    {
        value = r_u32(module_base + 0x13420u) + 1u;
        w_u32(module_base + 0x13420u, value);
        if ((sint32)value < 5)
        {
            w_u32(context, 10u);
            return 0u;
        }
    }
    port = r_u32(module_base + 0x13444u);
    result = r_u32(module_base + 0x13424u);
    mask = r_u32(module_base + 0x13434u);
    w_u32(module_base + 0x13434u, mask & ~(1u << (port & 31u)));
    w_u32(module_base + 0x1343Cu, v8_native_shell_10714(result));
    return 1u;
}

uint32 v8_native_shell_F1E0(uint32 module_base, uint32 context)
{
    uint32 state = r_u32(context);
    uint32 target, value, port, result;
    if (state >= 32u)
        return 0u;
    target = r_u32(module_base + 0x110Cu + (state << 2u));
    switch (target - module_base)
    {
    case 0xF220u:
        w_u32(module_base + 0x13430u, 0u);
        w_u32(module_base + 0x1342Cu, 0u);
        w_u32(module_base + 0x13428u, 0u);
        v8_native_shell_10C00(module_base, module_base + 0xEFA4u);
        w_u32(context, 10u);
        return 0u;
    case 0xF250u:
        value = r_u32(module_base + 0x1343Cu);
        if (value == 0u)
        {
            w_u32(context, 30u);
            return 0u;
        }
        if (value != 3u)
            return 1u;
        port = r_u32(module_base + 0x13444u);
        value = r_u32(module_base + 0x13434u);
        w_u32(module_base + 0x13430u, 1u);
        w_u32(module_base + 0x13434u, value | (1u << (port & 31u)));
        v8_native_shell_11080(module_base);
        port = r_u32(module_base + 0x13444u);
        (void)port;
        (void)v8_shell_recovery_todo(module_base, 0x10890u);
        w_u32(context, 21u);
        return 0u;
    case 0xF2B4u:
        if (v8_shell_recovery_todo(module_base, 0x11374u) == 0u)
            return 0u;
        (void)v8_native_shell_11260(module_base);
        w_u32(context, 30u);
        /* Original state21 falls through into the state30 body */
    case 0xF2D4u:
        v8_native_shell_11080(module_base);
        port = r_u32(module_base + 0x13444u);
        (void)port;
        (void)v8_shell_recovery_todo(module_base, 0x10860u);
        state = r_u32(context);
        w_u32(context, state + 1u);
        return 0u;
    case 0xF300u:
        if (v8_shell_recovery_11338(module_base) == 0u)
            return 0u;
        result = v8_shell_recovery_11188(module_base);
        w_u32(module_base + 0x1342Cu, result);
        if (result == 0u)
        {
            value = r_u32(module_base + 0x13430u);
            w_u32(module_base + 0x1343Cu, value != 0u ? 3u : 0u);
            return 1u;
        }
        if (result == 1u || result == 2u || result == 4u)
        {
            value = r_u32(module_base + 0x13428u) + 1u;
            w_u32(module_base + 0x13428u, value);
            if ((sint32)value < 5)
            {
                w_u32(context, 30u);
                return 0u;
            }
        }
        result = r_u32(module_base + 0x1342Cu);
        if (result == 4u)
            w_u32(module_base + 0x1343Cu, result);
        else
            w_u32(module_base + 0x1343Cu, v8_native_shell_10714(result));
        return 1u;
    case 0xF3FCu:
        return 0u;
    default:
        return v8_shell_recovery_todo(module_base, target - module_base);
    }
}

uint32 v8_native_shell_10CE8(uint32 module_base)
{
    return r_u32(module_base + 0x13354u) >> 31u;
}

void v8_native_shell_10C7C(uint32 module_base)
{
    uint32 index = r_u32(module_base + 0x13354u);
    uint32 target, context, result;
    if ((sint32)index < 0)
        return;
    target = r_u32(module_base + 0x134E0u + (index << 2u));
    context = module_base + 0x134A0u + (index << 4u);
    if (target == module_base + 0xF1E0u)
        result = v8_native_shell_F1E0(module_base, context);
    else if (target == module_base + 0xEFA4u)
        result = v8_native_shell_EFA4(module_base, context);
    else
        result = v8_shell_recovery_todo(module_base, target - module_base);
    if (result != 0u)
    {
        index = r_u32(module_base + 0x13354u);
        w_u32(module_base + 0x13354u, index - 1u);
    }
}

void v8_native_shell_10768(uint32 module_base)
{
    uint32 command, result, callback;
    if (v8_native_shell_10CE8(module_base) != 0u)
        return;
    v8_native_shell_10C7C(module_base);
    if (v8_native_shell_10CE8(module_base) == 0u)
        return;
    w_u32(module_base + 0x13440u, 1u);
    command = r_u32(module_base + 0x13438u);
    w_u32(module_base + 0x13480u, command);
    result = r_u32(module_base + 0x1343Cu);
    callback = r_u32(module_base + 0x13478u);
    w_u32(module_base + 0x13484u, result);
    w_u32(module_base + 0x13438u, 0u);
    w_u32(module_base + 0x1343Cu, 0u);
    if (callback != 0u)
    {
        command = r_u32(module_base + 0x13480u);
        result = r_u32(module_base + 0x13484u);
        (void)xport_guest_call2(callback, command, result);
    }
}

void v8_native_shell_card_recovery_poll(uint32 module_base)
{
    /* Advance real device producers before one original queue consumer turn */
    psx_root_counter_poll();
    psx_bios_card_poll();
    v8_native_shell_10768(module_base);
}

sint32 v8_native_shell_100F4(uint32 module_base, uint32 mode, uint32 *command, uint32 *result)
{
    uint32 current_command, current_result;
    current_command = r_u32(module_base + 0x13438u);
    if (current_command == 0u && r_u32(module_base + 0x13440u) == 0u)
        return -1;
    current_command = r_u32(module_base + 0x13438u);
    current_result = r_u32(module_base + 0x1343Cu);
    if (mode == 0u)
    {
        while (r_u32(module_base + 0x13440u) == 0u)
            v8_native_shell_card_recovery_poll(module_base);
    }
    else if (r_u32(module_base + 0x13440u) == 0u)
    {
        if (result != NULL)
            *result = current_result;
        if (command != NULL)
            *command = current_command;
        return 0;
    }
    if (result != NULL)
        *result = r_u32(module_base + 0x13484u);
    if (command != NULL)
        *command = r_u32(module_base + 0x13480u);
    w_u32(module_base + 0x13440u, 0u);
    return 1;
}
