
TGTS = 7-1 7-2 7-3 7-4

ALL: $(TGTS)

7-%: 7-%.c
	gcc -Wall -g -Og -o$@ $<

clean:
	rm -f $(TGTS) *.o
