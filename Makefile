CC=gcc
CFLAGS=-std=c11 -Wall -Wextra -Werror
#LDFLAGS=-lm
LDLIBS =`pkg-config gtk+-3.0 --cflags --libs`
NAME = mill

$(NAME): main.o mill.o
	$(CC) $(CFLAGS) main.o mill.o  $(LDLIBS) -o $(NAME)

main.o: main.c mill.h
	$(CC) $(CFLAGS) -c main.c $(LDLIBS) -o main.o

mill.o: mill.c mill.h
	$(CC) $(CFLAGS) -c mill.c $(LDLIBS) -o mill.o
	
mill_debug: main.o mill.o
	$(CC) $(CFLAGS) -g $(LDLIBS) main.o mill.o -o mill_debug

clean:
	rm -f main.o mill.o mill
