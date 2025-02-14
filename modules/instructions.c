/*
Functions related to instructions
*/
#include "../modules/instructions.h"

void add(decoded_instr_t instruction, uint32_t registers[])//rd = rs1 + rs2
{
  registers[instruction.rd] = registers[instruction.rs1] + registers[instruction.rs2];
}
