all:
	gcc test_float.c -o test_float -O3 -Wall -march=native
	gcc test_double.c -o test_double -O3 -Wall -march=native
