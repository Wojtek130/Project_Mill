#include "data_sending.h"

void send_move_information(int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, bool remove)
{
    long move_information_int = value_to_send(current_square_number, current_field_number, chosen_square_number, chosen_field_number, remove);
    char move_information[MAX_TEXT_LENGHT];
    char* move_information_char = long_int_to_char(move_information_int);
    strcpy(move_information, move_information_char);
    free(move_information_char);
    sendStringToPipe(potoki, move_information);
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