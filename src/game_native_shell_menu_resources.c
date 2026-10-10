#include "psx.h"

static uint32 shell_progress_status(uint32 index)
{
    uint32 table = r_u32(0x8006590Cu);
    uint32 value = r_u8(0x80065950u + index);
    uint32 shift = r_u32(table + index * 8u + 4u) & 31u;
    uint32 threshold = 1u << shift;
    uint32 complete = (2u << shift) - 1u;
    uint32 result = value >= 2u ? 1u : 0u;
    result += (sint32)value >= (sint32)threshold ? 1u : 0u;
    result += value == complete ? 1u : 0u;
    return result;
}

uint32 v8_native_shell_12F8(uint32 module_base)
{
    uint32 result = 0u;
    uint32 flags;
    if (shell_progress_status(0u) != 3u || shell_progress_status(1u) != 3u)
        result |= 1u << 4;
    if (shell_progress_status(2u) != 3u || shell_progress_status(3u) != 3u)
        result |= 1u << 5;
    if (shell_progress_status(6u) != 3u || shell_progress_status(7u) != 3u)
        result |= 1u << 10;
    if (shell_progress_status(8u) != 3u || shell_progress_status(9u) != 3u)
        result |= 1u << 11;
    if (shell_progress_status(4u) != 3u || shell_progress_status(10u) != 3u)
        result |= 1u << 13;
    if (shell_progress_status(5u) != 3u || shell_progress_status(11u) != 3u)
        result |= 1u << 14;
    if ((result & 0x6000u) != 0u)
        result |= 0x1000u;
    flags = r_u32(0x80065908u);
    if ((flags & 0x40u) != 0u)
        result &= 0xFFFFF000u;
    if ((flags & 0x80u) != 0u)
        result &= 0xFFFFEFFFu;
    if ((flags & 0x100u) != 0u)
        result &= 0xFFFF9FFFu;
    if ((flags & 0x200u) != 0u)
        result = 0u;
    return result;
}
