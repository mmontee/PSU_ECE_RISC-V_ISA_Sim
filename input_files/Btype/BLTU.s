.section .text
.global _start

_start:
    li x1, 0
    li x2, 0xFFFFFFFF  # -1 in signed, max in unsigned
    li x7, 0  # Success register

    bltu x1, x2, bltu_pass
    li x7, -1  # Fail case
bltu_pass:
    li x7, 5  # Success

    li a7, 10
    # ecall
