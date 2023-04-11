# Ex1.

## Scenario1.

> (Venus won't let you change this, why?)

Directly mapped!

> Cache Size (Bytes): 32 (Why?)

4*8=32.

### Q1.
Hit rate: `0`.

This is because we're visiting the same set of cache every time. For example:  

We may access 0x10008000 at first, and load 0x10008000 and 0x10008004 into the cache(since the cache is 8-byte long, which could store 2 words). They're in the first set of the cache.  
The next time we access 0x10008020 (+8bytes), which would goes into the first set and causing conflict miss.  
The others are similar.

### Q2.
Obviously the hit rate would still be `0` since it doesn't touch the core problem: the conflict miss causing by the `stepsize`.

### Q3.
To take advantage of *temporal locality*, we could set the option to `read and write`.  
To take advantage of *spacial locality*, we could set the stepsize to 1. Since we're accessing the `0x....0` and `0x....4` for the first time, and next time we will access `0x....4` and `0x....8`, the 0x4 is reused.

now we have a hit rate of `0.75`. illustration:
```
0x0 - miss
0x0 - hit
0x4 - hit
0x4 - hit
0x8 - miss
0x8 - hit
0xC - hit
0xC - hit
```


## Scenario 2.

### Q1.
hit rate: `0.75`.  
Note that our block size = 16Bytes which could store 2 operations (8Bytes each) at the same time.
```
(lw) 0x0 set1 -> miss
(sw) 0x0 set1 -> hit 
(lw) 0x8 set1 -> hit
(sw) 0x8 set1 -> hit
(lw) 0x10 set2 -> miss
(sw) 0x10 set2 -> hit
(lw) 0x18 set2 -> hit
(sw) 0x18 set2 -> hit
```

### Q2.
hit rate goes to `1` as the rep count goes to infty.  
Since `array size` = `cache size`, so all the info are stored in the cache, in the first rep. So in the following rep-s, all the data could be accessed inside cache, which means `hit` as always.

### Q3.
software.intel.com/en-us/articles/**cache-blocking**-techniques  

By dividing the huge dataset into multiple small blocks, this technique let cache reads the dataset part by part.


## Scenerio 3.
### Q1.
Best case: LRU! with a hit rate of `0.5`.  

The first rep: always miss
```
(lw) 0x0 set1 -> miss
(lw) 0x20 set1 -> miss
(lw) 0x40 set2 -> miss
(lw) 0x60 set2 -> miss
```

The 2nd rep: always hit, since they're recorded into the cache.
```
(lw) 0x0 set1 -> hit
(lw) 0x20 set1 -> miss
(lw) 0x40 set2 -> miss
(lw) 0x60 set2 -> miss
```

Worst case: why not acting as a "Most Recently Used" cache? This is similar to a 1-way cache, and only 4 cache lines are available. Now the hit rate becomes `0`.

### Q2.
like the worst case, set cache associativity to 1, and block number to 4, you will get a constant `0` hit rate.


# Ex3.

```
struct log_entry{
    int status;  
    int reference_time;
    int src_ip;
    char URL[128];
    char bro[128];
}logs[NUM_ENTRIES];

```
Let `int status`, `int reference_time` and `int src_ip` in one cache line. (Frequently accessed data should be adjacent to each other in memory)
And change `reference_time` from `long` to `int`. (Use types with as few bytes as possible)
Keep `status` as `int` to align. (Avoid padding)


---
# Ex2.
The alternative `apply_gb()` implementation:
```c
Image apply_gb(Image a, FVec gv)
{
    Image b = gb_h(a, gv);
    Image c = gb_h(transpose(b),gv);
    c = transpose(c);
    free(b.data);
}
```

Running result:
```
gcc -O2  -o gbfloat_base main.c apply_gb_base.c -lm
./gbfloat_base test.jpg test_base.jpg 0.6 -2.0 2.0 1001 201
horizontal gaussian blur time: 0.351749 
vertical gaussian blur time: 0.402348 
0.766982 
gcc -O2  -o gbfloat_fast main.c apply_gb_fast.c -lm
./gbfloat_fast test.jpg test_fast.jpg 0.6 -2.0 2.0 1001 201
0.483483 
gcc -O2  -o test_accuracy test_accuracy.c -lm
./test_accuracy test_base.jpg test_fast.jpg
0.000000
```

## Q1.
> Why `gb_h()` runs faster than `gb_v()`?

The only difference between `gb_h()` and `gb_v()`:
```c
// gb_h()
sum += ... get_pixel(a, x + offset, y)[channel];
// gb_v()
sum += ... get_pixel(a, x, y + offset)[channel];
```

Consider the definition of `get_pixel()`:
```c
{
    ...
    return img.data + img.numChannels * (y * img.dimX + x);
}
```
Since `img.dimX` is usually a big value (>10), so:  
for `gb_v()`: this function changes `y`, so the different addresses it returned usually have a far distance(multiple `dimX`-s) between them.  
for `gb_h()`: this function changes `x`, so the different addresses it returned usually have a small distance(multiple `x`-s) between them.

So `gb_h()` is more cache-friendly, since for 1 miss, it would load it and its neighbours into the cache, which is more likely to cover the next `get_pixel()`. 
