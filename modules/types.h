#ifndef		TYPES_H_
#define		TYPES_H_
#include <stdlib.h>
#include <stdint.h>
#include "../modules/defines.h"

typedef struct
{
	uint8_t array[MAX_SIZE];
	uint32_t startAddress;
    uint32_t instructionCount;
} memory_t;

typedef struct
{
    memory_t programMemory;
    uint32_t registers[32];
    uint32_t programCounter;
} hardware_t;

//struct for bit fields
typedef struct 
{
    uint32_t opcode;
    uint32_t rd;
    uint32_t rs1;
    uint32_t rs2;
    uint32_t imm;
    uint32_t funct3;
    uint32_t funct7;
    uint32_t halt;
} decoded_instr_t;

typedef struct
{
	FILE *inputFilePath;
	uint32_t startAddress;
	uint32_t stackPointer;
	uint32_t inputFileType;
} input_params_t;

#endif
