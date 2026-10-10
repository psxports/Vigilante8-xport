#include "psx.h"
#include <stdio.h>
#include "psx_gpu.h"
#include <stdlib.h>
#include <string.h>
uint32 sub_8005570C(uint32 *registers);
uint32 sub_800557CC(uint32 *registers);
uint32 sub_80055858(uint32 *registers, uint32 incoming_s3);
uint32 sub_80054C48(uint32 *registers);
void sub_8004BA34(uint32 first, uint32 second, uint32 third);
sint32 sub_80054984(uint32 *registers);
sint32 sub_800547AC(uint32 *registers);
uint32 sub_80054BB8(uint32 *registers);
uint32 setRC2wait(uint32 wait);
uint32 xport_guest_call4_with_registers(uint32 target, uint32 *registers);
uint32 sub_800555F4(uint32 *registers);
uint32 sub_80055634(uint32 *registers);
uint32 chkRC2wait(uint32 *registers);
uint32 sub_80052544(uint32 address);
uint32 sub_800541D8(uint32 *registers);
uint32 sub_80054240(uint32 *registers);
uint32 sub_800544D0(uint32 *registers);
uint32 sub_800546E4(uint32 *registers);
uint32 sub_80011CCC(void);
uint32 PadGetStatePSX(uint32 port);
void PadSetActPSX(uint32 port, uint32 actuator, uint32 length);
uint32 PadSetActAlignPSX(uint32 port, uint32 alignment);

uint32 sub_80052544(uint32 address)
{
    uint32 count = 0u, value;
    FUNCTION_MARKER(0x80052544u, "SLUS_005.10");
    if (address == 0u)
        return 0u;
    do
    {
        value = r_u8(address);
        address += 1u;
        if (value != 0u)
            count += 1u;
    } while (value != 0u);
    return count;
}

uint32 sub_800541D8(uint32 *registers)
{
    uint32 base, target;
    FUNCTION_MARKER(0x800541D8u, "SLUS_005.10");
    base = r_u32(0x800652BCu);
    if ((r_u32(base + 4u) & 1u) == 0u)
        return 0u;
    if ((r_u32(base) & 1u) == 0u)
        return 0u;
    target = r_u32(0x80065284u);
    if (target != 0u)
        (void)xport_guest_call4_with_registers(target, registers);
    return 1u;
}

uint32 sub_80054240(uint32 *registers)
{
    uint32 mode, bound, value, base, cursor;
    FUNCTION_MARKER(0x80054240u, "SLUS_005.10");
    mode = r_u32(0x800652ACu);
    w_u32(0x800652C4u, 1u);
    if (mode != 0u)
    {
        registers[0] = 0x800A4C78u;
        value = r_u32(registers[0]);
        if ((sint32)value < 150)
            w_u32(registers[0], value + 1u);
    }
    bound = r_u32(0x800652B0u);
    if (bound == 0u)
    {
        registers[0] = 0x800A4C7Cu;
        value = r_u32(registers[0]);
        if ((sint32)value < 150)
            w_u32(registers[0], value + 1u);
    }
    value = r_u32(0x80065294u);
    if (value == 0u)
        return 0u;
    mode = r_u32(0x800652ACu);
    bound = r_u32(0x800652B0u);
    registers[0] = mode << 4u;
    if ((sint32)bound < (sint32)mode)
        return 0u;
    registers[0] -= mode;
    base = r_u32(0x80065290u);
    registers[0] <<= 4u;
    w_u32(0x800652A0u, 0u);
    w_u32(0x8006529Cu, mode);
    registers[0] = base + registers[0];
    value = sub_800544D0(registers);
    if (value == 0u)
    {
        value = r_u32(0x8006525Cu);
        registers[0] = 0xFFFFu;
        (void)xport_guest_call4_with_registers(value, registers);
    }
    cursor = r_u32(0x8006529Cu);
    bound = r_u32(0x800652B0u);
    w_u32(0x800652A4u, 0u);
    while ((sint32)bound >= (sint32)cursor)
    {
        registers[0] = (cursor << 4u) - cursor;
        base = r_u32(0x80065290u);
        registers[0] <<= 4u;
        registers[0] = base + registers[0];
        (void)sub_800546E4(registers);
        cursor = r_u32(0x8006529Cu);
        bound = r_u32(0x800652B0u);
    }
    base = r_u32(0x800652C0u);
    w_u16(base + 0xEu, 0x88u);
    return 0u;
}

uint32 sub_800544D0(uint32 *registers)
{
    uint32 record = registers[0], device, index, queue, count, target, value;
    FUNCTION_MARKER(0x800544D0u, "SLUS_005.10");
    device = r_u32(0x800652C0u);
    w_u16(device + 0xAu, 0x40u);
    w_u16(device + 0xAu, 0u);
    w_u16(device + 8u, 0xDu);
    w_u16(device + 0xEu, 0x88u);
    value = r_u8(record + 0xE8u);
    registers[0] = 0x91u;
    if (value == 8u)
        registers[0] = 0x50u;
    (void)setRC2wait(registers[0]);
    index = r_u32(0x8006529Cu);
    registers[0] = r_u32(0x800652C0u);
    value = 0x1003u;
    if (index != 0u)
        value = 0x3003u;
    w_u16(registers[0] + 0xAu, (uint16)value);
    count = r_u32(0x800652B4u + (index << 2u));
    if ((sint32)count >= 0)
    {
        if ((sint32)count > 0)
        {
            do
            {
                index = r_u32(0x8006529Cu);
                queue = 0x800652B4u + (index << 2u);
                count = r_u32(queue) - 1u;
                registers[0] = ((count << 4u) - count) << 4u;
                w_u32(queue, count);
                value = r_u32(record + 0xCu);
                target = r_u32(0x8006527Cu);
                registers[0] = value + registers[0];
                (void)xport_guest_call4_with_registers(target, registers);
                index = r_u32(0x8006529Cu);
                count = r_u32(0x800652B4u + (index << 2u));
            } while ((sint32)count > 0);
        }
        index = r_u32(0x8006529Cu);
        registers[1] = 0x800652B4u + (index << 2u);
        count = r_u32(registers[1]);
        if (count == 0u)
        {
            registers[0] = record;
            target = r_u32(0x8006527Cu);
            w_u32(registers[1], 0xFFFFFFFFu);
            (void)xport_guest_call4_with_registers(target, registers);
            target = r_u32(0x80065280u);
            registers[0] = record;
            (void)xport_guest_call4_with_registers(target, registers);
        }
    }
    device = r_u32(0x800652C0u);
    value = r_u16(device + 4u);
    if ((value & 0x200u) != 0u)
    {
        value = r_u16(device + 0xAu);
        w_u16(device + 0xAu, (uint16)(value | 0x10u));
        value = r_u16(device + 4u);
        if ((value & 0x200u) != 0u)
        {
            w_u8(device, 1u);
            (void)sub_80054C48(registers);
            device = r_u32(0x800652C0u);
            (void)r_u8(device);
            return 0u;
        }
        device = r_u32(0x800652BCu);
        w_u32(device, 0xFFFFFF7Fu);
    }
    value = r_u8(record + 0x50u);
    if (value != 0u)
    {
        value = r_u8(record + 0x36u);
        if (value != 0u)
            return 0u;
    }
    device = r_u32(record + 0x3Cu);
    w_u8(device, 0u);
    return 1u;
}

uint32 sub_800546E4(uint32 *registers)
{
    uint32 stage, target, value;
    FUNCTION_MARKER(0x800546E4u, "SLUS_005.10");
    registers[1] = 0x800652A0u;
    stage = r_u32(registers[1]);
    target = r_u32(0x800652E0u + (stage << 2u));
    w_u32(registers[1], stage + 1u);
    value = xport_guest_call4_with_registers(target, registers);
    registers[0] = value;
    if ((sint32)registers[0] < 0)
    {
        target = r_u32(0x8006525Cu);
        return xport_guest_call4_with_registers(target, registers);
    }
    stage = r_u32(0x800652A0u);
    if (stage != 0u)
    {
        registers[0] = 0x3Cu;
        (void)setRC2wait(registers[0]);
        value = sub_80054BB8(registers);
        if (value == 0u)
        {
            target = r_u32(0x8006525Cu);
            registers[0] = 0xFFFFFFFDu;
            (void)xport_guest_call4_with_registers(target, registers);
        }
    }
    stage = r_u32(0x800652A0u);
    value = stage - 1u;
    if ((sint32)stage >= 5)
        w_u32(0x800652A0u, value);
    return value;
}

uint32 sub_800555F4(uint32 *registers)
{
    uint32 result;
    uint32 state = registers[0];
    FUNCTION_MARKER(0x800555F4u, "SLUS_005.10");
    result = xport_guest_call4_with_registers(r_u32(0x80065274u), registers);
    w_u32(0x800652DCu, result);
    registers[0] = state;
    registers[1] = 0xFFFFFFFEu;
    return (uint32)sub_800547AC(registers);
}

