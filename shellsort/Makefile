CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -ggdb

.PHONY: default clean

default:
	make clean
shellsort_test.exe: shellsort_test.c shellsort.h
	$(CC) $(CFLAGS) -O3 $< -o $@
qsort_benchmark.exe: qsort_benchmark.c
	$(CC) $(CFLAGS) -O3 $< -o $@
clean: 
	rm *.exe 
