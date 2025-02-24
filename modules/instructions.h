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

void sb(instruction, hrdwr.registers,  hrdwr.programMemory);
void sh(instruction, hrdwr.registers,  hrdwr.programMemory);
void sw(instruction, hrdwr.registers,  hrdwr.programMemory);

void beq(instruction,  hrdwr.registers,  hrdwr.programMemory,  hrdwr.programCounter);
void bne(instruction,  hrdwr.registers,  hrdwr.programMemory,  hrdwr.programCounter);
void blt(instruction,  hrdwr.registers,  hrdwr.programMemory,  hrdwr.programCounter);
void bge(instruction,  hrdwr.registers,  hrdwr.programMemory,  hrdwr.programCounter);
void bltu( instruction,  hrdwr.registers,  hrdwr.programMemory,  hrdwr.programCounter);
void bgeu( instruction,  hrdwr.registers,  hrdwr.programMemory,  hrdwr.programCounter);

void lb(decoded_instr_t instruction, uint32_t registers[], memory_t memory);
void lh(decoded_instr_t instruction, uint32_t registers[], memory_t memory);
void lw(decoded_instr_t instruction, uint32_t registers[], memory_t memory);
void lbu(decoded_instr_t instruction, uint32_t registers[], memory_t memory);
void lhu(decoded_instr_t instruction, uint32_t registers[], memory_t memory);
void jalr(decoded_instr_t instruction, uint32_t registers[], uint32_t programCounter);
void jal(decoded_instr_t instruction, uint32_t registers[], uint32_t programCounter)
void ebreak();
void ecall();

void lui(decoded_instr_t instruction, uint32_t registers[]);
void auipc(decoded_instr_t instruction, uint32_t registers[], uint32_t programCounter);

#endif