sint32 sub_800547AC(uint32 *registers)
{
    uint32 state = registers[0];
    uint32 command = registers[1];
    uint32 control;
    uint32 status;
    uint32 destination;
    uint32 captured;
    uint32 mode = 0x88u;
    uint32 value;
    uint32 count;
    uint32 index;
    FUNCTION_MARKER(0x800547ACu, "SLUS_005.10");
    if ((sint32)command < 0)
    {
        control = r_u32(0x800652C0u);
        destination = r_u32(state + 0x40u);
        captured = r_u8(control);
        registers[0] = captured;
        w_u8(state + 0x44u, 0xFFu);
        w_u8(state + 0x45u, 1u);
        w_u8(destination, (uint8)~command);
        control = r_u32(0x800652C0u);
        while ((r_u16(control + 4u) & 1u) == 0u) {}
        while (chkRC2wait(registers) == 0u) {}
        control = r_u32(0x800652C0u);
        w_u8(control, (uint8)~command);
        return (sint32)captured;
    }
    value = r_u8(r_u32(state + 0x3Cu));
    if ((value >> 4) == 8u && r_u8(state + 0x44u) >= 9u)
        mode = 0x22u;
    registers[2] = mode;
    control = r_u32(0x800652C0u);
    registers[1] = control;
    value = r_u16(0x1F801120u);
    registers[0] = value;
    status = r_u16(control + 4u);
    w_u32(0x800A4F0Cu, 0x1AEu);
    w_u32(0x800A4F08u, value);
    if ((status & 2u) == 0u)
        while ((r_u16(control + 4u) & 2u) == 0u) {}
    control = r_u32(0x800652C0u);
    status = r_u32(0x800652BCu);
    captured = r_u8(control);
    registers[0] = captured;
    w_u16(control + 14u, (uint16)mode);
    value = r_u32(status);
    if ((value & 0x80u) == 0u)
    {
        for (;;)
        {
            if (chkRC2wait(registers) != 0u)
                return -20;
            status = r_u32(0x800652BCu);
            if ((r_u32(status) & 0x80u) != 0u)
                break;
        }
    }
    control = r_u32(0x800652C0u);
    w_u8(control, (uint8)command);
    count = r_u8(state + 0x45u);
    index = r_u8(state + 0x44u);
    registers[0] = index;
    destination = r_u32(state + 0x3Cu) + index;
    w_u8(state + 0x45u, (uint8)(count + 1u));
    w_u8(destination, (uint8)captured);
    index = r_u8(state + 0x44u);
    w_u8(state + 0x44u, (uint8)(index + 1u));
    return (sint32)captured;
}

uint32 sub_80054BB8(uint32 *registers)
{
    uint32 status;
    uint32 control;
    uint32 value;
    FUNCTION_MARKER(0x80054BB8u, "SLUS_005.10");
    status = r_u32(0x800652BCu);
    control = r_u32(0x800652C0u);
    registers[0] = control;
    w_u32(status, 0xFFFFFF7Fu);
    if ((r_u16(control + 4u) & 0x80u) != 0u)
    {
        for (;;)
        {
            if (chkRC2wait(registers) != 0u)
                return 0u;
            control = r_u32(0x800652C0u);
            if ((r_u16(control + 4u) & 0x80u) == 0u)
                break;
        }
    }
    control = r_u32(0x800652C0u);
    registers[0] = control;
    value = r_u16(control + 10u);
    w_u16(control + 10u, (uint16)(value | 0x10u));
    return 1u;
}

uint32 sub_80055634(uint32 *registers)
{
    uint32 first;
    uint32 second;
    uint32 value;
    uint32 argument;
    uint32 target;
    uint32 state = registers[0];
    FUNCTION_MARKER(0x80055634u, "SLUS_005.10");
    first = r_u32(0x8006529Cu);
    second = r_u32(0x800652ACu);
    if (first == second && r_u32(0x80065298u) != 0u)
    {
        target = r_u32(0x8006528Cu);
        xport_guest_call4_with_registers(target, registers);
        target = r_u32(0x80065288u);
        xport_guest_call4_with_registers(target, registers);
    }
    if (r_u32(0x800652DCu) != 0u)
    {
        argument = r_u32(state + 12u);
        target = r_u32(0x80065274u);
        registers[0] = argument;
        xport_guest_call4_with_registers(target, registers);
        argument = r_u32(state + 12u);
        target = r_u32(0x80065274u);
        registers[0] = argument + 0xF0u;
        xport_guest_call4_with_registers(target, registers);
    }
    value = r_u8(state + 0x36u);
    if (value == 0u)
        value = 0x42u;
    else
        value = r_u8(state + 0x36u);
    registers[0] = state;
    registers[1] = value;
    return (uint32)sub_80054984(registers);
}

sint32 sub_80054984(uint32 *registers)
{
    uint32 state = registers[0];
    uint32 command = registers[1];
    uint32 mode = 0x88u;
    uint32 control;
    uint32 status;
    uint32 captured;
    uint32 index;
    uint32 count;
    uint32 value;
    uint32 start;
    uint32 limit;
    uint32 current;
    uint32 elapsed;
    uint32 destination;
    FUNCTION_MARKER(0x80054984u, "SLUS_005.10");
    value = r_u8(r_u32(state + 0x3Cu));
    if ((value >> 4) == 8u && r_u8(state + 0x44u) >= 9u)
        mode = 0x22u;
    control = r_u32(0x800652C0u);
    while ((r_u16(control + 4u) & 2u) == 0u) {}
    registers[0] = 0x190u;
    setRC2wait(registers[0]);
    control = r_u32(0x800652C0u);
    registers[0] = control;
    captured = r_u8(control);
    index = r_u8(state + 0x44u);
    if (index == 0u && (captured >> 4) == 8u)
        w_u16(control + 14u, 0x22u);
    else
        w_u16(control + 14u, (uint16)mode);
    status = r_u32(0x800652BCu);
    if ((r_u32(status) & 0x80u) == 0u)
    {
        registers[2] = 0x1F801128u;
        registers[3] = status;
        start = r_u32(0x800A4F08u);
        limit = r_u32(0x800A4F0Cu);
        registers[0] = start;
        registers[1] = limit;
        for (;;)
        {
            current = r_u16(0x1F801120u);
            if (current < start)
            {
                value = r_u16(0x1F801128u);
                if (value != 0u)
                    current += r_u16(0x1F801128u);
                else
                    current += 0x10000u;
            }
            value = r_u16(0x1F801124u);
            elapsed = current - start;
            if ((value & 0x200u) != 0u && elapsed >= limit)
                return -2;
            if ((elapsed >> 3) >= limit)
                return -2;
            if ((r_u32(status) & 0x80u) != 0u)
                break;
        }
    }
    if (r_u8(state + 0xE8u) != 8u && r_u32(0x800652A0u) == 2u)
    {
        registers[0] = 0x3Cu;
        setRC2wait(registers[0]);
        while (chkRC2wait(registers) == 0u) {}
    }
    control = r_u32(0x800652C0u);
    w_u8(control, (uint8)command);
    count = r_u8(state + 0x45u);
    index = r_u8(state + 0x44u);
    w_u8(state + 0x45u, (uint8)(count + 1u));
    if (index != 0xFFu)
    {
        index = r_u8(state + 0x44u);
        destination = r_u32(state + 0x3Cu) + index;
        w_u8(destination, (uint8)captured);
    }
    index = r_u8(state + 0x44u);
    w_u8(state + 0x44u, (uint8)(index + 1u));
    return (sint32)captured;
}

uint32 sub_8005570C(uint32 *registers)
{
    uint32 state = registers[0];
    uint32 result;
    uint32 target;
    uint32 flag;
    FUNCTION_MARKER(0x8005570Cu, "SLUS_005.10");
    if (r_u32(0x800652DCu) != 0u)
    {
        registers[0] = r_u32(state + 0xCu);
        target = r_u32(0x80065274u);
        registers[0] += 0x1E0u;
        (void)xport_guest_call4_with_registers(target, registers);
        registers[0] = r_u32(state + 0xCu);
        target = r_u32(0x80065274u);
        registers[0] += 0x2D0u;
        (void)xport_guest_call4_with_registers(target, registers);
    }
    flag = r_u8(state + 0x36u);
    registers[1] = 0u;
    if (flag == 0u)
        registers[1] = r_u32(0x800652A8u);
    registers[0] = state;
    result = sub_80054984(registers);
    if ((sint32)result < 0)
        return result;
    if ((result & 0xF0u) == 0u)
        return 0xFFFFFFF7u;
    result = (result & 0xFu) << 1;
    w_u32(0x800652D4u, result);
    if (result == 0u)
        w_u32(0x800652D4u, 0x20u);
    return 0u;
}

uint32 sub_800557CC(uint32 *registers)
{
    uint32 state = registers[0];
    uint32 kind;
    uint32 target;
    uint32 result;
    FUNCTION_MARKER(0x800557CCu, "SLUS_005.10");
    kind = r_u8(r_u32(state + 0x3Cu)) >> 4;
    registers[1] = 0u;
    if (kind == 8u)
        registers[1] = (uint32)(r_u8(state + 0x36u) == 0u);
    target = r_u32(0x80065264u);
    registers[0] = state;
    result = xport_guest_call4_with_registers(target, registers);
    registers[0] = state;
    registers[1] = result & 0xFFu;
    result = sub_80054984(registers);
    if (result == 0x5Au || result == 0u)
        return result;
    if ((sint32)result < 0)
        return result;
    return 0xFFFFFFF7u;
}

