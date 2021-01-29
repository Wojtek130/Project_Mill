#include "gui.h"

/*
typedef struct CallbackArguments
{
    int len;
    int *a_num;
    GtkWidget **a_label;    
} CallbackArguments;
typedef struct CallbackArguments CallbackArguments;*/

void *run_gtk_loop()
{
  gtk_widget_show_all(MAIN_WINDOW);
  gtk_main();
  return NULL;
}

void close_window(GtkWidget *widget, Board* board)
{
  closePipes(potoki);
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

GtkWidget *create_button(int coor_x, int coor_y, GtkWidget* box_to_put_in)
{
    GtkWidget *button = gtk_button_new();
    gtk_widget_set_name(button, "black-background");
    gtk_widget_set_size_request(button, 70, 70);
    gtk_style_context_add_class(gtk_widget_get_style_context( GTK_WIDGET(button)),"circular");
    gtk_fixed_put(GTK_FIXED(box_to_put_in), button, coor_x, coor_y);
    return button;
}
