/*
Functions related to executing instruction types. Uses decoded instructions decoded_instr_t
*/
#include "../modules/execute.h"

uint32_t execute_r_type(decoded_instr_t instruction, hardware_t hrdwr)
{
    #ifdef DEBUG
        printf("Executing R-type instruction.");
    #endif
    uint32_t instructionCode = 0;
    switch(instruction.funct3)
    {
    case 0x0:
        switch(instruction.funct7)
        {
        case 0x0:// add
            add(instruction, hrdwr.registers);
            break;
        case 0x2:// sub
            sub(instruction, hrdwr.registers);
            break;
        default:
            printf("Unknown func7 code in R-type\n");
            exit(EXIT_FAILURE);
            break;
        }
        break;
    case 0x1:// sll
        sll(instruction, hrdwr.registers);
        break;
    case 0x2:// slt
        slt(instruction, hrdwr.registers);
        break;
    case 0x3:// sltu
        sltu(instruction, hrdwr.registers);
        break;
    case 0x4:// xor
        xor_r(instruction, hrdwr.registers);
        break;
    case 0x5:
        switch(instruction.funct7)
        {
        case 0x0:// srl
            srl(instruction,hrdwr.registers);
            break;
        case 0x2:// sra
            sra(instruction, hrdwr.registers);
            break;
        default:
            printf("Unknown func7 code in R-type\n");
            exit(EXIT_FAILURE);
            break;
        }
        break;
    case 0x6:// or
        or_r(instruction, hrdwr.registers);
        break;
    case 0x7:// and
        and_r(instruction, hrdwr.registers);
        break;
    default:
        printf("Unknown func3 code in R-type\n");
        exit(EXIT_FAILURE);
        break;
    }
    return instructionCode;
}

uint32_t execute_i_type(decoded_instr_t instruction, hardware_t hrdwr)
{
    #ifdef DEBUG
        printf("Executing I-type instruction.");
    #endif
    switch(instruction.opcode)// outermost switch collects all possible opcodes
    {
        case 0x13://0010011b ALU imm instructions
            switch(instruction.funct3)// select from alu ops
            {
                case 0x0:// addi
                    addi(instruction, hrdwr.registers);
                    break;
                case 0x1:// slli
                    slli(instruction, hrdwr.registers);
                    break;
                case 0x2:// slti
                    slti(instruction, hrdwr.registers);
                    break;
                case 0x3:// sltiu
                    sltiu(instruction, hrdwr.registers);
                    break;
                case 0x4:// xori
                    xori(instruction, hrdwr.registers);
                    break;
                case 0x5:
                    uint32_t bits = 0;
                    bits = (instruction.imm >> 5) & 0x7F;
                    switch(bits)// two different shift right
                    {
                    case 0x0:// srli
                        srli(instruction, hrdwr.registers);
                        break;
                    case 0x2:// srai
                        srai(instruction, hrdwr.registers);
                        break;
                    default:
                        printf("Unknown funct7 code in I-type. opcode: 0x%X\n", instruction.opcode);
                        exit(EXIT_FAILURE);
                        break;
                    }
                    break;
                case 0x6:// ori
                    ori(instruction, hrdwr.registers);
                    break;
                case 0x7:// andi
                    andi(instruction, hrdwr.registers);
                    break;                                     
                default:
                    printf("Unknown funct3 code in I-type. opcode: 0x%X\n", instruction.opcode);
                    exit(EXIT_FAILURE);
                    break;
            }
            break;
        case 0x03:// load ops
            switch(instruction.funct3)
            {
                case 0x0:// lb
                    lb(instruction, hrdwr);
                    break;
                case 0x1:// lh
                    lh(instruction, hrdwr);
                    break;
                case 0x2:// lw
                    break;
                case 0x4:// lbu
                    lbu(instruction, hrdwr);
                    break; 
                case 0x5:// lhu
                    lhu(instruction, hrdwr);
                    break;                                                                                                  
                default:
                    printf("Unknown funct3 code in I-type. opcode: 0x%X\n", instruction.opcode);
                    exit(EXIT_FAILURE);
                    break;
            }
            break;
        case 0x67:// jalr
        
            break;
        case 0x73:
            switch(instruction.imm)// two different shift right
            {
            case 0x0:// ecall
                break;
            case 0x1:// ebreak
                break;
            default:
                printf("Unknown imm code in I-type. opcode: 0x%X\n", instruction.opcode);
                exit(EXIT_FAILURE);
                break;
            }        
            break;          
        default:
            printf("Unknown opcode code in I-type\n");
            exit(EXIT_FAILURE);
            break;
    }
}



uint32_t execute_s_type(decoded_instr_t instruction, hardware_t hrdwr)
{
    #ifdef DEBUG
        printf("Executing S-type instruction.");
    #endif
    switch(instruction.funct3)
    {
        case 0x0:// sb
            break;
        case 0x1:// sh
            break;
        case 0x2:// sw
            break;                        
        default:
            printf("Unknown funct3 code in S-type\n");
            exit(EXIT_FAILURE);        
            break;
    }
}

uint32_t execute_b_type(decoded_instr_t instruction, hardware_t hrdwr)
{
    #ifdef DEBUG
        printf("Executing B-type instruction.");
    #endif
    switch(instruction.funct3)
    {
        case 0x0:// beq
            break;
        case 0x1:// bne
            break;
        case 0x4:// blt
            break;  
        case 0x5:// bge
            break;  
        case 0x6:// bltu
            break; 
        case 0x7:// bgeu
            break;                                                                       
        default:
            printf("Unknown funct3 code in B-type\n");
            exit(EXIT_FAILURE);        
            break;
    }
}

uint32_t execute_u_type(decoded_instr_t instruction, hardware_t hrdwr)
{
    #ifdef DEBUG
        printf("Executing U-type instruction.");
    #endif
    switch(instruction.opcode)
    {
        case 0x37:// lui
            lui(instruction, hrdwr.registers);
            break;
        case 0x17:// auipc
            auipc(instruction, hrdwr.registers);
            break;                     
        default:
            printf("Unknown opcode code in U-type\n");
            exit(EXIT_FAILURE);        
            break;
    }
}

uint32_t execute_j_type(decoded_instr_t instruction, hardware_t hrdwr)
{
    #ifdef DEBUG
        printf("Executing J-type instruction.");
    #endif
    switch(instruction.opcode)
    {
        case 0x6F:// jal
            break;
        default:
            printf("Unknown opcode code in U-type\n");
            exit(EXIT_FAILURE);        
            break;
    }
}

