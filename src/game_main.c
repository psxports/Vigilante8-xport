#include "psx.h"
#include "xport.h"
#include "xport_trace.h"

/* Unresolved until the original PsyQ graph type storage is audited */
const uint32 xport_gpu_graph_type_address = 0x80064FC4u;

extern sint32 sub_80015098(void);

sint32 sub_800116B4(void)
{
    uint32 address = 0x800658D8u;
    uint32 previous_address;

    FUNCTION_MARKER(0x800116B4u, "SLUS_005.10");
    do
    {
        w_u32(address, 0u);
        previous_address = address;
        address += 4u;
    } while (previous_address < 0x800A4F10u);
    return sub_80015098();
}

void xport_main(void)
{
    sub_800116B4();
}

uint32 sub_80044FBC(uint32 base, uint32 bytes);
uint32 sub_80045004(uint32 bytes);
uint32 sub_800116F4(uint32 bytes);
uint32 sub_8001178C(uint32 count, uint32 size);
sint32 sub_80049534(uint32 position);
void nullsub_2(void);
uint32 sub_800451C0(uint32 count, uint32 size);
uint32 sub_80011914(uint32 value);
void sub_800165CC(uint32 wait);
uint32 sub_80020D3C(void);
uint32 sub_80015E8C(void);
uint8 *sub_800154F4(uint8 *destination, sint32 sector, sint32 count);
uint32 sub_80015C68(uint32 directory, uint32 sector, uint32 bytes);
sint32 sub_8001570C(sint32 sector);
uint32 sub_800156D4(void);
void sub_80015798(void);
sint32 CdInit(void);
CdlLOC *CdIntToPos(sint32 sector, CdlLOC *position);
sint32 CdRead(sint32 count, uint32 *destination, sint32 mode);
sint32 CdReadSync(sint32 mode, uint8 *result);
uint32 xport_cd_ready_guest_callback(uint32 guest_callback);
uint32 sub_80044EFC(uint32 destination, uint32 value, uint32 count);
uint32 sub_80044C44(uint32 destination, uint32 source, uint32 count);
uint32 sub_80045134(uint32 address, uint32 size);
sint32 sub_800495B4(void);
sint32 sub_8004AD14(uint32 reason, uint32 response);
sint32 sub_800493AC(uint32 destination, uint32 word_count);
sint32 sub_800493CC(uint32 destination, uint32 word_count);
sint32 CdDataSync(sint32 mode);
uint32 xport_cd_data_guest_callback(uint32 guest_callback);
uint32 xport_cd_sync_guest_callback(uint32 guest_callback);
uint32 xport_guest_buffer_address(void *host_buffer, size_t bytes);
sint32 xport_guest_call2(uint32 guest_target, uint32 argument0, uint32 argument1);
sint32 CD_getsector(uint32 guest_destination, uint32 words);
#include <stdlib.h>
void sub_8001714C(uint32 counter);
uint32 sub_80053A24(void);
void sub_80053A34(void);
sint32 OpenEvent(uint32 event_class, uint32 specification, uint32 mode, uint32 guest_callback);
sint32 EnableEvent(uint32 handle);
uint32 sub_80013CAC(void);
sint32 GetRCnt(sint32 counter);
void _boot(void);

sint32 sub_80015098(void)
{
    uint32 counter;
    uint32 event;
    uint32 heap = 0x800A4F18u;
    uint32 bytes;

    FUNCTION_MARKER(0x80015098u, "SLUS_005.10");
    nullsub_2();
    bytes = (0x80200000u - heap - r_u32(0x80065304u)) & 0xFFFFFFF8u;
    sub_80044FBC(heap, bytes);
    sub_80015E8C();
    ResetGraph(0);
    SetGraphDebug(0);
    InitGeom();
    counter = (uint32)GetRCnt((sint32)0xF2000002u);
    sub_8001714C(counter);
    SetRCnt(0xF2000002u, (uint16)0xFFFFFFFFu, 0x1000u);
    sub_80053A24();
    event = (uint32)OpenEvent(0xF2000002u, 2u, 0x1000u, 0x80014FF0u);
    EnableEvent(event);
    sub_80053A34();
    sub_80013CAC();
    return 0;
}

void nullsub_2(void)
{
    FUNCTION_MARKER(0x800116ECu, "SLUS_005.10");
    return;
}

uint32 sub_80044FBC(uint32 base, uint32 bytes)
{
    uint32 aligned, tail, units;
    FUNCTION_MARKER(0x80044FBCu, "SLUS_005.10");
    if (base == 0u || bytes == 0u)
        return 0xFFFFFFF8u;
    aligned = bytes & 0xFFFFFFF8u;
    tail = base + aligned;
    w_u32(tail - 8u, base);
    w_u32(tail - 4u, 0u);
    w_u32(base, tail - 8u);
    units = (aligned >> 3) - 1u;
    w_u32(0x8005ED4Cu, base);
    w_u32(0x8005ED50u, base);
    w_u32(base + 4u, units);
    return units;
}

uint32 sub_80015E8C(void)
{
    uint32 sector_words[512];
    uint8 *buffer = (uint8 *)sector_words;
    uint32 sector;
    uint32 bytes;
    uint32 directory;
    FUNCTION_MARKER(0x80015E8Cu, "SLUS_005.10");
    CdInit();
    sub_800154F4(buffer, 16, 1);
    w_u32(0x8006F608u, xport_load_le32(buffer + 0x28u));
    w_u32(0x8006F60Cu, xport_load_le32(buffer + 0x2Cu));
    w_u32(0x8006F610u, xport_load_le32(buffer + 0x30u));
    w_u32(0x8006F614u, xport_load_le32(buffer + 0x34u));
    w_u32(0x8006F618u, xport_load_le32(buffer + 0x38u));
    w_u32(0x8006F61Cu, xport_load_le32(buffer + 0x3Cu));
    w_u32(0x8006F620u, xport_load_le32(buffer + 0x40u));
    w_u32(0x8006F624u, xport_load_le32(buffer + 0x44u));
    bytes = xport_load_le32(buffer + 0xA6u);
    sector = xport_load_le32(buffer + 0x9Eu);
    directory = sub_800116F4(0x514u);
    directory = sub_80015C68(directory, sector, bytes);
    w_u32(0x800659B8u, directory);
    return directory;
}

void sub_80053A34(void)
{
    FUNCTION_MARKER(0x80053A34u, "SLUS_005.10");
    /* User-authorized stub for the absent BIOS syscall service */
    abort();
}

sint32 sub_800495B4(void)
{
    uint8 response[8];
    uint32 reason, flags = 0u, count = 0u, i;
    uint32 result, destination;

    FUNCTION_MARKER(0x800495B4u, "SLUS_005.10");
    w_u8(r_u32(0x80060344u), 1u);
    reason = r_u8(r_u32(0x80060350u)) & 7u;
    if (reason == 0u)
        return 0;
    while (reason != (r_u8(r_u32(0x80060350u)) & 7u))
        reason = r_u8(r_u32(0x80060350u)) & 7u;
    while (count < 8u && (r_u8(r_u32(0x80060344u)) & 0x20u) != 0u)
        response[count++] = r_u8(r_u32(0x80060348u));
    for (i = count; i < 8u; ++i)
        response[i] = 0u;
    w_u8(r_u32(0x80060344u), 1u);
    w_u8(r_u32(0x80060350u), 7u);
    w_u8(r_u32(0x8006034Cu), 7u);
    if (reason != 3u || r_u32(0x80060244u + 4u * r_u8(0x8006009Du)) != 0u)
    {
        if ((r_u32(0x8006008Cu) & 0x10u) == 0u && (response[0] & 0x10u) != 0u)
            w_u32(0x80060094u, r_u32(0x80060094u) + 1u);
        flags = response[0] & 0x1Du;
        w_u32(0x8006008Cu, response[0]);
        w_u32(0x80060090u, response[1]);
    }
    if (reason == 5u && (sint32)r_u32(0x80060088u) > 0)
    {
        printf("%s", (const char *)psx_addr(0x80010FECu, 1u));
        if ((sint32)r_u32(0x80060088u) > 0)
            printf((const char *)psx_addr(0x80010FF8u, 1u),
                (const char *)psx_addr(r_u32(0x800600A4u + 4u * r_u8(0x8006009Du)), 1u),
                r_u32(0x8006008Cu), r_u32(0x80060090u));
    }
    switch (reason)
    {
    case 1u:
        if (flags != 0u && count == 1u)
            flags = 0u;
        w_u8(0x8006035Du, flags != 0u ? 5u : 1u);
        for (i = 0u; i < 8u; ++i)
            w_u8(0x800A3248u + i, response[i]);
        w_u8(r_u32(0x80060344u), 0u);
        w_u8(r_u32(0x80060350u), 0u);
        return 4;
    case 2u:
        w_u8(0x8006035Cu, flags != 0u ? 5u : 2u);
        destination = 0x800A3240u;
        result = 2u;
        break;
    case 3u:
        if (flags != 0u)
        {
            w_u8(0x8006035Cu, 5u);
            result = 2u;
        }
        else if (r_u32(0x80060144u + 4u * r_u8(0x8006009Du)) != 0u)
        {
            w_u8(0x8006035Cu, 3u);
            result = 1u;
        }
        else
        {
            w_u8(0x8006035Cu, 2u);
            result = 2u;
        }
        destination = 0x800A3240u;
        break;
    case 4u:
        w_u8(0x8006035Eu, 4u);
        w_u8(0x8006035Du, r_u8(0x8006035Eu));
        for (i = 0u; i < 8u; ++i)
            w_u8(0x800A3250u + i, response[i]);
        destination = 0x800A3248u;
        result = 4u;
        break;
    case 5u:
        w_u8(0x8006035Du, 5u);
        w_u8(0x8006035Cu, r_u8(0x8006035Du));
        for (i = 0u; i < 8u; ++i)
            w_u8(0x800A3240u + i, response[i]);
        destination = 0x800A3248u;
        result = 6u;
        break;
    default:
        puts((const char *)psx_addr(0x80011014u, 1u));
        printf((const char *)psx_addr(0x80011028u, 1u), reason);
        return 0;
    }
    for (i = 0u; i < 8u; ++i)
        w_u8(destination + i, response[i]);
    return (sint32)result;
}

