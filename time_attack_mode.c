#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "all_functions.h"

void time_attack_mode(char *chosen_word, int time_limit_seconds){
    int i;
    time_t start_time, current_time;
    int lives = 5;
    int word_len = strlen(chosen_word);
    char *hidden_word = malloc(word_len + 1);
    char *guessed_letters = malloc(26); /*Allocate space for each letter of the alphabet*/

    /*Check if memory allocation was successful*/
    if (hidden_word == NULL || guessed_letters == NULL) {
        fprintf(stderr, "Failed to allocate memory.\n");
        free(hidden_word); 
        free(guessed_letters); 
        return;
    }

    /*Initialize hidden_word with underscores or a similar placeholder*/
    for (i = 0; i < word_len; ++i) {
        hidden_word[i] = '_';
    }
    hidden_word[word_len] = '\0';

    /*Initialize guessed_letters to 0 to track which letters have been guessed*/
    memset(guessed_letters, 0, 26 * sizeof(char));

    time(&start_time); /*Record start time*/

    while (lives > 0) {
        printf("Guess the word: %s\n", hidden_word);
        player_input(chosen_word, hidden_word, guessed_letters, &lives, word_len);

        time(&current_time); /*Check current time*/
        if (difftime(current_time, start_time) > time_limit_seconds) {
            printf("Time's up! You didn't guess the word in time.\n");
            break;
        }

        if (strcmp(chosen_word, hidden_word) == 0) {
            printf("Congratulations! You've guessed the word: %s\n", chosen_word);
            break;
        }
    }

    if (lives <= 0) {
        printf("Out of lives! The word was: %s\n", chosen_word);
    }

    /*Free the dynamically allocated memory*/
    free(hidden_word);
    free(guessed_letters);
}
