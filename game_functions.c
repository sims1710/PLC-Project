#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game_functions.h"
#include "leaderboard.h"
#include "clear_functions.h"

typedef enum
{
    START,
    CHECK_LETTER,
    UPDATE_LETTER,
    CONTINUE_SEARCH,
    END
} State;

/* The cheat codes features are not implemented
typedef enum
{
    NOCHEAT,
    CHEAT
} Cheats;

typedef struct
{
    Cheats current;
    char *hintsCheatCode;
    char *livesCheatCode;
} CheatsFSM;
*/

/* Configures the difficulty level for a word-guessing game by allowing the user to select a difficulty level.
   This function prompts the user to choose from predefined difficulty levels, each corresponding to different 
   word lengths. Upon a valid choice, it updates the game_levels structure with the appropriate file path for
   the word list and the expected word length for the selected difficulty.
 
   @param: game_levels: A pointer to a game_level struct that holds game state information including the selected 
                        difficulty, the file name from which to read words, and the word length to be used in the game.
    @return: nothing           
*/
void choose_difficulty(game_level *game_levels)
{
    char difficulty;
    int rletter, valid;

    printf("The following difficulties are available: \nEasy: 4-5 letter words \nMedium: 4-6 letter words \nHard: 5-7 letter words \n");
    printf("Please choose a difficulty. \n - 1: Easy \n - 2: Medium\n - 3: Hard\n");

    valid = 0;
    while (valid == 0)
    {
        difficulty = fgetc(stdin);
        if (difficulty > '0' && difficulty < '4')
        {
            valid = 1;
        }
        else
        {
            printf("Error: user input is not 1, 2, or 3. Please try again.\n");
        }
    }
    /*Clear input stream here for cleanliness*/
    clear_stdin();

    /*Change random's seed using time function*/
    srand(time(NULL));

    /*Store the chosen difficulty in the GameLevels struct*/
    game_levels->difficulty = difficulty - '0';

    /*Calculate the word length based on difficulty chosen*/
    switch (game_levels->difficulty)
    {
    case 1:
        rletter = rand() % 2;
        break;
    case 2:
        rletter = rand() % 3;
        break;
    case 3:
        rletter = (rand() % 3) + 1;
        break;
    }

    /*Assign the filename based on the random letter count*/
    switch (rletter)
    {
    case 0:
        game_levels->chosenDiff.filename = "./letter_textfiles/4letter.txt";
        break;
    case 1:
        game_levels->chosenDiff.filename = "./letter_textfiles/5letter.txt";
        break;
    case 2:
        game_levels->chosenDiff.filename = "./letter_textfiles/6letter.txt";
        break;
    case 3:
        game_levels->chosenDiff.filename = "./letter_textfiles/7letter.txt";
        break;
    }
    game_levels->chosenDiff.word_len = rletter + 4;
}

/*  this function is to update the level that the player is currently in based on the difficulty mode and determine the sequence of words to be guessed
    for easy mode: first 12 words to be guessed are 4 letters and the 8 words to be guessed are 5 letters
    for medium mode: first 8 words are 4 letters, 6 words next are 5 letters and 6 words next are 6 letters
    for hard mode: first 6 words are 5 letters, next 6 words are 6 letters and next 8 words are 7 letters

    @param game_levels: is the game_level structure which stores the current level and difficulty
    @return nothing because the function is only updating the current level
*/
void update_game_level(game_level *game_levels)
{
    int level;

    /*Increase current_level*/
    game_levels->current_level++;

    /*Determine the word length based on the current level and difficulty*/
    level = game_levels->current_level;
    switch (game_levels->difficulty)
    {
    case 1: /*Easy*/
        if (level <= 12)
        {
            game_levels->chosenDiff.filename = "./letter_textfiles/4letter.txt";
            game_levels->chosenDiff.word_len = 4;
        }
        else
        {
            game_levels->chosenDiff.filename = "./letter_textfiles/5letter.txt";
            game_levels->chosenDiff.word_len = 5;
        }
        break;
    case 2: /*Medium*/
        if (level <= 8)
        {
            game_levels->chosenDiff.filename = "./letter_textfiles/4letter.txt";
            game_levels->chosenDiff.word_len = 4;
        }
        else if (level <= 14)
        {
            game_levels->chosenDiff.filename = "./letter_textfiles/5letter.txt";
            game_levels->chosenDiff.word_len = 5;
        }
        else
        {
            game_levels->chosenDiff.filename = "./letter_textfiles/6letter.txt";
            game_levels->chosenDiff.word_len = 6;
        }
        break;
    case 3: /*Hard*/
        if (level <= 6)
        {
            game_levels->chosenDiff.filename = "./letter_textfiles/5letter.txt";
            game_levels->chosenDiff.word_len = 5;
        }
        else if (level <= 12)
        {
            game_levels->chosenDiff.filename = "./letter_textfiles/6letter.txt";
            game_levels->chosenDiff.word_len = 6;
        }
        else
        {
            game_levels->chosenDiff.filename = "./letter_textfiles/7letter.txt";
            game_levels->chosenDiff.word_len = 7;
        }
        break;
    default:
        printf("Invalid difficulty level\n");
    }
}

