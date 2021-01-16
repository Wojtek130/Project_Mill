
#include "mill.h"

// Wojciech Sniady, nr indeksu: 322993

int main()
{
    int n = 3;
    //int m = 2;
    Board *board_3 = generate_board(n);
    //Board *board_2 = generate_board(m);
    print_board(board_3);
    //print_board(board_2);
    printf("\n");
    // //printf("\n");
    int men_number_p_1 = 0;
    int men_number_p_2 = 0;
    for (int i = 0; i < n*3; i++)
    {
        place_men(board_3, true, &men_number_p_1, &men_number_p_2);
        print_board(board_3);
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
        place_men(board_3, false, &men_number_p_1, &men_number_p_2);
        print_board(board_3);
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
    }
    // for (int i = 0; i < m*3; i++)
    // {
    //     place_men(board_2, true);
    //     print_board(board_2);
    //     place_men(board_2, false);
    //     print_board(board_2);
    // }
    //free_board(board_2);
    free_board(board_3);
    //free_board(board_7);

    return 0;
}