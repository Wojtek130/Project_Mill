CC=gcc
#CFLAGS=-std=c11 -Wall -Wextra -Werror
CFLAGS=-std=c11 -Wall -Wextra
LDFLAGS=-lm
LDLIBS =`pkg-config gtk+-3.0 --cflags --libs`
NAME = mill

$(NAME): main.o mill.o lin-fifo.o
	$(CC) $(CFLAGS) main.o mill.o lin-fifo.o $(LDLIBS) -o $(NAME) $(LDFLAGS)

main.o: main.c mill.h fifo.h 
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

mill.o: mill.c mill.h 
	$(CC) $(CFLAGS) -c mill.c $(LDLIBS) -o mill.o

lin-fifo.o: lin-fifo.c fifo.h
	$(CC) $(CFLAGS) -c lin-fifo.c $(LDLIBS) -o lin-fifo.o
	
mill_debug: main.o mill.o
	$(CC) $(CFLAGS) -g $(LDLIBS) main.o mill.o -o mill_debug

clean:
	rm -f main.o mill.o lin-fifo.o mill AtoB BtoA
