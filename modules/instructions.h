#ifndef		INSTRUCTIONS_H_
#define		INSTRUCTIONS_H_

#include <stdio.h>
#include <stdint.h>
#include "../modules/memory.h"
#include "../modules/decode.h"
void add(decoded_instr_t instruction, uint32_t registers[]);
#endif
