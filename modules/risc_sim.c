#include "../modules/risc_sim.h"
#include <ctype.h>


input_params_t parse_args(int argc, char *argv[])
{
	input_params_t myParams;
	// Set defaults
	myParams.startAddress = DEFAULT_START_ADDRESS;
	myParams.stackPointer = DEFAULT_STACK_ADDRESS;
	myParams.inputFileType = 0;
	myParams.inputSpaceCount = 2;

	if(argc <= 1)
	{
		printf("No input path given.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		int count = 1;
		while(count < argc)
		{
			char *temp = argv[count];
			if(strcmp(temp,"-f") == 0)
			{
				myParams.inputFilePath = fopen(argv[count + 1], "r");
				printf("Input file path taken : %s\n", argv[count + 1]);
			}
			else if(strcmp(temp, "-s") == 0)
			{
				myParams.stackPointer = strtoul(argv[count + 1], NULL, 0);
				printf("Stack Pointer = %d\n", myParams.stackPointer);
			}
			else if(strcmp(temp, "-a") == 0)
			{
				myParams.startAddress = strtoul(argv[count + 1], NULL, 16);
				printf("Start Address = %d\n", myParams.startAddress);
			}
			count++;
		}
	}
	return myParams;
}


memory_t parse_input(input_params_t *input)
{
	memory_t programMemory;
    programMemory.instructionCount = 0;
	programMemory.startAddress = input->startAddress;

	char line[100];
	char address[10];
	char data[20];
	while (fgets(line, sizeof(line), input->inputFilePath) != NULL) {
		char *colon = strchr(line, ':');
		if (colon != NULL) {
			int addressLength = colon - line;
			strncpy(address, line, addressLength);
			address[addressLength] = '\0';
			uint32_t baseAddress = (int)strtol(address, NULL, 16);
			colon++;
			while (*colon == ' ' || *colon == '\t') {
				colon++;
			}
			strcpy(data, colon);
			data[strcspn(data, "\n")] = 0;
			uint8_t length = strlen(data) - 1;
			#ifdef DEBUG 
				printf("length = %d\n", length);
			#endif 
			if(length == 4)
			{
				write_memory(baseAddress, &programMemory, 2, (int)strtol(data, NULL, 16));
	
			}
			else
			{
				write_memory(baseAddress, &programMemory, 4, (int)strtol(data, NULL, 16));
			} 
        	#ifdef DEBUG  
				printf("Address: %s, Data: %s\n", address, data);
			#endif 
			programMemory.instructionCount++;
		}
		
	}	
	return programMemory;
}



void print_bits(uint32_t reg, uint32_t registers[])
{
	uint32_t localReg = registers[reg];
	switch(reg)
	{
		case 0:
			printf("Zero Constant \t\t\tx%02d = 0x%08X = ", reg, localReg);
			break;
		case 1:
			printf("Return Address \t\t\tx%02d = 0x%08X = ", reg, localReg);
			break;
		case 2:
			printf("Stack Pointer \t\t\tx%02d = 0x%08X = ", reg, localReg);
			break;
		case 3:
			printf("Global Pointer \t\t\tx%02d = 0x%08X = ", reg, localReg);
			break;
		case 4:
			printf("Thread Pointer \t\t\tx%02d = 0x%08X = ", reg, localReg);
			break;
		case 5:
		case 6:
		case 7:
			printf("Temporaries \t\t\tx%02d = 0x%08X = ", reg, localReg);
			break;
		case 8:
			printf("Save Frame Pointer \t\tx%02d = 0x%08X = ", reg, localReg);
			break;
		case 9:
			printf("Saved Reg \t\t\tx%02d = 0x%08X = ", reg, localReg);
			break;
		case 10:
		case 11:
			printf("Fn args / Return vals \t\tx%02d = 0x%08X = ", reg, localReg);
			break;
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
			printf("Fn args \t\t\tx%02d = 0x%08X = ", reg, localReg);
			break;
		case 18:
		case 19:
		case 20:
		case 21:
		case 22:
		case 23:
		case 24:
		case 25:
		case 26:
		case 27:
			printf("Saved register \t\t\tx%02d = 0x%08X = ", reg, localReg);
			break;
		case 28:
		case 29:
		case 30:
		case 31:
			printf("Temporaries \t\t\tx%02d = 0x%08X = ", reg, localReg);
			break;
		default:
			printf("REG \t\t\tx%02d = 0x%08X = ", reg, localReg);
			break;
	}

	for(int i = 0; i < 32; i++)
	{
		int temp = (localReg & (0x80000000 >> i))? 1: 0;
		printf("%d", temp);
	}
	printf("\n");
}
