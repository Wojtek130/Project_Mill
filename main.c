
#include "mill.h"
#include "fifo.h"
#include "data_sending.h"
#include "gui.h"
// Wojciech Sniady, nr indeksu: 322993


//static char *moj_id, *twoj_id;
PipesPtr potoki;
gchar wejscie[MAX_TEXT_LENGHT];
GtkWidget* MAIN_WINDOW;
GtkWidget* main_label;
bool your_turn;


int main(int argc,char *argv[])
{
    if ((potoki=initPipes(argc,argv)) == NULL)
        return 1;
    if (argc == 2 && strcmp(argv[1],"A") == 0) 
    { 
        your_turn = true;
    }
    else 
    { 
        your_turn = false;
    }
    gtk_init(&argc, &argv);
    enable_css("./styles/button_colors.css");
    int n = 3;
    Board *board_3 = generate_board(n);
    gchar window_heading[32];
    sprintf(window_heading,"Mill Game Player %d", (your_turn) ? (1) : (2));
    MAIN_WINDOW = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(MAIN_WINDOW), window_heading);
    gtk_window_set_default_size(GTK_WINDOW(MAIN_WINDOW), 1100, 800);
    g_signal_connect(G_OBJECT(MAIN_WINDOW), "destroy",G_CALLBACK(close_window), board_3);
    gtk_container_set_border_width(GTK_CONTAINER(MAIN_WINDOW), 10);
    //GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    //gtk_container_add(GTK_CONTAINER(MAIN_WINDOW), vbox);
    GtkWidget *hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    //gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, 0, 0);
    gtk_container_add(GTK_CONTAINER(MAIN_WINDOW), hbox);
    //gtk_box_pack_start(GTK_BOX(vbox), hbox, 0, 0, 0);
    GtkWidget *fixed_box = gtk_fixed_new();
    gtk_box_pack_start(GTK_BOX(hbox), fixed_box, 0, 0, 0);
    gtk_widget_set_has_window(fixed_box, TRUE);
    GtkWidget *image = gtk_image_new_from_file("./images/board_3.jpg");    
    gtk_container_add(GTK_CONTAINER(fixed_box), image);
    GtkWidget *main_label = gtk_label_new("Mill Game");
    gtk_box_pack_start(GTK_BOX(hbox), main_label, 0, 0, 0);
    //GtkWidget *second_label = gtk_label_new("Second labek");
    //gtk_box_pack_end(GTK_BOX(vbox), second_label, 0, 0, 0);
    //gtk_container_add(GTK_CONTAINER(MAIN_WINDOW), vbox);
    //GtkWidget *box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    //gtk_container_add(GTK_CONTAINER(MAIN_WINDOW), box1);
    
    //gtk_widget_set_size_request(main_label, 50, 10);
    //gtk_box_pack_start(GTK_BOX(box1), main_label, TRUE, TRUE, 0);
    

    //GtkWidget *layout = gtk_layout_new(NULL, NULL);
    //gtk_container_add(GTK_CONTAINER (fixed_box), layout);
    
    GtkWidget *button = gtk_button_new();
    gtk_widget_set_name(button, "black-background");
    gtk_widget_set_size_request(button, 70, 70);
    gtk_style_context_add_class(gtk_widget_get_style_context( GTK_WIDGET(button)),"circular");
    gtk_fixed_put(GTK_FIXED(fixed_box), button, 70, 70);

    GtkWidget* button_1 = create_button(500, 500, fixed_box);
    gtk_widget_set_name(button_1, "yellow-background");

    pthread_t thread_id;

    pthread_create(&thread_id, NULL, run_gtk_loop, NULL); 

    


    print_board(board_3);
    printf("\n");
    int men_number_p_1 = 0;
    int men_number_p_2 = 0;
    bool p_1_turn = true;
    bool received_no_message = true;
    bool waiting_for_remove_message = false;
    bool game_goes_on = true;
    bool loss_message_received = false;
    char move_information[MAX_TEXT_LENGHT];
    int x = 2; 
    for (int i = 0; i < 3*x; i++)
    {
        if (your_turn)
        {
            place_men(board_3, p_1_turn, &men_number_p_1, &men_number_p_2);
            print_board(board_3);
            change_label_value(main_label);
            gtk_widget_set_name(button, "yellow-background");
        }
        else
        {
            while (received_no_message)
            {
                if (getStringFromPipe(potoki,wejscie,MAX_TEXT_LENGHT))
                {
                    strcpy(move_information, wejscie);
                    //printf("rec : %s\n", move_information);
                    long* move_information_arr = received_value(move_information);
                    int sqr_number_pla = move_information_arr[0];
                    int fie_number_pla = move_information_arr[1];
                    if (waiting_for_remove_message == false)
                    {
                        place_men_received(board_3, p_1_turn, sqr_number_pla, fie_number_pla, &men_number_p_1, &men_number_p_2);
                        print_board(board_3);
                        int remove_man = move_information_arr[4];
                        if (remove_man)
                        {
                            waiting_for_remove_message = true;
                        }
                        else
                        {
                            received_no_message = false;
                        }
                    }
                    else
                    {
                        remove_men_received(board_3, p_1_turn, sqr_number_pla, fie_number_pla, &men_number_p_1, &men_number_p_2);
                        print_board(board_3);
                        waiting_for_remove_message = true;
                        received_no_message = false;
                    }
                    free(move_information_arr);
                }
            sleep(0.1);
            }
        }
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
        waiting_for_remove_message = false;
        received_no_message = true;
        your_turn = !your_turn;
        p_1_turn = !p_1_turn;
    }
    received_no_message = true;
    while (game_goes_on)
    {
        if (your_turn)
        {
            move_men(board_3, p_1_turn, &men_number_p_1, &men_number_p_2);
            print_board(board_3);
            if (game_over(board_3, p_1_turn, men_number_p_1, men_number_p_2) == true)
            {
                break;
            }
        }
        else
        {
            while (received_no_message)
            {
                if (getStringFromPipe(potoki,wejscie,MAX_TEXT_LENGHT))
                {   
                    strcpy(move_information, wejscie);
                    long* move_information_arr = received_value(move_information);
                    int sqr_number_pla = move_information_arr[0];
                    int fie_number_pla = move_information_arr[1];
                    int chosen_sqr_number_pla = move_information_arr[2];
                    int chosen_fie_number_pla = move_information_arr[3];
                    if (waiting_for_remove_message == false)
                    {
                        move_men_received(board_3, p_1_turn, sqr_number_pla, fie_number_pla, chosen_sqr_number_pla, chosen_fie_number_pla);
                        print_board(board_3);
                        int remove_man = move_information_arr[4];
                        if (remove_man)
                        {
                            waiting_for_remove_message = true;
                        }
                        else
                        {
                            received_no_message = false;
                        }
                    }
                    else
                    {
                        remove_men_received(board_3, p_1_turn, sqr_number_pla, fie_number_pla, &men_number_p_1, &men_number_p_2);
                        print_board(board_3);
                        waiting_for_remove_message = true;
                        received_no_message = false;
                    }
                    free(move_information_arr);
                    if (game_over(board_3, p_1_turn, men_number_p_1, men_number_p_2) == true)
                    {
                        game_goes_on = false;
                        loss_message_received = true;
                        break;
                    }
                }
                sleep(0.1);
            }
        }
        printf("men number player 1: %d, men number player 2: %d\n", men_number_p_1, men_number_p_2);
        waiting_for_remove_message = false;
        received_no_message = true;
        your_turn = !your_turn;
        p_1_turn = !p_1_turn;
    }
    show_winner(p_1_turn, loss_message_received);
    
    closePipes(potoki);
    //free_board(board_2);
    free_board(board_3);
    return 0;
}