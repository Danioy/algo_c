
TGTS = 6-1 6-2 6-3 6-4 6-5

ALL: $(TGTS)

6-%: 6-%.c
	gcc -Wall -g -Og -o$@ $<

clean:
	rm -f $(TGTS) *.o
