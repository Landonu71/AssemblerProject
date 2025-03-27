/*
* Author: Andrew Gautier
* Date: 2025/03/27
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void div_reg_assm(void) {
    // Validate opcode
    if (strcmp(OP_CODE, "DIV") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /* 
        Validate parameter types (both registers) 
    */
    if (PARAM1.type != REGISTER || PARAM2.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    /* 
        Validate register values (≤ 31) 
    */
    if (PARAM1.value > 31 || PARAM2.value > 31) {
        state = INVALID_REG;
        return;
    }

    /* 
        Encode binary: R-format (op=0, funct=0x1A) 
    */
    setBits_str(31, "000000");      // Opcode (0)
    setBits_num(25, PARAM1.value, 5); // Rs (dividend)
    setBits_num(20, PARAM2.value, 5); // Rt (divisor)
    setBits_str(5, "011010");       // Funct (0x1A)
    setBits_num(15, 0, 10);         // Unused (set to 0)

    state = COMPLETE_ENCODE;
}

void div_reg_bin(void) {
    // Check opcode (0) and funct (0x1A)
    if (checkBits(31, "000000") != 0 || checkBits(5, "011010") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Decode registers
    uint32_t Rs = getBits(25, 5);  // Dividend
    uint32_t Rt = getBits(20, 5);  // Divisor

    // Set instruction parameters
    setOp("DIV");
    setParam(1, REGISTER, Rs);  // Dividend
    setParam(2, REGISTER, Rt);  // Divisor

    state = COMPLETE_DECODE;
}