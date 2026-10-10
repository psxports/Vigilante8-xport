#include "psx.h"
#include "xport.h"
#include "xport_trace.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

sint32 v8_native_load_boot_image(void)
{
    const char *path = "BOOT/SLUS_005.10";
    const size_t expected_size = 354304u;
    uint8 *image;
    size_t file_size, read_size;
    sint32 ok = 0;
    if (!xport_file_size(path, &file_size) || file_size != expected_size)
    {
        fprintf(stderr, "V8: boot image missing or has invalid size: %s\n", path);
        return 0;
    }
    image = (uint8 *)malloc(expected_size);
    if (image == NULL)
    {
        fprintf(stderr, "V8: cannot allocate boot image buffer\n");
        return 0;
    }
    if (!xport_file_read(path, image, expected_size, &read_size) || read_size != expected_size)
        fprintf(stderr, "V8: cannot read complete boot image: %s\n", path);
    else if (memcmp(image, "PS-X EXE", 8u) != 0 ||
             xport_load_le32(image + 0x10u) != 0x800116B4u ||
             xport_load_le32(image + 0x18u) != 0x80010000u ||
             xport_load_le32(image + 0x1Cu) != 352256u)
        fprintf(stderr, "V8: boot image header does not match SLUS_005.10\n");
    else if (!xport_guest_copy(xport_guest_ref(0x80010000u),
                              xport_host_ref(image + 2048u), 352256u))
        fprintf(stderr, "V8: cannot copy boot image payload to guest RAM\n");
    else
        ok = 1;
    free(image);
    return ok;
}
