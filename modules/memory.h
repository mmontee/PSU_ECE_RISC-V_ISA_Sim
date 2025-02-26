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

uint32_t read_word(uint32_t address, memory_t input);

void write_word(uint32_t address, uint32_t word, memory_t input);

uint32_t read_byte(uint32_t address, int sign_extend, memory_t input);

void write_byte(uint32_t address, uint32_t value, memory_t input);

uint32_t read_upper_half(uint32_t address, int sign_extend, memory_t input);

void write_half_word(uint32_t address, uint32_t value, memory_t input);

uint32_t read_lower_half(uint32_t address, int sign_extend, memory_t input);

uint32_t read_half(uint32_t address, int sign_extend, memory_t programMemory);

#endif

