CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -ggdb

.PHONY: default clean

default:
	make clean
shellsort_test.exe: shellsort_test.c shellsort.h
	$(CC) $(CFLAGS) -O3 $< -o $@
shellsort_vla_test.exe: shellsort_test.c shellsort.h
	$(CC) $(CFLAGS) -DSHELLSORT_USE_VLA -O3 $< -o $@
qsort_benchmark.exe: qsort_benchmark.c
	$(CC) $(CFLAGS) -O3 $< -o $@
qsort_vla_benchmark.exe: qsort_vla_benchmark.c
	$(CC) $(CFLAGS) -O3 $< -o $@
std_sort_benchmark.exe: std_sort_benchmark.cpp
	g++ -std=c++11 -Wall -Wextra -ggdb -O3 $< -o $@
clean: 
	rm *.exe 
