mill_1: main.c mill.c
	gcc -xc -std=c11 -Wall -Wextra -Werror   main.o mill.o -lm -o mill_1

