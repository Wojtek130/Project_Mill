
#include "mill.h"

// Wojciech Sniady, nr indeksu: 322993

int main()
{
    int n = 3;
    int m = 2;
    //Board *board_3 = generate_board(n);
    Board *board_2 = generate_board(m);
    //Board *board_7 = generate_board(7);
    
    //print_board(board_3);
    print_board(board_2);
    printf("\n");
    //printf("\n");
    //print_board(board_7);
    // for (int i = 0; i < m*3; i++)
    // {
    //     place_men(board_3, true);
    //     print_board(board_3);
    //     place_men(board_3, false);
    //     print_board(board_3);
    // }
    for (int i = 0; i < n*3; i++)
    {
        place_men(board_2, true);
        print_board(board_2);
        place_men(board_2, false);
        print_board(board_2);
    }
    free_board(board_2);
    //free_board(board_3);
    //free_board(board_7);

    return 0;
}