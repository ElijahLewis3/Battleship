#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <ctype.h>


char board[5][5]; //game board
char computerBoard[5][5]; //board that contains all the computer's hits and misses
char player1Board[5][5]; //board that contains all the first player's hits and misses
char player2Board[5][5]; //board that contains all the second player's hits and misses
char computerGuesss[5][5]; //board that contains all the computer's guesses
char player1Guesss[5][5]; //board that contains all the first player's guesses
char player2Guesss[5][5]; //board that contains all the second player's guesses
char totalGuess[5][5]; //board that displays both player's hits and misses

void resetBoard(); //function to reset the board to all empty characters
void printBoard(); //prints the regular board 
void printPlayerVsPlayerBoard(); // prints the board for two player mode which shows the hits and misses
void player1Ships(); //function that gets the player to enter their ship's location
void player2Ships(); //function that gets the player to enter their ship's location
void computerShips();//function that gets computer to pick random ship locations
char player1Guess();//function that makes the first player guess the computers ship locations
char player2Guess();//function that makes the second player guess the computers ship locations
char computerGuess();//function that makes the computer guess the user's ship location
void printStars();


int main(){
    char repeat; //repeat variable that asks if they want to keep on playing
    int totalCompWins = 0, totalPlay1Wins = 0, totalPlay2Wins = 0; //total computer wins, player 1 wins and player 2 wins
    int mode; //variable used to determine if the user wants to face the computer or another player

    //      INTRO STATEMENTS        //

    printf("\n");
    printStars();
    printf("Welcome to my easy, simple to play, *** BATTLESHIP ***\n\nThe instructions are relatively simple, you are prompted to place 3 ships on a 5x5 board by entering their coordinates \n(row first then column) with a space in between.\n\n");
    printf("After you selected the column, press enter to input the next ship's coordinates.\n\n");
    printf("If you either enter coordinates that are GREATER than 5 or LESS than 0 OR enter coordinates for a ship that's already in that place.\n");
    printf("You will be asked to enter those coordinates again until they are valid.\n\n");
    printf("You will see that your ships are marked as a 'P' on the board. If the computer hit's one of your ships, it will be marked 'L'.\n\n");
    printf("If you guess a spot and miss, it will be marked with '$' if you hit one of the computer's ship, it's marked with 'W'.\nWhenever the computer misses, it's marked with '!'.\n\n");
    printf("However, if the computer guesses in a spot you've already guessed, '!' will not be displayed but the guess still counts.\n\n");
    printf("Good luck and HAVE FUN!!!\n");
    printStars();
    printf("\n");

    do {
    
        printf("This game has 2 modes. Player vs. Computer OR Player vs. Player.\nPress 1 to face the computer or 2 to face another player: ");
        scanf("%d",&mode);

        //  PLAYER VS COMPUTER  //

        if (mode == 1){

            do{

                resetBoard();//resets the board
                printBoard();//function that prints an empty board

                player1Ships(); //gets the user to enter their ships

                computerShips(); //gets the computer to enter ships' location

                printBoard();


                int playerHitShips = 0, computerHitShips = 0; //2 variables to count how many time the user/computer hits ships


                do{
                    char player1Result = player1Guess(); //variable used to store the character returned by player1Guess()
                    char computerResult = computerGuess(); //variable used to store the character returned by player1Guess()

                    if (player1Result == 'W'){//if the player hit a ship, playerHitShips gets incremented
                        playerHitShips++;
                    }
                    if (computerResult == 'L'){ //if the computer hit a ship, computerHitShips gets incremented
                        computerHitShips++;
                    }

                    // prints the total number of hits the computer and user have
                    printf("\nThe computer has hit (%d) ships so far\n",computerHitShips);
                    printf("You have hit (%d) ships so far\n\n",playerHitShips);

                    //prints the board after every player guess
                    printBoard();

                    //if the player sunk 3 ships, the game ends and the loop breaks
                    if (playerHitShips == 3) {
                        totalPlay1Wins++;//total player wins gets incremented
                        printf("Game over!\n");
                        printf("The player wins!\n");
                        break;
                    }

                    //if the computer sunk 3 ships, the game ends and the loop breaks
                    //all of the ship's locations are revealed to the user
                    else if (computerHitShips == 3){
                        totalCompWins++;//total computer wins gets incremented
                        printf("Game over!\n");
                        printf("The computer wins!\n");
                        printf("These were the locations of the computer's ships\n");
                        //for loop that prints the ships location
                        for (int i = 0; i < 5; i++) {
                            for (int j = 0; j < 5; j++) {
                                if (computerBoard[i][j] == 'C') {
                                    printf("[%d, %d] ", i+1, j+1);
                                }
                            }
                        }

                        printf("\n");
                        break;
                    }


                }while(playerHitShips != 3 || computerHitShips !=3); //game continues until one or the other wins

                printf("Would you like to play again?(y/n): "); //prompts the user if they want to play again
                getchar();
                scanf("%c",&repeat);
                repeat = tolower(repeat);

            }while (repeat == 'y'); //keeps on going until the user wants the continue

            // print statements that display the win count

            printf("\nThe total number of wins accumulated by player 1 is (%d)\n",totalPlay1Wins);
            printf("The total number of wins accumulated by player 2 is (%d)\n",totalPlay2Wins);
            printf("The total number of wins accumulated by the computer is (%d)\n\n",totalCompWins);
            printf("Thank you for playing\n");

        }

        //  PLAYER VS PLAYER    //

        else if (mode == 2){

            do{ //do-while loop that continues until the user doesn't want to play anymore

                resetBoard();//resets the board
                printPlayerVsPlayerBoard();//prints an empty board

                printf("***** PLAYER 1 *****\n\n");
                player1Ships(); //gets the first player to enter their ships

                printf("\n***** PLAYER 2 *****\n\n");
                player2Ships(); //gets the second player to enter their ships


                int player1HitShips = 0, player2HitShips = 0; //2 variables to count how many time the user/computer hits ships


                do{ //do-while loop that continues until there is a winner
                    char player1Result = player1Guess(); //variable used to store the character returned by player1Guess()

                    if (player1Result == 'W'){//if the player hit a ship, playerHitShips gets incremented
                        player1HitShips++;
                    }

                    if (player1HitShips == 3) {
                        totalPlay1Wins++;//total player wins gets incremented
                        printf("Game over!\n");
                        printf("Player 1 wins!\n");
                        printf("These were the locations of player 1's ships\n");

                        //for loop that prints the ships location
                        for (int i = 0; i < 5; i++) {
                            for (int j = 0; j < 5; j++) {
                                if (player1Board[i][j] == 'P') {
                                    printf("[%d, %d] ", i+1, j+1);
                                }
                            }
                        }
                        break;
                    }

                    char player2Result = player2Guess(); //variable used to store the character returned by player2Guess()

                    if (player2Result == 'H'){ //if player 2 hit a ship, player2HitShips gets incremented
                        player2HitShips++;
                    }

                    // prints the total number of hits player 1 and 2 have
                    printf("\nPlayer 1 has hit (%d) ships so far\n",player1HitShips);
                    printf("Player 2 has hit (%d) ships so far\n\n",player2HitShips);

                    //prints the board after every player guess
                    printPlayerVsPlayerBoard();
                    

                    if (player2HitShips == 3){
                        totalPlay2Wins++;//total player2 wins gets incremented
                        printf("Game over!\n");
                        printf("Player 2 wins!\n");
                        printf("These were the locations of player 2's ships\n");

                        //for loop that prints the ships location
                        for (int i = 0; i < 5; i++) {
                            for (int j = 0; j < 5; j++) {
                                if (player2Board[i][j] == 'U') {
                                    printf("[%d, %d] ", i+1, j+1);
                                }
                            }
                        }

                        printf("\n");
                        break;
                    }


                }while(player1HitShips != 3 || player2HitShips !=3); //game continues until one or the other wins

                printf("Would you like to play again?(y/n): "); //prompts the user if they want to play again
                getchar();
                scanf("%c",&repeat);
                repeat = tolower(repeat);

            }while (repeat == 'y'); //keeps on going until the user wants the continue

            printf("\nThe total number of wins accumulated by player 1 is (%d)\n",totalPlay1Wins);
            printf("The total number of wins accumulated by player 2 is (%d)\n",totalPlay2Wins);
            printf("The total number of wins accumulated by the computer is (%d)\n\n",totalCompWins);
            printf("Thank you for playing\n");

        }

    
    }while(mode != 1 && mode != 2); //loops while the player either selects 1 or 2

    return 0;
}


