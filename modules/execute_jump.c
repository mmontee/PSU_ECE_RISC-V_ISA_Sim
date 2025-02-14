#include <stdio.h>
#include <stdint.h>
#include "../modules/decode.h"

extern uint32_t registers[32]; 
extern uint32_t programCounter; 

void execute_jump(decoded_instr_t decoded) {
    switch (decoded.opcode) {
        case 0x6F: { // JAL (Jump and Link)
            uint32_t return_address = programCounter + 4; // Address after current instruction
            programCounter = programCounter + decoded.imm; // Jump to target address
            if (decoded.rd != 0) { // Avoid writing to x0
                registers[decoded.rd] = return_address;
            }
            printf("Executed JAL: rd=%u, target_pc=0x%08x\n", decoded.rd, programCounter);
            break;
        }

        case 0x67: { // JALR (Jump and Link Register)
            uint32_t return_address = programCounter + 4; // Address after current instruction
            programCounter = (registers[decoded.rs1] + decoded.imm) & ~1; // Jump to target address with LSB cleared
            if (decoded.rd != 0) { // Avoid writing to x0
                registers[decoded.rd] = return_address;
            }
            printf("Executed JALR: rd=%u, rs1=%u, target_pc=0x%08x\n", decoded.rd, decoded.rs1, programCounter);
            break;
        }

        default:
            printf("Unsupported jump instruction: opcode 0x%02x\n", decoded.opcode);
            break;
    }
}
