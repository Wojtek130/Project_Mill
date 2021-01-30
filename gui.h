#ifndef GUI_H
#define GUI_H
#include <gtk/gtk.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "mill.h"



void close_window(GtkWidget *widget, Board* board);
void *run_gtk_loop();
//void change_label_value(GtkWidget *widget, gpointer data);
void change_label_value(GtkWidget *label_m);
void enable_css(char* css_file);
GtkWidget *generate_single_button(ButtonBoard* button_board, int coor_x, int coor_y, GtkWidget* box_to_put_in, int square_number, int field_number);
void button_callback(GtkWidget *widget, gpointer data);
ButtonBoard* generate_button_board(int n);
void free_button_board(ButtonBoard* button_board);

#endif