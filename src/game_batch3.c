#include "psx.h"

uint32 sub_80011A10(void);
uint32 sub_800119C0(uint32 index);
uint32 sub_80011914(uint32 index);
uint32 sub_8001A4F8(uint32 object, uint32 alternate);
uint32 sub_8001DE08(uint32 object);
void sub_80045088(uint32 address);
uint32 sub_80016E64(uint32 matrix);
uint32 xport_guest_buffer_address(void *host_buffer, size_t bytes);
uint32 sub_8001DB54(uint32 position, uint32 bound);
uint32 sub_8001BE5C(uint32 model, uint32 matrix, uint32 ordering_table);
uint32 sub_8001DCC8(uint32 model, uint32 matrix);
uint32 sub_8003E2FC(uint32 object);
uint32 sub_8003E520(uint32 object);
void sub_8004D524(uint32 x, uint32 y);
MATRIX *CompMatrixLV(MATRIX *left, MATRIX *right, MATRIX *destination);
uint32 DrawOTagPSX(uint32 guest_ot);
uint32 *ClearOTagRPSX(uint32 *ot, sint32 count, uint32 header_address, uint32 header_target, uint32 guest_ot);
uint32 xport_guest_frame_acquire(size_t bytes);
void xport_guest_frame_release(uint32 address, size_t bytes);
uint32 sub_8001B3D4(uint32 object, uint32 index, uint32 incoming_s1);
uint32 sub_8001D708(uint32 node);
uint32 sub_8001DC1C(uint32 node);
uint32 sub_8001A2CC(uint32 rectangle, uint32 first, uint32 second, uint32 color);
uint32 sub_8001B49C(uint32 object, uint32 index, uint32 incoming_s1);
uint32 sub_800187E4(uint32 image, uint32 output, uint32 incoming_s1);
uint32 sub_80016A20(uint32 vector);
uint32 sub_800116F4(uint32 bytes);
uint32 sub_8001B36C(uint32 object, uint32 index, uint32 incoming_s1);
uint32 sub_80018124(uint32 width, uint32 height, uint32 horizontal_alignment, uint32 vertical_alignment, uint32 requested_width, uint32 requested_height);
uint32 SetDrawMove(uint32 destination, uint32 rectangle, uint32 x, uint32 y);
uint32 ClearOTagPSX(uint32 ot, uint32 count, uint32 header_address, uint32 header_target, uint32 debug_flag_address, uint32 debug_callback_slot, uint32 debug_format_address);
uint32 sub_8001A584(uint32 object);
uint32 sub_8001A4AC(uint32 object, uint32 incoming_v0);
uint32 sub_8001AF48(uint32 node, uint32 incoming_v0);
uint32 sub_8001BDDC(uint32 object, uint32 incoming_v0);
uint32 sub_8001A2AC(uint32 rectangle, uint32 x, uint32 y);
uint32 sub_800183EC(uint32 node, uint32 incoming_v0);
uint32 sub_800118B4(uint32 pointer);
uint32 sub_80044C44(uint32 destination, uint32 source, uint32 bytes);
uint32 sub_8002A1E8(uint32 screen, uint32 ordering, uint32 packet, uint32 polygon, uint32 incoming_t1);
void xport_mips_overflow_exception(uint32 pc);

uint32 sub_8001B49C(uint32 object, uint32 index, uint32 incoming_s1)
{
    uint32 value, other, argument0 = object, argument1 = index, argument2, argument3;
    uint32 packet, primitive, byte_count, source, packet_end, color_source, part, color_mask;
    uint32 inline_source, temporary, header, loop_index, special;
    uint32 transfer_values[32], transfer_mask = 0u, last_ra;
    uint32 branch_taken;
    FUNCTION_MARKER(0x8001B49Cu, "SLUS_005.10");
    object = argument0;
    value = r_u32(argument0 + 0x00000000u);
    value = r_u32(value + 0x00000004u);
    argument1 = argument1 & 0x0000FFFFu;
    argument1 = argument1 << 2;
    argument1 = argument1 + value;
    part = r_u32(argument1 + 0x00000000u);
    argument0 = r_u8(part + 0x00000019u);
    argument0 = argument0 << 2;
    argument0 = argument0 + 0x0000002Cu;
    value = sub_800116F4(argument0);
    last_ra = 0x8001B500u;
    other = r_u8(part + 0x00000019u);
    byte_count = 0u;
    loop_index = 0u;
    special = 0u;
    branch_taken = (other == 0u);
    header = value;
    if (branch_taken != 0u) goto block_8001B548;
    packet = value;
block_8001B51C:
    argument0 = object;
    argument1 = 0u;
    value = sub_8001B36C(argument0, argument1, incoming_s1);
    last_ra = 0x8001B528u;
    w_u32(packet + 0x0000002Cu, value);
    temporary = loop_index;
    value = r_u8(part + 0x00000019u);
    packet = packet + 0x00000004u;
    temporary = temporary + 0x00000001u;
    value = (sint32)temporary < (sint32)value;
    branch_taken = (value != 0u);
    loop_index = temporary;
    if (branch_taken != 0u) goto block_8001B51C;
block_8001B548:
    other = r_u16(part + 0x00000010u);
    loop_index = 0u;
    primitive = r_u32(part + 0x00000014u);
    branch_taken = (other == 0u);
    argument3 = 0x0000000Au;
    if (branch_taken != 0u) goto block_8001B5C8;
    value = 0x80050000u;
    argument2 = value + 0x000068FCu;
    argument1 = other;
block_8001B568:
    value = r_u8(primitive + 0x00000003u);
    value = value >> 2;
    argument0 = value & 0x0000000Fu;
    branch_taken = (argument0 != argument3);
    value = argument0 << 2;
    if (branch_taken != 0u) goto block_8001B5A0;
    value = r_u16(primitive + 0x0000000Au);
    other = value << 2;
    value = other + value;
    value = value << 3;
    byte_count = byte_count + value;
    primitive = primitive + other;
    value = argument0 << 2;
block_8001B5A0:
    value = value + argument2;
    other = r_u16(value + 0x00000002u);
    temporary = loop_index;
    value = r_u16(value + 0x00000000u);
    temporary = temporary + 0x00000001u;
    byte_count = byte_count + other;
    primitive = primitive + value;
    value = (sint32)temporary < (sint32)argument1;
    branch_taken = (value != 0u);
    loop_index = temporary;
    if (branch_taken != 0u) goto block_8001B568;
block_8001B5C8:
    temporary = header;
    w_u16(temporary + 0x00000000u, 0u);
    w_u16(temporary + 0x00000002u, byte_count);
    value = r_u32(part + 0x00000000u);
    w_u32(temporary + 0x00000004u, value);
    value = r_u32(part + 0x00000004u);
    w_u32(temporary + 0x00000008u, value);
    value = r_u32(part + 0x00000008u);
    w_u32(temporary + 0x0000000Cu, value);
    value = r_u32(part + 0x0000000Cu);
    w_u32(temporary + 0x00000010u, value);
    value = r_u16(part + 0x00000010u);
    w_u32(temporary + 0x00000014u, value);
    value = r_u32(part + 0x00000014u);
    argument0 = byte_count;
    w_u32(temporary + 0x00000018u, value);
    value = sub_800116F4(argument0);
    last_ra = 0x8001B624u;
    temporary = header;
    packet = value;
    w_u32(temporary + 0x0000001Cu, packet);
    w_u32(temporary + 0x00000020u, 0u);
    value = r_u8(part + 0x00000018u);
    w_u16(temporary + 0x00000028u, 0u);
    w_u16(temporary + 0x00000026u, value);
    value = r_u16(part + 0x00000012u);
    w_u16(temporary + 0x0000002Au, value);
    value = r_u16(part + 0x0000001Au);
    w_u16(temporary + 0x00000024u, value);
    value = r_u16(part + 0x00000010u);
    loop_index = 0u;
    primitive = r_u32(part + 0x00000014u);
    branch_taken = (value == 0u);
    color_mask = 0x00FF0000u;
    if (branch_taken != 0u) goto block_8001BD44;
    color_mask = color_mask | 0x0000FFFFu;
block_8001B670:
    value = r_u8(primitive + 0x00000003u);
    value = value & 0x00000080u;
    branch_taken = (value == 0u);
    color_source = primitive;
    if (branch_taken != 0u) goto block_8001B6A8;
    value = r_u8(0x80065304u + 0x00000854u);
    w_u8(primitive + 0x00000000u, value);
    value = r_u8(0x80065304u + 0x00000855u);
    w_u8(primitive + 0x00000001u, value);
    value = r_u8(0x80065304u + 0x00000856u);
    w_u8(primitive + 0x00000002u, value);
block_8001B6A8:
    value = r_u8(primitive + 0x00000003u);
    value = value >> 2;
    other = value & 0x0000000Fu;
    value = other < 0x00000010u;
    branch_taken = (value == 0u);
    value = 0x80010000u;
    if (branch_taken != 0u) goto block_8001BD08;
    value = value + 0x00000488u;
    other = other << 2;
    other = other + value;
    value = r_u32(other + 0x00000000u);
    switch (value)
    {
    case 0x8001B6E0u: goto block_8001B6E0;
    case 0x8001B700u: goto block_8001B700;
    case 0x8001B7B8u: goto block_8001B7B8;
    case 0x8001B7F8u: goto block_8001B7F8;
    case 0x8001B838u: goto block_8001B838;
    case 0x8001B860u: goto block_8001B860;
    case 0x8001B90Cu: goto block_8001B90C;
    case 0x8001B92Cu: goto block_8001B92C;
    case 0x8001B954u: goto block_8001B954;
    case 0x8001B97Cu: goto block_8001B97C;
    case 0x8001BA28u: goto block_8001BA28;
    case 0x8001BB44u: goto block_8001BB44;
    case 0x8001BB78u: goto block_8001BB78;
    case 0x8001BC18u: goto block_8001BC18;
    case 0x8001BCE0u: goto block_8001BCE0;
    case 0x8001BD08u: goto block_8001BD08;
    default:
        transfer_values[0] = 0u;
        transfer_values[2] = value;
        transfer_values[3] = other;
        transfer_values[8] = temporary;
        transfer_values[16] = packet;
        transfer_values[17] = primitive;
        transfer_values[18] = byte_count;
        transfer_values[21] = color_source;
        transfer_values[22] = part;
        transfer_values[23] = color_mask;
        transfer_values[28] = 0x80065304u;
        transfer_values[31] = last_ra;
        if ((transfer_mask & 0x00080000u) != 0u) transfer_values[19] = source;
        if ((transfer_mask & 0x00100000u) != 0u) transfer_values[20] = packet_end;
        if ((transfer_mask & 0x40000000u) != 0u) transfer_values[30] = inline_source;
        return xport_guest_nonlocal_transfer(0x8001B49Cu, 0x8001B6D8u, value, 0x90E7010Du | transfer_mask, transfer_values);
    }
block_8001B6E0:
    value = r_u32(primitive + 0x00000000u);
    other = r_u8(color_source + 0x00000003u);
    argument0 = 0x04000000u;
    w_u32(packet + 0x00000000u, argument0);
    value = value & color_mask;
    other = other & 0x00000003u;
    other = other | 0x00000020u;
    goto block_8001BB68;
block_8001B700:
    value = r_u16(primitive + 0x00000012u);
    argument1 = r_u16(part + 0x00000012u);
    argument0 = object;
    value = value & 0x00003FFFu;
    argument1 = argument1 + value;
    argument1 = argument1 & 0x0000FFFFu;
    value = sub_8001B3D4(argument0, argument1, primitive);
    last_ra = 0x8001B71Cu;
    argument1 = r_u32(primitive + 0x00000000u);
    other = r_u8(color_source + 0x00000003u);
    argument0 = 0x09000000u;
    w_u32(packet + 0x00000000u, argument0);
    argument1 = argument1 & color_mask;
    other = other & 0x00000003u;
    other = other | 0x00000034u;
    other = other << 24;
    argument1 = argument1 | other;
    w_u32(packet + 0x00000004u, argument1);
    other = r_u32(primitive + 0x00000014u);
    w_u32(packet + 0x00000010u, other);
    other = r_u32(primitive + 0x00000018u);
    w_u32(packet + 0x0000001Cu, other);
    other = r_u16(value + 0x0000000Au);
    w_u16(packet + 0x0000000Eu, other);
    other = r_u16(primitive + 0x00000012u);
    argument0 = r_u16(value + 0x00000008u);
    other = other & 0x0000C000u;
    other = other >> 9;
    argument0 = argument0 | other;
    w_u16(packet + 0x0000001Au, argument0);
    other = r_u16(primitive + 0x0000000Cu);
    argument0 = r_u16(value + 0x00000006u);
    other = other + argument0;
    w_u16(packet + 0x0000000Cu, other);
    other = r_u16(primitive + 0x0000000Eu);
    argument0 = r_u16(value + 0x00000006u);
    other = other + argument0;
    w_u16(packet + 0x00000018u, other);
    other = r_u16(primitive + 0x00000010u);
    value = r_u16(value + 0x00000006u);
    other = other + value;
    goto block_8001BA20;
block_8001B7B8:
    argument0 = r_u32(primitive + 0x00000000u);
    value = r_u8(color_source + 0x00000003u);
    other = 0x06000000u;
    w_u32(packet + 0x00000000u, other);
    argument0 = argument0 & color_mask;
    value = value & 0x00000003u;
    value = value | 0x00000030u;
    value = value << 24;
    argument0 = argument0 | value;
    w_u32(packet + 0x00000004u, argument0);
    value = r_u32(primitive + 0x0000000Cu);
    w_u32(packet + 0x0000000Cu, value);
    value = r_u32(primitive + 0x00000010u);
    w_u32(packet + 0x00000014u, value);
    goto block_8001BD08;
block_8001B7F8:
    argument0 = r_u32(primitive + 0x00000000u);
    value = r_u8(color_source + 0x00000003u);
    other = 0x09000000u;
    w_u32(packet + 0x00000000u, other);
    argument0 = argument0 & color_mask;
    value = value & 0x00000003u;
    value = value | 0x00000034u;
    value = value << 24;
    argument0 = argument0 | value;
    w_u32(packet + 0x00000004u, argument0);
    value = r_u32(primitive + 0x00000014u);
    w_u32(packet + 0x00000010u, value);
    value = r_u32(primitive + 0x00000018u);
    w_u32(packet + 0x0000001Cu, value);
    goto block_8001BD08;
block_8001B838:
    value = r_u32(primitive + 0x00000000u);
    other = r_u8(color_source + 0x00000003u);
    temporary = 0x00000001u;
    argument0 = 0x04000000u;
    special = temporary;
    w_u32(packet + 0x00000000u, argument0);
    value = value & color_mask;
    other = other & 0x00000003u;
    other = other | 0x00000020u;
    goto block_8001BB68;
block_8001B860:
    value = r_u16(primitive + 0x00000012u);
    argument1 = r_u16(part + 0x00000012u);
    argument0 = object;
    value = value & 0x00003FFFu;
    argument1 = argument1 + value;
    argument1 = argument1 & 0x0000FFFFu;
    value = sub_8001B3D4(argument0, argument1, primitive);
    last_ra = 0x8001B87Cu;
    argument0 = r_u32(primitive + 0x00000000u);
    other = r_u8(color_source + 0x00000003u);
    temporary = 0x07000000u;
    w_u32(packet + 0x00000000u, temporary);
    argument0 = argument0 & color_mask;
    other = other & 0x00000003u;
    other = other | 0x00000024u;
    other = other << 24;
    argument0 = argument0 | other;
    w_u32(packet + 0x00000004u, argument0);
    other = r_u16(value + 0x0000000Au);
    w_u16(packet + 0x0000000Eu, other);
    other = r_u16(primitive + 0x00000012u);
    argument0 = r_u16(value + 0x00000008u);
    other = other & 0x0000C000u;
    other = other >> 9;
    argument0 = argument0 | other;
    w_u16(packet + 0x00000016u, argument0);
    other = r_u16(primitive + 0x0000000Cu);
    argument0 = r_u16(value + 0x00000006u);
    other = other + argument0;
    w_u16(packet + 0x0000000Cu, other);
    other = r_u16(primitive + 0x0000000Eu);
    argument0 = r_u16(value + 0x00000006u);
    other = other + argument0;
    w_u16(packet + 0x00000014u, other);
    other = r_u16(primitive + 0x00000010u);
    value = r_u16(value + 0x00000006u);
    temporary = 0x00000001u;
    special = temporary;
    other = other + value;
    w_u16(packet + 0x0000001Cu, other);
    goto block_8001BD08;
block_8001B90C:
    value = r_u32(primitive + 0x00000000u);
    other = r_u8(color_source + 0x00000003u);
    argument0 = 0x03000000u;
    w_u32(packet + 0x00000000u, argument0);
    value = value & color_mask;
    other = other & 0x00000003u;
    other = other | 0x00000040u;
    goto block_8001BB68;
block_8001B92C:
    other = r_u32(primitive + 0x00000000u);
    value = r_u8(color_source + 0x00000003u);
    temporary = 0x00000001u;
    special = temporary;
    temporary = 0x07000000u;
    w_u32(packet + 0x00000000u, temporary);
    other = other & color_mask;
    value = value & 0x00000003u;
    value = value | 0x00000024u;
    goto block_8001BCFC;
block_8001B954:
    value = r_u32(primitive + 0x00000000u);
    other = r_u8(color_source + 0x00000003u);
    temporary = 0x00000001u;
    argument0 = 0x06000000u;
    special = temporary;
    w_u32(packet + 0x00000000u, argument0);
    value = value & color_mask;
    other = other & 0x00000003u;
    other = other | 0x00000030u;
    goto block_8001BB68;
block_8001B97C:
    value = r_u16(primitive + 0x00000016u);
    argument1 = r_u16(part + 0x00000012u);
    argument0 = object;
    value = value & 0x00003FFFu;
    argument1 = argument1 + value;
    argument1 = argument1 & 0x0000FFFFu;
    value = sub_8001B3D4(argument0, argument1, primitive);
    last_ra = 0x8001B998u;
    argument1 = r_u32(primitive + 0x00000000u);
    other = r_u8(color_source + 0x00000003u);
    argument0 = 0x09000000u;
    w_u32(packet + 0x00000000u, argument0);
    argument1 = argument1 & color_mask;
    other = other & 0x00000003u;
    other = other | 0x00000034u;
    other = other << 24;
    argument1 = argument1 | other;
    w_u32(packet + 0x00000004u, argument1);
    other = r_u16(value + 0x0000000Au);
    w_u16(packet + 0x0000000Eu, other);
    other = r_u16(primitive + 0x00000016u);
    argument0 = r_u16(value + 0x00000008u);
    other = other & 0x0000C000u;
    other = other >> 9;
    argument0 = argument0 | other;
    w_u16(packet + 0x0000001Au, argument0);
    other = r_u16(primitive + 0x00000010u);
    argument0 = r_u16(value + 0x00000006u);
    other = other + argument0;
    w_u16(packet + 0x0000000Cu, other);
    other = r_u16(primitive + 0x00000012u);
    argument0 = r_u16(value + 0x00000006u);
    other = other + argument0;
    w_u16(packet + 0x00000018u, other);
    other = r_u16(primitive + 0x00000014u);
    value = r_u16(value + 0x00000006u);
    temporary = 0x00000001u;
    special = temporary;
    other = other + value;
block_8001BA20:
    w_u16(packet + 0x00000024u, other);
    goto block_8001BD08;
block_8001BA28:
    value = r_u16(primitive + 0x0000000Au);
    packet_end = packet;
    transfer_mask |= 0x00100000u;
    byte_count = 0u;
    branch_taken = (value == 0u);
    inline_source = primitive;
    transfer_mask |= 0x40000000u;
    if (branch_taken != 0u) goto block_8001BB30;
    packet = packet + 0x00000025u;
    source = primitive;
    transfer_mask |= 0x00080000u;
block_8001BA44:
    value = r_u16(source + 0x0000000Eu);
    argument1 = r_u16(part + 0x00000012u);
    argument0 = object;
    value = value & 0x00003FFFu;
    argument1 = argument1 + value;
    argument1 = argument1 & 0x0000FFFFu;
    value = sub_8001B3D4(argument0, argument1, primitive);
    last_ra = 0x8001BA60u;
    other = 0x0000002Fu;
    w_u8(packet + 0xFFFFFFE2u, other);
    other = r_u16(value + 0x00000008u);
    other = other | 0x00000020u;
    w_u16(packet + 0xFFFFFFF1u, other);
    other = r_u16(value + 0x0000000Au);
    w_u16(packet + 0xFFFFFFE9u, other);
    other = r_u8(value + 0x00000006u);
    w_u8(packet + 0xFFFFFFE7u, other);
    other = r_u16(value + 0x00000006u);
    other = other >> 8;
    w_u8(packet + 0xFFFFFFE8u, other);
    other = r_u8(value + 0x00000006u);
    argument0 = r_u8(value + 0x00000002u);
    other = other + 0x000000FFu;
    argument0 = argument0 + other;
    w_u8(packet + 0xFFFFFFEFu, argument0);
    other = r_u16(value + 0x00000006u);
    other = other >> 8;
    w_u8(packet + 0xFFFFFFF0u, other);
    other = r_u8(value + 0x00000006u);
    w_u8(packet + 0xFFFFFFF7u, other);
    other = r_u16(value + 0x00000006u);
    argument0 = r_u8(value + 0x00000004u);
    other = other >> 8;
    other = other + 0x000000FFu;
    argument0 = argument0 + other;
    w_u8(packet + 0xFFFFFFF8u, argument0);
    other = r_u8(value + 0x00000006u);
    argument0 = r_u8(value + 0x00000002u);
    other = other + 0x000000FFu;
    argument0 = argument0 + other;
    w_u8(packet + 0xFFFFFFFFu, argument0);
    other = r_u16(value + 0x00000006u);
    value = r_u8(value + 0x00000004u);
    other = other >> 8;
    other = other + 0x000000FFu;
    value = value + other;
    w_u8(packet + 0x00000000u, value);
    value = r_u16(inline_source + 0x0000000Au);
    source = source + 0x00000004u;
    transfer_mask |= 0x00080000u;
    byte_count = byte_count + 0x00000001u;
    packet_end = packet_end + 0x00000028u;
    transfer_mask |= 0x00100000u;
    value = (sint32)byte_count < (sint32)value;
    branch_taken = (value != 0u);
    packet = packet + 0x00000028u;
    if (branch_taken != 0u) goto block_8001BA44;
block_8001BB30:
    value = r_u16(inline_source + 0x0000000Au);
    packet = packet_end;
    value = value << 2;
    primitive = primitive + value;
    goto block_8001BD08;
block_8001BB44:
    value = r_u32(primitive + 0x00000000u);
    other = r_u8(color_source + 0x00000003u);
    temporary = 0x00000001u;
    argument0 = 0x09000000u;
    special = temporary;
    w_u32(packet + 0x00000000u, argument0);
    value = value & color_mask;
    other = other & 0x00000003u;
    other = other | 0x00000034u;
block_8001BB68:
    other = other << 24;
    value = value | other;
    w_u32(packet + 0x00000004u, value);
    goto block_8001BD08;
block_8001BB78:
    value = r_u16(primitive + 0x00000010u);
    source = primitive;
    transfer_mask |= 0x00080000u;
    other = value & 0x00003FFFu;
    value = 0x00003FFFu;
    branch_taken = (other != value);
    byte_count = packet;
    if (branch_taken != 0u) goto block_8001BBA4;
    argument0 = 0x80065A28u;
    value = r_u8(argument0 + 0x00000004u);
    w_u8(primitive + 0x00000013u, value);
    goto block_8001BBBC;
block_8001BBA4:
    argument1 = r_u16(part + 0x00000012u);
    argument0 = object;
    argument1 = argument1 + other;
    argument1 = argument1 & 0x0000FFFFu;
    value = sub_8001B3D4(argument0, argument1, primitive);
    last_ra = 0x8001BBB8u;
    argument0 = value;
block_8001BBBC:
    value = r_u16(argument0 + 0x00000006u);
    other = r_u32(source + 0x00000000u);
    value = value >> 8;
    w_u8(source + 0x00000012u, value);
    value = r_u8(color_source + 0x00000003u);
    temporary = 0x07000000u;
    other = other & color_mask;
    w_u32(byte_count + 0x00000000u, temporary);
    value = value & 0x00000003u;
    value = value | 0x00000024u;
    value = value << 24;
    other = other | value;
    w_u32(byte_count + 0x00000004u, other);
    value = r_u16(argument0 + 0x0000000Au);
    w_u16(byte_count + 0x0000000Eu, value);
    value = r_u16(source + 0x00000010u);
    other = r_u16(argument0 + 0x00000008u);
    value = value & 0x0000C000u;
    value = value >> 9;
    other = other | value;
    w_u16(byte_count + 0x00000016u, other);
    goto block_8001BD08;
block_8001BC18:
    other = r_u16(primitive + 0x00000012u);
    source = primitive;
    transfer_mask |= 0x00080000u;
    value = 0x0000FFFFu;
    branch_taken = (other == value);
    byte_count = packet;
    if (branch_taken != 0u) goto block_8001BC4C;
    argument1 = r_u16(part + 0x00000012u);
    argument0 = object;
    value = other & 0x00003FFFu;
    argument1 = argument1 + value;
    argument1 = argument1 & 0x0000FFFFu;
    value = sub_8001B3D4(argument0, argument1, primitive);
    last_ra = 0x8001BC44u;
    argument0 = value;
    goto block_8001BC54;
block_8001BC4C:
    argument0 = 0x80065A28u;
block_8001BC54:
    other = r_u32(source + 0x00000000u);
    value = r_u8(color_source + 0x00000003u);
    temporary = 0x07000000u;
    w_u32(byte_count + 0x00000000u, temporary);
    other = other & color_mask;
    value = value & 0x00000003u;
    value = value | 0x00000025u;
    value = value << 24;
    other = other | value;
    w_u32(byte_count + 0x00000004u, other);
    value = r_u16(argument0 + 0x0000000Au);
    w_u16(byte_count + 0x0000000Eu, value);
    value = r_u16(source + 0x00000012u);
    other = r_u16(argument0 + 0x00000008u);
    value = value & 0x0000C000u;
    value = value >> 9;
    other = other | value;
    w_u16(byte_count + 0x00000016u, other);
    value = r_u16(source + 0x0000000Cu);
    other = r_u16(argument0 + 0x00000006u);
    value = value + other;
    w_u16(byte_count + 0x0000000Cu, value);
    value = r_u16(source + 0x0000000Eu);
    other = r_u16(argument0 + 0x00000006u);
    value = value + other;
    w_u16(byte_count + 0x00000014u, value);
    value = r_u16(source + 0x00000010u);
    other = r_u16(argument0 + 0x00000006u);
    value = value + other;
    w_u16(byte_count + 0x0000001Cu, value);
    goto block_8001BD08;
block_8001BCE0:
    other = r_u32(primitive + 0x00000000u);
    value = r_u8(color_source + 0x00000003u);
    temporary = 0x07000000u;
    w_u32(packet + 0x00000000u, temporary);
    other = other & color_mask;
    value = value & 0x00000003u;
    value = value | 0x00000025u;
block_8001BCFC:
    value = value << 24;
    other = other | value;
    w_u32(packet + 0x00000004u, other);
block_8001BD08:
    other = r_u8(color_source + 0x00000003u);
    temporary = loop_index;
    value = 0x800568FCu;
    other = other & 0x0000003Cu;
    other = other + value;
    argument0 = r_u16(other + 0x00000002u);
    other = r_u16(other + 0x00000000u);
    value = r_u16(part + 0x00000010u);
    temporary = temporary + 0x00000001u;
    loop_index = temporary;
    packet = packet + argument0;
    value = (sint32)temporary < (sint32)value;
    branch_taken = (value != 0u);
    primitive = primitive + other;
    if (branch_taken != 0u) goto block_8001B670;
block_8001BD44:
    temporary = special;
    branch_taken = (temporary == 0u);
    if (branch_taken != 0u) goto block_8001BD6C;
    temporary = header;
    value = r_u16(temporary + 0x00000000u);
    value = value | 0x00000001u;
    w_u16(temporary + 0x00000000u, value);
block_8001BD6C:
    value = header;
    return value;
}

