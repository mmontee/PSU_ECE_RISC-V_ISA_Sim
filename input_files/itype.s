	.section .text
	.align 2
	.globl _start

	.equ x, 0          # Symbolic name for X's position on the stack
	.equ y, 4          # Symbolic name for Y's position on the stack
	.equ yb1, 5        # Displacement for 2nd byte of Y (little endian)

_start:
	# Stack space allocation
	addi sp, sp, -8    # Allocate space for two 4-byte values (X, Y) on stack  

	# Load immediate values
	li t0, 0           # Load 0 into t0
	li t1, 2047        # Load upper limit for 12-bit immediate
	li t2, -2048       # Load lower limit for 12-bit immediate

	# I-Type Arithmetic Operations
	addi t0, t0, 10    # Add immediate value to t0
	addi t1, t1, -11   # Add negative immediate value to t1

	# Set Less Than Immediate Tests
	slti t3, t0, 15    # t3 = (t0 < 15)
	sltiu t4, t0, 20   # Unsigned compare t0 < 20

	# Logical Operations
	xori t5, t0, 0xF   # XOR immediate with t0
	ori  t6, t1, 0xA   # OR immediate with t1
	andi a0, t2, 0x7   # AND immediate with t2

	# Shift Operations
	slli t0, t0, 2     # Logical left shift by 2
	srli t1, t1, 3     # Logical right shift by 3
	srai t2, t2, 1     # Arithmetic right shift by 1

	# Store results in memory
	sw t0, x(sp)       # Store t0 to X on stack
	sw t1, y(sp)       # Store t1 to Y on stack
	sb t2, yb1(sp)     # Store single byte from t2 into second byte of Y

	# Load data from memory
	la a2, var          # Load address of var into a2
	lw t3, 0(a2)        # Load word from var into t3
	sw t3, x(sp)        # Write t3 to X

	.word 0             # Halt simulation

var:
	.word 0x12345678    # Static data for memory testing
