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
    
    write_memory(0x0, &hardware.programMemory, 4, 0x0);
    write_memory(0x4, &hardware.programMemory, 4, 0x0);
    
    hardware.registers[5] = 0x0;
    hardware.registers[6] = 0xAAAAAAAA;

    printf("\n SB test--------------------------------------------------------------------\n\n");
    
    // SB with no imm offset
    printf("SB - test - imm = 0: 0(r5)[7:0] <- r6[7:0]. Init r5=0, 0(r5)=0, r6=0xAAAAAAAA\n");
    uint32_t memoryAddress = 0;
    currentInstruction = 0x00628023; 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_s_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("memory[0x%08X] = 0x%08X\n", memoryAddress, read_memory(memoryAddress, 0, &hardware.programMemory, 4));
    printf("\n");
    if(read_memory(memoryAddress, 0, &hardware.programMemory, 4) & 0x000000AA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n");
    
    hardware.registers[6] = 0xBBBBBBBB;
    // SB with no imm offset
    printf("SB - test - imm > 0: 4(r5)[7:0] <- r6[7:0]. Init r5=0, 4(r5)=0, r6=0xBBBBBBBB\n");
    memoryAddress = 4;
    currentInstruction = 0x00628223; 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_s_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("memory[0x%08X] = 0x%08X\n", memoryAddress, read_memory(memoryAddress, 0, &hardware.programMemory, 4));
    printf("\n");
    if(read_memory(memoryAddress, 0, &hardware.programMemory, 4)  & 0x000000AA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n");

    write_memory(0x0, &hardware.programMemory, 4, 0x0);
    hardware.registers[6] = 0xCCCCCCCC;

     // SB with no imm offset
    hardware.registers[5] = 0x4;
    printf("SB - test - imm < 0: -4(r5)[7:0] <- r6[7:0]. Init r5=4, -4(r5)=0, r6=0xCCCCCCCC\n");
    memoryAddress = 0;
    currentInstruction = 0xFE628E23; 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_s_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("memory[0x%08X] = 0x%08X\n", memoryAddress, read_memory(memoryAddress, 0, &hardware.programMemory, 4));
    printf("\n");
    if(read_memory(memoryAddress, 0, &hardware.programMemory, 4)  & 0x000000AA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n");




 printf("\n SH test--------------------------------------------------------------------\n\n");
        write_memory(0x0, &hardware.programMemory, 4, 0x0);
    write_memory(0x4, &hardware.programMemory, 4, 0x0);
    
    hardware.registers[5] = 0x0;
    hardware.registers[6] = 0xAAAAAAAA;
    // SH with no imm offset
    printf("SH - test - imm = 0: 0(r5)[7:0] <- r6[7:0]. Init r5=0, 0(r5)=0, r6=0xAAAAAAAA\n");
    memoryAddress = 0;
    currentInstruction = 0x00629023; 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_s_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("memory[0x%08X] = 0x%08X\n", memoryAddress, read_memory(memoryAddress, 0, &hardware.programMemory, 4));
    printf("\n");
    if(read_memory(memoryAddress, 0, &hardware.programMemory, 4) & 0x000000AA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n");
    
    hardware.registers[6] = 0xBBBBBBBB;
    // SH with no imm offset
    printf("SH - test - imm > 0: 4(r5)[7:0] <- r6[7:0]. Init r5=0, 4(r5)=0, r6=0xBBBBBBBB\n");
    memoryAddress = 4;
    currentInstruction = 0x00629223; 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_s_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("memory[0x%08X] = 0x%08X\n", memoryAddress, read_memory(memoryAddress, 0, &hardware.programMemory, 4));
    printf("\n");
    if(read_memory(memoryAddress, 0, &hardware.programMemory, 4)  & 0x000000AA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n");

    write_memory(0x0, &hardware.programMemory, 4, 0x0);
    hardware.registers[6] = 0xCCCCCCCC;

     // SH with no imm offset
    hardware.registers[5] = 0x4;
    printf("SH - test - imm < 0: -4(r5)[7:0] <- r6[7:0]. Init r5=4, -4(r5)=0, r6=0xCCCCCCCC\n");
    memoryAddress = 0;
    currentInstruction = 0xFE629E23; 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_s_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("memory[0x%08X] = 0x%08X\n", memoryAddress, read_memory(memoryAddress, 0, &hardware.programMemory, 4));
    printf("\n");
    if(read_memory(memoryAddress, 0, &hardware.programMemory, 4)  & 0x0000AAAA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n");

     printf("\n SW test--------------------------------------------------------------------\n\n");
        write_memory(0x0, &hardware.programMemory, 4, 0x0);
    write_memory(0x4, &hardware.programMemory, 4, 0x0);
    
    hardware.registers[5] = 0x0;
    hardware.registers[6] = 0xAAAAAAAA;
    // SW with no imm offset
    printf("SW - test - imm = 0: 0(r5)[7:0] <- r6[7:0]. Init r5=0, 0(r5)=0, r6=0xAAAAAAAA\n");
    memoryAddress = 0;
    currentInstruction = 0x0062A023; 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_s_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("memory[0x%08X] = 0x%08X\n", memoryAddress, read_memory(memoryAddress, 0, &hardware.programMemory, 4));
    printf("\n");
    if(read_memory(memoryAddress, 0, &hardware.programMemory, 4) & 0x000000AA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n");
    
    hardware.registers[6] = 0xBBBBBBBB;
    // SW with no imm offset
    printf("SW - test - imm > 0: 4(r5)[7:0] <- r6[7:0]. Init r5=0, 4(r5)=0, r6=0xBBBBBBBB\n");
    memoryAddress = 4;
    currentInstruction = 0x0062A223; 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_s_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("memory[0x%08X] = 0x%08X\n", memoryAddress, read_memory(memoryAddress, 0, &hardware.programMemory, 4));
    printf("\n");
    if(read_memory(memoryAddress, 0, &hardware.programMemory, 4)  & 0x000000AA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n");

    write_memory(0x0, &hardware.programMemory, 4, 0x0);
    hardware.registers[6] = 0xCCCCCCCC;

     // SW with no imm offset
    hardware.registers[5] = 0x4;
    printf("SW - test - imm < 0: -4(r5)[7:0] <- r6[7:0]. Init r5=4, -4(r5)=0, r6=0xCCCCCCCC\n");
    memoryAddress = 0;
    currentInstruction = 0xFE62AE23; 
    decodedInstruction = decode_instruction(currentInstruction);
    execute_s_type(&decodedInstruction, &hardware);
    print_bits(6, hardware.registers);
    printf("memory[0x%08X] = 0x%08X\n", memoryAddress, read_memory(memoryAddress, 0, &hardware.programMemory, 4));
    printf("\n");
    if(read_memory(memoryAddress, 0, &hardware.programMemory, 4)  & 0x0000AAAA)
    {
        printf("Pass\n");
    }
    else
    {
        printf("Fail\n");
    }
    printf("\n");


    return 0;
}
