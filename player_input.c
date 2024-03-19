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

/* guessed letter is a malloc of 26 char */

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

void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len)
{
    char input_letter;
    int valid, match, i;
    valid = 0;
    while (valid == 0)
    {
        /* Get single char as user input */
        input_letter = fgetc(stdin);
        /* clear stdin */
        clear_stdin();
        /* Case converter */
        if (input_letter >= 'A' && input_letter <= 'Z')
        {
            input_letter = (char)((int)input_letter + 32);
        }
        /* Validity check */
        if (input_letter >= 'a' && input_letter <= 'z')
        {
            valid = 1;
            i = 0;
            while (guessed_letters != '\0')
            {
                if (input_letter == guessed_letters[i])
                {
                    valid = 0;
                }
                i++;
            }
        }
        else
        {
            printf("Invalid Input. Please enter a letter of the alphabet, preferably lowercase.");
        }
    }
    /* Check if letter in word and act on it */
    match = 0;
    for (i = 0; i < word_len; i++)
    {
        if (input_letter == chosen_word[i])
        {
            match = 1;
            update_hidden_word(hidden_word, chosen_word, input_letter);
        }
    }
    /* Response to match */
    switch (match)
    {
    case 0:
        /* No match, minus lives */
        lives = *lives - 1;
        break;
    case 1:
        /* Match found, no action */
        break;
    default:
        printf("You should not see this message.");
        break;
    }
    /* TODO: Add input into guessed letters */
    guessed_letters[input_letter - 'a'] = input_letter;
}