#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "./modules/risc_sim.h"
#include "./modules/decode.h"
#include "./modules/execute.h"
#include "./modules/instructions.h"
//#include "./modules/load_store.h"


uint32_t registers[32];
uint32_t programCounter = 0;
uint8_t halt = 0;
int main(int argc, char *argv[])
{
	// Read User arguments
	input_params_t userParams = parse_args(argc, argv);
	programCounter = userParams.startAddress;
	// Load input file into memory.
	memory_t programMemory = parse_input(&userParams);
	printf("instructionCount = %d\n", userParams.instructionCount);
	// While the machine is not halted fetch inctructions and incrment the PC
	while(halt == 0)
	{
		// fetch the current instruction
		uint32_t currentInstruction = read_word(programCounter, programMemory);
		
		decoded_instr_t decodedInstruction;// = decode_instruction(currentInstruction);
		
		switch(decodedInstruction.opcode)
		{
		  case 0x33:// R-type
                    execute_r_type(decodedInstruction, registers);
		    break;
	          case 0x13:// I-type
		  case 0x03:// I-type
		  case 0x17:// I-type
		  case 0x73:// I-type
		    // execute_i_type(decodedInstruction);
		    break;
		  case 0x23:// S-type
		    // execute_s_type(decodedInstruction);
		    break;
		  case 0x63:// B-type
		    // execute_b_type(decodedInstruction);
		    break;
		  case 0x37:// U-type
		    // execute_u_type(decodedInstruction);
		    break;
		  case 0x6F:// j-type
		    // execute_j_type(decodedInstruction);
		    break;
		  default:
		    printf("Unknown op-code\n");
		    exit(EXIT_FAILURE);
		    break;
		}
		
		printf("Address = 0x%08X Instruction = 0x%08X\n", programCounter, currentInstruction);
		// Decode current instruction

		// Exicute current instruction

		// Will need to jump over this is a new PC in created by instruction
		programCounter += 4;

		// This will be removed once we can decode the "jmp ra=0" halt instruction
		if
		((programCounter - userParams.startAddress >= userParams.instructionCount * 4)
		||
		(currentInstruction == 0x00000000))
		{
			halt = 1;
			printf("Halt\n");
		}
	}
	return 0;
}

