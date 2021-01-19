
#include "mill.h"

// Wojciech Sniady, nr indeksu: 322993

int main()
{
    int n = 3;
    //int m = 2;
    //Board *board_3 = generate_board(n);
    Board *board_test_3 = generate_board(n);
    board_test_3->data[0][0] = 1;
    board_test_3->data[0][1] = 1;
    board_test_3->data[0][3] = 1;
    board_test_3->data[0][4] = 2;
    board_test_3->data[0][6] = 2;
    board_test_3->data[0][7] = 2;
    board_test_3->data[1][0] = 1;
    board_test_3->data[1][1] = 1;
    board_test_3->data[1][3] = 1;
    board_test_3->data[1][4] = 2;
    board_test_3->data[1][6] = 2;
    board_test_3->data[1][7] = 2;
    //
    print_board(board_test_3);
    //Board *board_2 = generate_board(m);
    //print_board(board_3);
    //print_board(board_2);
    printf("\n");
    // //printf("\n");
    //int men_number_p_1 = 0;
    //int men_number_p_2 = 0;
    int men_number_p_1_test = 6;
    int men_number_p_2_test = 6;
    bool p_1_turn = true;
    /*
    for (int i = 0; i < n*3; i++)
    {
        place_men(board_3, p_1_turn, &men_number_p_1, &men_number_p_2);
        print_board(board_3);
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
        place_men(board_3, !p_1_turn, &men_number_p_1, &men_number_p_2);
        print_board(board_3);
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
    }
    while (1)
    {
        move_men(board_3, p_1_turn, &men_number_p_1, &men_number_p_2);
        print_board(board_3);
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
        move_men(board_3, !p_1_turn, &men_number_p_1, &men_number_p_2);
        print_board(board_3);
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
    }
    */
   while(1)
    {
        move_men(board_test_3, p_1_turn, &men_number_p_1_test, &men_number_p_2_test);
        print_board(board_test_3);
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1_test, men_number_p_2_test);
        p_1_turn = !p_1_turn;
    }

    // for (int i = 0; i < m*3; i++)
    // {
    //     place_men(board_2, true);
    //     print_board(board_2);
    //     place_men(board_2, false);
    //     print_board(board_2);
    // }
    //free_board(board_2);
    //free_board(board_3);
    free_board(board_test_3);
    //free_board(board_7);

    return 0;
}