/*
Functions related to instructions
*/
#include "../modules/instructions.h"

//R-type instructions -----------------------------------------------------------------------------------------------------------------------------------------------
// ADD: rd = rs1 + rs2
void add(decoded_instr_t *instruction, uint32_t *registers)
{
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = registers[instruction->rs1] + registers[instruction->rs2];
    }
    #ifdef DEBUG
        printf("Executing add rd = %d : rs1 = %d : rs2 = %d.\n", registers[instruction->rd], registers[instruction->rs1] , registers[instruction->rs2] );
    #endif
}

// SUB: rd = rs1 - rs2
void sub(decoded_instr_t *instruction, uint32_t *registers)
{
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = registers[instruction->rs1] - registers[instruction->rs2];
    }
    #ifdef DEBUG
        printf("Executing SUB: rd = %d (rs1 = %d, rs2 = %d)\n",
               registers[instruction->rd], registers[instruction->rs1], registers[instruction->rs2]);
    #endif
}

// SLL: rd = rs1 << rs2
void sll(decoded_instr_t *instruction, uint32_t *registers)
{
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = registers[instruction->rs1] << (registers[instruction->rs2] & 0x1F);
    }
    #ifdef DEBUG
        printf("Executing SLL: rd = %d\n", registers[instruction->rd]);
    #endif
}

// SLT:  rd = (rs1 < rs2)?1:0
void slt(decoded_instr_t *instruction, uint32_t *registers)
{
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = ((int32_t)registers[instruction->rs1] < (int32_t)registers[instruction->rs2]) ? 1 : 0; //convert rs1 to signed 32 bit int
    }
    #ifdef DEBUG
        printf("Executing SLT: rd = %d\n", registers[instruction->rd]);
    #endif
}

// SLTU: rd = (rs1 < rs2)?1:0 zero-extends
void sltu(decoded_instr_t *instruction, uint32_t *registers)
{
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = (registers[instruction->rs1] < registers[instruction->rs2]) ? 1 : 0;
    }
    #ifdef DEBUG
        printf("Executing SLTU: rd = %d\n", registers[instruction->rd]);
    #endif
}

// XOR: rd = rs1 ^ rs2
void xor_r(decoded_instr_t *instruction, uint32_t *registers)
{
    if(instruction->rd != 0)
    {   
        registers[instruction->rd] = registers[instruction->rs1] ^ registers[instruction->rs2];
    }
    #ifdef DEBUG
        printf("Executing XOR: rd = %d\n", registers[instruction->rd]);
    #endif
}

// SRL: rd = rs1 >> rs2 
void srl(decoded_instr_t *instruction, uint32_t *registers)
{
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = registers[instruction->rs1] >> (registers[instruction->rs2] & 0x1F);
    }
    #ifdef DEBUG
        printf("Executing SRL: rd = %d\n", registers[instruction->rd]);
    #endif
}

//  SRA: rd = rs1 >> rs2 msb-extends
void sra(decoded_instr_t *instruction, uint32_t *registers)
{
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = ((int32_t)registers[instruction->rs1]) >> (registers[instruction->rs2] & 0x1F); //convert rs1 to signed 32 bit int
    }
    #ifdef DEBUG
        printf("Executing SRA: rd = %d\n", registers[instruction->rd]);
    #endif
}

// OR: rd = rs1 | rs2
void or_r(decoded_instr_t *instruction, uint32_t *registers)
{
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = registers[instruction->rs1] | registers[instruction->rs2];
    }
    #ifdef DEBUG
        printf("Executing OR: rd = %d\n", registers[instruction->rd]);
    #endif
}

// AND : rd = rs1 & rs2
void and_r(decoded_instr_t *instruction, uint32_t *registers)
{
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = registers[instruction->rs1] & registers[instruction->rs2];
    }
    #ifdef DEBUG
        printf("Executing AND: rd = %d\n", registers[instruction->rd]);
    #endif
}


