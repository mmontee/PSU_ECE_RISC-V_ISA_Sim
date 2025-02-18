#ifndef		INSTRUCTIONS_H_
#define		INSTRUCTIONS_H_

#include <stdio.h>
#include <stdint.h>
#include "../modules/memory.h"
#include "../modules/decode.h"
void add(decoded_instr_t instruction, uint32_t registers[]);
void sub(decoded_instr_t instruction, uint32_t registers[]);
void sll(decoded_instr_t instruction, uint32_t registers[]);
void slt(decoded_instr_t instruction, uint32_t registers[]);
void sltu(decoded_instr_t instruction, uint32_t registers[]);
void xor_r(decoded_instr_t instruction, uint32_t registers[]);
void srl(decoded_instr_t instruction, uint32_t registers[]);
void sra(decoded_instr_t instruction, uint32_t registers[]);
void or_r(decoded_instr_t instruction, uint32_t registers[]);
void and_r(decoded_instr_t instruction, uint32_t registers[]);
#endif
