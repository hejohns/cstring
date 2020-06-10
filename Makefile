# template
CC := gcc
CC2 := clang
CFLAGS := -std=c11 -Wall -Wextra -ggdb
CXX := g++
CXX2 := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -ggdb

.PHONY: default clean

default:
	git push origin
	git push gitlab_eecs
	git push gitlab_umich
clean: 
	rm *.exe 
