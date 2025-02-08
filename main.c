#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "./modules/risc_sim.h"
#include "./modules/decode.h"
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
		printf("Current Instruction = 0x%08X\n", currentInstruction);
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
