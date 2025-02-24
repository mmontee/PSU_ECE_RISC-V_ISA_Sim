/*
Functions related to instructions
*/
#include "../modules/instructions.h"

//R-type instructions -----------------------------------------------------------------------------------------------------------------------------------------------
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


//I-Type Instructions -----------------------------------------------------------------------------------------------------------------------------------------------
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
        registers[instruction.rd] = (registers[instruction.rs1] < (uint32_t)instruction.imm) ? 1 : 0;
        #ifdef DEBUG
            printf("Executed SLTIU: rd=%u, rs1=%u, imm=%u\n", instruction.rd, instruction.rs1, (uint32_t)instruction.imm);
        #endif
}

void xori(decoded_instr_t instruction, uint32_t registers[]) //rd = rs1 ^ imm
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

void lb(decoded_instr_t instruction, uint32_t registers[], uint8_t memory[]) 
{
    uint32_t address = registers[instruction.rs1] + instruction.imm;
    registers[instruction.rd] = (int8_t)memory[address];  // Sign-extended
    #ifdef DEBUG
        printf("Executed LB: rd=%u, rs1=%u, address=0x%08x, value=%d\n", instruction.rd, instruction.rs1, address, (int8_t)memory[address]);
    #endif
}

void lh(decoded_instr_t instruction, uint32_t registers[], uint8_t memory[]) 
{
    uint32_t address = registers[instruction.rs1] + instruction.imm;
    registers[instruction.rd] = (int16_t)(memory[address] | (memory[address + 1] << 8));  // Sign-extended
    #ifdef DEBUG
        printf("Executed LH: rd=%u, rs1=%u, address=0x%08x, value=%d\n", instruction.rd, instruction.rs1, address, (int16_t)(memory[address] | (memory[address + 1] << 8)));
    #endif
}

void lw(decoded_instr_t instruction, uint32_t registers[], uint8_t memory[]) 
{
    uint32_t address = registers[instruction.rs1] + instruction.imm;
    registers[instruction.rd] = (memory[address] | (memory[address + 1] << 8) | (memory[address + 2] << 16) | (memory[address + 3] << 24)); // Word load
    #ifdef DEBUG
        printf("Executed LW: rd=%u, rs1=%u, address=0x%08x, value=%u\n", instruction.rd, instruction.rs1, address, registers[instruction.rd]);
    #endif
}

void lbu(decoded_instr_t instruction, uint32_t registers[], uint8_t memory[]) 
{
    uint32_t address = registers[instruction.rs1] + instruction.imm;
    registers[instruction.rd] = memory[address];  // Zero-extended
    #ifdef DEBUG
        printf("Executed LBU: rd=%u, rs1=%u, address=0x%08x, value=%u\n", instruction.rd, instruction.rs1, address, memory[address]);
    #endif
}

void lhu(decoded_instr_t instruction, uint32_t registers[], uint8_t memory[]) 
{
    uint32_t address = registers[instruction.rs1] + instruction.imm;
    registers[instruction.rd] = (memory[address] | (memory[address + 1] << 8));  // Zero-extended
    #ifdef DEBUG
        printf("Executed LHU: rd=%u, rs1=%u, address=0x%08x, value=%u\n", instruction.rd, instruction.rs1, address, registers[instruction.rd]);
    #endif
}

void jalr(decoded_instr_t instruction, uint32_t registers[], uint32_t programCounter)
{
    uint32_t temp = programCounter + 4;
    programCounter = (registers[instruction.rs1] + instruction.imm) & ~1;
    registers[instruction.rd] = temp;
    #ifdef DEBUG
        printf("Executed JALR: rd=%u, rs1=%u, imm=%d, newPC=0x%08x\n", instruction.rd, instruction.rs1, instruction.imm, programCounter);
    #endif
}

void ebreak()
{
    printf("EBREAK instruction executed: Entering debug mode or breaking execution.\n");
}

void ecall()
{
    printf("ECALL instruction executed: System call invoked.\n");
}


//U-Type Instructions ------------------------------------------------------------------------------------------------------------------------------------------------
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

// use opcode in decoded struct value 0x63 to enter this function 
void btype(decoded_instr_t instruction, uint32_t registers[], uint32_t programCounter, uint32_t target_address)
{
    int32_t rs1_value = registers[instruction.rs1]; // vbalue rs1 reg
    int32_t rs2_value = registers[instruction.rs2]; // vlue rs2 reg
    int32_t targetAddress; //  target adress
    
    
    targetAddress = programCounter + (instruction.imm << 1); //imm is shifted left by 1

   
    switch (instruction.funct3) {
        case 0x0: //beq
            if (rs1_value == rs2_value) {
                programCounter = targetAddress;
            }
            break;
        case 0x1: //bne
            if (rs1_value != rs2_value) {
                programCounter = targetAddress;
            }
            break;
        case 0x4: //blt
            if (rs1_value < rs2_value) {
                programCounter = targetAddress;
            }
            break;
        case 0x5: //bge
            if (rs1_value >= rs2_value) {
                programCounter = targetAddress;
            }
            break;
        case 0x8: //bltu
            if ((uint32_t)rs1_value < (uint32_t)rs2_value) {
                programCounter = targetAddress;
            }
            break;
        case 0x9: //bgeu
            if ((uint32_t)rs1_value >= (uint32_t)rs2_value) {
                programCounter = targetAddress;
            }
            break;
        default:
            // Invalid 
            printf("invalid branch");
            break;
    }

    #ifdef DEBUG
        printf("Executed Branch: funct3=0x%01x, rs1_value=%d, rs2_value=%d, targetAddress=0x%08x, programCounter=0x%08x\n",
               instruction.funct3, rs1_value, rs2_value, targetAddress, programCounter);
    #endif


}
