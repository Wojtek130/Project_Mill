#ifndef MILL_H
#define MILL_H
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>
// Wojciech Sniady, nr indeksu: 322993

typedef struct Board {
    int** data;
    int number_of_squares;
} Board;


Board *generate_board(int n);
void free_board(Board* board);
void print_board(Board* board);
void place_men(Board* board, bool players_1_turn);
bool mill_achieved(Board* board, int current_square, int current_field);

#endif