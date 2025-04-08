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


	// Initiazlies the test case char array and adds all test cases
	char testCases[5][50];
	strcpy(testCases[0], "AND $t1, $t2, $t3");
	strcpy(testCases[1], "AND $t1, $t2, $t3");
	strcpy(testCases[2], "AND $t1, $t2, $t3");
	strcpy(testCases[3], "AND $t1, $t2, $t3");
	strcpy(testCases[4], "AND $t1, $t2, $t3");
	

	// Initiazlies the expected results char array and adds all expected results
	char expectedResults[5][50];
	strcpy(expectedResults[0], "0000 0001 0100 1011 0100 1000 0010 0100");
	strcpy(expectedResults[1], "0000 0001 0100 1011 0100 1000 0010 0100");
	strcpy(expectedResults[2], "0000 0001 0100 1011 0100 1000 0010 0100");
	strcpy(expectedResults[3], "0000 0001 0100 1011 0100 1000 0010 0100");
	strcpy(expectedResults[4], "0000 0001 0100 1011 0100 1000 0010 0100");

	// Initilizes the number of test cases
	int numTests = sizeof(testCases) / sizeof(testCases[0]);
	
	// Initilizes the binary variable to be used for testing
	char actualBinary[50];
	

	int x = 0;

	// Loops through every test case 
	for(int i = 0; i < numTests; i++) {
		
		// For some reason, the test cases will not print correctly after the first one.  I have no idea why.
		printf("TEST COMMAND: %s\n", testCases[i]);

		// Calls the modded assembly to machine function to convert the test case to binary
		moddedAssembly2machine(testCases[i]);

		x = 0;
		// Loops through every bit in the BIN32 variable and copies the each bit to the actualBinary array
		for (int y = 31; y >= 0; y--) {
			
			// Sets each bit from BIN32 to the actualBinary array
			actualBinary[x++] = ((BIN32 >> y) & 1) ? '1' : '0';
			
			// Adds a space every 4 bits for readability
			if (y % 4 == 0 && y != 0) {
				actualBinary[x++] = ' ';
			}
		}

		// Null terminates the string
		actualBinary[x] = '\0';

		// Prints "TEST PASSED" if the test case passed, otherwise prints "TEST FAILED" and the expected and actual results
		if(strcmp(actualBinary, expectedResults[i]) == 0) {
			puts("TEST PASSED");
		}

		else {
			puts("TEST FAILED");
			printf("EXPECTED BINARY: %s\n", expectedResults[i]);
			printf("ACTUAL BINARY: %s\n", actualBinary);
			break;
		}

		for(int j = 0; j < numTests; j++) {
			moddedHex2assembly(expectedResults[j]);
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
void moddedHex2assembly(char* buff) {
	while (1) {
		// prompts and takes input
		char* test = malloc(strlen(buff) + 1);
		memset(buff, '\0', BUFF_SIZE);
		strcpy(buff, test);
		buff[strlen(buff)] = '\0';

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

		// either prints an error message or the encoded instruction
		printResult();
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

		// either prints an error message or the encoded instruction
		printResult();
	}
}