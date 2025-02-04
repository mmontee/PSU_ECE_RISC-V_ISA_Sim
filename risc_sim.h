#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Definitions
#define MAX_SIZE 64000

// Globals
uint8_t programMemory[MAX_SIZE];
uint32_t registers[32];
const char *defaultPath = "./risc.din";
uint32_t instructionCount = 0;
uint32_t startAddress = 0;
uint32_t stackSize = 0;
FILE *inputFilePath;
uint32_t inputFileType = 0;

void parse_args(int argc, char *argv[])
{

	if(argc <= 1)
	{
		inputFilePath = fopen(defaultPath, "r");
	}
	else
	{
		int count = 1;
		while(count < argc)
		{
			char *temp = argv[count];
			if(strcmp(temp,"-f") == 0)
			{
				inputFilePath = fopen(argv[count + 1], "r");
				printf("Input file path taken : %s\n", argv[count + 1]);
			}
			else if(strcmp(temp, "-s") == 0)
			{
				stackSize = strtoul(argv[count + 1], NULL, 0);
				printf("Stack Size = %d\n", stackSize);
			}
			else if(strcmp(temp, "-a") == 0)
			{
				startAddress = strtoul(argv[count + 1], NULL, 0);
				printf("Start Address = %d\n", startAddress);
			}
			else if(strcmp(temp, "-ft") == 0)
			{
				inputFileType = strtoul(argv[count + 1], NULL, 0);
				printf("Start Address = %d\n", startAddress);
			}
			count++;
		}
	}
}


// Given the file pointer read file into program memory.
// addressFlag = 0 for sequential idexing
// addressFlag = address indexing. This mode assumes 32bit words and needs an alligned address.
void parse_intput(FILE *fp, int addressFlag)
{
	char line[64];
        if(addressFlag == 0)
        {
        	uint32_t index = 0;
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
				programMemory[startAddress + index] = (int)strtol(byteString, NULL, 16);
				index++;
			}
		}
        }
        else
        {
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
			char addressString[count + 1];
			int index = 0;
			// the characters from 0 to count shoud be the address
			memcpy(addressString, &line[0], count);
			uint32_t baseAddress = (int)strtol(addressString, NULL, 16);
			if(baseAddress % 4 != 0)
			{
				printf("un-aligned reference. Address : 0x%08X\n", baseAddress);
				exit(EXIT_FAILURE);
			}
			printf("count = %d : BA = %d\n",count,  baseAddress);
			// Now copy the 8 byte word into memory 1 byte at a time
			count += 2; // Jump past the ': '
			for(int i = 6; i >= 0; i-=2)// Every two characters is a byte.
			{
				char byteString[3] = {0, 0, '\0'};
				memcpy(byteString, &line[count + i], 2);
				programMemory[startAddress + baseAddress + index] = (int)strtol(byteString, NULL, 16);
				index++;
			}
			printf("Base: %d + %d = %d\n", baseAddress, index, programMemory[startAddress + baseAddress + index]);
		}
        }
}
// Read a word from memory. User must provide aligned reference or fails.
uint32_t read_word(uint32_t address)
{
	// If not word aligned fail.
	if((address % 4) != 0)
	{
		printf("un-aligned reference on read word\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		uint32_t word = 0;
		for(int i = 0; i < 4; i++)
		{
			word |= (programMemory[startAddress + address + i] << i * 8);
		}
		return word;
	}
}

// Write a given word to memory. User must provide aligned reference or fails.
void write_word(uint32_t address, uint32_t word)
{
	// If not word aligned fail.
	if((address % 4) != 0)
	{
		printf("un-aligned reference on write word\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		for(int i = 0; i < 4; i++)
		{
			programMemory[startAddress + address + i] = (word >> i * 8);
		}
	}
}

// Returns byte in the LSBs of a 32bit
// sign_extend = 0 for no sign extension.
uint32_t read_byte(uint32_t address, int sign_extend)
{
	uint32_t reg = programMemory[startAddress + address];
	if(sign_extend && reg & 0x80)
	{
		reg |= 0xFFFFFF00;
	}
	return reg;
}


// stores LSB or value at the given address
void store_byte(uint32_t address, uint32_t value)
{
	programMemory[startAddress + address] &= 0xFFFFFF00;
	programMemory[startAddress + address] |= value;
}


// Returns LSBs of a 32bit. Fails with un-aligned address
// sign_extend = 0 for no sign extension.
uint32_t read_upper_half(uint32_t address, int sign_extend)
{
	if((address % 4) != 0)
	{
		printf("un-aligned reference on load upper word\n");
		exit(EXIT_FAILURE);
	}
	uint32_t reg = programMemory[startAddress + address + 3];
	reg = reg << 8;
	reg= reg | programMemory[startAddress + address + 2];
	if(sign_extend && reg & 0x8000)
	{
		reg |= 0xFFFF0000;
	}
	return reg;
}

// Store lower 16 bits of value at address
void store_half_word(uint32_t address, uint32_t value)
{
	if((address % 4) != 0)
	{
		printf("un-aligned reference on load upper word\n");
		exit(EXIT_FAILURE);
	}
	programMemory[startAddress + address] &= 0xFFFF0000;
	programMemory[startAddress + address] |= value;
}


// Returns LSBs of a 32bit. Fails with un-aligned address
// sign_extend = 0 for no sign extension.
uint32_t read_lower_half(uint32_t address, int sign_extend)
{
	if((address % 4) != 0)
	{
		printf("un-aligned reference on load upper word\n");
		exit(EXIT_FAILURE);
	}
	uint32_t reg = programMemory[startAddress + address + 1];
	reg = reg << 8;
	reg = reg | programMemory[startAddress + address];
	if(sign_extend && reg & 0x8000)
	{
		reg |= 0xFFFF0000;
	}
	return reg;
}

void print_reg(uint32_t reg)
{
	uint32_t localReg = registers[reg];
	printf("REG x%02d = 0x%08X = ", reg, localReg);
	for(int i = 0; i < 32; i++)
	{
		int temp = (localReg & (0x80000000 >> i))? 1: 0;
		printf("%d", temp);
	}
	printf("\n");
}
