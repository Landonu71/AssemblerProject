/*
* Author: Andrew Gautier
* Date: 2025/03/30
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void mfhi_reg_assm(void) {
    // Validate opcode
    if (strcmp(OP_CODE, "MFHI") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /* 
        Validate parameter type (single register) 
    */
    if (PARAM1.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    /* 
        Validate register value (≤ 31) 
    */
    if (PARAM1.value > 31) {
        state = INVALID_REG;
        return;
    }

    /* 
        Encode binary: R-format (op=0, funct=0x10)
        Format: [op(6)][0(5)][rd(5)][0(5)][funct(6)]
    */
    setBits_str(31, "000000");       // Opcode (0)
    setBits_num(15, PARAM1.value, 5); // Rd (destination)
    setBits_str(5, "010010");        // Funct (0x10)
    setBits_str(10, "00000");        // Unused (0)
    setBits_str(25, "0000000000");   // Unused (0)

    state = COMPLETE_ENCODE;
}

void mfhi_reg_bin(void) {
    // Check opcode (0) and funct (0x10), with unused bits as 0
    if (checkBits(31, "000000") != 0 || checkBits(5, "010010") != 0 ||
        checkBits(25, "0000000000") != 0 || checkBits(10, "00000") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Decode destination register (Rd)
    uint32_t Rd = getBits(15, 5);

    // Set instruction parameter
    setOp("MFHI");
    setParam(1, REGISTER, Rd);  // Destination

    state = COMPLETE_DECODE;
}