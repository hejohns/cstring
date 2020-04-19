CC := clang 
CFLAGS := -std=c11 -Wall -Wextra -ggdb

.PHONY: clean

cstring_tests.exe: cstring.c cstring_tests.c
	$(CC) $(CFLAGS) $^ -o $@

clean: 
	find cstring_tests.exe | xargs rm
