#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "risc_sim.h"
uint32_t registers[32] = {0};
void execute_load(uint32_t instruction){
	uint32_t opcode = instruction & 0x7F;
	uint32_t rd = (instruction >> 7) & 0x1F;
	uint32_t funct3 = (instruction >> 12) & 0x07;
	uint32_t rs1 = (instruction >> 15) & 0x1F;
	int32_t imm = (int32_t) (instruction >> 20);
	uint32_t address = registers[rs1] + imm;
	if (opcode == 0x03) {
		switch (funct3) {
			case 0x0:
				registers[rd] = (int8_t) array[address];
				break;
		        case 0x1:
				if(address % 2 != 0) {
					printf("Unaligned LH access at 0x%X\n", address);
					exit(EXIT_FAILURE);
				}
				registers[rd] = (int16_t)(array[address] | (array[address + 1] << 8));
				break;
			case 0x2:
				if (address % 4 != 0) {
					printf("Unaligned LW access at 0x%X\n", address);
					exit(EXIT_FAILURE);
				}
				registers[rd] = read_word(address);
				break;
			case 0x4:
				registers[rd] = array[address];
				break;
			case 0x5:
				if(address % 2 != 0) {
					printf("Unaligned LHU access at 0x%X\n", address);
					exit(EXIT_FAILURE);
				}
				registers[rd] = array[address] | (array[address + 1] << 8);
				break;
			default:
			       	printf("Unsupported load instruction\n");
		}
	}
}
void execute_store(uint32_t instruction) {
	uint32_t opcode = instruction & 0x7F;
	uint32_t funct3 = (instruction >> 12) & 0x07;
	uint32_t rs1 = (instruction >> 15) & 0x1F;
	uint32_t rs2 = (instruction >> 20) & 0x1F;
	int32_t imm = ((instruction >> 7) & 0x1F) | ((instruction >> 25) << 5 );
	uint32_t address = registers[rs1] + imm;
	if (opcode == 0x23) {
		switch (funct3) {
			case 0x0:
				array[address] = registers[rs2] & 0xFF;
				break;
			case 0x1:
				if(address % 2 != 0) {
					printf("Unaligned SH access at 0x%X\n", address);
					exit(EXIT_FAILURE);
				}
				array[address] = registers[rs2] & 0xFF;
				array[address + 1] = (registers[rs2] >> 8) & 0xFF;
				break;
			case 0x2:
				if(address % 4 != 0) {
					printf("Unaligned SW access at 0x%X\n", address);
					exit(EXIT_FAILURE);
				}
				write_word(address, registers[rs2]);
				break;
			default:
				printf("Unsupported store instructon\n");
		}
	}
}
