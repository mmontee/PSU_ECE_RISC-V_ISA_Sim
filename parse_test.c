#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "./risc_sim.h"

int main(int argc, char *argv[])
{
	parse_args(argc, argv);


	parse_intput(inputFilePath, inputFileType);
	// Print the bytes
	printf("Print bytes with no sign extension-----------------\n");
	for(int i = 0; i < instructionCount * 4; i++)
	{
		printf("Index = %d : Byte 0x%08X\n", i , read_byte(i, 0));
	}
	printf("\n");
	printf("Print bytes with sign extension-----------------\n");
	for(int i = 0; i < instructionCount * 4; i++)
	{
		printf("Index = %d : Byte 0x%08X\n", i , read_byte(i, 1));
	}
	printf("\n");
	// Print the words
	printf("Print the words-----------------\n");
	for(int i = 0; i < instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_word(i));
	}
	printf("\n");
	// Print the lower half
	printf("Print lower half of the words with no sign extension-----------------\n");
	for(int i = 0; i < instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_lower_word(i, 0));
	}
	printf("\n");
	printf("Print lower half of the words with sign extension-----------------\n");
	for(int i = 0; i < instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_lower_word(i, 1));
	}
	// Print the upper half
	printf("Print upper half of the words with no sign extension-----------------\n");
	for(int i = 0; i < instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_upper_word(i, 0));
	}
	printf("\n");
	printf("Print upper half of the words with sign extension-----------------\n");
	for(int i = 0; i < instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_upper_word(i, 1));
	}
	printf("\n");
	// Modify some words
	printf("Write 0x1234ABCD to index 0\n");
	write_word(0, 0x1234ABCD);
	printf("Write 0xFEDCBA33 to index 16\n");
	write_word(16, 0xFEDCBA33);
	printf("\n");
	// Print the words again
	printf("Print the words-----------------\n");
	for(int i = 0; i < instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_word(i));
	}
	printf("\n");
	printf("Load 0xDEAD1234 in reg x00 and print the register contents-----------------\n");
	registers[0] = 0xDEAD1234;
	print_reg(0);
	fclose(inputFilePath);
	return 0;
}

