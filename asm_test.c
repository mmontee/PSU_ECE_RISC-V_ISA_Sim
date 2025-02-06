#include <stdio.h>

int main() {
    int lb_result, lbu_result, lh_result, lhu_result, lw_result;

    asm volatile (
        // Define the memory arrays inside the assembly section
        ".section .data\n"
        "byte_array: .byte 1, 2, 3, 4\n"
        "half_array: .half 0x1234, 0x9ABC\n"
        "word_array: .word 0x12345678, 0x9ABCDEF0\n"
        ".section .text\n"

        // Load Byte (3rd element of byte_array, value = 3)
        "la t0, byte_array\n"  
        "lb %0, 2(t0)\n"

        // Load Byte Unsigned (3rd element of byte_array, value = 3, zero-extended)
        "lbu %1, 2(t0)\n"

        // Load Halfword (2nd element of half_array, value = 0x9ABC)
        "la t1, half_array\n"
        "lh %2, 2(t1)\n"

        // Load Halfword Unsigned (2nd element of half_array, value = 0x9ABC)
        "lhu %3, 2(t1)\n"

        // Load Word (2nd element of word_array, value = 0x9ABCDEF0)
        "la t2, word_array\n"
        "lw %4, 4(t2)\n"

        : "=r" (lb_result), "=r" (lbu_result), "=r" (lh_result), "=r" (lhu_result), "=r" (lw_result) // Output operands
        : // No input operands
        : "t0", "t1", "t2" // Clobbered registers
    );

    // Print the results
    printf("Loaded Byte (lb, sign-extended) : %d (0x%X)\n", lb_result, lb_result);
    printf("Loaded Byte Unsigned (lbu, zero-extended) : %d (0x%X)\n", lbu_result, lbu_result);
    printf("Loaded Halfword (lh, sign-extended) : %d (0x%X)\n", lh_result, lh_result);
    printf("Loaded Halfword Unsigned (lhu, zero-extended) : %d (0x%X)\n", lhu_result, lhu_result);
    printf("Loaded Word (lw) : %d (0x%X)\n", lw_result, lw_result);

    return 0;
}

