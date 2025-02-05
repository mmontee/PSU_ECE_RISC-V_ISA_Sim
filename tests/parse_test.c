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


int main(int argc, char *argv[])
{

	input_params_t userParams = parse_args(argc, argv);

	memory_t programMemory = parse_input(&userParams);
	printf("Instruction count = %d\n", userParams.instructionCount);
	// Print the bytes
	printf("Printe bytes with no sign extension-----------------\n");
	for(uint32_t i = 0; i < userParams.instructionCount * 4; i++)
	{
		printf("Index = %d : Byte 0x%08X\n", i , read_byte(i, 0, programMemory));
	}
	printf("\n");
	printf("Print bytes with sign extension-----------------\n");
	for(uint32_t i = 0; i < userParams.instructionCount * 4; i++)
	{
		printf("Index = %d : Byte 0x%08X\n", i , read_byte(i, 1, programMemory));
	}
	printf("\n");
	// Print the words
	printf("Print the words-----------------\n");
	for(uint32_t i = 0; i < userParams.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_word(i, programMemory));
	}
	printf("\n");
	// Print the lower half
	printf("Print lower half of the words with no sign extension-----------------\n");
	for(uint32_t i = 0; i < userParams.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_lower_half(i, 0, programMemory));
	}
	printf("\n");
	printf("Print lower half of the words with sign extension-----------------\n");
	for(uint32_t i = 0; i < userParams.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_lower_half(i, 1, programMemory));
	}
	// Print the upper half
	printf("Print upper half of the words with no sign extension-----------------\n");
	for(uint32_t i = 0; i < userParams.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_upper_half(i, 0, programMemory));
	}
	printf("\n");
	printf("Print upper half of the words with sign extension-----------------\n");
	for(uint32_t i = 0; i < userParams.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_upper_half(i, 1, programMemory));
	}
	printf("\n");

	// Print the words again
	printf("Print the words-----------------\n");
	for(uint32_t i = 0; i < userParams.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_word(i, programMemory));
	}
	printf("\n");
	// Modify some words
	printf("Write 0x1234ABCD to index 0\n");
	write_word(0, 0x1234ABCD, programMemory);
	printf("Write 0xFEDCBA33 to index 16\n");
	write_word(16, 0xFEDCBA33, programMemory);
	printf("\n");

	// Modify some half words
	printf("Write 0xXXXXBEEF to index 4\n");
	store_half_word(0, 0x1234ABCD, programMemory);
	printf("\n");

	// Modify some half words
	printf("Write 0xXXXXFFXX to index 8 + 1\n");
	store_byte(8 + 1, 0xFF, programMemory);
	printf("Write 0xEEXXXXXX to index 8 + 3\n");
	store_byte(8 + 3, 0xEE, programMemory);
	printf("\n");

	// Print the words again
	printf("Print the words-----------------\n");
	for(uint32_t i = 0; i < userParams.instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_word(i, programMemory));
	}
	printf("\n");
	printf("Load 0xDEAD1234 in reg x00 and print the register contents-----------------\n");
	registers[0] = 0xDEAD1234;
	print_reg(0, registers[0]);
	fclose(userParams.inputFilePath);
	return 0;
}

