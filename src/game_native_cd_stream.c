#include "psx.h"
#include "xport.h"
#include <stdio.h>
#include <stdlib.h>

extern const uint32 xport_cd_ready_callback_address;
uint32 sub_80015644(uint32 status);
CdlLOC *CdIntToPos(sint32 sector, CdlLOC *position);

static void v8_native_cd_ready_dispatch(uint8 status, uint8 *result)
{
    uint32 target = r_u32(xport_cd_ready_callback_address);
    if (target == 0u)
        return;
    if (target == 0x80015644u)
    {
        (void)sub_80015644(status);
        return;
    }
    fprintf(stderr, "Unsupported native CD ready callback %08X\n", target);
    abort();
}

uint32 v8_native_cd_ready_register(uint32 guest_callback)
{
    uint32 previous = CdReadyCallbackPSX(guest_callback);
    CdReadyCallback(guest_callback != 0u ? v8_native_cd_ready_dispatch : NULL);
    return previous;
}

sint32 v8_native_cd_stream_start(CdlLOC *position)
{
    return CdControl(2u, (uint8 *)position, NULL);
}

void v8_native_cd_stream_pump(void)
{
    CdlLOC position;
    uint32 producer = r_u32(0x800659ACu);
    uint32 consumer = r_u32(0x800659A8u);
    uint32 base, sector;
    if (producer != consumer)
        return;
    sector = r_u32(0x800659B4u);
    CdIntToPos((sint32)sector, &position);
    if (CdControl(2u, (uint8 *)&position, NULL) == 0 ||
        CdGetSector(psx_addr(producer, 2048u), 512) == 0)
    {
        fprintf(stderr, "Native CD stream read failed at sector %u, destination %08X\n", sector, producer);
        abort();
    }
    base = r_u32(0x800659A4u);
    producer = r_u32(0x800659ACu);
    if (producer == base)
        base += 2048u;
    sector = r_u32(0x800659B4u);
    w_u32(0x800659ACu, base);
    w_u32(0x800659B4u, sector + 1u);
}

sint32 sub_80043BB4(void)
{
    uint8 result[8];
    FUNCTION_MARKER(0x80043BB4u, "SLUS_005.10");
    (void)CdControlB(1u, NULL, result);
    return (result[0] >> 4u) & 1u;
}
