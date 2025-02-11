#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


uint32_t make_R_type(uint32_t opcode, uint32_t rd, uint32_t funct3, uint32_t rs1 ,uint32_t rs2, uint32_t funct7)
{
	uint32_t r_type = 0;
	r_type |= opcode;
	r_type |= (rd << 6);
	r_type |= (funct3 << (6 + 5));
	r_type |= (rs1 << (6 + 5 + 3));
	r_type |= (rs2 << (6 + 5 + 3 + 5));
	r_type |= (funct7 << (6 + 5 + 3 + 5 + 5));
	return r_type;
}

uint32_t make_I_type(uint32_t opcode, uint32_t rd, uint32_t funct3, uint32_t rs1 ,uint32_t imm)
{
	uint32_t r_type = 0;
	r_type |= opcode;
	r_type |= (rd << 6);
	r_type |= (rd << (6 + 5));
	r_type |= (rd << (6 + 5 + 3));
	r_type |= (rd << (6 + 5 + 3 + 5));
	return r_type;
}



int main(int argc, char *argv[])
{
	uint32_t address = 0;
	FILE *fp;
	fp = fopen("input_file.dat", "w");
	if(fp == NULL)
	{
		fputs("open err", stderr);
	}
	else// write the file
	{
		//R and I opcode 0110011b 0x33
		uint32_t opcode= 0x33;

		for(int func7 = 0; func7 <= 7; func7++)
		{
			uint32_t func3;
			if(func7 == 5)
			{
				func3 = 0x02;
			}
			else
			{
				func3 = 0x00;
			}
		
			for(int rd = 0; rd < 2; rd++)
			{

				fprintf(fp, "%08X: %08X\n", address, make_R_type(opcode, rd, func3, rd, rd, func7));
				address += 4;
			}
		}
	}
	fclose(fp);
	return 0;
}



