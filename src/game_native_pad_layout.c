#include "psx.h"

void sub_80044F64(uint32 destination, uint32 count);
uint32 sub_800541AC(void);

uint32 v8_native_pad_init_direct(uint32 first_packet, uint32 second_packet)
{
    uint32 port, index, owner, packet;
    if (PadInitDirectPSX(first_packet, second_packet) == 0u)
        return 0u;
    w_u32(0x80065294u, 0u);
    w_u32(0x800652A8u, 0u);
    w_u32(0x80065274u, 0x80056268u);
    w_u32(0x80065278u, 0x8005667Cu);
    w_u32(0x8006527Cu, 0x8005633Cu);
    w_u32(0x8006525Cu, 0x80055D9Cu);
    w_u32(0x80065260u, 0x80055D34u);
    w_u32(0x80065264u, 0x80055EA0u);
    w_u32(0x80065268u, 0x80055F5Cu);
    w_u32(0x8006526Cu, 0x800561D8u);
    w_u32(0x80065270u, 0x80056210u);
    w_u32(0x80065290u, 0x800A4D28u);
    w_u32(0x80065280u, 0x80055E90u);
    sub_80044F64(0x800A4D28u, 480u);
    w_u32(0x800A4D58u, first_packet);
    w_u32(0x800A4E48u, second_packet);
    for (port = 0u; port < 2u; ++port)
    {
        owner = 0x800A4D28u + port * 240u;
        packet = r_u32(owner + 48u);
        w_u32(owner + 12u, 0u);
        w_u32(owner + 16u, owner);
        w_u8(packet, 0xFFu);
        packet = r_u32(owner + 48u);
        w_u8(packet + 1u, 0u);
        w_u32(owner + 60u, 0x800A4C98u + port * 35u);
        w_u32(owner + 64u, 0x800A4CE0u + port * 35u);
        for (index = 0u; index < 6u; ++index)
            w_u8(owner + 93u + index, 0xFFu);
    }
    (void)sub_800541AC();
    psx_pad_bind_owner_packets(0x800A4D28u, 0x800A4E18u);
    w_u32(0x80065294u, 1u);
    return 1u;
}
