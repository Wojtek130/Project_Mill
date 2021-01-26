#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h> 
#include "mill.h"
#include "fifo.h"
#define NUMBER_OF_FIELDS 8


// Wojciech Sniady, nr indeksu: 322993



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
            //counter++;
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
        //int w = 123 + i;
        //printf("%d", w);
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

void place_men(Board* board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2)
{
    int square_number, field_number;
    bool not_successfully_selected = true;
    while (not_successfully_selected)
    {
        if (players_1_turn)
        {
            printf("Player's 1 turn! Enter number of the square and number of the field: ");
        }
        else
        {
            printf("Player's 2 turn! Enter number of the square and number of the field: ");
        }
        scanf("%d %d", &square_number, &field_number);
        printf("\n");
        if (board->data[square_number][field_number] == 0)
        {
            if (players_1_turn)
            {
                board->data[square_number][field_number] = 1;
                (*men_number_player_1)++;
            }
            else
            {
                board->data[square_number][field_number] = 2;
                (*men_number_player_2)++;
            }
            not_successfully_selected = false;
            if (mill_achieved(board, square_number, field_number))
            {
                print_board(board);
                send_move_information(square_number, field_number, -1, -1, true);
                remove_opponents_men(board, players_1_turn, men_number_player_1, men_number_player_2);
            }
            else
            {
                send_move_information(square_number, field_number, -1, -1, false);
            }
            
        }
        else
        {
            printf("wrong field selected, try again\n");
        }     
    }
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

void remove_opponents_men(Board* board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2)
{
    int square_number, field_number;
    bool not_successfully_selected = true;
    while (not_successfully_selected)
    {
        printf("Enter number of the square and number of the opponents man that you want to remove: ");
        scanf("%d %d", &square_number, &field_number);
        printf("\n");
        if (board->data[square_number][field_number] == 0)
        {
            printf("There is no men on this field selected, select again\n");
        }
        else if (board->data[square_number][field_number] == 1)
        {
            if (players_1_turn)
            {
                printf("You cannot remove your man, select a man of the opponent\n");
            }
            else
            {
                if (all_opponents_men_in_a_mill(board, players_1_turn))
                {
                    board->data[square_number][field_number] = 0;
                    (*men_number_player_1)--;
                    not_successfully_selected = false;
                }
                else
                {
                    
                    if (mill_achieved(board, square_number, field_number))
                    {
                        printf("This man is in the mill and you cannot remove it, select another one\n");
                    }
                    else
                    {
                        board->data[square_number][field_number] = 0;
                        (*men_number_player_1)--;
                        not_successfully_selected = false;
                    }  
                } 
            }     
        }
        else
        {
            if (players_1_turn == false)
            {
                printf("You cannot remove your man, select a man of the opponent\n");
            }
            else
            {
                if (all_opponents_men_in_a_mill(board, players_1_turn))
                {
                    board->data[square_number][field_number] = 0;
                    (*men_number_player_2)--;
                    not_successfully_selected = false;
                }
                else
                {
                    if (mill_achieved(board, square_number, field_number))
                    {
                        printf("This man is in the mill and you cannot remove it, select another one\n");
                    }
                    else
                    {
                        
                        board->data[square_number][field_number] = 0;
                        (*men_number_player_2)--;
                        not_successfully_selected = false;
                    }
                    
                }
            }
        }     
    }
    send_move_information(square_number, field_number, -1, -1, false);
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

void move_men(Board* board, bool players_1_turn, int *men_number_player_1, int *men_number_player_2)
{
    int current_square_number, current_field_number, chosen_square_number, chosen_field_number;
    bool not_successfully_selected = true; 
    while (not_successfully_selected)
    {   
        if (players_1_turn)
        {
            printf("Player's 1 turn! Enter number of the square and number of the man that you want to move: ");
        }
        else
        {
            printf("Player's 2 turn! Enter number of the square and number of the man that you want to move: ");
        }
        scanf("%d %d", &current_square_number, &current_field_number);
        printf("\n");
        
        if (properly_selected_man_to_move(board, players_1_turn, current_square_number, current_field_number, *men_number_player_1, *men_number_player_2) == false)
        {
            continue;
        }
        if (players_1_turn)
        {
            printf("Move! Enter number of the square and number of the field where you want to move it: ");
        }
        else
        {
            printf("Move! Enter number of the square and number of the field where you want to move it: ");
        }
        scanf("%d %d", &chosen_square_number, &chosen_field_number);
        printf("\n");
        if (properly_selected_field_to_move_on(board, players_1_turn, current_square_number, current_field_number, chosen_square_number, chosen_field_number, *men_number_player_1, *men_number_player_2) == false)
        {
            continue;
        }
        not_successfully_selected = false;  
    }
    board->data[current_square_number][current_field_number] = 0;
    if (players_1_turn)
    {
        board->data[chosen_square_number][chosen_field_number] = 1;
    }
    else
    {
        board->data[chosen_square_number][chosen_field_number] = 2;
    }
    /*char* text_to_send = int_to_char(value_to_send(chosen_square_number, chosen_square_number, -1, -1, players_1_turn));
    sendStringToPipe(potoki, text_to_send);*/
    if (mill_achieved(board, chosen_square_number, chosen_field_number))
    {
        print_board(board);
        send_move_information(current_square_number, current_field_number, chosen_square_number, chosen_field_number, true);
        remove_opponents_men(board, players_1_turn, men_number_player_1, men_number_player_2);
    }  
    send_move_information(current_square_number, current_field_number, chosen_square_number, chosen_field_number, false);

}

bool properly_selected_man_to_move(Board* board, bool players_1_turn, int square_number, int field_number, int men_number_player_1, int men_number_player_2)
{
    if (board->data[square_number][field_number] == 0)
    {
        printf("There is no man on this field, select again\n");
        return false;
    }
    if (players_1_turn && board->data[square_number][field_number] == 2)
    {
        printf("This is a man of Player 2, select again\n");
        return false;
    }
    if (players_1_turn == false && board->data[square_number][field_number] == 1)
    {
        printf("This is a man of Player 1, select again\n");
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
    printf("All fields around this man are occupied, select again\n");
    return false;
}

bool properly_selected_field_to_move_on(Board* board, bool players_1_turn, int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, int men_number_player_1, int men_number_player_2)
{
    if (board->data[chosen_square_number][chosen_field_number] != 0)
    {
        printf("This is a field is already occupied, select again\n");
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
        printf("A man can be moved only by one step, select again\n");
        return false;
    }
    return true;
}

bool game_over(Board* board, bool players_1_turn, int men_number_player_1, int men_number_player_2)
{
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
    printf("No moves possible!\n");
    return false;
}

void show_winner(bool players_1_turn, bool loss_message_received)
{
    printf("GAME OVER!!!\n");
    if (players_1_turn && loss_message_received == false)
    {
        printf("Player 1 won!\n");
    }
    else if (players_1_turn == false && loss_message_received == false)
    {
        printf("Player 2 won!\n");
    }
    else if (players_1_turn)
    {
        printf("Player 2 won!\n");
    }
    else
    {
        printf("Player 1 won!\n");
    }
    
    
}

int compute_value_to_send(int position_number, int characterstic_value)
{
    if (position_number == -1)
    {
        return 1;
    }
    return pow(characterstic_value, position_number+1);
}

long value_to_send(int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, bool remove)
{
    long result = 1;
    if (current_square_number == 17)
    {
        printf("here 17!!!!!\n");
        result = 17 * 3 * 5 * 7;
        return result; 
    }
    else
    {
        result *= compute_value_to_send(current_square_number, 2); 
    }
    
    
    result *= compute_value_to_send(current_field_number, 3);
    result *= compute_value_to_send(chosen_square_number, 5); 
    result *= compute_value_to_send(chosen_field_number, 7);
    if (remove)
    {
        result *= -1;
    }
    //printf("res com: %ld\n", result);
    return result;
}

char* long_int_to_char(long value)
{
    char *value_string = malloc(11*sizeof(char));
    sprintf(value_string, "%ld", value);
    return value_string;
}

long* received_value(char* value_char)
{
    long value_int = atol(value_char);
    long* move_information_int = malloc(5*sizeof(long));
    if (value_int % 17 == 0)
    {
        move_information_int[0] = 17;
        move_information_int[1] = -1;
        move_information_int[2] = -1;
        move_information_int[3] = -1;
        move_information_int[4] = 0;
        move_information_int[5] = 0;
        return move_information_int;
    }
    move_information_int[0] = compute_received_value(2, value_int);
    move_information_int[1] = compute_received_value(3, value_int);
    move_information_int[2] = compute_received_value(5, value_int);
    move_information_int[3] = compute_received_value(7, value_int);
    if (value_int < 0)
    {
        move_information_int[4] = 1;
    }
    else
    {
        move_information_int[4] = 0;
    }
    /*for (int i = 0; i < 6; i++)
    {
        printf("mov_info[%d] : %ld\n", i, move_information_int[i]);
    }*/
    return move_information_int;
}

long compute_received_value(int position_number, long received_value)
{
    int result = -1;
    //printf("rec_com_v : %ld\n", received_value);
    while (received_value % position_number == 0)
    {
        received_value = received_value / position_number;
        result++;
    }
    return result;
}

void place_men_received(Board* board, bool players_1_turn, int square_number, int field_number, int *men_number_player_1, int *men_number_player_2)
{
    if (players_1_turn)
    {
        board->data[square_number][field_number] = 1;
        (*men_number_player_1)++;
    }
    else
    {
        board->data[square_number][field_number] = 2;
        (*men_number_player_2)++;
    }
}

void remove_men_received(Board* board, bool players_1_turn, int square_number, int field_number, int *men_number_player_1, int *men_number_player_2)
{
    board->data[square_number][field_number] = 0;
    if (players_1_turn)
    {
        (*men_number_player_2)--;   
    }
    else
    {
        (*men_number_player_1)--;
    }
}
void move_men_received(Board* board, bool players_1_turn, int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number)
{
    board->data[current_square_number][current_field_number] = 0;
    if (players_1_turn)
    {
        board->data[chosen_square_number][chosen_field_number] = 1;
    }
    else
    {
        board->data[chosen_square_number][chosen_field_number] = 2;
    }
}


void send_move_information(int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, bool remove)
{
    long move_information_int = value_to_send(current_square_number, current_field_number, chosen_square_number, chosen_field_number, remove);
    char move_information[MAX_TEXT_LENGHT];
    strcpy(move_information, (long_int_to_char(move_information_int)));
    sendStringToPipe(potoki, move_information);
}