uint32 sub_80055858(uint32 *registers, uint32 incoming_s3)
{
    uint32 state = registers[0];
    uint32 candidate = incoming_s3;
    uint32 selected;
    uint32 slot;
    uint32 offset;
    uint32 active = 0u;
    uint32 target;
    uint32 result;
    uint32 count;
    uint32 value;
    FUNCTION_MARKER(0x80055858u, "SLUS_005.10");
    target = r_u32(0x80065268u);
    (void)xport_guest_call4_with_registers(target, registers);
    if (r_u32(0x800652A8u) != 0u)
    {
        value = r_u8(r_u32(state + 0x3Cu));
        if ((value >> 4) == 8u)
            active = (uint32)(r_u8(state + 0x36u) == 0u);
    }
    if (active != 0u)
    {
        uint32 index = 0xFFFFFFFFu;
        offset = 0xFFFFFF10u;
        for (;;)
        {
            count = r_u32(0x800652D4u) - 1u;
            w_u32(0x800652D4u, count);
            if ((sint32)count <= 0)
                break;
            if ((sint32)index >= 0)
            {
                registers[0] = r_u32(state + 0xCu);
                target = r_u32(0x80065268u);
                registers[0] += offset;
                (void)xport_guest_call4_with_registers(target, registers);
            }
            registers[0] = state;
            target = r_u32(0x80065264u);
            registers[1] = 1u;
            result = xport_guest_call4_with_registers(target, registers);
            registers[0] = state;
            registers[1] = result & 0xFFu;
            result = sub_80054984(registers);
            if ((sint32)result < 0)
                return result;
            registers[0] = 60u;
            (void)setRC2wait(registers[0]);
            result = sub_80054BB8(registers);
            index += 1u;
            if (result == 0u)
                return 0xFFFFFFFDu;
            value = (uint32)((sint32)index < 4);
            offset += 0xF0u;
            if (value == 0u)
                break;
        }
    }
    value = r_u32(0x8006529Cu);
    count = r_u32(0x800652D4u);
    registers[0] = (uint32)(value == 0u);
    selected = registers[0];
    if ((sint32)count >= 2)
    {
        slot = 0x800652B4u + (selected << 2);
        offset = ((selected << 4) - selected) << 4;
        for (;;)
        {
            registers[0] = r_u32(slot);
            if ((sint32)registers[0] < 0)
                break;
            if ((sint32)registers[0] > 0)
            {
                value = (registers[0] << 4) - registers[0];
                target = offset + r_u32(0x80065290u);
                candidate = r_u32(target + 0xCu) + (value << 4) - 0xF0u;
                target = r_u32(0x8006527Cu);
                registers[0] = candidate;
                (void)xport_guest_call4_with_registers(target, registers);
            }
            value = r_u32(slot);
            if (value == 3u)
            {
                target = r_u32(0x8006527Cu);
                registers[0] = candidate - 0xF0u;
                (void)xport_guest_call4_with_registers(target, registers);
                w_u32(slot, 1u);
                registers[0] = state;
            }
            else if ((sint32)value < 4)
            {
                registers[0] = state;
                if ((sint32)value < 2 && (sint32)value >= 0)
                {
                    candidate = r_u32(0x80065290u) + offset;
                    target = r_u32(0x8006527Cu);
                    registers[0] = candidate;
                    (void)xport_guest_call4_with_registers(target, registers);
                    target = r_u32(0x80065280u);
                    registers[0] = candidate;
                    (void)xport_guest_call4_with_registers(target, registers);
                    w_u32(slot, 0xFFFFFFFFu);
                    registers[0] = state;
                }
            }
            else
            {
                registers[0] = state;
                if (value == 4u)
                    w_u32(slot, 3u);
            }
            target = r_u32(0x80065264u);
            registers[1] = active;
            result = xport_guest_call4_with_registers(target, registers);
            registers[0] = state;
            registers[1] = result & 0xFFu;
            result = sub_800547AC(registers);
            if ((sint32)result < 0)
                return result;
            registers[0] = 60u;
            (void)setRC2wait(registers[0]);
            result = sub_80054BB8(registers);
            if (result == 0u)
                return 0xFFFFFFFDu;
            count = r_u32(0x800652D4u) - 1u;
            w_u32(0x800652D4u, count);
            if ((sint32)count < 2)
                break;
        }
    }
    for (;;)
    {
        count = r_u32(0x800652D4u) - 1u;
        w_u32(0x800652D4u, count);
        if ((sint32)count <= 0)
            break;
        registers[0] = state;
        target = r_u32(0x80065264u);
        registers[1] = active;
        result = xport_guest_call4_with_registers(target, registers);
        registers[0] = state;
        registers[1] = result & 0xFFu;
        result = sub_800547AC(registers);
        if ((sint32)result < 0)
            return result;
        registers[0] = 60u;
        (void)setRC2wait(registers[0]);
        result = sub_80054BB8(registers);
        if (result == 0u)
            return 0xFFFFFFFDu;
    }
    (void)sub_80054C48(registers);
    value = r_u8(state + 0x44u);
    w_u8(state + 0x44u, value + 1u);
    target = r_u32(0x800652D8u);
    registers[0] = r_u32(state + 0x3Cu);
    result = r_u8(target);
    w_u8(registers[0] + value, result);
    target = r_u32(0x8006525Cu);
    registers[0] = 0u;
    (void)xport_guest_call4_with_registers(target, registers);
    return 0u;
}

uint32 sub_80054C48(uint32 *registers)
{
    uint32 base;
    uint32 result;
    FUNCTION_MARKER(0x80054C48u, "SLUS_005.10");
    base = r_u32(0x800652C0u);
    do
    {
        result = r_u16(base + 4u) & 2u;
    } while (result == 0u);
    return result;
}

uint32 sub_80011CCC(void)
{
    uint32 index, source, destination, end, a, b, c, d;
    uint32 actor, port, state, active, intensity, decay, delay;
    FUNCTION_MARKER(0x80011CCCu, "SLUS_005.10");
    index = (r_u8(0x80065905u) + 1u) & 7u;
    w_u8(0x80065905u, (uint8)index);
    source = 0x80066458u;
    destination = 0x8006ECB8u + 68u * index;
    end = source + 0x40u;
    /* Both bases and the 68-byte stride prove every copied address aligned */
    if (((destination | source) & 3u) != 0u)
    {
        do
        {
            a = r_u32(source + 0u);
            a = r_u32(source + 0u);
            b = r_u32(source + 4u);
            b = r_u32(source + 4u);
            c = r_u32(source + 8u);
            c = r_u32(source + 8u);
            d = r_u32(source + 12u);
            d = r_u32(source + 12u);
            w_u32(destination + 0u, a);
            w_u32(destination + 0u, a);
            w_u32(destination + 4u, b);
            w_u32(destination + 4u, b);
            w_u32(destination + 8u, c);
            w_u32(destination + 8u, c);
            w_u32(destination + 12u, d);
            w_u32(destination + 12u, d);
            source += 16u;
            destination += 16u;
        } while (source != end);
    }
    else
    {
        do
        {
            a = r_u32(source + 0u);
            b = r_u32(source + 4u);
            c = r_u32(source + 8u);
            d = r_u32(source + 12u);
            w_u32(destination + 0u, a);
            w_u32(destination + 4u, b);
            w_u32(destination + 8u, c);
            w_u32(destination + 12u, d);
            source += 16u;
            destination += 16u;
        } while (source != end);
    }
    a = r_u32(source);
    a = r_u32(source);
    w_u32(destination, a);
    w_u32(destination, a);
    index = 0u;
    actor = 0x80065940u;
    do
    {
        port = index << 4;
        state = PadGetStatePSX(port);
        if (state == 2u)
            w_u8(actor + 2u, 1u);
        else if ((sint32)state < 3)
        {
            if (state == 1u)
            {
                w_u8(actor + 2u, 0u);
                PadSetActPSX(port, actor, 2u);
            }
        }
        else if (state == 6u)
        {
            if (r_u8(actor + 2u) == 0u)
            {
                if (PadSetActAlignPSX(port, 0x80056864u) != 0u)
                    w_u8(actor + 2u, 2u);
            }
        }
        if (r_u8(actor + 3u) != 0u)
        {
            active = r_u8(actor + 4u);
            intensity = r_u8(actor + 5u);
            active = active != 0u;
            w_u8(actor + 1u, (uint8)intensity);
            w_u8(actor, (uint8)active);
            if (active != 0u)
            {
                active = r_u8(actor + 4u);
                w_u8(actor + 4u, (uint8)(active - 1u));
            }
            delay = r_u8(actor + 6u);
            active = delay - 1u;
            if (delay != 0u)
                w_u8(actor + 6u, (uint8)active);
            else
            {
                intensity = r_u8(actor + 5u);
                decay = r_u8(actor + 7u);
                active = intensity - decay;
                if (intensity < decay)
                    w_u8(actor + 5u, 0u);
                else
                    w_u8(actor + 5u, (uint8)active);
            }
        }
        else
        {
            w_u8(actor + 1u, 0u);
            w_u8(actor, 0u);
        }
        ++index;
        actor += 8u;
    } while (index < 2u);
    return 0u;
}

void sub_8004BA34(uint32 first, uint32 second, uint32 third)
{
    FUNCTION_MARKER(0x8004BA34u, "SLUS_005.10");
    w_u32(0x800A32C0u, first);
    w_u32(0x800A329Cu, second);
    w_u32(0x800A32BCu, third);
}

