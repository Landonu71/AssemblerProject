/*
* Author: Andrew Gautier
* Date: 2025/03/27
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void beq_immd_assm(void) {
    // Validate opcode
    if (strcmp(OP_CODE, "BEQ") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /* 
        Validate parameter types (registers + immediate) 
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
        Encode binary: I-format (op=0x04) 
    */
    setBits_str(31, "000100");      // Opcode (0x04)
    setBits_num(20, PARAM1.value, 5); // Rt
    setBits_num(25, PARAM2.value, 5); // Rs
    setBits_num(15, PARAM3.value, 16); // Offset (16-bit)

    state = COMPLETE_ENCODE;
}

void beq_immd_bin(void) {
    // Check opcode (0x04)
    if (checkBits(31, "000100") != 0) {  // Fixed: Was "001000" (ADDI's opcode)
        state = WRONG_COMMAND;
        return;
    }

    // Decode fields
    uint32_t Rt = getBits(20, 5);
    uint32_t Rs = getBits(25, 5);
    uint32_t offset = getBits(15, 16);

    // Set instruction parameters (fixed Rt/Rs order)
    setOp("BEQ");
    setParam(1, REGISTER, Rt);  // Destination
    setParam(2, REGISTER, Rs);  // Source
    setParam(3, IMMEDIATE, offset); // Branch offset

    state = COMPLETE_DECODE;
}