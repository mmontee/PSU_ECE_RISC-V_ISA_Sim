#ifndef         RISC_SIM_H_
#define         RISC_SIM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../modules/memory.h"



typedef struct{
	FILE *inputFilePath;
	uint32_t instructionCount;
	uint32_t startAddress;
	uint32_t stackSize;
	uint32_t inputFileType;
} input_params_t;

input_params_t parse_args(int argc, char *argv[]);

memory_t parse_input(input_params_t *params);


#endif