uint32 sub_8001B3D4(uint32 object, uint32 index, uint32 incoming_s1)
{
    uint32 reference, count, base, table, image;
    FUNCTION_MARKER(0x8001B3D4u, "SLUS_005.10");
    index &= 0xFFFFu;
    reference = object + 12u * index + 12u;
    count = r_u16(reference) + 1u;
    w_u16(reference, (uint16)count);
    if ((count & 0xFFFFu) == 1u)
    {
        base = r_u32(object);
        table = r_u32(base + 20u);
        image = r_u32(table + 4u * index);
        (void)sub_800187E4(image, reference, incoming_s1);
    }
    return reference;
}

uint32 sub_8001D708(uint32 node)
{
    uint32 first, second, third;
    FUNCTION_MARKER(0x8001D708u, "SLUS_005.10");
    first = r_u32(node + 72u);
    second = r_u32(node + 76u);
    third = r_u32(node + 80u);
    w_u32(node + 36u, first);
    w_u32(node + 40u, second);
    w_u32(node + 44u, third);
    (void)RotMatrixYXZ((SVECTOR *)psx_addr(node + 64u, 6u), (MATRIX *)psx_addr(node + 16u, 18u));
    return node + 16u;
}

uint32 sub_8001DC1C(uint32 node)
{
    uint32 descriptor, maximum, shift, extent, child, result, length;
    FUNCTION_MARKER(0x8001DC1Cu, "SLUS_005.10");
    descriptor = r_u32(node + 48u);
    maximum = 0u;
    if (descriptor != 0u)
    {
        shift = r_u16(descriptor + 38u);
        extent = r_u16(descriptor + 36u);
        maximum = extent << ((16u - shift) & 31u);
    }
    child = r_u32(node + 56u);
    while (child != 0u)
    {
        result = sub_8001DC1C(child);
        length = sub_80016A20(child + 36u);
        result += length;
        if ((sint32)result < (sint32)maximum)
            result = maximum;
        child = r_u32(child + 52u);
        maximum = result;
        if (child == 0u) break;
    }
    w_u32(node + 84u, maximum);
    return maximum;
}

uint32 sub_8001A2CC(uint32 rectangle, uint32 first, uint32 second, uint32 color)
{
    DRAWENV environment;
    uint32 node, value, width, height, child, x, y, allocated;
    FUNCTION_MARKER(0x8001A2CCu, "SLUS_005.10");
    node = sub_800116F4(136u);
    value = (uint32)(sint32)(sint16)r_u16(rectangle);
    w_u32(node, value);
    value = (uint32)(sint32)(sint16)r_u16(rectangle + 2u);
    w_u32(node + 8u, first);
    w_u32(node + 12u, second);
    w_u32(node + 4u, value);
    width = (uint32)(sint32)(sint16)r_u16(rectangle + 4u);
    height = (uint32)(sint32)(sint16)r_u16(rectangle + 6u);
    allocated = sub_80018124(width, height, 64u, 1u, 64u, 1u);
    w_u32(node + 20u, allocated);
    (void)ClearOTagPSX(node + 72u, 1u, 0x800650E4u, 0x800650D0u, 0x80065026u, 0x80065020u, 0x800112B0u);
    child = r_u32(node + 20u);
    width = (uint32)(sint32)(sint16)r_u16(rectangle + 4u);
    x = (uint32)(sint32)(sint16)r_u16(child);
    y = (uint32)(sint32)(sint16)r_u16(child + 2u);
    height = (uint32)(sint32)(sint16)r_u16(rectangle + 6u);
    SetDefDrawEnv(&environment, (sint32)x, (sint32)y, (sint32)width, (sint32)height);
    xport_store_u8((uint8 *)&environment + 23u, 1u);
    if ((sint32)color < 0)
    {
        width = (uint32)(sint32)(sint16)r_u16(rectangle + 4u);
        height = (uint32)(sint32)(sint16)r_u16(rectangle + 6u);
        allocated = sub_80018124(width, height, 1u, 1u, 1u, 1u);
        w_u32(node + 16u, allocated);
        SetDrawEnv(psx_addr(node + 72u, 64u), &environment);
        child = r_u32(node + 20u);
        x = (uint32)(sint32)(sint16)r_u16(rectangle);
        y = (uint32)(sint32)(sint16)r_u16(rectangle + 2u);
        (void)SetDrawMove(node + 24u, child, x, y);
        child = r_u32(node + 20u);
        allocated = r_u32(node + 16u);
        x = (uint32)(sint32)(sint16)r_u16(child);
        y = (uint32)(sint32)(sint16)r_u16(child + 2u);
        (void)SetDrawMove(node + 48u, allocated, x, y);
        (void)MargePrim(node + 24u, node + 48u);
        value = r_u32(node + 24u);
        child = r_u32(node + 16u);
        w_u32(node + 24u, (value & 0xFF000000u) | ((node + 72u) & 0xFFFFFFu));
        x = (uint32)(sint32)(sint16)r_u16(child);
        y = (uint32)(sint32)(sint16)r_u16(child + 2u);
        MoveImage((PSX_RECT *)psx_addr(rectangle, 8u), (sint32)x, (sint32)y);
        return node;
    }
    w_u32(node + 16u, 0u);
    xport_store_u8((uint8 *)&environment + 26u, (uint8)(color >> 8));
    xport_store_u8((uint8 *)&environment + 24u, 1u);
    xport_store_u8((uint8 *)&environment + 25u, (uint8)color);
    xport_store_u8((uint8 *)&environment + 27u, (uint8)(color >> 16));
    SetDrawEnv(psx_addr(node + 72u, 64u), &environment);
    child = r_u32(node + 20u);
    x = (uint32)(sint32)(sint16)r_u16(rectangle);
    y = (uint32)(sint32)(sint16)r_u16(rectangle + 2u);
    (void)SetDrawMove(node + 24u, child, x, y);
    value = r_u32(node + 24u);
    w_u32(node + 24u, (value & 0xFF000000u) | ((node + 72u) & 0xFFFFFFu));
    return node;
}

