.section .text
.align 4
.globl _start

_start:
    # I-Type Instructions
    li a0, 10       # Load immediate value 10 into a0
    li a1, 5        # Load immediate value 5 into a1

    addi a2, a0, 15    # a2 = a0 + 15
    xori a3, a1, 3     # a3 = a1 ^ 3
    andi a4, a0, 7     # a4 = a0 & 7
    ori  a5, a1, 8     # a5 = a1 | 8

    slli a6, a0, 2     # a6 = a0 << 2 (logical shift left)
    srli a7, a1, 1     # a7 = a1 >> 1 (logical shift right)
    srai t0, a0, 1     # t0 = a0 >> 1 (arithmetic shift right)

    slti t1, a0, 20    # t1 = (a0 < 20) ? 1 : 0
    sltiu t2, a1, 15   # t2 = (a1 < 15) ? 1 : 0 (unsigned)

    nop
