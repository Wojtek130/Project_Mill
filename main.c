
#include "mill.h"
// Wojciech Sniady, nr indeksu: 322993

int main()
{
    int n = 3;
    int m = 2;
    int **board_3 = generate_board(n);
    int **board_2 = generate_board(m);
    print_board(n, board_3);
    printf("\n");
    print_board(m, board_2);
    return 0;
}