void sub_8001A0AC(uint32 rectangle, uint32 color);
uint32 xport_guest_buffer_address(void *host_buffer, size_t bytes);
uint32 sub_800185CC(uint32 parsed, uint32 image);
uint32 sub_80019010(uint32 object, uint32 mode);
uint32 sub_800187E4(uint32 image, uint32 output, uint32 incoming_s1);
uint32 sub_80018618(uint32 image, uint32 tpage_out, uint32 clut_out, uint32 uv_out, uint32 incoming_s1);
uint32 sub_80018124(uint32 width, uint32 height, uint32 width_alignment, uint32 height_alignment, uint32 max_width, uint32 max_height);
uint32 sub_80017EC4(uint32 node, uint32 split);
uint32 sub_80017F4C(uint32 node, uint32 split);
uint32 sub_80015368(uint32 path);
uint32 sub_80018080(uint32 optional_split);
uint32 sub_80017E3C(uint32 parent, uint32 type, uint32 x, uint32 y, uint32 width, uint32 height);
uint32 sub_80019034(uint32 asset, uint32 size);
uint32 sub_800116F4(uint32 bytes);
void sub_80017E0C(void);
uint32 sub_80011F8C(uint32 lane);
uint32 sub_80012088(uint32 buttons, uint32 map_low, uint32 map_high);
uint32 sub_80017D5C(void);
void sub_80019E7C(uint32 flags);
uint32 sub_800120D4(void);
void xport_gte_write_data(uint32 register_index, uint32 value);
uint32 xport_gte_read_data(uint32 register_index);

uint32 sub_80017D5C(void)
{
    uint8 local_frame[128];
    uint32 frame;
    DRAWENV *environment, *result;
    FUNCTION_MARKER(0x80017D5Cu, "SLUS_005.10");
    frame = xport_guest_buffer_address(local_frame, sizeof(local_frame));
    environment = (DRAWENV *)psx_addr(frame + 0x18u, sizeof(DRAWENV));
    w_u32(frame + 0x10u, 0x200u);
    (void)SetDefDrawEnv(environment, 0, 0, 0x400, 0x200);
    w_u8(frame + 0x30u, 1u);
    w_u8(frame + 0x2Fu, 1u);
    (void)PutDrawEnv(environment);
    (void)VSync(0);
    result = PutDrawEnv(environment);
    return xport_guest_buffer_address(result, sizeof(DRAWENV));
}

uint32 sub_800120D4(void)
{
    uint32 consumer, producer, raw, low, high, first, second, bits, extra, mode;
    uint32 count, pointer, origin, old, rising, lane, cache, type, table, value, map_low, map_high;
    uint32 buttons, converted, part, cooldown, selectors, nibble, axis_value;
    FUNCTION_MARKER(0x800120D4u, "SLUS_005.10");
    consumer = r_u8(0x80065918u);
    producer = r_u8(0x80065905u);
    if (producer != consumer)
        w_u8(0x80065918u, (uint8)((consumer + 1u) & 7u));
    consumer = r_u8(0x80065918u);
    raw = 0x8006ECB8u + (((consumer << 4u) + consumer) << 2u);
    value = r_u8(raw);
    low = 0xFFFFu;
    if (value != 0xFFu)
    {
        first = r_u8(raw + 2u);
        second = r_u8(raw + 3u);
        low = (first << 8u) | second;
    }
    value = r_u8(raw + 0x22u);
    high = 0xFFFF0000u;
    if (value != 0xFFu)
    {
        first = r_u8(raw + 0x24u);
        second = r_u8(raw + 0x25u);
        high = ((first << 8u) | second) << 16u;
    }
    bits = ~(high | low);
    value = r_u8(raw + 1u);
    if (value == 0x23u)
    {
        first = r_u8(raw + 5u);
        second = r_u8(raw + 7u);
        extra = (uint32)(first == 0xFFu) << 6u;
        if (second == 0xFFu)
            extra |= 4u;
        value = r_u8(raw + 6u);
        if (value == 0xFFu)
            bits |= 0x80u | extra;
        else
            bits |= extra;
    }
    value = r_u8(raw + 0x23u);
    if (value == 0x23u)
    {
        first = r_u8(raw + 0x27u);
        second = r_u8(raw + 0x29u);
        extra = (uint32)(first == 0xFFu) << 22u;
        if (second == 0xFFu)
            extra |= 0x40000u;
        value = r_u8(raw + 0x28u);
        if (value == 0xFFu)
            bits |= 0x800000u | extra;
        else
            bits |= extra;
    }
    mode = r_u32(0x8006591Cu);
    if (mode == 1u)
    {
        count = r_u16(0x80065922u) - 1u;
        w_u16(0x80065922u, (uint16)count);
        if ((count & 0xFFFFu) == 0xFFFFu)
        {
            pointer = r_u32(0x80065914u);
            count = r_u16(pointer + 4u);
            w_u32(0x80065914u, pointer + 4u);
            w_u16(0x80065922u, (uint16)count);
        }
        pointer = r_u32(0x80065914u);
        value = r_u16(pointer + 2u);
        if (bits != 0u)
            bits = value | 0x800u;
        else
            bits = value;
    }
    else if (mode == 2u)
    {
        origin = r_u32(0x80065938u);
        pointer = r_u32(0x80065914u);
        low = bits & 0xFFFFu;
        value = 0u;
        if (pointer != origin + 8u)
        {
            value = r_u16(pointer + 2u);
            value = (uint32)(value == low);
        }
        if (value != 0u)
        {
            count = r_u16(pointer);
            w_u16(pointer, (uint16)(count + 1u));
        }
        else
        {
            pointer = r_u32(0x80065914u);
            w_u32(0x80065914u, pointer + 4u);
            w_u16(pointer + 6u, (uint16)bits);
            w_u16(pointer + 4u, 0u);
        }
    }
    old = r_u32(0x800658D8u);
    w_u32(0x800658D8u, bits);
    rising = bits & ~old;
    w_u32(0x80065930u, (bits & 0xFFFFu) | (rising << 16u));
    w_u32(0x80065934u, (bits >> 16u) | (rising & 0xFFFF0000u));
    lane = 0u;
    do
    {
        mode = r_u32(0x8006591Cu);
        cache = 0x80065C28u + lane * 0x18u;
        if (mode == 0u)
            type = sub_80011F8C(lane);
        else
            type = 2u;
        w_u16(cache, (uint16)type);
        type = (uint32)(sint32)(sint16)r_u16(cache);
        buttons = r_u32(0x80065930u + (lane << 2u));
        table = 0x80056774u + lane * 0x30u + (type << 3u);
        w_u32(cache + 0xCu, buttons);
        high = r_u32(table + 4u);
        (void)r_u32(table);
        w_u8(0x80065943u + (lane << 3u), (uint8)((high >> 12u) & 1u));
        type = (uint32)(sint32)(sint16)r_u16(cache);
        buttons = r_u32(0x80065930u + (lane << 2u));
        table = 0x80056774u + lane * 0x30u + (type << 3u);
        map_low = r_u32(table);
        map_high = r_u32(table + 4u);
        converted = sub_80012088(buttons & 0xF7FFF7FFu, map_low, map_high);
        buttons = r_u32(cache + 0xCu);
        w_u32(cache + 8u, converted);
        part = buttons & 0xF0000000u;
        value = part >> 1u;
        if (part != 0u)
        {
            old = r_u32(cache + 4u);
            old <<= 4u;
            xport_gte_write_data(30u, value);
            value = xport_gte_read_data(31u);
            w_u32(cache + 4u, old | value);
            w_u16(cache + 2u, 0x14u);
        }
        else
        {
            cooldown = (uint32)(sint32)(sint16)r_u16(cache + 2u);
            count = r_u16(cache + 2u);
            count -= 1u;
            if (cooldown != 0u)
            {
                w_u16(cache + 2u, (uint16)count);
                if ((count << 16u) == 0u)
                    w_u32(cache + 4u, 0u);
            }
        }
        type = (uint32)(sint32)(sint16)r_u16(cache);
        if ((sint32)type >= 3)
        {
            selectors = r_u16(0x800567D4u + lane * 12u + (type << 1u));
            old = r_u32(cache + 0x10u);
            w_u32(cache + 0x10u, 0x80808080u);
            nibble = selectors & 0xFu;
            w_u32(cache + 0x14u, old);
            if (nibble != 0u)
            {
                value = r_u8(raw + 4u);
                axis_value = r_u8(0x80065C58u + lane * 0x400u + value);
                w_u8(cache + 0xFu + nibble, (uint8)axis_value);
            }
            nibble = (selectors >> 4u) & 0xFu;
            if (nibble != 0u)
            {
                value = r_u8(raw + 5u);
                axis_value = r_u8(0x80065D58u + lane * 0x400u + value);
                w_u8(cache + 0xFu + nibble, (uint8)axis_value);
            }
            nibble = (selectors >> 8u) & 0xFu;
            if (nibble != 0u)
            {
                value = r_u8(raw + 6u);
                axis_value = r_u8(0x80065E58u + lane * 0x400u + value);
                w_u8(cache + 0xFu + nibble, (uint8)axis_value);
            }
            nibble = selectors >> 12u;
            if (nibble != 0u)
            {
                value = r_u8(raw + 7u);
                axis_value = r_u8(0x80065F58u + lane * 0x400u + value);
                w_u8(cache + 0xFu + nibble, (uint8)axis_value);
            }
        }
        raw += 0x22u;
        lane += 1u;
    } while (lane < 2u);
    return 0u;
}

uint32 sub_80011F8C(uint32 lane)
{
    uint32 base = 0x80066458u + (((lane << 4u) + lane) << 1u);
    uint32 type;
    FUNCTION_MARKER(0x80011F8Cu, "SLUS_005.10");
    if (r_u8(base) != 0u)
        return 0u;
    type = r_u8(base + 1u);
    if (type == 0x53u)
        return 4u;
    if ((sint32)type < 0x54)
    {
        if (type == 0x23u)
            return 3u;
        if (type == 0x41u)
            return 2u;
        return 1u;
    }
    if (type == 0x73u)
        return 5u;
    return 1u;
}

