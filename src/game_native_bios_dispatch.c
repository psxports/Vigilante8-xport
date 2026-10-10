#include "psx.h"
#include "xport.h"
#include "xport_trace.h"
#include <stdio.h>
#include <stdlib.h>

void v8_native_16364(void);
void v8_native_12710(void);
uint32 sub_80011CCC(void);

static sint32 v8_native_bios_callback(void *context, uint32 address)
{
    switch (address)
    {
    case 0x80014FF0u:
        FUNCTION_MARKER(0x80014FF0u, "SLUS_005.10");
        w_u16(0x800102F2u, (uint16)(r_u16(0x800102F2u) + 1u));
        return 1;
    case 0x80011CCCu:
        (void)sub_80011CCC();
        return 1;
    case 0x80012710u:
        v8_native_12710();
        return 1;
    case 0x80016364u:
        v8_native_16364();
        return 1;
    default:
        fprintf(stderr, "V8: unsupported BIOS callback %08X\n", address);
        return 0;
    }
}

sint32 v8_native_dispatch_bios_callback(uint32 address)
{
    return v8_native_bios_callback(NULL, address);
}

void v8_native_bind_bios_callbacks(void)
{
    psx_bios_bind_guest_callback_service(v8_native_bios_callback, NULL);
    if (!psx_vblank_bind_native_counter(0x8005FFB4u))
        abort();
}
