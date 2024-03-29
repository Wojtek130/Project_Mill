#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h> 
#include "mill.h"
#include "fifo.h"
#include "data_sending.h"
#define NUMBER_OF_FIELDS 8

// Wojciech Sniady, nr indeksu: 322993

GtkWidget *MEN_NUMBER_P_1_LABEL;
GtkWidget *MEN_NUMBER_P_2_LABEL;
bool REMOVING;

Board* generate_board(int n)
{
    //int counter = 0;
    Board* board = malloc(sizeof(Board));
    board->number_of_squares = n;
    board->data = malloc(sizeof(int*)*n);
    
    for (int k = 0; k < n; k++)
    {
        board->data[k] = malloc(sizeof(int)*NUMBER_OF_FIELDS);   
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < NUMBER_OF_FIELDS; j++)
        {
            board->data[i][j] = 0;
        }
    }
    return board;
}

void print_board(Board* board)
{
    int n = board->number_of_squares;
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < 3*i; k++)
        {
            printf(" ");
        }
        printf("%d", board->data[n-i-1][0]);
        for (int j = 3*(n - i); j >= 1; j--)
        {
            printf(" ");
        }
        printf("%d", board->data[n-i-1][1]);
        for (int j = 3*(n - i); j >= 1; j--)
        {
            printf(" ");
        }
        printf("%d", board->data[n-i-1][2]);
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d  ", board->data[n-i-1][7]);
    }
    printf("     ");
    for (int i = 0; i < n; i++)
    {
        printf("%d  ", board->data[i][3]);
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < 3*(n-i-1); k++)
        {
            printf(" ");
        }
        printf("%d", board->data[i][6]);
        for (int j = 3*(-i-1); j < 0; j++)
        {
            printf(" ");
        }
        printf("%d", board->data[i][5]);
        for (int j = 3*(-i-1); j < 0; j++)
        {
            printf(" ");
        }
        printf("%d", board->data[i][4]);

        printf("\n");
    }
}

void free_board(Board* board)
{
    for (int k = 0; k < board->number_of_squares; k++)
    {
        free(board->data[k]);  
    }
    free(board->data);
    free(board);
}

bool place_men(Board* board, ButtonBoard* button_board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2, int square_number, int field_number)
{
                            
    /*if (players_1_turn)
    {
        printf("Player's 1 turn! Choose a free field to place your man\n");
    }
    else
    {
        printf("Player's 2 turn! Choose a free field to place your man\n");
    }*/
    if (board->data[square_number][field_number] == 0)
    {
        if (players_1_turn)
        {
            board->data[square_number][field_number] = 1;
            gtk_widget_set_name(CURRENT_BUTTON, "blue-background");
            (*men_number_player_1)++;
            update_label_number_of_men(true, *men_number_player_1, MEN_NUMBER_P_1_LABEL);
            return true;
        }
        else
        {
            board->data[square_number][field_number] = 2;
            gtk_widget_set_name(CURRENT_BUTTON, "red-background");
            (*men_number_player_2)++;
            update_label_number_of_men(false, *men_number_player_2, MEN_NUMBER_P_2_LABEL);
            return true;
        }
    }
    //printf("wrong field selected, try again\n"); 
    return false;
}


bool mill_achieved(Board* board, int current_square, int current_field)
{
    if (current_field % 2 == 0)
    {
        if ((board->data[current_square][current_field] ==  board->data[current_square][(current_field + 1) % NUMBER_OF_FIELDS]) 
        && (board->data[current_square][(current_field + 1) % NUMBER_OF_FIELDS] == board->data[current_square][(current_field + 2) %  NUMBER_OF_FIELDS])
        && (board->data[current_square][current_field + 1] != 0))
        {
            return true;
        }
        if ((board->data[current_square][current_field] ==  board->data[current_square][(current_field +  NUMBER_OF_FIELDS - 1) %  NUMBER_OF_FIELDS]) 
        && (board->data[current_square][(current_field +  NUMBER_OF_FIELDS - 1) %  NUMBER_OF_FIELDS] == board->data[current_square][(current_field +  NUMBER_OF_FIELDS - 2) %  NUMBER_OF_FIELDS])
        && (board->data[current_square][(current_field +  NUMBER_OF_FIELDS - 1) %  NUMBER_OF_FIELDS] != 0))
        {
            return true;
        }
    }
    else
    {
        if ((board->data[current_square][current_field] ==  board->data[current_square][(current_field + NUMBER_OF_FIELDS - 1) % NUMBER_OF_FIELDS]) 
        && (board->data[current_square][(current_field + NUMBER_OF_FIELDS - 1) % NUMBER_OF_FIELDS] == board->data[current_square][(current_field + 1) % NUMBER_OF_FIELDS])
        && (board->data[current_square][(current_field + NUMBER_OF_FIELDS - 1) % NUMBER_OF_FIELDS] != 0))
        {
            return true;
        }
    }
    if (current_field % 2 == 1 && board->number_of_squares == 3)
    {
        if ((board->data[0][current_field] ==  board->data[1][current_field]) 
        && (board->data[0][current_field] == board->data[2][current_field])
        && (board->data[current_square][current_field] != 0))
        {
            return true;
        }
    }
    return false;
}

