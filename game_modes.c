#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "game_modes.h"
#include "game_functions.h"
#include "clear_functions.h"

/*  The time attack mode is to time the player against the time when they trying to guess a word that was randomly selected
    the player will lose if they are unable to guess the word correctly before the fixed time limit ends (4 minutes)
    or the player will lose if they lose their all of their lives even before the time ends
 
    @parameter chosen_word: is a string of the word that is needed to be guessed by the player
               hidden_word: is a string that is the player that need to guess and will updated the guess letter into this string
               guessed_letters: array of character which is the letters that the players had guessed
               lives: pointer to the players' lives
               word_len: the length of the word that is going to be guessed
               scores: pointer to the scores of the player
    @return nothing is returned as this is a time attack mode, it will keep on looping while the time and lives is not 0*/
void time_attack_mode(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *scores){
    time_t start_time, current_time;
    /*4 minutes (360 seconds) for the player to guess the word in this time attack mode*/
    int time_left, fixed_time_limits = 360;

    /*Record start time*/
    start_time = time(NULL);

    while (*lives > 0) {
        printf("Guess the word: %s\n", hidden_word);
        player_input(chosen_word, hidden_word, guessed_letters, lives, word_len, scores);

        /*Check current time*/
        current_time = time(NULL);
        /*Calculate the time the player has left*/
        time_left = fixed_time_limits - (int)difftime(current_time, start_time);

        /*Checking if the player time exceed the game time, if it exceeds, Time's up*/
        if(time_left > 0) {
            printf("You still have %d seconds left!\n", time_left);
     
        } else {
            /*Printing out the remaining time left for the player*/
            printf("Time's up! You didn't guess the word in time.\n");
            break;
        }

        /*Checking if the word guessed and the chosen word match to know if the player wins or not*/
        if (strcmp(chosen_word, hidden_word) == 0) {
            printf("Congratulations! You've guessed the word: %s\n", chosen_word);
            break;
        }
    }

    /*Checking if player has enough lives to play with*/
    if (*lives <= 0) {
        printf("Out of lives! The word was: %s\n", chosen_word);
    }
}

void enter_name(char name[]) {
    printf("Enter your name: ");
    fgets(name, MAX_WORD_LENGTH, stdin);
    name[strcspn(name, "\n")] = '\0';
}

/*  In multiplayer mode, two players alternate turns to guess letters of a hidden word. Each player starts
    with a predetermined number of lives and scores, both initialized to zero at the start of the game. The 
    game continues until one of the players runs out of lives or correctly guesses the word.
    
    @param: nothing
    @return: nothing
*/
void multiplayer_mode(void) {
    char guessed_letters[MAX_WORD_LENGTH] = "";
    char hidden_word[MAX_WORD_LENGTH];
    char chosen_word[MAX_WORD_LENGTH];
    Player player1, player2;
    int turn = 1;

    printf("Ready Player 1?\n");
    enter_name(player1.name);
    printf("Ready Player 2?\n");
    enter_name(player2.name);
    player1.lives = player2.lives = MAX_GUESSES;
    player1.score = player2.score = 0;

    strcpy(chosen_word, "star"); /* Easy Level */

    strcpy(guessed_letters, "");

    memset(hidden_word, '_', strlen(chosen_word));
    hidden_word[strlen(chosen_word)] = '\0';

    printf("\n\nLevel 1\n\n");

    while (player1.lives > 0 && player2.lives > 0) {
        Player *current_player = (turn == 1) ? &player1 : &player2;
        printf("\n%s's turn\n\n", current_player->name);
        printf("Hidden Word: %s\n", hidden_word);
        printf("Guessed Letters: %s\n", guessed_letters);

        player_input(chosen_word, hidden_word, guessed_letters, &(current_player->lives), strlen(chosen_word), &(current_player->score));

        if (strcmp(hidden_word, chosen_word) == 0) {
            printf("\nCongratulations, %s! You guessed the word.\n", current_player->name);
            break;
        }

        turn = (turn == 1) ? 2 : 1;
    }

    if (player2.lives <= 0) {
        printf("\n%s is out of lives. Game Over!\n", player1.name);
    }

    printf("\nFinal Scores:\n");
    printf("%s's Score: %d\n", player1.name, player1.score);
    printf("%s's Score: %d\n", player2.name, player2.score);
}