/* Retrieves a random word from a specified file and assigns it to the chosen_word variable. The word is selected based on a random index, 
   which is determined by the total number of words listed in the first line of the file. The function ensures that the word consists only 
   of lowercase letters and matches the specified length from the chosen_difficulty structure.
 
  @param:
    - file_set: A pointer to a chosen_difficulty struct that contains information about the word length and the filename from which the 
      word should be retrieved.
    - chosen_word: A pointer to a character array where the chosen word will be stored. The function reallocates this pointer to match 
      the required word length.
  @return: nothing
*/
void get_word(chosen_difficulty *file_set, char *chosen_word)
{
    FILE *fptr;
    int index, iterate, i, flag;
    char *word_count = (char *)malloc(sizeof(char) * 100); /*temporary allocation*/
    char *buffer = (char *)malloc(sizeof(char) * 100);
    chosen_word = (char *)realloc(chosen_word, sizeof(char) * ((file_set->word_len) + 1));

    flag = 0;

    if (!word_count || !buffer || !chosen_word)
    {
        fprintf(stderr, "Memory allocation failed\n");
        /*free(word_count);*/
        free(buffer);
        free(chosen_word);
    }

    /* Open file */
    fptr = fopen(file_set->filename, "r");
    if (fptr == NULL)
    {
        fprintf(stderr, "Failed to open file %s\n", file_set->filename);
    }
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
            for(i=0; i<file_set->word_len;i++){
                if (buffer[i] < 'a' || buffer[i] > 'z'){
                    flag = 1;
                    break;
                }
            }
            if(flag){
                flag = 0;
                continue;
            }

            /* Take from buffer instead */
            strncpy(chosen_word, buffer, file_set->word_len);
            chosen_word[file_set->word_len] = '\0';
            break;
        }
        iterate++;
    }
    fclose(fptr);
    free(word_count);
    free(buffer);
}



