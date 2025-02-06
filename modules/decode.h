#ifndef		DECODE_H_
#define		DECODE_H_

#include <stdio.h>
#include <stdint.h>

//struct for bit fields
typedef struct {
    uint32_t opcode;
    uint32_t rd;
    uint32_t rs1;
    uint32_t rs2;
    int32_t imm;
    uint32_t funct3;
    uint32_t funct7;
} decoded_instr_t;

#endif