## ex1.
> Try to tell the difference of the following "load" intrisics:

- `_mm_load_si128`: load a 128-bit data, but the address should be 16-byte aligned. 
- `_mm_loadu_si128`: load a 128-bit data, but alignment not required. 
- `_mm_load_pd`: Load 128-bits (composed of 2 packed double-precision (64-bit) floating-point elements), requires 16-byte address alignment; **Column**-order
- `_mm_load1_pd`: Load 128-bits (composed of 2 packed double-precision (64-bit) floating-point elements), requires 16-byte address alignment; **NOT Column**-order (row?)