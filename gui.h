#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "mill.h"

enum stage_of_moving {select_your_man = 0, select_free_field_to_move_on = 1};

void close_window(GtkWidget *widget, Board* board);
void change_label_value(GtkWidget *label_m);
void enable_css(char* css_file);
GtkWidget *generate_single_button(ButtonBoard* button_board, int coor_x, int coor_y, GtkWidget* box_to_put_in, int square_number, int field_number);
void button_callback(GtkWidget *widget, gpointer data);
ButtonBoard* generate_button_board(int n);
void free_button_board(ButtonBoard* button_board);
void disable_all_your_buttons(ButtonBoard* button_board);
void enable_all_your_buttons(ButtonBoard* button_board);
void show_winner_pop_up_window();
#endif