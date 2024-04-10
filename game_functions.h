#include <time.h>
#include "game_structures.h"
#define ALPHABET_COUNT 26

void choose_difficulty(game_level *game_levels);

/*update the game levels based on the difficulty mode*/
void update_game_level(game_level *game_levels);

char *get_word(chosen_difficulty *filename);

void update_hidden_word(char *hidden_word, char *chosen_word, char input_letter);

void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *score);

int *link_number(void);

int suggest_hint(char* chosen_word, char *guessed_letters, game_level *game_levels, int* hints_given, int* player_points);

void score_tracker(int *score, int *lives);

