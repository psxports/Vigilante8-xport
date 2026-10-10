#include "psx.h"
#include <stdio.h>
#include <stdlib.h>

uint32 v8_native_terrain_point_noop(uint32 target, uint32 event);

/* Unimplemented native callback transports fail at the named boundary */
uint32 xport_guest_call_known_registers(uint32 target, uint32 *registers, uint32 known_register_mask)
{
    fprintf(stderr, "Missing V8 native callback transport target=%08X mask=%08X\n", target, known_register_mask);
    abort();
}

uint32 xport_guest_call_known_registers_post_sdk(uint32 target, uint32 *registers, uint32 known_register_mask)
{
    return xport_guest_call_known_registers(target, registers, known_register_mask);
}

uint32 v8_native_point_callback(uint32 target, uint32 object, uint32 event, const sint32 *point)
{
    if (v8_native_terrain_point_noop(target, event) != 0u)
        return 0u;
    fprintf(stderr, "Missing V8 point callback target=%08X object=%08X event=%08X\n", target, object, event);
    abort();
}
