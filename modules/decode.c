#include <stdio.h>
#include <stdint.h>
#include "../modules/decode.h"

// Decode function
void decode_instruction(uint32_t instruction) {
    
    uint32_t opcode = instruction & 0x7F;  // last 7 bits r opcode
    decoded_instr_t decoded = {0};

    decoded.opcode = opcode;

    switch (opcode) {
        case 0x33:  // read
            
            decoded.funct7 = (instruction >> 25) & 0x7F;
            decoded.rs2 = (instruction >> 20) & 0x1F;
            decoded.rs1 = (instruction >> 15) & 0x1F;
            decoded.funct3 = (instruction >> 12) & 0x7;
            decoded.rd = (instruction >> 7) & 0x1F;
            printf("Rtype instruction:\n");
            printf("funct7: 0x%02x, rs2: %u, rs1: %u, funct3: 0x%01x, rd: %u\n", decoded.funct7, decoded.rs2, decoded.rs1, decoded.funct3, decoded.rd);
            break;

        case 0x13:  // ALU/Immediate
           
            decoded.imm = (int32_t)(instruction >> 20);  // Sign extended 12 bit immediate
            decoded.rs1 = (instruction >> 15) & 0x1F;
            decoded.funct3 = (instruction >> 12) & 0x7;
            decoded.rd = (instruction >> 7) & 0x1F;
            printf("I type instruction:\n");
            printf("imm: 0x%03x, rs1: %u, funct3: 0x%01x, rd: %u\n", decoded.imm, decoded.rs1, decoded.funct3, decoded.rd);
            break;

        case 0x23:  // store
            
            decoded.imm = ((instruction >> 25) & 0x7F) << 5 | ((instruction >> 7) & 0x1F); //  imm[11:5], imm[4:0]???
            decoded.rs2 = (instruction >> 20) & 0x1F;
            decoded.rs1 = (instruction >> 15) & 0x1F;
            decoded.funct3 = (instruction >> 12) & 0x7;
            printf("S type instruction:\n");
            printf("imm: 0x%03x, rs2: %u, rs1: %u, funct3: 0x%01x\n", decoded.imm, decoded.rs2, decoded.rs1, decoded.funct3);
            break;

        case 0x63:  // branch
           
            decoded.imm = (((instruction >> 31) & 0x1) << 12) | (((instruction >> 7) & 0x1F) << 5) | (((instruction >> 25) & 0x3F) << 1) | (((instruction >> 8) & 0x1) << 11);
            decoded.rs2 = (instruction >> 20) & 0x1F;
            decoded.rs1 = (instruction >> 15) & 0x1F;
            decoded.funct3 = (instruction >> 12) & 0x7;
            printf("B type instruction:\n");
            printf("imm: 0x%03x, rs2: %u, rs1: %u, funct3: 0x%01x\n", decoded.imm, decoded.rs2, decoded.rs1, decoded.funct3);
            break;

        case 0x37:  // immediate
            
            decoded.imm = (instruction >> 12) & 0xFFFFF;  // extract upper 20-bit immediate
            decoded.rd = (instruction >> 7) & 0x1F;
            printf("U type instuction:\n");
            printf("imm: 0x%05x, rd: %u\n", decoded.imm, decoded.rd);
            break;

        case 0x6F:  //jal - j-type          
            decoded.imm = (((instruction >> 31) & 0x1) << 19) | (((instruction >> 21) & 0x3FF) << 1) | (((instruction >> 20) & 0x1) << 11) | (((instruction >> 12) & 0xFF) << 12);
            decoded.rd = (instruction >> 7) & 0x1F;
            printf("J type instuction:\n");
            printf("imm: 0x%05x, rd: %u\n", decoded.imm, decoded.rd);
            break;

        case 0x67: //jalr - jump with i-type encoding
            decoded.imm = (int32_t)(instruction >> 20);  // Sign extended 12 bit immediate
            decoded.rs1 = (instruction >> 15) & 0x1F;
            decoded.funct3 = (instruction >> 12) & 0x7;
            decoded.rd = (instruction >> 7) & 0x1F;
            printf("I type instruction:\n");
            printf("imm: 0x%03x, rs1: %u, funct3: 0x%01x, rd: %u\n", decoded.imm, decoded.rs1, decoded.funct3, decoded.rd);
            break;


        default:
            printf("Invalid opcode: 0x%02x\n", opcode);
            break;
    }
}       