uint32 sub_80012088(uint32 buttons, uint32 map_low, uint32 map_high)
{
    uint32 result = 0u;
    FUNCTION_MARKER(0x80012088u, "SLUS_005.10");
    while ((buttons & 0xFFFFu) != 0u)
    {
        result |= (buttons & 0x10001u) << (map_low & 0xFu);
        map_low = (map_low >> 4u) | (map_high << 28u);
        map_high >>= 4u;
        buttons >>= 1u;
    }
    return result;
}

void sub_80019E7C(uint32 flags)
{
    uint32 wide = (flags >> 1u) & 1u;
    DISPENV display;
    DRAWENV draw;
    FUNCTION_MARKER(0x80019E7Cu, "SLUS_005.10");
    (void)sub_80018080(flags & 1u);
    (void)SetDefDispEnv(&display, 0, 0, wide != 0u ? 960 : 640, 480);
    (void)SetDefDrawEnv(&draw, 0, 0, 640, 480);
    display.screen.h = 240;
    draw.dfe = 1;
    display.isrgb24 = (uint8)wide;
    draw.tpage = 32;
    display.screen.x = (sint16)(sint8)r_u8(0x8006531Cu);
    display.screen.y = (sint16)(sint8)r_u8(0x8006531Du);
    (void)PutDrawEnv(&draw);
    (void)PutDispEnv(&display);
}

uint32 sub_80018080(uint32 optional_split)
{
    uint32 root;
    uint32 left;
    uint32 leaf;
    uint32 result;
    FUNCTION_MARKER(0x80018080u, "SLUS_005.10");
    if (r_u32(0x800659C8u) != 0u)
        sub_80017E0C();
    root = sub_80017E3C(0u, 0u, 0u, 0u, 0x400u, 0x200u);
    w_u32(0x800659C8u, root);
    sub_80017EC4(root, 0x280u);
    root = r_u32(0x800659C8u);
    left = r_u32(root + 0x10u);
    sub_80017F4C(left, 0x1E0u);
    root = r_u32(0x800659C8u);
    left = r_u32(root + 0x10u);
    leaf = r_u32(left + 0x10u);
    result = 1u;
    w_u32(leaf + 8u, result);
    if (optional_split != 0u)
        result = sub_80017F4C(r_u32(root + 0x14u), 0x100u);
    return result;
}

uint32 sub_80017E3C(uint32 parent, uint32 type, uint32 x, uint32 y, uint32 width, uint32 height)
{
    uint32 node;
    uint32 count;
    FUNCTION_MARKER(0x80017E3Cu, "SLUS_005.10");
    node = sub_800116F4(0x18u);
    count = r_u32(0x800659CCu);
    w_u32(node + 12u, parent);
    w_u32(node + 8u, type);
    w_u16(node, (uint16)x);
    w_u16(node + 2u, (uint16)y);
    w_u16(node + 4u, (uint16)width);
    w_u16(node + 6u, (uint16)height);
    w_u32(0x800659CCu, count + 1u);
    return node;
}

uint32 sub_80017EC4(uint32 node, uint32 split)
{
    uint32 x;
    uint32 y;
    uint32 width;
    uint32 height;
    uint32 first;
    uint32 second;
    FUNCTION_MARKER(0x80017EC4u, "SLUS_005.10");
    x = (uint32)(sint32)(sint16)r_u16(node);
    y = (uint32)(sint32)(sint16)r_u16(node + 2u);
    height = (uint32)(sint32)(sint16)r_u16(node + 6u);
    first = sub_80017E3C(node, 0u, x, y, split, height);
    x = (uint32)(sint32)(sint16)r_u16(node);
    width = (uint32)(sint32)(sint16)r_u16(node + 4u);
    y = (uint32)(sint32)(sint16)r_u16(node + 2u);
    width -= split;
    height = (uint32)(sint32)(sint16)r_u16(node + 6u);
    x += split;
    second = sub_80017E3C(node, 0u, x, y, width, height);
    w_u32(node + 8u, 2u);
    w_u32(node + 16u, first);
    w_u32(node + 20u, second);
    return second;
}

uint32 sub_80017F4C(uint32 node, uint32 split)
{
    uint32 x;
    uint32 y;
    uint32 width;
    uint32 height;
    uint32 first;
    uint32 second;
    FUNCTION_MARKER(0x80017F4Cu, "SLUS_005.10");
    x = (uint32)(sint32)(sint16)r_u16(node);
    y = (uint32)(sint32)(sint16)r_u16(node + 2u);
    width = (uint32)(sint32)(sint16)r_u16(node + 4u);
    first = sub_80017E3C(node, 0u, x, y, width, split);
    x = (uint32)(sint32)(sint16)r_u16(node);
    width = (uint32)(sint32)(sint16)r_u16(node + 4u);
    y = (uint32)(sint32)(sint16)r_u16(node + 2u);
    height = (uint32)(sint32)(sint16)r_u16(node + 6u);
    y += split;
    height -= split;
    second = sub_80017E3C(node, 0u, x, y, width, height);
    w_u32(node + 8u, 3u);
    w_u32(node + 16u, first);
    w_u32(node + 20u, second);
    return second;
}

uint32 sub_80019034(uint32 asset, uint32 size)
{
    uint32 object;
    uint32 offset;
    FUNCTION_MARKER(0x80019034u, "SLUS_005.10");
    object = sub_800116F4(0x14u);
    offset = r_u32(asset);
    sub_800187E4(asset + offset, object + 8u, asset);
    w_u32(object, asset);
    w_u8(object + 4u, 0x80u);
    w_u8(object + 5u, 0x80u);
    w_u8(object + 6u, 0x80u);
    sub_80019010(object, size);
    return object;
}

uint32 sub_800187E4(uint32 image, uint32 output, uint32 incoming_s1)
{
    uint32 result, bitmap, flags, width, height, shift;
    FUNCTION_MARKER(0x800187E4u, "SLUS_005.10");
    result = sub_80018618(image, output + 8u, output + 10u, output + 6u, incoming_s1);
    bitmap = r_u32(result + 12u);
    flags = r_u32(result);
    width = (uint32)(sint32)(sint16)r_u16(bitmap + 4u);
    shift = (2u - (flags & 3u)) & 31u;
    w_u16(output + 2u, (uint16)(width << shift));
    bitmap = r_u32(result + 12u);
    height = r_u16(bitmap + 6u);
    w_u16(output, 1u);
    w_u16(output + 4u, (uint16)height);
    return result;
}

uint32 sub_80018618(uint32 image, uint32 tpage_out, uint32 clut_out, uint32 uv_out, uint32 incoming_s1)
{
    uint32 palette = incoming_s1, rectangle, flags, width, height, stored_width;
    uint32 pixels, bitmap, x, y, value, shift;
    FUNCTION_MARKER(0x80018618u, "SLUS_005.10");
    sub_800185CC(0x8006F628u, image);
    rectangle = r_u32(0x8006F62Cu);
    if (rectangle != 0u)
    {
        flags = r_u32(0x8006F628u);
        if ((flags & 0x10u) != 0u)
        {
            width = (uint32)(sint32)(sint16)r_u16(rectangle + 4u);
            if ((sint32)width < 17)
                width = 16u;
            else
                width = 256u;
        }
        else
            width = (uint32)(sint32)(sint16)r_u16(rectangle + 4u);
        rectangle = r_u32(0x8006F62Cu);
        height = (uint32)(sint32)(sint16)r_u16(rectangle + 6u);
        stored_width = (uint32)(sint32)(sint16)r_u16(rectangle + 4u);
        palette = sub_80018124(width, height, 16u, 1u, stored_width, 1u);
        if (palette != 0u)
        {
            pixels = r_u32(0x8006F630u);
            LoadImagePSX((PSX_RECT *)psx_addr(palette, sizeof(PSX_RECT)), (uint32 *)psx_addr(pixels, 1u));
            if (clut_out != 0u)
            {
                x = (uint32)(sint32)(sint16)r_u16(palette);
                y = (uint32)(sint32)(sint16)r_u16(palette + 2u);
                value = GetClut((sint32)x, (sint32)y);
                w_u16(clut_out, (uint16)value);
            }
        }
        else if (clut_out != 0u)
            w_u16(clut_out, 0u);
    }
    else if (clut_out != 0u)
        w_u16(clut_out, 0u);
    rectangle = r_u32(0x8006F634u);
    flags = r_u32(0x8006F628u);
    width = (uint32)(sint32)(sint16)r_u16(rectangle + 4u);
    height = (uint32)(sint32)(sint16)r_u16(rectangle + 6u);
    stored_width = 64u << (flags & 3u);
    bitmap = sub_80018124(width, height, 64u, 256u, stored_width, 256u);
    if (bitmap != 0u)
    {
        pixels = r_u32(0x8006F638u);
        LoadImagePSX((PSX_RECT *)psx_addr(bitmap, sizeof(PSX_RECT)), (uint32 *)psx_addr(pixels, 1u));
    }
    w_u32(0x8006F62Cu, palette);
    w_u32(0x8006F634u, bitmap);
    if (tpage_out != 0u)
    {
        x = (uint32)(sint32)(sint16)r_u16(bitmap);
        flags = r_u32(0x8006F628u);
        y = (uint32)(sint32)(sint16)r_u16(bitmap + 2u);
        value = GetTPage((sint32)(flags & 3u), 0, (sint32)x, (sint32)y);
        w_u16(tpage_out, (uint16)value);
    }
    if (uv_out != 0u)
    {
        x = r_u16(bitmap);
        flags = r_u32(0x8006F628u);
        y = r_u8(bitmap + 2u);
        shift = (2u - (flags & 3u)) & 31u;
        value = ((x & 0x3Fu) << shift) | (y << 8);
        w_u16(uv_out, (uint16)value);
    }
    return 0x8006F628u;
}

