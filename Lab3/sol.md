## Ex1
1. > What do the `.data`, `.word`, `.text` directives mean?  
   
   `.text`: 用来保存程序指令  
   `.data`: 用来存储已经初始化的全局变量，这些变量的值在程序启动之前就已确定  
   `.word`: 让汇编器编译一个32bit值并将它添加到活动段

   Or, more precisely,  
   `.text` is a read-only section containing executable code  
   `.data` is a read-write section containing global or static variables  
   `.word` indicates 32-bit comma separated words (naturally aligned)  

   Or, according to CS61C UC Berkerly, `--version = 20su`,  
   `.text` denotes code storage  
   `.data` denotes data storage  
   `.word` indicates 32-bit comma separated words (naturally aligned)  
   哎CS110抄都不好好抄……

2. >What number did the program output? What does this number represent?

    34; `Fib(9)`.

3. >At what address is `n` stored in memory?
   
   0x10000010. This is based on the instruction `la t3, n` so we could know the content inside register `t3` is the address of `n`.

4. >Manually editing ...
   
   After the instruction `lw t3, 0(t3)` is done, register `t3` has value `0x00000009`. Modify it to `0x0000000D` (13 demical), we get the return value `233`.

---
## Ex2
1. >The register representing the variable `k`.  
   
   `t0`.

2. >The registers acting as pointers to the `source` and `dest` arrays.
   
   `t1`, `t2`.

3. >The assembly code for the loop found in the C code.
   
```
loop:
	slli t3, t0, 2
	add t4, t1, t3
	lw t5, 0(t4)
	beq t5, x0, exit
	add t6, t2, t3
	sw t5, 0(t6)
	addi t0, t0, 1
	jal x0, loop
```

4. >How the pointers are manipulated in the assembly code.
   
    In C codes accessing the `k`-th item in a list (`dest` or `source`) is actually add `k*sizeof(int)` to the pointer `list[0]` (very simplified).  
    It's similar in Assembly: `t0` stands for `k`, and `t3` multiply `k` to `4*k` where `4` is the size of a word.  
    Then the instructions `add t4, t1, t3` and `add t6, t2, t3` just do the work of adding `4*k` to access the `k`-th item. Then using the `lw` instruction to load the content of the pointer.
   
---
## Ex3
Iterately finished the question, or more vividly, using the `for` loop.