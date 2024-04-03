#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "all_functions.h"

void time_attack_mode(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len){
    int i;
    time_t start_time, current_time, time_left;
    /*4 minutes (360 seconds) for the player to guess the word in this time attack mode*/
    time_t fixed_time_limits = 360;

    /*Record start time*/
    time(&start_time); 

    while (lives > 0) {
        printf("Guess the word: %s\n", hidden_word);
        player_input(chosen_word, hidden_word, guessed_letters, &lives, word_len);

        time(&current_time); /*Check current time*/
        /*Printing out the remaining time left for the player*/
        if(difftime(current_time, start_time) < fixed_time_limits) {
            time_left = fixed_time_limits - current_time;
            printf("You still have %s time left!", ctime(&time_left));
        }

        /*Checking if the player time exceed the game time, if it exceeds, Time's up*/
        if (difftime(current_time, start_time) > fixed_time_limits) {
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
