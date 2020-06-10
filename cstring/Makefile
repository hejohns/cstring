CC := gcc
CC2 := clang
CFLAGS := -std=c11 -Wall -Wextra -ggdb -O0

.PHONY: default test clean

default:
	make test
cstring_tests_gcc.exe: cstring_tests.c
	$(CC) $(CFLAGS) $^ -o $@
cstring_tests_clang.exe: cstring_tests.c
	$(CC2) $(CFLAGS) $^ -o $@
test: cstring_tests_gcc.exe cstring_tests_clang.exe
	valgrind ./cstring_tests_gcc.exe
	valgrind ./cstring_tests_clang.exe
clean: 
	rm *.exe
