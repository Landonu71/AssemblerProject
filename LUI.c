/*
* Author: Andrew Gautier
* Date: 2025/03/30
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void lui_immd_assm(void) {
    // Validate opcode
    if (strcmp(OP_CODE, "LUI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /* 
        Validate parameter types (1 register + 1 immediate) 
        Note: LUI only uses 1 register (Rt) and 1 immediate.
        Fixed: Removed redundant PARAM2 check (not used in LUI).
    */
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }
    if (PARAM2.type != IMMEDIATE) {  // LUI format: "LUI $rt, imm"
        state = INVALID_PARAM;
        return;
    }

    /* 
        Validate register value (≤ 31) and immediate (≤ 0xFFFF) 
    */
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }
    if (PARAM2.value > 0xFFFF) {
        state = INVALID_IMMED;
        return;
    }

    /* 
        Encode binary: I-format (op=0x0F) 
        LUI encodes as: [op(6)][0(5)][rt(5)][imm(16)]
        Fixed: PARAM2 (immediate) is the only value used after Rt.
    */
    setBits_str(31, "001111");       // Opcode (0x0F)
    setBits_num(20, PARAM1.value, 5); // Rt (destination)
    setBits_num(15, PARAM2.value, 16); // Immediate value (shifted left 16)

    state = COMPLETE_ENCODE;
}

void lui_immd_bin(void) {
    // Check opcode (0x0F)
    if (checkBits(31, "001111") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Decode fields
    uint32_t Rt = getBits(20, 5);    // Destination register
    uint32_t imm16 = getBits(15, 16); // Immediate value

    // Set instruction parameters
    setOp("LUI");
    setParam(1, REGISTER, Rt);      // Destination register
    setParam(2, IMMEDIATE, imm16);  // Immediate value

    state = COMPLETE_DECODE;
}