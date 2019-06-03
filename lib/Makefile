#

TGTS = common.o list.o stack.o

ALL: $(TGTS)

%.o: %.c
	gcc -Wall -Og -I. -c $<

clean:
	rm -f $(TGT) *.o
