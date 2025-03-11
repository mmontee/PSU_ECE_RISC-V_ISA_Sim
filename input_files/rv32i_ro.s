    .section .text
    .align 2
    .globl _start

_start:
    # Load 0x7FFFFFFF using LUI and ADDI
    lui t1, 0x7FFFF     # Load upper 20 bits (0x7FFFF000)
    addi t1, t1, -1     # t1 = 0x7FFFFFFF (2147483647, max signed 32-bit)

    # Load 0x80000000 using LUI and ADDI
    lui t2, 0x80000     # Load upper 20 bits (0x80000000)
    addi t2, t2, 0      # No need to modify, already exact value

    li t3, 1            # Load constant 1

    # Positive Overflow Test: 0x7FFFFFFF + 1
    add a0, t1, t3      # Expected: 0x80000000 (-2147483648, overflow)

    # Negative Overflow Test: 0x80000000 - 1
    sub a1, t2, t3      # Expected: 0x7FFFFFFF (2147483647, overflow)

    # End of test
    nop
