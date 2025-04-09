#include "MIPS_Interpreter.h"

int main(void) {
	// inializes everything
	initAll();

	// buffer for reading/writing
	char buffer[BUFF_SIZE] = { '\0' };

	// startup message
	puts("Welcome to the MIPS-Translatron 3000 Tool");
	puts("ByteForge Systems ©2012");

	// loopps forever
	while (1) {
		// prompts and takes input
		puts("\nPlease enter an option:");
		puts("\t(1) Assembly to Machine Code");
		puts("\t(2) Machine Code to Assembly");
		puts("\t(Test Bench) Test Bench");
		puts("\t(3) Quit");
		printf("\n> ");

		memset(buffer, '\0', BUFF_SIZE);
		gets(buffer, BUFF_SIZE);

		// either calls the assembly menu, the machine menu, or exits the program
		if (strcmp(buffer, "1") == 0) {
			assembly2machine(buffer);
		}
		else if (strcmp(buffer, "2") == 0) {
			machine2assembly(buffer);
		}
		else if (strcmp(buffer, "3") == 0) {
			return 0;
		}
		else if (strcmp(buffer, "Test Bench") == 0) {
			// test bench
			testBench();
		}
		else if (strcmp(buffer, "Test") == 0) {
			// test bench
			test();
		}
		else if (strcmp(buffer, "TEST") == 0) {
			// test bench
			test();
		}
		else if (strcmp(buffer, "Tewst") == 0) {
			test();
		}
		else if (strcmp(buffer, "TEWST") == 0) {
			test();
		}
		else if (strcmp(buffer, "test") == 0) {
			test();
		}
	}
	return 0;
}

/*
	Purpose: dummy function to test code
	Params: none
	Return: none
*/
void test(void) {
	char* buff = "AND $t1, $t2, $t3";
	printf("%s\n", buff);
	parseAssem(buff);
	printResult();
	printAssm();
}

void testBench(void) {

    // Prints out the test bench header
    puts("");
    puts("/===========================/");
    puts("Test Bench Running...");
    puts("/===========================/");
    puts("");

    // Define a structure to hold a single test case
    typedef struct {
        char command[50];     // Assembly instruction as a string
        char expected1[50];   // Expected binary output (formatted)
        char expected2[50];   // Expected hexadecimal output
    } TestCase;

    // Initialize the array of test cases
    TestCase tests[] = {
        {"AND $t1, $t2, $t3", "0000 0001 0100 1011 0100 1000 0010 0100", "0x014b4824"},
        {"ADD $s0, $s1, $s2", "0000 0010 0011 0010 1000 0000 0010 0000", "0x02328020"},
        {"BNE $t0, $t1, #42", "0001 0101 0010 1000 0000 0000 0010 1010", "0x1528002a"},
        {"SLTI $t2, $t3, #5", "0010 1001 0110 1010 0000 0000 0000 0101", "0x296a0005"},
        {"OR $t0, $t1, $t2",  "0000 0001 0010 1010 0100 0000 0010 0101", "0x012a4025"}
    };

    // Determine the number of test cases
    int numTests = sizeof(tests) / sizeof(tests[0]);

    // Buffer to hold the actual binary string generated
    char actualBinary[50];
    int x = 0;

    // Loop through each test case
    for (int i = 0; i < numTests; i++) {
        char command[50];
        strcpy(command, tests[i].command);  // Copy current command into local buffer

        printf("TEST %d/%d: %s\n", i + 1, numTests, tests[i].command);

        // Convert assembly instruction to machine code (binary and hex)
        moddedAssembly2machine(command);

        char instruction[50];
        char appendTo[50] = "";

        // Add appropriate hex prefix
        if (tests[i].expected2[2] == '0') {
            strcpy(appendTo, "0x0");
        } else {
            strcpy(appendTo, "0x");
        }

        // Convert the global `instruct` variable (assumed to hold hex value) to hex string
        itoa(instruct, instruction, 16);
        strcat(appendTo, instruction);  // Complete the hex string
        x = 0;

        // Convert BIN32 to formatted binary string with spaces every 4 bits
        for (int y = 31; y >= 0; y--) {
            actualBinary[x++] = ((BIN32 >> y) & 1) ? '1' : '0';
            if (y % 4 == 0 && y != 0) {
                actualBinary[x++] = ' ';
            }
        }
        actualBinary[x] = '\0';  // Null-terminate the binary string

        // Compare generated binary and hex strings to expected outputs
        if (strcmp(actualBinary, tests[i].expected1) == 0 && strcmp(appendTo, tests[i].expected2) == 0) {
            puts("ASSEMBLY TO HEX TEST PASSED");
        } else {
            // Print error and exit loop if there's a mismatch
            puts("ASSEMBLY TO BINARY AND HEX TEST FAILED");
            
            printf("EXPECTED HEX:    %s\n", tests[i].expected2);
            printf("ACTUAL HEX:      %s\n", appendTo);
            break;
        }

        // Begin test for converting hex back to assembly
        printf("TEST COMMAND HEX TO ASSEMBLY: %s\n", tests[i].command);

        moddedHex2assembly(appendTo);         // Convert hex string back to assembly
        char* temp = getAssemblyString();     // Retrieve generated assembly string

        if (strcmp(temp, tests[i].command) == 0) {
            puts("HEX CODE TO ASSEMBLY TEST PASSED");
        } else {
            puts("HEX TO ASSEMBLY TEST FAILED");
            printf("EXPECTED COMMAND: %s\n", tests[i].command);
            printf("ACTUAL COMMAND:   %s\n", temp);
            break;
        }

		printf("TEST COMMAND BINARY TO ASSEMBLY: %s\n", tests[i].command);

		moddedBinary2assembly(appendTo);

		if (strcmp(temp, tests[i].command) == 0) {
            puts("BINARY TO ASSEMBLY TEST PASSED");
        } else {
            puts("BINARY TO ASSEMBLY TEST FAILED");
            printf("EXPECTED COMMAND: %s\n", tests[i].command);
            printf("ACTUAL COMMAND:   %s\n", temp);
            break;
        }
    }
}

