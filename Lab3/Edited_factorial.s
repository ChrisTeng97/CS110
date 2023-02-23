.data
# originally: test_input: .word 3 6 7 8
test_input: .word 3 4 8 9

.text
main:
	add t0, x0, x0 # t0 = 0
	addi t1, x0, 4 # t1 = 4
	la t2, test_input # t2 = ptr
main_loop:
	beq t0, t1, main_exit
	slli t3, t0, 2 # t3 = t0 * 4
	add t4, t2, t3 # t4 = t2 + t3
	lw a0, 0(t4) # a0 = *t4

	addi sp, sp, -20
	sw t0, 0(sp)
	sw t1, 4(sp)
	sw t2, 8(sp)
	sw t3, 12(sp)
	sw t4, 16(sp)

	jal ra, factorial

	lw t0, 0(sp)
	lw t1, 4(sp)
	lw t2, 8(sp)
	lw t3, 12(sp)
	lw t4, 16(sp)
	addi sp, sp, 20

	addi a1, a0, 0
	addi a0, x0, 1
	ecall # Print Result
	addi a1, x0, ' '
	addi a0, x0, 11
	ecall
	
	addi t0, t0, 1
	jal x0, main_loop
main_exit:  
	addi a0, x0, 10
	ecall # Exit

factorial:
	# YOUR CODE HERE
	# calculate $n!$, where n = a0
	addi t0, x0, 1 # t0 = cnt = 1 -> n (1,n included)
	addi t1, x0, 1 # t1 = res, starts at 1
	
f_loop:
	mul t1, t1, t0 # t1 *= 1, t1*= 2, ... 
	addi t0, t0, 1 # t0++
	blt a0, t0, f_return # when a0<t0 (now t0=n+1) break
	jal x0, f_loop # continue the loop

f_return:
	add a0, t1, x0 # return a0
	jr ra # return, so end
