/*
Functions related to reading and writing from memory
*/
#ifndef		MEMORY_H_
#define		MEMORY_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../modules/types.h"
#include "../modules/defines.h"

uint32_t read_memory(uint32_t address, int sign_extend, memory_t *programMemory, uint8_t numBytes);

void write_memory(uint32_t address, memory_t *programMemory, uint8_t numBytes, uint32_t value);

#endif

