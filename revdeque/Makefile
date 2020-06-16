CXX := clang++
CXXFLAGS := -std=c++2a -Wall -Wextra -ggdb

.PHONY: default test clean

default:
	make clean && make test
revdeque_test.exe: revdeque_test.cpp revdeque.h
	$(CXX) $(CXXFLAGS) -O0 $< -o $@
test: revdeque_test.exe
	valgrind ./revdeque_test.exe
clean: 
	rm *.exe 