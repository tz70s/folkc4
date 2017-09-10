CC=gcc
CFLAGS=-O3 -Wall -W

folkc4: folkc4.c vm.o lexer.o
	$(CC) $(CFLAGS) -o $@ $^

%.c.o: vm.c lexer.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean
clean:
	rm *.o folkc4