uint8 *sub_800154F4(uint8 *destination, sint32 sector, sint32 count)
{
    CdlLOC position;
    FUNCTION_MARKER(0x800154F4u, "SLUS_005.10");
    CdIntToPos(sector, &position);
    CdControl(0x15u, (uint8 *)&position, NULL);
    CdRead(count, (uint32 *)destination, 0x80);
    CdReadSync(0, NULL);
    return destination;
}

sint32 sub_80049534(uint32 position)
{
    uint32 minute, second, frame;
    FUNCTION_MARKER(0x80049534u, "SLUS_005.10");
    minute = r_u8(position);
    second = r_u8(position + 1u);
    minute = 10u * (minute >> 4) + (minute & 15u);
    second = 10u * (second >> 4) + (second & 15u);
    frame = r_u8(position + 2u);
    frame = 10u * (frame >> 4) + (frame & 15u);
    return (sint32)(75u * (60u * minute + second) + frame) - 150;
}

sint32 sub_8004AD14(uint32 reason, uint32 response)
{
    uint8 sector[16];
    uint32 position;
    uint32 callback;
    sint32 result;
    uint32 finish;

    FUNCTION_MARKER(0x8004AD14u, "SLUS_005.10");
    w_u32(0x800603CCu, response);
    if ((reason & 0xFFu) != 1u)
        w_u32(0x800603ACu, 0xFFFFFFFFu);
    else if ((sint32)r_u32(0x800603ACu) > 0)
    {
        if (r_u32(0x800603A8u) == 512u)
        {
            position = xport_guest_buffer_address(sector, sizeof(sector));
            if ((r_u32(0x800603C8u) & 1u) != 0u)
            {
                xport_cd_data_guest_callback(0u);
                sub_800493CC(position, 3u);
                CdDataSync(0);
                xport_cd_data_guest_callback(0x8004AF74u);
            }
            else
                sub_800493AC(position, 3u);
            if ((uint32)sub_80049534(position) != r_u32(0x800603B8u))
            {
                puts((const char *)psx_addr(0x800110D4u, 1u));
                w_u32(0x800603ACu, 0xFFFFFFFFu);
            }
        }
        if ((r_u32(0x800603C8u) & 1u) != 0u)
            sub_800493CC(r_u32(0x800603A0u), r_u32(0x800603A8u));
        else
        {
            sub_800493AC(r_u32(0x800603A0u), r_u32(0x800603A8u));
            w_u32(0x800603A0u, r_u32(0x800603A0u) + (r_u32(0x800603A8u) << 2));
            w_u32(0x800603ACu, r_u32(0x800603ACu) - 1u);
            w_u32(0x800603B8u, r_u32(0x800603B8u) + 1u);
        }
    }
    w_u32(0x800603B0u, (uint32)sub_80047E44(-1));
    if ((sint32)r_u32(0x800603ACu) < 0)
        sub_8004B040(1u);
    result = sub_80047E44(-1);
    if ((sint32)(r_u32(0x800603B4u) + 1200u) < result)
        w_u32(0x800603ACu, 0xFFFFFFFFu);
    result = (sint32)r_u32(0x800603ACu);
    finish = result == 0;
    if (!finish)
    {
        result = sub_80047E44(-1);
        finish = (sint32)(r_u32(0x800603B4u) + 1200u) < result;
    }
    if (finish)
    {
        xport_cd_sync_guest_callback(r_u32(0x800603BCu));
        xport_cd_ready_guest_callback(r_u32(0x800603C0u));
        if ((r_u32(0x800603C8u) & 1u) != 0u)
            xport_cd_data_guest_callback(r_u32(0x800603C4u));
        result = sub_8004910C(9u, 0u);
        callback = r_u32(0x80060394u);
        if (callback != 0u)
            result = xport_guest_call2(callback, r_u32(0x800603ACu) == 0u ? 2u : 5u, response);
    }
    return result;
}

sint32 sub_800493AC(uint32 destination, uint32 word_count)
{
    FUNCTION_MARKER(0x800493ACu, "SLUS_005.10");
    return CD_getsector(destination, word_count) == 0;
}

uint32 sub_800116F4(uint32 bytes)
{
    uint32 result;
    FUNCTION_MARKER(0x800116F4u, "SLUS_005.10");
    result = sub_80045004(bytes);
    if (result != 0u || bytes == 0u)
        return result;
    DrawSync(0);
    sub_80011914(1u - r_u32(0x80065308u));
    sub_800165CC(1u);
    for (;;)
    {
        result = sub_80045004(bytes);
        if (result != 0u)
            return result;
        if (sub_80020D3C() == 0u)
        {
            _boot();
            return result;
        }
    }
}

uint32 sub_80045004(uint32 bytes)
{
    uint32 units, previous, first, block, remaining, next;
    FUNCTION_MARKER(0x80045004u, "SLUS_005.10");
    units = (bytes + 15u) >> 3;
    if (bytes == 0u)
        return 0u;
    previous = r_u32(0x8005ED4Cu);
    first = previous;
    for (;;)
    {
        block = r_u32(previous);
        remaining = r_u32(block + 4u) - units;
        if ((remaining & 0x80000000u) == 0u)
        {
            if (remaining == 0u)
            {
                next = r_u32(block);
                w_u32(0x8005ED4Cu, previous);
                w_u32(previous, next);
                return block + 8u;
            }
            w_u32(block + 4u, remaining);
            block += remaining << 3;
            w_u32(block + 4u, units);
            w_u32(0x8005ED4Cu, previous);
            return block + 8u;
        }
        previous = block;
        if (block == first)
            return 0u;
    }
}

uint32 sub_80015C68(uint32 directory, uint32 sector, uint32 remaining)
{
    uint32 record;
    uint32 entry;
    uint32 child;
    uint32 count;
    uint32 copied;
    uint32 length;
    uint32 character;
    FUNCTION_MARKER(0x80015C68u, "SLUS_005.10");
    sub_8001570C((sint32)sector);
    w_u32(directory + 0x10u, 0u);
    w_u32(directory + 8u, 0u);
    while (remaining != 0u)
    {
        record = sub_800156D4();
        while (r_u8(record) != 0u)
        {
            if ((r_u8(record + 0x19u) & 2u) != 0u)
            {
                if (r_u8(record + 0x21u) >= 2u)
                {
                    child = sub_800116F4(0x514u);
                    sub_80044EFC(child, 0x20u, 8u);
                    length = r_u8(record + 0x20u);
                    if (length >= 8u)
                        length = 8u;
                    sub_80044C44(child, record + 0x21u, length);
                    w_u32(child + 0x20u, r_u32(record + 2u));
                    w_u32(child + 0x24u, r_u32(record + 0x0Au));
                    w_u32(child + 0x0Cu, r_u32(directory + 8u));
                    w_u32(directory + 8u, child);
                }
            }
            else
            {
                count = r_u32(directory + 0x10u);
                entry = directory + count * 20u + 20u;
                w_u32(directory + 0x10u, count + 1u);
                copied = 0u;
                do
                {
                    character = r_u8(record + copied + 0x21u);
                    if (character == 0x3Bu)
                        break;
                    w_u8(entry + copied, character);
                    copied += 1u;
                } while (copied < 12u);
                while (copied < 12u)
                {
                    w_u8(entry + copied, 0x20u);
                    copied += 1u;
                }
                w_u32(entry + 12u, r_u32(record + 2u));
                w_u32(entry + 16u, r_u32(record + 0x0Au));
            }
            record += r_u8(record);
        }
        remaining -= 0x800u;
    }
    sub_80015798();
    directory = sub_80045134(directory, r_u32(directory + 0x10u) * 20u + 20u);
    child = r_u32(directory + 8u);
    while (child != 0u)
    {
        sub_80015C68(child, r_u32(child + 0x20u), r_u32(child + 0x24u));
        child = r_u32(child + 12u);
    }
    return directory;
}

sint32 sub_8001570C(sint32 sector)
{
    CdlLOC position;
    uint8 mode[4];
    uint32 initial_buffer;
    uint32 observed_buffer;
    FUNCTION_MARKER(0x8001570Cu, "SLUS_005.10");
    w_u32(0x800659B4u, (uint32)sector);
    xport_store_le32(mode, r_u32(0x8006565Cu));
    xport_cd_ready_guest_callback(0x80015644u);
    initial_buffer = sub_8001178C(0x800u, 2u);
    w_u32(0x800659ACu, initial_buffer);
    observed_buffer = r_u32(0x800659ACu);
    w_u32(0x800659A4u, initial_buffer);
    w_u32(0x800659A8u, observed_buffer);
    CdControl(0x0Eu, mode, NULL);
    CdIntToPos((sint32)r_u32(0x800659B4u), &position);
    return CdControl(0x06u, (uint8 *)&position, NULL);
}

uint32 sub_8001178C(uint32 count, uint32 size)
{
    uint32 result;
    FUNCTION_MARKER(0x8001178Cu, "SLUS_005.10");
    result = sub_800451C0(count, size);
    if (result != 0u || count == 0u)
        return result;
    DrawSync(0);
    sub_80011914(1u - r_u32(0x80065308u));
    sub_800165CC(1u);
    for (;;)
    {
        result = sub_800451C0(count, size);
        if (result != 0u)
            return result;
        if (sub_80020D3C() == 0u)
        {
            _boot();
            return result;
        }
    }
}

