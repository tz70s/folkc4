CC=gcc
CFLAGS=-O3 -Wall -W

c4clone: c4clone.c vm.o
	$(CC) $(CFLAGS) -o $@ $^

%.c.o: vm.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm *.o c4clone
