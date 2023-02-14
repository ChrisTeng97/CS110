#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define PS(x) printf("Size of %s: %lu\n", #x, (long unsigned int)sizeof(x))

int main()
{
    PS(char);
    PS(short);
    PS(short int);
    PS(int);
    PS(long int);
    PS(unsigned int);
    PS(void *);
    PS(size_t);
    PS(float);
    PS(double);
    PS(int8_t);
    PS(int16_t);
    PS(int32_t);
    PS(int64_t);
    PS(time_t);
    PS(clock_t);
    PS(struct tm);
    PS(NULL);

    return 0;
}