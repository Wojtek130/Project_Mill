
#include "mill.h"
// Wojciech Sniady, nr indeksu: 322993

int main()
{
    int n = 3;
    int m = 2;
    int **board_3 = generate_board(n);
    int **board_2 = generate_board(m);
    int **board_7 = generate_board(7);
    
    print_board(n, board_3);
    printf("\n");
    print_board(m, board_2);
    printf("\n");
    print_board(7, board_7);
    return 0;
}