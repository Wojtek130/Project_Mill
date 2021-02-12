#include "gui.h"
#define NUMBER_OF_FIELDS 8

int CURRENT_MOVE[2];
GtkWidget* CURRENT_BUTTON;
bool YOUR_TURN;
bool P_1_TURN;
bool REMOVING = false;
int TOTALLY_PLACED_MEN_PLAYER_1 = 0;
int TOTALLY_PLACED_MEN_PLAYER_2 = 0;
enum stage_of_moving CURRENT_STAGE_OF_MOVING = select_your_man;
ButtonBoard* BUTTON_BOARD; 
Board *BOARD; 
int MEN_NUMBER_P_1;
int MEN_NUMBER_P_2;
int SQUARE_NUMBER_TO_MOVE_FROM;
int FIELD_NUMBER_TO_MOVE_FROM;

void close_window(GtkWidget *widget, Board* board)
{
  //closePipes(potoki);
  free_board(board);
  gtk_main_quit();
  exit(0);
}

void change_label_value(GtkWidget *label_m)
{
    gtk_label_set_text(GTK_LABEL(label_m), "555");
}

void enable_css(char* css_file)
{
    GtkCssProvider *provider = gtk_css_provider_new();
    GdkDisplay *display = gdk_display_get_default();
    GdkScreen *screen = gdk_display_get_default_screen(display);
    gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    GError *error = 0;
    gtk_css_provider_load_from_file(provider, g_file_new_for_path(css_file), &error);
    g_object_unref (provider);
}

GtkWidget *generate_single_button(ButtonBoard* button_board, int coor_x, int coor_y, GtkWidget* box_to_put_in, int square_number, int field_number)
{
    GtkWidget *button = gtk_button_new();
    gtk_widget_set_name(button, "black-background");
    gtk_widget_set_size_request(button, 70, 70);
    gtk_style_context_add_class(gtk_widget_get_style_context(GTK_WIDGET(button)),"circular");
    gtk_fixed_put(GTK_FIXED(box_to_put_in), button, coor_x, coor_y);
    if (button_board->number_of_squares == 2)
    {
      square_number--;
    }
    int arr_button[] = {square_number, field_number};
    button_board->data[square_number][field_number] = button;
    return button;
}

void button_callback(GtkWidget *widget, gpointer data)
{
    int *move_array = (int*) data;
    int square_number = move_array[0];
    int field_number = move_array[1];
    CURRENT_BUTTON = widget;
    int *totally_placed_men_current_player = (P_1_TURN) ? (&TOTALLY_PLACED_MEN_PLAYER_1) : (&TOTALLY_PLACED_MEN_PLAYER_2);
    if (YOUR_TURN == false)
    {
        return;
    }
    if (REMOVING)
    {
        if (remove_opponents_men(BOARD, BUTTON_BOARD, P_1_TURN, &MEN_NUMBER_P_1, &MEN_NUMBER_P_2, square_number, field_number))
        {
            REMOVING = false;
            P_1_TURN = !P_1_TURN;
            YOUR_TURN = !YOUR_TURN;
        }
    }
    else if ((*totally_placed_men_current_player) < 9)
    {
        if (place_men(BOARD, BUTTON_BOARD, P_1_TURN, &MEN_NUMBER_P_1, &MEN_NUMBER_P_2, square_number, field_number))
        {
            (*totally_placed_men_current_player)++;
            if (mill_achieved(BOARD, square_number, field_number))
            {
                REMOVING = true;
            }
            else
            {
                REMOVING = false;
                P_1_TURN = !P_1_TURN;
                YOUR_TURN = !YOUR_TURN;
            }
        }
    }
    else
    {
        if (CURRENT_STAGE_OF_MOVING == select_your_man)
        {
            if (select_man_to_move(BOARD, BUTTON_BOARD, P_1_TURN, &MEN_NUMBER_P_1, &MEN_NUMBER_P_2, square_number, field_number))
            {
                CURRENT_STAGE_OF_MOVING = select_free_field_to_move_on;
                SQUARE_NUMBER_TO_MOVE_FROM = square_number;
                FIELD_NUMBER_TO_MOVE_FROM = field_number;
            }
        }
        else if (CURRENT_STAGE_OF_MOVING == select_free_field_to_move_on)
        {
            if (select_field_to_move_on(BOARD, BUTTON_BOARD, P_1_TURN, &MEN_NUMBER_P_1, &MEN_NUMBER_P_2, square_number, field_number))
            {
                CURRENT_STAGE_OF_MOVING = select_your_man;
                if (mill_achieved(BOARD, square_number, field_number))
                {
                    REMOVING = true;
                }
                else
                {
                    REMOVING = false;
                    P_1_TURN = !P_1_TURN;
                    YOUR_TURN = !YOUR_TURN;
                }
            }
        }    
    }
}

ButtonBoard* generate_button_board(int n)
{
    //int counter = 0;
    ButtonBoard* button_board = malloc(sizeof(ButtonBoard));
    button_board->number_of_squares = n;
    button_board->data = malloc(sizeof(GtkWidget**)*n);
    for (int k = 0; k < n; k++)
    {
        button_board->data[k] = malloc(sizeof(GtkWidget*)*NUMBER_OF_FIELDS);   
    }
    return button_board;
}

void free_button_board(ButtonBoard* button_board)
{
    for (int k = 0; k < button_board->number_of_squares; k++)
    {
        free(button_board->data[k]);  
    }
    free(button_board->data);
    free(button_board);
}

void disable_all_your_buttons(ButtonBoard* button_board)
{
  for (int sqr = 0; sqr < button_board->number_of_squares; sqr++)
  {
    for (int fie = 0; fie < NUMBER_OF_FIELDS; fie++)
    {
      gtk_widget_set_sensitive (button_board->data[sqr][fie], FALSE);
    }
  }
}

void enable_all_your_buttons(ButtonBoard* button_board)
{
  for (int sqr = 0; sqr < button_board->number_of_squares; sqr++)
  {
    for (int fie = 0; fie < NUMBER_OF_FIELDS; fie++)
    {
      gtk_widget_set_sensitive (button_board->data[sqr][fie], TRUE);
    }
  }
}