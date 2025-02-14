/*
Functions related to reading and writing from memory
*/
#ifndef		EXECUTE_H_
#define		EXECUTE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../modules/instructions.h"

uint32_t execute_r_type(decoded_instr_t instruction, uint32_t registers[]);

#endif
