#include "../modules/decode.h"
// Decode function
decoded_instr_t decode_instruction(uint32_t instruction) {
    
    uint32_t opcode = instruction & 0x7F;  // least 7 bits r opcode
    decoded_instr_t decoded = {0};

    decoded.opcode = opcode;

    switch (opcode) {
        case 0x33:  // R type
            
            decoded.funct7 = (instruction >> 25) & 0x7F;
            decoded.rs2 = (instruction >> 20) & 0x1F;
            decoded.rs1 = (instruction >> 15) & 0x1F;
            decoded.funct3 = (instruction >> 12) & 0x7;
            decoded.rd = (instruction >> 7) & 0x1F;
            #ifdef DEBUG
                printf("Decoding R-type instruction:\t");
                printf("funct7: 0x%02x, rs2: %u, rs1: %u, funct3: 0x%01x, rd: %u\n", decoded.funct7, decoded.rs2, decoded.rs1, decoded.funct3, decoded.rd);
            #endif
            break;

        case 0x13:  // ALU/Immediate
        case 0x03:
        case 0x67:
        case 0x73:
            decoded.imm = (int32_t)(instruction >> 20);  // Sign extended 12 bit immediate
            decoded.rs1 = (instruction >> 15) & 0x1F;
            decoded.funct3 = (instruction >> 12) & 0x7;
            decoded.rd = (instruction >> 7) & 0x1F;
            #ifdef DEBUG
                printf("Decoding I-type instruction:\t");
                printf("imm: 0x%03x, rs1: %u, funct3: 0x%01x, rd: %u\n", decoded.imm, decoded.rs1, decoded.funct3, decoded.rd);
            #endif
            break;

        case 0x23:  // store
            
            decoded.imm = ((instruction >> 25) & 0x7F) << 5 | ((instruction >> 7) & 0x1F); //  imm[11:5], imm[4:0]???
            decoded.rs2 = (instruction >> 20) & 0x1F;
            decoded.rs1 = (instruction >> 15) & 0x1F;
            decoded.funct3 = (instruction >> 12) & 0x7;
            #ifdef DEBUG
                printf("Decoding S-type instruction:\t");
                printf("imm: 0x%03x, rs2: %u, rs1: %u, funct3: 0x%01x\n", decoded.imm, decoded.rs2, decoded.rs1, decoded.funct3);
            #endif
            break;

        case 0x63:  // branch
           
            decoded.imm = (((instruction >> 31) & 0x1) << 12) | (((instruction >> 7) & 0x1F) << 5) | (((instruction >> 25) & 0x3F) << 1) | (((instruction >> 8) & 0x1) << 11);
            decoded.rs2 = (instruction >> 20) & 0x1F;
            decoded.rs1 = (instruction >> 15) & 0x1F;
            decoded.funct3 = (instruction >> 12) & 0x7;
            #ifdef DEBUG
                printf("Decoding B-type instruction:\t");
                printf("imm: 0x%03x, rs2: %u, rs1: %u, funct3: 0x%01x\n", decoded.imm, decoded.rs2, decoded.rs1, decoded.funct3);
            #endif
            break;

        case 0x37:  // immediate
        case 0x17:
            decoded.imm = (instruction >> 12) & 0xFFFFF;  // extract upper 20-bit immediate
            decoded.rd = (instruction >> 7) & 0x1F;
            #ifdef DEBUG
                printf("Decoding U-type instuction:\t");
                printf("imm: 0x%05x, rd: %u\n", decoded.imm, decoded.rd);
            #endif
            break;

        case 0x6F:  //jal - j-type          
            decoded.imm = (((instruction >> 31) & 0x1) << 19) | (((instruction >> 21) & 0x3FF) << 1) | (((instruction >> 20) & 0x1) << 11) | (((instruction >> 12) & 0xFF) << 12);
            decoded.rd = (instruction >> 7) & 0x1F;
            #ifdef DEBUG
            printf("Decoding J-type instuction:\t");
            printf("imm: 0x%05x, rd: %u\n", decoded.imm, decoded.rd);
            #endif
            break;

        default:
            printf("Invalid opcode: 0x%02x\t", opcode);
            decoded.halt = 1;
            break;
    }

    return decoded;
}       


