/*
Functions related to reading and writing from memory
*/
#include "../modules/memory.h"

// Read a word from memory. User must provide aligned reference or fails.
uint32_t read_word(uint32_t address, memory_t *programMemory)
{
	// If not word aligned fail.
	if((address % 4) != 0)
	{
		printf("un-aligned reference on read_word\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		uint32_t word = 0;
		for(int i = 0; i < 4; i++)
		{
			word |= (programMemory->array[programMemory->startAddress + address + i] << i * 8);
		}
		return word;
	}
}

// Write a given word to memory. User must provide aligned reference or fails.
void write_word(uint32_t address, uint32_t word, memory_t *programMemory)
{
	// If not word aligned fail.
	if((address % 4) != 0)
	{
		printf("un-aligned reference on write_word\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		for(int i = 0; i < 4; i++)
		{
			programMemory->array[programMemory->startAddress + address + i] = (word >> i * 8);
		}
	}
}

// Returns byte in the LSBs of a 32bit
// sign_extend = 0 for no sign extension.
uint32_t read_byte(uint32_t address, int sign_extend, memory_t *programMemory)
{
	uint32_t reg = programMemory->array[programMemory->startAddress + address];
	if(sign_extend && reg & 0x80)
	{
		reg |= 0xFFFFFF00;
	}
	return reg;
}


// stores LSB or value at the given address
void write_byte(uint32_t address, uint32_t value, memory_t *programMemory) {
  programMemory->array[programMemory->startAddress + address] = (uint8_t)value;
}


// Returns LSBs of a 32bit. Fails with un-aligned address
// sign_extend = 0 for no sign extension.
uint32_t read_upper_half(uint32_t address, int sign_extend, memory_t *programMemory)
{
	if((address % 4) != 0)
	{
		printf("un-aligned reference on read_upper_half\n");
		exit(EXIT_FAILURE);
	}
	uint32_t reg = programMemory->array[programMemory->startAddress + address + 3];
	reg = reg << 8;
	reg= reg | programMemory->array[programMemory->startAddress + address + 2];
	if(sign_extend && reg & 0x8000)
	{
		reg |= 0xFFFF0000;
	}
	return reg;
}

// Store lower 16 bits of value at address
void write_half_word(uint32_t address, uint32_t value, memory_t *programMemory)
{
	if((address % 2) != 0)
	{
		printf("un-aligned reference on write_half_word\n");
		exit(EXIT_FAILURE);
	}

	programMemory->array[programMemory->startAddress + address] |= value;
    value = value >> 8;
    programMemory->array[programMemory->startAddress + address + 1] |= value;
}


// Returns LSBs of a 32bit. Fails with un-aligned address
// sign_extend = 0 for no sign extension.
uint32_t read_lower_half(uint32_t address, int sign_extend, memory_t *programMemory)
{
	if((address % 4) != 0)
	{
		printf("un-aligned reference on read_lower_half\n");
		exit(EXIT_FAILURE);
	}
	uint32_t reg = programMemory->array[programMemory->startAddress + address + 1];
	reg = reg << 8;
	reg = reg | programMemory->array[programMemory->startAddress + address];
	if(sign_extend && reg & 0x8000)
	{
		reg |= 0xFFFF0000;
	}
	return reg;
}



// Returns a 32bit where the lower are the word. Fails with un-aligned address
// sign_extend = 0 for no sign extension.
// little-endian
uint32_t read_half(uint32_t address, int sign_extend, memory_t *programMemory)
{
	if((address % 2) != 0)
	{
		printf("un-aligned reference on read_half\n");
		exit(EXIT_FAILURE);
	}
	uint32_t reg = programMemory->array[programMemory->startAddress + address + 1];
	reg = reg << 8;
	reg = reg | programMemory->array[programMemory->startAddress + address];
	if(sign_extend && reg & 0x8000)
	{
		reg |= 0xFFFF0000;
	}
	return reg;
}

