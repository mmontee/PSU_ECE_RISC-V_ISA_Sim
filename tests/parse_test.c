#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../modules/risc_sim.h"
#include "../modules/memory.h"


//const char *defaultPath = "./risc.din";


hardware_t hardware;
int main(int argc, char *argv[])
{

	input_params_t userParams = parse_args(argc, argv);
    hardware.programCounter = userParams.startAddress;
    hardware.programMemory = parse_input(&userParams);

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
	printf("Print half of the words with no sign extension-----------------\n");
	for(uint32_t i = 0; i < hardware.programMemory.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_memory(i, 0, &hardware.programMemory, 2));
	}
	printf("\n");
	printf("Print half of the words with sign extension-----------------\n");
	for(uint32_t i = 0; i < hardware.programMemory.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_memory(i, 1, &hardware.programMemory, 2));
	}
	

	// Print the words again
	printf("Print the words-----------------\n");
	for(uint32_t i = 0; i < hardware.programMemory.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_memory(i, 0, &hardware.programMemory, 4));
	}
	printf("\n");
	// Modify some words
	printf("Write 0x1234ABCD to index 0\n");
	write_memory(0, &hardware.programMemory, 4, 0x1234ABCD);
	printf("Write 0xFEDCBA33 to index 16\n");
	write_memory(16, &hardware.programMemory, 4, 0xFEDCBA33);
	printf("\n");

	// Modify some half words
	printf("Write 0xXXXXBEEF to index 4\n");
	write_memory(16, &hardware.programMemory, 2, 0x1234ABCD);
	printf("\n");

	// Modify some half words
	printf("Write 0xXXXXFFXX to index 8 + 1\n");
	write_memory((8 + 1), &hardware.programMemory, 1, 0xFF);
	printf("Write 0xEEXXXXXX to index 8 + 3\n");
	write_memory((8 + 3), &hardware.programMemory, 1, 0xEE);
	printf("\n");

	// Print the words again
	printf("Print the words-----------------\n");
	for(uint32_t i = 0; i < hardware.programCounter * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_memory(i, 0, &hardware.programMemory, 4));
	}
	printf("\n");
	printf("Load 0xDEAD1234 in reg x00 and print the register contents-----------------\n");
	hardware.registers[0] = 0xDEAD1234;
	print_bits(0, &hardware.registers[0]);
	fclose(userParams.inputFilePath);
	return 0;
}

