#include "gui.h"

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

GtkWidget *create_single_button(int coor_x, int coor_y, GtkWidget* box_to_put_in)
{
    GtkWidget *button = gtk_button_new();
    gtk_widget_set_name(button, "black-background");
    gtk_widget_set_size_request(button, 70, 70);
    gtk_style_context_add_class(gtk_widget_get_style_context( GTK_WIDGET(button)),"circular");
    gtk_fixed_put(GTK_FIXED(box_to_put_in), button, coor_x, coor_y);
    return button;
}

void button_callback(GtkWidget *widget, gpointer data)
{
  int *move_array = (int*) data;
  CURRENT_MOVE[0] = move_array[0];
  CURRENT_MOVE[1] = move_array[1];
  CURRENT_BUTTON = widget;
  /*if (REMOVE)
  {
    gtk_widget_set_name(widget, "black-background");
    REMOVE = false;
  }
  else if (P_1_TURN)
  {
    gtk_widget_set_name(widget, "red-background");
  }
  else
  {
    gtk_widget_set_name(widget, "blue-background");
  }*/
  
  
}

GtkWidget **create_all_buttons(int board_size, GtkWidget* box_to_put_in)
{
  GtkWidget **button_arr = malloc(sizeof(GtkWidget*)*board_size);
  GtkWidget* button_2_0 = create_single_button(70, 70, box_to_put_in);
  GtkWidget* button_2_1 = create_single_button(365, 70, box_to_put_in);
  GtkWidget* button_2_2 = create_single_button(660, 70, box_to_put_in);
  GtkWidget* button_2_3 = create_single_button(660, 365, box_to_put_in);
  GtkWidget* button_2_4 = create_single_button(660, 660, box_to_put_in);
  GtkWidget* button_2_5 = create_single_button(365, 660, box_to_put_in);
  GtkWidget* button_2_6 = create_single_button(70, 660, box_to_put_in);
  GtkWidget* button_2_7 = create_single_button(70, 365, box_to_put_in);
  GtkWidget* button_1_0 = create_single_button(170, 170, box_to_put_in);
  GtkWidget* button_1_1 = create_single_button(365, 170, box_to_put_in);
  GtkWidget* button_1_2 = create_single_button(560, 170, box_to_put_in);
  GtkWidget* button_1_3 = create_single_button(560, 365, box_to_put_in);
  GtkWidget* button_1_4 = create_single_button(560, 560, box_to_put_in);
  GtkWidget* button_1_5 = create_single_button(365, 560, box_to_put_in);
  GtkWidget* button_1_6 = create_single_button(170, 560, box_to_put_in);
  GtkWidget* button_1_7 = create_single_button(170, 365, box_to_put_in);
  GtkWidget* button_0_0 = create_single_button(270, 270, box_to_put_in);
  GtkWidget* button_0_1 = create_single_button(365, 270, box_to_put_in);
  GtkWidget* button_0_2 = create_single_button(460, 270, box_to_put_in);
  GtkWidget* button_0_3 = create_single_button(460, 365, box_to_put_in);
  GtkWidget* button_0_4 = create_single_button(460, 460, box_to_put_in);
  GtkWidget* button_0_5 = create_single_button(365, 460, box_to_put_in);
  GtkWidget* button_0_6 = create_single_button(270, 460, box_to_put_in);
  GtkWidget* button_0_7 = create_single_button(270, 365, box_to_put_in);
  return button_arr;
}
