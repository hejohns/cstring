CC := clang 
CFLAGS := -std=c11 -Wall -Wextra -ggdb

.PHONY: test clean

cstring_tests.exe: cstring.o cstring_tests.o
	$(CC) $(CFLAGS) $^ -o $@
cstring.o: cstring.c
	$(CC) $(CFLAGS) -c $^ -o $@
cstring_tests.o: cstring_tests.c
	$(CC) $(CFLAGS) -c $^ -o $@
test: cstring_tests.exe
	valgrind ./cstring_tests.exe
clean: 
	printf "cstring_tests.exe\ncstring.o\ncstring_tests.o" | xargs -L 1 rm