void resetBoard(){
    for (int i = 0; i < 5;i++){
        for (int j = 0; j < 5;j++){
            board[i][j] = ' '; //every spot on the 2D array is empty
            computerBoard[i][j] = ' '; //the computer's board gets reset
            computerGuesss[i][j] = ' '; //the computer's guess board gets reset
            player1Guesss[i][j] = ' '; //player 1's guess board gets reset
            player1Board[i][j] = ' ';//player 1's board gets reset
            player2Board[i][j] = ' ';//player 2's board gets reset
            player2Guesss[i][j] = ' ';//player 2's guess board gets reset
            totalGuess[i][j] = ' ';// the total guess board gets reset
        }
    }
}

void printBoard(){
    for (int i = 0; i < 5; i++){
        printf(" %c | %c | %c | %c | %c\n",board[i][0],board[i][1],board[i][2],board[i][3],board[i][4]);//prints whatever the value is at that array index
        printf("---|---|---|---|---\n");
    }
}


//  FUNCTION THAT GETS THE FIRST PLAYER TO CHOOSE THEIR SHIPS' LOCATIONS  //

void player1Ships(){

    int ship1Row, ship1Col, ship2Row, ship2Col, ship3Row ,ship3Col;

    //      FIRST SHIP      //


    printf("Enter the row and column of your first ship separated by a space(1-5): ");
    scanf("%d%d",&ship1Row,&ship1Col);

    printf("\n");

    //if the ship's location that the user entered isn't a spot on the board it is invalid

    if ((ship1Row > 5 || ship1Row < 1) || (ship1Col > 5 || ship1Col < 1)){
        printf("That isn't a valid option\n");
        do{
            printf("Enter the row and column of your first ship separated by a space(1-5): ");
            scanf("%d%d",&ship1Row,&ship1Col);

        }while(((ship1Row > 5 || ship1Row < 1) || (ship1Col > 5 || ship1Col < 1)));
    }

    ship1Row--;
    ship1Col--;

    //if the spot the user wants to place the ship is open, a 'P' is placed

    if (board[ship1Row][ship1Col] == ' ') {
        board[ship1Row][ship1Col] = 'P';
        player1Board[ship1Row][ship1Col] = 'P';
        //computerBoard[ship1Row][ship1Col] = 'P';
    }



    //      SECOND SHIP      //


    printf("Enter the row and column of your second ship separated by a space: ");
    scanf("%d%d",&ship2Row,&ship2Col);

    //if the ship's location that the user entered isn't a spot on the board it is invalid


    if ((ship2Row > 5 || ship2Row < 1) || (ship2Col > 5 || ship2Col < 1)){
        printf("That isn't a valid option\n");

        do{
            printf("Enter the row and column of your second ship separated by a space(1-5): ");
            scanf("%d%d",&ship2Row,&ship2Col);

        }while(((ship2Row > 5 || ship2Row < 1) || (ship2Col > 5 || ship2Col < 1)));
    }

    ship2Row--;
    ship2Col--;

    //if the ship's coordinates is already taken, it prompts the user to keep on entering valid coordinates

    if (board[ship2Row][ship2Col] != ' '){
        do{
            printf("That spot is taken\n");
            printf("Enter the row and column of your second ship separated by a space(1-5): ");
            scanf("%d%d",&ship2Row,&ship2Col);
            ship2Row--;
            ship2Col--;
            
        } while(board[ship2Row][ship2Col] != ' ');
    }

    //if the spot the user wants to place the ship is open, a 'P' is placed

    if (board[ship2Row][ship2Col] == ' ') {
        player1Board[ship2Row][ship2Col] = 'P';
        board[ship2Row][ship2Col] = 'P';
    }


    printf("\n");


    //      THIRD SHIP      //


    printf("Enter the row and column of your third ship separated by a space: ");
    scanf("%d%d",&ship3Row,&ship3Col);

    //if the ship's location that the user entered isn't a spot on the board it is invalid


    if ((ship3Row > 5 || ship3Row < 1) || (ship3Col > 5 || ship3Col < 1)){
        printf("That isn't a valid option\n");

        do{
            printf("Enter the row and column of your third ship separated by a space(1-5): ");
            scanf("%d%d",&ship3Row,&ship3Col);

        }while(((ship3Row > 5 || ship3Row < 1) || (ship3Col > 5 || ship3Col < 1)));
    }

    ship3Row--;
    ship3Col--;

    //if the ship's coordinates is already taken, it prompts the user to keep on entering valid coordinates

    if (board[ship3Row][ship3Col] != ' '){
        do{
            printf("That spot is taken\n");
            printf("Enter the row and column of your third ship separated by a space(1-5): ");
            scanf("%d%d",&ship3Row,&ship3Col);
            ship3Row--;
            ship3Col--;
            
        }while(board[ship3Row][ship3Col] != ' ');
    }

    //if the spot the user wants to place the ship is open, a 'P' is placed

    if (board[ship3Row][ship3Col] == ' ') {
        player1Board[ship3Row][ship3Col] = 'P';
        board[ship3Row][ship3Col] = 'P';
    }

}

