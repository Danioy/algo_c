
TGTS = 8-1 8-2 8-3

ALL: $(TGTS)

8-%: 8-%.c
	gcc -Wall -g -Og -o$@ $<

clean:
	rm -f $(TGTS) *.o
