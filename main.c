/* Where all functions are run to make the game run*/
#include <stdio.h>
#include <stdlib.h>
#include "all_functions.h"

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
    char *chosen_word, *guessed_letters, *hidden_word;
    int *lives, *score, *hints_given, *linking_hint, *currentState;
    int word_len, i, hint, continue_game, initialised;
    chosen_difficulty *file_set;
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

        /*display the main menu*/
        main_menu(currentState, game_levels);

        if (*currentState == SAVED_GAME)
        {
            load_game_state(lives, score, guessed_letters, chosen_word);
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
            break;
        }

        /*player to choose the difficulty of the game*/
        choose_difficulty(game_levels);

        /*getting the word for the players to guess*/
        chosen_word = get_word(file_set);

        /*extracting the word length from the game_level structure*/
        word_len = game_levels->chosenDiff.word_len;

        /*allocating memory for guessed letters and hidden word*/
        guessed_letters = (char *)malloc(sizeof(char) * 26);
        hidden_word = (char *)malloc(sizeof(char) * word_len);
        /*check if the memory allocation failed*/
        if (!guessed_letters || !hidden_word)
        {
            printf("Failed to allocate memory.\n");
            break;
        }

        /*display hangman*/
        display_hangman(hidden_word, lives, word_len);

        /*processing the player input when they are playing the hangman*/
        player_input(chosen_word, hidden_word, guessed_letters, lives, word_len, score);

        /*updating the hidden word for every time the player guessed the letter correctly*/
        update_hidden_word(hidden_word, chosen_word, guessed_letters[i]);

        /*tracking the scores and leaderboard is called everytime calling this function*/
        score_tracker(score, lives);

        /*using hints if the player wanted, display 1 hint at a time, 2 hints allowed in total*/
        hint = suggest_hint(chosen_word, guessed_letters, game_levels, hints_given, score);
        /*linking the hint which is a number to the letter*/
        linking_hint = link_number();

        /*when the player wins a game of a level*/
        add_new_word();

        /*update game level when player succeed to win the previous level*/
        update_game_level(game_levels);
    }

    /*freeing the allocated memory*/
    free(guessed_letters);
    free(hidden_word);
}
