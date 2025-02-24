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

void addi(decoded_instr_t instruction, uint32_t registers[]);
void slti(decoded_instr_t instruction, uint32_t registers[]);
void sltiu(decoded_instr_t instruction, uint32_t registers[]);
void xori(decoded_instr_t instruction, uint32_t registers[]);
void ori(decoded_instr_t instruction, uint32_t registers[]);
void andi(decoded_instr_t instruction, uint32_t registers[]);
void slli(decoded_instr_t instruction, uint32_t registers[]);
void srli(decoded_instr_t instruction, uint32_t registers[]);
void srai(decoded_instr_t instruction, uint32_t registers[]);
void lb(decoded_instr_t instruction, uint32_t registers[], memory_t mem);
void lh(decoded_instr_t instruction, uint32_t registers[], memory_t mem);
void lw(decoded_instr_t instruction, uint32_t registers[], memory_t mem);
void lbu(decoded_instr_t instruction, uint32_t registers[], memory_t mem);
void lhu(decoded_instr_t instruction, uint32_t registers[], memory_t mem);
void jalr(decoded_instr_t instruction, uint32_t registers[], uint32_t programCounter);
void ebreak();
void ecall();

void lui(decoded_instr_t instruction, uint32_t registers[]);
void auipc(decoded_instr_t instruction, uint32_t registers[], uint32_t programCounter);


#endif
