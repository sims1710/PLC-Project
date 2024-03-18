/* Track guesses and lives, check player input. This function is run in main in a while loop with lives */
#include <string.h>
#include <stdio.h>
#include "all_functions.h"
/* Steps
1a. Get input from player
1b. Check if input has not already been guessed and is valid.
2. Check if input exists in chosen
3. If exists, run update hidden, else -1 lives
4. Function ends
*/

void player_input(char *chosen_word, char *guessed_letters, int *lives)
{
    int correct_guess = 0;
    size_t length = strlen(chosen_word);

    if (*lives > 0)
    {
        for (int j = 0; guessed_letters[j] != '\0'; j++)
        {
            char guess = guessed_letters[j];
            int found = 0;

            for (int i = 0; i < length; i++)
            {
                if (guess == chosen_word[i])
                {
                    found = 1;
                    correct_guess = 1;
                }
            }

            if (!found)
            {
                (*lives)--;
                break;
            }
        }

        if (!correct_guess)
        {
            printf("Incorrect guess. You have %d lives left.\n", *lives);
        }
        else
        {
            printf("Good guess!\n");
        }
    }

    else if (*lives <= 0)
    {
        printf("You lose!\n");
    }
}