bool remove_opponents_men(Board* board, ButtonBoard* button_board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2, int square_number, int field_number)
{
    //printf("Choose an opponents man that you want to remove\n");
    if (board->data[square_number][field_number] == 0)
    {
        //printf("There is no men on this field selected, select again\n");
        return false;
    }
    else if (board->data[square_number][field_number] == 1)
    {
        if (players_1_turn)
        {
            //printf("You cannot remove your man, select a man of the opponent\n");
            return false;
        }
        else
        {
            if (all_opponents_men_in_a_mill(board, players_1_turn))
            {
                board->data[square_number][field_number] = 0;
                gtk_widget_set_name(button_board->data[square_number][field_number], "black-background");
                (*men_number_player_1)--;
                update_label_number_of_men(true, *men_number_player_1, MEN_NUMBER_P_1_LABEL);
                return true;
            }
            else
            {
                if (mill_achieved(board, square_number, field_number))
                {
                    //printf("This man is in the mill and you cannot remove it, select again\n");
                    return false;
                }
                else
                {
                    board->data[square_number][field_number] = 0;
                    gtk_widget_set_name(button_board->data[square_number][field_number], "black-background");
                    (*men_number_player_1)--;
                    update_label_number_of_men(true, *men_number_player_1, MEN_NUMBER_P_1_LABEL);
                    return true;
                }  
            } 
        }     
    }
    else
    {
        if (players_1_turn == false)
        {
            //printf("You cannot remove your man, select a man of the opponent\n");
            return false;
        }
        else
        {
            if (all_opponents_men_in_a_mill(board, players_1_turn))
            {
                board->data[square_number][field_number] = 0;
                gtk_widget_set_name(button_board->data[square_number][field_number], "black-background");
                (*men_number_player_2)--;
                update_label_number_of_men(false, *men_number_player_2, MEN_NUMBER_P_2_LABEL);
                return true;
            }
            else
            {
                if (mill_achieved(board, square_number, field_number))
                {
                    //printf("This man is in the mill and you cannot remove it, select again\n");
                    return false;
                }
                else
                {
                    board->data[square_number][field_number] = 0;
                    gtk_widget_set_name(button_board->data[square_number][field_number], "black-background");
                    (*men_number_player_2)--;
                    update_label_number_of_men(false, *men_number_player_2, MEN_NUMBER_P_2_LABEL);
                    return true;
                }
            }
        }
    }     
    return false;
}

bool all_opponents_men_in_a_mill(Board* board, bool player_1_turn)
{
    for (int sqr = 0; sqr < board->number_of_squares; sqr++)
    {
        for (int field = 0; field < NUMBER_OF_FIELDS; field++)
        {
            
            if (player_1_turn && board->data[sqr][field] == 2)
            {
                if (mill_achieved(board, sqr, field) == false)
                {
                    return false;
                }
            }
            else if (player_1_turn == false && board->data[sqr][field] == 1)
            {
                
                if (mill_achieved(board, sqr, field) == false)
                    {
                        return false;
                    }
            }
        }
    }
    return true;
}

bool select_man_to_move(Board* board, ButtonBoard* button_board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2, int current_square_number, int current_field_number)
{   
    /*if (players_1_turn)
    {
        printf("Player's 1 turn! Choose your man that you want to move\n");
    }
    else
    {
        printf("Player's 2 turn! Choose your man that you want to move\n");
    }*/
    if (properly_selected_man_to_move(board, players_1_turn, current_square_number, current_field_number, *men_number_player_1, *men_number_player_2) == false)
    {
        return false;
    }
    return true;
}

bool select_field_to_move_on(Board* board, ButtonBoard* button_board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2, int chosen_square_number, int chosen_field_number)
{
    /*if (players_1_turn)
    {
        printf("Move! Choose a field where you want to move your man\n");
    }
    else
    {
        printf("Move! Choose a field where you want to move your man\n");
    }*/
    if (properly_selected_field_to_move_on(board, players_1_turn, SQUARE_NUMBER_TO_MOVE_FROM, FIELD_NUMBER_TO_MOVE_FROM, chosen_square_number, chosen_field_number, *men_number_player_1, *men_number_player_2) == false)
    {
        return false;
    }
    board->data[SQUARE_NUMBER_TO_MOVE_FROM][FIELD_NUMBER_TO_MOVE_FROM] = 0;
    gtk_widget_set_name(button_board->data[SQUARE_NUMBER_TO_MOVE_FROM][FIELD_NUMBER_TO_MOVE_FROM], "black-background");
    if (players_1_turn)
    {
        board->data[chosen_square_number][chosen_field_number] = 1;
        gtk_widget_set_name(button_board->data[chosen_square_number][chosen_field_number], "blue-background");
    }
    else
    {
        board->data[chosen_square_number][chosen_field_number] = 2;
        gtk_widget_set_name(button_board->data[chosen_square_number][chosen_field_number], "red-background");

    }
    return true;
}

