.data
n: .word 3 # number of test data
data: # input, answer
.word 0x12345678, 0x1E6A2C48
.word 0x71C924BF, 0xFD24938E
.word 0x19260817, 0xE8106498

.text
# === main and helper functions ===
# You don't need to understand these, but reading them may be useful
main:
    la t0, n
    lw s0, 0(t0)
    la s1, data
    main_loop: # run each of the n tests
        beq s0, zero, main_loop_end
        lw a0, 0(s1)
        jal print_hex_and_space # print input
        lw a0, 4(s1)
        jal print_hex_and_space # print answer
        lw a0, 0(s1)
        jal bitrev1
        jal print_hex_and_space # print result of bitrev1
        lw a0, 0(s1)
        jal bitrev2
        jal print_hex_and_space # print result of bitrev2
        jal print_newline
        addi s0, s0, -1
        addi s1, s1, 8
        j main_loop
    main_loop_end:
    li a0, 10
    ecall # exit

print_hex_and_space:
    mv a1, a0
    li a0, 34
    ecall
    li a1, ' '
    li a0, 11
    ecall
    ret

print_newline:
    li a1, '\n'
    li a0, 11
    ecall
    ret

# === The first version ===
# Reverse the bits in a0 with a loop
bitrev1:
    ### TODO: YOUR CODE HERE ###
    addi t0, x0, 0 # output
    addi t1, x0, 32 # cnt
    b1_loop:
        beq t1, x0, b1_end
        slli t0, t0, 1 # output: left-shift 1 digit
        andi t2, a0, 1 # get the last digit of input
        srli a0, a0, 1 # input: right-shift 1 digit
        add t0, t0, t2 # add
        addi t1, t1, -1
        j b1_loop
    b1_end:
        mv a0, t0
    ret

# === The second version ===
# Reverse the bits in a0. Only use li, and, or, slli, srli!
bitrev2:
    ### TODO: YOUR CODE HERE ###

    # input: a0; output: a0

    # swap the first 16 digits and last 16 digits
    li t0, 0xffffffff # 1111....
    and t1, a0, t0
    and t2, a0, t0
    slli t1, t1, 16
    srli t2, t2, 16
    or a0, t1, t2

    # for each 16 digits, swap the first 8 and last 8
    li, t0, 0x00ff00ff
    and t1, a0, t0
    li, t0, 0xff00ff00
    and t2, a0, t0
    slli t1, t1, 8
    srli t2, t2, 8
    or a0, t1, t2

    # for each 8 digits, swap the first 4 and last 4
    li, t0, 0x0f0f0f0f
    and t1, a0, t0
    li, t0, 0xf0f0f0f0
    and t2, a0, t0
    slli t1, t1, 4
    srli t2, t2, 4
    or a0, t1, t2

    # for each 4 digits, swap the first 2 and last 2
    li, t0, 0x33333333 # 0011 0011 0011 0011...
    and t1, a0, t0
    li, t0, 0xcccccccc # 1100 1100 1100 1100...
    and t2, a0, t0
    slli t1, t1, 2
    srli t2, t2, 2
    or a0, t1, t2

    # for each 2 digits, swap the first 1 and last 1
    li, t0, 0x55555555 # 0101 0101 0101 0101...
    and t1, a0, t0
    li, t0, 0xaaaaaaaa # 1010 1010 1010 1010...
    and t2, a0, t0
    slli t1, t1, 1
    srli t2, t2, 1
    or a0, t1, t2

    ret
