# MIPS-Translatron 3000

A C-based MIPS assembler and disassembler tool for converting between MIPS assembly and machine code. Developed by ByteForge Systems.

## Features

- Converts MIPS assembly instructions to machine code (hex and binary)
- Converts machine code (hex or binary) back to MIPS assembly
- Supports a wide range of MIPS instructions (arithmetic, logic, memory, branch, etc.)
- Includes a test bench for automated verification of instruction encoding/decoding

## Project Structure

```
ADD.c         # ADD instruction implementation
ADDI.c        # ADDI instruction implementation
AND.c         # AND instruction implementation
ANDI.c        # ANDI instruction implementation
BEQ.c         # BEQ instruction implementation
BNE.c         # BNE instruction implementation
DIV.c         # DIV instruction implementation
LUI.c         # LUI instruction implementation
LW.c          # LW instruction implementation
MFHI.c        # MFHI instruction implementation
MFLO.c        # MFLO instruction implementation
MULT.c        # MULT instruction implementation
OR.c          # OR instruction implementation
ORI.c         # ORI instruction implementation
SLT.c         # SLT instruction implementation
SLTI.c        # SLTI instruction implementation
SUB.c         # SUB instruction implementation
SW.c          # SW instruction implementation
MIPS_Instruction.c/.h # Core instruction parsing, encoding, decoding logic
MIPS_Interpreter.c/.h # Main program logic and user interface
global_data.h # Global variables and enums
Instruction.h # Instruction function declarations
gen_gcc_cmd.py # Helper script for building the project
.vscode/      # VSCode configuration files
```

## Building

You can build the project using GCC. A helper script is provided:

```sh
python3 gen_gcc_cmd.py --run
```

Or manually:

```sh
gcc *.c -o MIPS_translatron
```

## Usage

Run the compiled executable:

```sh
./MIPS_translatron
```

You will be presented with a menu to:
- Convert assembly to machine code
- Convert machine code to assembly
- Run the test bench

Follow the prompts to enter instructions or machine code.

## Supported Instructions

- Arithmetic: ADD, ADDI, SUB, MULT, DIV
- Logic: AND, ANDI, OR, ORI
- Comparison: SLT, SLTI
- Memory: LW, SW, LUI
- Branch: BEQ, BNE
- Special: MFHI, MFLO

## Testing

To run the built-in test bench, select the "Test Bench" option from the main menu. This will automatically verify encoding and decoding for a suite of instructions.

## Authors

- Andrew Gautier
- Ol' Jim
- Ian Jackson

## License

This project is for educational purposes.