//I-Type Instructions -----------------------------------------------------------------------------------------------------------------------------------------------
void addi(decoded_instr_t *instruction, uint32_t *registers) //rd = rs1 + imm
{
	int32_t imm = instruction->imm; // Start with the immediate value

	if (imm & (1 << 11)) {  // Check if the 12th bit (sign bit) is set
    		imm |= 0xFFFFF000;  // Extend sign to upper 20 bits
	}
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = registers[instruction->rs1] + imm;
    }
        #ifdef DEBUG
            printf("Executed ADDI: rd=%u, rs1=%u, imm=%d, Result=%d\n", instruction->rd, instruction->rs1, imm, registers[instruction->rd]);
        #endif
}

void slti(decoded_instr_t *instruction, uint32_t *registers) //rd = (rs1 < imm)?1:0
{
    int32_t imm = instruction->imm;

    if (imm & (1 << 11)) {
        imm |= 0xFFFFF000;
    }
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = ((int32_t)registers[instruction->rs1] < imm) ? 1 : 0;
    }
    #ifdef DEBUG
        printf("Executed SLTI: rd=%u, rs1=%u, imm=%d\n", instruction->rd, instruction->rs1, imm);
    #endif
}

void sltiu(decoded_instr_t *instruction, uint32_t *registers) //rd = (rs1 < imm)?1:0 zero extends
{
    uint32_t imm = instruction->imm;

    if (imm & (1 << 11)) {
        imm |= 0xFFFFF000;
    }

    if(instruction->rd != 0)

    {
        registers[instruction->rd] = (registers[instruction->rs1] < imm) ? 1 : 0;
    }

    #ifdef DEBUG


        printf("Executed SLTIU: rd=%u, rs1=%u, imm=%u\n", instruction->rd, instruction->rs1, imm);

    #endif
}

void xori(decoded_instr_t *instruction, uint32_t *registers) //rd = rs1 ^ imm
{
    int32_t imm = instruction->imm;

    if (imm & (1 << 11)) {
        imm |= 0xFFFFF000;
    }
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = registers[instruction->rs1] ^ imm;
    }
    #ifdef DEBUG
        printf("Executed XORI: rd=%u, rs1=%u, imm=%d\n", instruction->rd, instruction->rs1, imm);
    #endif
}

void ori(decoded_instr_t *instruction, uint32_t *registers) //rd = rs1 | imm
{
    int32_t imm = instruction->imm;

    if (imm & (1 << 11)) {
        imm |= 0xFFFFF000;
    }
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = registers[instruction->rs1] | imm;
    }
    #ifdef DEBUG
        printf("Executed ORI: rd=%u, rs1=%u, imm=%d\n", instruction->rd, instruction->rs1, imm);
    #endif
}

void andi(decoded_instr_t *instruction, uint32_t *registers) //rd = rs1 & imm
{
    int32_t imm = instruction->imm;

    if (imm & (1 << 11)) {
        imm |= 0xFFFFF000;
    }
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = registers[instruction->rs1] & imm;
    }
    #ifdef DEBUG
        printf("Executed ANDI: rd=%u, rs1=%u, imm=%d\n", instruction->rd, instruction->rs1, imm);
    #endif
}

void slli(decoded_instr_t *instruction, uint32_t *registers)
{
    int32_t imm = instruction->imm;

    if (imm & (1 << 11)) {
        imm |= 0xFFFFF000;
    }
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = registers[instruction->rs1] << (imm & 0x1F);
    }
    #ifdef DEBUG
        printf("Executed SLLI: rd=%u, rs1=%u, imm=%d\n", instruction->rd, instruction->rs1, imm);
    #endif
}

void srli(decoded_instr_t *instruction, uint32_t *registers)
{
    int32_t imm = instruction->imm;

    if (imm & (1 << 11)) {
        imm |= 0xFFFFF000;
    }
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = registers[instruction->rs1] >> (imm & 0x1F);
    }
    #ifdef DEBUG
        printf("Executed SRLI: rd=%u, rs1=%u, imm=%d\n", instruction->rd, instruction->rs1, imm);
    #endif
}

