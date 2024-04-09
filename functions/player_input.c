/* Track guesses and lives, check player input. This function is run in main in a while loop with lives */
#include <string.h>
#include <stdio.h>
#include "all_functions.h"
#include <time.h>

/* Steps
1a. Get input from player
1b. Check if input has not already been guessed and is valid.
2. Check if input exists in chosen
3. If exists, run update hidden, else -1 lives
4. Function ends
*/

/* guessed letter is a malloc of 26 char */

/* Initialize the FSM with the target letter, as in Task 2. */
void initCheatFSM(CheatsFSM *cheatFsm, char* hintCheat, char* liveCheat) {
    cheatFsm->current = NOCHEAT;
    cheatFsm->hintsCheatCode = hintCheat;
    cheatFsm->livesCheatCode = liveCheat;
}

void processCheatChoice(CheatsFSM *cheatFsm, char * input, char * chosen_word, int * lives) {
    switch(cheatFsm->current){
    	case NOCHEAT:
            if(input == cheatFsm->hintsCheatCode){
                cheatFsm->current = CHEAT;
                printf("%s", chosen_word);                
            }
            else if(input == cheatFsm->livesCheatCode){
                cheatFsm->current = CHEAT;
                lives = MAX_LIVES;
            }
            cheatFsm->current = NOCHEAT;
            break;
	}	
}

void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *score)
{
    char input_letter;
    int valid, match, i;
    char * hintCheat, liveCheat, full_input;
    CheatsFSM cheatFsm;
    valid = 0;


    hintCheat = "HINTSALL";
    liveCheat = "LIVEFULL";
    fgets(full_input, sizeof(char) * 10, stdin);
    initCheatFSM(&cheatFsm, hintCheat, liveCheat);
    processCheatChoice(&cheatFsm, full_input, chosen_word, lives);


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

// void cheats(){
//     fgets(input, sizeof(input), stdin);
// }
