#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Default values
    unsigned int start_address = 0;
    unsigned int stack_size = 65536;

    // Check if filename is provided
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename> [start_address] [stack_size]\n", argv[0]);
        return 1;
    }

    // Read the filename
    char *filename = argv[1];

    // Read the optional start_address (if provided)
    if (argc > 2) {
        start_address = strtoul(argv[2], NULL, 0);
    }

    // Read the optional stack_size (if provided)
    if (argc > 3) {
        stack_size = strtoul(argv[3], NULL, 0);
    }

    // Print the values
    printf("Filename: %s\n", filename);
    printf("Start Address: 0x%X\n", start_address);
    printf("Stack Size: %u bytes\n", stack_size);

    return 0;
}
