/*
* Author: Andrew Gautier
* Date: 2025/03/30
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void ori_immd_assm(void) {
    // Validate opcode
    if (strcmp(OP_CODE, "ORI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /* 
        Validate parameter types:
        - PARAM1: Destination register (Rt)
        - PARAM2: Source register (Rs)
        - PARAM3: Unsigned immediate
    */
    if (PARAM1.type != REGISTER || PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }
    if (PARAM3.type != IMMEDIATE) {
        state = INVALID_PARAM;
        return;
    }

    /* 
        Validate register values (≤ 31) and immediate (≤ 0xFFFF) 
    */
    if (PARAM1.value > 31 || PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }
    if (PARAM3.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

    /* 
        Encode binary: I-format (op=0x0D)
        Format: [op(6)][rs(5)][rt(5)][imm(16)]
    */
    setBits_str(31, "001101");       // Opcode (0x0D)
    setBits_num(25, PARAM2.value, 5); // Rs (source)
    setBits_num(20, PARAM1.value, 5); // Rt (destination)
    setBits_num(15, PARAM3.value, 16); // Unsigned immediate

    state = COMPLETE_ENCODE;
}

void ori_immd_bin(void) {
    // Check opcode (0x0D)
    if (checkBits(31, "001101") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Decode fields
    uint32_t Rs = getBits(25, 5);    // Source register
    uint32_t Rt = getBits(20, 5);    // Destination register
    uint32_t imm16 = getBits(15, 16); // Unsigned immediate

    // Set instruction parameters
    setOp("ORI");
    setParam(1, REGISTER, Rt);      // Destination
    setParam(2, REGISTER, Rs);      // Source
    setParam(3, IMMEDIATE, imm16);  // Immediate

    state = COMPLETE_DECODE;
}