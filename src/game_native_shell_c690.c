#include "psx.h"
#include <stdio.h>
#include <stdlib.h>

uint32 v8_native_shell_12F8(uint32 base);

void sub_8001714C(uint32 seed);
uint32 sub_80017160(void);

static uint32 shellc690_random_word(void)
{
    (void)sub_80017160();
    return r_u32(0x800568D4u);
}

static uint32 shellc690_14D0(uint32 base,uint32 record)
{
    uint64 packed=0u,remaining;
    uint32 index,sum=0u,checksum,first,second;
    for(index=0u;index<12u;++index)
        packed=(packed<<5u)|r_u8(0x80065950u+index);
    remaining=packed;
    for(index=0u;index<13u;++index)
    {
        sum+=(uint32)(remaining%26u);
        remaining/=26u;
    }
    checksum=sum%26u;
    sub_8001714C(0x31415926u);
    for(index=0u;index<checksum;++index)
        (void)sub_80017160();
    first=shellc690_random_word()>>3u;
    second=shellc690_random_word();
    packed^=((uint64)first<<32u)|second;
    w_u8(record,checksum);
    for(index=1u;index<14u;++index)
    {
        w_u8(record+index,(uint32)(packed%26u));
        packed/=26u;
    }
    return record;
}

void v8_shell_C690(uint32 base)
{
    uint32 previous,character,slot,flags,stage,changed,value;
    previous=v8_native_shell_12F8(base);
    character=(uint32)(sint32)(sint8)r_u8(0x80065674u);
    slot=0x80065950u+character;
    flags=r_u8(slot);
    stage=(uint32)(sint32)(sint8)r_u8(0x80065904u);
    value=31u-(uint32)Lzc((sint32)flags);
    if(stage==value)
    {
        stage=(uint32)(sint32)(sint8)r_u8(0x80065904u);
        value=(flags & ~(1u<<(stage&31u))) | (2u<<(stage&31u));
        w_u8(slot,value);
    }
    shellc690_14D0(base,0x80065C08u);
    stage=(uint32)(sint32)(sint8)r_u8(0x80065904u);
    value=r_u8(slot)|(1u<<(stage&31u));
    w_u8(slot,value);
    shellc690_14D0(base,0x80065C16u);
    changed=previous^v8_native_shell_12F8(base);
    value=31u-(uint32)Lzc((sint32)changed);
    w_u8(0x80065920u,value);
    w_u8(slot,flags);
}