uint32 sub_800451C0(uint32 count, uint32 size);
uint32 sub_80044EFC(uint32 destination, uint32 value, uint32 count);
uint32 sub_80044C44(uint32 destination, uint32 source, uint32 count);
void sub_80045088(uint32 address);
uint32 sub_80045134(uint32 address, uint32 size);
uint32 sub_80045354(void);
uint32 sub_80044D9C(uint32 destination, uint32 source, uint32 count);
uint32 _SpuInit(uint32 mode);
uint32 sub_80045004(uint32 size);
void xport_mips_overflow_exception(uint32 pc);
uint32 sub_800156D4(void);
uint32 sub_80015644(uint32 status);
void sub_80015798(void);
sint32 sub_8004938C(uint32 volume);
sint32 sub_80043EF0(void);
sint32 sub_800493AC(uint32 destination,uint32 word_count);
uint32 sub_80044080(uint32 enabled, uint32 volume, uint32 setting);
uint32 sub_80043A74(void);
sint32 CD_vol(CdlATV *volume);
uint32 SpuInitMalloc(uint32 count, uint32 table);
sint32 sub_8004F1E8(void);
void sub_8001714C(uint32 counter);
uint32 sub_80047674(uint32 left, uint32 right);
#include <stdlib.h>
uint32 sub_80053A24(void);
char *strcpy(char *destination, const char *source);
uint32 sub_80013CAC(void);
uint32 xport_guest_call0(uint32 target);
uint32 xport_guest_buffer_address(void *host_buffer, size_t bytes);
sint32 MargePrim(uint32 first, uint32 second);
uint32 sub_80011834(void);
uint32 sub_800128D4(void);
uint32 sub_800251FC(uint32 mode);
uint32 sub_80011ADC(uint32 path);
void sub_80029DEC(void);
void sub_800227A4(uint32 mask);
uint32 sub_80044360(uint32 path);
uint32 sub_80015F80(uint32 path);
void sub_800165CC(uint32 wait);
void sub_80017FD4(uint32 value);
uint32 sub_80019034(uint32 asset, uint32 size);
void sub_8001910C(uint32 font);
void sub_8002A598(void);
void sub_80022BA8(uint32 message, uint32 text, uint32 flags);
void sub_80012980(void);
void sub_800212C4(uint32 counter);
void sub_8001A0AC(uint32 text, uint32 flags);
void sub_80019960(uint32 font, uint32 text, uint32 x, uint32 y);
void sub_800126F0(void);
sint32 sub_80043BB4(void);
uint32 sub_80012A90(uint32 font, uint32 player);
uint32 sub_800120D4(void);
void sub_8002131C(uint32 ticks);
void sub_80021394(uint32 counter);
void sub_80021678(void);
void sub_8001D994(uint32 width, uint32 height, uint32 center_x, uint32 center_y);
uint32 sub_800119C0(uint32 index);
void sub_8001DB24(uint32 object, sint32 height);
void sub_80021600(void);
uint32 sub_80019D10(uint32 message, uint32 font, uint32 ordering, uint32 ticks);
void sub_80018F7C(uint32 overlay, uint32 ordering);
void sub_80043DF8(uint32 path, sint32 character);
uint32 sub_8001392C(uint32 font);
void sub_8002AF98(uint32 player, uint32 view, uint32 ordering);
void sub_8002B7BC(uint32 player, uint32 matrix, uint32 ordering);
void sub_8002A25C(sint32 x, sint32 y, uint32 ordering);
void sub_80012828(uint32 display, uint32 draw, uint32 ordering, uint32 end);
void sub_800128BC(void);
void sub_8002B8D0(uint32 player);
void sub_80019C64(uint32 font, uint32 text, uint32 width, uint32 rows, uint32 ordering);
uint32 sub_800220D4(void);
void sub_80018F3C(uint32 overlay);
void sub_8001265C(void);
uint32 sub_80011C58(uint32 source);
void sub_800126C8(void);
void sub_80044054(void);
void sub_80044394(uint32 sound);
void sub_80022A1C(void);
void sub_800204DC(uint32 object);
void sub_8002ACCC(void);
void sub_80041E80(void);
void sub_8001356C(uint32 font);
uint32 sub_800190D8(uint32 object);
uint32 sub_80011914(uint32 value);
void sub_80016678(uint32 value);

