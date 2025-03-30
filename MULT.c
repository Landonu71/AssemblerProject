/*
* Author: Andrew Gautier
* Date: 2025/03/30
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void mult_reg_assm(void) {
    // Validate opcode
    if (strcmp(OP_CODE, "MULT") != 0) {
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
        Encode binary: R-format (op=0, funct=0x18)
        Format: [op(6)][rs(5)][rt(5)][0(10)][funct(6)]
    */
    setBits_str(31, "000000");       // Opcode (0)
    setBits_num(25, PARAM1.value, 5); // Rs (multiplicand)
    setBits_num(20, PARAM2.value, 5); // Rt (multiplier)
    setBits_str(5, "011000");        // Funct (0x18)
    setBits_str(15, "0000000000");   // Unused (0)

    state = COMPLETE_ENCODE;
}

void mult_reg_bin(void) {
    // Check opcode (0) and funct (0x18), with unused bits as 0
    if (checkBits(31, "000000") != 0 || checkBits(5, "011000") != 0 ||
        checkBits(15, "0000000000") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Decode registers
    uint32_t Rs = getBits(25, 5);  // Multiplicand
    uint32_t Rt = getBits(20, 5);  // Multiplier

    // Set instruction parameters
    setOp("MULT");
    setParam(1, REGISTER, Rs);
    setParam(2, REGISTER, Rt);

    state = COMPLETE_DECODE;
}