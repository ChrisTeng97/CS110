## Ex1.
1. >What caused the errors in `simple_fn`, `naive_pow`, and `inc_arr` that were reported by the Venus CC checker?

   `simple_fn`: Undeclared register `t0`: 
   ```
   [CC Violation]: (PC=0x00000080) Usage of unset register t0! editor.S:58 mv a0, t0
   ```

   `naive_pow`: Unsaved `a0, a1, s0`:
   ```
   [CC Violation]: (PC=0x00000090) Setting of a saved register (s0) which has not been saved! editor.S:83 li s0, 1
   [CC Violation]: (PC=0x00000098) Setting of a saved register (s0) which has not been saved! editor.S:86 mul s0, s0, a0
   [CC Violation]: (PC=0x00000098) Setting of a saved register (s0) which has not been saved! editor.S:86 mul s0, s0, a0
   [CC Violation]: (PC=0x00000098) Setting of a saved register (s0) which has not been saved! editor.S:86 mul s0, s0, a0
   [CC Violation]: (PC=0x00000098) Setting of a saved register (s0) which has not been saved! editor.S:86 mul s0, s0, a0
   [CC Violation]: (PC=0x00000098) Setting of a saved register (s0) which has not been saved! editor.S:86 mul s0, s0, a0
   [CC Violation]: (PC=0x00000098) Setting of a saved register (s0) which has not been saved! editor.S:86 mul s0, s0, a0
   [CC Violation]: (PC=0x00000098) Setting of a saved register (s0) which has not been saved! editor.S:86 mul s0, s0, a0
   ```

   `inc_arr`: Unsaved `ra,a0,a1,s0,s1,t0`:
   ```
   不想抄了
   ```

2. > In RISC-V, we call functions by jumping to them and storing the return address in the ra register. Does calling convention apply to the jumps to the `naive_pow_loop` or `naive_pow_end labels`?

   No. Since these aren't function calls; these are some branches, who returns no values & addresses, and not stores/loads `ra`.

3. > Why do we need to store `ra` in the prologue for `inc_arr`, but not in any other function?
   
   `inc_arr` calls `helper_fn` which would change the `ra`. Other functions makes no function calls inside.

4. > Why wasn't the calling convention error in `helper_fn` reported by the CC checker?
   
   Once you've fixed all the violations reported by the CC checker, the code might still fail: this is likely because there's still some remaining calling convention errors that Venus doesn't report. Since function calls in assembly language are ultimately just jumps, Venus can't report these violMUCH MUCH easier than ex1.
   
   ations without more information, **at risk of producing false positives**.  
   Venus's calling convention checker will not report all calling convention bugs; it is intended to be used primarily as a sanity check. Most importantly, **it will only look for bugs in functions that are exported with the `.globl` directive** - the meaning of `.globl` is explained in more detail in the Venus reference.

---
## Ex2.
MUCH MUCH easier than ex1.

---
## Ex3.
COOL!