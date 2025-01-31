#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Definitions
#define MAX_SIZE 64000

// Globals
uint8_t array[MAX_SIZE];
uint32_t arrayIndex = 0;
const char *defaultPath = "./risc.din";
uint32_t instructionCount = 0;

// Given the file pointer read file into program memory.
void parse_intput(FILE *fp)
{
	char line[64];
	// Get a line from the file or fail trying
	while (fgets(line, sizeof(line), fp) != NULL)
	{
		instructionCount++;
		// Following the ':' is the command, find the ':'
		int count = 0;
		char peekChar;
		peekChar = line[count];
		while(peekChar != ':')
		{
			count++;
			peekChar = line[count];
		}
		// Now copy the 8 byte word into memory 1 byte at a time
		count += 2; // Jump past the ': '
		for(int i = 6; i >= 0; i-=2)
		{
			char byteString[3] = {0, 0, '\0'};
			memcpy(byteString, &line[count + i], 2);
			array[arrayIndex] = (int)strtol(byteString, NULL, 16);
			arrayIndex++;
		}
	}

}
// Read a word from memory. User must provide aligned reference or fails.
uint32_t read_word(int offset)
{
	// If not word aligned fail.
	if((offset % 4) != 0)
	{
		printf("un-aligned reference\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		uint32_t word = 0;
		for(int i = 0; i < 4; i++)
		{
			word |= (array[offset + i] << i * 8);
		}
		return word;
	}
}

// Write a given word to memory. User must provide aligned reference or fails.
void write_word(int offset, uint32_t word)
{
	// If not word aligned fail.
	if((offset % 4) != 0)
	{
		printf("un-aligned reference\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		for(int i = 0; i < 4; i++)
		{
			array[offset + i] = (word >> i * 8);
		}
	}
}
