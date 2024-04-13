/* Where all functions are run to make the game run*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "game_functions.h"
#include "clear_functions.h"
#include "game_modes.h"
#include "leaderboard.h"
#include "game_structures.h"

#define MAX_LIVES 7
#define MAX_ENTRIES 100
#define MAX_LEADERBOARD_ENTRIES 10
#define MAX_GUESSES 8
#define MAX_WORD_LENGTH 100

/* Enumerations for menu choices and difficulty levels */
typedef enum
{
    NEW_GAME = 1,
    MULTIPLAYER = 2,
    LEADERBOARD = 3,
    ATTACK = 4,
    GAMERULE = 5,
    MAIN_MENU = 6,
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
    int difficulty, lives_address, score_address, hint_address, word_len, continue_game, want_hint, i, game_over, state, hidden_index;
    int *lives = &lives_address, *score = &score_address, *hints_given = &hint_address, *hint_integer, *currentState;
    char name[100];
    game_level *game_levels;
    currentState = &state;
    *currentState = MAIN_MENU;
    continue_game = 1;

    /*allocate memory for game_levels with size of game_level structure*/
    game_levels = (game_level *)malloc(sizeof(game_level));
    /*hints given in each game are 2 hints*/
    hint_char = (char *)malloc(sizeof(char) * 3); /*size is 3, extra 1 is for the null terminating*/
    hint_integer = (int *)malloc(sizeof(int) * 26);
    guessed_letters = (char *)malloc(sizeof(char) * 26);
    chosen_word = (char *)malloc(sizeof(char) * 8);
    hidden_word = (char *)malloc(sizeof(char) * 7);
    hint_char[0] = '_';
    hint_char[1] = '_';
    if (!game_levels || !hint_char)
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
        main_menu(currentState, game_levels, name);

        /*the saved_game was decided not to be implemented*/
        /*if (*currentState == SAVED_GAME)
        {
            difficulty = game_levels->difficulty;
            load_game_state(lives, score, guessed_letters, chosen_word, difficulty, hints_given);
            if(lives == NULL || score == NULL || chosen_word ==NULL){
                *currentState = NEW_GAME;
            }

        }*/

        switch (*currentState)
        {
        case NEW_GAME:
            srand(time(NULL));
            /*set the current game levels as 1, the first level*/
            game_levels->current_level = 1;
            difficulty = game_levels->difficulty;
            while (!game_over && (game_levels->current_level <= 20))
            {
                get_word(&game_levels->chosenDiff, chosen_word);
                if (chosen_word == NULL)
                {
                    printf("Failed to load the word. Exiting...\n");
                    exit(EXIT_FAILURE);
                }

                /*extracting the word length from the game_level structure*/
                word_len = game_levels->chosenDiff.word_len;

                /*allocating memory for guessed letters and hidden word*/
                guessed_letters = (char *)realloc(guessed_letters, sizeof(char) * 26);
                for(i=0; i<26; i++){
                    guessed_letters[i] = '\0';
                }
                hidden_word = (char *)realloc(hidden_word, sizeof(char) * word_len + 1);
                for (hidden_index = 0; hidden_index < word_len; hidden_index++)
                {
                    hidden_word[hidden_index] = '_';
                }
                hidden_word[word_len] = '\0';
                /*check if the memory allocation failed*/
                if (!guessed_letters || !hidden_word)
                {
                    printf("Failed to allocate memory.\n");
                    break;
                }
                link_number(hint_integer);

                /*display the initial hangman*/
                display_hangman(chosen_word, hidden_word, lives, word_len, hint_char, hint_integer, hints_given, score);
                clear_stdin();
                while (*lives > 0)
                {
                    printf("\nCurrent word to guess: %s\n", hidden_word);
                    printf("Do you want a hint? (0 for no, 1 for yes): \n");

                    want_hint = fgetc(stdin);
                    clear_stdin();

                    if (want_hint == 49)
                    {
                        suggest_hint(chosen_word, guessed_letters, game_levels, hints_given, score, hint_integer, hint_char);
                    }
                    printf("Please input your guess!\n");

                    /*processing the player input when they are playing the hangman*/
                    player_input(chosen_word, hidden_word, guessed_letters, lives, word_len, score);

                    /*displaying hangman for every input given by player*/
                    display_hangman(chosen_word, hidden_word, lives, word_len, hint_char, hint_integer, hints_given, score);

                    score_tracker(score, lives);

                    if (strncmp(hidden_word, chosen_word, word_len) == 0)
                    {
                        printf("Congratulations! You move on to the next word");
                        update_game_level(game_levels);
                        if((game_levels->current_level) >= 20){
                            updateLeaderboard(name, *score, difficulty);
                            displayLeaderboard();
                            
                        }
                        break;
                    }
                }

                if (*lives <= 0)
                {
                    printf("Game over! You've run out of lives.\n");
                    free(chosen_word);
                    free(hidden_word);
                    free(game_levels);
                    free(hint_char);
                    free(hint_integer);
                    free(guessed_letters);
                    game_over = 1;
                }

                if (game_levels->current_level > 20)
                {
                    printf("Congratulations! You have completed all levels.\n");
                }

                hint_char[0] = '_';
                hint_char[1] = '_';
                *hints_given = 0;
                *lives = MAX_LIVES;
            }

            break;
        case MULTIPLAYER:
            multiplayer_mode();
            break;
        case LEADERBOARD:
            displayLeaderboard();
            addToLeaderboard(name, *score, game_levels->difficulty);
            break;
        case ATTACK:
            choose_difficulty(game_levels);
            word_len = game_levels->chosenDiff.word_len;
            get_word(&game_levels->chosenDiff, chosen_word);
            guessed_letters = (char *)malloc(sizeof(char) * 26);
            chosen_word = (char *)malloc(sizeof(char) * 7);
            hidden_word = (char *)malloc(sizeof(char) * word_len + 1);
            for (i = 0; i < word_len; i++)
            {
                hidden_word[i] = '_';
            }
            hidden_word[word_len] = '\0';

            printf("Starting Time Attack Mode Test...\n");
            time_attack_mode(chosen_word, hidden_word, guessed_letters, lives, word_len, score);
            free(chosen_word);
            free(guessed_letters);
            free(hidden_word);
            free(game_levels);
            break;
        case GAMERULE:
            /*display the game rules*/
            display_rules();
            break;
        case END:
            exit(0);
            break;
        default:
            *currentState = MAIN_MENU;
            break;
        }
        
    }
    free(chosen_word);
    free(hidden_word);
    free(game_levels);
    free(hint_char);
    free(hint_integer);
    free(guessed_letters);
    return 0;
}
