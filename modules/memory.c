/*
Functions related to reading and writing from memory
*/
#include "../modules/memory.h"
#include "../modules/types.h"

// Returns a 32bit where the lower byte are the requested
// sign_extend = 0 for no sign extension.
// little-endian
uint32_t read_memory(uint32_t address, int sign_extend, memory_t *programMemory, uint8_t numBytes)
{
    uint32_t rtrnVal = 0;
    // Check allignment
    switch(numBytes)
    {
        case 1:
            // PASS
            break;
        case 2:
            if((address % 2) != 0)
	        {
                printf("un-aligned reference on 2 byte read\n");
                exit(EXIT_FAILURE);
	        }
            break;
        case 4:
            if((address % 4) != 0)
            {
                printf("un-aligned reference on 4 byte read\n");
                exit(EXIT_FAILURE);
               //*programCounter = (*programCounter + 3) & ~3;  // Round up to the nearest multiple of 4
                //printf("Adjusted Program Counter to 0x%08x\n", *programCounter);
            }
            break;
        default:
            printf("Incorrect numBytes in read_memory()\n");
            exit(EXIT_FAILURE);
            break;
    }
    // Get value
    for(int i = 0; i < numBytes; i++)
    {
        uint32_t byte = programMemory->array[programMemory->startAddress + address + i];
        printf("loading  0x%X at 0x%X\n", byte, programMemory->startAddress + address + i);
        rtrnVal = rtrnVal | (byte << (i * 8));
    }
    // Sign extension
    if(sign_extend)
    {
        switch(numBytes)
        {
            case 1:
                if(sign_extend && rtrnVal & 0x80)
                {
                    rtrnVal |= 0xFFFFFF00;
                }
                break;
            case 2:
                if(sign_extend && (rtrnVal & 0x8000))
                {
                    rtrnVal |= 0xFFFF0000;
                }
                break;
                // Errors get checked at alignment check
        }
    }
    return rtrnVal;
}

void write_memory(uint32_t address, memory_t *programMemory, uint8_t numBytes, uint32_t value)
{
    // Check allignment
    switch(numBytes)
    {
        case 1:
            // PASS
            break;
        case 2:
            if((address % 2) != 0)
	        {
		       printf("un-aligned reference on 2 byte write\n");
		       exit(EXIT_FAILURE);
	        }
            break;
        case 4:
            if((address % 4) != 0)
            {
                printf("un-aligned reference on 4 byte writen");
                exit(EXIT_FAILURE);
            }
            break;
        default:
            printf("Incorrect numBytes in write_memory()\n");
            exit(EXIT_FAILURE);
            break;
    }
    //Write Value
    for(int i = 0; i < numBytes; i++)
    {
        programMemory->array[programMemory->startAddress + address + i] = (value >> i * 8);
        printf("plaing 0x%X at 0x%X\n", (value >> i * 8), programMemory->startAddress + address + i);
    }
}
