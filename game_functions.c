#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include "game_functions.h"

typedef enum{
    START,
    CHECK_LETTER,
    UPDATE_LETTER,
    CONTINUE_SEARCH,
    END
}State;

/* Retrieve word from file */
char *get_word(chosen_difficulty *file_set)
{
    FILE *fptr;
    char *word_count;
    char *buffer;
    char *chosen_word;
    int index, iterate;
    /* Open file */
    fptr = fopen(file_set->filename, "r");
    /* Get number of words from first line, shift pointer to first word */
    fgets(word_count, 100, fptr);
    /* Change random seed using time function */
    srand(time(NULL));
    /* Get random int to get */
    index = rand() % (int)*word_count;
    iterate = 0;
    while (fgets(buffer, 100, fptr))
    {
        if (iterate == index)
        {
            /* Might need to redo this part */
            fgets(chosen_word, 100, fptr);
            break;
        }
        iterate++;
    }
    fclose(file_set->filename);
    return chosen_word;
}

/* Track guesses and lives, check player input. This function is run in main in a while loop with lives */
/* Steps
1a. Get input from player
1b. Check if input has not already been guessed and is valid.
2. Check if input exists in chosen
3. If exists, run update hidden, else -1 lives
4. Function ends
*/
void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *score)
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
            (*score)++; // Increment score for correct guess
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

/* This function is to update the pointer for the hidden word display
   Using the State struct to keep track of the letter guessed by the player
   this function will end (when reach the END state) when all of the letters have been checked
   and it will check the input letter when it reach the CHECK_LETTER state 
   
   @param hidden_word: is a string that is the player that need to guess and will updated the guess letter into this string
          chosen_word: is a string which is the word that the player need to guess and will be used to check against hidden_word
          input_letter: is a character that the player inputs
   @return return nothing because it is updating the hidden_word string character upon successful guess*/
void update_hidden_word(char *hidden_word, char *chosen_word, char input_letter)
{
    State currentState = START;
    int i = 0;
    int length = strlen(chosen_word); 

    while (currentState != END) {
        switch (currentState) {
            case START:
                i = 0; 
                currentState = CHECK_LETTER;
                break;
            case CHECK_LETTER:
                if (i >= length) {
                    /*End if all letters have been checked*/
                    currentState = END; 
                } else if (chosen_word[i] == input_letter) {
                    /*Match found, update the letter*/
                    currentState = UPDATE_LETTER; 
                } else {
                    /*No match, move to the next letter*/
                    currentState = CONTINUE_SEARCH; 
                }
                break;
            case UPDATE_LETTER:
                /*Update the hidden word with the input letter*/
                hidden_word[i] = input_letter; 
                /*Continue search after updating*/
                currentState = CONTINUE_SEARCH; 
                break;
            case CONTINUE_SEARCH:
                i++; 
                /*Check the next letter*/
                currentState = CHECK_LETTER; 
                break;
            case END:
                /*Exit the loop*/
                break;
        }
    }
}

