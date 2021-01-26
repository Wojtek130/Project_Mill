CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror
#CFLAGS=-std=c11 -Wall -Wextra
LDFLAGS=-lm
LDLIBS =`pkg-config gtk+-3.0 --cflags --libs`
NAME = mill

$(NAME): main.o mill.o lin-fifo.o data_sending.o
	$(CC) $(CFLAGS) -g main.o mill.o lin-fifo.o data_sending.o $(LDLIBS) -o $(NAME) $(LDFLAGS)

main.o: main.c mill.h fifo.h  data_sending.h
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

mill.o: mill.c mill.h data_sending.h
	$(CC) $(CFLAGS) -c mill.c $(LDLIBS) -o mill.o

lin-fifo.o: lin-fifo.c fifo.h
	$(CC) $(CFLAGS) -c lin-fifo.c -o lin-fifo.o

data_sending.o: data_sending.c data_sending.h mill.h fifo.h 
	$(CC) $(CFLAGS) -c data_sending.c $(LDLIBS) -o data_sending.o
	
mill_debug: main.o mill.o
	$(CC) $(CFLAGS) -g $(LDLIBS) main.o mill.o -o mill_debug

clean:
	rm -f main.o mill.o lin-fifo.o data_sending.o mill AtoB BtoA 
