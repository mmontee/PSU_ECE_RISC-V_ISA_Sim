#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "./modules/types.h"
#include "./modules/risc_sim.h"
#include "./modules/decode.h"
#include "./modules/execute.h"
#include "./modules/instructions.h"

//#define DEBUG

hardware_t hardware;
uint8_t halt = 0;
int main(int argc, char *argv[])
{
    // Read User arguments
    input_params_t userParams = parse_args(argc, argv);
    hardware.programCounter = userParams.startAddress;
    // Load input file into memory.
    hardware.programMemory = parse_input(&userParams);
    printf("instructionCount = %d\n", userParams.instructionCount);
    // While the machine is not halted fetch inctructions and incrment the PC
    while(halt == 0)
    {
        #ifdef DEBUG
            printf("\nPC Address = 0x%08X\n", hardware.programCounter);
        #endif
            
        // fetch the current instruction
        uint32_t currentInstruction = read_word(hardware.programCounter, &hardware.programMemory);
        #ifdef DEBUG
            printf("Instruction Code = 0x%08X\n", currentInstruction);
        #endif
        // Decode current instruction
        decoded_instr_t decodedInstruction = decode_instruction(currentInstruction);
        

        // Execute current instruction
        switch(decodedInstruction.opcode)
        {
            case 0x33:// R-type
                execute_r_type(decodedInstruction, &hardware);
                break;
            case 0x13:// I-type
            case 0x03:// I-type
            case 0x67:// I-type
            case 0x73:// I-type
		          execute_i_type(decodedInstruction, &hardware);
		          break;
            case 0x23:// S-type
		          execute_s_type(decodedInstruction, &hardware);
		          break;
            case 0x63:// B-type
		          execute_b_type(decodedInstruction, &hardware);
		          break;
            case 0x37:// U-type
            case 0x17:
		          execute_u_type(decodedInstruction, &hardware);
		          break;
            case 0x6F:// j-type
		          execute_j_type(decodedInstruction, &hardware);
		          break;
            default:
		          printf("Unknown op-code\n");
		          exit(EXIT_FAILURE);
		          break;
        }
              
        for(int i = 0; i < 32; i++)
        {
            print_bits(i, hardware.registers);
            
        }
        for(int i = 0; i < 32; i++)
        {
            printf("memory address 0x%08X = 0x%08X\n", i * 4,read_word(i * 4, &hardware.programMemory));
            
            
        }
            
                            
        // Will need to jump over this is a new PC in created by instruction
        hardware.programCounter += 4;
        
        // This will be removed once we can decode the "jmp ra=0" halt instruction
        if(currentInstruction == 0x00000000)
        {
            halt = 1;
            printf("Halt\n");
        }
    }
    return 0;
 }

