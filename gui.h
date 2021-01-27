#ifndef GUI_H
#define GUI_H
#include <gdk-pixbuf/gdk-pixbuf.h>
#include "mill.h"


void close_window(GtkWidget *widget, Board* board);
void *run_gtk_loop();
//void change_label_value(GtkWidget *widget, gpointer data);
void change_label_value(GtkWidget *label_m);
void enable_css(char* css_file);

#endif