uint32 sub_800451C0(uint32 count, uint32 size)
{
    uint32 checked_result;
    uint32 bytes = count * size;
    uint32 result, cursor;
    FUNCTION_MARKER(0x800451C0u, "SLUS_005.10");
    result = sub_80045004(bytes);
    cursor = result;
    if (result != 0u)
    {
        do
        {
            w_u32(cursor, 0u);
            w_u32(cursor + 4u, 0u);
            checked_result = bytes + 0xFFFFFFF8u;
            if ((((bytes ^ checked_result) & (0xFFFFFFF8u ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x800451E4u);
            bytes = checked_result;
            checked_result = cursor + 8u;
            if ((((cursor ^ checked_result) & (8u ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x800451ECu);
            cursor = checked_result;
        } while ((sint32)bytes > 0);
    }
    return result;
}

uint32 sub_800156D4(void)
{
    uint32 previous;
    uint32 ready;
    FUNCTION_MARKER(0x800156D4u, "SLUS_005.10");
    previous = r_u32(0x800659A8u);
    ready = r_u32(0x800659ACu);
    if (ready == previous)
    {
        do
        {
            ready = r_u32(0x800659ACu);
        } while (ready == previous);
    }
    w_u32(0x800659A8u, r_u32(0x800659ACu));
    return previous;
}

uint32 sub_80015644(uint32 status)
{
    CdlLOC position;
    uint32 result = 1u;
    uint32 producer;
    uint32 consumer;
    uint32 base;
    uint32 sector;
    FUNCTION_MARKER(0x80015644u, "SLUS_005.10");
    if ((status & 0xFFu) == 1u)
    {
        producer = r_u32(0x800659ACu);
        consumer = r_u32(0x800659A8u);
        if (producer != consumer)
        {
            CdIntToPos((sint32)r_u32(0x800659B4u), &position);
            result = (uint32)CdControl(6u, (uint8 *)&position, NULL);
        }
        else
        {
            sub_800493AC(r_u32(0x800659ACu), 512u);
            base = r_u32(0x800659A4u);
            producer = r_u32(0x800659ACu);
            if (producer == base)
                base += 2048u;
            sector = r_u32(0x800659B4u);
            w_u32(0x800659ACu, base);
            result = sector + 1u;
            w_u32(0x800659B4u, result);
        }
    }
    return result;
}

uint32 sub_80044EFC(uint32 destination, uint32 value, uint32 count)
{
    uint32 checked_result;
    uint32 original = destination;
    uint32 remaining, fill, end, offset;
    FUNCTION_MARKER(0x80044EFCu, "SLUS_005.10");
    if (count == 0u)
        return original;
    value &= 0xFFu;
    while ((destination & 3u) != 0u)
    {
        w_u8(destination, value);
        checked_result = count + 0xFFFFFFFFu;
        if ((((count ^ checked_result) & (0xFFFFFFFFu ^ checked_result)) & 0x80000000u) != 0u)
            xport_mips_overflow_exception(0x80044F14u);
        count = checked_result;
        checked_result = destination + 1u;
        if ((((destination ^ checked_result) & (1u ^ checked_result)) & 0x80000000u) != 0u)
            xport_mips_overflow_exception(0x80044F1Cu);
        destination = checked_result;
        if (count == 0u)
            return original;
    }
    fill = value | (value << 8);
    fill |= fill << 16;
    remaining = count - 4u;
    if ((sint32)remaining >= 0)
    {
        do
        {
            w_u32(destination, fill);
            checked_result = remaining + 0xFFFFFFFCu;
            if ((((remaining ^ checked_result) & (0xFFFFFFFCu ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044F44u);
            remaining = checked_result;
            checked_result = destination + 4u;
            if ((((destination ^ checked_result) & (4u ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044F4Cu);
            destination = checked_result;
        } while ((sint32)remaining >= 0);
    }
    remaining += 3u;
    checked_result = destination + remaining;
    if ((((destination ^ checked_result) & (remaining ^ checked_result)) & 0x80000000u) != 0u)
        xport_mips_overflow_exception(0x80044F58u);
    end = checked_result;
    if ((sint32)remaining >= 0)
    {
        offset = end & 3u;
        w_masked_u32(end & ~3u, fill >> (8u * (3u - offset)), (1u << (offset + 1u)) - 1u);
    }
    return original;
}

uint32 sub_80044C44(uint32 destination, uint32 source, uint32 count)
{
    uint32 checked_result;
    uint32 original = destination;
    uint32 remaining, word0 = 0u, word1, word2, word3, offset, last;
    FUNCTION_MARKER(0x80044C44u, "SLUS_005.10");
    if (count == 0u)
        return original;
    while ((source & 3u) != 0u)
    {
        word0 = r_u8(source);
        checked_result = source + 1u;
        if ((((source ^ checked_result) & (1u ^ checked_result)) & 0x80000000u) != 0u)
            xport_mips_overflow_exception(0x80044C5Cu);
        source = checked_result;
        w_u8(destination, word0);
        checked_result = count + 0xFFFFFFFFu;
        if ((((count ^ checked_result) & (0xFFFFFFFFu ^ checked_result)) & 0x80000000u) != 0u)
            xport_mips_overflow_exception(0x80044C64u);
        count = checked_result;
        checked_result = destination + 1u;
        if ((((destination ^ checked_result) & (1u ^ checked_result)) & 0x80000000u) != 0u)
            xport_mips_overflow_exception(0x80044C6Cu);
        destination = checked_result;
        if (count == 0u)
            return original;
    }
    word0 = destination & 3u;
    remaining = count - 16u;
    if ((destination & 3u) == 0u)
    {
        if ((sint32)remaining >= 0)
        {
            do
            {
                word0 = r_u32(source);
                word1 = r_u32(source + 4u);
                word2 = r_u32(source + 8u);
                word3 = r_u32(source + 12u);
                w_u32(destination, word0);
                w_u32(destination + 4u, word1);
                w_u32(destination + 8u, word2);
                w_u32(destination + 12u, word3);
                checked_result = source + 16u;
                if ((((source ^ checked_result) & (16u ^ checked_result)) & 0x80000000u) != 0u)
                    xport_mips_overflow_exception(0x80044CA8u);
                source = checked_result;
                checked_result = remaining + 0xFFFFFFF0u;
                if ((((remaining ^ checked_result) & (0xFFFFFFF0u ^ checked_result)) & 0x80000000u) != 0u)
                    xport_mips_overflow_exception(0x80044CACu);
                remaining = checked_result;
                checked_result = destination + 16u;
                if ((((destination ^ checked_result) & (16u ^ checked_result)) & 0x80000000u) != 0u)
                    xport_mips_overflow_exception(0x80044CB4u);
                destination = checked_result;
            } while ((sint32)remaining >= 0);
        }
        remaining += 12u;
        if ((sint32)remaining >= 0)
        {
            do
            {
                word0 = r_u32(source);
                checked_result = source + 4u;
                if ((((source ^ checked_result) & (4u ^ checked_result)) & 0x80000000u) != 0u)
                    xport_mips_overflow_exception(0x80044CC8u);
                source = checked_result;
                w_u32(destination, word0);
                checked_result = remaining + 0xFFFFFFFCu;
                if ((((remaining ^ checked_result) & (0xFFFFFFFCu ^ checked_result)) & 0x80000000u) != 0u)
                    xport_mips_overflow_exception(0x80044CD0u);
                remaining = checked_result;
                checked_result = destination + 4u;
                if ((((destination ^ checked_result) & (4u ^ checked_result)) & 0x80000000u) != 0u)
                    xport_mips_overflow_exception(0x80044CD8u);
                destination = checked_result;
            } while ((sint32)remaining >= 0);
        }
        remaining += 3u;
        checked_result = source + remaining;
        if ((((source ^ checked_result) & (remaining ^ checked_result)) & 0x80000000u) != 0u)
            xport_mips_overflow_exception(0x80044CE4u);
        source = checked_result;
        if ((sint32)remaining >= 0)
        {
            offset = source & 3u;
            word0 = (word0 & (0x00FFFFFFu >> (8u * offset))) | (r_u32(source & ~3u) << (8u * (3u - offset)));
            checked_result = destination + remaining;
            if ((((destination ^ checked_result) & (remaining ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044CECu);
            destination = checked_result;
            offset = destination & 3u;
            w_masked_u32(destination & ~3u, word0 >> (8u * (3u - offset)), (1u << (offset + 1u)) - 1u);
        }
        return original;
    }
    if ((sint32)remaining >= 0)
    {
        do
        {
            word0 = r_u32(source);
            word1 = r_u32(source + 4u);
            word2 = r_u32(source + 8u);
            word3 = r_u32(source + 12u);
            offset = destination & 3u;
            w_masked_u32((destination) & ~3u, word0 << (8u * offset), (15u << offset) & 15u);
            last = destination + 3u;
            w_masked_u32(last & ~3u, word0 >> (8u * (3u - (last & 3u))), (1u << ((last & 3u) + 1u)) - 1u);
            w_masked_u32((destination + 4u) & ~3u, word1 << (8u * offset), (15u << offset) & 15u);
            last = destination + 4u + 3u;
            w_masked_u32(last & ~3u, word1 >> (8u * (3u - (last & 3u))), (1u << ((last & 3u) + 1u)) - 1u);
            w_masked_u32((destination + 8u) & ~3u, word2 << (8u * offset), (15u << offset) & 15u);
            last = destination + 8u + 3u;
            w_masked_u32(last & ~3u, word2 >> (8u * (3u - (last & 3u))), (1u << ((last & 3u) + 1u)) - 1u);
            w_masked_u32((destination + 12u) & ~3u, word3 << (8u * offset), (15u << offset) & 15u);
            last = destination + 12u + 3u;
            w_masked_u32(last & ~3u, word3 >> (8u * (3u - (last & 3u))), (1u << ((last & 3u) + 1u)) - 1u);
            checked_result = source + 16u;
            if ((((source ^ checked_result) & (16u ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044D30u);
            source = checked_result;
            checked_result = remaining + 0xFFFFFFF0u;
            if ((((remaining ^ checked_result) & (0xFFFFFFF0u ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044D34u);
            remaining = checked_result;
            checked_result = destination + 16u;
            if ((((destination ^ checked_result) & (16u ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044D3Cu);
            destination = checked_result;
        } while ((sint32)remaining >= 0);
    }
    remaining += 12u;
    if ((sint32)remaining >= 0)
    {
        do
        {
            word0 = r_u32(source);
            checked_result = source + 4u;
            if ((((source ^ checked_result) & (4u ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044D50u);
            source = checked_result;
            offset = destination & 3u;
            w_masked_u32(destination & ~3u, word0 << (8u * offset), (15u << offset) & 15u);
            last = destination + 3u;
            w_masked_u32(last & ~3u, word0 >> (8u * (3u - (last & 3u))), (1u << ((last & 3u) + 1u)) - 1u);
            checked_result = remaining + 0xFFFFFFFCu;
            if ((((remaining ^ checked_result) & (0xFFFFFFFCu ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044D5Cu);
            remaining = checked_result;
            checked_result = destination + 4u;
            if ((((destination ^ checked_result) & (4u ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044D64u);
            destination = checked_result;
        } while ((sint32)remaining >= 0);
    }
    remaining += 4u;
    if (remaining != 0u)
    {
        do
        {
            word0 = (uint32)(sint32)(sint8)r_u8(source);
            checked_result = source + 1u;
            if ((((source ^ checked_result) & (1u ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044D78u);
            source = checked_result;
            w_u8(destination, word0);
            checked_result = remaining + 0xFFFFFFFFu;
            if ((((remaining ^ checked_result) & (0xFFFFFFFFu ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044D80u);
            remaining = checked_result;
            checked_result = destination + 1u;
            if ((((destination ^ checked_result) & (1u ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044D88u);
            destination = checked_result;
        } while (remaining != 0u);
    }
    return original;
}

void sub_80015798(void)
{
    FUNCTION_MARKER(0x80015798u, "SLUS_005.10");
    CdControl(9u, NULL, NULL);
    xport_cd_ready_guest_callback(0u);
    sub_80045088(r_u32(0x800659A4u));
}

void sub_80045088(uint32 address)
{
    uint32 previous, next, units, following_units, previous_units;
    uint32 block = address - 8u;
    FUNCTION_MARKER(0x80045088u, "SLUS_005.10");
    previous = r_u32(0x8005ED4Cu);
    for (;;)
    {
        next = r_u32(previous);
        if (previous < block && block < next)
            break;
        if (previous >= next && (previous < block || block < next))
            break;
        previous = next;
    }
    units = r_u32(block + 4u);
    if (block + (units << 3) == next)
    {
        following_units = r_u32(next + 4u);
        units += following_units;
        if (following_units != 0u)
        {
            next = r_u32(next);
            w_u32(block + 4u, units);
        }
    }
    previous_units = r_u32(previous + 4u);
    w_u32(block, next);
    if (previous + (previous_units << 3) == block)
    {
        w_u32(previous + 4u, units + previous_units);
        block = next;
    }
    w_u32(0x8005ED4Cu, previous);
    w_u32(previous, block);
    return;
}

uint32 sub_80045134(uint32 address, uint32 size)
{
    uint32 checked_result;
    uint32 old_units, new_units, remaining, tail, result;
    FUNCTION_MARKER(0x80045134u, "SLUS_005.10");
    if (address == 0u)
        return sub_80045004(0u);
    if (size == 0u)
    {
        sub_80045088(address);
        return 0u;
    }
    old_units = r_u32(address - 4u);
    checked_result = size + 15u;
    if ((((size ^ checked_result) & (15u ^ checked_result)) & 0x80000000u) != 0u)
        xport_mips_overflow_exception(0x80045148u);
    new_units = checked_result >> 3;
    checked_result = old_units - new_units;
    if ((((old_units ^ new_units) & (old_units ^ checked_result)) & 0x80000000u) != 0u)
        xport_mips_overflow_exception(0x80045154u);
    remaining = checked_result;
    if (old_units == new_units)
        return address;
    tail = new_units << 3;
    if ((sint32)remaining >= 0)
    {
        w_u32(address - 4u, new_units);
        checked_result = address + tail;
        if ((((address ^ checked_result) & (tail ^ checked_result)) & 0x80000000u) != 0u)
            xport_mips_overflow_exception(0x80045168u);
        tail = checked_result;
        w_u32(tail - 4u, remaining);
        sub_80045088(tail);
        return address;
    }
    result = sub_80045004(size);
    if (result == 0u)
        return 0u;
    sub_80044D9C(result, address, size);
    sub_80045088(address);
    return result;
}

uint32 sub_80053A24(void)
{
    FUNCTION_MARKER(0x80053A24u, "SLUS_005.10");
    /* User-authorized missing BIOS syscall service */
    abort();
}

void sub_8001714C(uint32 counter)
{
    FUNCTION_MARKER(0x8001714Cu, "SLUS_005.10");
    w_u32(0x800568D4u, counter);
    w_u8(0x800568D8u, 0u);
}

uint32 sub_80013CAC(void)
{
    uint8 local_frame[0xC8];
    const uint32 gp = 0x80065304u;
    uint32 frame, packet, ordering, overlay, mask, index, module, string, asset;
    uint32 first, second, target, selected, other, selected_view, view_first, view_second;
    uint32 ticks, iteration, flags_first, flags_second, value, value2, a, b, c, d;
    sint32 height, offset_x, offset_y;
    FUNCTION_MARKER(0x80013CACu, "SLUS_005.10");
    frame = xport_guest_buffer_address(local_frame, sizeof(local_frame));
    w_u32(frame + 0xB8u, 0u);
    for (packet = frame + 0x20u; packet < frame + 0x60u; packet += 32u)
    {
        w_u8(packet + 3u, 3u); w_u8(packet + 7u, 0x60u);
        w_u8(packet + 4u, 0u); w_u8(packet + 5u, 0u); w_u8(packet + 6u, 0u);
        if (packet == frame + 0x20u)
        {
            w_u16(packet + 8u, 0u); w_u16(packet + 10u, 119u);
            w_u16(packet + 12u, 320u); w_u16(packet + 14u, 2u);
        }
        else
        {
            w_u16(packet + 8u, 159u); w_u16(packet + 10u, 0u);
            w_u16(packet + 12u, 2u); w_u16(packet + 14u, 240u);
        }
        a = r_u32(packet); b = r_u32(packet + 4u); c = r_u32(packet + 8u); d = r_u32(packet + 12u);
        w_u32(packet + 16u, a); w_u32(packet + 20u, b); w_u32(packet + 24u, c); w_u32(packet + 28u, d);
    }
    SetDefDrawEnv((DRAWENV *)psx_addr(0x8006F208u, 92u), 0, 0, 320, 240);
    SetDefDrawEnv((DRAWENV *)psx_addr(0x8006F264u, 92u), 0, 240, 320, 240);
    SetDefDrawEnv((DRAWENV *)psx_addr(0x8006F2C0u, 92u), 0, 0, 320, 119);
    SetDefDrawEnv((DRAWENV *)psx_addr(0x8006F31Cu, 92u), 0, 240, 320, 119);
    SetDefDrawEnv((DRAWENV *)psx_addr(0x8006F378u, 92u), 0, 121, 320, 119);
    SetDefDrawEnv((DRAWENV *)psx_addr(0x8006F3D4u, 92u), 0, 361, 320, 119);
    SetDefDrawEnv((DRAWENV *)psx_addr(0x8006F430u, 92u), 0, 0, 159, 240);
    SetDefDrawEnv((DRAWENV *)psx_addr(0x8006F48Cu, 92u), 0, 240, 159, 240);
    SetDefDrawEnv((DRAWENV *)psx_addr(0x8006F4E8u, 92u), 161, 0, 159, 240);
    SetDefDrawEnv((DRAWENV *)psx_addr(0x8006F544u, 92u), 161, 240, 159, 240);
    SetDefDispEnv((DISPENV *)psx_addr(0x8006F5A0u, 20u), 0, 240, 320, 240);
    SetDefDispEnv((DISPENV *)psx_addr(0x8006F5B4u, 20u), 0, 0, 320, 240);
    w_u32(0x8006ECA0u, 0x8006ECA4u); w_u32(0x8006ECA4u, 0u);
    w_u32(0x8006ECA8u, 0x8006ECA0u); w_u32(0x8006ECACu, 0x8006ECB0u);
    w_u32(0x8006ECB0u, 0u); w_u32(0x8006ECB4u, 0x8006ECACu);
    sub_80043EF0();
    w_u8(0x8006EEDBu, 1u); w_u32(0x8006EEDCu, 0xE1000220u);
    w_u8(0x8006EEE3u, 3u); w_u8(0x8006EEE7u, 0x62u);
    w_u16(0x8006EEE8u, 0u); w_u16(0x8006EEECu, 320u); w_u16(0x8006EEEEu, 240u);
    MargePrim(0x8006EED8u, 0x8006EEE0u);
restart:
    overlay = 0u;
    sub_80011834();
    w_u32(frame + 0xBCu, 120u);
    sub_800128D4(); sub_800251FC(64u);
    if (r_u32(frame + 0xB8u) == 0u)
    {
        module = sub_80011ADC(0x800655D4u);
        string = xport_guest_call0(r_u32(module + 4u));
        if (string == 0u) string = 0x80065344u;
        strcpy((char *)psx_addr(frame + 0x60u, 1u), (const char *)psx_addr(string, 1u));
        sub_80045088(module);
        if (r_u8(frame + 0x60u) == 0u) return 0u;
    }
    offset_x = (sint8)r_u8(gp + 0x18u); offset_y = (sint8)r_u8(gp + 0x19u);
    w_u32(frame + 0xB8u, 0u);
    w_u16(0x8006F5BCu, (uint16)offset_x); w_u16(0x8006F5A8u, (uint16)offset_x);
    w_u16(0x8006F5BEu, (uint16)offset_y); w_u16(0x8006F5AAu, (uint16)offset_y);
    sub_80029DEC();
    mask = 0xE000u;
    for (index = 0u; index < 8u; ++index)
        if (index < 2u || (sint8)r_u8(0x8006567Cu + index - 2u) != 0)
            mask |= 1u << ((uint32)(sint32)(sint8)r_u8(0x80065674u + index) & 31u);
    sub_800227A4(mask);
    value = sub_80044360(0x800655E4u); w_u32(gp + 0x5F8u, value);
    asset = sub_80015F80(0x800655F4u);
    sub_800165CC(0u); sub_80017FD4(1u);
    value = sub_80019034(asset, 35u); w_u32(gp + 0x628u, value);
    sub_8001910C(value); sub_8002A598();
    if ((sint8)r_u8(gp + 0x15u) == 5) sub_8001714C(0xBB40E64Du);
    value = r_u8(gp + 0x15u);
    w_u16(0x8006F100u, 0u); w_u16(0x8006EFF8u, 0u); w_u16(0x8006EEF0u, 0u);
    value2 = (value - 3u < 2u) ? 2u : 0u; w_u32(gp + 0x10u, value2);
    w_u8(gp + 0x6CFu, value2 != 0u ? 0xABu : 0xFFu);
    view_first = 1u; view_second = 1u;
    if (value == 0u)
    {
        a = r_u32(gp + 0x608u); b = (uint32)(sint32)(sint8)r_u8(0x80065674u); c = (uint32)(sint32)(sint8)r_u8(gp + 0x600u);
        target = r_u32(a + (b << 3) + 8u) + (c << 4);
        string = r_u32(target + 12u); a = r_u16(target + 2u); b = r_u16(target + 4u);
        w_u16(gp + 0x6F0u, (uint16)a); w_u16(gp + 0x7DCu, (uint16)b);
        value2 = r_u8(target + 1u);
    }
    else { string = r_u32(gp + 0x618u) != 0u ? 0x8001029Cu : 0x80065344u; value2 = 0u; }
    sub_80022BA8(frame + 0x60u, string, value2);
    sub_80012980(); w_u32(gp + 0xCu, 0u); sub_800212C4(0u);
    if ((sint8)r_u8(gp + 0x15u) == 0)
    {
        sub_8001A0AC(0x80065604u, 0u);
        sub_80019960(r_u32(gp + 0x628u), 0x800102B0u, 16u, 192u);
        do { sub_800126F0(); } while ((r_u32(gp + 0x62Cu) & 0x40u) == 0u);
    }
    first = r_u32(gp + 0x7D0u); second = r_u32(gp + 0x7D4u);
    w_u32(frame + 0xB4u, 0u); w_u32(frame + 0xB0u, r_u32(first + 0xE0u));
    if (second != 0u) w_u32(frame + 0xB4u, r_u32(second + 0xE0u));
    w_u16(frame + 0xA4u, 320u); w_u16(frame + 0xA0u, 0u);
    w_u16(frame + 0xA2u, 0u); w_u16(frame + 0xA6u, 480u);
    ClearImage((PSX_RECT *)psx_addr(frame + 0xA0u, 8u), 0u, 0u, 0u);
    ordering = frame + 0xA8u; w_u32(frame + 0xACu, 0u);
    w_u32(gp - 0x5350u, 1u); w_u32(gp + 0x624u, 0u);
next_frame:
    flags_first = 0u; flags_second = 0u; w_u32(frame + 0xC0u, 0u);
    value = r_u32(frame + 0xACu) + 1u; w_u32(frame + 0xACu, value);
    if ((value & 7u) == 0u && sub_80043BB4() != 0u && sub_80012A90(r_u32(gp + 0x628u), 0u) != 0u) goto cleanup;
    ticks = 2u;
    if (r_u32(gp + 0x618u) == 0u)
        ticks = r_u32(gp + 0x1Cu) != 0u ? r_u32(gp - 0x5350u) - r_u32(gp + 0xCu) : 1u;
    w_u32(frame + 0x18u, ticks);
    for (iteration = 0u; iteration < r_u32(frame + 0x18u); ++iteration)
    {
        sub_800120D4(); value = r_u32(gp + 0xCu) + 1u;
        w_u32(gp + 0xCu, value); w_u16(gp + 0x6CCu, (uint16)value);
        sub_8002131C(iteration == r_u32(frame + 0x18u) - 1u ? r_u32(frame + 0x18u) : 0u);
        sub_80021394(r_u32(gp + 0xCu)); sub_80021678();
        if ((r_u32(0x80065C30u) & 0x800000u) != 0u) view_first = 3u - view_first;
        if (r_u32(gp + 0x7D4u) != 0u && (r_u32(0x80065C48u) & 0x800000u) != 0u) view_second = 3u - view_second;
        flags_first |= r_u32(gp + 0x62Cu); flags_second = r_u32(frame + 0xC0u) | r_u32(gp + 0x630u);
        w_u32(frame + 0xC0u, flags_second);
    }
    sub_800212C4(r_u16(gp + 0xCu));
    first = r_u32(gp + 0x7D0u); value = r_u32(gp + 8u); a = r_u16(first + 0xCu);
    w_u32(gp + 8u, 1u - value);
    if (a == 0u) view_first = 0u;
    else if (view_first == 2u && (r_u32(first) & 0x1000000u) != 0u) view_first = 1u;
    second = r_u32(gp + 0x7D4u);
    if (second != 0u)
    {
        if (r_u16(second + 0xCu) == 0u) view_second = 0u;
        else if (view_second == 2u && (r_u32(second) & 0x1000000u) != 0u) view_second = 1u;
    }
    value = r_u32(gp + 0x10u);
    if (value != 0u)
    {
        if (value == 1u) sub_8001D994(320u, 120u, 160u, 60u);
        else sub_8001D994(160u, 240u, 80u, 120u);
        sub_800119C0(0u);
        second = r_u32(gp + 0x7D4u); value = r_u32(second);
        if ((value & 0x1000000u) == 0u) w_u32(second, value & ~2u);
        target = r_u32(frame + 0xB0u);
        if (view_first == 2u)
        {
            first = r_u32(gp + 0x7D0u); target = r_u32(first + 0xF8u); w_u32(first, r_u32(first) | 2u);
        }
        height = (sint16)r_u16(r_u32(frame + 0xB0u) + 0x8Au); sub_8001DB24(target, height);
        a = r_u32(0x8006F680u); b = r_u32(0x8006F684u); w_u32(0x8006F6A0u, a); w_u32(0x8006F6A4u, b);
        a = r_u32(0x8006F688u); b = r_u32(0x8006F68Cu); w_u32(0x8006F6A8u, a); w_u32(0x8006F6ACu, b);
        a = r_u32(0x8006F690u); b = r_u32(0x8006F694u); w_u32(0x8006F6B0u, a); w_u32(0x8006F6B4u, b);
        a = r_u32(0x8006F698u); b = r_u32(0x8006F69Cu); w_u32(0x8006F6B8u, a); w_u32(0x8006F6BCu, b);
        sub_80021600(); ClearOTagR((uint32 *)psx_addr(ordering, 4u), 1);
        if (sub_80019D10(0x8006EEF0u, r_u32(gp + 0x628u), ordering, r_u32(frame + 0x18u)) != 0u || overlay != 0u)
        {
            if (overlay != 0u) sub_80018F7C(overlay, ordering);
            value = r_u32(ordering); packet = frame + 32u * r_u32(gp + 0x10u) + 16u * r_u32(gp + 8u);
            w_u32(ordering, packet & 0xFFFFFFu); w_u32(packet, ((uint32)r_u8(packet + 3u) << 24) | value);
            target = 0x8006F224u + 92u * (1u - r_u32(gp + 8u));
            SetDrawEnv(psx_addr(target, 64u), (DRAWENV *)psx_addr(0x8006F208u + 92u * (1u - r_u32(gp + 8u)), 92u));
            value = r_u32(ordering); target = 0x8006F224u + 92u * (1u - r_u32(gp + 8u));
            w_u32(ordering, target & 0xFFFFFFu); w_u32(target, ((uint32)r_u8(target + 3u) << 24) | value);
        }
        else if (r_u32(gp + 0x624u) != 0u && (sint16)r_u16(0x8006EEF0u) == 0 && (sint16)r_u16(0x8006EFF8u) == 0 && (sint16)r_u16(0x8006F100u) == 0)
        {
            if (r_u32(gp + 0x5ACu) == 4u)
            {
                string = r_u32(gp + 0x24u) != 0u || (sint8)r_u8(gp + 0x15u) == 3 ? 0x800102CCu : 0x800102E0u;
                index = (sint8)r_u8(gp + 0x15u) == 3 ? (r_u16(r_u32(gp + 0x7D0u) + 0xCu) == 0u) : 0u;
                sub_80043DF8(string, (sint32)(sint8)r_u8(0x80065674u + index));
            }
            overlay = sub_8001392C(r_u32(gp + 0x628u));
        }
        if (view_second != 0u) sub_8002AF98(r_u32(gp + 0x7D4u), (r_u32(gp + 0x10u) << 1) | 1u, ordering);
        sub_8002B7BC(r_u32(gp + 0x7D4u), 0x8006F6C0u, ordering);
        sub_80019D10(0x8006F100u, r_u32(gp + 0x628u), ordering, r_u32(frame + 0x18u)); DrawSync(0);
        target = 0x8006F208u + 92u * ((r_u32(gp + 0x10u) << 2) - (r_u32(gp + 8u) - 1u));
        sub_8002A25C((sint16)r_u16(target), (sint16)r_u16(target + 2u), ordering);
        sub_80012828(0x8006F5A0u + 20u * r_u32(gp + 8u), 0x8006F150u + 92u * (4u * r_u32(gp + 0x10u) + r_u32(gp + 8u)), ordering, r_u32(gp + 0x60Cu) + 0x3FFCu);
        sub_800119C0(1u);
        first = r_u32(gp + 0x7D0u); value = r_u32(first); if ((value & 0x1000000u) == 0u) w_u32(first, value & ~2u);
        target = r_u32(frame + 0xB4u);
        if (view_second == 2u) { second = r_u32(gp + 0x7D4u); target = r_u32(second + 0xF8u); w_u32(second, r_u32(second) | 2u); }
        height = (sint16)r_u16(r_u32(frame + 0xB4u) + 0x8Au); sub_8001DB24(target, height);
        a = r_u32(0x8006F680u); b = r_u32(0x8006F684u); w_u32(0x8006F6C0u, a); w_u32(0x8006F6C4u, b);
        a = r_u32(0x8006F688u); b = r_u32(0x8006F68Cu); w_u32(0x8006F6C8u, a); w_u32(0x8006F6CCu, b);
        a = r_u32(0x8006F690u); b = r_u32(0x8006F694u); w_u32(0x8006F6D0u, a); w_u32(0x8006F6D4u, b);
        a = r_u32(0x8006F698u); b = r_u32(0x8006F69Cu); w_u32(0x8006F6D8u, a); w_u32(0x8006F6DCu, b);
        sub_80021600(); ClearOTagR((uint32 *)psx_addr(ordering, 4u), 1);
        if (view_first != 0u) sub_8002AF98(r_u32(gp + 0x7D0u), 2u * r_u32(gp + 0x10u), ordering);
        sub_8002B7BC(r_u32(gp + 0x7D0u), 0x8006F6A0u, ordering);
        sub_80019D10(0x8006EFF8u, r_u32(gp + 0x628u), ordering, r_u32(frame + 0x18u));
        sub_800128BC(); DrawSync(0);
        target = 0x8006F208u + 92u * (4u * r_u32(gp + 0x10u) + r_u32(gp + 8u) - 2u);
        sub_8002A25C((sint16)r_u16(target), (sint16)r_u16(target + 2u), ordering);
        DrawOTag((uint32 *)psx_addr(ordering, 4u)); DrawSync(0);
        if ((sint16)r_u16(0x80065C28u) < 2) flags_first |= 0x8000000u;
        if ((sint16)r_u16(0x80065C40u) < 2) w_u32(frame + 0xC0u, r_u32(frame + 0xC0u) | 0x8000000u);
        PutDrawEnv((DRAWENV *)psx_addr(0x8006F208u + 92u * (4u * r_u32(gp + 0x10u) + r_u32(gp + 8u)), 92u));
        DrawOTag((uint32 *)psx_addr(r_u32(gp + 0x60Cu) + 0x3FFCu, 4u));
    }
    else
    {
        value = (uint32)(sint32)(sint8)r_u8(gp + 0x15u);
        if ((sint32)value < 3 || (first = r_u32(gp + 0x7D0u), r_u16(first + 0xCu) != 0u))
        { other = r_u32(gp + 0x7D4u); selected = r_u32(gp + 0x7D0u); selected_view = view_first; }
        else { other = first; selected = r_u32(gp + 0x7D4u); selected_view = view_second; }
        if (other != 0u) { value = r_u32(other); if ((value & 0x1000000u) == 0u) w_u32(other, value & ~2u); }
        if (selected_view == 2u)
        { target = r_u32(selected + 0xF8u); value = r_u32(selected + 0xE0u); w_u32(selected, r_u32(selected) | 2u); height = (sint16)r_u16(value + 0x8Au); }
        else
        { value = r_u32(selected); if ((value & 0x1000000u) == 0u) w_u32(selected, value & ~2u); target = r_u32(selected + 0xE0u); height = (sint16)r_u16(target + 0x8Au); }
        sub_8001DB24(target, height); sub_800119C0(r_u32(gp + 8u)); sub_8001D994(320u, 240u, 160u, 120u); sub_80021600();
        if (selected_view == 2u && (r_u32(selected) & 0x20000000u) == 0u) sub_8002B8D0(selected);
        ClearOTagR((uint32 *)psx_addr(ordering, 4u), 1);
        value = r_u32(gp + 0x680u);
        if (value != 0u)
        {
            a = r_u32(0x8006EEE4u); value2 = r_u32(ordering); b = r_u8(0x8006EEDBu);
            w_u32(ordering, 0x8006EED8u & 0xFFFFFFu); w_u32(0x8006EEE4u, (a & 0xFF000000u) | value);
            w_u32(0x8006EED8u, (b << 24) | value2);
        }
        w_u32(gp + 0x680u, 0u);
        if (selected_view != 0u) sub_8002AF98(selected, 2u - selected_view, ordering);
        sub_8002B7BC(selected, 0x8006F680u, ordering);
        if (r_u32(gp + 0x618u) != 0u)
        {
            if ((r_u32(gp + 0xCu) & 0x3Fu) < 0x28u)
            {
                w_u8(r_u32(gp + 0x628u) + 4u, 0x80u); w_u8(r_u32(gp + 0x628u) + 5u, 0x80u); w_u8(r_u32(gp + 0x628u) + 6u, 0u);
                sub_80019C64(r_u32(gp + 0x628u), 0x8006560Cu, 0x80065618u, 10u, ordering);
            }
        }
        else sub_80019D10(0x8006EEF0u, r_u32(gp + 0x628u), ordering, r_u32(frame + 0x18u));
        if (overlay != 0u) sub_80018F7C(overlay, ordering);
        else if (r_u32(gp + 0x624u) != 0u && (sint16)r_u16(0x8006EEF0u) == 0)
        {
            if (r_u32(gp + 0x5ACu) == 4u)
            { string = r_u32(gp + 0x24u) != 0u ? 0x800102CCu : 0x800102E0u; sub_80043DF8(string, (sint32)(sint8)r_u8(0x80065674u)); }
            if ((sint8)r_u8(gp + 0x15u) == 0)
            { value = sub_800220D4(); w_u32(gp + 0x620u, value ^ ((sint8)r_u8(0x80065674u) < 6)); }
            overlay = sub_8001392C(r_u32(gp + 0x628u));
        }
        sub_800128BC(); DrawSync(0);
        target = 0x8006F208u + 92u * (1u - r_u32(gp + 4u));
        sub_8002A25C(0, (sint16)r_u16(target + 2u), ordering);
        if ((sint16)r_u16(0x80065C28u) < 2) flags_first |= 0x8000000u;
        sub_80012828(0x8006F5A0u + 20u * r_u32(gp + 8u), 0x8006F208u + 92u * r_u32(gp + 4u), ordering, r_u32(gp + 0x60Cu) + 0x3FFCu);
    }
    if (overlay != 0u)
    {
        value = r_u32(gp + 0x624u) + r_u32(frame + 0x18u); w_u32(gp + 0x624u, value);
        if ((sint32)value >= 301)
        {
            if ((sint8)r_u8(gp + 0x15u) == 0)
            { if ((flags_first & 0x8400000u) != 0u || (r_u32(gp + 0x24u) == 0u && (sint32)value >= 1201)) goto cleanup; }
            else
            {
                value2 = flags_first | r_u32(frame + 0xC0u);
                if ((value2 & 0x8600000u) != 0u || (sint32)value >= 1201)
                { w_u32(frame + 0xB8u, value2 & 0x200000u); goto cleanup; }
            }
        }
    }
    value = flags_first | r_u32(frame + 0xC0u);
    if ((value & 0x100u) != 0u)
    {
        if ((value & 0x800u) != 0u)
        { value2 = r_u32(frame + 0xBCu) - r_u32(frame + 0x18u); w_u32(frame + 0xBCu, value2); if ((sint32)value2 < 0) goto quit; }
        else w_u32(frame + 0xBCu, 120u);
        goto next_frame;
    }
    if ((value & 0x8000000u) == 0u) goto next_frame;
    if (r_u32(gp + 0x618u) != 0u || sub_80012A90(r_u32(gp + 0x628u), ((flags_first >> 27) ^ 1u) & 1u) != 0u) goto quit;
    goto next_frame;
quit:
    w_u8(gp + 0x14u, 3u);
cleanup:
    if (overlay != 0u) sub_80018F3C(overlay);
    if (r_u32(gp + 0x618u) != 0u)
    {
        sub_8001265C(); sub_800120D4();
        value = 3u; if (r_u32(gp + 0x62Cu) == 0u && r_u32(gp + 0x630u) == 0u) value = 2u;
        w_u8(gp + 0x14u, (uint8)value); sub_80011C58(0x80065968u); sub_800126C8();
    }
    sub_800128BC(); sub_80044054(); sub_80044394(r_u32(gp + 0x5F8u)); sub_80022A1C();
    sub_800204DC(r_u32(frame + 0xB0u));
    if (r_u32(gp + 0x7D4u) != 0u) sub_800204DC(r_u32(frame + 0xB4u));
    sub_8002ACCC(); sub_80041E80(); sub_8001356C(r_u32(gp + 0x628u)); sub_800190D8(r_u32(gp + 0x628u));
    sub_80011914(0u); sub_80011914(1u); sub_80016678(0u);
    goto restart;
}

sint32 sub_8004F1E8(void)
{
    FUNCTION_MARKER(0x8004F1E8u, "SLUS_005.10");
    return r_u32(0x80064FC4u);
}

sint32 sub_80043EF0(void)
{
    SpuCommonAttr common = {0};
    SpuVoiceAttr voice = {0};
    sint32 index = 23;
    uint32 address = 0x800A3007u;
    FUNCTION_MARKER(0x80043EF0u, "SLUS_005.10");
    sub_80045354();
    SpuInitMalloc(16u, 0x800A3008u);
    do
    {
        w_u8(address, (uint32)index);
        index -= 1;
        address -= 1u;
    } while (index >= 0);
    sub_8004938C(0x800658B4u);
    common.mask = 0x2C3u;
    common.cd.volume.right = 0x3FFF;
    common.cd.volume.left = 0x3FFF;
    common.mvol.right = 0x3FFF;
    common.mvol.left = 0x3FFF;
    common.cd.mix = 1;
    SpuSetCommonAttr(&common);
    sub_80044080(0u, 0x2CCCu, 0x2CCCu);
    voice.voice = 0xFFFFFFu;
    voice.mask = 0xFF13u;
    voice.pitch = 0x400u;
    voice.r_mode = 3;
    voice.volume.left = 0x3FFF;
    voice.volume.right = 0x3FFF;
    voice.a_mode = 1;
    voice.s_mode = 1;
    voice.ar = 0u;
    voice.dr = 0u;
    voice.sr = 0u;
    voice.rr = 0u;
    voice.sl = 15u;
    SpuSetVoiceAttr(&voice);
    w_u32(0x80065C00u, 0u);
    return sub_80043A74();
}

uint32 sub_80045354(void)
{
    uint32 result;
    FUNCTION_MARKER(0x80045354u, "SLUS_005.10");
    result = _SpuInit(0u);
    return result;
}

sint32 sub_8004938C(uint32 volume)
{
    FUNCTION_MARKER(0x8004938Cu, "SLUS_005.10");
    CD_vol((CdlATV *)psx_addr(volume, sizeof(CdlATV)));
    return 1;
}

uint32 sub_80044080(uint32 enabled, uint32 volume, uint32 setting)
{
    volatile uint8 local_bytes[4];
    sint32 scaled_volume;
    uint32 result;

    FUNCTION_MARKER(0x80044080u, "SLUS_005.10");
    local_bytes[0] = 0xFFu;
    local_bytes[1] = enabled == 0u ? 0xFFu : 0u;
    local_bytes[2] = enabled != 0u ? 0xFFu : 0u;
    scaled_volume = (sint32)(sint16)(uint16)(volume << 1);
    local_bytes[3] = 0u;
    sub_80047674(scaled_volume, scaled_volume);
    w_u16(0x80065BE8u, setting);
    w_u16(0x80065C04u, volume);
    result = enabled == 0u;
    w_u8(0x800658ACu, result);
    return result;
}

sint32 sub_80052384(uint32 first, uint32 second, uint32 count);
uint32 sub_800251FC(uint32 mode);
uint32 sub_80011ADC(uint32 path);
void sub_8001D994(uint32 first, uint32 second, uint32 x, uint32 y);
void sub_8004D524(uint32 x, uint32 y);
uint32 sub_80015948(uint32 path);
uint32 sub_80011834(void);
uint32 sub_800128D4(void);
uint32 sub_80015F80(uint32 path);
uint32 sub_800157D4(uint32 path);
uint32 sub_80015368(uint32 path);
uint32 sub_800116F4(uint32 bytes);
uint32 sub_80045134(uint32 address, uint32 bytes);
uint8 *sub_800154F4(uint8 *destination, sint32 sector, sint32 count);
uint32 sub_80047674(uint32 left, uint32 right);
uint32 sub_80043A74(void);
void sub_80044F64(uint32 destination, uint32 count);
uint32 sub_800541AC(void);
uint32 sub_80048120(uint32 incoming_v0, uint32 slot, uint32 guest_callback);
sint32 sub_80049534(uint32 position);
uint32 sub_80011F0C(void);
uint32 PadInitDirectPSX(uint32 first_packet, uint32 second_packet);
uint32 PadStartComPSX(void);
uint32 VSyncCallbackPSX(uint32 guest_callback);

uint32 sub_80047674(uint32 left, uint32 right)
{
    uint32 base;
    FUNCTION_MARKER(0x80047674u, "SLUS_005.10");
    base = r_u32(0x8005EDD4u);
    w_u16(base + 0x1B0u, (uint16)left);
    w_u16(base + 0x1B2u, (uint16)right);
    return base;
}

uint32 sub_80043A74(void)
{
    uint32 count, sector, result;
    FUNCTION_MARKER(0x80043A74u, "SLUS_005.10");
    do
    {
        count = (uint32)CdGetToc((CdlLOC *)psx_addr(0x800A3090u, 400u));
        w_u8(0x80065BFCu, (uint8)count);
    } while ((count & 0xFFu) == 0u);
    sector = sub_80049534(0x800A3090u);
    count = r_u8(0x80065BFCu);
    CdIntToPos((sint32)(sector - 150u), (CdlLOC *)psx_addr(0x800A3094u + (count << 2u), sizeof(CdlLOC)));
    result = r_u32(0x800658B0u);
    count = r_u8(0x80065BFCu);
    result = result >= 3u ? 1u : 0u;
    w_u8(0x80065BFCu, (uint8)(count - result));
    return result;
}

uint32 sub_80011834(void)
{
    uint32 selected;
    uint32 next;
    uint32 following;
    uint32 result;
    FUNCTION_MARKER(0x80011834u, "SLUS_005.10");
    selected = r_u32(r_u32(0x8005ED4Cu));
    while (r_u32(selected + 4u) != 0u)
        selected = r_u32(selected);
    next = r_u32(selected);
    result = r_u32(next + 4u);
    if (result != 0u)
    {
        for (;;)
        {
            following = r_u32(next);
            result = r_u32(following + 4u);
            if (result == 0u)
                break;
            selected = next;
            next = following;
        }
    }
    w_u32(0x8005ED4Cu, selected);
    return result;
}

uint32 sub_800128D4(void)
{
    uint32 base;
    uint32 count_address;
    uint32 pointer_address;
    uint32 outer = 0u;
    uint32 inner;
    uint32 item;
    uint32 entry;
    uint32 left;
    uint32 right;
    uint32 result;
    FUNCTION_MARKER(0x800128D4u, "SLUS_005.10");
    base = sub_80015F80(0x80065474u);
    result = r_u32(base);
    count_address = base + 4u;
    w_u32(0x8006590Cu, base);
    if ((sint32)result > 0)
    {
        pointer_address = base + 8u;
        do
        {
            item = r_u32(pointer_address) + base;
            w_u32(pointer_address, item);
            inner = 0u;
            if ((sint32)r_u32(count_address) > 0)
            {
                entry = item + 8u;
                do
                {
                    right = r_u32(entry + 4u);
                    left = r_u32(entry);
                    right += base;
                    left += base;
                    w_u32(entry + 4u, right);
                    w_u32(entry, left);
                    result = r_u32(count_address);
                    inner += 1u;
                    result = (uint32)((sint32)inner < (sint32)result);
                    entry += 16u;
                } while (result != 0u);
            }
            result = r_u32(base);
            outer += 1u;
            pointer_address += 8u;
            result = (uint32)((sint32)outer < (sint32)result);
            count_address += 8u;
        } while (result != 0u);
    }
    return result;
}

uint32 sub_80015F80(uint32 path)
{
    uint32 result;
    FUNCTION_MARKER(0x80015F80u, "SLUS_005.10");
    result = sub_80015948(path);
    if (result == 0u)
        result = sub_80015368(path);
    return result;
}

uint32 sub_80015948(uint32 path)
{
    uint32 entry;
    uint32 rounded;
    uint32 allocation;
    uint32 sectors;
    uint32 sector;
    FUNCTION_MARKER(0x80015948u, "SLUS_005.10");
    entry = sub_800157D4(path);
    if (entry == 0u)
        return 0u;
    rounded = (r_u32(entry + 16u) + 2047u) & 0xFFFFF800u;
    allocation = sub_800116F4(rounded);
    sectors = r_u32(entry + 16u);
    sector = r_u32(entry + 12u);
    sectors = (sectors + 2047u) >> 11;
    sub_800154F4((uint8 *)psx_addr(allocation, rounded), (sint32)sector, (sint32)sectors);
    return sub_80045134(allocation, r_u32(entry + 16u));
}

uint32 sub_800157D4(uint32 path)
{
    uint8 component[12];
    uint32 directory;
    uint32 cursor = path;
    uint32 length;
    uint32 character;
    uint32 guest_component;
    uint32 index;
    uint32 offset;
    uint32 entry;
    uint32 count;
    FUNCTION_MARKER(0x800157D4u, "SLUS_005.10");
    character = r_u8(cursor);
    directory = r_u32(0x800659B8u);
    if (character == 0x5Cu)
        cursor += 1u;
    if (directory == 0u)
        return 0u;
    for (;;)
    {
        length = 0u;
        do
        {
            character = r_u8(cursor);
            cursor += 1u;
            if (character >= 0x61u)
                character -= 32u;
            if (character == 0u || character == 0x5Cu)
                break;
            component[length] = (uint8)character;
            length += 1u;
        } while (length < 12u);
        while (length < 12u)
            component[length++] = 0x20u;
        guest_component = xport_guest_buffer_address(component, sizeof(component));
        if (character == 0x5Cu)
        {
            directory = r_u32(directory + 8u);
            while (directory != 0u)
            {
                if (sub_80052384(directory, guest_component, 8) == 0)
                    break;
                directory = r_u32(directory + 12u);
            }
            if (directory == 0u)
                return 0u;
        }
        else
        {
            count = r_u32(directory + 16u);
            index = 0u;
            if ((sint32)count <= 0)
                return 0u;
            offset = 20u;
            do
            {
                entry = directory + offset;
                count = (uint32)sub_80052384(entry, guest_component, 12);
                index += 1u;
                if (count == 0u)
                    return entry;
                count = r_u32(directory + 16u);
                offset += 20u;
            } while ((sint32)index < (sint32)count);
            return 0u;
        }
    }
}

sint32 sub_80052384(uint32 first, uint32 second, uint32 count)
{
    FUNCTION_MARKER(0x80052384u, "SLUS_005.10");
    for (;;)
    {
        uint32 left = r_u8(first);
        uint32 right = r_u8(second);
        first += 1u;
        if (left != right)
        {
            first -= 1u;
            left = r_u8(first);
            right = r_u8(second);
            return (sint32)(left - right);
        }
        count -= 1u;
        second += 1u;
        if ((sint32)count <= 0)
            return 0;
    }
}

uint32 sub_800251FC(uint32 mode)
{
    uint32 index;
    uint32 row;
    uint32 column;
    uint32 buffer;
    FUNCTION_MARKER(0x800251FCu, "SLUS_005.10");
    w_u16(0x80065B30u, mode);
    w_u16(0x80065B18u, 0u);
    for (index = 0u; index < 64u; ++index)
    {
        uint32 old = r_u32(0x8007A8A0u + index * 4u);
        if (old != 0u)
            sub_80045088(old);
    }
    buffer = sub_800116F4(0x3000u);
    w_u32(0x8007A8A0u, buffer);
    for (index = 1u; index < 64u; ++index)
        w_u32(0x8007A8A0u + index * 4u, 0u);
    for (row = 0u; row < 64u; ++row)
    {
        for (column = 0u; column < 64u; ++column)
        {
            w_u16(buffer + (row << 7) + column * 2u, 0x45FFu);
            w_u8(buffer + 0x2000u + (row << 6) + column, 0u);
        }
    }
    for (row = 0xFFFFFFFFu; (sint32)row < 33; ++row)
    {
        for (column = 0u; column < 32u; ++column)
            w_u32(0x80091120u + (row << 7) + column * 4u + 0x80u, buffer);
    }
    for (index = 0u; index < 0x900u; ++index)
    {
        uint32 packet = 0x80092220u + index * 0x1Cu;
        w_u8(packet + 3u, 6u);
        w_u8(packet + 7u, 0x30u);
    }
    for (index = 0u; index < 0x800u; ++index)
    {
        uint32 packet = 0x8007A9A0u + index * 0x28u;
        w_u8(packet + 3u, 9u);
        w_u8(packet + 7u, 0x34u);
        w_u8(packet + 0x1Fu, 0x34u);
        w_u8(packet + 0x13u, 0x34u);
    }
    for (index = 0u; index < 0x20u; ++index)
    {
        uint32 packet = 0x8008E9A0u + index * 0x34u;
        w_u8(packet + 3u, 12u);
        w_u8(packet + 7u, 0x3Cu);
    }
    for (index = 0u; index < 2u; ++index)
    {
        uint32 first = 0x800910C0u + index * 0x30u;
        uint32 second = first + 0x18u;
        w_u8(first + 3u, 5u);
        w_u8(first + 7u, 0x28u);
        w_u8(second + 3u, 5u);
        w_u8(second + 7u, 0x28u);
        (void)MargePrim(first, second);
    }
    return 0u;
}

uint32 sub_80011ADC(uint32 path)
{
    uint32 base;
    uint32 cursor;
    uint32 relocation;
    uint32 instruction_base;
    FUNCTION_MARKER(0x80011ADCu, "SLUS_005.10");
    base = sub_80015948(path);
    if (base == 0u)
        return base;
    cursor = base + r_u32(base);
    relocation = r_u32(cursor);
    if (relocation != 0xFFFFFFFFu)
    {
        instruction_base = (base << 4) >> 6;
        relocation = r_u32(cursor);
        cursor += 4u;
        for (;;)
        {
            uint32 target = base + (relocation & 0xFFFFFFFCu);
            uint32 kind = relocation & 3u;
            if (kind == 1u)
            {
                uint32 addend = r_u32(cursor);
                cursor += 4u;
                w_u16(target, (base + addend + 0x8000u) >> 16);
            }
            else if (kind == 0u)
                w_u32(target, r_u32(target) + base);
            else if (kind == 2u)
                w_u16(target, r_u16(target) + base);
            else
                w_u32(target, r_u32(target) + instruction_base);
            relocation = r_u32(cursor);
            cursor += 4u;
            if (relocation == 0xFFFFFFFFu)
                break;
        }
    }
    (void)sub_80045134(base, r_u32(base));
    return base;
}

void sub_8001D994(uint32 first, uint32 second, uint32 x, uint32 y)
{
    FUNCTION_MARKER(0x8001D994u, "SLUS_005.10");
    w_u32(0x800659DCu, first);
    w_u32(0x800659E0u, second);
    sub_8004D524(x, y);
}

void sub_8004D524(uint32 x, uint32 y)
{
    FUNCTION_MARKER(0x8004D524u, "SLUS_005.10");
    SetGeomOffset((sint32)(sint16)(uint16)x, (sint32)(sint16)(uint16)y);
}

uint32 sub_80011F0C(void)
{
    uint32 page, value, address;
    FUNCTION_MARKER(0x80011F0Cu, "SLUS_005.10");
    PadInitDirectPSX(0x80066458u, 0x8006647Au);
    PadStartComPSX();
    VSyncCallbackPSX(0x80011CCCu);
    for (page = 0u; page < 4u; ++page)
    {
        for (value = 0u; value < 256u; ++value)
        {
            address = 0x80065C58u + (page << 8) + value;
            w_u8(address + 0x400u, (uint8)value);
            w_u8(address, (uint8)value);
        }
    }
    return 0u;
}

void sub_80044F64(uint32 destination, uint32 count)
{
    uint32 checked_result, end;
    FUNCTION_MARKER(0x80044F64u, "SLUS_005.10");
    if (count == 0u)
        return;
    while ((destination & 3u) != 0u)
    {
        w_u8(destination, 0u);
        checked_result = count + 0xFFFFFFFFu;
        if ((((count ^ checked_result) & (0xFFFFFFFFu ^ checked_result)) & 0x80000000u) != 0u)
            xport_mips_overflow_exception(0x80044F78u);
        count = checked_result;
        checked_result = destination + 1u;
        if ((((destination ^ checked_result) & (1u ^ checked_result)) & 0x80000000u) != 0u)
            xport_mips_overflow_exception(0x80044F80u);
        destination = checked_result;
        if (count == 0u)
            return;
    }
    count -= 4u;
    if ((sint32)count >= 0)
    {
        do
        {
            w_u32(destination, 0u);
            checked_result = count + 0xFFFFFFFCu;
            if ((((count ^ checked_result) & (0xFFFFFFFCu ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044F9Cu);
            count = checked_result;
            checked_result = destination + 4u;
            if ((((destination ^ checked_result) & (4u ^ checked_result)) & 0x80000000u) != 0u)
                xport_mips_overflow_exception(0x80044FA4u);
            destination = checked_result;
        } while ((sint32)count >= 0);
    }
    count += 3u;
    checked_result = destination + count;
    if ((((destination ^ checked_result) & (count ^ checked_result)) & 0x80000000u) != 0u)
        xport_mips_overflow_exception(0x80044FB0u);
    end = checked_result;
    if ((sint32)count < 0)
        return;
    for (uint32 byte = 0u; byte <= (end & 3u); ++byte)
        w_u8((end & ~3u) + byte, 0u);
}

uint32 sub_800541AC(void)
{
    FUNCTION_MARKER(0x800541ACu, "SLUS_005.10");
    w_u32(0x800A4C6Cu, 0x80054240u);
    w_u32(0x800A4C70u, 0x800541D8u);
    w_u32(0x800A4C68u, 0u);
    w_u32(0x800A4C74u, 0u);
    return 0x800A4C6Cu;
}

uint32 sub_80048120(uint32 incoming_v0, uint32 slot, uint32 guest_callback)
{
    uint32 target, result;
    FUNCTION_MARKER(0x80048120u, "SLUS_005.10");
    target = r_u32(incoming_v0 + 0x14u);
    result = (uint32)xport_guest_call2(target, slot, guest_callback);
    return result;
}
