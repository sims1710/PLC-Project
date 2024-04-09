#include <time.h>

/*TODO: where does the fixed values were used?*/
/* Fixed Values */
#define MAX_LIVES 7
#define ALPHABET_COUNT 26
#define MAX_ENTRIES 100
#define MAX_NAME_LENGTH 50
#define EXIT_CHAR 'E'
#define MAX_LEADERBOARD_ENTRIES 10
#define MAX_GUESSES 8
#define MAX_WORD_LENGTH 100

/* Return filename to read from, no external input, only player input inside function */
typedef struct
{
    char *filename;
    int word_len;
} chosen_difficulty;

typedef struct
{
    int current_level;
    int difficulty;
    chosen_difficulty chosenDiff;
} game_level;

void choose_difficulty(game_level *game_levels);

/*update the game levels based on the difficulty mode*/
void update_game_level(game_level *game_levels);

char *get_word(chosen_difficulty *filename);

void update_hidden_word(char *hidden_word, char *chosen_word, char input_letter);

void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *score);

int *link_number(void);

int *random_number(char *chosen_word, int word_len);

int suggest_hint(char* chosen_word, char *guessed_letters, game_level *game_levels, int* hints_given, int* player_points);

void score_tracker(int *score, int *lives);

void add_new_word(void);

/*void clear_stdin(void);*/

