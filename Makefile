# template
CC := gcc
CC2 := clang
CFLAGS := -std=c11 -Wall -Wextra -ggdb
CXX := g++
CXX2 := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -ggdb

.PHONY: default clean

default:
	make clean
clean: 
	rm *.exe 
