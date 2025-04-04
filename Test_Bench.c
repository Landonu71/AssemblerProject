/*
* Author: Landon Urcho
* Date: 04/04/2025
* ByteForge Systems
* MIPS-Translatron 3000
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MIPS_Instruction.h"
#include "MIPS_Interpreter.h"
#include "global_data.h"

Assm_Instruct assm_instruct;
#define PARAM1 assm_instruct.param1
#define PARAM2 assm_instruct.param2
#define PARAM3 assm_instruct.param3
#define PARAM4 assm_instruct.param4

const char* modifiedassembly2machine(char* buff) {
	
    char* machine_code = malloc(256 * sizeof(char));
	memset(buff, '\0', BUFF_SIZE);

	// tries to parse the instruction
	parseAssem(buff);

    char* test = malloc(256 * sizeof(char));
    readParam(test, &PARAM1);
    machine_code = test;
    readParam(test, &PARAM2);
    machine_code = strcat(machine_code, test);
    readParam(test, &PARAM3);
    machine_code = strcat(machine_code, test);
    readParam(test, &PARAM4);
    machine_code = strcat(machine_code, test);

	// checks if there was an error, and encodes if there wasn't
	if (state == NO_ERROR) {
		encode();
	}

    return machine_code;
}



int run_MIPS_to_bin_test(const char* unassembled, const char* expected) {

    char* assembled = malloc(256 * sizeof(char));
    //assembled = assembly2machine(unassembled);

    if (assembled == NULL) {
        printf("Error: Assembly to machine conversion failed. Assembly code entered: %s\n", unassembled);
        return -1;
    }

    if(strcmp(assembled, expected) != 0) {
        printf("Test failed. Actual binary result: %s\nExpected binary result: %s", unassembled, expected);
    }
    
    return 0;
}

int run_bin_to_MIPS_test(const char* assembled, const char* expected) {

    char* unassembled = malloc(256 * sizeof(char));
    //unassembled = machine2assembly(assembled);

    if (unassembled == NULL) {
        printf("Error: Machine to assembly conversion failed. Binary code entered: %s\n", assembled);
        return -1;
    }

    if(strcmp(unassembled, expected) != 0) {
        printf("Test failed. Actual assembly result: %s\nExpected assembly result: %s", assembled, expected);
    }
    
    return 0;
}

int main() {
    char* test = malloc(256 * sizeof(char));
    test = modifiedassembly2machine("ADD $t0, $t1, $t2");
    printf("%s", test);
}