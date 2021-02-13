#include "data_sending.h"

int TOTALLY_PLACED_MEN_PLAYER_1;
int TOTALLY_PLACED_MEN_PLAYER_2;
int MEN_NUMBER_P_1;
int MEN_NUMBER_P_2;

void send_move_information(int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, bool remove)
{
    long move_information_int = value_to_send(current_square_number, current_field_number, chosen_square_number, chosen_field_number, remove);
    char move_information[MAX_TEXT_LENGHT];
    char* move_information_char = long_int_to_char(move_information_int);
    strcpy(move_information, move_information_char);
    free(move_information_char);
    sendStringToPipe(potoki, move_information);
}

gboolean receive_move_information(gpointer data)
{
  if (YOUR_TURN == true)
  {
      return TRUE;
  }
  gchar wejscie[MAX_TEXT_LENGHT];
  if (getStringFromPipe(potoki,wejscie,MAX_TEXT_LENGHT)) 
  {
    char move_information[MAX_TEXT_LENGHT];
    strcpy(move_information, wejscie);
    long* move_information_arr = received_value(move_information);
    int *totally_placed_men_current_player = (P_1_TURN) ? (&TOTALLY_PLACED_MEN_PLAYER_1) : (&TOTALLY_PLACED_MEN_PLAYER_2);
    int sqr_number_pla = move_information_arr[0];
    int fie_number_pla = move_information_arr[1];
    int chosen_sqr_number_pla = move_information_arr[2];
    int chosen_fie_number_pla = move_information_arr[3];
    bool remove_rec = move_information_arr[4];
    printf("RECEIVED VALUE: sqr : %d, fie: %d, ch_sqr: %d, ch_fie : %d, remove : %d\n", sqr_number_pla, fie_number_pla, chosen_sqr_number_pla, chosen_fie_number_pla, remove_rec);
    free(move_information_arr);
    int maximal_number_of_men = (BUTTON_BOARD->number_of_squares == 3) ? (5) : (6);
    if (remove_rec)
    {
        printf("remove\n");
        remove_men_received(BOARD, BUTTON_BOARD, P_1_TURN, sqr_number_pla, fie_number_pla, &MEN_NUMBER_P_1, &MEN_NUMBER_P_2);
        remove_rec = false;
        P_1_TURN = !P_1_TURN;
        YOUR_TURN = !YOUR_TURN;
        //enable_all_your_buttons(BUTTON_BOARD);
    }
    else if ((*totally_placed_men_current_player) < maximal_number_of_men)
    {
        
        place_men_received(BOARD, BUTTON_BOARD, P_1_TURN, sqr_number_pla, fie_number_pla, &MEN_NUMBER_P_1, &MEN_NUMBER_P_2);
        (*totally_placed_men_current_player)++;
        if (mill_achieved(BOARD, sqr_number_pla, fie_number_pla))
        {
            remove_rec = true;
        }
        else
        {
            remove_rec = false;
            P_1_TURN = !P_1_TURN;
            YOUR_TURN = !YOUR_TURN;
            //enable_all_your_buttons(BUTTON_BOARD);   
        }
    }
    else
    {
        move_men_received(BOARD, BUTTON_BOARD, P_1_TURN, sqr_number_pla, fie_number_pla, chosen_sqr_number_pla, chosen_fie_number_pla);
        if (mill_achieved(BOARD, chosen_sqr_number_pla, chosen_fie_number_pla))
        {
            remove_rec = true;
        }
        else
        {
            remove_rec = false;
            P_1_TURN = !P_1_TURN;
            YOUR_TURN = !YOUR_TURN;
            //enable_all_your_buttons(BUTTON_BOARD);
        }   
    }
    }
  return TRUE;
}

int compute_value_to_send(int position_number, int characterstic_value)
{
    if (position_number == -1)
    {
        return 1;
    }
    return pow(characterstic_value, position_number+1);
}

long value_to_send(int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, bool remove)
{
    long result = 1;
    result *= compute_value_to_send(current_square_number, 2); 
    result *= compute_value_to_send(current_field_number, 3);
    result *= compute_value_to_send(chosen_square_number, 5); 
    result *= compute_value_to_send(chosen_field_number, 7);
    if (remove)
    {
        result *= -1;
    }
        printf("VALUE TO SEND: sqr : %d, fie: %d, ch_sqr: %d, ch_fie : %d, remove : %d\n", current_square_number, current_field_number, chosen_square_number, chosen_field_number, remove);
    //printf("res com: %ld\n", result);
    return result;
}

char* long_int_to_char(long value)
{
    char *value_string = malloc(11*sizeof(char));
    sprintf(value_string, "%ld", value);
    return value_string;
}


long* received_value(char* value_char)
{
    long value_int = atol(value_char);
    long* move_information_int = malloc(5*sizeof(long));
    move_information_int[0] = compute_received_value(2, value_int);
    move_information_int[1] = compute_received_value(3, value_int);
    move_information_int[2] = compute_received_value(5, value_int);
    move_information_int[3] = compute_received_value(7, value_int);
    if (value_int < 0)
    {
        move_information_int[4] = 1;
    }
    else
    {
        move_information_int[4] = 0;
    }
    //printf("RECEIVED VALUE: sqr : %ld, fie: %ld, ch_sqr: %ld, ch_fie : %ld, remove : %ld\n", move_information_int[0], move_information_int[1], move_information_int[2], move_information_int[3], move_information_int[4]);
    return move_information_int;
}

long compute_received_value(int position_number, long received_value)
{
    int result = -1;
    //printf("rec_com_v : %ld\n", received_value);
    while (received_value % position_number == 0)
    {
        received_value = received_value / position_number;
        result++;
    }
    return result;
}