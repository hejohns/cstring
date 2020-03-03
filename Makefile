CXX := gcc
CXXFLAGS := -std=c11 -Wall -Wextra -ggdb

cstring_tests.exe: cstring.c cstring_tests.c
	$(CXX) $(CXXFLAGS) $^ -o $@

clean: 
	find cstring_tests.exe | xargs rm
