
#include "mill.h"
#include "fifo.h"
#define MAX_TEXT_LENGHT 10
// Wojciech Sniady, nr indeksu: 322993


//static char *moj_id, *twoj_id;
PipesPtr potoki;
gchar wejscie[MAX_TEXT_LENGHT];
bool your_turn;

static void przekaz_tekst(gpointer arg_1)
{
    sendStringToPipe(potoki, arg_1);
}

static gboolean pobierz_tekst(gpointer data)
{
    getStringFromPipe(potoki,wejscie+strlen(wejscie),MAX_TEXT_LENGHT);
    printf("output : %s\n", wejscie);
    return TRUE;
}

int main(int argc,char *argv[])
{
    if ((potoki=initPipes(argc,argv)) == NULL)
        return 1;
    if (argc == 2 && strcmp(argv[1],"A") == 0) 
    { 
        your_turn = true;
    }
    else 
    { 
        your_turn = false;
    }
    /*if (strcmp(argv[1],"A") == 0)
    {
        przekaz_tekst((gpointer) "AAA");
    }
    else
    {
        przekaz_tekst((gpointer) "BBB");
    }
    int counter = 0;
    int a;
    while (counter < 10)
    {
        getStringFromPipe(potoki,wejscie+strlen(wejscie),MAX_TEXT_LENGHT);
        printf("input: ");
        scanf("%d", &a);
        counter++;
    }
    */
    //int m = 2;
    int n = 3;
    /*Board *board_test_3 = generate_board(n);
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
    board_test_3->data[1][7] = 2;*/

    //print_board(board_test_3);

    //Board *board_2 = generate_board(m);
    
    //print_board(board_2);
    
    // //printf("\n");
    //int men_number_p_1_test = 6;
    //int men_number_p_2_test = 6;
    
    Board *board_3 = generate_board(n); 
    print_board(board_3);
    printf("\n");
    int men_number_p_1 = 0;
    int men_number_p_2 = 0;
    bool p_1_turn = true;
    bool received_no_message = true;
    char move_information[MAX_TEXT_LENGHT];
    for (int i = 0; i < 2*n*3; i++)
    {
        if (your_turn)
        {
            place_men(board_3, p_1_turn, &men_number_p_1, &men_number_p_2);
            print_board(board_3);
            printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
        }
        else
        {
            while (received_no_message)
            {
                if (getStringFromPipe(potoki,wejscie,MAX_TEXT_LENGHT))
                {
                    strcpy(move_information, wejscie);
                    printf("rec : %s", move_information);
                    received_value(move_information);
                    received_no_message = false;
                }
            }
            received_no_message = true;
        }
        your_turn = !your_turn;
        p_1_turn = !p_1_turn;
        
    }
    while (1)
    {
        move_men(board_3, your_turn, &men_number_p_1, &men_number_p_2);
        print_board(board_3);
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
        if (game_over(board_3, p_1_turn, men_number_p_1, men_number_p_2) == true)
        {
            break;
        }
        p_1_turn = !p_1_turn;
    }
    show_winner(p_1_turn);

   /*
    for (int i = 0; i < m*3; i++)
    {
        place_men(board_2, p_1_turn, &men_number_p_1, &men_number_p_2);
        print_board(board_2);
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
        place_men(board_2, !p_1_turn, &men_number_p_1, &men_number_p_2);
        print_board(board_2);
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
    }
    while (1)
    {
        move_men(board_2, p_1_turn, &men_number_p_1, &men_number_p_2);
        print_board(board_2);
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
        if (game_over(board_2, p_1_turn, men_number_p_1, men_number_p_2) == true)
        {
            break;
        }
        p_1_turn = !p_1_turn;
    }
    show_winner(p_1_turn);
    */
/*
   while(1)
    {
        move_men(board_test_3, p_1_turn, &men_number_p_1_test, &men_number_p_2_test);
        print_board(board_test_3);
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1_test, men_number_p_2_test);
        if (game_over(board_test_3, p_1_turn, men_number_p_1_test, men_number_p_2_test) == true)
        {
            break;
        }
        p_1_turn = !p_1_turn;
    }
    show_winner(p_1_turn);
*/

    // for (int i = 0; i < m*3; i++)
    // {
    //     place_men(board_2, true);
    //     print_board(board_2);
    //     place_men(board_2, false);
    //     print_board(board_2);
    // }
    //g_timeout_add(100,pobierz_tekst,NULL);
    //free_board(board_2);
    //free_board(board_3);
    //free_board(board_test_3);
    //free_board(board_7);

    return 0;
}