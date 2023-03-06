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
    li t0, 0 # output
    li t1, 32 # loop counter
    bitrev1_loop:
        beqz t1, bitrev1_end # end loop if counter is 0
        slli t0, t0, 1 # shift output left by 1 bit
        andi t2, a0, 1 # get the lowest bit of input
        or t0, t0, t2 # add it to output
        srli a0, a0, 1 # shift input right by 1 bit
        addi t1, t1, -1 # decrement counter
        j bitrev1_loop # repeat loop
    bitrev1_end:
    mv a0, t0 # return output in a0
    ret

# === The second version ===
# Reverse the bits in a0. Only use li, and, or, slli, srli!
bitrev2:
  li t0, 0xffffffff 
  and t1, a0, t0
  slli t1, t1, 16 
  and t2, a0, t0
  srli t2, t2, 16 
  or a0, t1, t2 # swaps the high 16 bits and the low 16 bits

  li t0, 0x00ff00ff
  and t1, a0, t0
  slli t1, t1, 8 
  li t0, 0xff00ff00
  and t2, a0, t0
  srli t2, t2, 8 
  or a0, t1, t2 # swaps the high 8 bits and the low 8 bits

  li t0, 0x0f0f0f0f
  and t1, a0, t0
  slli t1, t1, 4 
  li t0, 0xf0f0f0f0
  and t2, a0, t0
  srli t2, t2, 4 
  or a0, t1, t2 # swaps the high 4 bits and the low 4 bits

  li t0, 0x33333333
  and t1, a0, t0
  slli t1, t1, 2
  li t0, 0xcccccccc
  and t2, a0, t0
  srli t2, t2, 2
  or a0, t1, t2 # swaps the high 2 bits and the low 2 bits

  li t0, 0x55555555
  and t1, a0, t0
  slli t1, t1, 1 
  li t0, 0xaaaaaaaa
  and t2, a0, t0
  srli t2, t2, 1 
  or a0, t1, t2 # swaps the high 1 bits and the low 1 bits
  ret
