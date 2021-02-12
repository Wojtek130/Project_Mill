CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Wextra -Wno-unused-parameter -Wno-unused-variable -Werror
#CFLAGS=-std=c11 -Wall -Wextra
LDFLAGS=-lm
LDLIBS =`pkg-config gtk+-3.0 --cflags --libs`
NAME = mill

$(NAME): main.o mill.o lin-fifo.o data_sending.o gui.o
	$(CC) $(CFLAGS) -g main.o mill.o lin-fifo.o data_sending.o gui.o $(LDLIBS) -o $(NAME) $(LDFLAGS)

main.o: main.c mill.h fifo.h  data_sending.h
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

mill.o: mill.c mill.h data_sending.h
	$(CC) $(CFLAGS) -c mill.c $(LDLIBS) -o mill.o

lin-fifo.o: lin-fifo.c fifo.h
	$(CC) $(CFLAGS) -c lin-fifo.c -o lin-fifo.o

data_sending.o: data_sending.c data_sending.h mill.h fifo.h 
	$(CC) $(CFLAGS) -c data_sending.c $(LDLIBS) -o data_sending.o

gui.o: gui.c gui.h mill.h fifo.h 
	$(CC) $(CFLAGS) -c gui.c $(LDLIBS) -o gui.o

clean:
	rm -f main.o mill.o lin-fifo.o data_sending.o gui.o mill AtoB BtoA 
