/*
Functions related to instructions
*/
#include "../modules/instructions.h"

//R-type instructions
// ADD: rd = rs1 + rs2
void add(decoded_instr_t instruction, uint32_t registers[])
{
    registers[instruction.rd] = registers[instruction.rs1] + registers[instruction.rs2];
    #ifdef DEBUG
        printf("Executing add rd = %d : rs1 = %d : rs2 = %d.\n", registers[instruction.rd], registers[instruction.rs1] , registers[instruction.rs2] );
    #endif
}

// SUB: rd = rs1 - rs2
void sub(decoded_instr_t instruction, uint32_t registers[])
{
    registers[instruction.rd] = registers[instruction.rs1] - registers[instruction.rs2];
    #ifdef DEBUG
        printf("Executing SUB: rd = %d (rs1 = %d, rs2 = %d)\n",
               registers[instruction.rd], registers[instruction.rs1], registers[instruction.rs2]);
    #endif
}

// SLL: rd = rs1 << rs2
void sll(decoded_instr_t instruction, uint32_t registers[])
{
    registers[instruction.rd] = registers[instruction.rs1] << (registers[instruction.rs2] & 0x1F);
    #ifdef DEBUG
        printf("Executing SLL: rd = %d\n", registers[instruction.rd]);
    #endif
}

// SLT:  rd = (rs1 < rs2)?1:0
void slt(decoded_instr_t instruction, uint32_t registers[])
{
    registers[instruction.rd] = ((int32_t)registers[instruction.rs1] < (int32_t)registers[instruction.rs2]) ? 1 : 0; //convert rs1 to signed 32 bit int
    #ifdef DEBUG
        printf("Executing SLT: rd = %d\n", registers[instruction.rd]);
    #endif
}

// SLTU: rd = (rs1 < rs2)?1:0 zero-extends
void sltu(decoded_instr_t instruction, uint32_t registers[])
{
    registers[instruction.rd] = (registers[instruction.rs1] < registers[instruction.rs2]) ? 1 : 0;
    #ifdef DEBUG
        printf("Executing SLTU: rd = %d\n", registers[instruction.rd]);
    #endif
}

// XOR: rd = rs1 ^ rs2
void xor_r(decoded_instr_t instruction, uint32_t registers[])
{
    registers[instruction.rd] = registers[instruction.rs1] ^ registers[instruction.rs2];
    #ifdef DEBUG
        printf("Executing XOR: rd = %d\n", registers[instruction.rd]);
    #endif
}

// SRL: rd = rs1 >> rs2 
void srl(decoded_instr_t instruction, uint32_t registers[])
{
    registers[instruction.rd] = registers[instruction.rs1] >> (registers[instruction.rs2] & 0x1F);
    #ifdef DEBUG
        printf("Executing SRL: rd = %d\n", registers[instruction.rd]);
    #endif
}

//  SRA: rd = rs1 >> rs2 msb-extends
void sra(decoded_instr_t instruction, uint32_t registers[])
{
    registers[instruction.rd] = ((int32_t)registers[instruction.rs1]) >> (registers[instruction.rs2] & 0x1F); //convert rs1 to signed 32 bit int
    #ifdef DEBUG
        printf("Executing SRA: rd = %d\n", registers[instruction.rd]);
    #endif
}

// OR: rd = rs1 | rs2
void or_r(decoded_instr_t instruction, uint32_t registers[])
{
    registers[instruction.rd] = registers[instruction.rs1] | registers[instruction.rs2];
    #ifdef DEBUG
        printf("Executing OR: rd = %d\n", registers[instruction.rd]);
    #endif
}

// AND : rd = rs1 & rs2
void and_r(decoded_instr_t instruction, uint32_t registers[])
{
    registers[instruction.rd] = registers[instruction.rs1] & registers[instruction.rs2];
    #ifdef DEBUG
        printf("Executing AND: rd = %d\n", registers[instruction.rd]);
    #endif
}


