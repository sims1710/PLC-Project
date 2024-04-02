/* Define all planned functions here, include in all c files (TEMPORARY)*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> // Added
#include <stdbool.h>

/* Constants */
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

void choose_difficulty(chosen_difficulty *file_set);

/* Return a selected word, function input is filename */
char *get_word(chosen_difficulty *filename);

/* Update contents of pointer for hidden word, return nothing, function input is pointer to hidden word display and chosen word */
void update_hidden_word(char *hidden_word, char *chosen_word, char input_letter);

/* Check player input, invalid if number or already guessed, run if update if hit. function input is the selected word, hidden word display  */
void player_input(char *chosen_word, char *guessed_letters, int *lives, int *score); // Updated

/* Main Menu */
void main_menu();
int validateChoice(int start, int end);
void enter_player_name(char *name);
int main1(); // Temporary Function

/* Keep track of score */
void score_tracker(int *score, int *lives);

/* Display and update leaderboard */
void updateLeaderboard(int score, int mode);
void addToLeaderboard(const char *name, int score, int mode);
void bubbleSortLeaderboard();
void generateLeaderboardHTML();

/* Display Game Rules */
void displayRules();

/* Endless Mode */
void endless_mode();

/* Multiplayer Mode */
void multiplayer_mode();

/* Adding a new word upon winning */
void add_new_word();
