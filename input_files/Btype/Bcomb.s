.section .text
.global _start

_start:
    # Setup test values in registers
    li x1, 10         # x1 = 10
    li x2, 10         # x2 = 10
    li x3, -5         # x3 = -5
    li x4, 15         # x4 = 15
    li x5, 0          # x5 = 0
    li x6, 0xFFFFFFFF # x6 = -1 (unsigned max)

    # BEQ Test (Equal values should branch)
    beq x1, x2, beq_taken
    li x7, 1          # x7 = 1 (should not execute if branch works)

beq_taken:
    li x7, 2          # x7 = 2 if branch taken

    # BNE Test (Not equal should branch)
    bne x1, x4, bne_taken
    li x8, 1          # x8 = 1 (should not execute if branch works)

bne_taken:
    li x8, 2          # x8 = 2 if branch taken

    # BLT Test (x3 = -5 is less than x1 = 10, should branch)
    blt x3, x1, blt_taken
    li x9, 1          # x9 = 1 (should not execute if branch works)

blt_taken:
    li x9, 2          # x9 = 2 if branch taken

    # BGE Test (x1 = 10 is greater than x3 = -5, should branch)
    bge x1, x3, bge_taken
    li x10, 1         # x10 = 1 (should not execute if branch works)

bge_taken:
    li x10, 2         # x10 = 2 if branch taken

    # BLTU Test (x5 = 0 is less than x6 = -1 in unsigned comparison, should branch)
    bltu x5, x6, bltu_taken
    li x11, 1         # x11 = 1 (should not execute if branch works)

bltu_taken:
    li x11, 2         # x11 = 2 if branch taken

    # BGEU Test (x6 = -1 is greater than x5 = 0 in unsigned comparison, should branch)
    bgeu x6, x5, bgeu_taken
    li x12, 1         # x12 = 1 (should not execute if branch works)

bgeu_taken:
    li x12, 2         # x12 = 2 if branch taken

    # Halt execution
    li a7, 10
    ecall