/*
	Purpose: initializes anything that needs to be initialized
	Params: none
	Return: none
*/
void initAll(void) {
	initInstructs();
}


/*
	Purpose: menu for assembly to machine conversion
	Params: char* buff - buffer to be used for reading/writing
	Return: none
*/
void assembly2machine(char* buff) {
	// loops forever
	while (1) {
		// prompts and takes input
		puts("\nEnter a line of assembly:");
		printf("> ");
		memset(buff, '\0', BUFF_SIZE);
		gets(buff, BUFF_SIZE);

		// if the string is empty, go back to the previous menu
		if (strlen(buff) == 0) {
			break;
		}

		// tries to parse the instruction
		parseAssem(buff);

		// checks if there was an error, and encodes if there wasn't
		if (state == NO_ERROR) {
			encode();
		}

		// either prints an error message or the encoded instruction
		printResult();
	}
}


/*
	Purpose: menu for machine to assembly conversion
	Params: char* buff - buffer to be used for reading/writing
	Return: none
*/
void machine2assembly(char* buff) {
	while (1) {
		while (1) {
			// prompts and takes input
			puts("\nPlease select an option:");
			puts("\t(1) Hexadecimal to Assembly");
			puts("\t(2) Binary to Assembly");
			puts("\t[3] Main Menu");
			printf("\n> ");

			memset(buff, '\0', BUFF_SIZE);
			gets(buff, BUFF_SIZE);


			// either calls the hex menu or binary menu
			// otherwise exist back tot he previous menu
			if (strcmp(buff, "1") == 0) {
				hex2assembly(buff);
			}
			else if (strcmp(buff, "2") == 0) {
				binary2assembly(buff);
			}
			else {
				return;
			}
		}
	}
}

void moddedBinary2assembly(char* buff) {
	
		// prompts and takes input
		memset(buff, '\0', BUFF_SIZE);
		char* test = malloc(strlen(buff) + 1);
		strcpy(test, buff);

		// tries to parse the number
		parseBin(buff);

		// checks if there was an error, and decodes if there wasn't
		if (state == NO_ERROR) {
			decode();
		}

		// either prints an error message or the encoded instruction
}


void moddedHex2assembly(char* buff) {
		
	// prompts and takes input
	memset(buff, '\0', BUFF_SIZE);
	char* test = malloc(strlen(buff) + 1);
	strcpy(test, buff);
		

	
		
	// tries to parse the number
	parseHex(test);
		
	// checks if there was an error, and decodes if there wasn't
	if (state == NO_ERROR) {
		decode();
	}
}

void moddedAssembly2machine(char* buff) {
	
		char* test = malloc(strlen(buff) + 1);
		strcpy(test, buff);
		// prompts and takes input
		memset(buff, '\0', BUFF_SIZE);
		strcpy(buff, test);
		buff[strlen(buff)] = '\0';
		// if the string is empty, go back to the previous menu
		if (strlen(buff) == 0) {
			return;
		}

		// tries to parse the instruction
		parseAssem(buff);

		// checks if there was an error, and encodes if there wasn't
		if (state == NO_ERROR) {
			encode();
		}

	
}