bool properly_selected_man_to_move(Board* board, bool players_1_turn, int square_number, int field_number, int men_number_player_1, int men_number_player_2)
{
    if (board->data[square_number][field_number] == 0)
    {
        //printf("There is no man on this field, select again\n");
        return false;
    }
    if (players_1_turn && board->data[square_number][field_number] == 2)
    {
        //printf("This is a man of Player 2, select again\n");
        return false;
    }
    if (players_1_turn == false && board->data[square_number][field_number] == 1)
    {
        //printf("This is a man of Player 1, select again\n");
        return false;
    }
    if (players_1_turn && men_number_player_1 == 3)
    {
        return true;
    }
    if (!players_1_turn && men_number_player_2 == 3)
    {
        return true;
    }
    if (board->data[square_number][(field_number + 1) % NUMBER_OF_FIELDS] == 0 || board->data[square_number][(field_number + - 1 + NUMBER_OF_FIELDS) % NUMBER_OF_FIELDS] == 0)
    {
        return true;
    }
    if ((square_number - 1 >= 0) && (field_number % 2 == 1))
    {
        if (board->data[square_number - 1][field_number] == 0)
        {
            return true;
        }
    }
    if ((square_number + 1 <= board->number_of_squares - 1) && (field_number % 2 == 1))
    {
        if (board->data[square_number + 1][field_number] == 0)
        {
            return true;
        }
    }
    //printf("All fields around this man are occupied, select again\n");
    return false;
}

bool properly_selected_field_to_move_on(Board* board, bool players_1_turn, int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, int men_number_player_1, int men_number_player_2)
{
    if (board->data[chosen_square_number][chosen_field_number] != 0)
    {
        //printf("This is a field is already occupied, select again\n");
        return false;
    }
    if (players_1_turn && men_number_player_1 == 3)
    {
        return true;
    }
    if (!players_1_turn && men_number_player_2 == 3)
    {
        return true;
    }
    if ((((abs(current_field_number - chosen_field_number) == 1 || abs(current_field_number - chosen_field_number) == 7) 
    && current_square_number == chosen_square_number) 
    || ((current_field_number % 2 == 1) && current_field_number == chosen_field_number && (abs(current_square_number - chosen_square_number) == 1))) == false) 
    {
        //printf("A man can be moved only by one step, select again\n");
        return false;
    }
    return true;
}

bool game_over(Board* board, bool players_1_turn, int men_number_player_1, int men_number_player_2)
{
    int *totally_placed_men_current_player = (P_1_TURN) ? (&TOTALLY_PLACED_MEN_PLAYER_1) : (&TOTALLY_PLACED_MEN_PLAYER_2);
    int maximal_number_of_men = (BUTTON_BOARD->number_of_squares == 3) ? (9) : (6);
    if (*totally_placed_men_current_player < maximal_number_of_men)
    {
        return false;
    }
    if (players_1_turn && men_number_player_2 <=2)
    {
        return true;
    }
    if (!players_1_turn && men_number_player_1 <=2)
    {
        return true;
    }
    if (any_move_possible(board, players_1_turn, men_number_player_1, men_number_player_2) == false)
    {
        return true;
    }
    return false;
}

bool any_move_possible(Board* board, bool players_1_turn, int men_number_player_1, int men_number_player_2)
{
    if (players_1_turn && men_number_player_2 == 3)
    {
        return true;
    }
    if (!players_1_turn && men_number_player_1 == 3)
    {
        return true;
    }
    int opponents_men;
    if (players_1_turn)
    {
        opponents_men = 2; 
    }
    else
    {
        opponents_men = 1;
    }
    for (int sqr = 0; sqr < board->number_of_squares; sqr++)
    {
        for (int field = 0; field < NUMBER_OF_FIELDS; field++)
        {
            if (board->data[sqr][field] != opponents_men)
            {
                continue;
            }
            if (board->data[sqr][(field + 1) % NUMBER_OF_FIELDS] == 0 || board->data[sqr][(field + - 1 + NUMBER_OF_FIELDS) % NUMBER_OF_FIELDS] == 0)
            {
                return true;
            }
            if ((sqr - 1 >= 0) && (field % 2 == 1))
            {
                if (board->data[sqr - 1][field] == 0)
                {
                    return true;
                }
            }
            if ((sqr + 1 <= board->number_of_squares - 1) && (field % 2 == 1))
            {
                if (board->data[sqr + 1][field] == 0)
                {
                    return true;
                }
            }
        }
    }
    //printf("No moves possible!\n");
    return false;
}

