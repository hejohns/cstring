CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -ggdb

.PHONY: default test clean

default:
	make clean && make test
revdeque_test.exe: revdeque_test.cpp revdeque.h
	$(CXX) $(CXXFLAGS) -O0 $< -o $@
revdeque_benchmark.exe: revdeque_benchmark.cpp revdeque.h
	$(CXX) $(CXXFLAGS) -O0 $< -o $@
vector_benchmark.exe: vector_benchmark.cpp
	$(CXX) $(CXXFLAGS) -O3 $< -o $@
test: revdeque_test.exe
	valgrind ./revdeque_test.exe
clean: 
	rm *.exe 
