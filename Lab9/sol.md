## ex1.
> Try to tell the difference of the following "load" intrisics:

- `_mm_load_si128`: load a 128-bit data, but the address should be 16-byte aligned. 
- `_mm_loadu_si128`: load a 128-bit data, but alignment not required. 
- `_mm_load_pd`: Load 128-bits (composed of 2 packed double-precision (64-bit) floating-point elements), requires 16-byte address alignment; **Column**-order
- `_mm_load1_pd`: Load 128-bits (composed of 2 packed double-precision (64-bit) floating-point elements), requires 16-byte address alignment; **NOT Column**-order (row?)

## ex2.
Take the advantage of SIMD of executing the same instruction on multiple data at the same time.

## ex3.
The loop unrolling has following advantages:
1. reduce the loop iterations, which also reduce the total costs of branch prediction (the number of branch reduced);
2. Increased data locality;
3. Take the advantage of MIMD.

## ex4.
https://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html

The website tells us everyting about optimization options.  
Some vectorizing options are enabled in `-O3`.

> Why the example program runs faster?

Under x86 instruction set, without `-O3` we have the following assembly code:
```asm
a:
        .zero   4
modify:
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], edi
        mov     edx, DWORD PTR a[rip]
        mov     eax, DWORD PTR [rbp-4]
        add     eax, edx
        mov     DWORD PTR a[rip], eax
        nop
        pop     rbp
        ret
main:
        push    rbp
        mov     rbp, rsp
        mov     DWORD PTR [rbp-4], 0
        jmp     .L3
.L4:
        mov     eax, DWORD PTR a[rip]
        add     eax, 1
        mov     DWORD PTR a[rip], eax
        add     DWORD PTR [rbp-4], 1
.L3:
        cmp     DWORD PTR [rbp-4], 999
        jle     .L4
        mov     DWORD PTR [rbp-8], 0
        jmp     .L5
.L6:
        mov     edx, DWORD PTR a[rip]
        mov     eax, DWORD PTR [rbp-8]
        add     eax, edx
        mov     DWORD PTR a[rip], eax
        add     DWORD PTR [rbp-8], 1
.L5:
        cmp     DWORD PTR [rbp-8], 999
        jle     .L6
        mov     eax, DWORD PTR a[rip]
        pop     rbp
        ret
```

However, with `-O3` enabled, we have:
```assembly
modify:
        add     DWORD PTR a[rip], edi
        ret
main:
        mov     eax, DWORD PTR a[rip]
        add     eax, 500500
        mov     DWORD PTR a[rip], eax
        ret
a:
        .zero   4
```

The `-O3` option increases the compling time to decrease the execution time. It calculates the constant out during the compling time. (However under `-O2` it could also be done.)