uint32 sub_800185CC(uint32 parsed, uint32 image)
{
    uint32 flags, value;
    FUNCTION_MARKER(0x800185CCu, "SLUS_005.10");
    flags = r_u32(image + 4u);
    w_u32(parsed, flags);
    if ((flags & 8u) != 0u)
    {
        w_u32(parsed + 4u, image + 12u);
        w_u32(parsed + 8u, image + 20u);
        value = r_u32(image + 8u);
        image += value;
    }
    else
    {
        w_u32(parsed + 8u, 0u);
        w_u32(parsed + 4u, 0u);
    }
    w_u32(parsed + 12u, image + 12u);
    value = image + 20u;
    w_u32(parsed + 16u, value);
    return value;
}

uint32 sub_80018124(uint32 width, uint32 height, uint32 width_alignment, uint32 height_alignment, uint32 max_width, uint32 max_height)
{
    uint32 node, kind, region_width, region_height, x, y, x_mask, y_mask, x_slack, y_slack, value, parent, sibling;
    FUNCTION_MARKER(0x80018124u, "SLUS_005.10");
    node = r_u32(0x800659C8u);
    x_mask = width_alignment - 1u;
    y_mask = height_alignment - 1u;
    x_slack = max_width - width;
    y_slack = max_height - height;
    if (node == 0u)
        goto out_of_vram;
iteration:
    kind = r_u32(node + 8u);
    if (kind == 1u)
        goto backtrack;
    if (kind == 0u)
    {
        region_width = (uint32)(sint32)(sint16)r_u16(node + 4u);
        if ((sint32)region_width < (sint32)width)
            goto backtrack;
        region_height = (uint32)(sint32)(sint16)r_u16(node + 6u);
        if ((sint32)region_height < (sint32)height)
            goto backtrack;
        x = (uint32)(sint32)(sint16)r_u16(node);
        value = (uint32)((sint32)x_slack < (sint32)(x & x_mask));
        parent = 0u - x;
        if (value != 0u)
        {
            if ((sint32)region_width < (sint32)(width + (parent & x_mask)))
                goto backtrack;
        }
        y = (uint32)(sint32)(sint16)r_u16(node + 2u);
        parent = 0u - y;
        if ((sint32)y_slack < (sint32)(y & y_mask))
        {
            if ((sint32)region_height < (sint32)(height + (parent & y_mask)))
                goto backtrack;
        }
        if (value != 0u)
        {
            (void)sub_80017EC4(node, (0u - x) & x_mask);
            node = r_u32(node + 20u);
        }
        region_width = (uint32)(sint32)(sint16)r_u16(node + 4u);
        if ((sint32)width < (sint32)region_width)
        {
            (void)sub_80017EC4(node, width);
            node = r_u32(node + 16u);
        }
        y = (uint32)(sint32)(sint16)r_u16(node + 2u);
        if ((sint32)y_slack < (sint32)(y & y_mask))
        {
            (void)sub_80017F4C(node, (0u - y) & y_mask);
            node = r_u32(node + 20u);
        }
        region_height = (uint32)(sint32)(sint16)r_u16(node + 6u);
        if ((sint32)height < (sint32)region_height)
        {
            (void)sub_80017F4C(node, height);
            node = r_u32(node + 16u);
        }
        w_u32(node + 8u, 1u);
        return node;
    }
    if (kind == 2u)
    {
        sibling = r_u32(node + 16u);
        value = r_u32(sibling + 8u);
        if (value != 1u)
        {
            region_width = (uint32)(sint32)(sint16)r_u16(sibling + 4u);
            if ((sint32)region_width >= (sint32)width)
                goto descend;
        }
        sibling = r_u32(node + 20u);
        value = r_u32(sibling + 8u);
        if (value == 1u)
            goto backtrack;
        region_width = (uint32)(sint32)(sint16)r_u16(sibling + 4u);
        if ((sint32)region_width < (sint32)width)
            goto backtrack;
        goto descend;
    }
    if (kind == 3u)
    {
        sibling = r_u32(node + 16u);
        value = r_u32(sibling + 8u);
        if (value != 1u)
        {
            region_height = (uint32)(sint32)(sint16)r_u16(sibling + 6u);
            if ((sint32)region_height >= (sint32)height)
                goto descend;
        }
        sibling = r_u32(node + 20u);
        value = r_u32(sibling + 8u);
        if (value == 1u)
            goto backtrack;
        region_height = (uint32)(sint32)(sint16)r_u16(sibling + 6u);
        if ((sint32)region_height < (sint32)height)
            goto backtrack;
        goto descend;
    }
    goto iteration;
descend:
    node = sibling;
    if (node != 0u)
        goto iteration;
    goto out_of_vram;
backtrack:
    value = r_u32(node + 12u);
    while (value != 0u)
    {
        parent = r_u32(node + 12u);
        sibling = r_u32(parent + 20u);
        if (node != sibling)
            break;
        node = parent;
        value = r_u32(node + 12u);
    }
    node = r_u32(node + 12u);
    if (node == 0u)
        goto out_of_vram;
    node = r_u32(node + 20u);
    if (node != 0u)
        goto iteration;
out_of_vram:
    (void)sub_80015368(0x80065668u);
    return 0u;
}

uint32 sub_80019010(uint32 object, uint32 mode)
{
    uint32 flags, opcode;
    FUNCTION_MARKER(0x80019010u, "SLUS_005.10");
    flags = r_u16(object + 16u);
    opcode = (mode & 3u) ^ 0x65u; w_u8(object + 7u, (uint8)opcode);
    w_u16(object + 16u, (uint16)((flags & 0xFF9Fu) | (mode & 0x60u)));
    return opcode;
}

void sub_8001A0AC(uint32 rectangle, uint32 color)
{
    static TILE packet;
    static uint32 registered;
    FUNCTION_MARKER(0x8001A0ACu, "SLUS_005.10");
    if (registered == 0u)
    {
        if (!gpu_register_packet_range(&packet, sizeof(packet)))
        {
            fprintf(stderr, "V8: cannot register rectangle GPU packet\n");
            abort();
        }
        registered = 1u;
    }
    packet.tag = 0x03000000u;
    packet.code = 0x60u;
    packet.r0 = (uint8)color;
    packet.g0 = (uint8)(color >> 8);
    packet.b0 = (uint8)(color >> 16);
    packet.x0 = (sint16)r_u16(rectangle);
    packet.y0 = (sint16)r_u16(rectangle + 2u);
    packet.w = (sint16)r_u16(rectangle + 4u);
    packet.h = (sint16)r_u16(rectangle + 6u);
    DrawPrim(&packet);
}

void sub_80045088(uint32 address);
uint32 sub_800190D8(uint32 object);
uint32 sub_800190A8(uint32 object);
uint32 sub_8001884C(uint32 descriptor);
uint32 sub_8001859C(uint32 clut);
uint32 sub_80018530(uint32 x, uint32 y);
uint32 sub_80018470(uint32 x, uint32 y);
uint32 sub_800183EC(uint32 node, uint32 incoming_v0);
uint32 sub_80017160(void);
uint32 sub_80019138(uint32 object, uint32 text);
uint32 sub_80019370(uint32 object, uint32 packet, uint32 character, uint32 x, uint32 y);
void sub_80019960(uint32 object, uint32 text, uint32 x, uint32 y);
void sub_80019A58(uint32 object, uint32 text, uint32 rectangle, uint32 flags, uint32 incoming_s2, uint32 incoming_s3);
uint32 xport_guest_buffer_address(void *host_buffer, size_t bytes);
uint32 sub_80015FB4(void);
void sub_80019E20(void);
void sub_8001A11C(uint32 rectangle, uint32 color);
void sub_800165CC(uint32 wait);
uint32 VSyncCallbackPSX(uint32 guest_callback);

uint32 sub_80017160(void)
{
    uint32 old_byte, old_state, state;
    FUNCTION_MARKER(0x80017160u, "SLUS_005.10");
    old_byte = r_u8(0x800568D8u);
    old_state = r_u32(0x800568D4u);
    w_u8(0x800568D8u, old_state);
    state = (old_state >> 1u) + (old_byte << 31u);
    state ^= old_state << 12u;
    state ^= state >> 20u;
    w_u32(0x800568D4u, state);
    return state & 0x7FFFu;
}

