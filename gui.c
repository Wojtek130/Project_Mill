#include "gui.h"
#define NUMBER_OF_FIELDS 8
/*
typedef struct CallbackArguments
{
    int len;
    int *a_num;
    GtkWidget **a_label;    
} CallbackArguments;
typedef struct CallbackArguments CallbackArguments;*/
int CURRENT_MOVE[2];
GtkWidget* CURRENT_BUTTON;

void *run_gtk_loop()
{
  gtk_widget_show_all(MAIN_WINDOW);
  gtk_main();
  return NULL;
}

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
  CURRENT_MOVE[0] = move_array[0];
  CURRENT_MOVE[1] = move_array[1];
  CURRENT_BUTTON = widget; 
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