/* Track guesses and lives, check player input. This function is run in main in a while loop with lives */
/* Steps
1a. Get input from player
1b. Check if input has not already been guessed and is valid.
2. Check if input exists in chosen
3. If exists, run update hidden, else -1 lives
4. Function ends

  @param:
    - chosen_word: A pointer to the character array holding the word that the player needs to guess.
    - hidden_word: A pointer to the character array that displays the current state of the guessed word, with unguessed
      letters represented by underscores or another placeholder.
    - guessed_letters: A pointer to the character array that stores all letters guessed so far to prevent repeat guesses.
    - lives: A pointer to an integer representing the player's remaining lives. This value is decremented if the player
      makes an incorrect guess.
    - word_len: An integer representing the length of the chosen_word.
    - score: A pointer to an integer representing the player's score. The score is increased by the number of lives left
      for every correct guess.
  @return: nothing
*/
void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *score)
{
    char input_letter;
    int valid, match, i;
    valid = 0;

    while (valid == 0)
    {
        input_letter = fgetc(stdin);
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
            while (guessed_letters[i] != '\0')
            {
                if (input_letter == guessed_letters[i])
                {
                    printf("Invalid Input. You have already guessed this letter.");
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
            *score =+ *lives; /* Increment score for correct guess*/
        }
    }
    /* Response to match */
    switch (match)
    {
    case 0:
        /* No match, minus lives */
        *lives = *lives - 1;
        break;
    case 1:
        /* Match found, no action */
        break;
    default:
        printf("You should not see this message.");
        break;
    }
    /*Add input into guessed letters */
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

    while (currentState != END)
    {
        switch (currentState)
        {
        case START:
            i = 0;
            currentState = CHECK_LETTER;
            break;
        case CHECK_LETTER:
            if (i >= length)
            {
                /*End if all letters have been checked*/
                currentState = END;
            }
            else if (chosen_word[i] == input_letter)
            {
                /*Match found, update the letter*/
                currentState = UPDATE_LETTER;
            }
            else
            {
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

/*  for the hints implementation, link numbers to letters 
    Populates an integer array with unique random numbers from 1 to 26. Each number in the range is used exactly once.
    This function can be used to assign random unique identifiers or to shuffle numbers without repetition.
 
    @params:
    - hint_integer: A pointer to an integer array that must be preallocated with at least 26 integers. This array will
      be filled with the unique numbers. The size of the array should match the number of unique numbers to generate,
      which is defined by ALPHABET_COUNT (assumed to be 26 here).
    @return: nothing
*/
void link_number(int *hint_integer)
{
    int letter_index, tracker_count, number, i, valid;
    int tracker[26];
    tracker_count = 0;
    letter_index = 0;

    while (tracker_count < 26)
    {
        valid = 1;
        number = rand() % 26;
        if (tracker_count != 0)
        {
            for (i = 0; i < tracker_count; i++)
            {
                if (number == tracker[i])
                {
                    valid = 0;
                }
            }
        }
        if (valid == 1)
        {
            tracker[letter_index] = number;
            hint_integer[letter_index] = number + 1;
            letter_index++;
            tracker_count++;
            printf("number: %d /n", number);
        }
    }
}

/* suggest_hint function is to allow players to use 2 hints to guess the letter
   the hints rules are as follows:
       1. First hint used doesn't require points (no point will be deducted from the player)
       2. The second hint require points to be deducted which depends on the player's game difficulty
          The cost of the hint are as follows:
               - easy and medium: 1 point
               - hard: 2 points

   @param  chosen_word: A pointer to the chosen word in the game.
           guessed_letters: A pointer to an array containing guessed letters.
           game_levels: A pointer to the game_level structure containing difficulty information.
           hints_given: A pointer to the number of hints given to the player.
           player_points: A pointer to the player's points.
           hint_integer: A pointer to an integer array containing random numbers linked to letters.
           hint_char: A pointer to a character array where the hint letter will be stored.
*/
void suggest_hint(char *chosen_word, char *guessed_letters, game_level *game_levels, int *hints_given, int *player_points, int *hint_integer, char *hint_char)
{
    int i, hint_cost;
    char current_letter;
    int word_len, letter_found = 0;

    /*Determine the cost of the second hint used based on the difficulty level*/
    hint_cost = (game_levels->difficulty == 3) ? 2 : 1;
    /*Getting the length of the word*/
    word_len = game_levels->chosenDiff.word_len;

    /*Check if hint is available */
    if (*hints_given >= 2)
    {
        printf("No more hints available.\n");
        return;
    }

    /*Check if this is the second hint and if the player has enough points*/
    if (*hints_given == 1 && *player_points < hint_cost)
    {
        printf("Not enough points for a hint.\n");
        return;
    }

    /*Deduct the point for using the hint*/
    if (*hints_given == 1)
    {
        *player_points -= hint_cost;
    }

    /*Find a letter in the word that hasn't been guessed yet and return its associated random number*/
    for (i = 0; i < word_len && !letter_found; i++)
    {
        current_letter = chosen_word[i];
        if (!strchr(guessed_letters, chosen_word[i]))
        {

            if (hint_char[0] == '_')
            {
                hint_char[0] = current_letter;
            }
            else
            {
                hint_char[1] = current_letter;
            }

            (*hints_given)++;
            printf("Hint provided of the hint letter is %c\n", current_letter);
            letter_found = 1;
        }
    }
}

/*keeping track of the players score*/
void score_tracker(int *score, int *lives)
{
    if (*lives == 0)
    {
        printf("You have run out of lives! Your score is %d\n", *score);
    }
    else
    {
        printf("Your score is %d\n", *score);
    }
}

/* The cheat features are not implemented
void initCheatFSM(CheatsFSM *cheatFsm, char *hintCheat, char *liveCheat)
{
    cheatFsm->current = NOCHEAT;
    cheatFsm->hintsCheatCode = hintCheat;
    cheatFsm->livesCheatCode = liveCheat;
}

void processCheatChoice(CheatsFSM *cheatFsm, char *input, char *chosen_word, int *lives)
{
    int cheat1, cheat2, i;
    switch (cheatFsm->current)
    {
    case NOCHEAT:
        cheat1 = 1;
        cheat2 = 1;
        for (i = 0; i < 8; i++)
        {
            if (cheat1)
            {
                if (input[i] != cheatFsm->hintsCheatCode[i])
                {
                    cheat1 = 0;
                }
            }
            if (cheat2)
            {
                if (input[i] != cheatFsm->livesCheatCode[i])
                {
                    cheat2 = 0;
                }
            }
        }
        if (cheat1)
        {
            cheatFsm->current = CHEAT;
            printf("%s", chosen_word);
        }
        else if (cheat2)
        {
            cheatFsm->current = CHEAT;
            *lives = 7;
        }

        break;
    case CHEAT:
        cheat1 = 1;
        cheat2 = 1;
        for (i = 0; i < 8; i++)
        {
            if (cheat1)
            {
                if (input[i] != cheatFsm->hintsCheatCode[i])
                {
                    cheat1 = 0;
                }
            }
            if (cheat2)
            {
                if (input[i] != cheatFsm->livesCheatCode[i])
                {
                    cheat2 = 0;
                }
            }
        }
        if (cheat1)
        {
            cheatFsm->current = CHEAT;
            printf("%s", chosen_word);
        }
        else if (cheat2)
        {
            cheatFsm->current = CHEAT;
            *lives = 7;
        }
        break;
    }
}
*/
