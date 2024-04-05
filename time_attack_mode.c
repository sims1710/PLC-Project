#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "all_functions.h"

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
    int i;
    time_t start_time, current_time, time_left;
    /*4 minutes (360 seconds) for the player to guess the word in this time attack mode*/
    time_t fixed_time_limits = 360;

    /*Record start time*/
    time(&start_time); 

    while (lives > 0) {
        printf("Guess the word: %s\n", hidden_word);
        player_input(chosen_word, hidden_word, guessed_letters, &lives, word_len, scores);

        /*Check current time*/
        time(&current_time); 
        /*Calculate the time the player has left*/
        time_left = fixed_time_limits - difftime(current_time, start_time);

        /*Checking if the player time exceed the game time, if it exceeds, Time's up*/
        if(time_left > 0) {
            printf("You still have %s time left!", ctime(&time_left));
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
    if (lives <= 0) {
        printf("Out of lives! The word was: %s\n", chosen_word);
    }
}
