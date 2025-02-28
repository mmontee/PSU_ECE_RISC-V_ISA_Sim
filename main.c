#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "./modules/types.h"
#include "./modules/risc_sim.h"
#include "./modules/decode.h"
#include "./modules/execute.h"
#include "./modules/instructions.h"

//uint8_t halt = 0;
hardware_t hardware;
int main(int argc, char *argv[])
{
    // Read User arguments
    input_params_t userParams = parse_args(argc, argv);
    hardware.programCounter = userParams.startAddress;
    // Load input file into memory.
    hardware.programMemory = parse_input(&userParams);
    hardware.programMemory.startAddress = userParams.startAddress;
    // init registers
    hardware.registers[2] = userParams.stackPointer;
    hardware.registers[1] = 0;
    hardware.registers[0] = 0;
    

    
    decoded_instr_t decodedInstruction;
    decodedInstruction.halt = 0;
    // While the machine is not halted fetch inctructions and incrment the PC
    while(decodedInstruction.halt == 0)
    {
        #ifdef VERBOSE
            printf("\nPC Address = 0x%08X\n", hardware.programCounter);
        #endif
            
        // fetch the current instruction
        uint32_t currentInstruction = read_memory(hardware.programCounter, 0, &hardware.programMemory, 4);
        #ifdef VERBOSE
            printf("Instruction Code = 0x%08X\n", currentInstruction);
        #endif
        
        
        // Decode current instruction
        decodedInstruction = decode_instruction(currentInstruction);


        // Execute current instruction
        switch(decodedInstruction.opcode)
        {
            case 0x33:// R-type
                execute_r_type(&decodedInstruction, &hardware);
                break;
            case 0x13:// I-type
            case 0x03:// I-type
            case 0x67:// I-type
            case 0x73:// I-type
		          execute_i_type(&decodedInstruction, &hardware);
		          break;
            case 0x23:// S-type
		          execute_s_type(&decodedInstruction, &hardware);
		          break;
            case 0x63:// B-type
		          execute_b_type(&decodedInstruction, &hardware);
		          break;
            case 0x37:// U-type
            case 0x17:
		          execute_u_type(&decodedInstruction, &hardware);
		          break;
            case 0x6F:// j-type
		          execute_j_type(&decodedInstruction, &hardware);
		          break;
            default:
		          printf("Unknown op-code\n");
		          decodedInstruction.halt = 1;
		          break;
        }
          
          
        #ifdef VERBOSE          
            for(int i = 0; i < 32; i++)
            {
                print_bits(i, hardware.registers);
                
            }
        #endif  
        #ifdef DEBUG          
            for(uint32_t i = 0; i < hardware.programMemory.instructionCount; i++)
            {
                printf("memory address 0x%08X = 0x%08X\n", i * 4, read_memory(i * 4, 0, &hardware.programMemory, 4));
            }
        #endif
            
                            
        // Will need to jump over this is a new PC in created by instruction(currently handled by - 4 on execution)
        hardware.programCounter += 4;
        
        // This will be removed once we can decode the "jmp ra=0" halt instruction
        if(currentInstruction == 0x00000000)
        {
            decodedInstruction.halt = 1;
            printf("Halt\n");
        }
        
        #ifdef STEP
            printf("\nPress Return to step to PC = 0x%08x\n", hardware.programCounter);
            getchar(); // This is the key part!  Blocks until a key is pressed.
        #endif
        
    }
    printf("\n-----PROGRAM HALT------\n");
    // Print the final PC and registeres on the way out.
    printf("\nFinal PC Address = 0x%08X\n", hardware.programCounter - 4);
    for(int i = 0; i < 32; i++)
    {
        print_bits(i, hardware.registers);
    }
    return 0;
 }

