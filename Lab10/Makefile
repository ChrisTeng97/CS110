CC = gcc
CFLAGS = -Wall -Wextra -std=gnu99 -fopenmp
EXECUTABLES = hello v_add dotp matmul hello.exe v_add.exe dotp.exe matmul.exe

all: $(EXECUTABLES)

% : %.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	$(RM) $(EXECUTABLES)

.PHONY: all clean
