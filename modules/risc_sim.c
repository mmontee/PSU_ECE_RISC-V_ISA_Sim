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
				myParams.startAddress = strtoul(argv[count + 1], NULL, 0);
				printf("Start Address = %d\n", myParams.startAddress);
			}
			else if(strcmp(temp, "-ft") == 0)
			{
				myParams.inputFileType = strtoul(argv[count + 1], NULL, 0);
				printf("Input File Type = %d\n", myParams.inputFileType);
			}
			else if(strcmp(temp, "-sp") == 0)
			{
				myParams.inputFileType = strtoul(argv[count + 1], NULL, 0);
				printf("Input File Type = %d\n", myParams.inputSpaceCount);
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
    char line[64];

    while (fgets(line, sizeof(line), input->inputFilePath) != NULL)
    {
        // Trim leading and trailing whitespace from the line
        char *trimmedLine = line;
        while (*trimmedLine == ' ' || *trimmedLine == '\t') trimmedLine++; // Skip leading spaces/tabs
        char *end = trimmedLine + strlen(trimmedLine) - 1;
        while (end > trimmedLine && (*end == '\n' || *end == '\r' || *end == ' ' || *end == '\t')) end--;
        *(end + 1) = '\0'; // Null-terminate the trimmed line

        // Find the ':' to locate the instruction
        int count = 0;
        while (trimmedLine[count] != ':' && trimmedLine[count] != '\0')
        {
            count++;
        }

        if (trimmedLine[count] != ':')
        {
            printf("Error: Invalid line format (missing ':')\n");
            exit(EXIT_FAILURE);
        }

        // Extract the address from the line
        char addressString[count + 1];
        memcpy(addressString, trimmedLine, count);
        addressString[count] = '\0';
        uint32_t address = (int)strtol(addressString, NULL, 16);

        // Jump past the ': ' to get to the instruction
        count += input->inputFileType == 0 ? input->inputSpaceCount : 2;

        // Determine the length of the instruction
        int instructionLength = 0;
        for (int i = count; trimmedLine[i] != '\0'; i += 2)
        {
            // Check if the characters are valid hexadecimal digits
            if (!isxdigit(trimmedLine[i]) || !isxdigit(trimmedLine[i + 1]))
            {
                break; // Stop if non-hexadecimal characters are encountered
            }
            instructionLength += 2;
        }

        // Check if the instruction is longer than 8 characters
        if (instructionLength > 8)
        {
            printf("Error: Instruction at address 0x%08X is longer than 8 characters (length: %d)\n", address, instructionLength);
            exit(EXIT_FAILURE);
        }

        // Pad the instruction with zeros to make it 8 characters (4 bytes)
        char paddedInstruction[9] = "00000000"; // Default padding
        memcpy(paddedInstruction + (8 - instructionLength), &trimmedLine[count], instructionLength);

        // Process the padded instruction (8 characters)
        for (int i = 0; i < 8; i += 2)
        {
            char byteString[3] = {0, 0, '\0'};
            // Reverse the byte order for big-endian storage
            memcpy(byteString, &paddedInstruction[6 - i], 2);
            programMemory.array[address + (i / 2)] = (uint8_t)strtol(byteString, NULL, 16);
        }

        programMemory.instructionCount++;
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
