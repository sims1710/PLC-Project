/* Track guesses and lives, check player input */
#include <string.h>
#include <stdio.h>
#include "all_functions.h"

void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives)
{
    int correct_guess = 0;
    size_t length = strlen(chosen_word);

    if(*lives>0){
        for (int j = 0; guessed_letters[j] != '\0'; j++) {
            char guess = guessed_letters[j];
            int found = 0;

            for (int i = 0; i < length; i++) {
                if (guess == chosen_word[i]) {
                    found = 1;
                    correct_guess = 1;
                }
            }

            if (!found) {
                (*lives)--; 
                break; 
            }
        }

        if (!correct_guess) {
            printf("Incorrect guess. You have %d lives left.\n", *lives);
        } else {
            printf("Good guess!\n");
        }
    }

    else if(*lives<=0){
        printf("You lose!\n");
    }
}
