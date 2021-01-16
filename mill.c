#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mill.h"
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
//board[][8]
{
    /*int counter = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            printf("%d ", board[i][j]);
            counter++;
        }
    }*/
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

void place_men(Board* board, bool players_1_turn)
{
    int square_number, field_number;
    bool not_successfully_placed = true;
    while (not_successfully_placed)
    {
        printf("Enter number of the square and number of the field: ");
        scanf("%d %d", &square_number, &field_number);
        printf("\n");
        if (board->data[square_number][field_number] == 0)
        {
            if (players_1_turn)
            {
                board->data[square_number][field_number] = 1;
            }
            else
            {
                board->data[square_number][field_number] = 2;
            }
            not_successfully_placed = false;
            if (mill_achieved(board, square_number, field_number))
            {
                printf("MILL!!!\n");
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
        if ((board->data[current_square][current_field] ==  board->data[current_square][(current_field + 1) % 8]) 
        && (board->data[current_square][(current_field + 1) % 8] == board->data[current_square][(current_field + 2) % 8])
        && (board->data[current_square][current_field + 1] != 0))
        {
            return true;
        }
        if ((board->data[current_square][current_field] ==  board->data[current_square][(current_field + 8 - 1) % 8]) 
        && (board->data[current_square][(current_field + 8 - 1) % 8] == board->data[current_square][(current_field + 8) - 2 % 8])
        && (board->data[current_square][(current_field + 8 - 1) % 8] != 0))
        {
            return true;
        }
    }
    return false;
}
