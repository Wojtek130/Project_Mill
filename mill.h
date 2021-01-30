#ifndef MILL_H
#define MILL_H
#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h> 
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
extern GtkWidget* MAIN_WINDOW;
extern GtkWidget* main_label;
extern int CURRENT_MOVE[2];
extern GtkWidget* CURRENT_BUTTON;
//extern ButtonBoard* BUTTON_BOARD;


Board *generate_board(int n);
void free_board(Board* board);
void print_board(Board* board);
void place_men(Board* board, ButtonBoard* button_board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2);
bool mill_achieved(Board* board, int current_square, int current_field);
void remove_opponents_men(Board* board, ButtonBoard* button_board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2);
bool all_opponents_men_in_a_mill(Board* board, bool player_1_turn);
void move_men(Board* board, ButtonBoard* button_board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2);
bool properly_selected_field_to_move_on(Board* board, bool players_1_turn, int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, int men_number_player_1, int men_number_player_2);
bool properly_selected_man_to_move(Board* board, bool players_1_turn, int square_number, int field_number, int men_number_player_1, int men_number_player_2);
bool any_move_possible(Board* board, bool players_1_turn, int men_number_player_1, int men_number_player_2);
bool game_over(Board* board, bool players_1_turn, int men_number_player_1, int men_number_player_2);
void show_winner(bool players_1_turn, bool loss_message_received);
//char* long_int_to_char(long value);
long value_to_send(int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, bool remove);
//long* received_value(char* value_char);
//long compute_received_value(int position_number, long received_value);
void place_men_received(Board* board, ButtonBoard* button_board, bool players_1_turn, int square_number, int field_number, int *men_number_player_1, int *men_number_player_2);
void remove_men_received(Board* board, ButtonBoard* button_board, bool players_1_turn, int square_number, int field_number, int *men_number_player_1, int *men_number_player_2);
void move_men_received(Board* board, ButtonBoard* button_board, bool players_1_turn, int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number);
//void send_move_information(int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, bool remove);



#endif