void srai(decoded_instr_t *instruction, uint32_t *registers)
{
    int32_t imm = instruction->imm;

    if (imm & (1 << 11)) {
        imm |= 0xFFFFF000;
    }
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = (int32_t)registers[instruction->rs1] >> (imm & 0x1F);
    }
    #ifdef DEBUG
        printf("Executed SRAI: rd=%u, rs1=%u, imm=%d\n", instruction->rd, instruction->rs1, imm);
    #endif
}

void lb(decoded_instr_t *instruction, uint32_t *registers, memory_t *memory) 
{

printf("\nin lb imm = 0x%X\n", instruction->imm);
    // Sign exend imm
    if(instruction->imm & 0x800)
    {
        instruction->imm |= 0xFFFFF000;
    }

    uint32_t address = registers[instruction->rs1] + (int32_t)instruction->imm; // This should be the byte address -note
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = read_memory(address, 1, memory, 1);  // Sign-extended
    }
    #ifdef DEBUG
        printf("Executed LB: rd=%u, rs1=%u, address=0x%08x, value=%d\n", instruction->rd, instruction->rs1, address, registers[instruction->rd]);
    #endif
    
}

void lh(decoded_instr_t *instruction, uint32_t *registers, memory_t *memory) 
{
    if(instruction->imm & 0x800)
    {
        instruction->imm |= 0xFFFFF000;;
    }
    uint32_t address = registers[instruction->rs1] + (int32_t)instruction->imm; // This should be the word address -note
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = read_memory(address, 1, memory, 2);   // Sign-extended    
    }
    #ifdef DEBUG
        printf("Executed LH: rd=%u, rs1=%u, address=0x%08x, value=%d\n", instruction->rd, instruction->rs1, address, registers[instruction->rd]);
    #endif
    
}

void lw(decoded_instr_t *instruction, uint32_t *registers, memory_t *memory) 
{
    if(instruction->imm & 0x800)
    {
        instruction->imm |= 0xFFFFF000;
    }
    uint32_t address = registers[instruction->rs1] + (int32_t)instruction->imm;
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = read_memory(address, 0, memory, 4);
    }
    #ifdef DEBUG
        printf("Executed LW: rd=%u, rs1=%u, address=0x%08x, value=%u\n", instruction->rd, instruction->rs1, address, registers[instruction->rd]);
    #endif
    
}

void lbu(decoded_instr_t *instruction, uint32_t *registers, memory_t *memory) 
{
    if(instruction->imm & 0x800)
    {
        instruction->imm |= 0xFFFFF000;
    }
    uint32_t address = registers[instruction->rs1] + (int32_t)instruction->imm;
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = read_memory(address, 0, memory, 1);  // Zero-extended
    }
    #ifdef DEBUG
        printf("Executed LBU: rd=%u, rs1=%u, address=0x%08x, value=%u\n", instruction->rd, instruction->rs1, address, registers[instruction->rd]);
    #endif
    
}

void lhu(decoded_instr_t *instruction, uint32_t *registers, memory_t *memory) 
{
    if(instruction->imm & 0x800)
    {
        instruction->imm |= 0xFFFFF000;
    }
    uint32_t address = registers[instruction->rs1] + (int32_t)instruction->imm;
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = read_memory(address, 0, memory, 2);  // Zero-extended
    }
    #ifdef DEBUG
        printf("Executed LHU: rd=%u, rs1=%u, address=0x%08x, value=%u\n", instruction->rd, instruction->rs1, address, registers[instruction->rd]);
    #endif
    
}

