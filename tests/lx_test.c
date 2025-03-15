#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "../modules/types.h"
#include "../modules/risc_sim.h"
#include "../modules/decode.h"
#include "../modules/execute.h"
#include "../modules/instructions.h"

#define DEBUG

hardware_t hardware;
int main()
{
    hardware.programCounter = 0;
    hardware.registers[2] = 256;
    hardware.registers[1] = 0;
    hardware.registers[0] = 0;
    uint32_t currentInstruction;
    decoded_instr_t decodedInstruction;
    
    write_memory(0x0, &hardware.programMemory, 4, 0xAAAAAAAA);
    write_memory(0x4, &hardware.programMemory, 4, 0x55555555);
    
    printf("\n LB test--------------------------------------------------------------------\n\n");
    
    // LB with no imm offset
    printf("LB - test: r5 <- 0(r5). Init r5=0 and 0(r5)=0xAAAAAAAA\n");
    currentInstruction = 0x00028283;// r5 <- [0+(r5)]  
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(5, hardware.registers);
    printf("\n\n");
    if(hardware.registers[5] & 0xFFFFFFAA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    
    // LB with imm offset > 0
    hardware.registers[5] = 0;
    print_bits(5, hardware.registers);
    printf("LB - test: r6 <- 4(r5). Init r5=0 and 4(r5)=0x55555555\n");
    currentInstruction = 0x00428303;// r6 <- [4+(r5)] 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("\n\n");
    if(hardware.registers[6] & 0x00000055)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    
    // LB with imm offset < 0
    hardware.registers[5] = 4;
    print_bits(5, hardware.registers);
    printf("LB - test: r7 <- 4(r5). Init r5=4 and 4(r5)=0xAAAAAAAA\n");
    currentInstruction = 0xFFC28383;// r5 <- [-4+(r5)]
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(7, hardware.registers);
    printf("\n\n");
    if(hardware.registers[7] & 0xFFFFFFAA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    printf("\n LH test--------------------------------------------------------------------\n\n");
  
    hardware.registers[5] = 0;
    hardware.registers[6] = 0;
    // LH with no imm offset
    printf("LH - test: r5 <- 0(r5). Init r5=0 and 0(r5)=0xAAAAAAAA\n");
    currentInstruction = 0x00029283;// r5 <- [0+(r5)]  
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(5, hardware.registers);
    printf("\n\n");
    if(hardware.registers[5] & 0xFFFFAAAA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    
    // LH with imm offset > 0
    hardware.registers[5] = 0;
    print_bits(5, hardware.registers);
    printf("LH - test: r6 <- 4(r5). Init r5=0 and 4(r5)=0x55555555\n");
    currentInstruction = 0x00429303;// r6 <- [4+(r5)] 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("\n\n");
    if(hardware.registers[6] & 0x00005555)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    
    // LH with imm offset < 0
    hardware.registers[5] = 4;
    print_bits(5, hardware.registers);
    printf("LH - test: r7 <- 4(r5). Init r5=4 and 4(r5)=0xAAAAAAAA\n");
    currentInstruction = 0xFFC29383;// r5 <- [-4+(r5)]
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(7, hardware.registers);
    printf("\n\n");
    if(hardware.registers[7] & 0xFFFFAAAA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    
    
    printf("\n LW test--------------------------------------------------------------------\n\n");
    
    hardware.registers[5] = 0;
    hardware.registers[6] = 0;
    // LH with no imm offset
    printf("LW - test: r5 <- 0(r5). Init r5=0 and 0(r5)=0xAAAAAAAA\n");
    currentInstruction = 0x0002A283;// r5 <- [0+(r5)]  
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(5, hardware.registers);
    printf("\n\n");
    if(hardware.registers[5] & 0xAAAAAAAA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    
    // LH with imm offset > 0
    hardware.registers[5] = 0;
    print_bits(5, hardware.registers);
    printf("LW - test: r6 <- 4(r5). Init r5=0 and 4(r5)=0x55555555\n");
    currentInstruction = 0x0042A303;// r6 <- [4+(r5)] 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("\n\n");
    if(hardware.registers[6] & 0x55555555)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    
    // LH with imm offset < 0
    hardware.registers[5] = 4;
    print_bits(5, hardware.registers);
    printf("LW - test: r7 <- 4(r5). Init r5=4 and 4(r5)=0xAAAAAAAA\n");
    currentInstruction = 0xFFC2A383;// r5 <- [-4+(r5)]
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(7, hardware.registers);
    printf("\n\n");
    if(hardware.registers[7] & 0xAAAAAAAA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");

    printf("\n LBU test--------------------------------------------------------------------\n\n");
    
    hardware.registers[5] = 0;
    hardware.registers[6] = 0;
    // LH with no imm offset
    printf("LBU - test: r5 <- 0(r5). Init r5=0 and 0(r5)=0xAAAAAAAA\n");
    currentInstruction = 0x0002C283;// r5 <- [0+(r5)]  
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(5, hardware.registers);
    printf("\n\n");
    if(hardware.registers[5] & 0x000000AA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    
    // LH with imm offset > 0
    hardware.registers[5] = 0;
    print_bits(5, hardware.registers);
    printf("LBU - test: r6 <- 4(r5). Init r5=0 and 4(r5)=0x55555555\n");
    currentInstruction = 0x0042C303;// r6 <- [4+(r5)] 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("\n\n");
    if(hardware.registers[6] & 0x00000055)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    
    // LH with imm offset < 0
    hardware.registers[5] = 4;
    print_bits(5, hardware.registers);
    printf("LBU - test: r7 <- 4(r5). Init r5=4 and 4(r5)=0xAAAAAAAA\n");
    currentInstruction = 0xFFC2C383;// r5 <- [-4+(r5)]
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(7, hardware.registers);
    printf("\n\n");
    if(hardware.registers[7] & 0x000000AA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");

    printf("\n LHU test--------------------------------------------------------------------\n\n");
    
    hardware.registers[5] = 0;
    hardware.registers[6] = 0;
    // LH with no imm offset
    printf("LHU - test: r5 <- 0(r5). Init r5=0 and 0(r5)=0xAAAAAAAA\n");
    currentInstruction = 0x0002D283;// r5 <- [0+(r5)]  
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(5, hardware.registers);
    printf("\n\n");
    if(hardware.registers[5] & 0x0000AAAA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    
    // LH with imm offset > 0
    hardware.registers[5] = 0;
    print_bits(5, hardware.registers);
    printf("LHU - test: r6 <- 4(r5). Init r5=0 and 4(r5)=0x55555555\n");
    currentInstruction = 0x0042D303;// r6 <- [4+(r5)] 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("\n\n");
    if(hardware.registers[6] & 0x000005555)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    
    // LH with imm offset < 0
    hardware.registers[5] = 4;
    print_bits(5, hardware.registers);
    printf("LHU - test: r7 <- 4(r5). Init r5=4 and 4(r5)=0xAAAAAAAA\n");
    currentInstruction = 0xFFC2D383;// r5 <- [-4+(r5)]
    decodedInstruction = decode_instruction(currentInstruction);
    execute_i_type(&decodedInstruction, &hardware);
    print_bits(7, hardware.registers);
    printf("\n\n");
    if(hardware.registers[7] & 0x0000AAAA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n\n");
    return 0;
}
