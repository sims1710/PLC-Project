#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "game_functions.h"
#include "menu_functions.h"
#include "clear_functions.h"

typedef enum{
    START,
    CHECK_LETTER,
    UPDATE_LETTER,
    CONTINUE_SEARCH,
    END
}State;

void choose_difficulty(game_level *game_levels) {
    char difficulty;
    int rletter, valid;

    printf("The following difficulties are available: \nEasy: 4-5 letter words \nMedium: 4-6 letter words \nHard: 5-7 letter words \n");
    printf("Please choose a difficulty. \n - 1: Easy \n - 2: Medium\n - 3: Hard\n");
    
    valid = 0;
    while (valid == 0) {
        difficulty = fgetc(stdin);
        if (difficulty > '0' && difficulty < '4') {
            valid = 1;
        } else {
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
    switch (game_levels->difficulty) {
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
    switch (rletter) {
        case 0:
            game_levels->chosenDiff.filename = "4_letter_words.txt";
            break;
        case 1:
            game_levels->chosenDiff.filename = "5_letter_words.txt";
            break;
        case 2:
            game_levels->chosenDiff.filename = "6_letter_words.txt";
            break;
        case 3:
            game_levels->chosenDiff.filename = "7_letter_words.txt";
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
void update_game_level(game_level *game_levels) {
    int level;

    /*Increase current_level*/
    game_levels->current_level++;

    /*Determine the word length based on the current level and difficulty*/
    level = game_levels->current_level;
    switch (game_levels->difficulty) {
        case 1: /*Easy*/
            if (level <= 12) {
                game_levels->chosenDiff.filename = "4_letter_words.txt";
                game_levels->chosenDiff.word_len = 4;
            } else {
                game_levels->chosenDiff.filename = "5_letter_words.txt";
                game_levels->chosenDiff.word_len = 5;
            }
            break;
        case 2: /*Medium*/
            if (level <= 8) {
                game_levels->chosenDiff.filename = "4_letter_words.txt";
                game_levels->chosenDiff.word_len = 4;
            } else if (level <= 14) {
                game_levels->chosenDiff.filename = "5_letter_words.txt";
                game_levels->chosenDiff.word_len = 5;
            } else {
                game_levels->chosenDiff.filename = "6_letter_words.txt";
                game_levels->chosenDiff.word_len = 6;
            }
            break;
        case 3: /*Hard*/
            if (level <= 6) {
                game_levels->chosenDiff.filename = "5_letter_words.txt";
                game_levels->chosenDiff.word_len = 5;
            } else if (level <= 12) {
                game_levels->chosenDiff.filename = "6_letter_words.txt";
                game_levels->chosenDiff.word_len = 6;
            } else {
                game_levels->chosenDiff.filename = "7_letter_words.txt";
                game_levels->chosenDiff.word_len = 7;
            }
            break;
        default:
            printf("Invalid difficulty level\n");
    }
}

/* Retrieve word from file */
char *get_word(chosen_difficulty *file_set)
{
    FILE *fptr;
    int index, iterate;
    char *word_count = NULL;
    char *buffer = NULL;
    char *chosen_word = NULL;

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
    fclose(fptr);
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
            while (guessed_letters[i] != '\0')
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
            (*score)++; /* Increment score for correct guess*/
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

/* for the hints implementation, link numbers to letters */
int *link_number(void)
{
    int letter_index, tracker_count, number, i;
    int tracker[26];
    /* MUST FREE */
    int *output = (int *)malloc(sizeof(int) * ALPHABET_COUNT);
    tracker_count = 0;
    letter_index = 0;
    while (tracker_count < 26)
    {
        srand(time(NULL));
        number = rand() % 26;
        for (i = 0; i < tracker_count; i++)
        {
            if (number == tracker[i])
            {
                /* if match, rand again */
                continue;
            }
        }
        /* no match, assign number */
        tracker[letter_index] = number;
        output[letter_index] = number + 1;
        letter_index++;
        tracker_count++;
    }
    return output;
}

/* This function will generate random numbers for the chosen word where it will be used as a hint
   for each letter of the word, they will have distinct integer from 1 to 26, for example, h will be associated with 13
   but when the word contains same letter, the same letter will have the same integer

   @param chosen_word: is a string which is the word that the player will need to guess
          word_len: is an Integer to keep track of the word's length
   @return an array of integer, each integer is associated to each letter in the word, the length of the array is equal to the word length
*/
int* random_number(char* chosen_word, int word_len){
    int i, index;
    int letter_numbers[26] = {0};
    int* numbers_for_words = (int*)malloc(sizeof(int)*word_len);

    /*using time as the seed to generate random integer everytime*/
    srand((unsigned int)time(NULL));
    for(i=0; chosen_word[i]!= '\0'; i++){
        /*checking if no number has been generated for the particular letter */
        index = chosen_word[i] - 'a';
        if(letter_numbers[index] == 0){
            letter_numbers[index] = rand() % 26 + 1;
        }
        numbers_for_words[i] = letter_numbers[index];
    }
    return numbers_for_words;
}

 /* suggest_hint function is to allow players to use 2 hints to guess the letter
    the hints rules are as follows:
        1. First hint used doesn't require points (no point will be deducted from the player)
        2. The second hint require points to be deducted which depends on the player's game difficulty
           The cost of the hint are as follows:
                - easy and medium: 1 point
                - hard: 2 points
    
    @param chosen_word: is a string which is the word that the player will need to guess
           guessed_letters: is an array of character of the letters that had been guessed by the player
           game_levels: is a pointer to the struct GameLevels
           hints_given: is an array of integer to check how many hints that the player had used
           player_points: is an integer pointer to keep track of how many points that the players have
    @return an integer which is the random integer retreived from the function random_number and will be used as a hint for the player (hint for a letter in the word)
 */
int suggest_hint(char* chosen_word, char *guessed_letters, game_level *game_levels, int* hints_given, int* player_points){
    int i, hint, hint_cost;
    int* random_integers;
    int word_len;

    hint = 0;

    /*Determine the cost of the second hint used based on the difficulty level*/
    hint_cost = game_levels->difficulty == 3 ? 2 : 1;
    /*Getting the length of the word*/
    word_len = game_levels->chosenDiff.word_len;

    /*Getting an array of random integers according to the chosen_word*/
    random_integers = random_number(chosen_word, word_len);

    /*Check if hint is available */
    if(*hints_given >= 2){
        printf("No more hints available.\n");
        return 0; 
    }

    /*Check if this is the second hint and if the player has enough points*/
    if(*hints_given == 1 && *player_points < hint_cost){
        printf("Not enough points for a hint.\n");
        return 0; 
    }

    /*Deduct the point for using the hint*/
    if(*hints_given == 1){
        *player_points -= hint_cost;
    }

    /*Provide the hint*/
    for(i = 0; i < word_len; i++){
        if(strchr(guessed_letters, chosen_word[i]) == NULL){
            hint = random_integers[i];
            break; 
        }
    }

    (*hints_given)++; 
    return hint;
}

/*keeping track of the players score*/
void score_tracker(int *score, int *lives) {
    static int challenges_completed = 0;

    if (*lives == 0) {
        printf("You have run out of lives! Your score is %d\n", *score);
        challenges_completed = 0; /* Reset challenges completed */ 
    } else {
        printf("Your score is %d\n", *score);
        challenges_completed++;
        if (challenges_completed >= 20) {
            printf("Congratulations! You have completed 20 challenges.\n");
            generateLeaderboardHTML();  /* Display leaderboard after completing 20 challenges */ 
            challenges_completed = 0; /* Reset challenges completed */ 
        }
    }
}

/* Function to add a new word upon winning */ 
void add_new_word(void)
{
    FILE *fp;
    char new_word[MAX_NAME_LENGTH];
    char filename[] = "words.txt";
    int word_len;

    /* Open file in append mode */ 
    fp = fopen(filename, "a");

    /* Check if file is opened */ 
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    /* Get new word from player */ 
    do {
        printf("Enter a new word: ");
        scanf("%s", new_word);

        /* Check if word is valid */ 
        word_len = strlen(new_word);
        if (word_len < 4 || word_len > 7) {
            printf("Word must be between 4 and 7 characters long\n");
        }
    } while (word_len < 4 || word_len > 7);

    /* Write word to file */ 
    fprintf(fp, "%s\n", new_word);

    fclose(fp);
}

int main(int argc, char *argv[]){
    char *chosen_word, *hidden_word;
    game_level *game_levels = (game_level*)malloc(sizeof(game_level));
    int word_len, game_over, lives, scores, roundOver;
    char guessed_letters[26] = {0};

    game_levels->current_level = 1;
    choose_difficulty(game_levels);
    word_len = game_levels->chosenDiff.word_len; /*maybe no need word_len in choosenDiff*/

    game_over = 0;
    lives = 7;
    scores = 0;
    roundOver = 0;
    hidden_word = (char*)malloc(sizeof(char)*word_len+1);

    while(!game_over){
        update_game_level(game_levels);
        chosen_word = get_word(&game_levels->chosenDiff);
        if (chosen_word == NULL) {
            printf("Failed to load the word. Exiting...\n");
            exit(EXIT_FAILURE);
        }
    

        while (!roundOver && lives > 0) {
                printf("\nCurrent word to guess: %s\n", hidden_word);
                player_input(chosen_word, hidden_word, guessed_letters, &lives, word_len, &scores);
            
                if (strcmp(hidden_word, chosen_word) == 0) {
                    printf("Congratulations! You've guessed the word: %s\n", chosen_word);
                    scores += lives; 
                    roundOver = 1;
                }
                
                printf("Your score: %d, Lives remaining: %d\n", scores, lives);
            }

        if (lives <= 0) {
            printf("Game over! You've run out of lives.\n");
            game_over = 1; 
        }

        free(chosen_word);
        free(hidden_word);

        while (getchar() != '\n');
    }
    return 0;
    
}