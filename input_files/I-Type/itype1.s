.section .data
.align 4
data:
    .byte 0x12          # Byte data
    .half 0x3456        # Halfword data
    .word 0x789ABCDE    # Word data

.section .text
.align 4
.globl _start

_start:
    # Load Immediate to Setup Base Address
    la a0, data         # Load address of data into a0

    # I-Type Load Instructions
    lb a1, 0(a0)        # Load byte from data[0] into a1
    lh a2, 1(a0)        # Load halfword from data[1] into a2
    lw a3, 2(a0)        # Load word from data[2] into a3
    lbu a4, 0(a0)       # Load unsigned byte from data[0] into a4
    lhu a5, 1(a0)       # Load unsigned halfword from data[1] into a5

    nop

