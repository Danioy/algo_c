
TGTS = 4-3 4-2 4-4 4-5 4-21


ALL: $(TGTS)

4-2%: 4-2%.o poly.o
	gcc -Wall -I. -o$@ $^

4-1%: 4-1%.o
	gcc -Wall -lm -o$@ $<

4-%: 4-%.o ../lib/stack.o
	gcc -Wall -o$@ $^

poly.o: poly.c
	gcc -Wall -O3 -I. -c $<

%.o: %.c
	gcc -Wall -Og -I../lib/ -c $<

../lib/stack.o: ../lib/stack.c
	gcc -Wall -Og -I../lib/ -c -o$@ $<

.PHONY: clean
clean:
	rm -f $(TGTS) *.o