//  FUNCTION THAT GETS THE SECOND PLAYER TO PLACE THEIR SHIPS   //

void player2Ships(){

    int ship1Row, ship1Col, ship2Row, ship2Col, ship3Row ,ship3Col;

    //      FIRST SHIP      //


    printf("Enter the row and column of your first ship separated by a space(1-5): ");
    scanf("%d%d",&ship1Row,&ship1Col);

    printf("\n");

    //if the ship's location that the user entered isn't a spot on the board it is invalid

    if ((ship1Row > 5 || ship1Row < 1) || (ship1Col > 5 || ship1Col < 1)){
        printf("That isn't a valid option\n");
        do{
            printf("Enter the row and column of your first ship separated by a space(1-5): ");
            scanf("%d%d",&ship1Row,&ship1Col);

        }while(((ship1Row > 5 || ship1Row < 1) || (ship1Col > 5 || ship1Col < 1)));
    }

    ship1Row--;
    ship1Col--;

    //if the spot the user wants to place the ship is open, a 'P' is placed

    if (board[ship1Row][ship1Col] == ' ') {
        board[ship1Row][ship1Col] = 'U';
        player2Board[ship1Row][ship1Col] = 'U';
    }


    //      SECOND SHIP      //


    printf("Enter the row and column of your second ship separated by a space: ");
    scanf("%d%d",&ship2Row,&ship2Col);

    //if the ship's location that the user entered isn't a spot on the board it is invalid

    if ((ship2Row > 5 || ship2Row < 1) || (ship2Col > 5 || ship2Col < 1)){
        printf("That isn't a valid option\n");

        do{
            printf("Enter the row and column of your second ship separated by a space(1-5): ");
            scanf("%d%d",&ship2Row,&ship2Col);

        }while(((ship2Row > 5 || ship2Row < 1) || (ship2Col > 5 || ship2Col < 1)));
    }

    ship2Row--;
    ship2Col--;

    //if the ship's coordinates is already taken, it prompts the user to keep on entering valid coordinates

    if (board[ship2Row][ship2Col] != ' '){
        do{
            printf("That spot is taken\n");
            printf("Enter the row and column of your second ship separated by a space(1-5): ");
            scanf("%d%d",&ship2Row,&ship2Col);
            ship2Row--;
            ship2Col--;
            
        } while(board[ship2Row][ship2Col] != ' ');
    }

    //if the spot the user wants to place the ship is open, a 'P' is placed

    if (board[ship2Row][ship2Col] == ' ') {
        player2Board[ship2Row][ship2Col] = 'U';
        board[ship2Row][ship2Col] = 'U';
    }


    printf("\n");


    //      THIRD SHIP      //


    printf("Enter the row and column of your third ship separated by a space: ");
    scanf("%d%d",&ship3Row,&ship3Col);

    //if the ship's location that the user entered isn't a spot on the board it is invalid


    if ((ship3Row > 5 || ship3Row < 1) || (ship3Col > 5 || ship3Col < 1)){
        printf("That isn't a valid option\n");

        do{
            printf("Enter the row and column of your third ship separated by a space(1-5): ");
            scanf("%d%d",&ship3Row,&ship3Col);

        }while(((ship3Row > 5 || ship3Row < 1) || (ship3Col > 5 || ship3Col < 1)));
    }

    ship3Row--;
    ship3Col--;

    //if the ship's coordinates is already taken, it prompts the user to keep on entering valid coordinates

    if (board[ship3Row][ship3Col] != ' '){
        do{
            printf("That spot is taken\n");
            printf("Enter the row and column of your third ship separated by a space(1-5): ");
            scanf("%d%d",&ship3Row,&ship3Col);
            ship3Row--;
            ship3Col--;
            
        }while(board[ship3Row][ship3Col] != ' ');
    }

    //if the spot the user wants to place the ship is open, a 'P' is placed

    if (board[ship3Row][ship3Col] == ' ') {
        player2Board[ship3Row][ship3Col] = 'U';
        board[ship3Row][ship3Col] = 'U';
    }

}