/*
	Purpose: menu for binary to assembly conversion
	Params: char* buff - buffer to be used for reading/writing
	Return: none
*/
void binary2assembly(char* buff) {
	while (1) {
		// prompts and takes input
		puts("\nEnter Binary:");
		printf("> ");
		memset(buff, '\0', BUFF_SIZE);
		gets(buff, BUFF_SIZE);

		// if the string is empty, go back to the previous menu
		if (strlen(buff) == 0) {
			break;
		}

		// tries to parse the number
		parseBin(buff);

		// checks if there was an error, and decodes if there wasn't
		if (state == NO_ERROR) {
			decode();
		}

		// either prints an error message or the encoded instruction
		printResult();
	}
}


/*
	Purpose: menu for hex to assembly conversion
	Params: char* buff - buffer to be used for reading/writing
	Return: none
*/
void hex2assembly(char* buff) {
	while (1) {
		// prompts and takes input
		puts("\nEnter Hex:");
		printf("> ");
		memset(buff, '\0', BUFF_SIZE);
		gets(buff, BUFF_SIZE);

		// if the string is empty, go back to the previous menu
		if (strlen(buff) == 0) {
			break;
		}

		// tries to parse the number
		parseHex(buff);

		// checks if there was an error, and decodes if there wasn't
		if (state == NO_ERROR) {
			decode();
		}

		printResult();
	}
}


char* getAssemblyString(void) {
    static char fullStr[256]; // static or dynamically allocated for return
    char temp[50];

    fullStr[0] = '\0'; // clear buffer

    // Add opcode
    snprintf(fullStr, sizeof(fullStr), "%s ", assm_instruct.op);

    // PARAM1
    if (PARAM1.type != EMPTY) {
        strcat(fullStr, getParamString(&PARAM1, temp, sizeof(temp)));
    }

    // PARAM2
    if (PARAM2.type != EMPTY) {
        strcat(fullStr, ", ");
        strcat(fullStr, getParamString(&PARAM2, temp, sizeof(temp)));
    }

    // PARAM3
    if (PARAM3.type != EMPTY) {
        if (PARAM3.type == REGISTER && (strcmp(OP_CODE, "LW") == 0 || strcmp(OP_CODE, "SW") == 0)) {
            strcat(fullStr, "(");
            strcat(fullStr, getParamString(&PARAM3, temp, sizeof(temp)));
            strcat(fullStr, ")");
        } else {
            strcat(fullStr, ", ");
            strcat(fullStr, getParamString(&PARAM3, temp, sizeof(temp)));
        }
    }

    // PARAM4
    if (PARAM4.type != EMPTY) {
        strcat(fullStr, ", ");
        strcat(fullStr, getParamString(&PARAM4, temp, sizeof(temp)));
    }

    return fullStr;
}

char* getParamString(struct Param* param, char* buffer, size_t size) {
     // initialize to empty string

    switch (param->type) {
        case EMPTY:
            snprintf(buffer, size, "<>");
            break;

        case REGISTER: {
            uint32_t temp = param->value;
            if (temp == 0) {
                snprintf(buffer, size, "$zero");
            } else if (temp == 2 || temp == 3) {
                snprintf(buffer, size, "$v%d", temp - 2);
            } else if (temp >= 4 && temp <= 7) {
                snprintf(buffer, size, "$a%d", temp - 4);
            } else if (temp >= 8 && temp <= 15) {
                snprintf(buffer, size, "$t%d", temp - 8);
            } else if (temp >= 16 && temp <= 23) {
                snprintf(buffer, size, "$s%d", temp - 16);
            } else if (temp == 24 || temp == 25) {
                snprintf(buffer, size, "$t%d", temp - 16);
            } else if (temp == 28) {
                snprintf(buffer, size, "$gp");
            } else if (temp == 29) {
                snprintf(buffer, size, "$sp");
            } else if (temp == 30) {
                snprintf(buffer, size, "$fp");
            } else if (temp == 31) {
                snprintf(buffer, size, "$ra");
            } else {
                snprintf(buffer, size, "<reg:%u>", temp);
            }
            break;
        }

        case IMMEDIATE:
            snprintf(buffer, size, "#%u", param->value);
            break;

        default:
            snprintf(buffer, size, "<unknown: %d, %d>", param->type, param->value);
            break;
    }

    return buffer;
}