#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mill.h"
#define NUMBER_OF_FIELDS 8


// Wojciech Sniady, nr indeksu: 322993

Board* generate_board(int n)
{
    int counter = 0;
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
            board->data[i][j] = counter%10;
            counter++;
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
        printf("%d", board->data[i][0]);
        for (int j = 3*(n - i); j >= 1; j--)
        {
            printf(" ");
        }
        printf("%d", board->data[i][1]);
        for (int j = 3*(n - i); j >= 1; j--)
        {
            printf(" ");
        }
        printf("%d", board->data[i][2]);
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d  ", board->data[i][7]);
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