//  FUNCTION THAT GETS THE COMPUTER TO PLACE RANDOM SHIPS   //

void computerShips(){
    srand(time(0));
    //while loop that goes 3 times to get 3 different ship locations
    int i = 0;
    while (i < 3) {
        int row = rand() % 5;
        int col = rand() % 5;
        if (computerBoard[row][col] != 'C') {
            computerBoard[row][col] = 'C';
            i++;
        }
    }
}

//  FUNCTION THAT PROMPTS THE FIRST PLAYER TO GUESS THE SHIPS LOCATION  //

char player1Guess(){ //returns W if player guessed the computer's or player 2's ship location
    int x,y; //variables for row and column
    bool alreadyGuessed = false; //variable to store whether the computer has already guessed the spot


    do {
        printf("***** PLAYER 1 *****\n");
        printf("Guess the location of player 2 or the computer's ships(ROW then COLUMN(1-5)): ");
        scanf("%d%d",&x,&y);


        /*for loop that checks to see if the player has already guessed that space. If they have, the loop breaks and 
        already guessed is set to true, meaning the player already guessed that space.
        */
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                if (((player1Guesss[i][j] == '$') || player1Guesss[i][j] == 'W') && i == x-1 && j == y-1){
                    alreadyGuessed = true;
                    printf("You have already selected that location\n");
                    break;
                }
            }
        }
        
        if (!alreadyGuessed){ //if already guessed is false, that means that the user hasn't selected that spot yet and is able to place an $ or W

            if ((x > 5 || x < 1) || (y > 5 || y < 1)){
                printf("That isn't a valid option\n");

                do{
                    printf("Guess the location of the computer's ships(ROW then COLUMN(1-5)): ");
                    scanf("%d%d",&x,&y);

                }while(((x > 5 || x < 1) || (y > 5 || y < 1)));
            }

            x--;
            y--;

            //If the player correctly guessed where the Ai's ship is

            if (player2Board[x][y] == 'U' || computerBoard[x][y] == 'C'){
                printf("Player 1 HIT!!!\n");
                board[x][y] = 'W'; //replaces the board location with a W to symbolize a hit ship
                player1Guesss[x][y] = 'W'; //player guess board gets a W
                player1Board[x][y] = 'W'; //player's board also gets a W
                totalGuess[x][y] = 'W';
                return board[x][y];
            }

            //If the player misses the AI's ship

            else {

                printf("Player 1 MISSED!\n");

                //if the place the player guessed is a spot where their own ship stays, they get asked if they want to keep the P or replace it with $

                if (board[x][y] == 'P'){        
                    printf("However, you guessed a spot on the board where one of your ships are. Would you like to place an '$' over it?(y/n): ");
                    char choice; // variable that asks the user if they want to put a '$' over where one of their ships are
                    scanf(" %c", &choice);
                    if (choice == 'y') {
                        board[x][y] = '$';
                        totalGuess[x][y] = '$';
                        return '$';
                    }
                }
                //if the user guessed a spot where they previously guessed
                else if (player1Guesss[x][y] == 'W' || player1Guesss[x][y] == '$'){
                    do {
                        printf("You already guessed there. Please guess again: ");
                        scanf("%d%d",&x,&y);
                        x--;
                        y--;

                        if (board[x][y] != 'W' && board[x][y] != '$'){
                            board[x][y] = '$';
                            totalGuess[x][y] = '$';
                            break;
                        }

                    } while (board[x][y] == 'W' || board[x][y] == '$');
                    return '$';
                }
                //if the player already guessed a spot the computer guessed, the '!' gets replaced with a '$' 
                else if (board[x][y] == '!'){
                    board[x][y] = '$';
                    totalGuess[x][y] = '$';
                    return '$';
                }
                else {
                    //a '$' is placed to signify a miss
                    board[x][y] = '$';
                    totalGuess[x][y] = '$';
                    return '$';
                }

                player1Guesss[x][y] = '$';
                totalGuess[x][y] = '$';
                return '$';

            }
        }

        else{ //if the computer has already guessed this spot, reset alreadyGuessed to false and try again
            alreadyGuessed = false;
        }

    }while (true);

}



