        .section .text
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

    # Immediate Arithmetic Instructions
    addi a2, a0, -3    # a2 = 10 + (-3)
    xori a3, a0, 7     # a3 = 10 ^ 7
    ori  a4, a0, 7     # a4 = 10 | 7
    andi a5, a0, 7     # a5 = 10 & 7
    slli a6, a0, 2     # a6 = 10 << 2
    srli a2, a0, 2     # a2 = 10 >> 2 (logical)
    srai a3, a0, 2     # a3 = 10 >> 2 (arithmetic)
    slti a4, a0, 20    # a4 = (10 < 20) ? 1 : 0
    sltiu a5, a1, 10   # a5 = (5 < 10) ? 1 : 0 (unsigned)

    # Load and Store Instructions
    la t0, test_data
    lw t1, 0(t0)       # Load word
    sw t1, 4(t0)       # Store word
    lb t2, 1(t0)       # Load byte (signed)
    lbu t3, 1(t0)      # Load byte (unsigned)
    lh t4, 2(t0)       # Load half-word (signed)
    lhu t5, 2(t0)      # Load half-word (unsigned)
    sb t2, 5(t0)       # Store byte
    sh t3, 6(t0)       # Store half-word

    # Branch Instructions (modified targets within valid range)
    beq a0, a1, skip   # Branch if equal (should not branch)
    bne a0, a1, label  # Branch if not equal (should branch)
label:
    blt a1, a0, label2 # Branch if less than (should branch)
    bge a0, a1, label3 # Branch if greater or equal (should branch)
    bltu a1, a0, label4 # Branch if less than (unsigned) (should branch)
    bgeu a0, a1, label5 # Branch if greater or equal (unsigned) (should branch)

skip:
    # Jump Instructions
    j continue        # Unconditional jump
label2:
    jal ra, continue  # Jump and link (store return address in ra)
label3:
    jalr ra, a0, 0    # Jump and link register (computed jump)
label4:
    ebreak            # Trigger debugger breakpoint
label5:
    ecall             # Environment call

continue:
    # Safe infinite loop within valid range
    j continue

    .section .data
    .align 4

test_data:
    .word 0x12345678

