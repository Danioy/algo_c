
TGTS = 4-3 4-2 4-4 4-5


ALL: $(TGTS)

4-%: 4-%.o ../lib/stack.o
	gcc -Wall -o$@ $^

%.o: %.c
	gcc -Wall -Og -I../lib/ -c $<

../lib/stack.o: ../lib/stack.c
	gcc -Wall -Og -I../lib/ -c -o$@ $<

.PHONY: clean
clean:
	rm -f $(TGTS) *.o
