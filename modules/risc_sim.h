#ifndef         RISC_SIM_H_
#define         RISC_SIM_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../modules/types.h"
#include "../modules/memory.h"

input_params_t parse_args(int argc, char *argv[]);

memory_t parse_input(input_params_t *params);

#endif