void jalr(decoded_instr_t *instruction, uint32_t *registers, uint32_t *programCounter)
{
   // **Sign-extend the 12-bit immediate**
    int32_t imm = (int32_t)(instruction->imm);
    if (imm & (1 << 11)) {  
        imm |= 0xFFFFF000;  // Extend sign to upper 20 bits
    }


    uint32_t return_address = *(programCounter) + 4;  // Save return address (PC + 4)

    // **Compute target address and ensure LSB is 0 (per RISC-V spec)**
    *(programCounter) = ((registers[instruction->rs1] + imm) & ~1);

    // **Store return address in rd (if not x0)**
    if (instruction->rd != 0) {  
        if(instruction->rd != 0)
        {
            registers[instruction->rd] = return_address;
        }
    }

    #ifdef DEBUG
        printf("Executed JALR: rd=%u, rs1=%u, imm=0x%08x (signed:%d), newPC=0x%08x\n", instruction->rd, instruction->rs1,imm,imm, *(programCounter));
    #endif

   // **Halt condition if return address (ra) is 0
    if (registers[1] == 0) { 
        printf("Halt condition met: Return address (ra) is 0\n");
        instruction->halt = 1;
        return;
    }

    *(programCounter) -= 4;
}

void ebreak()
{
    printf("EBREAK instruction executed: Entering debug mode or breaking execution.\n");
}

void ecall(decoded_instr_t *instruction, uint32_t *registers)
{
    switch(registers[7])
    {
        case 63:
            break;
        case 64:
            break;
        case 94:
            break;
        default:
            printf("Unknown ecall() code\n");
            instruction->halt = 1;
            break;
    }
    printf("ECALL instruction executed: System call invoked.\n");
}

//S-Type Instructions ------------------------------------------------------------------------------------------------------------------------------------------------

void sb(decoded_instr_t *instruction, uint32_t *registers, memory_t *memory)
{
    if(instruction->imm & 0x800)
    {
        instruction->imm |= 0xFFFFF000;
    }
    uint32_t address = registers[instruction->rs1] + (int32_t)instruction->imm; // This should be the byte address -note
    uint32_t value = 0;
    value = (registers[instruction->rs2] & 0xFF); // Store the lower 8 bits
    
    #ifdef DEBUG
        printf("Executed SB: rs1=%u, rs2=%u address=0x%08X, value=%u\n", instruction->rs1, instruction->rs2, address, value);
    #endif
    write_memory(address, memory, 1, value);
}

void sh(decoded_instr_t *instruction, uint32_t *registers, memory_t *memory)
{
    if(instruction->imm & 0x800)
    {
        instruction->imm |= 0xFFFFF000;
    }
    uint32_t address = registers[instruction->rs1] + (int32_t)instruction->imm; 
    uint32_t value = 0;
    value = (registers[instruction->rs2] & 0x0000FFFF); // Store the lower 16 bits
    
    #ifdef DEBUG
        printf("Executed SH:: rs1=%u, rs2=%u address=0x%08x, value=%u\n", instruction->rs1, instruction->rs2, address, value);
    #endif
    write_memory(address, memory, 2, value);
}

void sw(decoded_instr_t *instruction, uint32_t *registers, memory_t *memory)
{
    if(instruction->imm & 0x800)
    {
        instruction->imm |= 0xFFFFF000;
    }
    uint32_t address = registers[instruction->rs1] + (int32_t)instruction->imm; 
    
    #ifdef DEBUG
        printf("Executed SW:: rs1=%u, rs2=%u address=0x%08x, value=%u\n", instruction->rs1, instruction->rs2, address, instruction->rs2);
    #endif
    write_memory(address, memory, 4, registers[instruction->rs2]);
}


//B-Type Instructions ------------------------------------------------------------------------------------------------------------------------------------------------

void beq(decoded_instr_t *instruction, uint32_t *registers, uint32_t *programCounter)
{
    int32_t rs1_value = registers[instruction->rs1]; // vbalue rs1 reg
    int32_t rs2_value = registers[instruction->rs2]; // vlue rs2 reg
    if(instruction->imm & 0x1000)
    {
        instruction->imm |= 0xFFFFE000;
    }
    int32_t targetAddress = *(programCounter)  + (instruction->imm);
    if (rs1_value == rs2_value) 
    {
        *(programCounter)  = targetAddress - 4; // The - 4 counters the PC + 4 in the main loop
        #ifdef DEBUG
            printf("Executed BEQ - TAKEN: rs1=%d, rs2=%d, targetAddress=0x%08x\n", rs1_value, rs2_value, targetAddress);
        #endif
    }
    else
    {
        #ifdef DEBUG
            printf("Executed BEQ - NOT TAKEN: rs1=%d, rs2=%d, targetAddress=0x%08x\n", rs1_value, rs2_value, targetAddress);
        #endif
    }
    
}

