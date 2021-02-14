#ifndef MILL_H
#define MILL_H
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <unistd.h>
#include "fifo.h"
#define MAX_TEXT_LENGHT 20
// Wojciech Sniady, nr indeksu: 322993

typedef struct Board {
    int** data;
    int number_of_squares;
} Board;

typedef struct ButtonBoard {
    GtkWidget*** data;
    int number_of_squares;
} ButtonBoard;

extern PipesPtr potoki;
extern int CURRENT_MOVE[2];
extern GtkWidget* CURRENT_BUTTON;
//extern int CURRENT_SQUARE_NUMBER;
//extern int CURRENT_FIELD_NUMBER;
extern bool YOUR_TURN;
extern bool P_1_TURN;
extern ButtonBoard* BUTTON_BOARD; 
extern Board *BOARD; 
extern int MEN_NUMBER_P_1;
extern int MEN_NUMBER_P_2;
extern int SQUARE_NUMBER_TO_MOVE_FROM;
extern int FIELD_NUMBER_TO_MOVE_FROM;
extern int TOTALLY_PLACED_MEN_PLAYER_1;
extern int TOTALLY_PLACED_MEN_PLAYER_2;
extern GtkWidget *FIXED_BOX;
extern GtkWidget *MAIN_WINDOW;



//extern ButtonBoard* BUTTON_BOARD;


Board *generate_board(int n);
void free_board(Board* board);
void print_board(Board* board);
bool place_men(Board* board, ButtonBoard* button_board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2, int square_number, int field_number);
bool mill_achieved(Board* board, int current_square, int current_field);
bool remove_opponents_men(Board* board, ButtonBoard* button_board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2, int square_number, int field_number);
bool all_opponents_men_in_a_mill(Board* board, bool player_1_turn);
bool select_man_to_move(Board* board, ButtonBoard* button_board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2, int current_square_number, int current_field_number);
bool select_field_to_move_on(Board* board, ButtonBoard* button_board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2, int chosen_square_number, int chosen_field_number);
bool properly_selected_field_to_move_on(Board* board, bool players_1_turn, int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, int men_number_player_1, int men_number_player_2);
bool properly_selected_man_to_move(Board* board, bool players_1_turn, int square_number, int field_number, int men_number_player_1, int men_number_player_2);
bool any_move_possible(Board* board, bool players_1_turn, int men_number_player_1, int men_number_player_2);
bool game_over(Board* board, bool players_1_turn, int men_number_player_1, int men_number_player_2);
void show_winner(bool players_1_turn, bool loss_message_received, GtkWidget* parent_window);
void place_men_received(Board* board, ButtonBoard* button_board, bool players_1_turn, int square_number, int field_number, int *men_number_player_1, int *men_number_player_2);
void remove_men_received(Board* board, ButtonBoard* button_board, bool players_1_turn, int square_number, int field_number, int *men_number_player_1, int *men_number_player_2);
void move_men_received(Board* board, ButtonBoard* button_board, bool players_1_turn, int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number);



#endif