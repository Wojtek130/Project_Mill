#include "gui.h"




void close_window(GtkWidget *widget, Board* board)
{
  closePipes(potoki);
  free_board(board);
  gtk_main_quit();
}