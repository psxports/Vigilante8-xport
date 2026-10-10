#include "psx.h"
#include "xport_trace.h"

uint32 _bu_init(void);

static uint32 v8_shell_startup_1172C(uint32 module_base)
{ return r_u32(module_base + 0x13374u); }
static void v8_shell_startup_11490(uint32 module_base, uint32 mode)
{ (void)module_base; (void)xport_bios_init_card(mode); }
static void v8_shell_startup_1165C(uint32 module_base)
{
    uint32 source = module_base + 0x114C0u;
    uint32 end = module_base + 0x11530u;
    uint32 destination = 0xDF80u;
    uint32 word;
    do
    {
        word = r_u32(source);
        w_u32(destination, word);
        source += 4u;
        destination += 4u;
    } while (source != end);
}
/* Original BIOS table getters return the loaded kernel table addresses */
static uint32 v8_shell_GetC0Table(void)
{
    return 0x674u;
}
static uint32 v8_shell_GetB0Table(void)
{
    return 0x874u;
}

static void v8_shell_startup_11558(uint32 module_base)
{
    uint32 table, handler, high, low, destination, index;
    (void)xport_bios_enter_critical();
    table = v8_shell_GetC0Table();
    handler = r_u32(table + 24u);
    high = r_u32(handler + 0x70u);
    low = r_u32(handler + 0x74u);
    destination = ((high & 0xFFFFu) << 16) + (low & 0xFFFFu) + 0x28u;
    for (index = 0u; index < 5u; ++index)
        w_u32(destination + 4u * index, r_u32(module_base + 0x11530u + 4u * index));
    w_u32(0xDFFCu, destination + 20u);
    FlushCache();
}

static void v8_shell_startup_115EC(uint32 module_base)
{
    uint32 table, handler, destination, index;
    (void)xport_bios_enter_critical();
    table = v8_shell_GetB0Table();
    handler = r_u32(table + 0x16Cu);
    destination = handler + 0x9C8u;
    (void)r_u32(destination);
    for (index = 0u; index < 5u; ++index)
        w_u32(destination + 4u * index, r_u32(module_base + 0x11544u + 4u * index));
    FlushCache();
}

static void v8_shell_startup_114A0(uint32 module_base)
{ (void)module_base; (void)xport_bios_start_card(); }

static void v8_shell_startup_113C0(uint32 module_base, uint32 mode)
{
    (void)ChangeClearPAD(0u);
    (void)xport_bios_enter_critical();
    if (v8_shell_startup_1172C(module_base) == 0u)
        mode = 0u;
    v8_shell_startup_11490(module_base, mode);
    v8_shell_startup_1165C(module_base);
    v8_shell_startup_11558(module_base);
    v8_shell_startup_115EC(module_base);
    xport_bios_exit_critical();
}

static void v8_shell_startup_1142C(uint32 module_base)
{
    (void)xport_bios_enter_critical();
    v8_shell_startup_114A0(module_base);
    (void)ChangeClearPAD(0u);
    xport_bios_exit_critical();
}

static uint32 v8_shell_startup_113B0(uint32 module_base)
{
    return _bu_init();
}

static uint32 v8_shell_startup_10DA0(uint32 module_base, uint32 mode)
{
    (void)v8_shell_startup_113C0(module_base, mode);
    (void)v8_shell_startup_1142C(module_base);
    return v8_shell_startup_113B0(module_base);
}

uint32 v8_native_shell_EE60(uint32 module_base, uint32 mode)
{
    w_u32(module_base + 0x13434u, 0u);
    w_u32(module_base + 0x13478u, 0u);
    return v8_shell_startup_10DA0(module_base, mode);
}
