#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "mill.h"

// Wojciech Sniady, nr indeksu: 322993

int **generate_board(int n)
{
    int counter = 0;
    int **board;
    board = malloc(sizeof(int*)*n);
    
    for (int k = 0; k < n; k++)
    {
        board[k] = malloc(sizeof(int*)*8);   
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            board[i][j] = counter%10;
            counter++;
        }
    }
    return board;
}

void print_board(int n, int **board)
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
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < 3*i; k++)
        {
            printf(" ");
        }
        printf("%d", board[i][0]);
        for (int j = 3*(n - i); j >= 1; j--)
        {
            printf(" ");
        }
        printf("%d", board[i][1]);
        for (int j = 3*(n - i); j >= 1; j--)
        {
            printf(" ");
        }
        printf("%d", board[i][2]);
        printf("\n");
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", board[i][7]);
    }
    printf("    ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", board[i][3]);
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        for (int k = 3*(n/2-i+1); k > 0; k--)
        {
            printf(" ");
        }
        printf("%d", board[i][6]);
        for (int j = 3*(-i-1); j < 0; j++)
        {
            printf(" ");
        }
        printf("%d", board[i][5]);
        for (int j = 3*(-i-1); j < 0; j++)
        {
            printf(" ");
        }
        printf("%d", board[i][4]);

        printf("\n");
    }
}
