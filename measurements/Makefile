CC = gcc
CFLAGS = -O3 -march=native -std=c99 -pedantic -Wall -Wextra -Wshadow -Wpointer-arith -Wcast-qual -Wstrict-prototypes -Wmissing-prototypes

run_float: run_float.c to_run.h
	$(CC) run_float.c -o run_float $(CFLAGS)

run_double: run_double.c to_run.h
	$(CC) run_double.c -o run_double $(CFLAGS)
