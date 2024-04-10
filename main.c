/* Where all functions are run to make the game run*/
#include <stdio.h>
#include <stdlib.h>
#include "ui.h"
#include "game_functions.h"
#include "clear_functions.h"
#include "game_modes.h"
#include "game_state.h"
#include "leaderboard.h"
#include "utility.h"
#include "game_structures.h"

#define MAX_LIVES 7
#define MAX_ENTRIES 100
#define EXIT_CHAR 0
#define MAX_LEADERBOARD_ENTRIES 10
#define MAX_GUESSES 8
#define MAX_WORD_LENGTH 100


/* Enumerations for menu choices and difficulty levels */
typedef enum
{
    NEW_GAME = 1,
    SAVED_GAME = 2,
    MULTIPLAYER = 3,
    LEADERBOARD = 4,
    ATTACK = 5,
    ENDLESS = 6,
    GAMERULE = 7,
    MAIN_MENU = 8,
    END = 0
} Choice;

typedef enum
{
    EASY = 1,
    MEDIUM = 2,
    HARD = 3
} Difficulty;

int main(int argc, char *argv[])
{
    char *chosen_word, *guessed_letters, *hidden_word, *name;
    int *lives, *score, *hints_given, *linking_hint, *currentState, *hint_result; /*current_state not an integer?*/
    int word_len, i, hint, continue_game, initialised, want_hint, game_over;
    game_level *game_levels;

    currentState = MAIN_MENU;
    continue_game = 1;
    initialised = 0;

    /*allocate memory for game_levels with size of game_level structure*/
    game_levels = (game_level *)malloc(sizeof(game_level));
    if (!game_levels)
    { /*checking if the memory allocation successful or not*/
        printf("Failed to allocate memory for game levels.\n");
        return 1;
    }

    while (continue_game)
    {
        lives = MAX_LIVES;
        score = 0;
        hints_given = 0;
        linking_hint = 0;  
        hint_result = 0; 
        want_hint = 0;
        game_over = 0;

        /*display the main menu*/
        main_menu(currentState, game_levels);

        /*set the current game levels as 1, the first level*/
        game_levels->current_level = 1;

        /*player to choose the difficulty of the game*/
        choose_difficulty(game_levels);
        clear_stdin();

        /*extracting the word length from the game_level structure*/
        word_len = game_levels->chosenDiff.word_len;

        /*allocating memory for guessed letters and hidden word*/
        guessed_letters = (char *)malloc(sizeof(char) * 26);
        hidden_word = (char *)malloc(sizeof(char) * word_len+1);
        /*check if the memory allocation failed*/
        if (!guessed_letters || !hidden_word)
        {
            printf("Failed to allocate memory.\n");
            break;
        }
        /*NEED TO DO MEMSET OR NOT?*/
        memset(hidden_word, '_', word_len);
        hidden_word[word_len] = '\0'; 

        memset(guessed_letters, 0, sizeof(guessed_letters));

        while(!game_over && (game_levels->current_level <= 20)){
            update_game_level(game_levels);
            /*getting the word for the players to guess*/
            chosen_word = get_word(&game_levels->chosenDiff);
            if (chosen_word == NULL)
            {
                printf("Failed to load the word. Exiting...\n");
                exit(EXIT_FAILURE);
            }

            while(lives>0){
                printf("\nCurrent word to guess: %s\n", hidden_word);
                printf("Do you want a hint? (0 for no, 1 for yes): ");
                scanf("%d", &want_hint);
                if (want_hint) {
                    /*TODO: modify the return output */
                    hint_result = suggest_hint(chosen_word, guessed_letters, game_levels, &hints_given, &score);
                    printf("Hint: One of the letters is: %d\n", hint_result); 
                }
                clear_stdin();

                /*processing the player input when they are playing the hangman*/
                player_input(chosen_word, hidden_word, guessed_letters, &lives, word_len, &score);

                /*display hangman everytime here?*/
                display_hangman(hidden_word, lives, word_len);
                
                /*what happen if they manage to guess the word? just print a congrulations message?*/
                if (strcmp(hidden_word, chosen_word) == 0) {
                    printf("Congratulations! You've guessed the word: %s\n", chosen_word);
                }

            }
            score_tracker(&score, &lives);

            if (lives <= 0) {
                printf("Game over! You've run out of lives.\n");
                game_over = 1;
            }

            if (game_levels->current_level > 20)
            {
                printf("Congratulations! You have completed all levels.\n");
            }

            free(chosen_word);
            free(hidden_word);

            while (getchar() != '\n');
        }


        if (*currentState == SAVED_GAME)
        {
            load_game_state(lives, score, guessed_letters, chosen_word, file_set, hints_given);
            initialised = 1;
        }

        switch (*currentState)
        {
        case NEW_GAME:
            /* code */
            break;
        case MULTIPLAYER:
            /* code */
            break;
        case LEADERBOARD:
            /* code */
            break;
        case ATTACK:
            /* code */
            break;
        case ENDLESS:
            /* code */
            break;
        case GAMERULE:
            /*display the game rules*/
            display_rules();
            break;
        case END:
            exit(0);
            break;
        default:
            currentState = MAIN_MENU;
            break;
        }

        /*when the player wins a game of a level*/
        add_new_word();
    }

    /*freeing the allocated memory*/
    free(guessed_letters);
    free(hidden_word);
    free(game_levels);

    return 0;
}
