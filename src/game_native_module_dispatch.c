#include "psx.h"
#include <stdio.h>
#include <stdlib.h>

uint32 v8_native_shell_entry(uint32 module_base);
void v8_native_load_167C(uint32 base, const char *filename, uint32 text, uint32 flags);
uint32 v8_native_terrain_call3(uint32 callback, uint32 object, uint32 mode, uint32 value);

uint32 v8_native_module_entry0(uint32 module)
{
    uint32 target = r_u32(module + 4u);
    if (target == module + 0xC784u)
        return v8_native_shell_entry(module);
    fprintf(stderr, "Unsupported V8 native module entry %08X at module %08X\n", target, module);
    abort();
}

void v8_native_module_entry3(uint32 module, const char *filename, uint32 text, uint32 flags)
{
    uint32 target = r_u32(module + 4u);
    if (target == module + 0x167Cu)
    {
        v8_native_load_167C(module, filename, text, flags);
        return;
    }
    fprintf(stderr, "TODO V8 native module entry3 %08X at module %08X offset %08X\n", target, module, target - module);
    abort();
}

void v8_native_level_callback3(uint32 callback, uint32 object, uint32 mode, uint32 value)
{
    (void)v8_native_terrain_call3(callback, object, mode, value);
}
