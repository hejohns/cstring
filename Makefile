CXX := gcc
CXXFLAGS := -std=gnu11 -Wall -Wextra -ggdb

cstring_tests.exe: cstring.c cstring_tests.c
	$(CXX) $(CXXFLAGS) $^ -o $@
