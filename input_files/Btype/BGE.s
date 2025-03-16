.section .text
.global _start

_start:
    li x1, 10
    li x2, -5
    li x7, 0  # Success register

    bge x1, x2, bge_pass
    li x7, -1  # Fail case
bge_pass:
    li x7, 4  # Success

    li a7, 10
   # ecall