void bne(decoded_instr_t *instruction, uint32_t *registers, uint32_t *programCounter)
{
    int32_t rs1_value = registers[instruction->rs1]; // vbalue rs1 reg
    int32_t rs2_value = registers[instruction->rs2]; // vlue rs2 reg
    if(instruction->imm & 0x1000)
    {
        instruction->imm |= 0xFFFFE000;
    }
    int32_t targetAddress = *(programCounter)  + (instruction->imm);
    if (rs1_value != rs2_value) 
    {
        *(programCounter)  = targetAddress - 4; // The - 4 counters the PC + 4 in the main loop
        #ifdef DEBUG
            printf("Executed BNE - TAKEN: rs1=%d, rs2=%d, targetAddress=0x%08x\n", rs1_value, rs2_value, targetAddress);
        #endif
    }
    else
    {
        #ifdef DEBUG
            printf("Executed BNE - NOT TAKEN: rs1=%d, rs2=%d, targetAddress=0x%08x\n", rs1_value, rs2_value, targetAddress);
        #endif
    }
    
}


void blt(decoded_instr_t *instruction, uint32_t *registers, uint32_t *programCounter)
{
    int32_t rs1_value = registers[instruction->rs1]; // vbalue rs1 reg
    int32_t rs2_value = registers[instruction->rs2]; // vlue rs2 reg
    if(instruction->imm & 0x1000)
    {
        instruction->imm |= 0xFFFFE000;
    }
    int32_t targetAddress = *(programCounter)  + (instruction->imm);
   printf("Current Program Counter (PC): 0x%08x\n", *programCounter);
   printf("%08x\n", instruction->imm);
    printf("%08x\n", instruction->imm << 1);
    printf("%08x\n", targetAddress);
    printf("%08x\n", targetAddress-4);
    if (rs1_value < rs2_value) 
    {
        *(programCounter)  = targetAddress - 4; // The - 4 counters the PC + 4 in the main loop
        #ifdef DEBUG
            printf("Executed BLT - TAKEN: rs1=%d, rs2=%d, targetAddress=0x%08x\n", rs1_value, rs2_value, *programCounter);
        #endif
    }
    else
    {
        #ifdef DEBUG
            printf("Executed BLT - NOT TAKEN: rs1=%d, rs2=%d, targetAddress=0x%08x\n", rs1_value, rs2_value, targetAddress);
        #endif
    }
}

void bge(decoded_instr_t *instruction, uint32_t *registers, uint32_t *programCounter)
{
    int32_t rs1_value = registers[instruction->rs1]; // vbalue rs1 reg
    int32_t rs2_value = (registers[instruction->rs2]); // vlue rs2 reg
    
    if(instruction->imm & 0x1000)
    {
        instruction->imm |= 0xFFFFE000;
    }
    int32_t targetAddress = *(programCounter)  + (instruction->imm);
    if(rs1_value >= rs2_value)
    {
        *(programCounter)  = targetAddress - 4; // The - 4 counters the PC + 4 in the main loop
        #ifdef DEBUG
            printf("Executed BGE - TAKEN: rs1=%d, rs2=%d, targetAddress=0x%08x\n", rs1_value , rs2_value, targetAddress);
        #endif
    }
    else
    {
        #ifdef DEBUG
            printf("Executed BGE - NOT TAKEN: rs1=%d, rs2=%d, targetAddress=0x%08x\n", rs1_value, rs2_value, targetAddress);
        #endif
    }

}


