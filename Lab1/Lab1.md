# Lab1

## Exercise 3

The bit pattern looks like an **'A'**. 

Five decimal digits: **6, 9, 15, 9, 9**.

Five hexadecimal digits: **6, 9, F, 9, 9**.

The letter drawn with '1, 1, 9, 9, 6' is **'J'**.

The letter drawn with '0xF8F88' is **'F'**.

For 'B', the hexadecimal representation is **0xE9E9E**. 

For 'N', the hexadecimal representation is **0x9DB9**. 

## Exercise 4

The dollar bills in the ten envelopes: **1, 2, 4, 8, 16, 32, 64, 128, 256, 489**.

## Exercise 5

### Version 32bit:

Size of char: 1  
Size of short: 2  
Size of short int: 2  
Size of int: 4  
Size of long int: 4  
Size of unsigned int: 4  
Size of void *: 4  
Size of size_t: 4  
Size of float: 4  
Size of double: 8  
Size of int8_t: 1  
Size of int16_t: 2  
Size of int32_t: 4  
Size of int64_t: 8  
Size of time_t: 4  
Size of clock_t: 4  
Size of struct tm: 44  
Size of NULL: 4  

---

### Version 64bit:

Size of char: 1  
Size of short: 2  
Size of short int: 2  
Size of int: 4  
Size of long int: 8  
Size of unsigned int: 4  
Size of void *: 8  
Size of size_t: 8  
Size of float: 4  
Size of double: 8  
Size of int8_t: 1  
Size of int16_t: 2  
Size of int32_t: 4  
Size of int64_t: 8  
Size of time_t: 8  
Size of clock_t: 8  
Size of struct tm: 56  
Size of NULL: 8  

---

### Diff

long int: 4 bytes in 32bit, 8 bytes in 64bit.  
void *: 4 bytes in 32bit, 8 bytes in 64bit.  
Here, length of address in 32bit system equals to 4byte, in 64bit system equals to 8byte.  
size_t: the length of address. So 4 bytes in 32bit, 8 bytes in 64bit.  
NULL: An address. So 4 bytes in 32bit, 8 bytes in 64bit.  
time_t, clock_t: `typedef long time_t`, `typedef long clock_t`.  

struct tm:
it has 9 int defined in the struct, this takes 36 bytes.  
The glibc also has these 2 additional fields:  
```c
long tm_gmtoff;           /* Seconds east of UTC */
const char *tm_zone;      /* Timezone abbreviation */
```
In 32bit system, this would take 4+4=8 bytes. In 64bit system, this would take 8+8=16 bytes.  
Also, in the 64bit version, due to the memory alignment, after the 9th int, 4 bytes would be remain empty, then comes the long and the char*.  
So the 64bit version would take an extra 4 bytes.
So this is where 44 and 56 comes from.  