void v8_native_19A58(uint32 object, uint32 text, const PSX_RECT *rectangle, uint32 flags, uint32 incoming_s2, uint32 incoming_s3)
{
    uint32 x = incoming_s2, y = incoming_s3, mode, width, first, second, font, height, delta, adjusted, color, shadow_x, shadow_y;
    mode = flags & 3u;
    if (mode == 1u)
    {
        width = sub_80019138(object, text);
        first = (uint32)(sint32)(sint16)xport_load_le16((const uint8 *)rectangle);
        second = (uint32)(sint32)(sint16)xport_load_le16((const uint8 *)rectangle + 4u);
        x = first + second - width;
    }
    else if (mode == 0u)
        x = (uint32)(sint32)(sint16)xport_load_le16((const uint8 *)rectangle);
    else if (mode == 2u)
    {
        width = sub_80019138(object, text);
        second = (uint32)(sint32)(sint16)xport_load_le16((const uint8 *)rectangle + 4u);
        first = (uint32)(sint32)(sint16)xport_load_le16((const uint8 *)rectangle);
        x = first + ((second - width) >> 1u);
    }
    mode = flags & 12u;
    if (mode == 4u)
    {
        first = (uint32)(sint32)(sint16)xport_load_le16((const uint8 *)rectangle + 2u);
        font = r_u32(object);
        second = (uint32)(sint32)(sint16)xport_load_le16((const uint8 *)rectangle + 6u);
        height = r_u8(font + 6u);
        y = first + second - height;
    }
    else if (mode == 0u)
        y = (uint32)(sint32)(sint16)xport_load_le16((const uint8 *)rectangle + 2u);
    else if (mode == 8u)
    {
        font = r_u32(object);
        second = (uint32)(sint32)(sint16)xport_load_le16((const uint8 *)rectangle + 6u);
        height = r_u8(font + 6u);
        first = (uint32)(sint32)(sint16)xport_load_le16((const uint8 *)rectangle + 2u);
        delta = second - height;
        adjusted = delta + (delta >> 31u);
        y = first + ((adjusted >> 1u) | (adjusted & 0x80000000u));
    }
    if ((flags & 0x40u) != 0u)
    {
        shadow_x = x + ((flags >> 8u) & 15u);
        color = r_u32(object + 4u);
        shadow_y = y + ((flags >> 12u) & 15u);
        w_u8(object + 4u, 0u);
        w_u8(object + 5u, 0u);
        w_u8(object + 6u, 0u);
        sub_80019960(object, text, shadow_x, shadow_y);
        w_u32(object + 4u, color);
    }
    sub_80019960(object, text, x, y);
    return;
}

void sub_80019A58(uint32 object, uint32 text, uint32 rectangle, uint32 flags, uint32 incoming_s2, uint32 incoming_s3)
{
    FUNCTION_MARKER(0x80019A58u, "SLUS_005.10");
    v8_native_19A58(object, text, (const PSX_RECT *)psx_addr(rectangle, sizeof(PSX_RECT)), flags, incoming_s2, incoming_s3);
}

uint32 sub_80019138(uint32 object, uint32 text)
{
    uint32 character;
    uint32 total = 0u, glyph = 0u, font, delta, advance, bearing, width;
    FUNCTION_MARKER(0x80019138u, "SLUS_005.10");
    character = r_u8(text);
    text += 1u;
    while (character != 0u)
    {
        if (character >= 32u)
        {
            font = r_u32(object);
            delta = character - r_u8(font + 5u);
            glyph = font + (delta << 2u) + delta + 8u;
            advance = r_u8(glyph + 3u);
            total += advance;
        }
        else
            text += r_u8(0x800568DCu + character);
        character = r_u8(text);
        text += 1u;
    }
    if (glyph != 0u)
    {
        advance = r_u8(glyph + 3u);
        bearing = (uint32)(sint32)(sint8)r_u8(glyph + 4u);
        width = r_u8(glyph + 2u);
        return total - advance + bearing + width;
    }
    return total;
}

static sint32 native_font_merge_host(uint8 *first, uint8 *second)
{
    uint32 first_length = first[3];
    uint32 second_length = second[3];
    uint32 length = first_length + second_length + 1u;
    if (length >= 17u)
        return -1;
    xport_store_u8(first + 3u, (uint8)length);
    xport_store_le32(second, 0u);
    return 0;
}

uint32 v8_native_19370(uint32 object, uint8 *packet, uint32 character, uint32 x, uint32 y)
{
    uint32 font, base_code, page, rgb, clut, height_font, height, delta, glyph, low, high, uv, bearing, width, advance;
    font = r_u32(object);
    base_code = r_u8(font + 5u);
    xport_store_u8(packet + 3u, (uint8)(1u));
    page = r_u16(object + 0x10u);
    xport_store_le32(packet + 4u, (page & 0x9FFu) | 0xE1000400u);
    rgb = r_u32(object + 4u);
    xport_store_le32(packet + 8u, 0x04000000u);
    xport_store_le32(packet + 12u, rgb);
    clut = r_u16(object + 0x12u);
    xport_store_le16(packet + 0x16u, (uint16)(clut));
    height_font = r_u32(object);
    height = r_u8(height_font + 6u);
    delta = (character & 255u) - base_code;
    xport_store_le16(packet + 0x1Au, (uint16)(height));
    glyph = font + (delta << 2u) + delta + 8u;
    low = r_u8(glyph);
    high = r_u8(glyph + 1u);
    uv = r_u16(object + 14u);
    xport_store_le16(packet + 0x14u, (uint16)(uv + (low | (high << 8u))));
    bearing = (uint32)(sint32)(sint8)r_u8(glyph + 4u);
    xport_store_le16(packet + 0x12u, (uint16)(y));
    xport_store_le16(packet + 0x10u, (uint16)(x + bearing));
    width = r_u8(glyph + 2u);
    xport_store_le16(packet + 0x18u, (uint16)(width));
    (void)native_font_merge_host(packet, packet + 8u);
    advance = r_u8(glyph + 3u);
    return x + advance;
}

void sub_80019960(uint32 object, uint32 text, uint32 x, uint32 y)
{
    uint32 packet_words[8];
    uint32 start_x = x, character, font, height, component;
    FUNCTION_MARKER(0x80019960u, "SLUS_005.10");
    character = r_u8(text);
    text += 1u;
    while (character != 0u)
    {
        if (character == 10u)
        {
            font = r_u32(object);
            height = r_u8(font + 7u);
            x = start_x;
            y += height;
        }
        else if (character == 1u)
        {
            component = r_u8(text);
            w_u8(object + 4u, component);
            component = r_u8(text + 1u);
            w_u8(object + 5u, component);
            component = r_u8(text + 2u);
            text += 3u;
            w_u8(object + 6u, component);
        }
        else
        {
            (void)DrawSync(0);
            x = v8_native_19370(object, (uint8 *)packet_words, character, x, y);
            DrawPrim(packet_words);
        }
        character = r_u8(text);
        text += 1u;
    }
    return;
}

uint32 sub_80019370(uint32 object, uint32 packet, uint32 character, uint32 x, uint32 y)
{
    FUNCTION_MARKER(0x80019370u, "SLUS_005.10");
    return v8_native_19370(object, (uint8 *)psx_addr(packet, 28u), character, x, y);
}

uint32 sub_800190D8(uint32 object)
{
    uint32 image;
    FUNCTION_MARKER(0x800190D8u, "SLUS_005.10");
    image = r_u32(object);
    sub_80045088(image);
    return sub_800190A8(object);
}

uint32 sub_800190A8(uint32 object)
{
    uint32 result;
    FUNCTION_MARKER(0x800190A8u, "SLUS_005.10");
    result = sub_8001884C(object + 8u);
    sub_80045088(object);
    return result;
}

uint32 sub_8001884C(uint32 descriptor)
{
    uint32 page, position, shift, x, y, clut;
    FUNCTION_MARKER(0x8001884Cu, "SLUS_005.10");
    if (r_u16(descriptor) == 0u)
        return 1u;
    page = r_u16(descriptor + 8u);
    position = r_u16(descriptor + 6u);
    shift = (2u - (page >> 7)) & 31u;
    clut = r_u16(descriptor + 10u);
    x = ((page & 15u) << 6) + ((position & 255u) >> shift);
    y = ((page & 16u) << 4) + (position >> 8);
    if (clut != 0u)
        (void)sub_8001859C(clut);
    w_u16(descriptor, 0u);
    return sub_80018530(x, y);
}

uint32 sub_8001859C(uint32 clut)
{
    FUNCTION_MARKER(0x8001859Cu, "SLUS_005.10");
    return sub_80018530((clut & 63u) << 4, (clut & 65535u) >> 6);
}

uint32 sub_80018530(uint32 x, uint32 y)
{
    uint32 node;
    FUNCTION_MARKER(0x80018530u, "SLUS_005.10");
    node = sub_80018470(x, y);
    if (node == 0u)
        return 0u;
    (void)sub_800183EC(node, node);
    return 1u;
}

uint32 sub_80018470(uint32 x, uint32 y)
{
    uint32 node;
    uint32 kind, value, parent, sibling;
    FUNCTION_MARKER(0x80018470u, "SLUS_005.10");
    node = r_u32(0x800659C8u);
    while (node != 0u)
    {
        kind = r_u32(node + 8u);
        if (kind == 1u)
        {
            value = (uint32)(sint32)(sint16)r_u16(node);
            if (value == x)
            {
                value = (uint32)(sint32)(sint16)r_u16(node + 2u);
                if (value == y)
                    return node;
            }
        }
        else if (kind != 0u)
        {
            if (kind >= 4u)
                continue;
            node = r_u32(node + 16u);
            continue;
        }
        value = r_u32(node + 12u);
        while (value != 0u)
        {
            parent = r_u32(node + 12u);
            sibling = r_u32(parent + 20u);
            if (node != sibling)
                break;
            node = parent;
            value = r_u32(node + 12u);
        }
        node = r_u32(node + 12u);
        if (node == 0u)
            break;
        node = r_u32(node + 20u);
        continue;
    }
    return node;
}

uint32 sub_800183EC(uint32 node, uint32 incoming_v0)
{
    uint32 parent, sibling, result = incoming_v0;
    FUNCTION_MARKER(0x800183ECu, "SLUS_005.10");
    parent = r_u32(node + 12u);
    while (parent != 0u)
    {
        sibling = r_u32(parent + 16u);
        if (node == sibling)
            sibling = r_u32(parent + 20u);
        result = r_u32(sibling + 8u);
        if (result != 0u)
            break;
        sub_80045088(node);
        sub_80045088(sibling);
        node = parent;
        parent = r_u32(node + 12u);
    }
    w_u32(node + 8u, 0u);
    return result;
}

