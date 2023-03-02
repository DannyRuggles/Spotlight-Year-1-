#include <stdio.h>
#include <string.h>
#include "snake.c"
/*
Author: Danny Ruggles
Date: 2/11/2023
Purpose: Tic-Tac-Toe game to be played by 2 people, with a main menu and high scores
Notes: This program is a bit of a mess, sorry about that. I tried to rework what I'd already done to fit the updated requirements, but it's not the cleanest.
UPDATE 2/27/2023: I added in a snake game which is option 5 in the main menu. I've also parsed a lot of the code into functions to make it more modular. 
*/

// Exit game function
void exitgame() {
    printf("Goodbye!\n");
    getchar();
    getchar();
    exit(0);
}

// The main menu display
void mainmenu() {
    system("cls");
    printf("Welcome to Tic Tac Toe!\n\n");
    printf("1. New game\n");
    printf("2. Rules\n");
    printf("3. Scoreboard\n");
    printf("4. Exit\n\n");
}

// The Rules menu that gets called in case 2
void rules() {
    system("cls");
    printf("\nYou don't know the rules for tic tac toe? Wow, okay, well I'll explain..\n\n");
    printf("\nThe game is played with 2 people, each taking turns placing their markers on the board.\n");
    printf("You place your markers by first input the row (from 1 to 3) and then input a column (from 1 to 3)\n");
    printf("You can also input your move in one input. Example: '1 3' \n");
    printf("To QUIT back to the main menu during a match, enter 9 for either your row or column selection.\n");
    printf("The goal of the game is to get a line of 3 symbols, they can be a horizontal line, a vertical line, or\n");
    printf("a diagonal line.");
    printf("\n\n Examples: \n");
    printf("x  x  \n");
    printf("x   x  \n");
    printf("x    x  xxx\n");
    printf("1.  2.   3. \n");
    printf("1= Vertical 2= Diagonal 3= Horizontal \n");
    printf("\nHints: \n");
    printf("Try to interrupt your opponents lines to win.\n");
    printf("\n\nPress Enter to Return to menu....\n");
    getchar();
    getchar();      // Wait for the user to press Enter
}

// Define a struct type to hold information about a player
typedef struct {
    char name[20];  // player name, up to 20 characters
    char symbol;    // X or O
    int wins;       // number of games won
    int losses;     // number of games lost
} Player;

// Function to print the game board
void print_board(char board[3][3]) {
    printf("  1 2 3\n");                // Print column labels
    for (int i = 0; i < 3; i++) {       // Loop over rows
        printf("%d ", i+1);             // Print row label
        for (int j = 0; j < 3; j++) {   // Loop over columns
            printf("%c ", board[i][j]); // Print the symbol in the cell
        }
        printf("\n");                   // Move to the next row
    }
}

// Function to check for a win
int check_win(char board[3][3], char symbol) {
    // Check rows and columnsS
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == symbol) {
            return 1;   // A row contains all the same symbol, so there's a win
        }
        if (board[0][i] == symbol && board[1][i] == symbol && board[2][i] == symbol) {
            return 1;   // A column contains all the same symbol, so there's a win
        }
    }
    // Check diagonals
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == symbol) {
        return 1;       // Top-left to bottom-right diagonal contains all the same symbol, so there's a win
    }
    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == symbol) {
        return 1;       // Top-right to bottom-left diagonal contains all the same symbol, so there's a win
    }
    return 0;           // There's no win yet
}

// Main Function
int main() {
    char ply;   // Variable used for play again choice at the end of the game

    Player player1, player2;     // Create two Player objects to hold information about the two players

    // Player X
    printf("Enter player 1's name: ");
    scanf("%s", player1.name);  // Get the name of the player
    player1.symbol = 'X';       // Assign the symbol to the player
    player1.wins = 0;           // Initialize the number of wins for the player to 0
    player1.losses = 0;         // Initialize the number of loses for the player to 0

    // Player O
    printf("Enter player 2's name: ");
    scanf("%s", player2.name);
    player2.symbol = 'O';
    player2.wins = 0;
    player2.losses = 0;

    //  Main menu start location
    menu:

    do{

    mainmenu();

    int choice;
    printf("Enter your choice: ");
    scanf("%d", &choice);      // Get the user's choice from the main menu

    switch (choice) {
        case 1:                 // `break` to the game below
            break;
        case 2:                 // Rules menu
            rules();
            goto menu;      // Go back to the main menu
        case 3:             // Prints the # of wins for each player
            system("cls");
            printf("%s has a score of %d\n", player1.name, player1.wins);
            printf("%s has a score of %d\n", player2.name, player2.wins);
            printf("\n\nPress Enter to Return to menu....\n");
            getchar();
            getchar();
            goto menu;
        case 4:             // Main menu exit function
            exitgame();
        case 5:             // Snake game. Launches the snake.c file
            system("cls");
            printf("OH, you found the secret option, congrats!\nWell then...");
            sleep(1);
            printf("\nLet's play snake!");
            sleep(1);
            snakegame();    // This is the main function in the snake.c file
            continue;
        default:
            printf("Invalid choice. Please Enter to try again.\n");
            getchar();
            getchar();
            getchar();      // Seemed to need an extra `getchar()` to avoid it skipping past
            goto menu;
    }

    // Gameplay starts here
    start:
    getchar();
    system("cls");

    char board[3][3];
    int turn = 0, row, col;
    memset(board, ' ', sizeof(board));

    while (1) {
        Player *current_player = turn % 2 == 0 ? &player1 : &player2;
        Player *other_player = turn % 2 == 0 ? &player2 : &player1;

        printf("%s's turn (%c):\n", current_player->name, current_player->symbol);
        print_board(board);

                // Player selects place on board to move
        printf("Enter row (1-3): ");
        scanf("%d", &row);
        printf("Enter column (1-3): ");
        scanf("%d", &col);
        
        if (row==9||col==9){
            printf("going to main menu..");
            getchar;
            getchar;
            sleep(1);
            break;
        }

                //checks if spot is open
        if (board[row-1][col-1] != ' ') {
            printf("That spot is already taken. Press Enter to try again.\n");
            getchar();
            getchar();
            system("cls");
            continue;
        }
                //checks for winner, clears screen between turns, and updates scoreboard
        board[row-1][col-1] = current_player->symbol;
        system("cls");
        if (check_win(board, current_player->symbol)) {
            printf("%s wins!\n", current_player->name);
            current_player->wins++;
            other_player->losses++;
            print_board(board);
            break;
        }
            // Max turns == tie game
        if (turn == 8) {
            printf("Tie game!\n");
            print_board(board);
            break;
        }

        turn++;
    }
        // End of game display
    printf("%s: %d wins, %d losses\n", player1.name, player1.wins, player1.losses);
    printf("%s: %d wins, %d losses\n", player2.name, player2.wins, player2.losses);
    printf("To play again press Y .. Press any key to return to the Menu.\n\n");
    getchar();
    scanf("%c", &ply);

        if(ply=='Y'||ply=='y')
            {
            goto start;
            }
        if(ply=='Q'||ply=='q')
            {
            exitgame();
            }
        else
            {
            goto menu;
            };
        }while (ply != 'Q' && ply != 'q'); // Hidden escape input from game over screen, using "Q"
    return 0;
}

