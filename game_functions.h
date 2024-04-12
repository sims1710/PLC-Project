#include <time.h>
#include "game_structures.h"
#define ALPHABET_COUNT 26

void choose_difficulty(game_level *game_levels);

void update_game_level(game_level *game_levels);

void get_word(chosen_difficulty *filename, char* chosen_word);

void update_hidden_word(char *hidden_word, char *chosen_word, char input_letter);

void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *score);

void link_number(int* hint_integer);

void suggest_hint(char* chosen_word, char *guessed_letters, game_level *game_levels, int* hints_given, int* player_points, int* hint_integer, char* hint_char);

void score_tracker(int *score, int *lives);

