#include "psx.h"
#include <stdio.h>
#include <stdlib.h>

uint32 v8_native_terrain_point_noop(uint32 target, uint32 event);

/* Unimplemented native callback transports fail at the named boundary */




uint32 v8_native_point_callback(uint32 target, uint32 object, uint32 event, const sint32 *point)
{
    if (v8_native_terrain_point_noop(target, event) != 0u)
        return 0u;
    fprintf(stderr, "Missing V8 point callback target=%08X object=%08X event=%08X\n", target, object, event);
    abort();
}
