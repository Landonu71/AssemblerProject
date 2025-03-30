/*
* Author: Andrew Gautier
* Date: 2025/03/30
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void sw_immd_assm(void) {
    // Validate opcode
    if (strcmp(OP_CODE, "SW") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /* 
        Validate parameter types:
        - PARAM1: Source register (Rt)
        - PARAM2: Offset (immediate)
        - PARAM3: Base register (Rs)
    */
    if (PARAM1.type != REGISTER || PARAM3.type != REGISTER) {
        state = MISSING_REG;
        return;
    }
    if (PARAM2.type != IMMEDIATE) {
        state = INVALID_IMMED;
        return;
    }

    /* 
        Validate register values (≤ 31) and unsigned immediate (≤ 0xFFFF) 
    */
    if (PARAM1.value > 31 || PARAM3.value > 31) {
        state = INVALID_REG;
        return;
    }
    if (PARAM2.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

    /* 
        Encode binary: I-format (op=0x2B)
        Format: [op(6)][rs(5)][rt(5)][offset(16)]
    */
    setBits_str(31, "101011");       // Opcode (0x2B)
    setBits_num(20, PARAM1.value, 5); // Rt (source)
    setBits_num(25, PARAM3.value, 5); // Rs (base)
    setBits_num(15, PARAM2.value, 16); // Offset (unsigned)

    state = COMPLETE_ENCODE;
}

void sw_immd_bin(void) {
    // Check opcode (0x2B)
    if (checkBits(31, "101011") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Decode fields
    uint32_t Rt = getBits(20, 5);    // Source register
    uint32_t Rs = getBits(25, 5);    // Base register
    uint32_t offset = getBits(15, 16); // Offset

    // Set instruction parameters
    setOp("SW");
    setParam(1, REGISTER, Rt);      // Source
    setParam(2, IMMEDIATE, offset); // Offset
    setParam(3, REGISTER, Rs);      // Base

    state = COMPLETE_DECODE;
}