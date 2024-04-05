/* Where all functions are run to make the game run*/
#include "all_functions.h"

int main(int argc, char *argv[])
{
    char *chosen_word;
    char *guessed_letters;
    char *hidden_word;
    int *lives, *score;
    int word_len, i = 0;
    chosen_difficulty *file_set;
    game_level *game_levels;

    /*make it inside a while loop*/

    /*display hangman UI */

    /*player to choose the difficulty of the game*/
    choose_difficulty(game_levels);

    /*extracting the word length from the game_level structure*/
    word_len = game_levels->chosenDiff.word_len;

    /*getting the word for the players to guess*/
    chosen_word = get_word(file_set);

    /*processing the player input when they are playing the hangman*/
    player_input(chosen_word, hidden_word, guessed_letters, lives, word_len, score);

    /*updating the hidden word for every time the player guessed the letter correctly*/
    update_hidden_word(hidden_word, chosen_word, guessed_letters[i]);

    /*tracking the scores*/
    score_tracker(score, lives);

    /*update game level when player succeed to win the previous level*/
}