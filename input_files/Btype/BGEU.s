.section .text
.global _start

_start:
    li x1, 0xFFFFFFFF  # Max unsigned
    li x2, 0
    li x7, 0  # Success register

    bgeu x1, x2, bgeu_pass
    li x7, -1  # Fail case
bgeu_pass:
    li x7, 6  # Success

    li a7, 10
    //ecall
