CC := clang 
CFLAGS := -std=c11 -Wall -Wextra -ggdb

.PHONY: test clean

cstring_tests.exe: cstring_tests.c
	$(CC) $(CFLAGS) $^ -o $@
test: cstring_tests.exe
	valgrind ./cstring_tests.exe
clean: 
	printf "cstring_tests.exe\n" | xargs -L 1 rm
