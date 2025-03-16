# Test BNE
.text
main:
    li x1, 10
    li x2, 5
    bne x1, x2, label  # If x1 != x2, jump
    li x3, 1  # Should be skipped
label:
    li x3, 0  # Expected execution
    jr ra
