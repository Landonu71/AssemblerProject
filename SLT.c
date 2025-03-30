/*
* Author: Andrew Gautier
* Date: 2025/03/30
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include "Instruction.h"

void slt_reg_assm(void) {
    // Validate opcode
    if (strcmp(OP_CODE, "SLT") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    /* 
        Validate parameter types (all registers) 
    */
    if (PARAM1.type != REGISTER || PARAM2.type != REGISTER || PARAM3.type != REGISTER) {
        state = MISSING_REG;
        return;
    }

    /* 
        Validate register values (≤ 31) 
    */
    if (PARAM1.value > 31 || PARAM2.value > 31 || PARAM3.value > 31) {
        state = INVALID_REG;
        return;
    }

    /* 
        Encode binary: R-format (op=0, funct=0x2A)
        Format: [op(6)][rs(5)][rt(5)][rd(5)][shamt(5)][funct(6)]
    */
    setBits_num(31, 0, 6);          // Opcode (0)
    setBits_str(5, "101010");       // Funct (0x2A)
    setBits_num(15, PARAM1.value, 5); // Rd (destination)
    setBits_num(25, PARAM2.value, 5); // Rs (source 1)
    setBits_num(20, PARAM3.value, 5); // Rt (source 2)

    state = COMPLETE_ENCODE;
}

void slt_reg_bin(void) {
    // Check opcode (0) and funct (0x2A)
    if (checkBits(31, "000000") != 0 || checkBits(5, "101010") != 0) {
        state = WRONG_COMMAND;
        return;
    }

    // Decode registers
    uint32_t Rd = getBits(15, 5);
    uint32_t Rs = getBits(25, 5);
    uint32_t Rt = getBits(20, 5);

    // Set instruction parameters
    setOp("SLT");
    setParam(1, REGISTER, Rd);  // Destination
    setParam(2, REGISTER, Rs);  // Source 1
    setParam(3, REGISTER, Rt);  // Source 2

    state = COMPLETE_DECODE;
}