//  FUNCTION THAT PROMPTS THE SECOND PLAYER TO GUESS THE SHIPS LOCATION  //

char player2Guess(){ //returns H if player 2 guessed player 1's ship location
    int x,y; //variables for row and column
    bool alreadyGuessed = false; //variable to store whether player 2 has already guessed the spot


    do {
        printf("***** PLAYER 2 *****\n");
        printf("Guess the location of the first player's ships(ROW then COLUMN(1-5)): ");
        scanf("%d%d",&x,&y);


        /*for loop that checks to see if the player has already guessed that space. If they have, the loop breaks and 
        already guessed is set to true, meaning player 1 already guessed that space.
        */
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                if (((player2Guesss[i][j] == '!') || player2Guesss[i][j] == 'H') && i == x-1 && j == y-1){
                    alreadyGuessed = true;
                    printf("You have already selected that location\n");
                    break;
                }
            }
        }
        
        if (!alreadyGuessed){ //if already guessed is false, that means that the user hasn't selected that spot yet and is able to place an $ or W

            if ((x > 5 || x < 1) || (y > 5 || y < 1)){
                printf("That isn't a valid option\n");

                do{
                    printf("Guess the location of the computer's ships(ROW then COLUMN(1-5)): ");
                    scanf("%d%d",&x,&y);

                }while(((x > 5 || x < 1) || (y > 5 || y < 1)));
            }

            x--;
            y--;

            //If the player correctly guessed where the computer's or player 2's ship is

            if (player1Board[x][y] == 'P'){
                printf("Player 2 HIT!!!\n");
                board[x][y] = 'H'; //replaces the board location with a H to symbolize a hit ship
                player2Guesss[x][y] = 'H'; //player guess board gets a H
                player2Board[x][y] = 'H'; //player's board also gets a H
                totalGuess[x][y] = 'H';
                return board[x][y];
            }

            //If the player misses the AI's ship

            else {

                printf("Player 2 MISSED!\n");

                //if the place player 2 guessed is a spot where their own ship stays, they get asked if they want to keep the U or replace it with !

                if (player2Board[x][y] == 'U'){        
                    printf("However, you guessed a spot on the board where one of your ships are. Would you like to place an '!' over it?(y/n): ");
                    char choice; // variable that asks player 2 if they want to put a '!' over where one of their ships are
                    scanf(" %c", &choice);
                    if (choice == 'y') {
                        board[x][y] = '!';
                        totalGuess[x][y] = '!';
                        return '!';
                    }
                }
                //if the user guessed a spot where they previously guessed
                else if (player2Guesss[x][y] == 'H' || player2Guesss[x][y] == '!'){
                    do {
                        printf("You already guessed there. Please guess again: ");
                        scanf("%d%d",&x,&y);
                        x--;
                        y--;

                        if (board[x][y] != 'H' && board[x][y] != '!'){
                            board[x][y] = '!';
                            break;
                        }

                    } while (player2Board[x][y] == 'H' || player2Board[x][y] == '!');
                    return '!';
                }
                //if the second player already guessed a spot the first player guessed, the '!' gets replaced with a 'B' symbolizing both players guessed that spot 
                else if (player1Guesss[x][y] == '$'){
                    board[x][y] = 'B';
                    totalGuess[x][y] = 'B';
                    return 'B';
                }
                else {
                    //a '!' is placed to signify a miss
                    board[x][y] = '!';
                    totalGuess[x][y] = '!';
                    return '!';
                }

                player2Guesss[x][y] = '!';
                totalGuess[x][y] = '!';
                return '!';

            }
        }

        else{ //if the first player has already guessed this spot, reset alreadyGuessed to false and try again
            alreadyGuessed = false;
        }

    }while (true);

}



