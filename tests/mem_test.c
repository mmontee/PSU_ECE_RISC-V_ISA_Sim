#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../modules/risc_sim.h"
#include "../modules/memory.h"

uint32_t registers[32];
//const char *defaultPath = "./risc.din";


void print_reg(uint8_t regNum, uint32_t regVal)
{
        //uint32_t localReg = registers[reg];
        printf("REG x%02d = 0x%08X = ", regNum, regVal);
        for(int i = 0; i < 32; i++)
        {
                int tempBit = (regVal & (0x80000000 >> i))? 1: 0;
                printf("%d", tempBit);
        }
        printf("\n");
}

hardware_t hardware;
int main(int argc, char *argv[])
{

	// Read User arguments
    input_params_t userParams = parse_args(argc, argv);
    hardware.programCounter = userParams.startAddress;
    // Load input file into memory.
    hardware.programMemory = parse_input(&userParams);
    hardware.programMemory.startAddress = userParams.startAddress;
    hardware.programMemory.heapSize = userParams.heapSize;
    hardware.programMemory.stackSize = userParams.stackSize;

	printf("Instruction count = %d\n", hardware.programMemory.instructionCount);
	// Print the bytes
	printf("Printe bytes with no sign extension-----------------\n");
	for(uint32_t i = 0; i < hardware.programMemory.instructionCount * 4; i++)
	{
		printf("Index = %d : Byte 0x%08X\n", i , read_memory(i, 0, &hardware.programMemory, 1));
	}
	printf("\n");
	printf("Print bytes with sign extension-----------------\n");
	for(uint32_t i = 0; i < hardware.programMemory.instructionCount * 4; i++)
	{
		printf("Index = %d : Byte 0x%08X\n", i , read_memory(i, 1, &hardware.programMemory, 1));
	}
	printf("\n");
	// Print the words
	printf("Print the words-----------------\n");
	for(uint32_t i = 0; i < hardware.programMemory.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_memory(i, 0, &hardware.programMemory, 4));
	}
	printf("\n");
	// Print the lower half
	printf("Print half words with no sign extension-----------------\n");
	for(uint32_t i = 0; i < hardware.programMemory.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_memory(i, 0, &hardware.programMemory, 2));
	}
	printf("\n");
	printf("Print half words with sign extension-----------------\n");
	for(uint32_t i = 0; i < hardware.programMemory.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_memory(i, 1, &hardware.programMemory, 2));
	}

	printf("\n");
	// Modify some words
	printf("Write 0x1234ABCD to index 0\n");
    write_memory(0, &hardware.programMemory, 4, 0x1234ABCD);
	printf("Write 0xFEDCBA33 to index 16\n");
    write_memory(16, &hardware.programMemory, 4, 0xFEDCBA33);
	printf("\n");

	// Modify some half words
	printf("Write 0xDEADBEEF to index 4\n");
    write_memory(0, &hardware.programMemory, 2, 0xDEADBEEF);
	printf("\n");

	// Modify some half words
	printf("Write 0xXXXXFFXX to index 8 + 1\n");
    write_memory(8 + 1, &hardware.programMemory, 1, 0xFF);
	printf("Write 0xEEXXXXXX to index 8 + 3\n");
    write_memory(8 + 3, &hardware.programMemory, 1, 0xEE);
	printf("\n");

	// Print the words again
	printf("Print the words-----------------\n");
	for(uint32_t i = 0; i < hardware.programMemory.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_memory(i, 0, &hardware.programMemory, 4));
	}
	printf("\n");
	fclose(userParams.inputFilePath);
	return 0;
}

