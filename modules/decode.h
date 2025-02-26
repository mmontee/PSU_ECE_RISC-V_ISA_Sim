#ifndef		DECODE_H_
#define		DECODE_H_

#include <stdio.h>
#include <stdint.h>
#include "../modules/types.h"
#include "../modules/defines.h"


decoded_instr_t decode_instruction(uint32_t instruction);

#endif