uint32 sub_80015FB4(void)
{
    uint8 packet[8];
    uint32 guest_packet, iteration;
    FUNCTION_MARKER(0x80015FB4u, "SLUS_005.10");
    sub_80019E20();
    guest_packet = xport_guest_buffer_address(packet, sizeof(packet));
    SetDrawMode1((DR_MODE *)psx_addr(guest_packet, sizeof(packet)), 1, 1, 0x40);
    DrawPrim(psx_addr(guest_packet, sizeof(packet)));
    iteration = 0u;
    do
    {
        (void)VSync(0);
        sub_8001A11C(0u, 0x101010u);
        (void)DrawSync(2);
        iteration += 16u;
    } while (iteration < 256u);
    return 0u;
}

void sub_80019E20(void)
{
    uint8 environment_bytes[92];
    uint32 guest_environment, value;
    DRAWENV *environment;
    FUNCTION_MARKER(0x80019E20u, "SLUS_005.10");
    guest_environment = xport_guest_buffer_address(environment_bytes, sizeof(environment_bytes));
    environment = (DRAWENV *)psx_addr(guest_environment, sizeof(environment_bytes));
    (void)SetDefDrawEnv(environment, 0, 0, 640, 480);
    w_u8(guest_environment + 23u, 1u);
    value = GetTPage(0, 1, 0, 0);
    w_u16(guest_environment + 20u, (uint16)value);
    (void)PutDrawEnv(environment);
    return;
}

void sub_8001A11C(uint32 rectangle, uint32 color)
{
    uint8 packet[16];
    uint16 value;
    uint32 guest_packet;
    FUNCTION_MARKER(0x8001A11Cu, "SLUS_005.10");
    packet[3] = 3u;
    packet[7] = 0x62u;
    packet[4] = (uint8)color;
    packet[5] = (uint8)(color >> 8);
    packet[6] = (uint8)(color >> 16);
    if (rectangle != 0u)
    {
        value = r_u16(rectangle);
        memcpy(packet + 8, &value, sizeof(value));
        value = r_u16(rectangle + 2u);
        memcpy(packet + 10, &value, sizeof(value));
        value = r_u16(rectangle + 4u);
        memcpy(packet + 12, &value, sizeof(value));
        value = (uint16)(sint16)r_u16(rectangle + 6u);
        memcpy(packet + 14, &value, sizeof(value));
    }
    else
    {
        value = 640u;
        memcpy(packet + 12, &value, sizeof(value));
        value = 0u;
        memcpy(packet + 10, &value, sizeof(value));
        memcpy(packet + 8, &value, sizeof(value));
        value = 511u;
        memcpy(packet + 14, &value, sizeof(value));
    }
    guest_packet = xport_guest_buffer_address(packet, sizeof(packet));
    DrawPrim(psx_addr(guest_packet, sizeof(packet)));
    return;
}

void sub_800165CC(uint32 wait)
{
    uint32 module, value, index, environment;
    FUNCTION_MARKER(0x800165CCu, "SLUS_005.10");
    module = r_u32(0x800659C0u);
    if (module != 0u)
    {
        if (wait == 0u)
        {
            value = r_u32(module + 0x5DCCu);
            if (value == 0u)
            {
                do
                {
                    // Service native interrupts while awaiting the original callback flag
                    (void)VSync(-1);
                    value = r_u32(module + 0x5DCCu);
                    if (value != 0u)
                        break;
                } while (wait == 0u);
            }
        }
        module = r_u32(0x800659C0u);
        value = r_u32(module + 0x5DD0u);
        (void)VSyncCallbackPSX(value);
        index = r_u32(0x80065308u);
        environment = 0x8006F208u + 92u * (1u - index);
        (void)PutDrawEnv((DRAWENV *)psx_addr(environment, sizeof(DRAWENV)));
        module = r_u32(0x800659C0u);
        sub_80045088(module);
        w_u32(0x800659C0u, 0u);
        w_u8(0x8006F27Cu, 0u);
        w_u8(0x8006F220u, 0u);
    }
    return;
}

typedef struct V8_NATIVE_TIM_CONTEXT
{
    uint32 flags;
    uint32 bitmap;
    int palette_is_descriptor;
    union
    {
        uint32 guest_rectangle;
        uint8 *descriptor;
    } palette;
} V8_NATIVE_TIM_CONTEXT;

static void v8_native_18618(uint32 image, uint8 *tpage_out, uint8 *clut_out, uint8 *uv_out, uint8 *descriptor, V8_NATIVE_TIM_CONTEXT *context)
{
    uint32 palette = 0u, rectangle, flags, width, height, stored_width;
    uint32 pixels, bitmap, x, y, value, shift;
    sub_800185CC(0x8006F628u, image);
    rectangle = r_u32(0x8006F62Cu);
    if (rectangle != 0u)
    {
        flags = r_u32(0x8006F628u);
        if ((flags & 0x10u) != 0u)
        {
            width = (uint32)(sint32)(sint16)r_u16(rectangle + 4u);
            if ((sint32)width < 17)
                width = 16u;
            else
                width = 256u;
        }
        else
            width = (uint32)(sint32)(sint16)r_u16(rectangle + 4u);
        rectangle = r_u32(0x8006F62Cu);
        height = (uint32)(sint32)(sint16)r_u16(rectangle + 6u);
        stored_width = (uint32)(sint32)(sint16)r_u16(rectangle + 4u);
        palette = sub_80018124(width, height, 16u, 1u, stored_width, 1u);
        if (palette != 0u)
        {
            pixels = r_u32(0x8006F630u);
            LoadImagePSX((PSX_RECT *)psx_addr(palette, sizeof(PSX_RECT)), (uint32 *)psx_addr(pixels, 1u));
            if (clut_out != NULL)
            {
                x = (uint32)(sint32)(sint16)r_u16(palette);
                y = (uint32)(sint32)(sint16)r_u16(palette + 2u);
                value = GetClut((sint32)x, (sint32)y);
                xport_store_le16(clut_out, (uint16)value);
            }
        }
        else if (clut_out != NULL)
            xport_store_le16(clut_out, 0u);
    }
    else if (clut_out != NULL)
        xport_store_le16(clut_out, 0u);
    context->palette_is_descriptor = rectangle == 0u;
    if (context->palette_is_descriptor)
        context->palette.descriptor = descriptor;
    else
        context->palette.guest_rectangle = palette;
    rectangle = r_u32(0x8006F634u);
    flags = r_u32(0x8006F628u);
    width = (uint32)(sint32)(sint16)r_u16(rectangle + 4u);
    height = (uint32)(sint32)(sint16)r_u16(rectangle + 6u);
    stored_width = 64u << (flags & 3u);
    bitmap = sub_80018124(width, height, 64u, 256u, stored_width, 256u);
    if (bitmap != 0u)
    {
        pixels = r_u32(0x8006F638u);
        LoadImagePSX((PSX_RECT *)psx_addr(bitmap, sizeof(PSX_RECT)), (uint32 *)psx_addr(pixels, 1u));
    }
    if (!context->palette_is_descriptor)
        w_u32(0x8006F62Cu, context->palette.guest_rectangle);
    w_u32(0x8006F634u, bitmap);
    if (tpage_out != NULL)
    {
        x = (uint32)(sint32)(sint16)r_u16(bitmap);
        flags = r_u32(0x8006F628u);
        y = (uint32)(sint32)(sint16)r_u16(bitmap + 2u);
        value = GetTPage((sint32)(flags & 3u), 0, (sint32)x, (sint32)y);
        xport_store_le16(tpage_out, (uint16)value);
    }
    if (uv_out != NULL)
    {
        x = r_u16(bitmap);
        flags = r_u32(0x8006F628u);
        y = r_u8(bitmap + 2u);
        shift = (2u - (flags & 3u)) & 31u;
        value = ((x & 0x3Fu) << shift) | (y << 8);
        xport_store_le16(uv_out, (uint16)value);
    }
    context->flags = r_u32(0x8006F628u);
    context->bitmap = r_u32(0x8006F634u);
}

void v8_native_187E4(uint32 image, uint8 *output)
{
    V8_NATIVE_TIM_CONTEXT context;
    uint32 bitmap, flags, width, height, shift;
    v8_native_18618(image, output + 8u, output + 10u, output + 6u, output, &context);
    bitmap = context.bitmap;
    flags = context.flags;
    width = (uint32)(sint32)(sint16)r_u16(bitmap + 4u);
    shift = (2u - (flags & 3u)) & 31u;
    xport_store_le16(output + 2u, (uint16)(width << shift));
    bitmap = r_u32(0x8006F634u);
    height = r_u16(bitmap + 6u);
    xport_store_le16(output, 1u);
    xport_store_le16(output + 4u, (uint16)height);
}



uint32 v8_native_1884C(uint8 *descriptor)
{
    uint32 page, position, shift, x, y, clut;
    if (xport_load_le16(descriptor) == 0u)
        return 1u;
    page = xport_load_le16(descriptor + 8u);
    position = xport_load_le16(descriptor + 6u);
    shift = (2u - (page >> 7)) & 31u;
    clut = xport_load_le16(descriptor + 10u);
    x = ((page & 15u) << 6) + ((position & 255u) >> shift);
    y = ((page & 16u) << 4) + (position >> 8);
    if (clut != 0u)
        (void)sub_8001859C(clut);
    xport_store_le16(descriptor, 0u);
    return sub_80018530(x, y);
}

