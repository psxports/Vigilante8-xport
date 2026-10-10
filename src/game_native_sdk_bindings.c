#include "psx.h"
#include "xport.h"

uint32 sub_80046C94(uint32 voice, uint32 pitch)
{
    SpuSetVoicePitch((sint32)voice, (uint16)pitch);
    return 0u;
}

uint32 sub_80046C14(uint32 voice, sint32 left, sint32 right)
{
    SpuSetVoiceVolume((sint32)voice, (sint16)((uint32)left & 0x7FFFu), (sint16)((uint32)right & 0x7FFFu));
    return 0u;
}

uint32 sub_80046D04(uint32 voice, uint32 address)
{
    SpuSetVoiceStartAddr((sint32)voice, address);
    return 0u;
}

uint32 sub_8004C934(uint32 matrix, uint32 destination)
{
    PsxGteSnapshot saved;
    VECTOR rows[3];
    SVECTOR normalized;
    uint32 i, result;
    sint32 first[3], second[3];
    psx_gte_snapshot(&saved);
    for (i = 0u; i < 3u; ++i)
    {
        first[i] = (sint16)r_u16(matrix + 2u * i);
        second[i] = (sint16)r_u16(matrix + 6u + 2u * i);
    }
    xport_gte_write_control(0u, (uint32)first[0]);
    xport_gte_write_control(2u, (uint32)first[1]);
    xport_gte_write_control(4u, (uint32)first[2]);
    for (i = 0u; i < 3u; ++i)
        xport_gte_write_data(9u + i, (uint32)second[i]);
    xport_gte_execute(0x4B78000Cu);
    rows[2].vx = (sint32)xport_gte_read_data(25u);
    rows[2].vy = (sint32)xport_gte_read_data(26u);
    rows[2].vz = (sint32)xport_gte_read_data(27u);
    xport_gte_write_control(0u, (uint32)second[0]);
    xport_gte_write_control(2u, (uint32)second[1]);
    xport_gte_write_control(4u, (uint32)second[2]);
    xport_gte_execute(0x4B78000Cu);
    rows[0].vx = (sint32)xport_gte_read_data(25u);
    rows[0].vy = (sint32)xport_gte_read_data(26u);
    rows[0].vz = (sint32)xport_gte_read_data(27u);
    xport_gte_write_data(0u, (uint32)second[0]);
    xport_gte_write_data(1u, (uint32)second[1]);
    xport_gte_write_data(2u, (uint32)second[2]);
    xport_gte_write_control(0u, (uint16)saved.rotation.m[0][0] | ((uint32)(uint16)saved.rotation.m[0][1] << 16));
    xport_gte_write_control(2u, (uint16)saved.rotation.m[1][1] | ((uint32)(uint16)saved.rotation.m[1][2] << 16));
    xport_gte_write_control(4u, (uint32)(sint32)saved.rotation.m[2][2]);
    rows[1].vx = second[0];
    rows[1].vy = second[1];
    rows[1].vz = second[2];
    result = 0u;
    for (i = 0u; i < 3u; ++i)
    {
        /* Native VectorNormalS defines zero-vector behavior */
        result = (uint32)VectorNormalS(&rows[i], &normalized);
        w_u16(destination + 6u * i, (uint16)normalized.vx);
        w_u16(destination + 6u * i + 2u, (uint16)normalized.vy);
        w_u16(destination + 6u * i + 4u, (uint16)normalized.vz);
    }
    return result;
}