uint32 sub_80011A10(void)
{
    uint32 index;
    FUNCTION_MARKER(0x80011A10u, "SLUS_005.10");
    index = r_u32(0x80065308u);
    return sub_800119C0(1u - index);
}

uint32 sub_800119C0(uint32 index)
{
    uint32 table;
    FUNCTION_MARKER(0x800119C0u, "SLUS_005.10");
    table = 0x800664A0u + (((index << 4) + index) << 10);
    w_u32(0x80065308u, index);
    w_u32(0x80065910u, table);
    (void)ClearOTagRPSX((uint32 *)psx_addr(table, 16384u), 4096, 0x800650E4u, 0x800650D0u, table);
    return sub_80011914(index);
}

uint32 sub_80011914(uint32 index)
{
    uint32 header, current, next;
    FUNCTION_MARKER(0x80011914u, "SLUS_005.10");
    header = 0x8006ECA0u + index * 12u;
    current = r_u32(header);
    next = r_u32(current);
    while (next != 0u)
    {
        sub_80045088(r_u32(current + 8u));
        sub_80045088(current);
        current = next;
        next = r_u32(next);
    }
    header = 0x8006ECA0u + index * 12u;
    w_u32(header, header + 4u);
    w_u32(header + 4u, 0u);
    w_u32(header + 8u, header);
    return header;
}

uint32 sub_8001A4F8(uint32 object, uint32 alternate)
{
    uint32 present, selected, result, x, y;
    FUNCTION_MARKER(0x8001A4F8u, "SLUS_005.10");
    present = r_u32(object + 16u);
    if (present != 0u)
    {
        if (alternate != 0u)
            w_u32(object + 48u, 0u);
        else
            w_u32(object + 48u, ((object + 72u) & 0xFFFFFFu) | 0x05000000u);
    }
    selected = object + 24u;
    if (alternate == 0u)
    {
        present = r_u32(object + 16u);
        selected = present != 0u ? object + 48u : object + 72u;
    }
    result = DrawOTagPSX(selected);
    x = r_u32(object + 8u);
    y = r_u32(object + 12u);
    sub_8004D524(x, y);
    return result;
}

uint32 sub_8001DE08(uint32 object)
{
    uint8 *frame;
    uint32 frame_address, selected, flags, result, model;
    uint32 first, second, third, fourth, x, y, page, brightness, limit;
    FUNCTION_MARKER(0x8001DE08u, "SLUS_005.10");
    result = r_u32(object) & 2u;
    if (result != 0u)
        return result;
    model = r_u32(object + 84u);
    result = sub_8001DB54(object + 36u, model);
    if (result == 0u)
        return result;
    frame_address = xport_guest_frame_acquire(96u);
    frame = (uint8 *)psx_addr(frame_address, 96u);
    selected = frame_address + 16u;
    (void)CompMatrixLV((MATRIX *)psx_addr(0x8006F680u, 32u), (MATRIX *)psx_addr(object + 16u, 32u), (MATRIX *)(frame + 16u));
    first = xport_load_le32(frame + 44u);
    if ((sint32)first > 0x3FFFFF)
    {
        result = 1u;
        goto frame_release;
    }
    flags = r_u32(object);
    if ((flags & 0x10u) != 0u)
    {
        if ((flags & 0x400u) != 0u)
        {
            first = r_u32(object + 16u);
            second = r_u32(object + 20u);
            third = r_u32(object + 24u);
            fourth = r_u32(object + 28u);
            xport_store_le32(frame + 48u, first);
            xport_store_le32(frame + 52u, second);
            xport_store_le32(frame + 56u, third);
            xport_store_le32(frame + 60u, fourth);
            first = r_u16(object + 32u);
            xport_store_le16(frame + 64u, (uint16)first);
            first = xport_load_le32(frame + 36u);
            second = xport_load_le32(frame + 40u);
            third = xport_load_le32(frame + 44u);
            xport_store_le32(frame + 68u, first);
            xport_store_le32(frame + 72u, second);
            xport_store_le32(frame + 76u, third);
            selected = frame_address + 48u;
        }
        else
        {
            first = r_u16(object + 34u);
            if (first != 0u)
                (void)sub_80016E64(frame_address + 16u);
            else
            {
                first = r_u32(0x8006F660u + 0u);
                second = r_u32(0x8006F660u + 4u);
                third = r_u32(0x8006F660u + 8u);
                xport_store_le32(frame + 16u, first);
                xport_store_le32(frame + 20u, second);
                xport_store_le32(frame + 24u, third);
                first = r_u32(0x8006F660u + 12u);
                second = r_u16(0x8006F660u + 16u);
                xport_store_le32(frame + 28u, first);
                xport_store_le16(frame + 32u, (uint16)second);
            }
        }
    }
    flags = r_u32(object);
    brightness = 64u;
    if ((flags & 0x2000u) != 0u)
    {
        x = r_u32(object + 72u);
        if ((sint32)x < 0)
            x += 0xFFFFu;
        y = r_u32(object + 80u);
        x = (uint32)((sint32)x >> 16);
        if ((sint32)y < 0)
            y += 0xFFFFu;
        y = (uint32)((sint32)y >> 16);
        page = r_u32(0x800911A0u + ((y >> 6) << 2) + ((x >> 6) << 7));
        first = r_u16(page + ((y & 63u) << 1) + ((x & 63u) << 7));
        brightness = (first & 0xF800u) >> 8;
    }
    SetBackColor((sint32)brightness, (sint32)brightness, (sint32)brightness);
    limit = r_u32(object + 108u);
    if (limit != 0u)
        first = xport_load_le32(frame + 44u);
    if (limit != 0u && (sint32)limit < (sint32)first)
    {
        model = r_u32(object + 104u);
        if (model != 0u)
        {
            flags = r_u32(object);
            if ((flags & 0x1010u) == 0x1000u)
            {
                if ((flags & 0x400u) != 0u)
                {
                    first = r_u32(0x800568B4u + 0u);
                    second = r_u32(0x800568B4u + 4u);
                    third = r_u32(0x800568B4u + 8u);
                    xport_store_le32(frame + 16u, first);
                    xport_store_le32(frame + 20u, second);
                    xport_store_le32(frame + 24u, third);
                    first = r_u32(0x800568B4u + 12u);
                    second = r_u16(0x800568B4u + 16u);
                    xport_store_le32(frame + 28u, first);
                    xport_store_le16(frame + 32u, (uint16)second);
                }
                else
                {
                    first = r_u16(object + 34u);
                    if (first != 0u)
                        (void)sub_80016E64(frame_address + 16u);
                    else
                    {
                        first = r_u32(0x8006F660u + 0u);
                        second = r_u32(0x8006F660u + 4u);
                        third = r_u32(0x8006F660u + 8u);
                        xport_store_le32(frame + 16u, first);
                        xport_store_le32(frame + 20u, second);
                        xport_store_le32(frame + 24u, third);
                        first = r_u32(0x8006F660u + 12u);
                        second = r_u16(0x8006F660u + 16u);
                        xport_store_le32(frame + 28u, first);
                        xport_store_le16(frame + 32u, (uint16)second);
                    }
                }
            }
            model = r_u32(object + 104u);
            page = r_u32(0x80065910u);
            sub_8001BE5C(model, selected, page);
        }
    }
    else
    {
        model = r_u32(object + 48u);
        if (model != 0u)
        {
            page = r_u32(0x80065910u);
            sub_8001BE5C(model, selected, page);
        }
        model = r_u32(object + 56u);
        if (model != 0u)
            (void)sub_8001DCC8(model, frame_address + 16u);
    }
    flags = r_u32(object);
    result = flags & 0x200u;
    if ((flags & 8u) != 0u)
    {
        if (result == 0u)
            (void)sub_8003E2FC(object);
        model = r_u32(object + 112u);
        result = sub_8003E520(model);
        goto frame_release;
    }
frame_release:
    xport_guest_frame_release(frame_address, 96u);
    return result;
}

uint32 sub_8001DB54(uint32 position, uint32 bound)
{
    uint32 first, second, third, x, y, z, tx, ty, tz, value;
    sint32 limit;
    FUNCTION_MARKER(0x8001DB54u, "SLUS_005.10");
    first = r_u32(0x8006F780u);
    second = r_u32(0x8006F784u);
    xport_gte_write_control(0u, first);
    xport_gte_write_control(1u, second);
    first = r_u32(0x8006F788u);
    second = r_u32(0x8006F78Cu);
    third = r_u32(0x8006F790u);
    xport_gte_write_control(2u, first);
    xport_gte_write_control(3u, second);
    xport_gte_write_control(4u, third);
    x = r_u32(position);
    tx = r_u32(0x8006F6F4u);
    y = r_u32(position + 4u);
    ty = r_u32(0x8006F6F8u);
    z = r_u32(position + 8u);
    tz = r_u32(0x8006F6FCu);
    xport_gte_write_data(9u, (uint32)((sint32)(x - tx) >> 8));
    xport_gte_write_data(10u, (uint32)((sint32)(y - ty) >> 8));
    xport_gte_write_data(11u, (uint32)((sint32)(z - tz) >> 8));
    xport_gte_mvmva(0x49E012u);
    limit = (sint32)bound >> 8;
    value = xport_gte_read_data(9u);
    if ((sint32)value >= limit) return 0u;
    value = xport_gte_read_data(10u);
    if ((sint32)value >= limit) return 0u;
    value = xport_gte_read_data(11u);
    return (sint32)value < limit;
}

