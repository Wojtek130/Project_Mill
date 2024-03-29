#ifndef DATA_SENDING_H
#define DATA_SENDING_H
#include <math.h>
#include "gui.h"

// Wojciech Sniady, nr indeksu: 322993

void send_move_information(int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, bool remove);
gboolean receive_move_information(gpointer data);
long value_to_send(int current_square_number, int current_field_number, int chosen_square_number, int chosen_field_number, bool remove);
int compute_value_to_send(int position_number, int characterstic_value);
long compute_received_value(int position_number, long received_value);
long* received_value(char* value_char);
char* long_int_to_char(long value);

#endif