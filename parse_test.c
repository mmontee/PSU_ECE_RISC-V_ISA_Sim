/* 	Simple C program to parse .din into commands and addresses.
	A file path can be given as process argument. Otherwise the default is used.
	Program assumes perect input data and structure.

	Mitch Montee 11/05/24
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "./risc_sim.h"

// Definitions
#define DEBUG


int main(int argc, char *argv[])
{
	// Open the default file or the file given as an argument
	FILE *inputFile;
	if(argc <= 1)
	{
		inputFile = fopen(defaultPath, "r");
	}
	else
	{
		inputFile = fopen(argv[1], "r");
		printf("%s\n", argv[1]);
	}

	parse_intput(inputFile);

	#ifdef DEBUG
	for(int i = 0; i < instructionCount * 4; i++)
	{
		printf("Index = %d : Byte 0x%02X\n", i , array[i]);
	}
	printf("\n");
	for(int i = 0; i < instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_word(i));
	}
	printf("\n");
	printf("Write 0x1234ABCD to index 0\n");
	write_word(0, 0x1234ABCD);
	printf("Write 0xFEDCBA33 to index 16\n\n");
	write_word(16, 0xFEDCBA33);
	for(int i = 0; i < instructionCount * 4; i+=4)
	{
		printf("@index = %d :  word = 0x%08X\n", i, read_word(i));
	}
	#endif
	fclose(inputFile);
	return 0;
}

