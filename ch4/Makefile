
TGTS = 4-3 4-2 4-4

ALL: $(TGTS)

4-%: 4-%.o ../lib/stack.o
	gcc -Wall -o$@ $^

%.o: %.c
	gcc -Wall -Og -I../lib/ -c $<

clean:
	rm -f $(TGTS) *.o
