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

    # Overflow Test Cases
    li a0, 0x7FFFFFFF  # Maximum positive 32-bit integer
    li a1, 1
    add a2, a0, a1     # Overflow: 0x7FFFFFFF + 1 -> -2147483648 (wrapped)

    li a0, -2147483648 # Minimum 32-bit integer
    li a1, -1
    sub a3, a0, a1     # Overflow: -2147483648 - (-1) -> 2147483647 (wrapped)

    li a0, 0xFFFFFFFF  # -1 in signed 32-bit
    li a1, 1
    add a2, a0, a1     # -1 + 1 -> 0 (no overflow)

    li a0, 0x80000000  # Most negative 32-bit number
    sra a4, a0, a1     # Arithmetic shift right: should stay -2147483648

    li a0, 31
    li a1, 1
    sll a2, a1, a0     # Shift left 1 by 31 places -> sign bit set (0x80000000)

    li a0, 0
    li a1, 32
    sll a2, a0, a1     # Shift left past 31 should give 0

    # End of test cases
    nop

