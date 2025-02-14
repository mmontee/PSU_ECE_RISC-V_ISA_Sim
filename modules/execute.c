/*
Functions related to executing instruction types
*/
#include "../modules/execute.h"

uint32_t execute_r_type(decoded_instr_t instruction, uint32_t registers[])
{
  uint32_t instructionCode = 0;
  switch(instruction.funct3)
  {
    case 0x0:
      switch(instruction.funct7)
      {
        case 0x0:
          add(instruction, registers);
          break;
        case 0x2:
          // sub
          break;
        default:
          printf("Unknown func7 code in R-type\n");
          exit(EXIT_FAILURE);
          break;
      }
      break;
    case 0x1:
      // sll
      break;
    case 0x2:
      // slt
      break;
    case 0x3:
      // sltu
      break;
    case 0x4:
      // xor
      break;
    case 0x5:
      switch(instruction.funct7)
      {
        case 0x0:
          // srl
          break;
        case 0x2:
          // sra
          break;
        default:
          printf("Unknown func7 code in R-type\n");
          exit(EXIT_FAILURE);
          break;
      }
      break;
    case 0x6:
      // or
      break;
    case 0x7:
      // and
      break;
    default:
      printf("Unknown func3 code in R-type\n");
      exit(EXIT_FAILURE);
      break;
  }
  return instructionCode;
}
