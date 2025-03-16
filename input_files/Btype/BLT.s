.section .text
.global _start

_start:
    li x1, -5
    li x2, 10
    li x7, 0  # Success register

    blt x1, x2, blt_pass
    li x7, -1  # Fail case
blt_pass:
    li x7, 3  # Success

    li a7, 10
   # ecall