//I-Type Instructions
void addi(decoded_instr_t instruction, uint32_t registers[]) //rd = rs1 + imm
{
        registers[instruction.rd] = registers[instruction.rs1] + instruction.imm;
        #ifdef DEBUG
            printf("Executed ADDI: rd=%u, rs1=%u, imm=%d\n", instruction.rd, instruction.rs1, instruction.imm);
        #endif
}

void slti(decoded_instr_t instruction, uint32_t registers[]) //rd = (rs1 < imm)?1:0
{
        registers[instruction.rd] = (registers[instruction.rs1] < instruction.imm) ? 1 : 0;
        #ifdef DEBUG
            printf("Executed SLTI: rd=%u, rs1=%u, imm=%d\n", instructoin.rd, instruction.rs1, instruction.imm);
        #endif
}

void sltiu(decoded_instr_t instruction, uint32_t registers[]) //rd = (rs1 < imm)?1:0 zero extends
{
        registers[instruction.rd] = (registers[instruction.rs1] < (uint32_t)instruction.imm ? 1 : 0;
        #ifdef DEBUG
            printf("Executed SLTIU: rd=%u, rs1=%u, imm=%u\n", instruction.rd, instruction.rs1, (uint32_t)instruction.imm);
        #endif
}

void xori(decoded_instr_i instruction, uint32_t registers[]) //rd = rs1 ^ imm
{
        registers[instruction.rd] = registers[instruction.rs1] ^ instruction.imm;
        #ifdef DEBUG
            printf("Executed XORI: rd=%u, rs1=%u, imm=%d\n", instruction.rd, instruction.rs1, instruction.imm);
        #endif
}

void ori(decoded_instr_t instruction, uint32_t registers[]) //rd = rs1 | imm
{
        registers[instruction.rd] = registers[instruction.rs1] | instruction.imm;
        #ifdef DEBUG
            printf("Executed ORI: rd=%u, rs1=%u, imm=%d\n", instruction.rd, instruction.rs1, instruction.imm);
        #endif
}

void andi(decoded_instr_t instruction, uint32_t registers[]) //rd = rs1 & imm
{
        registers[instruction.rd] = registers[instruction.rs1] & instruction.imm;
        #ifdef DEBUG
            printf("Executed ANDI: rd=%u, rs1=%u, imm=%d\n", instruction.rd, instruction.rs1, instruction.imm);
        #endif
}

void slli(decoded_instr_t instruction, uint32_t registers[])
{
        registers[instruction.rd] = registers[instruction.rs1] << (instruction.imm & 0x1F);
        #ifdef DEBUG
            printf("Executed SLLI: rd=%u, rs1=%u, imm%d\n", instruction.rd, instruction.rs1, instruction.imm);
        #endif
}

void srli(decoded_instr_t instruction, uint32_t registers[])
{
        registers[instruction.rd] = registers[instruction.rs1] >> (instruction.imm & 0x1F);
        #ifdef DEBUG
            printf("Executed SRLI: rd=%u, rs1=%u, imm=%d\n", instruction.rd, instruction.rs1, instruction.imm);
        #endif
}

void srai(decoded_instr_t instruction, uint32_t registers[])
{
        registers[instruction.rd] = (int32_t)registers[instruction.rs1] >> (instruction.imm & 0x1F);
        #ifdef DEBUG
            printf("Executed SRAI: rd=%u, rs1=%u, imm=%d\n", instruction.rd, instruction.rs1, instruction.imm);
        #endif
}

void lui(decoded_instr_t instruction, uint32_t registers[]) //rd = imm << 12
{
        registers[instruction.rd] = instruction.imm << 12;
        #ifdef DEBUG
            printf("Executed LUI: rd=%u, imm=0x%08x\n", instruction.rd, instruction.imm);
        #endif
}

void auipc(decoded_instr_t instruction, uint32_t registers[], uint32_t programCounter) //rd = PC + (imm << 12)
{
        registers[instruction.rd] = programCounter + (instruction.imm << 12);
        #ifdef DEBUG
            printf("Executed AUIPC: rd=%u, imm=0x%08x, programCounter=0x%08\n", instruction.rd, instruction.imm, programCounter);
        #endif
}
