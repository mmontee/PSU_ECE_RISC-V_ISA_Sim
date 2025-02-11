#include "../modules/risc_sim.h"


input_params_t parse_args(int argc, char *argv[])
{
	input_params_t myParams;
	// Set defaults
	myParams.instructionCount = 0;
	myParams.startAddress = 0;
	myParams.stackSize = 0;
	myParams.inputFileType = 0;

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
				myParams.stackSize = strtoul(argv[count + 1], NULL, 0);
				printf("Stack Size = %d\n", myParams.stackSize);
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
			count++;
		}
	}
	return myParams;
}


memory_t parse_input(input_params_t *input)
{
	memory_t programMemory;
	programMemory.startAddress = input->startAddress;
	char line[64];
	if(input->inputFileType== 0)
	{
	    uint32_t index = 0;
	    while (fgets(line, sizeof(line), input->inputFilePath) != NULL)
	    {
            input->instructionCount++;
            // Following the ':' is the command, find the ':'
            int count = 0;
            char peekChar;
            peekChar = line[count];
            while(peekChar != ':')
            {
				count++;
				peekChar = line[count];
            }
            // Now copy the 8 byte word into memory 1 byte at a time
            count += 2; // Jump past the ': '
            for(int i = 6; i >= 0; i-=2)
            {
				char byteString[3] = {0, 0, '\0'};
				memcpy(byteString, &line[count + i], 2);
				programMemory.array[input->startAddress + index] = (int)strtol(byteString, NULL, 16);
				index++;
            }
	    }
	}
	else
	{
		// Get a line from the file or fail trying
		while (fgets(line, sizeof(line), input->inputFilePath) != NULL)
		{
			input->instructionCount++;
			// Following the ':' is the command, find the ':'
			int count = 0;
			char peekChar;
			peekChar = line[count];
			while(peekChar != ':')
			{
				count++;
				peekChar = line[count];
			}
			char addressString[count + 1];
			int index = 0;
			// the characters from 0 to count shoud be the address
			memcpy(addressString, &line[0], count);
			// the address from the inputfile is the baseAddress
			uint32_t baseAddress = (int)strtol(addressString, NULL, 16);
			// Check address for alignment
			if(baseAddress % 4 != 0)
			{
				printf("un-aligned reference. Address : 0x%08X\n", baseAddress);
				exit(EXIT_FAILURE);
			}
			// Now copy the 8 byte word into memory 1 byte at a time
			count += 2; // Jump past the ': '

			for(int i = 6; i >= 0; i-=2)// Every two characters is a byte.
			{
				char byteString[3] = {0, 0, '\0'};
				memcpy(byteString, &line[count + i], 2);
				programMemory.array[programMemory.startAddress + baseAddress + index] = (uint8_t)strtol(byteString, NULL, 16);
				index++;
			}
		}
	}
	return programMemory;
}

