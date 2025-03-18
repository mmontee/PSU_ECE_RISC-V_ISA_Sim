    .section .text
    .globl _start

_start:
    # Test JAL - Jump and Link
    jal x1, target1   # Jump to target1, store return address in x1
    nop               


    # End of test
    j end_test

# Target addresses for jumps
target1:
    li x4, 1          # If we land here, set x4 to 1
    jalr x0, x1, -4   #this should generate HALT

end_test:
    # End the test with an infinite loop
    nop
    j end_test
