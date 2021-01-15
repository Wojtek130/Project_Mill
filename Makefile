#CC=gcc
#CFLAGS=-std=c11 -Wall -Wextra -Werror
#LDFLAGS=-lm
#LDLIBS ='pkg-config gtk+-3.0 --cflags --libs'
#NAME = mill

mill: main.o mill.o
	#$(CC) $(CFLAGS) -g   main.c mill.c 'pkg-config gtk+-3.0 --cflags --libs'
	#$(CC) main.c mill.c -o mill $(CFLAGS) `pkg-config gtk+-3.0 --cflags --libs`
	gcc -std=c99 -Wall main.c mill.c  `pkg-config gtk+-3.0 --cflags --libs` -o mill
	
mill_debug: main.o mill.o
	gcc -std=c99 -Wall main.c mill.c -g `pkg-config gtk+-3.0 --cflags --libs` -o mill_debug

clean:
	rm -f main.o mill.o mill
