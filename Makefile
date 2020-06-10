CC := gcc
CC2 := clang
CFLAGS := -std=c11 -Wall -Wextra -ggdb
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -ggdb

.PHONY: default test clean

default:
	make test
cstring_tests_gcc.exe: cstring_tests.c
	$(CC) $(CFLAGS) $^ -o $@
cstring_tests_clang.exe: cstring_tests.c
	$(CC2) $(CFLAGS) $^ -o $@
grid2d_tests.exe: grid2d_tests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
bheap.exe: bheap.c bheap.h
	$(CC2) -std=c11 -ggdb -O0 $< -o $@
bheap_extern.h: bheap.h
	cp bheap.h $@
	sed -i 's/static //g' $@
test: cstring_tests_gcc.exe cstring_tests_clang.exe
	valgrind ./cstring_tests_gcc.exe
	valgrind ./cstring_tests_clang.exe
clean: 
	rm *.exe bheap_extern.h
