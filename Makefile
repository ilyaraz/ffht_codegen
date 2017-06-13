CC = gcc
CFLAGS = -O3 -march=native -std=c99 -pedantic -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes

all:
	$(CC) fht_avx.c -c $(CFLAGS)
	$(CC) test_float.c fht_avx.o -o test_float $(CFLAGS)
	$(CC) test_double.c fht_avx.o -o test_double $(CFLAGS)
