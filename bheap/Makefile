CC := gcc
CC2 := clang
CFLAGS := -std=c11 -ggdb

.PHONY: default clean

default:
	make bheap_demo.exe
bheap_demo.exe: bheap_demo.c bheap.h
	$(CC2) $(CFLAGS) -O3 $< -o $@
bheap_extern.h: bheap.h
	cp bheap.h $@
	sed -i 's/static //g' $@
clean: 
	rm *.exe bheap_extern.h
