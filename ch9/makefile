#

TGTS = 9-1 9-2
CFLAGS = -Wall -g -O3

ALL: $(TGTS)

9-%: 9-%.c
	gcc $(CFLAGS) -o$@ $<

pq.o: pq.c
	gcc $(CFLAGS) -c $<
