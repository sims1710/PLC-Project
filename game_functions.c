#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
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

/* for the hints implementation, link numbers to letters */
int *link_number()
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
    int i, hint;
    int* random_integers;
    int word_len;

    /*Determine the cost of the second hint used based on the difficulty level*/
    const int hint_cost = game_levels->difficulty == 3 ? 2 : 1;
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
        leaderboard(*score);
        challenges_completed = 0; /* Reset challenges completed */ 
    } else {
        printf("Your score is %d\n", *score);
        challenges_completed++;
        if (challenges_completed >= 20) {
            printf("Congratulations! You have completed 20 challenges.\n");
            leaderboard(*score);  /* Display leaderboard after completing 20 challenges */ 
            challenges_completed = 0; /* Reset challenges completed */ 
        }
    }
}

/* Function to add a new word upon winning */ 
void add_new_word()
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

/*
current game states:
lives: 0-7
score: positive int
lettersGuessed: list of chars
word: list of chars
gameOver: if 1, do not scan other game state, else scan other game state
*/

void save_game_state(int lives, int score, char* lettersGuessed, char* word, int gameOver) {
    FILE* file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
    }

    fprintf(file, "game_over: %d\n", gameOver);
    fprintf(file, "lives: %d\n", lives);
    fprintf(file, "score: %d\n", score);
    fprintf(file, "letters_guessed: %s\n", lettersGuessed);
    fprintf(file, "word: %s\n", word);
    
    fclose(file);
}

void load_game_state(int* lives, int* score, char* lettersGuessed, char* word, int* gameOver) {
    int i;

    FILE* file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("No saved game found!\n");
        Sleep(1);
        /* calls the start of a new game */
        clear_screen();
        main_menu();
    }
    else{

        fscanf(file, "game_over: %d\n", gameOver);

        /* reload the game into the main gameplay function */
        if (*gameOver != 1){
            printf("Saved game found! Loading...\n");
            fscanf(file, "lives: %d\n", lives);
            fscanf(file, "score: %d\n", score);
            fscanf(file, "letters_guessed: %s\n", lettersGuessed);
            fscanf(file, "word: %s\n", word);
            i = 0;
            while(*word != '\0'){
                i++;
            }
            /* main gameplay function */
            Sleep(2);
            clear_screen();
            display_hangman(word, lives, i);
        }
        /* new game*/
        else{
            printf("No saved game found!\n");
            Sleep(1);
            clear_screen();
            main_menu();
        }
        
    }

    fclose(file);
}

/* starts time record */
time_t start_time(){
    time_t start;
    start=clock();
    return start;
}

/* stops time and calculates in seconds */
time_t end_time(time_t start){
    time_t stop;
    time_t difference;

    stop=clock();
    difference =(stop-start)/CLOCKS_PER_SEC;
    return difference;
}

