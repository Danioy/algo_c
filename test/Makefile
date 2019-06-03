PATHU = ../unity/
PATHL = ../lib/

TGTS = test_llist

all: $(TGTS)

test_llist: test_llist.o llist.o unity.o
	gcc -Wall -Og -o $@ $^

test_%.o: test_%.c
	gcc -Wall -I$(PATHU) -I$(PATHL) -c $<

unity.o: $(PATHU)unity.c
	gcc -Wall -I$(PATHU) -c $<

llist.o: $(PATHL)llist.c
	gcc -Wall -I$(PATHL) -c $^

clean:
	rm -f $(TGTS) *.o