char computerGuess(){
    int rowGuess, colGuess; //variables to store the computer's guess
    bool alreadyGuessed = false; //variable to store whether the computer has already guessed the spot
    //char result; //variable to store the result of the computer's guess

    do{
        rowGuess = rand() % 5; //generates a random number between 0 and 4 for the row
        colGuess = rand() % 5; //generates a random number between 0 and 4 for the column

        // Check if the computer has already guessed this spot
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < 5; j++){
                if (((computerGuesss[i][j] == '!') || (computerGuesss[i][j] == 'L')) && i == rowGuess && j == colGuess){
                    alreadyGuessed = true;
                    break;
                }
            }
        }

        // If the computer has not already guessed this spot, check if it's a hit or miss
        if (!alreadyGuessed){
            if (player1Board[rowGuess][colGuess] == 'P'){ //if the computer hit a player's ship
                printf("The computer HIT!!!\n");
                printf("The computer guessed [%d,%d]\n",rowGuess+1,colGuess+1);
                board[rowGuess][colGuess] = 'L'; //mark it as a hit on the player's board
                computerGuesss[rowGuess][colGuess] = 'L'; //mark it as a hit on the computer's board
                return 'L'; //set result to 'L'
                break;
            }
            else{ //if the computer missed
                printf("The computer MISSED!!\n");
                printf("The computer guessed [%d,%d]\n",rowGuess+1,colGuess+1);
                

                if (board[rowGuess][colGuess] == 'W'){
                    return '!';
                }

                //if the board is empty, the spot gets occupied by a '!'
                if (board[rowGuess][colGuess] == ' '){
                    board[rowGuess][colGuess] = '!';
                    computerGuesss[rowGuess][colGuess] = '!';
                    return '!';
                }

                
                //If the computer guesses a spot where their ship is, replace it on the game board with '!'
                if (computerBoard[rowGuess][colGuess] == 'C'){
                    board[rowGuess][colGuess] = '!';
                    return '!';
                }

                //board[rowGuess][colGuess] = '!'; //mark it as a miss on the player's board
                computerGuesss[rowGuess][colGuess] = '!'; //mark it as a guess on the computer's board
                return '!';
            }
        }
        else{ //if the computer has already guessed this spot, reset alreadyGuessed to false and try again
            alreadyGuessed = false;
        }
    } while (true);

}


void printPlayerVsPlayerBoard(){
    for (int i = 0; i < 5; i++){
            printf(" %c | %c | %c | %c | %c\n",totalGuess[i][0],totalGuess[i][1],totalGuess[i][2],totalGuess[i][3],totalGuess[i][4]);//prints whatever the value is at that array index
            printf("---|---|---|---|---\n");
        }

}

void printStars(){
    for (int i = 0; i < 50;i++){
        printf("*");
    }
    printf("\n");
}