    .section .text
    .align 4
    .globl _start

_start:
    # Arithmetic and Logical Instructions
    li a0, 10
    li a1, 5
    add a2, a0, a1     # a2 = 10 + 5
    sub a3, a0, a1     # a3 = 10 - 5
    xor a4, a0, a1     # a4 = 10 ^ 5
    or  a5, a0, a1     # a5 = 10 | 5
    and a6, a0, a1     # a6 = 10 & 5
    sll a2, a0, a1     # a2 = 10 << 5
    srl a3, a0, a1     # a3 = 10 >> 5 (logical)
    sra a4, a0, a1     # a4 = 10 >> 5 (arithmetic)
    slt a5, a0, a1     # a5 = (10 < 5) ? 1 : 0
    sltu a6, a1, a0    # a6 = (5 < 10) ? 1 : 0 (unsigned)

    nop