void show_winner(bool players_1_turn, bool loss_message_received, GtkWidget* parent_window)
{
    char game_over_message[30];
    if (players_1_turn && loss_message_received == false)
    {
        strcpy(game_over_message, "Player 1 won!");
    }
    else if (players_1_turn == false && loss_message_received == false)
    {
        strcpy(game_over_message, "Player 2 won!");
    }
    else if (players_1_turn)
    {
        strcpy(game_over_message, "Player 2 won!");
    }
    else
    {
        strcpy(game_over_message, "Player 1 won!");
    }
    GtkWidget *pop_up_window = gtk_message_dialog_new(GTK_WINDOW(parent_window), GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, "%s", game_over_message);
    gtk_window_set_title(GTK_WINDOW(pop_up_window), "GAME OVER!!!");
    GtkResponseType response = gtk_dialog_run(GTK_DIALOG(pop_up_window));
    gtk_widget_destroy(pop_up_window);
}

void place_men_received(Board* board, ButtonBoard* button_board, bool players_1_turn, int square_number, int field_number, int *men_number_player_1, int *men_number_player_2)
{
    if (players_1_turn)
    {
        board->data[square_number][field_number] = 1;
        (*men_number_player_1)++;
        update_label_number_of_men(true, *men_number_player_1, MEN_NUMBER_P_1_LABEL);
        gtk_widget_set_name(button_board->data[square_number][field_number], "blue-background");
    }
    else
    {
        board->data[square_number][field_number] = 2;
        (*men_number_player_2)++;
        update_label_number_of_men(false, *men_number_player_2, MEN_NUMBER_P_2_LABEL);
        gtk_widget_set_name(button_board->data[square_number][field_number], "red-background");
    }
}

void remove_men_received(Board* board, ButtonBoard* button_board, bool players_1_turn, int square_number, int field_number, int *men_number_player_1, int *men_number_player_2)
{
    board->data[square_number][field_number] = 0;
    gtk_widget_set_name(button_board->data[square_number][field_number], "black-background");
    if (players_1_turn)
    {
        (*men_number_player_2)--;
        update_label_number_of_men(false, *men_number_player_2, MEN_NUMBER_P_2_LABEL);   
    }
    else
    {
        (*men_number_player_1)--;
        update_label_number_of_men(true, *men_number_player_1, MEN_NUMBER_P_1_LABEL);
    }
}
void move_men_received(Board* board, ButtonBoard* button_board, bool players_1_turn, int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number)
{
    board->data[current_square_number][current_field_number] = 0;
    gtk_widget_set_name(button_board->data[current_square_number][current_field_number], "black-background");
    if (players_1_turn)
    {
        board->data[chosen_square_number][chosen_field_number] = 1;
        gtk_widget_set_name(button_board->data[chosen_square_number][chosen_field_number], "blue-background");
    }
    else
    {
        board->data[chosen_square_number][chosen_field_number] = 2;
        gtk_widget_set_name(button_board->data[chosen_square_number][chosen_field_number], "red-background");
    }
}

void reset_all_global_variables()
{
    for (int sqr = 0; sqr < BOARD->number_of_squares; sqr++)
    {
        for (int fie = 0; fie < NUMBER_OF_FIELDS; fie++)
        {
            BOARD->data[sqr][fie] = 0;
            gtk_widget_set_name(BUTTON_BOARD->data[sqr][fie], "black-background");
        }
    }
    MEN_NUMBER_P_1 = 0;
    MEN_NUMBER_P_2 = 0;
    update_label_number_of_men(true, MEN_NUMBER_P_1, MEN_NUMBER_P_1_LABEL);
    update_label_number_of_men(false, MEN_NUMBER_P_2, MEN_NUMBER_P_2_LABEL);
    TOTALLY_PLACED_MEN_PLAYER_1 = 0;
    TOTALLY_PLACED_MEN_PLAYER_2 = 0;
    CURRENT_BUTTON = NULL;
    CURRENT_STAGE_OF_MOVING = select_your_man;
    REMOVING = false;
    if (PLAYER_ID == 1)
    {
        YOUR_TURN = true;
        enable_all_your_buttons(BUTTON_BOARD);
    }
    else
    {
        YOUR_TURN = false;
        disable_all_your_buttons(BUTTON_BOARD);
    }
    P_1_TURN = TRUE;
    update_label_whose_turn(P_1_TURN, WHOSE_TURN_LABEL);
    return;
}

void new_game()
{
    reset_all_global_variables();
    send_move_information(13, -1, -1, -1, false);
}