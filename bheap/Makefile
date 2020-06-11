CC := gcc
CC2 := clang
CFLAGS := -std=c11 -ggdb

.PHONY: default clean

default:
	make bheap_demo.exe
bheap_demo.exe: bheap_demo.c bheap.h
	$(CC2) $(CFLAGS) -O3 $< -o $@
bheap_extern_helper.h: bheap.h
	cp $< $@
	sed -i 's/static //g' $@
bheap_extern.o: bheap_extern.c bheap_extern_helper.h
	$(CC) $(CFLAGS) -O3 -c $< -o $@
bheap_extern_demo.o : bheap_extern_demo.c bheap_extern.h
	$(CC) $(CFLAGS) -O3 -c $< -o $@
bheap_extern_demo.exe : bheap_extern.o bheap_extern_demo.o
	$(CC) $(CFLAGS) -O3 $^ -o $@
clean: 
	rm *.exe *.o bheap_extern_helper.h
