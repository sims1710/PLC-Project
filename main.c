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
    char *chosen_word, *guessed_letters, *hidden_word, *hint_char;
    int difficulty, lives_address, score_address, hint_address, word_len, i, hint, continue_game, initialised, want_hint, game_over, currentState;
    int *lives = &lives_address, *score = &score_address, *hints_given = &hint_address, *hint_integer;
    game_level *game_levels;
    
    currentState = MAIN_MENU;
    continue_game = 1;
    initialised = 0;

    /*allocate memory for game_levels with size of game_level structure*/
    game_levels = (game_level *)malloc(sizeof(game_level));
    /*hints given in each game are 2 hints*/
    hint_char = (char*)malloc(sizeof(char)*3); /*size is 3, extra 1 is for the null terminating*/
    hint_integer = (int*)malloc(sizeof(int)*2);
    hint_integer[0] = -1;
    hint_integer[1] = -1;
    if (!game_levels || !hint_char || !hint_integer)
    { /*checking if the memory allocation successful or not*/
        printf("Failed to allocate memory for game levels.\n");
        return 1;
    }

    while (continue_game)
    {
        *lives = MAX_LIVES;
        *score = 0;
        *hints_given = 0;
        want_hint = 0;
        game_over = 0;

        /*display the main menu*/
        main_menu(currentState, game_levels);

        if (currentState == SAVED_GAME)
        {   
            difficulty = game_levels->difficulty;
            load_game_state(lives, score, guessed_letters, chosen_word, difficulty, hints_given); 
            initialised = 1;
        }

        switch (currentState)
        {
        case NEW_GAME:
            main_menu(currentState, game_levels);
            /*set the current game levels as 1, the first level*/
            game_levels->current_level = 1;
            while(!game_over && (game_levels->current_level <= 20)){
                update_game_level(game_levels);
                chosen_word = get_word(&game_levels->chosenDiff);
                if (chosen_word == NULL)
                {
                    printf("Failed to load the word. Exiting...\n");
                    exit(EXIT_FAILURE);
                }

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
            
                /*display the initial hangman*/
                display_hangman(chosen_word, hidden_word, lives, word_len, hint_char, hint_integer, hints_given, score);

                while(lives>0){
                printf("\nCurrent word to guess: %s\n", hidden_word);
                printf("Do you want a hint? (0 for no, 1 for yes): ");

                want_hint = fgetc(stdin);
                if ((int)want_hint==49) {
                    suggest_hint(chosen_word, guessed_letters, game_levels, &hints_given, &score, hint_integer, hint_char);
                }
                clear_stdin();
            

                /*processing the player input when they are playing the hangman*/
                player_input(chosen_word, hidden_word, guessed_letters, &lives, word_len, &score);
                score_tracker(&score, &lives);

                /*displaying hangman for every input given by player*/
                display_hangman(chosen_word, hidden_word, lives, word_len, hint_char, hint_integer, hints_given, score);

                /*if managed to guess correctly*/
                if (strcmp(hidden_word, chosen_word) == 0) {
                    printf("Congratulations! You've guessed the word: %s\n", chosen_word);
                }
            }

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
            free(game_levels);

            while (getchar() != '\n');
        }
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
    }

    return 0;
}
