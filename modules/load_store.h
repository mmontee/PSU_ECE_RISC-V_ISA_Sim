#ifndef		LOAD_STORE_H_
#define		LOAD_STORE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../modules/memory.h"

void execute_load(uint32_t instruction, memory_t memory, uint32_t registers[]);

void execute_store(uint32_t instruction, memory_t memory, uint32_t registers[]);

#endif