void bltu(decoded_instr_t *instruction, uint32_t *registers, uint32_t *programCounter)
{
    int32_t rs1_value = registers[instruction->rs1]; // vbalue rs1 reg
    int32_t rs2_value = registers[instruction->rs2]; // vlue rs2 reg
    if(instruction->imm & 0x800)
    {
        instruction->imm |= 0xFFFFE000;
    }
    int32_t targetAddress = *(programCounter)  + (instruction->imm);
    if ((uint32_t)rs1_value < (uint32_t)rs2_value) 
    {
        *(programCounter)  = targetAddress - 4; // The - 4 counters the PC + 4 in the main loop
        #ifdef DEBUG
            printf("Executed BLTU - TAKEN: rs1=%d, rs2=%d, targetAddress=0x%08x\n", rs1_value, rs2_value, targetAddress);
        #endif
    }
    else
    {
        #ifdef DEBUG
            printf("Executed BLTU - NOT TAKEN: rs1=%d, rs2=%d, targetAddress=0x%08x\n", rs1_value, rs2_value, targetAddress);
        #endif
    }

}


void bgeu(decoded_instr_t *instruction, uint32_t *registers, uint32_t *programCounter)
{
    int32_t rs1_value = registers[instruction->rs1]; // vbalue rs1 reg
    int32_t rs2_value = registers[instruction->rs2]; // vlue rs2 reg
    if(instruction->imm & 0x800)
    {
        instruction->imm |= 0xFFFFE000;
    }
    int32_t targetAddress = *(programCounter)  + (instruction->imm);
    
    if ((uint32_t)rs1_value >= (uint32_t)rs2_value) 
    {
        *(programCounter)  = targetAddress - 4; // The - 4 counters the PC + 4 in the main loop
        #ifdef DEBUG
            printf("Executed BGEU - TAKEN: rs1=%d, rs2=%d, targetAddress=0x%08x\n", rs1_value, rs2_value, targetAddress);
        #endif
    }
    else
    {
        #ifdef DEBUG
            printf("Executed BGEU - NOT TAKEN: rs1=%d, rs2=%d, targetAddress=0x%08x\n", rs1_value, rs2_value, targetAddress);
        #endif
    }

}

//U-Type Instructions ------------------------------------------------------------------------------------------------------------------------------------------------
void lui(decoded_instr_t *instruction, uint32_t *registers) //rd = imm << 12
{
    int32_t imm = instruction->imm;

    if (imm & (1 << 19)) {  // Sign extend if needed
        imm |= 0xFFF00000;
    }
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = imm << 12;
    }
    #ifdef DEBUG
        printf("Executed LUI: rd=%u, imm=0x%08x\n", instruction->rd, imm);
    #endif
}

void auipc(decoded_instr_t *instruction, uint32_t *registers, uint32_t *programCounter) //rd = PC + (imm << 12)
{
    int32_t imm = instruction->imm;

    if (imm & (1 << 19)) {  // Sign extend if needed
        imm |= 0xFFF00000;
    }
    if(instruction->rd != 0)
    {
        registers[instruction->rd] = *(programCounter) + (imm << 12);
    }
    #ifdef DEBUG
        printf("Executed AUIPC: rd=%u, imm=0x%08x, programCounter=0x%08X\n", instruction->rd, imm, *(programCounter));
    #endif
}



//J-Type Instructions ------------------------------------------------------------------------------------------------------------------------------------------------

void jal(decoded_instr_t *instruction, uint32_t *registers, uint32_t *programCounter)
{
    uint32_t return_address = *(programCounter) + 4; // Address after current instruction
    uint32_t imm = instruction->imm;

    if (imm & (1 << 19)) {  // If bit 19 (sign bit) is 1
        imm |= 0xFFF00000;  // Sign-extend the upper 12 bits
    }
    
    *(programCounter) = *(programCounter) + imm; // Jump to target address


    if (instruction->rd != 0) 
    { // Avoid writing to x0
        registers[instruction->rd] = return_address;
    
    }
    #ifdef DEBUG
        printf("Executed JAL: rd=%u, imm=0x%08x (signed: %d), Targetaddress(PC) =0x%08x\n", return_address, imm, imm,  *(programCounter));
    #endif
   *(programCounter) -= 4; 
}

