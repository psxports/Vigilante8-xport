#include "psx.h"

void v8_native_shell_card_recovery_poll(uint32 module_base);

static void shell_cleanup_10FCC(uint32 module_base)
{
    sint32 critical;
    uint32 index;
    critical = EnterCriticalSectionPSX();
    for (index = 0u; index < 8u; ++index)
        (void)CloseEvent(r_u32(module_base + 0x13510u + 4u * index));
    if (critical == 1)
        ExitCriticalSection();
}

void v8_native_shell_EEFC(uint32 module_base)
{
    /* Advance native producers while preserving the original busy condition */
    while (r_u32(module_base + 0x13438u) != 0u)
        v8_native_shell_card_recovery_poll(module_base);
    (void)InterruptCallback(7, NULL);
    shell_cleanup_10FCC(module_base);
}
