
#include "mill.h"
#include "fifo.h"
#include "data_sending.h"
#include "gui.h"

// Wojciech Sniady, nr indeksu: 322993

PipesPtr potoki;
gchar wejscie[MAX_TEXT_LENGHT];
bool YOUR_TURN;
bool P_1_TURN = true;
GtkWidget* CURRENT_BUTTON;
ButtonBoard* BUTTON_BOARD; 
Board *BOARD; 
int MEN_NUMBER_P_1 = 0;
int MEN_NUMBER_P_2 = 0;
int SQUARE_NUMBER_TO_MOVE_FROM;
int FIELD_NUMBER_TO_MOVE_FROM;
GtkWidget *MAIN_WINDOW;
GtkWidget *MEN_NUMBER_P_1_LABEL;
GtkWidget *MEN_NUMBER_P_2_LABEL;
GtkWidget *WHOSE_TURN_LABEL;
int PLAYER_ID;
bool REMOVING;
int NUMBER_OF_SQUARES_ARG;

int main(int argc,char *argv[])
{
    if ((potoki=initPipes(argc,argv)) == NULL)
        return 1;
    if (argc >= 2 && strcmp(argv[1],"A") == 0) 
    { 
        YOUR_TURN = true;
        PLAYER_ID = 1;
    }
    else 
    { 
        YOUR_TURN = false;
        PLAYER_ID = 2;
    }
    gtk_init(&argc, &argv);
    enable_css("./styles/button_colors.css");
    if (argc <= 2)
    {
        printf("Too few arguments\n");
        return 0;
    }
    int n = atoi(argv[2]);
    if (n != 2 && n != 3)
    {
        printf("The size of the board must be set to 2 or 3\n");
        return 0;
    }
    BOARD = generate_board(n);
    NUMBER_OF_SQUARES_ARG = n;
    send_move_information(10, NUMBER_OF_SQUARES_ARG, -1, -1, false);
    gchar window_heading[32];
    sprintf(window_heading,"Mill Game Player %d", (YOUR_TURN) ? (1) : (2));
    GtkWidget* MAIN_WINDOW = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(MAIN_WINDOW), window_heading);
    gtk_window_set_default_size(GTK_WINDOW(MAIN_WINDOW), 1100, 800);
    g_signal_connect(G_OBJECT(MAIN_WINDOW), "destroy",G_CALLBACK(close_window), BOARD);
    gtk_container_set_border_width(GTK_CONTAINER(MAIN_WINDOW), 10);
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_container_add(GTK_CONTAINER(MAIN_WINDOW), hbox);
    GtkWidget *fixed_box = gtk_fixed_new();
    GtkWidget *label_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_box_pack_start(GTK_BOX(hbox), fixed_box, 0, 0, 0);
    gtk_container_add(GTK_CONTAINER(hbox), label_box);
    gtk_widget_set_has_window(fixed_box, TRUE);
    GtkWidget *image;
    if (n == 2)
    {
         image = gtk_image_new_from_file("./images/board_2.jpg"); 
    }
    else 
    {
        image = gtk_image_new_from_file("./images/board_3.jpg"); 
    }     
    gtk_container_add(GTK_CONTAINER(fixed_box), image);
    GtkWidget *main_label = gtk_label_new("Mill Game");
    MEN_NUMBER_P_1_LABEL = gtk_label_new("Men number Player 1 : 0");
    MEN_NUMBER_P_2_LABEL = gtk_label_new("Men number Player 2 : 0");
    WHOSE_TURN_LABEL = gtk_label_new("Turn : Player 1");
    GtkWidget *grid =gtk_grid_new();
    GtkWidget *button = gtk_button_new_with_label("New game");
    g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(new_game), (gpointer) NULL);
    gtk_grid_set_row_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_row_homogeneous(GTK_GRID(grid), TRUE);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 5);
    gtk_grid_set_column_homogeneous(GTK_GRID(grid), TRUE);
    gtk_box_pack_start(GTK_BOX(label_box), grid, TRUE, FALSE, 0);
    gtk_widget_set_hexpand (label_box, TRUE);
    gtk_widget_set_halign (label_box, GTK_ALIGN_CENTER);
    gtk_grid_attach(GTK_GRID(grid), main_label, 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), MEN_NUMBER_P_1_LABEL, 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), MEN_NUMBER_P_2_LABEL, 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), WHOSE_TURN_LABEL, 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), button, 0, 4, 1, 1);
    gtk_widget_set_halign (fixed_box, GTK_ALIGN_START);
    gtk_widget_set_halign (label_box, GTK_ALIGN_CENTER);
    BUTTON_BOARD = generate_button_board(n); 
    GtkWidget* button_2_0 = generate_single_button(BUTTON_BOARD, 70, 70, fixed_box, 2, 0);
    int arr_2_0[] = {2, 0};
    g_signal_connect(G_OBJECT(button_2_0), "clicked",G_CALLBACK(button_callback), (gpointer) arr_2_0);
    GtkWidget* button_2_1 = generate_single_button(BUTTON_BOARD, 365, 70, fixed_box, 2, 1);
    int arr_2_1[] = {2, 1};
    g_signal_connect(G_OBJECT(button_2_1), "clicked",G_CALLBACK(button_callback), (gpointer) arr_2_1);
    GtkWidget* button_2_2 = generate_single_button(BUTTON_BOARD, 660, 70, fixed_box,  2, 2);
    int arr_2_2[] = {2, 2};
    g_signal_connect(G_OBJECT(button_2_2), "clicked",G_CALLBACK(button_callback), (gpointer) arr_2_2);
    GtkWidget* button_2_3 = generate_single_button(BUTTON_BOARD, 660, 365, fixed_box, 2, 3);
    int arr_2_3[] = {2, 3};
    g_signal_connect(G_OBJECT(button_2_3), "clicked",G_CALLBACK(button_callback), (gpointer) arr_2_3);
    GtkWidget* button_2_4 = generate_single_button(BUTTON_BOARD, 660, 660, fixed_box, 2, 4);
    int arr_2_4[] = {2, 4};
    g_signal_connect(G_OBJECT(button_2_4), "clicked",G_CALLBACK(button_callback), (gpointer) arr_2_4);
    GtkWidget* button_2_5 = generate_single_button(BUTTON_BOARD, 365, 660, fixed_box, 2, 5);
    int arr_2_5[] = {2, 5};
    g_signal_connect(G_OBJECT(button_2_5), "clicked",G_CALLBACK(button_callback), (gpointer) arr_2_5);
    GtkWidget* button_2_6 = generate_single_button(BUTTON_BOARD, 70, 660, fixed_box, 2, 6);
    int arr_2_6[] = {2, 6};
    g_signal_connect(G_OBJECT(button_2_6), "clicked",G_CALLBACK(button_callback), (gpointer) arr_2_6);
    GtkWidget* button_2_7 = generate_single_button(BUTTON_BOARD, 70, 365, fixed_box, 2, 7);
    int arr_2_7[] = {2, 7};
    g_signal_connect(G_OBJECT(button_2_7), "clicked",G_CALLBACK(button_callback), (gpointer) arr_2_7);
    GtkWidget* button_1_0 = generate_single_button(BUTTON_BOARD, 170, 170, fixed_box, 1, 0);
    int arr_1_0[] = {1, 0};
    g_signal_connect(G_OBJECT(button_1_0), "clicked",G_CALLBACK(button_callback), (gpointer) arr_1_0);
    GtkWidget* button_1_1 = generate_single_button(BUTTON_BOARD, 365, 170, fixed_box, 1, 1);
    int arr_1_1[] = {1, 1};
    g_signal_connect(G_OBJECT(button_1_1), "clicked",G_CALLBACK(button_callback), (gpointer) arr_1_1);
    GtkWidget* button_1_2 = generate_single_button(BUTTON_BOARD, 560, 170, fixed_box, 1, 2);
    int arr_1_2[] = {1, 2};
    g_signal_connect(G_OBJECT(button_1_2), "clicked",G_CALLBACK(button_callback), (gpointer) arr_1_2);
    GtkWidget* button_1_3 = generate_single_button(BUTTON_BOARD, 560, 365, fixed_box, 1, 3);
    int arr_1_3[] = {1, 3};
    g_signal_connect(G_OBJECT(button_1_3), "clicked",G_CALLBACK(button_callback), (gpointer) arr_1_3);
    GtkWidget* button_1_4 = generate_single_button(BUTTON_BOARD, 560, 560, fixed_box, 1, 4);
    int arr_1_4[] = {1, 4};
    g_signal_connect(G_OBJECT(button_1_4), "clicked",G_CALLBACK(button_callback), (gpointer) arr_1_4);
    GtkWidget* button_1_5 = generate_single_button(BUTTON_BOARD, 365, 560, fixed_box, 1, 5);
    int arr_1_5[] = {1, 5};
    g_signal_connect(G_OBJECT(button_1_5), "clicked",G_CALLBACK(button_callback), (gpointer) arr_1_5);
    GtkWidget* button_1_6 = generate_single_button(BUTTON_BOARD, 170, 560, fixed_box, 1, 6);
    int arr_1_6[] = {1, 6};
    g_signal_connect(G_OBJECT(button_1_6), "clicked",G_CALLBACK(button_callback), (gpointer) arr_1_6);
    GtkWidget* button_1_7 = generate_single_button(BUTTON_BOARD, 170, 365, fixed_box, 1, 7);
    int arr_1_7[] = {1, 7};
    g_signal_connect(G_OBJECT(button_1_7), "clicked",G_CALLBACK(button_callback), (gpointer) arr_1_7);
    if (n == 3)
    {
        GtkWidget* button_0_0 = generate_single_button(BUTTON_BOARD, 270, 270, fixed_box, 0, 0);
        int arr_0_0[] = {0, 0};
        g_signal_connect(G_OBJECT(button_0_0), "clicked",G_CALLBACK(button_callback), (gpointer) arr_0_0);
        GtkWidget* button_0_1 = generate_single_button(BUTTON_BOARD, 365, 270, fixed_box, 0, 1);
        int arr_0_1[] = {0, 1};
        g_signal_connect(G_OBJECT(button_0_1), "clicked",G_CALLBACK(button_callback), (gpointer) arr_0_1);
        GtkWidget* button_0_2 = generate_single_button(BUTTON_BOARD, 460, 270, fixed_box, 0, 2);
        int arr_0_2[] = {0, 2};
        g_signal_connect(G_OBJECT(button_0_2), "clicked",G_CALLBACK(button_callback), (gpointer) arr_0_2);
        GtkWidget* button_0_3 = generate_single_button(BUTTON_BOARD, 460, 365, fixed_box, 0, 3);
        int arr_0_3[] = {0, 3};
        g_signal_connect(G_OBJECT(button_0_3), "clicked",G_CALLBACK(button_callback), (gpointer) arr_0_3);
        GtkWidget* button_0_4 = generate_single_button(BUTTON_BOARD, 460, 460, fixed_box, 0, 4);
        int arr_0_4[] = {0, 4};
        g_signal_connect(G_OBJECT(button_0_4), "clicked",G_CALLBACK(button_callback), (gpointer) arr_0_4);
        GtkWidget* button_0_5 = generate_single_button(BUTTON_BOARD, 365, 460, fixed_box, 0, 5);
        int arr_0_5[] = {0, 5};
        g_signal_connect(G_OBJECT(button_0_5), "clicked",G_CALLBACK(button_callback), (gpointer) arr_0_5);
        GtkWidget* button_0_6 = generate_single_button(BUTTON_BOARD, 270, 460, fixed_box, 0, 6);
        int arr_0_6[] = {0, 6};
        g_signal_connect(G_OBJECT(button_0_6), "clicked",G_CALLBACK(button_callback), (gpointer) arr_0_6);
        GtkWidget* button_0_7 = generate_single_button(BUTTON_BOARD, 270, 365, fixed_box, 0, 7);
        int arr_0_7[] = {0, 7};
        g_signal_connect(G_OBJECT(button_0_7), "clicked",G_CALLBACK(button_callback), (gpointer) arr_0_7);
    }
    g_timeout_add(100, receive_move_information,NULL);
    gtk_widget_show_all(MAIN_WINDOW);
    gtk_main();
    closePipes(potoki);
    free_board(BOARD);
    return 0;
}
