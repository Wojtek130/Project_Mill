
#include "mill.h"
#include "fifo.h"
#include "data_sending.h"
// Wojciech Sniady, nr indeksu: 322993


//static char *moj_id, *twoj_id;
PipesPtr potoki;
gchar wejscie[MAX_TEXT_LENGHT];
bool your_turn;


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
    int n = 3;
    Board *board_3 = generate_board(n); 
    print_board(board_3);
    printf("\n");
    int men_number_p_1 = 0;
    int men_number_p_2 = 0;
    bool p_1_turn = true;
    bool received_no_message = true;
    bool waiting_for_remove_message = false;
    bool game_goes_on = true;
    bool loss_message_received = false;
    char move_information[MAX_TEXT_LENGHT];
    int x = 2; 
    for (int i = 0; i < 3*x; i++)
    {
        if (your_turn)
        {
            place_men(board_3, p_1_turn, &men_number_p_1, &men_number_p_2);
            print_board(board_3);
        }
        else
        {
            while (received_no_message)
            {
                if (getStringFromPipe(potoki,wejscie,MAX_TEXT_LENGHT))
                {
                    strcpy(move_information, wejscie);
                    //printf("rec : %s\n", move_information);
                    long* move_information_arr = received_value(move_information);
                    int sqr_number_pla = move_information_arr[0];
                    int fie_number_pla = move_information_arr[1];
                    if (waiting_for_remove_message == false)
                    {
                        place_men_received(board_3, p_1_turn, sqr_number_pla, fie_number_pla, &men_number_p_1, &men_number_p_2);
                        print_board(board_3);
                        int remove_man = move_information_arr[4];
                        if (remove_man)
                        {
                            waiting_for_remove_message = true;
                        }
                        else
                        {
                            received_no_message = false;
                        }
                    }
                    else
                    {
                        remove_men_received(board_3, p_1_turn, sqr_number_pla, fie_number_pla, &men_number_p_1, &men_number_p_2);
                        print_board(board_3);
                        waiting_for_remove_message = true;
                        received_no_message = false;
                    }
                    free(move_information_arr);
                }
            sleep(0.1);
            }
        }
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
        waiting_for_remove_message = false;
        received_no_message = true;
        your_turn = !your_turn;
        p_1_turn = !p_1_turn;
    }
    received_no_message = true;
    while (game_goes_on)
    {
        if (your_turn)
        {
            move_men(board_3, p_1_turn, &men_number_p_1, &men_number_p_2);
            print_board(board_3);
            if (game_over(board_3, p_1_turn, men_number_p_1, men_number_p_2) == true)
            {
                break;
            }
        }
        else
        {
            while (received_no_message)
            {
                if (getStringFromPipe(potoki,wejscie,MAX_TEXT_LENGHT))
                {   
                    strcpy(move_information, wejscie);
                    long* move_information_arr = received_value(move_information);
                    int sqr_number_pla = move_information_arr[0];
                    int fie_number_pla = move_information_arr[1];
                    int chosen_sqr_number_pla = move_information_arr[2];
                    int chosen_fie_number_pla = move_information_arr[3];
                    if (waiting_for_remove_message == false)
                    {
                        move_men_received(board_3, p_1_turn, sqr_number_pla, fie_number_pla, chosen_sqr_number_pla, chosen_fie_number_pla);
                        print_board(board_3);
                        int remove_man = move_information_arr[4];
                        if (remove_man)
                        {
                            waiting_for_remove_message = true;
                        }
                        else
                        {
                            received_no_message = false;
                        }
                    }
                    else
                    {
                        remove_men_received(board_3, p_1_turn, sqr_number_pla, fie_number_pla, &men_number_p_1, &men_number_p_2);
                        print_board(board_3);
                        waiting_for_remove_message = true;
                        received_no_message = false;
                    }
                    free(move_information_arr);
                    if (game_over(board_3, p_1_turn, men_number_p_1, men_number_p_2) == true)
                    {
                        game_goes_on = false;
                        loss_message_received = true;
                        break;
                    }
                }
                sleep(0.1);
            }
        }
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
        waiting_for_remove_message = false;
        received_no_message = true;
        your_turn = !your_turn;
        p_1_turn = !p_1_turn;
    }
    show_winner(p_1_turn, loss_message_received);
    closePipes(potoki);
    //free_board(board_2);
    free_board(board_3);
    return 0;
}