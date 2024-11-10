CC = gcc
CFLAGS = -Wall -std=c99 -pedantic

all: a2q1 a2q2

a2q1: q1.c q1_functions.c
	$(CC) $(CFLAGS) -o a2q1 q1.c q1_functions.c

a2q2: q2.c q2_functions.c
	$(CC) $(CFLAGS) -o a2q2 q2.c q2_functions.c -lm

clean:
	rm -f a2q1 a2q2