uint32 sub_8001BE5C(uint32 model, uint32 matrix, uint32 ordering_table)
{
uint32 r[32], known = 0x10000071u, lo, x, y, value, target;
sint32 branch;
PsxGteSnapshot snapshot;
SVECTOR vectors[3]; uint32 colors[3]; sint32 screen[3], depths[3], flags;
FUNCTION_MARKER(0x8001BE5Cu, "SLUS_005.10");
r[0] = 0u; r[4] = model; r[5] = matrix; r[6] = ordering_table; r[28] = 0x80065304u; r[16] = r[4] + r[0]; known = (known & ~0x00010000u) | ((known & 0x00000011u) == 0x00000011u ? 0x00010000u : 0u);
r[25] = r_u16((r[16] + 0x00000000u)); known = (known & ~0x02000000u) | ((known & 0x00010000u) == 0x00010000u ? 0x02000000u : 0u); r[1] = r[25] & 0x0001u; known = (known & ~0x00000002u) | ((known & 0x02000000u) == 0x02000000u ? 0x00000002u : 0u);
branch = (r[1] == r[0]); if (branch) goto L_8001BF84;
r[24] = 0x80070000u; known = (known & ~0x01000000u) | ((known & 0x00000000u) == 0x00000000u ? 0x01000000u : 0u); r[24] = r[24] + 0xFFFFF700u; known = (known & ~0x01000000u) | ((known & 0x01000000u) == 0x01000000u ? 0x01000000u : 0u);
r[8] = r_u32((r[24] + 0x00000000u)); known = (known & ~0x00000100u) | ((known & 0x01000000u) == 0x01000000u ? 0x00000100u : 0u); r[9] = r_u32((r[24] + 0x00000004u)); known = (known & ~0x00000200u) | ((known & 0x01000000u) == 0x01000000u ? 0x00000200u : 0u);
r[10] = r_u32((r[24] + 0x00000008u)); known = (known & ~0x00000400u) | ((known & 0x01000000u) == 0x01000000u ? 0x00000400u : 0u); r[11] = r_u32((r[24] + 0x0000000Cu)); known = (known & ~0x00000800u) | ((known & 0x01000000u) == 0x01000000u ? 0x00000800u : 0u);
r[12] = r_u32((r[24] + 0x00000010u)); known = (known & ~0x00001000u) | ((known & 0x01000000u) == 0x01000000u ? 0x00001000u : 0u); xport_gte_write_control(0u, r[8]);
xport_gte_write_control(1u, r[9]); xport_gte_write_control(2u, r[10]);
xport_gte_write_control(3u, r[11]); xport_gte_write_control(4u, r[12]);
r[8] = (uint32)(sint32)(sint16)r_u16((r[5] + 0x00000000u)); known = (known & ~0x00000100u) | ((known & 0x00000020u) == 0x00000020u ? 0x00000100u : 0u); r[9] = (uint32)(sint32)(sint16)r_u16((r[5] + 0x00000006u)); known = (known & ~0x00000200u) | ((known & 0x00000020u) == 0x00000020u ? 0x00000200u : 0u);
r[10] = (uint32)(sint32)(sint16)r_u16((r[5] + 0x0000000Cu)); known = (known & ~0x00000400u) | ((known & 0x00000020u) == 0x00000020u ? 0x00000400u : 0u); xport_gte_write_data(9u, r[8]);
xport_gte_write_data(10u, r[9]); xport_gte_write_data(11u, r[10]);
xport_gte_mvmva(0x49E012u); r[11] = (uint32)(sint32)(sint16)r_u16((r[5] + 0x00000002u)); known = (known & ~0x00000800u) | ((known & 0x00000020u) == 0x00000020u ? 0x00000800u : 0u);
r[12] = (uint32)(sint32)(sint16)r_u16((r[5] + 0x00000008u)); known = (known & ~0x00001000u) | ((known & 0x00000020u) == 0x00000020u ? 0x00001000u : 0u); r[13] = (uint32)(sint32)(sint16)r_u16((r[5] + 0x0000000Eu)); known = (known & ~0x00002000u) | ((known & 0x00000020u) == 0x00000020u ? 0x00002000u : 0u);
r[8] = xport_gte_read_data(9u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); r[9] = xport_gte_read_data(10u); known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
r[10] = xport_gte_read_data(11u); known = (known & ~0x00000400u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000400u : 0u); xport_gte_write_data(9u, r[11]);
xport_gte_write_data(10u, r[12]); xport_gte_write_data(11u, r[13]);
xport_gte_mvmva(0x49E012u); r[14] = (uint32)(sint32)(sint16)r_u16((r[5] + 0x00000004u)); known = (known & ~0x00004000u) | ((known & 0x00000020u) == 0x00000020u ? 0x00004000u : 0u);
r[15] = (uint32)(sint32)(sint16)r_u16((r[5] + 0x0000000Au)); known = (known & ~0x00008000u) | ((known & 0x00000020u) == 0x00000020u ? 0x00008000u : 0u); r[24] = (uint32)(sint32)(sint16)r_u16((r[5] + 0x00000010u)); known = (known & ~0x01000000u) | ((known & 0x00000020u) == 0x00000020u ? 0x01000000u : 0u);
r[11] = xport_gte_read_data(9u); known = (known & ~0x00000800u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000800u : 0u); r[12] = xport_gte_read_data(10u); known = (known & ~0x00001000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00001000u : 0u);
r[13] = xport_gte_read_data(11u); known = (known & ~0x00002000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00002000u : 0u); xport_gte_write_data(9u, r[14]);
xport_gte_write_data(10u, r[15]); xport_gte_write_data(11u, r[24]);
xport_gte_mvmva(0x49E012u); r[11] = (r[11] << 16u); known = (known & ~0x00000800u) | ((known & 0x00000800u) == 0x00000800u ? 0x00000800u : 0u);
x = r[8]; y = r[11]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001BF48u); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000900u) == 0x00000900u ? 0x00000100u : 0u);
psx_gte_snapshot(&snapshot); snapshot.light.m[0][0] = (sint16)r[8]; snapshot.light.m[0][1] = (sint16)(r[8] >> 16u); SetLightMatrix(&snapshot.light); r[13] = (r[13] << 16u); known = (known & ~0x00002000u) | ((known & 0x00002000u) == 0x00002000u ? 0x00002000u : 0u);
x = r[10]; y = r[13]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001BF54u); r[10] = value; known = (known & ~0x00000400u) | ((known & 0x00002400u) == 0x00002400u ? 0x00000400u : 0u);
psx_gte_snapshot(&snapshot); snapshot.light.m[2][0] = (sint16)r[10]; snapshot.light.m[2][1] = (sint16)(r[10] >> 16u); SetLightMatrix(&snapshot.light); r[14] = xport_gte_read_data(9u); known = (known & ~0x00004000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00004000u : 0u);
r[15] = xport_gte_read_data(10u); known = (known & ~0x00008000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00008000u : 0u); r[24] = xport_gte_read_data(11u); known = (known & ~0x01000000u) | ((known & 0x00000000u) == 0x00000000u ? 0x01000000u : 0u);
r[9] = (r[9] << 16u); known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); x = r[9]; y = r[14]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001BF6Cu);
r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00004200u) == 0x00004200u ? 0x00000200u : 0u); psx_gte_snapshot(&snapshot); snapshot.light.m[0][2] = (sint16)r[9]; snapshot.light.m[1][0] = (sint16)(r[9] >> 16u); SetLightMatrix(&snapshot.light);
r[15] = (r[15] << 16u); known = (known & ~0x00008000u) | ((known & 0x00008000u) == 0x00008000u ? 0x00008000u : 0u); x = r[12]; y = r[15]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001BF78u);
r[12] = value; known = (known & ~0x00001000u) | ((known & 0x00009000u) == 0x00009000u ? 0x00001000u : 0u); psx_gte_snapshot(&snapshot); snapshot.light.m[1][1] = (sint16)r[12]; snapshot.light.m[1][2] = (sint16)(r[12] >> 16u); SetLightMatrix(&snapshot.light);
psx_gte_snapshot(&snapshot); snapshot.light.m[2][2] = (sint16)r[24]; SetLightMatrix(&snapshot.light); L_8001BF84:;
r[8] = r_u32((r[5] + 0x00000000u)); known = (known & ~0x00000100u) | ((known & 0x00000020u) == 0x00000020u ? 0x00000100u : 0u); r[9] = r_u32((r[5] + 0x00000004u)); known = (known & ~0x00000200u) | ((known & 0x00000020u) == 0x00000020u ? 0x00000200u : 0u);
r[10] = r_u32((r[5] + 0x00000008u)); known = (known & ~0x00000400u) | ((known & 0x00000020u) == 0x00000020u ? 0x00000400u : 0u); r[11] = r_u32((r[5] + 0x0000000Cu)); known = (known & ~0x00000800u) | ((known & 0x00000020u) == 0x00000020u ? 0x00000800u : 0u);
r[12] = r_u32((r[5] + 0x00000010u)); known = (known & ~0x00001000u) | ((known & 0x00000020u) == 0x00000020u ? 0x00001000u : 0u); xport_gte_write_control(0u, r[8]);
xport_gte_write_control(1u, r[9]); xport_gte_write_control(2u, r[10]);
xport_gte_write_control(3u, r[11]); xport_gte_write_control(4u, r[12]);
r[20] = (uint32)(sint32)(sint16)r_u16((r[16] + 0x00000026u)); known = (known & ~0x00100000u) | ((known & 0x00010000u) == 0x00010000u ? 0x00100000u : 0u); r[11] = r[0] + 0x00000010u; known = (known & ~0x00000800u) | ((known & 0x00000001u) == 0x00000001u ? 0x00000800u : 0u);
x = r[11]; y = r[20]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001BFB4u); r[11] = value; known = (known & ~0x00000800u) | ((known & 0x00100800u) == 0x00100800u ? 0x00000800u : 0u);
r[1] = r[25] & 0x0002u; known = (known & ~0x00000002u) | ((known & 0x02000000u) == 0x02000000u ? 0x00000002u : 0u); branch = (r[1] == r[0]);
x = r[20]; y = 0xFFFFFFF9u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001BFC0u); r[20] = value; known = (known & ~0x00100000u) | ((known & 0x00100000u) == 0x00100000u ? 0x00100000u : 0u);
if (branch) goto L_8001BFC8; r[20] = r[0] + 0x00000010u; known = (known & ~0x00100000u) | ((known & 0x00000001u) == 0x00000001u ? 0x00100000u : 0u);
L_8001BFC8:; r[8] = r_u32((r[5] + 0x00000014u)); known = (known & ~0x00000100u) | ((known & 0x00000020u) == 0x00000020u ? 0x00000100u : 0u);
r[9] = r_u32((r[5] + 0x00000018u)); known = (known & ~0x00000200u) | ((known & 0x00000020u) == 0x00000020u ? 0x00000200u : 0u); r[10] = r_u32((r[5] + 0x0000001Cu)); known = (known & ~0x00000400u) | ((known & 0x00000020u) == 0x00000020u ? 0x00000400u : 0u);
r[8] = ((sint32)r[8] >> (r[11] & 31u)); known = (known & ~0x00000100u) | ((known & 0x00000900u) == 0x00000900u ? 0x00000100u : 0u); r[9] = ((sint32)r[9] >> (r[11] & 31u)); known = (known & ~0x00000200u) | ((known & 0x00000A00u) == 0x00000A00u ? 0x00000200u : 0u);
r[10] = ((sint32)r[10] >> (r[11] & 31u)); known = (known & ~0x00000400u) | ((known & 0x00000C00u) == 0x00000C00u ? 0x00000400u : 0u); xport_gte_write_control(5u, r[8]);
xport_gte_write_control(6u, r[9]); xport_gte_write_control(7u, r[10]);
r[1] = r[25] & 0x0004u; known = (known & ~0x00000002u) | ((known & 0x02000000u) == 0x02000000u ? 0x00000002u : 0u); r[22] = 0x80020000u; known = (known & ~0x00400000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00400000u : 0u);
r[22] = r[22] + 0xFFFFCD60u; known = (known & ~0x00400000u) | ((known & 0x00400000u) == 0x00400000u ? 0x00400000u : 0u); branch = (r[1] == r[0]);
if (branch) goto L_8001C004; x = r[22]; y = 0x00000040u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C000u);
r[22] = value; known = (known & ~0x00400000u) | ((known & 0x00400000u) == 0x00400000u ? 0x00400000u : 0u); L_8001C004:;
r[17] = r[6] + r[0]; known = (known & ~0x00020000u) | ((known & 0x00000041u) == 0x00000041u ? 0x00020000u : 0u); r[18] = 0x80060000u; known = (known & ~0x00040000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00040000u : 0u);
r[18] = r_u32((r[18] + 0x00005308u)); known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); r[8] = (uint32)(sint32)(sint16)r_u16((r[16] + 0x00000028u)); known = (known & ~0x00000100u) | ((known & 0x00010000u) == 0x00010000u ? 0x00000100u : 0u);
r[18] = (r[18] << 2u); known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); x = r[18]; y = r[16]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C018u);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00050000u) == 0x00050000u ? 0x00040000u : 0u); r[18] = r_u32((r[18] + 0x0000001Cu)); known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u);
r[8] = (r[8] << 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); branch = (r[18] != r[0]);
x = r[17]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C028u); r[17] = value; known = (known & ~0x00020000u) | ((known & 0x00020100u) == 0x00020100u ? 0x00020000u : 0u);
if (branch) goto L_8001C068; r[4] = r_u16((r[16] + 0x00000002u)); known = (known & ~0x00000010u) | ((known & 0x00010000u) == 0x00010000u ? 0x00000010u : 0u);
r[31] = 0x8001C038u; known |= 0x80000000u; r[19] = r[4] + r[0]; known = (known & ~0x00080000u) | ((known & 0x00000011u) == 0x00000011u ? 0x00080000u : 0u);
r[2] = sub_800116F4(r[4]); known = (known & 0xD0FF0001u) | 4u; r[8] = 0x80060000u; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
r[8] = r_u32((r[8] + 0x00005308u)); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[4] = r[2] + r[0]; known = (known & ~0x00000010u) | ((known & 0x00000005u) == 0x00000005u ? 0x00000010u : 0u);
r[6] = r[19] + r[0]; known = (known & ~0x00000040u) | ((known & 0x00080001u) == 0x00080001u ? 0x00000040u : 0u); r[8] = (r[8] << 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
x = r[16]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C04Cu); r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00010100u) == 0x00010100u ? 0x00040000u : 0u);
w_u32((r[18] + 0x0000001Cu), r[4]); r[8] = r[8] ^ 0x0004u; known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
x = r[16]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C058u); r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00010100u) == 0x00010100u ? 0x00040000u : 0u);
r[5] = r_u32((r[18] + 0x0000001Cu)); known = (known & ~0x00000020u) | ((known & 0x00040000u) == 0x00040000u ? 0x00000020u : 0u); r[31] = 0x8001C068u; known |= 0x80000000u;
r[18] = r[4] + r[0]; known = (known & ~0x00040000u) | ((known & 0x00000011u) == 0x00000011u ? 0x00040000u : 0u); r[2] = sub_80044C44(r[4], r[5], r[6]); known = (known & 0xD0FF0001u) | 4u;
L_8001C068:; r[19] = r_u32((r[16] + 0x00000018u)); known = (known & ~0x00080000u) | ((known & 0x00010000u) == 0x00010000u ? 0x00080000u : 0u);
r[21] = r_u32((r[16] + 0x00000014u)); known = (known & ~0x00200000u) | ((known & 0x00010000u) == 0x00010000u ? 0x00200000u : 0u); L_8001C070:;
r[2] = r_u32((r[16] + 0x00000008u)); known = (known & ~0x00000004u) | ((known & 0x00010000u) == 0x00010000u ? 0x00000004u : 0u); r[3] = r_u32((r[16] + 0x00000010u)); known = (known & ~0x00000008u) | ((known & 0x00010000u) == 0x00010000u ? 0x00000008u : 0u);
L_8001C078:; branch = (r[21] == r[0]);
r[9] = r_u32((r[19] + 0x00000004u)); known = (known & ~0x00000200u) | ((known & 0x00080000u) == 0x00080000u ? 0x00000200u : 0u); if (branch) goto L_8001CD38;
r[11] = r_u32((r[19] + 0x00000008u)); known = (known & ~0x00000800u) | ((known & 0x00080000u) == 0x00080000u ? 0x00000800u : 0u); r[10] = (r[9] >> 16u); known = (known & ~0x00000400u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000400u : 0u);
r[9] = r[9] & 0xFFFFu; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); r[12] = (r[11] >> 16u); known = (known & ~0x00001000u) | ((known & 0x00000800u) == 0x00000800u ? 0x00001000u : 0u);
r[11] = r[11] & 0xFFFFu; known = (known & ~0x00000800u) | ((known & 0x00000800u) == 0x00000800u ? 0x00000800u : 0u); r[9] = r[9] + r[2]; known = (known & ~0x00000200u) | ((known & 0x00000204u) == 0x00000204u ? 0x00000200u : 0u);
r[10] = r[10] + r[2]; known = (known & ~0x00000400u) | ((known & 0x00000404u) == 0x00000404u ? 0x00000400u : 0u); r[11] = r[11] + r[2]; known = (known & ~0x00000800u) | ((known & 0x00000804u) == 0x00000804u ? 0x00000800u : 0u);
xport_gte_write_data(0u, r_u32((r[9] + 0x00000000u))); xport_gte_write_data(1u, r_u32((r[9] + 0x00000004u)));
xport_gte_write_data(2u, r_u32((r[10] + 0x00000000u))); xport_gte_write_data(3u, r_u32((r[10] + 0x00000004u)));
xport_gte_write_data(4u, r_u32((r[11] + 0x00000000u))); xport_gte_write_data(5u, r_u32((r[11] + 0x00000004u)));
r[8] = r_u32((r[19] + 0x00000000u)); known = (known & ~0x00000100u) | ((known & 0x00080000u) == 0x00080000u ? 0x00000100u : 0u); x = r[21]; y = 0xFFFFFFFFu; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C0BCu);
r[21] = value; known = (known & ~0x00200000u) | ((known & 0x00200000u) == 0x00200000u ? 0x00200000u : 0u); psx_gte_snapshot(&snapshot); vectors[0].vx = snapshot.v0[0]; vectors[0].vy = snapshot.v0[1]; vectors[0].vz = snapshot.v0[2]; vectors[1].vx = snapshot.v1[0]; vectors[1].vy = snapshot.v1[1]; vectors[1].vz = snapshot.v1[2]; vectors[2].vx = snapshot.v2[0]; vectors[2].vy = snapshot.v2[1]; vectors[2].vz = snapshot.v2[2]; gte_project3_full_depth(vectors, screen, depths, &flags); xport_gte_complete_rtpt();
r[1] = (r[8] >> 24u); known = (known & ~0x00000002u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000002u : 0u); r[1] = r[1] & 0x003Cu; known = (known & ~0x00000002u) | ((known & 0x00000002u) == 0x00000002u ? 0x00000002u : 0u);
x = r[1]; y = r[22]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C0CCu); r[1] = value; known = (known & ~0x00000002u) | ((known & 0x00400002u) == 0x00400002u ? 0x00000002u : 0u);
r[1] = r_u32((r[1] + 0x00000000u)); known = (known & ~0x00000002u) | ((known & 0x00000002u) == 0x00000002u ? 0x00000002u : 0u); r[6] = r[18] + r[0]; known = (known & ~0x00000040u) | ((known & 0x00040001u) == 0x00040001u ? 0x00000040u : 0u);
target = r[1]; r[7] = r[19] + r[0]; known = (known & ~0x00000080u) | ((known & 0x00080001u) == 0x00080001u ? 0x00000080u : 0u);
switch (target) { case 0x8001C100u: goto L_8001C100;
case 0x8001C134u: goto L_8001C134; case 0x8001C168u: goto L_8001C168;
case 0x8001C19Cu: goto L_8001C19C; case 0x8001C22Cu: goto L_8001C22C;
case 0x8001C280u: goto L_8001C280; case 0x8001C2D4u: goto L_8001C2D4;
case 0x8001C2F8u: goto L_8001C2F8; case 0x8001C3A0u: goto L_8001C3A0;
case 0x8001C3D4u: goto L_8001C3D4; case 0x8001C480u: goto L_8001C480;
case 0x8001C4B4u: goto L_8001C4B4; case 0x8001C560u: goto L_8001C560;
case 0x8001C5ACu: goto L_8001C5AC; case 0x8001C630u: goto L_8001C630;
case 0x8001C71Cu: goto L_8001C71C; case 0x8001CB8Cu: goto L_8001CB8C;
case 0x8001CBD8u: goto L_8001CBD8; case 0x8001CD38u: goto L_8001CD38;
default: return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001C0D8u, target, known, r); }
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
x = r[18]; y = 0x00000014u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C0E4u); r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u);
branch = ((sint32)r[9] < 0); x = r[19]; y = 0x0000000Cu; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C0ECu);
r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u); if (branch) return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001C0E8u, 0x8001CE24u, known, r);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x0000000Cu), (uint32)snapshot.sxy[1]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), (uint32)snapshot.sxy[2]); goto L_8001CC64;
L_8001C100:; psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); x = r[18]; y = 0x00000014u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C104u);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); branch = ((sint32)r[9] < 0);
x = r[19]; y = 0x0000000Cu; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C10Cu); r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u);
if (branch) return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001C108u, 0x8001CE10u, known, r); psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]);
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
branch = ((sint32)r[9] <= 0); if (branch) goto L_8001C078;
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x0000000Cu), (uint32)snapshot.sxy[1]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), (uint32)snapshot.sxy[2]); goto L_8001CC64;
L_8001C134:; psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); x = r[18]; y = 0x00000028u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C138u);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); branch = ((sint32)r[9] < 0);
x = r[19]; y = 0x0000001Cu; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C140u); r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u);
if (branch) return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001C13Cu, 0x8001D230u, known, r); psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]);
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
branch = ((sint32)r[9] <= 0); if (branch) goto L_8001C078;
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000014u), (uint32)snapshot.sxy[1]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000020u), (uint32)snapshot.sxy[2]); goto L_8001CC64;
L_8001C168:; psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); x = r[18]; y = 0x0000001Cu; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C16Cu);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); branch = ((sint32)r[9] < 0);
x = r[19]; y = 0x00000014u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C174u); r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u);
if (branch) return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001C170u, 0x8001CF68u, known, r); psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]);
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
branch = ((sint32)r[9] <= 0); if (branch) goto L_8001C078;
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), (uint32)snapshot.sxy[1]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000018u), (uint32)snapshot.sxy[2]); goto L_8001CC64;
L_8001C19C:; psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); x = r[18]; y = 0x00000028u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C1A0u);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); branch = ((sint32)r[9] < 0);
x = r[19]; y = 0x0000001Cu; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C1A8u); r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u);
if (branch) goto L_8001C078; psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]);
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
branch = ((sint32)r[9] <= 0); if (branch) goto L_8001C078;
r[9] = r_u16((r[7] + 0x00000012u)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u); r[8] = r[9] & 0x3FFFu; known = (known & ~0x00000100u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000100u : 0u);
r[8] = (r[8] << 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[8] = r[8] + r[16]; known = (known & ~0x00000100u) | ((known & 0x00010100u) == 0x00010100u ? 0x00000100u : 0u);
r[8] = r_u32((r[8] + 0x0000002Cu)); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[9] = r[9] & 0xC000u; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u);
r[10] = r_u32((r[8] + 0x00000008u)); known = (known & ~0x00000400u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000400u : 0u); r[9] = (r[9] >> 9u); known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u);
r[11] = (r[10] >> 16u); known = (known & ~0x00000800u) | ((known & 0x00000400u) == 0x00000400u ? 0x00000800u : 0u); r[10] = r[10] | r[9]; known = (known & ~0x00000400u) | ((known & 0x00000600u) == 0x00000600u ? 0x00000400u : 0u);
w_u16((r[6] + 0x0000001Au), r[10]); w_u16((r[6] + 0x0000000Eu), r[11]);
r[8] = r_u16((r[8] + 0x00000006u)); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[9] = r_u16((r[7] + 0x0000000Cu)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u);
r[10] = r_u16((r[7] + 0x0000000Eu)); known = (known & ~0x00000400u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000400u : 0u); r[11] = r_u16((r[7] + 0x00000010u)); known = (known & ~0x00000800u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000800u : 0u);
x = r[9]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C204u); r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000200u : 0u);
x = r[10]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C208u); r[10] = value; known = (known & ~0x00000400u) | ((known & 0x00000500u) == 0x00000500u ? 0x00000400u : 0u);
x = r[11]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C20Cu); r[11] = value; known = (known & ~0x00000800u) | ((known & 0x00000900u) == 0x00000900u ? 0x00000800u : 0u);
w_u16((r[6] + 0x0000000Cu), r[9]); w_u16((r[6] + 0x00000018u), r[10]);
w_u16((r[6] + 0x00000024u), r[11]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000014u), (uint32)snapshot.sxy[1]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000020u), (uint32)snapshot.sxy[2]);
goto L_8001CC64; L_8001C22C:;
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
x = r[18]; y = 0x00000014u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C230u); r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u);
branch = ((sint32)r[9] < 0); x = r[19]; y = 0x0000000Cu; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C238u);
r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u); if (branch) return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001C234u, 0x8001CDE0u, known, r);
psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]); psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); r[10] = 0x10000000u; known = (known & ~0x00000400u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000400u : 0u);
branch = ((sint32)r[9] <= 0); x = r[8]; y = r[10]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C24Cu);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000500u) == 0x00000500u ? 0x00000100u : 0u); if (branch) goto L_8001C078;
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x0000000Cu), (uint32)snapshot.sxy[1]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), (uint32)snapshot.sxy[2]); xport_gte_write_data(6u, r[8]);
x = r[12]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C260u); r[12] = value; known = (known & ~0x00001000u) | ((known & 0x00001008u) == 0x00001008u ? 0x00001000u : 0u);
xport_gte_write_data(0u, r_u32((r[12] + 0x00000000u))); xport_gte_write_data(1u, r_u32((r[12] + 0x00000004u)));
psx_gte_snapshot(&snapshot); vectors[0].vx = snapshot.v0[0]; vectors[0].vy = snapshot.v0[1]; vectors[0].vz = snapshot.v0[2]; (void)gte_normal_color_col(&vectors[0], snapshot.rgbc); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000004u), snapshot.rgb[2]);
goto L_8001CC64; L_8001C280:;
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
x = r[18]; y = 0x00000020u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C284u); r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u);
branch = ((sint32)r[9] < 0); x = r[19]; y = 0x00000014u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C28Cu);
r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u); if (branch) return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001C288u, 0x8001D080u, known, r);
psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]); psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); r[10] = 0x10000000u; known = (known & ~0x00000400u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000400u : 0u);
branch = ((sint32)r[9] <= 0); x = r[8]; y = r[10]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C2A0u);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000500u) == 0x00000500u ? 0x00000100u : 0u); if (branch) goto L_8001C078;
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), (uint32)snapshot.sxy[1]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000018u), (uint32)snapshot.sxy[2]); xport_gte_write_data(6u, r[8]);
x = r[12]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C2B4u); r[12] = value; known = (known & ~0x00001000u) | ((known & 0x00001008u) == 0x00001008u ? 0x00001000u : 0u);
xport_gte_write_data(0u, r_u32((r[12] + 0x00000000u))); xport_gte_write_data(1u, r_u32((r[12] + 0x00000004u)));
psx_gte_snapshot(&snapshot); vectors[0].vx = snapshot.v0[0]; vectors[0].vy = snapshot.v0[1]; vectors[0].vz = snapshot.v0[2]; (void)gte_normal_color_col(&vectors[0], snapshot.rgbc); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000004u), snapshot.rgb[2]);
goto L_8001CC64; L_8001C2D4:;
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
x = r[18]; y = 0x00000010u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C2D8u); r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u);
branch = ((sint32)r[9] < 0); x = r[19]; y = 0x0000000Cu; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C2E0u);
r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u); if (branch) goto L_8001C078;
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x0000000Cu), (uint32)snapshot.sxy[1]);
psx_gte_snapshot(&snapshot); r[8] = snapshot.sz[1] & 0xFFFFu; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
r[8] = (r[8] >> 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); goto L_8001CC74;
L_8001C2F8:; psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); x = r[18]; y = 0x00000020u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C2FCu);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); branch = ((sint32)r[9] < 0);
x = r[19]; y = 0x00000014u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C304u); r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u);
if (branch) goto L_8001C078; psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]);
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
r[10] = 0x08000000u; known = (known & ~0x00000400u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000400u : 0u); branch = ((sint32)r[9] <= 0);
x = r[8]; y = r[10]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C318u); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000500u) == 0x00000500u ? 0x00000100u : 0u);
if (branch) goto L_8001C078; xport_gte_write_data(6u, r[8]);
x = r[12]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C320u); r[12] = value; known = (known & ~0x00001000u) | ((known & 0x00001008u) == 0x00001008u ? 0x00001000u : 0u);
xport_gte_write_data(0u, r_u32((r[12] + 0x00000000u))); xport_gte_write_data(1u, r_u32((r[12] + 0x00000004u)));
r[9] = r_u16((r[7] + 0x00000012u)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u); psx_gte_snapshot(&snapshot); vectors[0].vx = snapshot.v0[0]; vectors[0].vy = snapshot.v0[1]; vectors[0].vz = snapshot.v0[2]; (void)gte_normal_color_col(&vectors[0], snapshot.rgbc);
r[8] = r[9] & 0x3FFFu; known = (known & ~0x00000100u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000100u : 0u); r[8] = (r[8] << 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[8] = r[8] + r[16]; known = (known & ~0x00000100u) | ((known & 0x00010100u) == 0x00010100u ? 0x00000100u : 0u); r[8] = r_u32((r[8] + 0x0000002Cu)); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[9] = r[9] & 0xC000u; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); r[10] = r_u32((r[8] + 0x00000008u)); known = (known & ~0x00000400u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000400u : 0u);
r[9] = (r[9] >> 9u); known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); r[11] = (r[10] >> 16u); known = (known & ~0x00000800u) | ((known & 0x00000400u) == 0x00000400u ? 0x00000800u : 0u);
r[10] = r[10] | r[9]; known = (known & ~0x00000400u) | ((known & 0x00000600u) == 0x00000600u ? 0x00000400u : 0u); w_u16((r[6] + 0x00000016u), r[10]);
w_u16((r[6] + 0x0000000Eu), r[11]); r[8] = r_u16((r[8] + 0x00000006u)); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[9] = r_u16((r[7] + 0x0000000Cu)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u); r[10] = r_u16((r[7] + 0x0000000Eu)); known = (known & ~0x00000400u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000400u : 0u);
r[11] = r_u16((r[7] + 0x00000010u)); known = (known & ~0x00000800u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000800u : 0u); x = r[9]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C374u);
r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000200u : 0u); x = r[10]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C378u);
r[10] = value; known = (known & ~0x00000400u) | ((known & 0x00000500u) == 0x00000500u ? 0x00000400u : 0u); x = r[11]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C37Cu);
r[11] = value; known = (known & ~0x00000800u) | ((known & 0x00000900u) == 0x00000900u ? 0x00000800u : 0u); w_u16((r[6] + 0x0000000Cu), r[9]);
w_u16((r[6] + 0x00000014u), r[10]); w_u16((r[6] + 0x0000001Cu), r[11]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), (uint32)snapshot.sxy[1]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000018u), (uint32)snapshot.sxy[2]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000004u), snapshot.rgb[2]);
goto L_8001CC64; L_8001C3A0:;
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
x = r[18]; y = 0x0000001Cu; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C3A4u); r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u);
branch = ((sint32)r[9] < 0); x = r[19]; y = 0x00000010u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C3ACu);
r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u); if (branch) return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001C3A8u, 0x8001CF68u, known, r);
psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]); psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); branch = ((sint32)r[9] <= 0);
if (branch) goto L_8001C078; psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), (uint32)snapshot.sxy[1]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000018u), (uint32)snapshot.sxy[2]);
goto L_8001CC64; L_8001C3D4:;
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
x = r[18]; y = 0x0000001Cu; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C3D8u); r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u);
branch = ((sint32)r[9] < 0); x = r[19]; y = 0x00000010u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C3E0u);
r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u); if (branch) return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001C3DCu, 0x8001CF14u, known, r);
psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]); psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); r[10] = 0x10000000u; known = (known & ~0x00000400u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000400u : 0u);
branch = ((sint32)r[9] <= 0); x = r[8]; y = r[10]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C3F4u);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000500u) == 0x00000500u ? 0x00000100u : 0u); if (branch) goto L_8001C078;
psx_gte_snapshot(&snapshot); (void)AverageZ3((sint32)snapshot.sz[1], (sint32)snapshot.sz[2], (sint32)snapshot.sz[3]); xport_gte_write_data(6u, r[8]);
r[9] = r_u32((r[7] + 0x0000000Cu)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u); x = r[12]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C404u);
r[12] = value; known = (known & ~0x00001000u) | ((known & 0x00001008u) == 0x00001008u ? 0x00001000u : 0u); r[10] = (r[9] >> 16u); known = (known & ~0x00000400u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000400u : 0u);
r[9] = r[9] & 0xFFFFu; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); x = r[9]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C410u);
r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000208u) == 0x00000208u ? 0x00000200u : 0u); x = r[10]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C414u);
r[10] = value; known = (known & ~0x00000400u) | ((known & 0x00000408u) == 0x00000408u ? 0x00000400u : 0u); xport_gte_write_data(0u, r_u32((r[12] + 0x00000000u)));
xport_gte_write_data(1u, r_u32((r[12] + 0x00000004u))); xport_gte_write_data(2u, r_u32((r[9] + 0x00000000u)));
xport_gte_write_data(3u, r_u32((r[9] + 0x00000004u))); xport_gte_write_data(4u, r_u32((r[10] + 0x00000000u)));
xport_gte_write_data(5u, r_u32((r[10] + 0x00000004u))); psx_gte_snapshot(&snapshot);
r[8] = snapshot.otz & 0xFFFFu; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); psx_gte_snapshot(&snapshot); vectors[0].vx = snapshot.v0[0]; vectors[0].vy = snapshot.v0[1]; vectors[0].vz = snapshot.v0[2]; vectors[1].vx = snapshot.v1[0]; vectors[1].vy = snapshot.v1[1]; vectors[1].vz = snapshot.v1[2]; vectors[2].vx = snapshot.v2[0]; vectors[2].vy = snapshot.v2[1]; vectors[2].vz = snapshot.v2[2]; gte_normal_color_col3(vectors, snapshot.rgbc, colors);
r[8] = (r[8] >> (r[20] & 31u)); known = (known & ~0x00000100u) | ((known & 0x00100100u) == 0x00100100u ? 0x00000100u : 0u); r[8] = (r[8] << 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
x = r[8]; y = r[17]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C444u); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00020100u) == 0x00020100u ? 0x00000100u : 0u);
r[1] = 0x06000000u; known = (known & ~0x00000002u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000002u : 0u); r[9] = (r[6] << 8u); known = (known & ~0x00000200u) | ((known & 0x00000040u) == 0x00000040u ? 0x00000200u : 0u);
r[9] = (r[9] >> 8u); known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); r[10] = r_u32((r[8] + 0x00000000u)); known = (known & ~0x00000400u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000400u : 0u);
w_u32((r[8] + 0x00000000u), r[9]); x = r[10]; y = r[1]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C45Cu);
r[10] = value; known = (known & ~0x00000400u) | ((known & 0x00000402u) == 0x00000402u ? 0x00000400u : 0u); w_u32((r[6] + 0x00000000u), r[10]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), (uint32)snapshot.sxy[1]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000018u), (uint32)snapshot.sxy[2]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000004u), snapshot.rgb[0]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x0000000Cu), snapshot.rgb[1]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000014u), snapshot.rgb[2]);
goto L_8001C078; L_8001C480:;
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
x = r[18]; y = 0x00000028u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C484u); r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u);
branch = ((sint32)r[9] < 0); x = r[19]; y = 0x00000018u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C48Cu);
r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u); if (branch) return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001C488u, 0x8001D230u, known, r);
psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]); psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); branch = ((sint32)r[9] <= 0);
if (branch) goto L_8001C078; psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000014u), (uint32)snapshot.sxy[1]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000020u), (uint32)snapshot.sxy[2]);
goto L_8001CC64; L_8001C4B4:;
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
x = r[18]; y = 0x00000028u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C4B8u); r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u);
branch = ((sint32)r[9] < 0); x = r[19]; y = 0x00000018u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C4C0u);
r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u); if (branch) return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001C4BCu, 0x8001D1DCu, known, r);
psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]); psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); r[10] = 0x10000000u; known = (known & ~0x00000400u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000400u : 0u);
branch = ((sint32)r[9] <= 0); x = r[8]; y = r[10]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C4D4u);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000500u) == 0x00000500u ? 0x00000100u : 0u); if (branch) goto L_8001C078;
psx_gte_snapshot(&snapshot); (void)AverageZ3((sint32)snapshot.sz[1], (sint32)snapshot.sz[2], (sint32)snapshot.sz[3]); xport_gte_write_data(6u, r[8]);
r[9] = r_u32((r[7] + 0x0000000Cu)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u); x = r[12]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C4E4u);
r[12] = value; known = (known & ~0x00001000u) | ((known & 0x00001008u) == 0x00001008u ? 0x00001000u : 0u); r[10] = (r[9] >> 16u); known = (known & ~0x00000400u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000400u : 0u);
r[9] = r[9] & 0xFFFFu; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); x = r[9]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C4F0u);
r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000208u) == 0x00000208u ? 0x00000200u : 0u); x = r[10]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C4F4u);
r[10] = value; known = (known & ~0x00000400u) | ((known & 0x00000408u) == 0x00000408u ? 0x00000400u : 0u); xport_gte_write_data(0u, r_u32((r[12] + 0x00000000u)));
xport_gte_write_data(1u, r_u32((r[12] + 0x00000004u))); xport_gte_write_data(2u, r_u32((r[9] + 0x00000000u)));
xport_gte_write_data(3u, r_u32((r[9] + 0x00000004u))); xport_gte_write_data(4u, r_u32((r[10] + 0x00000000u)));
xport_gte_write_data(5u, r_u32((r[10] + 0x00000004u))); psx_gte_snapshot(&snapshot);
r[8] = snapshot.otz & 0xFFFFu; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); psx_gte_snapshot(&snapshot); vectors[0].vx = snapshot.v0[0]; vectors[0].vy = snapshot.v0[1]; vectors[0].vz = snapshot.v0[2]; vectors[1].vx = snapshot.v1[0]; vectors[1].vy = snapshot.v1[1]; vectors[1].vz = snapshot.v1[2]; vectors[2].vx = snapshot.v2[0]; vectors[2].vy = snapshot.v2[1]; vectors[2].vz = snapshot.v2[2]; gte_normal_color_col3(vectors, snapshot.rgbc, colors);
r[8] = (r[8] >> (r[20] & 31u)); known = (known & ~0x00000100u) | ((known & 0x00100100u) == 0x00100100u ? 0x00000100u : 0u); r[8] = (r[8] << 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
x = r[8]; y = r[17]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C524u); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00020100u) == 0x00020100u ? 0x00000100u : 0u);
r[1] = 0x09000000u; known = (known & ~0x00000002u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000002u : 0u); r[9] = (r[6] << 8u); known = (known & ~0x00000200u) | ((known & 0x00000040u) == 0x00000040u ? 0x00000200u : 0u);
r[9] = (r[9] >> 8u); known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); r[10] = r_u32((r[8] + 0x00000000u)); known = (known & ~0x00000400u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000400u : 0u);
w_u32((r[8] + 0x00000000u), r[9]); x = r[10]; y = r[1]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C53Cu);
r[10] = value; known = (known & ~0x00000400u) | ((known & 0x00000402u) == 0x00000402u ? 0x00000400u : 0u); w_u32((r[6] + 0x00000000u), r[10]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000014u), (uint32)snapshot.sxy[1]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000020u), (uint32)snapshot.sxy[2]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000004u), snapshot.rgb[0]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), snapshot.rgb[1]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x0000001Cu), snapshot.rgb[2]);
goto L_8001C078; L_8001C560:;
r[10] = r_u16((r[7] + 0x0000000Au)); known = (known & ~0x00000400u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000400u : 0u); psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); r[11] = (r[10] << 2u); known = (known & ~0x00000800u) | ((known & 0x00000400u) == 0x00000400u ? 0x00000800u : 0u);
x = r[10]; y = r[11]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C56Cu); r[10] = value; known = (known & ~0x00000400u) | ((known & 0x00000C00u) == 0x00000C00u ? 0x00000400u : 0u);
r[10] = (r[10] << 3u); known = (known & ~0x00000400u) | ((known & 0x00000400u) == 0x00000400u ? 0x00000400u : 0u); x = r[18]; y = r[10]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C574u);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040400u) == 0x00040400u ? 0x00040000u : 0u); x = r[19]; y = r[11]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C578u);
r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080800u) == 0x00080800u ? 0x00080000u : 0u); branch = ((sint32)r[9] < 0);
x = r[19]; y = 0x0000000Cu; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C580u); r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u);
if (branch) goto L_8001C078; psx_gte_snapshot(&snapshot);
r[8] = snapshot.sz[1] & 0xFFFFu; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); psx_gte_snapshot(&snapshot);
r[4] = (uint32)snapshot.sxy[0]; known = (known & ~0x00000010u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000010u : 0u); r[8] = (r[8] >> 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[8] = (r[8] >> (r[20] & 31u)); known = (known & ~0x00000100u) | ((known & 0x00100100u) == 0x00100100u ? 0x00000100u : 0u); x = r[8]; y = 0xFFFFFFF8u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C594u);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[8] = (r[8] << 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[31] = 0x8001C5A4u; known |= 0x80000000u; x = r[17]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C5A0u);
r[5] = value; known = (known & ~0x00000020u) | ((known & 0x00020100u) == 0x00020100u ? 0x00000020u : 0u); r[2] = sub_8002A1E8(r[4], r[5], r[6], r[7], r[9]); known = (known & 0xD0FF0001u) | 4u;
branch = ((sint32)r[0] >= 0); if (branch) goto L_8001C070;
L_8001C5AC:; psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); x = r[18]; y = 0x00000028u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C5B0u);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); branch = ((sint32)r[9] < 0);
x = r[19]; y = 0x00000018u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C5B8u); r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u);
if (branch) goto L_8001C078; psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]);
psx_gte_snapshot(&snapshot); r[10] = (uint32)snapshot.mac0; known = (known & ~0x00000400u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000400u : 0u);
r[9] = r_u16((r[7] + 0x00000016u)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u); branch = ((sint32)r[10] <= 0);
r[8] = r[9] & 0x3FFFu; known = (known & ~0x00000100u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000100u : 0u); if (branch) goto L_8001C078;
r[8] = (r[8] << 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[8] = r[8] + r[16]; known = (known & ~0x00000100u) | ((known & 0x00010100u) == 0x00010100u ? 0x00000100u : 0u);
r[8] = r_u32((r[8] + 0x0000002Cu)); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[9] = r[9] & 0xC000u; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u);
r[10] = r_u32((r[8] + 0x00000008u)); known = (known & ~0x00000400u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000400u : 0u); r[9] = (r[9] >> 9u); known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u);
r[11] = (r[10] >> 16u); known = (known & ~0x00000800u) | ((known & 0x00000400u) == 0x00000400u ? 0x00000800u : 0u); r[10] = r[10] | r[9]; known = (known & ~0x00000400u) | ((known & 0x00000600u) == 0x00000600u ? 0x00000400u : 0u);
w_u16((r[6] + 0x0000001Au), r[10]); w_u16((r[6] + 0x0000000Eu), r[11]);
r[8] = r_u16((r[8] + 0x00000006u)); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[9] = r_u16((r[7] + 0x00000010u)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u);
r[10] = r_u16((r[7] + 0x00000012u)); known = (known & ~0x00000400u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000400u : 0u); r[11] = r_u16((r[7] + 0x00000014u)); known = (known & ~0x00000800u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000800u : 0u);
x = r[9]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C608u); r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000200u : 0u);
x = r[10]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C60Cu); r[10] = value; known = (known & ~0x00000400u) | ((known & 0x00000500u) == 0x00000500u ? 0x00000400u : 0u);
x = r[11]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C610u); r[11] = value; known = (known & ~0x00000800u) | ((known & 0x00000900u) == 0x00000900u ? 0x00000800u : 0u);
w_u16((r[6] + 0x0000000Cu), r[9]); w_u16((r[6] + 0x00000018u), r[10]);
w_u16((r[6] + 0x00000024u), r[11]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000014u), (uint32)snapshot.sxy[1]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000020u), (uint32)snapshot.sxy[2]);
goto L_8001CC64; L_8001C630:;
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
x = r[18]; y = 0x00000028u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C634u); r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u);
branch = ((sint32)r[9] < 0); x = r[19]; y = 0x00000018u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C63Cu);
r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u); if (branch) goto L_8001C078;
psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]); psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); r[10] = 0x08000000u; known = (known & ~0x00000400u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000400u : 0u);
branch = ((sint32)r[9] <= 0); x = r[8]; y = r[10]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C650u);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000500u) == 0x00000500u ? 0x00000100u : 0u); if (branch) goto L_8001C078;
xport_gte_write_data(6u, r[8]); r[9] = r_u32((r[7] + 0x0000000Cu)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u);
x = r[12]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C65Cu); r[12] = value; known = (known & ~0x00001000u) | ((known & 0x00001008u) == 0x00001008u ? 0x00001000u : 0u);
r[10] = (r[9] >> 16u); known = (known & ~0x00000400u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000400u : 0u); r[9] = r[9] & 0xFFFFu; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u);
x = r[9]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C668u); r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000208u) == 0x00000208u ? 0x00000200u : 0u);
x = r[10]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C66Cu); r[10] = value; known = (known & ~0x00000400u) | ((known & 0x00000408u) == 0x00000408u ? 0x00000400u : 0u);
xport_gte_write_data(0u, r_u32((r[12] + 0x00000000u))); xport_gte_write_data(1u, r_u32((r[12] + 0x00000004u)));
xport_gte_write_data(2u, r_u32((r[9] + 0x00000000u))); xport_gte_write_data(3u, r_u32((r[9] + 0x00000004u)));
xport_gte_write_data(4u, r_u32((r[10] + 0x00000000u))); xport_gte_write_data(5u, r_u32((r[10] + 0x00000004u)));
r[9] = r_u16((r[7] + 0x00000016u)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u); psx_gte_snapshot(&snapshot); vectors[0].vx = snapshot.v0[0]; vectors[0].vy = snapshot.v0[1]; vectors[0].vz = snapshot.v0[2]; vectors[1].vx = snapshot.v1[0]; vectors[1].vy = snapshot.v1[1]; vectors[1].vz = snapshot.v1[2]; vectors[2].vx = snapshot.v2[0]; vectors[2].vy = snapshot.v2[1]; vectors[2].vz = snapshot.v2[2]; gte_normal_color_col3(vectors, snapshot.rgbc, colors);
r[8] = r[9] & 0x3FFFu; known = (known & ~0x00000100u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000100u : 0u); r[8] = (r[8] << 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[8] = r[8] + r[16]; known = (known & ~0x00000100u) | ((known & 0x00010100u) == 0x00010100u ? 0x00000100u : 0u); r[8] = r_u32((r[8] + 0x0000002Cu)); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[9] = r[9] & 0xC000u; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); r[10] = r_u32((r[8] + 0x00000008u)); known = (known & ~0x00000400u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000400u : 0u);
r[9] = (r[9] >> 9u); known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); r[11] = (r[10] >> 16u); known = (known & ~0x00000800u) | ((known & 0x00000400u) == 0x00000400u ? 0x00000800u : 0u);
r[10] = r[10] | r[9]; known = (known & ~0x00000400u) | ((known & 0x00000600u) == 0x00000600u ? 0x00000400u : 0u); w_u16((r[6] + 0x0000001Au), r[10]);
w_u16((r[6] + 0x0000000Eu), r[11]); r[8] = r_u16((r[8] + 0x00000006u)); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[9] = r_u16((r[7] + 0x00000010u)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u); r[10] = r_u16((r[7] + 0x00000012u)); known = (known & ~0x00000400u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000400u : 0u);
r[11] = r_u16((r[7] + 0x00000014u)); known = (known & ~0x00000800u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000800u : 0u); x = r[9]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C6D0u);
r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000200u : 0u); x = r[10]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C6D4u);
r[10] = value; known = (known & ~0x00000400u) | ((known & 0x00000500u) == 0x00000500u ? 0x00000400u : 0u); x = r[11]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C6D8u);
r[11] = value; known = (known & ~0x00000800u) | ((known & 0x00000900u) == 0x00000900u ? 0x00000800u : 0u); w_u16((r[6] + 0x0000000Cu), r[9]);
w_u16((r[6] + 0x00000018u), r[10]); w_u16((r[6] + 0x00000024u), r[11]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000014u), (uint32)snapshot.sxy[1]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000020u), (uint32)snapshot.sxy[2]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000004u), snapshot.rgb[0]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), snapshot.rgb[1]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x0000001Cu), snapshot.rgb[2]);
goto L_8001CC64; psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); x = r[18]; y = 0x00000020u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C708u);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); branch = ((sint32)r[9] < 0);
x = r[19]; y = 0x00000014u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C710u); r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u);
if (branch) goto L_8001C740; goto L_8001C078;
L_8001C71C:; psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); x = r[18]; y = 0x00000020u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C720u);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); branch = ((sint32)r[9] < 0);
x = r[19]; y = 0x00000014u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C728u); r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u);
if (branch) goto L_8001C078; psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]);
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
branch = ((sint32)r[9] <= 0); if (branch) goto L_8001C078;
L_8001C740:; r[8] = (uint32)(sint32)(sint16)r_u16((r[7] + 0x00000004u)); known = (known & ~0x00000100u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000100u : 0u);
r[8] = r[8] + r[2]; known = (known & ~0x00000100u) | ((known & 0x00000104u) == 0x00000104u ? 0x00000100u : 0u); xport_gte_write_data(0u, r_u32((r[8] + 0x00000000u)));
xport_gte_write_data(1u, r_u32((r[8] + 0x00000004u))); xport_gte_mvmva(0x480012u);
r[8] = r_u16((r[7] + 0x0000000Au)); known = (known & ~0x00000100u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000100u : 0u); r[12] = xport_gte_read_data(25u); known = (known & ~0x00001000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00001000u : 0u);
r[13] = xport_gte_read_data(26u); known = (known & ~0x00002000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00002000u : 0u); r[14] = xport_gte_read_data(27u); known = (known & ~0x00004000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00004000u : 0u);
x = r[8]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C770u); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000108u) == 0x00000108u ? 0x00000100u : 0u);
xport_gte_write_data(0u, r_u32((r[8] + 0x00000000u))); xport_gte_write_data(1u, r_u32((r[8] + 0x00000004u)));
xport_gte_mvmva(0x486012u); r[8] = xport_gte_read_data(25u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
lo = r[8] * r[12]; r[9] = lo; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
r[8] = xport_gte_read_data(26u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); lo = r[8] * r[13];
r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); r[9] = r[9] + r[8]; known = (known & ~0x00000200u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000200u : 0u);
r[8] = xport_gte_read_data(27u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); lo = r[8] * r[14];
r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); r[9] = r[9] + r[8]; known = (known & ~0x00000200u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000200u : 0u);
r[9] = ((sint32)r[9] >> 11u); known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); r[8] = xport_gte_read_data(25u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
lo = r[9] * r[8]; r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
r[8] = ((sint32)r[8] >> 12u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[12] = r[12] + r[8]; known = (known & ~0x00001000u) | ((known & 0x00001100u) == 0x00001100u ? 0x00001000u : 0u);
r[8] = xport_gte_read_data(26u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); lo = r[9] * r[8];
r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); r[8] = ((sint32)r[8] >> 12u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[13] = r[13] + r[8]; known = (known & ~0x00002000u) | ((known & 0x00002100u) == 0x00002100u ? 0x00002000u : 0u); r[8] = xport_gte_read_data(27u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
lo = r[9] * r[8]; r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
r[8] = ((sint32)r[8] >> 12u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[14] = r[14] + r[8]; known = (known & ~0x00004000u) | ((known & 0x00004100u) == 0x00004100u ? 0x00004000u : 0u);
r[8] = (uint32)(sint32)(sint16)r_u16((r[7] + 0x00000006u)); known = (known & ~0x00000100u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000100u : 0u); r[8] = r[8] + r[2]; known = (known & ~0x00000100u) | ((known & 0x00000104u) == 0x00000104u ? 0x00000100u : 0u);
xport_gte_write_data(0u, r_u32((r[8] + 0x00000000u))); xport_gte_write_data(1u, r_u32((r[8] + 0x00000004u)));
branch = ((sint32)r[12] >= 0); r[8] = r[12] + r[0]; known = (known & ~0x00000100u) | ((known & 0x00001001u) == 0x00001001u ? 0x00000100u : 0u);
if (branch) goto L_8001C82C; x = r[0]; y = r[8]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C828u);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000101u) == 0x00000101u ? 0x00000100u : 0u); L_8001C82C:;
xport_gte_mvmva(0x480012u); branch = ((sint32)r[14] >= 0);
r[9] = r[14] + r[0]; known = (known & ~0x00000200u) | ((known & 0x00004001u) == 0x00004001u ? 0x00000200u : 0u); if (branch) goto L_8001C83C;
x = r[0]; y = r[9]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C838u); r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000201u) == 0x00000201u ? 0x00000200u : 0u);
L_8001C83C:; r[8] = ((sint32)r[8] < (sint32)r[9]); known = (known & ~0x00000100u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000100u : 0u);
branch = (r[8] != r[0]); r[8] = (r[14] << 7u); known = (known & ~0x00000100u) | ((known & 0x00004000u) == 0x00004000u ? 0x00000100u : 0u);
if (branch) goto L_8001C850; if (r[12] == 0u) lo = (sint32)r[8] < 0 ? 1u : 0xFFFFFFFFu; else if (r[8] == 0x80000000u && r[12] == 0xFFFFFFFFu) lo = 0x80000000u; else lo = (uint32)((sint64)(sint32)r[8] / (sint64)(sint32)r[12]);
goto L_8001C858; L_8001C850:;
r[8] = (r[12] << 7u); known = (known & ~0x00000100u) | ((known & 0x00001000u) == 0x00001000u ? 0x00000100u : 0u); if (r[14] == 0u) lo = (sint32)r[8] < 0 ? 1u : 0xFFFFFFFFu; else if (r[8] == 0x80000000u && r[14] == 0xFFFFFFFFu) lo = 0x80000000u; else lo = (uint32)((sint64)(sint32)r[8] / (sint64)(sint32)r[14]);
L_8001C858:; r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
x = r[8]; y = 0x00000080u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C85Cu); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
w_u8((r[6] + 0x0000000Cu), r[8]); branch = ((sint32)r[13] >= 0);
r[8] = r[13] + r[0]; known = (known & ~0x00000100u) | ((known & 0x00002001u) == 0x00002001u ? 0x00000100u : 0u); if (branch) goto L_8001C870;
x = r[0]; y = r[8]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C86Cu); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000101u) == 0x00000101u ? 0x00000100u : 0u);
L_8001C870:; branch = ((sint32)r[14] >= 0);
r[9] = r[14] + r[0]; known = (known & ~0x00000200u) | ((known & 0x00004001u) == 0x00004001u ? 0x00000200u : 0u); if (branch) goto L_8001C87C;
x = r[0]; y = r[9]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C878u); r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000201u) == 0x00000201u ? 0x00000200u : 0u);
L_8001C87C:; r[8] = ((sint32)r[8] < (sint32)r[9]); known = (known & ~0x00000100u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000100u : 0u);
branch = (r[8] != r[0]); r[8] = (r[14] << 7u); known = (known & ~0x00000100u) | ((known & 0x00004000u) == 0x00004000u ? 0x00000100u : 0u);
if (branch) goto L_8001C890; if (r[13] == 0u) lo = (sint32)r[8] < 0 ? 1u : 0xFFFFFFFFu; else if (r[8] == 0x80000000u && r[13] == 0xFFFFFFFFu) lo = 0x80000000u; else lo = (uint32)((sint64)(sint32)r[8] / (sint64)(sint32)r[13]);
goto L_8001C898; L_8001C890:;
r[8] = (r[13] << 7u); known = (known & ~0x00000100u) | ((known & 0x00002000u) == 0x00002000u ? 0x00000100u : 0u); if (r[14] == 0u) lo = (sint32)r[8] < 0 ? 1u : 0xFFFFFFFFu; else if (r[8] == 0x80000000u && r[14] == 0xFFFFFFFFu) lo = 0x80000000u; else lo = (uint32)((sint64)(sint32)r[8] / (sint64)(sint32)r[14]);
L_8001C898:; r[9] = r_u16((r[7] + 0x00000012u)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u);
r[13] = lo; known = (known & ~0x00002000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00002000u : 0u); r[8] = (r[9] >> 8u); known = (known & ~0x00000100u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000100u : 0u);
x = r[8]; y = r[13]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C8A4u); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00002100u) == 0x00002100u ? 0x00000100u : 0u);
branch = ((sint32)r[8] >= 0); r[9] = r[9] & 0x00FFu; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u);
if (branch) goto L_8001C8B4; r[8] = r[0] + r[0]; known = (known & ~0x00000100u) | ((known & 0x00000001u) == 0x00000001u ? 0x00000100u : 0u);
L_8001C8B4:; x = r[8]; y = r[9]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C8B4u);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000100u : 0u); w_u8((r[6] + 0x0000000Du), r[8]);
r[8] = r_u16((r[7] + 0x0000000Cu)); known = (known & ~0x00000100u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000100u : 0u); r[12] = xport_gte_read_data(25u); known = (known & ~0x00001000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00001000u : 0u);
r[13] = xport_gte_read_data(26u); known = (known & ~0x00002000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00002000u : 0u); r[14] = xport_gte_read_data(27u); known = (known & ~0x00004000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00004000u : 0u);
x = r[8]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C8CCu); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000108u) == 0x00000108u ? 0x00000100u : 0u);
xport_gte_write_data(0u, r_u32((r[8] + 0x00000000u))); xport_gte_write_data(1u, r_u32((r[8] + 0x00000004u)));
xport_gte_mvmva(0x486012u); r[8] = xport_gte_read_data(25u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
lo = r[8] * r[12]; r[9] = lo; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
r[8] = xport_gte_read_data(26u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); lo = r[8] * r[13];
r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); r[9] = r[9] + r[8]; known = (known & ~0x00000200u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000200u : 0u);
r[8] = xport_gte_read_data(27u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); lo = r[8] * r[14];
r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); r[9] = r[9] + r[8]; known = (known & ~0x00000200u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000200u : 0u);
r[9] = ((sint32)r[9] >> 11u); known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); r[8] = xport_gte_read_data(25u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
lo = r[9] * r[8]; r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
r[8] = ((sint32)r[8] >> 12u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[12] = r[12] + r[8]; known = (known & ~0x00001000u) | ((known & 0x00001100u) == 0x00001100u ? 0x00001000u : 0u);
r[8] = xport_gte_read_data(26u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); lo = r[9] * r[8];
r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); r[8] = ((sint32)r[8] >> 12u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[13] = r[13] + r[8]; known = (known & ~0x00002000u) | ((known & 0x00002100u) == 0x00002100u ? 0x00002000u : 0u); r[8] = xport_gte_read_data(27u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
lo = r[9] * r[8]; r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
r[8] = ((sint32)r[8] >> 12u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[14] = r[14] + r[8]; known = (known & ~0x00004000u) | ((known & 0x00004100u) == 0x00004100u ? 0x00004000u : 0u);
r[8] = (uint32)(sint32)(sint16)r_u16((r[7] + 0x00000008u)); known = (known & ~0x00000100u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000100u : 0u); r[8] = r[8] + r[2]; known = (known & ~0x00000100u) | ((known & 0x00000104u) == 0x00000104u ? 0x00000100u : 0u);
xport_gte_write_data(0u, r_u32((r[8] + 0x00000000u))); xport_gte_write_data(1u, r_u32((r[8] + 0x00000004u)));
branch = ((sint32)r[12] >= 0); r[8] = r[12] + r[0]; known = (known & ~0x00000100u) | ((known & 0x00001001u) == 0x00001001u ? 0x00000100u : 0u);
if (branch) goto L_8001C988; x = r[0]; y = r[8]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C984u);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000101u) == 0x00000101u ? 0x00000100u : 0u); L_8001C988:;
xport_gte_mvmva(0x480012u); branch = ((sint32)r[14] >= 0);
r[9] = r[14] + r[0]; known = (known & ~0x00000200u) | ((known & 0x00004001u) == 0x00004001u ? 0x00000200u : 0u); if (branch) goto L_8001C998;
x = r[0]; y = r[9]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C994u); r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000201u) == 0x00000201u ? 0x00000200u : 0u);
L_8001C998:; r[8] = ((sint32)r[8] < (sint32)r[9]); known = (known & ~0x00000100u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000100u : 0u);
branch = (r[8] != r[0]); r[8] = (r[14] << 7u); known = (known & ~0x00000100u) | ((known & 0x00004000u) == 0x00004000u ? 0x00000100u : 0u);
if (branch) goto L_8001C9AC; if (r[12] == 0u) lo = (sint32)r[8] < 0 ? 1u : 0xFFFFFFFFu; else if (r[8] == 0x80000000u && r[12] == 0xFFFFFFFFu) lo = 0x80000000u; else lo = (uint32)((sint64)(sint32)r[8] / (sint64)(sint32)r[12]);
goto L_8001C9B4; L_8001C9AC:;
r[8] = (r[12] << 7u); known = (known & ~0x00000100u) | ((known & 0x00001000u) == 0x00001000u ? 0x00000100u : 0u); if (r[14] == 0u) lo = (sint32)r[8] < 0 ? 1u : 0xFFFFFFFFu; else if (r[8] == 0x80000000u && r[14] == 0xFFFFFFFFu) lo = 0x80000000u; else lo = (uint32)((sint64)(sint32)r[8] / (sint64)(sint32)r[14]);
L_8001C9B4:; r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
x = r[8]; y = 0x00000080u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C9B8u); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
w_u8((r[6] + 0x00000014u), r[8]); branch = ((sint32)r[13] >= 0);
r[8] = r[13] + r[0]; known = (known & ~0x00000100u) | ((known & 0x00002001u) == 0x00002001u ? 0x00000100u : 0u); if (branch) goto L_8001C9CC;
x = r[0]; y = r[8]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C9C8u); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000101u) == 0x00000101u ? 0x00000100u : 0u);
L_8001C9CC:; branch = ((sint32)r[14] >= 0);
r[9] = r[14] + r[0]; known = (known & ~0x00000200u) | ((known & 0x00004001u) == 0x00004001u ? 0x00000200u : 0u); if (branch) goto L_8001C9D8;
x = r[0]; y = r[9]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001C9D4u); r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000201u) == 0x00000201u ? 0x00000200u : 0u);
L_8001C9D8:; r[8] = ((sint32)r[8] < (sint32)r[9]); known = (known & ~0x00000100u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000100u : 0u);
branch = (r[8] != r[0]); r[8] = (r[14] << 7u); known = (known & ~0x00000100u) | ((known & 0x00004000u) == 0x00004000u ? 0x00000100u : 0u);
if (branch) goto L_8001C9EC; if (r[13] == 0u) lo = (sint32)r[8] < 0 ? 1u : 0xFFFFFFFFu; else if (r[8] == 0x80000000u && r[13] == 0xFFFFFFFFu) lo = 0x80000000u; else lo = (uint32)((sint64)(sint32)r[8] / (sint64)(sint32)r[13]);
goto L_8001C9F4; L_8001C9EC:;
r[8] = (r[13] << 7u); known = (known & ~0x00000100u) | ((known & 0x00002000u) == 0x00002000u ? 0x00000100u : 0u); if (r[14] == 0u) lo = (sint32)r[8] < 0 ? 1u : 0xFFFFFFFFu; else if (r[8] == 0x80000000u && r[14] == 0xFFFFFFFFu) lo = 0x80000000u; else lo = (uint32)((sint64)(sint32)r[8] / (sint64)(sint32)r[14]);
L_8001C9F4:; r[9] = r_u16((r[7] + 0x00000012u)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u);
r[13] = lo; known = (known & ~0x00002000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00002000u : 0u); r[8] = (r[9] >> 8u); known = (known & ~0x00000100u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000100u : 0u);
x = r[8]; y = r[13]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CA00u); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00002100u) == 0x00002100u ? 0x00000100u : 0u);
branch = ((sint32)r[8] >= 0); r[9] = r[9] & 0x00FFu; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u);
if (branch) goto L_8001CA10; r[8] = r[0] + r[0]; known = (known & ~0x00000100u) | ((known & 0x00000001u) == 0x00000001u ? 0x00000100u : 0u);
L_8001CA10:; x = r[8]; y = r[9]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CA10u);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000100u : 0u); w_u8((r[6] + 0x00000015u), r[8]);
r[8] = r_u16((r[7] + 0x0000000Eu)); known = (known & ~0x00000100u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000100u : 0u); r[12] = xport_gte_read_data(25u); known = (known & ~0x00001000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00001000u : 0u);
r[13] = xport_gte_read_data(26u); known = (known & ~0x00002000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00002000u : 0u); r[14] = xport_gte_read_data(27u); known = (known & ~0x00004000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00004000u : 0u);
x = r[8]; y = r[3]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CA28u); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000108u) == 0x00000108u ? 0x00000100u : 0u);
xport_gte_write_data(0u, r_u32((r[8] + 0x00000000u))); xport_gte_write_data(1u, r_u32((r[8] + 0x00000004u)));
xport_gte_mvmva(0x486012u); r[8] = xport_gte_read_data(25u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
lo = r[8] * r[12]; r[9] = lo; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
r[8] = xport_gte_read_data(26u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); lo = r[8] * r[13];
r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); r[9] = r[9] + r[8]; known = (known & ~0x00000200u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000200u : 0u);
r[8] = xport_gte_read_data(27u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); lo = r[8] * r[14];
r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); r[9] = r[9] + r[8]; known = (known & ~0x00000200u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000200u : 0u);
r[9] = ((sint32)r[9] >> 11u); known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); r[8] = xport_gte_read_data(25u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
lo = r[9] * r[8]; r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
r[8] = ((sint32)r[8] >> 12u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[12] = r[12] + r[8]; known = (known & ~0x00001000u) | ((known & 0x00001100u) == 0x00001100u ? 0x00001000u : 0u);
r[8] = xport_gte_read_data(26u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); lo = r[9] * r[8];
r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); r[8] = ((sint32)r[8] >> 12u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[13] = r[13] + r[8]; known = (known & ~0x00002000u) | ((known & 0x00002100u) == 0x00002100u ? 0x00002000u : 0u); r[8] = xport_gte_read_data(27u); known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
lo = r[9] * r[8]; r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u);
r[8] = ((sint32)r[8] >> 12u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); r[14] = r[14] + r[8]; known = (known & ~0x00004000u) | ((known & 0x00004100u) == 0x00004100u ? 0x00004000u : 0u);
branch = ((sint32)r[12] >= 0); r[8] = r[12] + r[0]; known = (known & ~0x00000100u) | ((known & 0x00001001u) == 0x00001001u ? 0x00000100u : 0u);
if (branch) goto L_8001CAD0; x = r[0]; y = r[8]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CACCu);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000101u) == 0x00000101u ? 0x00000100u : 0u); L_8001CAD0:;
branch = ((sint32)r[14] >= 0); r[9] = r[14] + r[0]; known = (known & ~0x00000200u) | ((known & 0x00004001u) == 0x00004001u ? 0x00000200u : 0u);
if (branch) goto L_8001CADC; x = r[0]; y = r[9]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CAD8u);
r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000201u) == 0x00000201u ? 0x00000200u : 0u); L_8001CADC:;
r[8] = ((sint32)r[8] < (sint32)r[9]); known = (known & ~0x00000100u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000100u : 0u); branch = (r[8] != r[0]);
r[8] = (r[14] << 7u); known = (known & ~0x00000100u) | ((known & 0x00004000u) == 0x00004000u ? 0x00000100u : 0u); if (branch) goto L_8001CAF0;
if (r[12] == 0u) lo = (sint32)r[8] < 0 ? 1u : 0xFFFFFFFFu; else if (r[8] == 0x80000000u && r[12] == 0xFFFFFFFFu) lo = 0x80000000u; else lo = (uint32)((sint64)(sint32)r[8] / (sint64)(sint32)r[12]); goto L_8001CAF8;
L_8001CAF0:; r[8] = (r[12] << 7u); known = (known & ~0x00000100u) | ((known & 0x00001000u) == 0x00001000u ? 0x00000100u : 0u);
if (r[14] == 0u) lo = (sint32)r[8] < 0 ? 1u : 0xFFFFFFFFu; else if (r[8] == 0x80000000u && r[14] == 0xFFFFFFFFu) lo = 0x80000000u; else lo = (uint32)((sint64)(sint32)r[8] / (sint64)(sint32)r[14]); L_8001CAF8:;
r[8] = lo; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); x = r[8]; y = 0x00000080u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CAFCu);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u); w_u8((r[6] + 0x0000001Cu), r[8]);
branch = ((sint32)r[13] >= 0); r[8] = r[13] + r[0]; known = (known & ~0x00000100u) | ((known & 0x00002001u) == 0x00002001u ? 0x00000100u : 0u);
if (branch) goto L_8001CB10; x = r[0]; y = r[8]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CB0Cu);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000101u) == 0x00000101u ? 0x00000100u : 0u); L_8001CB10:;
branch = ((sint32)r[14] >= 0); r[9] = r[14] + r[0]; known = (known & ~0x00000200u) | ((known & 0x00004001u) == 0x00004001u ? 0x00000200u : 0u);
if (branch) goto L_8001CB1C; x = r[0]; y = r[9]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CB18u);
r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000201u) == 0x00000201u ? 0x00000200u : 0u); L_8001CB1C:;
r[8] = ((sint32)r[8] < (sint32)r[9]); known = (known & ~0x00000100u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000100u : 0u); branch = (r[8] != r[0]);
r[8] = (r[14] << 7u); known = (known & ~0x00000100u) | ((known & 0x00004000u) == 0x00004000u ? 0x00000100u : 0u); if (branch) goto L_8001CB30;
if (r[13] == 0u) lo = (sint32)r[8] < 0 ? 1u : 0xFFFFFFFFu; else if (r[8] == 0x80000000u && r[13] == 0xFFFFFFFFu) lo = 0x80000000u; else lo = (uint32)((sint64)(sint32)r[8] / (sint64)(sint32)r[13]); goto L_8001CB38;
L_8001CB30:; r[8] = (r[13] << 7u); known = (known & ~0x00000100u) | ((known & 0x00002000u) == 0x00002000u ? 0x00000100u : 0u);
if (r[14] == 0u) lo = (sint32)r[8] < 0 ? 1u : 0xFFFFFFFFu; else if (r[8] == 0x80000000u && r[14] == 0xFFFFFFFFu) lo = 0x80000000u; else lo = (uint32)((sint64)(sint32)r[8] / (sint64)(sint32)r[14]); L_8001CB38:;
r[9] = r_u16((r[7] + 0x00000012u)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u); r[13] = lo; known = (known & ~0x00002000u) | ((known & 0x00000000u) == 0x00000000u ? 0x00002000u : 0u);
r[8] = (r[9] >> 8u); known = (known & ~0x00000100u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000100u : 0u); x = r[8]; y = r[13]; value = x - y; if (((x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CB44u);
r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00002100u) == 0x00002100u ? 0x00000100u : 0u); branch = ((sint32)r[8] >= 0);
r[9] = r[9] & 0x00FFu; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); if (branch) goto L_8001CB54;
r[8] = r[0] + r[0]; known = (known & ~0x00000100u) | ((known & 0x00000001u) == 0x00000001u ? 0x00000100u : 0u); L_8001CB54:;
x = r[8]; y = r[9]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CB54u); r[8] = value; known = (known & ~0x00000100u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000100u : 0u);
w_u8((r[6] + 0x0000001Du), r[8]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), (uint32)snapshot.sxy[1]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000018u), (uint32)snapshot.sxy[2]);
goto L_8001CC64; psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); x = r[18]; y = 0x00000020u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CB70u);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); branch = ((sint32)r[9] < 0);
x = r[19]; y = 0x00000014u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CB78u); r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u);
if (branch) return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001CB74u, 0x8001D0C4u, known, r); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), (uint32)snapshot.sxy[1]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000018u), (uint32)snapshot.sxy[2]);
goto L_8001CC64; L_8001CB8C:;
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
x = r[18]; y = 0x00000020u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CB90u); r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u);
branch = ((sint32)r[9] < 0); x = r[19]; y = 0x00000014u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CB98u);
r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u); if (branch) return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001CB94u, 0x8001D0B0u, known, r);
psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]); psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); branch = ((sint32)r[9] <= 0);
if (branch) goto L_8001C078; psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), (uint32)snapshot.sxy[1]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000018u), (uint32)snapshot.sxy[2]);
goto L_8001CC64; psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); x = r[18]; y = 0x00000020u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CBC4u);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); branch = ((sint32)r[9] >= 0);
x = r[19]; y = 0x00000014u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CBCCu); r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u);
if (branch) goto L_8001CBFC; goto L_8001C078;
L_8001CBD8:; psx_gte_snapshot(&snapshot);
r[9] = (uint32)snapshot.flag; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u); x = r[18]; y = 0x00000020u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CBDCu);
r[18] = value; known = (known & ~0x00040000u) | ((known & 0x00040000u) == 0x00040000u ? 0x00040000u : 0u); branch = ((sint32)r[9] < 0);
x = r[19]; y = 0x00000014u; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CBE4u); r[19] = value; known = (known & ~0x00080000u) | ((known & 0x00080000u) == 0x00080000u ? 0x00080000u : 0u);
if (branch) goto L_8001C078; psx_gte_snapshot(&snapshot); (void)NormalClip(snapshot.sxy[0], snapshot.sxy[1], snapshot.sxy[2]);
psx_gte_snapshot(&snapshot); r[9] = (uint32)snapshot.mac0; known = (known & ~0x00000200u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000200u : 0u);
branch = ((sint32)r[9] <= 0); if (branch) goto L_8001C078;
L_8001CBFC:; r[9] = r_u16((r[7] + 0x00000012u)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u);
r[8] = r[9] & 0x3FFFu; known = (known & ~0x00000100u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000100u : 0u); r[8] = (r[8] << 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[8] = r[8] + r[16]; known = (known & ~0x00000100u) | ((known & 0x00010100u) == 0x00010100u ? 0x00000100u : 0u); r[8] = r_u32((r[8] + 0x0000002Cu)); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[9] = r[9] & 0xC000u; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); r[10] = r_u32((r[8] + 0x00000008u)); known = (known & ~0x00000400u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000400u : 0u);
r[9] = (r[9] >> 9u); known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u); r[11] = (r[10] >> 16u); known = (known & ~0x00000800u) | ((known & 0x00000400u) == 0x00000400u ? 0x00000800u : 0u);
r[10] = r[10] | r[9]; known = (known & ~0x00000400u) | ((known & 0x00000600u) == 0x00000600u ? 0x00000400u : 0u); w_u16((r[6] + 0x00000016u), r[10]);
w_u16((r[6] + 0x0000000Eu), r[11]); r[8] = r_u16((r[8] + 0x00000006u)); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
r[9] = r_u16((r[7] + 0x0000000Cu)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u); r[10] = r_u16((r[7] + 0x0000000Eu)); known = (known & ~0x00000400u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000400u : 0u);
r[11] = r_u16((r[7] + 0x00000010u)); known = (known & ~0x00000800u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000800u : 0u); x = r[9]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CC40u);
r[9] = value; known = (known & ~0x00000200u) | ((known & 0x00000300u) == 0x00000300u ? 0x00000200u : 0u); x = r[10]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CC44u);
r[10] = value; known = (known & ~0x00000400u) | ((known & 0x00000500u) == 0x00000500u ? 0x00000400u : 0u); x = r[11]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CC48u);
r[11] = value; known = (known & ~0x00000800u) | ((known & 0x00000900u) == 0x00000900u ? 0x00000800u : 0u); w_u16((r[6] + 0x0000000Cu), r[9]);
w_u16((r[6] + 0x00000014u), r[10]); w_u16((r[6] + 0x0000001Cu), r[11]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000008u), (uint32)snapshot.sxy[0]); psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000010u), (uint32)snapshot.sxy[1]);
psx_gte_snapshot(&snapshot); w_u32((r[6] + 0x00000018u), (uint32)snapshot.sxy[2]); L_8001CC64:;
psx_gte_snapshot(&snapshot); (void)AverageZ3((sint32)snapshot.sz[1], (sint32)snapshot.sz[2], (sint32)snapshot.sz[3]); psx_gte_snapshot(&snapshot);
r[8] = snapshot.otz & 0xFFFFu; known = (known & ~0x00000100u) | ((known & 0x00000000u) == 0x00000000u ? 0x00000100u : 0u); L_8001CC74:;
branch = (r[21] == r[0]); r[8] = (r[8] >> (r[20] & 31u)); known = (known & ~0x00000100u) | ((known & 0x00100100u) == 0x00100100u ? 0x00000100u : 0u);
if (branch) goto L_8001CD0C; r[8] = (r[8] << 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
x = r[17]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CC80u); r[7] = value; known = (known & ~0x00000080u) | ((known & 0x00020100u) == 0x00020100u ? 0x00000080u : 0u);
r[9] = r_u32((r[19] + 0x00000004u)); known = (known & ~0x00000200u) | ((known & 0x00080000u) == 0x00080000u ? 0x00000200u : 0u); r[11] = r_u32((r[19] + 0x00000008u)); known = (known & ~0x00000800u) | ((known & 0x00080000u) == 0x00080000u ? 0x00000800u : 0u);
r[10] = (r[9] >> 16u); known = (known & ~0x00000400u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000400u : 0u); r[9] = r[9] & 0xFFFFu; known = (known & ~0x00000200u) | ((known & 0x00000200u) == 0x00000200u ? 0x00000200u : 0u);
r[12] = (r[11] >> 16u); known = (known & ~0x00001000u) | ((known & 0x00000800u) == 0x00000800u ? 0x00001000u : 0u); r[11] = r[11] & 0xFFFFu; known = (known & ~0x00000800u) | ((known & 0x00000800u) == 0x00000800u ? 0x00000800u : 0u);
r[9] = r[9] + r[2]; known = (known & ~0x00000200u) | ((known & 0x00000204u) == 0x00000204u ? 0x00000200u : 0u); r[10] = r[10] + r[2]; known = (known & ~0x00000400u) | ((known & 0x00000404u) == 0x00000404u ? 0x00000400u : 0u);
r[11] = r[11] + r[2]; known = (known & ~0x00000800u) | ((known & 0x00000804u) == 0x00000804u ? 0x00000800u : 0u); xport_gte_write_data(0u, r_u32((r[9] + 0x00000000u)));
xport_gte_write_data(1u, r_u32((r[9] + 0x00000004u))); xport_gte_write_data(2u, r_u32((r[10] + 0x00000000u)));
xport_gte_write_data(3u, r_u32((r[10] + 0x00000004u))); xport_gte_write_data(4u, r_u32((r[11] + 0x00000000u)));
xport_gte_write_data(5u, r_u32((r[11] + 0x00000004u))); r[8] = r_u32((r[19] + 0x00000000u)); known = (known & ~0x00000100u) | ((known & 0x00080000u) == 0x00080000u ? 0x00000100u : 0u);
x = r[21]; y = 0xFFFFFFFFu; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CCC4u); r[21] = value; known = (known & ~0x00200000u) | ((known & 0x00200000u) == 0x00200000u ? 0x00200000u : 0u);
psx_gte_snapshot(&snapshot); vectors[0].vx = snapshot.v0[0]; vectors[0].vy = snapshot.v0[1]; vectors[0].vz = snapshot.v0[2]; vectors[1].vx = snapshot.v1[0]; vectors[1].vy = snapshot.v1[1]; vectors[1].vz = snapshot.v1[2]; vectors[2].vx = snapshot.v2[0]; vectors[2].vy = snapshot.v2[1]; vectors[2].vz = snapshot.v2[2]; gte_project3_full_depth(vectors, screen, depths, &flags); xport_gte_complete_rtpt(); r[1] = r_u32((r[6] + 0x00000000u)); known = (known & ~0x00000002u) | ((known & 0x00000040u) == 0x00000040u ? 0x00000002u : 0u);
r[9] = r_u32((r[7] + 0x00000000u)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u); r[1] = (r[1] >> 24u); known = (known & ~0x00000002u) | ((known & 0x00000002u) == 0x00000002u ? 0x00000002u : 0u);
r[1] = (r[1] << 24u); known = (known & ~0x00000002u) | ((known & 0x00000002u) == 0x00000002u ? 0x00000002u : 0u); r[1] = r[1] | r[9]; known = (known & ~0x00000002u) | ((known & 0x00000202u) == 0x00000202u ? 0x00000002u : 0u);
w_u32((r[6] + 0x00000000u), r[1]); r[1] = (r[6] << 8u); known = (known & ~0x00000002u) | ((known & 0x00000040u) == 0x00000040u ? 0x00000002u : 0u);
r[1] = (r[1] >> 8u); known = (known & ~0x00000002u) | ((known & 0x00000002u) == 0x00000002u ? 0x00000002u : 0u); w_u32((r[7] + 0x00000000u), r[1]);
r[1] = (r[8] >> 24u); known = (known & ~0x00000002u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000002u : 0u); r[1] = r[1] & 0x003Cu; known = (known & ~0x00000002u) | ((known & 0x00000002u) == 0x00000002u ? 0x00000002u : 0u);
x = r[1]; y = r[22]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CCF8u); r[1] = value; known = (known & ~0x00000002u) | ((known & 0x00400002u) == 0x00400002u ? 0x00000002u : 0u);
r[1] = r_u32((r[1] + 0x00000000u)); known = (known & ~0x00000002u) | ((known & 0x00000002u) == 0x00000002u ? 0x00000002u : 0u); r[6] = r[18] + r[0]; known = (known & ~0x00000040u) | ((known & 0x00040001u) == 0x00040001u ? 0x00000040u : 0u);
target = r[1]; r[7] = r[19] + r[0]; known = (known & ~0x00000080u) | ((known & 0x00080001u) == 0x00080001u ? 0x00000080u : 0u);
switch (target) { case 0x8001C100u: goto L_8001C100;
case 0x8001C134u: goto L_8001C134; case 0x8001C168u: goto L_8001C168;
case 0x8001C19Cu: goto L_8001C19C; case 0x8001C22Cu: goto L_8001C22C;
case 0x8001C280u: goto L_8001C280; case 0x8001C2D4u: goto L_8001C2D4;
case 0x8001C2F8u: goto L_8001C2F8; case 0x8001C3A0u: goto L_8001C3A0;
case 0x8001C3D4u: goto L_8001C3D4; case 0x8001C480u: goto L_8001C480;
case 0x8001C4B4u: goto L_8001C4B4; case 0x8001C560u: goto L_8001C560;
case 0x8001C5ACu: goto L_8001C5AC; case 0x8001C630u: goto L_8001C630;
case 0x8001C71Cu: goto L_8001C71C; case 0x8001CB8Cu: goto L_8001CB8C;
case 0x8001CBD8u: goto L_8001CBD8; case 0x8001CD38u: goto L_8001CD38;
default: return xport_guest_nonlocal_transfer(0x8001BE5Cu, 0x8001CD04u, target, known, r); }
L_8001CD0C:; r[8] = (r[8] << 2u); known = (known & ~0x00000100u) | ((known & 0x00000100u) == 0x00000100u ? 0x00000100u : 0u);
x = r[17]; y = r[8]; value = x + y; if ((~(x ^ y) & (x ^ value) & 0x80000000u) != 0u) xport_mips_overflow_exception(0x8001CD10u); r[7] = value; known = (known & ~0x00000080u) | ((known & 0x00020100u) == 0x00020100u ? 0x00000080u : 0u);
r[1] = r_u32((r[6] + 0x00000000u)); known = (known & ~0x00000002u) | ((known & 0x00000040u) == 0x00000040u ? 0x00000002u : 0u); r[9] = r_u32((r[7] + 0x00000000u)); known = (known & ~0x00000200u) | ((known & 0x00000080u) == 0x00000080u ? 0x00000200u : 0u);
r[1] = (r[1] >> 24u); known = (known & ~0x00000002u) | ((known & 0x00000002u) == 0x00000002u ? 0x00000002u : 0u); r[1] = (r[1] << 24u); known = (known & ~0x00000002u) | ((known & 0x00000002u) == 0x00000002u ? 0x00000002u : 0u);
r[1] = r[1] | r[9]; known = (known & ~0x00000002u) | ((known & 0x00000202u) == 0x00000202u ? 0x00000002u : 0u); w_u32((r[6] + 0x00000000u), r[1]);
r[1] = (r[6] << 8u); known = (known & ~0x00000002u) | ((known & 0x00000040u) == 0x00000040u ? 0x00000002u : 0u); r[1] = (r[1] >> 8u); known = (known & ~0x00000002u) | ((known & 0x00000002u) == 0x00000002u ? 0x00000002u : 0u);
w_u32((r[7] + 0x00000000u), r[1]); L_8001CD38:;
return r[2]; }

