/*
Functions related to reading and writing from memory
*/
#ifndef		EXECUTE_H_
#define		EXECUTE_H_
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../modules/types.h"
#include "../modules/instructions.h"
#include "../modules/defines.h"

void execute_r_type(decoded_instr_t instruction, hardware_t *hrdwr);

void execute_i_type(decoded_instr_t instruction, hardware_t *hrdwr);

void execute_s_type(decoded_instr_t instruction, hardware_t *hrdwr);

void execute_b_type(decoded_instr_t instruction, hardware_t *hrdwr);

void execute_u_type(decoded_instr_t instruction, hardware_t *hrdwr);

void execute_j_type(decoded_instr_t instruction, hardware_t *hrdwr);

#endif
