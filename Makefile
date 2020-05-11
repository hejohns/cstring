CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -ggdb
CXX := g++
CXXFLAGS := -std=c++11 -Wall -Wextra -ggdb

.PHONY: test clean

cstring_tests.exe: cstring_tests.c
	$(CC) $(CFLAGS) $^ -o $@
grid2d_tests.exe: grid2d_tests.cpp
	$(CXX) $(CXXFLAGS) $^ -o $@
test: cstring_tests.exe grid2d_tests.exe
	valgrind ./cstring_tests.exe
	valgrind ./grid2d_tests.exe
clean: 
	rm *.exe massif*
