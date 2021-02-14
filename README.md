# Project "The Mill Game"

## The idea of the project

The implementation of a famous board game called "the mill game" (this game is also called "nine men's morris", "mill" or "merels").
It is possible to play the standard version of the game (3 squares, 9 pieces for each player) ...
![](https://i.imgur.com/s8g43vk.png)


... as well as the modified version (2 squares, 6 pieces for each player)
![](https://i.imgur.com/LZpbo2h.png)

 
## Rules of the game

At the beginning players place all their pieces interchangeably on the board. In the standard version each player has 9 men whereas in the 2 square version only 6 ones. The aim is to form so called "mill" which means a string of three men in one column or row. Once a "mill" is achieved the player removes one of the opponents pieces which is not in a "mill" unless all opponent's men are in "mills". Otherwise the player is allowed to remove any man of the opponent they want. After placing all men on the board players slide one of their pieces alternately on an adjacent free field. If a player has only 3 pieces left, they can move their man on any free field on the board. The game ends when one player has only 2 pieces left or is not able to perform any move.       

## Instruction of the game

Placing men consists of clicking on one of the black fields on the board. Removing an opponent's man is performed by clicking on the chosen piece after creating a mill. To move your man you should first click your man then and then a free field.

## Running the program

### Requirements

It is required to have GTK+ 3.0 library installed. The program uses math library (math.h) as well.


### Compilation

All files can be compiled using command:

~~~ 
make
~~~

### Linux
The program should be run in two diffrent terminals. Player ID (A or B) is the first argument of the program. The second argument is the number of squares (2 or 3) the board consists of.
For example if you want to run the 3 square version of the program. In the first terminal you should execute the command (in the directory where the source code is stored) ...

~~~ 
./mill A 3
~~~

... and in the second:

~~~ 
./mill B 3
~~~

Accordingly the 2 square version of the program can be started by the following commands: 
~~~ 
./mill A 2
./mill B 2
~~~
## Modules description
The program consists of 5 modules:
* main.c - the module consists of main function in which gtk main loop is started. There are also many GtkWidgets for GUI created.
* mill.c - the module is responsible for the implementation of the rules of the game. Here are functions which place, move and remove pieces.
* lin-fifo.c - the module creating FIFO files which are necessary for the communication between two copies of the program. 
* gui.c - the module contains functions which are supposed to manage the graphical interface written using GTK+ 3.0 library 
* data_sending.c - the module is responsible for encoding data which is sent and decoding received messages

## Graphical interface

![](https://i.imgur.com/xHyZ0OB.png)

The window title shows the ID of the player (here is Player 1)
* Men number Player 1 - number of men of Player 1
* Men number Player 2 - number of men of Player 2
* Turn - information whose turn it is
* New game - a button to start new game (instanly on both copies of the program)



