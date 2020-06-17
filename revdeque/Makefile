CXX := clang++
CXXFLAGS := -std=c++17 -Wall -Wextra -ggdb

.PHONY: default test clean

default:
	make clean && make test
revdeque_test.exe: revdeque_test.cpp revdeque.h
	$(CXX) $(CXXFLAGS) -O0 $< -o $@
revdeque_benchmark.exe: revdeque_benchmark.cpp revdeque.h
	$(CXX) $(CXXFLAGS) -DNDEBUG -O3 $< -o $@
vector_benchmark.exe: vector_benchmark.cpp
	$(CXX) $(CXXFLAGS) -DNDEBUG -O3 $< -o $@
test: revdeque_benchmark.exe vector_benchmark.exe
	time ./revdeque_benchmark.exe > delete.txt
	time ./vector_benchmark.exe > delete2.txt
	diff delete.txt delete2.txt
clean: 
	rm *.exe 