uint32 sub_8001A584(uint32 object)
{
    uint32 rectangle, x, y;
    FUNCTION_MARKER(0x8001A584u, "SLUS_005.10");
    rectangle = r_u32(object + 20u);
    x = r_u32(object);
    y = r_u32(object + 4u);
    return sub_8001A2AC(rectangle, x, y);
}

uint32 sub_8001A4AC(uint32 object, uint32 incoming_v0)
{
    uint32 node, result = incoming_v0;
    FUNCTION_MARKER(0x8001A4ACu, "SLUS_005.10");
    node = r_u32(object + 16u);
    if (node != 0u)
        result = sub_800183EC(node, result);
    node = r_u32(object + 20u);
    result = sub_800183EC(node, result);
    sub_80045088(object);
    return result;
}

uint32 sub_8001AF48(uint32 node, uint32 incoming_v0)
{
    uint32 saved, child, result = incoming_v0;
    FUNCTION_MARKER(0x8001AF48u, "SLUS_005.10");
    while (node != 0u)
    {
        child = r_u32(node + 48u);
        result = sub_8001BDDC(child, result);
        saved = node;
        child = r_u32(node + 56u);
        result = sub_8001AF48(child, result);
        node = r_u32(node + 52u);
        sub_80045088(saved);
    }
    return result;
}

uint32 sub_8001BDDC(uint32 object, uint32 incoming_v0)
{
    uint32 index, pointer, result = incoming_v0;
    FUNCTION_MARKER(0x8001BDDCu, "SLUS_005.10");
    if (object != 0u)
    {
        index = r_u32(0x80065308u);
        pointer = r_u32(object + (index << 2u) + 28u);
        if (pointer != 0u)
            (void)sub_800118B4(pointer);
        index = r_u32(0x80065308u);
        result = object + ((1u - index) << 2u);
        pointer = r_u32(result + 28u);
        if (pointer != 0u)
            sub_80045088(pointer);
        sub_80045088(object);
    }
    return result;
}
