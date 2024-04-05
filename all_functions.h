/* Define all planned functions here, include in all c files (TEMPORARY)*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h> 
#include <stdbool.h>

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

/*void choose_difficulty(chosen_difficulty *file_set);*/
void choose_difficulty(game_level *game_levels);

/*update the game levels based on the difficulty mode*/
void update_game_level(game_level *game_levels);

/* Return a selected word, function input is filename */
char *get_word(chosen_difficulty *filename);

/* Update contents of pointer for hidden word, return nothing, function input is pointer to hidden word display and chosen word */
void update_hidden_word(char *hidden_word, char *chosen_word, char input_letter);

/* Check player input, invalid if number or already guessed, run if update if hit. function input is the selected word, hidden word display  */
void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *score);

/* Display the Hangman menu in console */
void display_hangman(char *hidden_word, int *lives, int word_len);

/* Make connections between letters and numbers */
int *link_number();

/* Clear console screen */
void clear_screen();

/* Clear stdin (Input stream) */
void clear_stdin();

/* Generate random number for the hints */
int *random_number(char *chosen_word, int word_len);

/* Function to suggest hints */
int suggest_hint(char *chosen_word, char *guessed_letters, game_level *game_levels, int *hints_given, int *player_points);

/*Implement the time attack mode*/
void time_attack_mode(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *scores);

/* Main Menu */
void main_menu();
int validateChoice(int start, int end);
void enter_player_name(char *name);
/*int main1();*/

/* Keep track of score */
void score_tracker(int *score, int *lives);

/* Display and update leaderboard */
void updateLeaderboard(int score, int mode);
void addToLeaderboard(const char *name, int score, int mode);
void bubbleSortLeaderboard();
void generateLeaderboardHTML();

/* Display Game Rules */
void display_rules();

/* Endless Mode */
void endless_mode();

/* Multiplayer Mode */
void multiplayer_mode();

/* Adding a new word upon winning */
void add_new_word();

/* Save and resume function */
void save_game_state(int lives, int score, char *lettersGuessed, char *word, int gameOver);
void load_game_state(int *lives, int *score, char *lettersGuessed, char *word, int *gameOver);

/* timer functions */
time_t start_time();
time_t end_time(time_t start);

/* UI
void displayRules();

void main_menu();

void display_hangman(char *hidden_word, int *lives, int word_len);

void clear_screen();

void clear_stdin();

/*I move these 2 here because it was used in the main_menu function 
int validateChoice(int start, int end);
void enter_player_name(char *name);

*/

/* Game functions

char *get_word(chosen_difficulty *filename);

void update_hidden_word(char *hidden_word, char *chosen_word, char input_letter);

void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *score);

int *link_number();

int *random_number(char *chosen_word, int word_len);

int suggest_hint(char *chosen_word, int word_len, int *numbers_hint, int difficulty, int *hints_given, int *player_points);

void score_tracker(int *score, int *lives);

void add_new_word();

void save_game_state(int lives, int score, char *lettersGuessed, char *word, int gameOver);

void load_game_state(int *lives, int *score, char *lettersGuessed, char *word, int *gameOver);

time_t start_time();

time_t end_time(time_t start);

*/

/*Game mode functions

void time_attack_mode(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *scores);

void multiplayer_mode();

void endless_mode();

*/

/* Menu functions

void updateLeaderboard(int score, int mode);
void addToLeaderboard(const char *name, int score, int mode);
void bubbleSortLeaderboard();
void generateLeaderboardHTML();

/*these functions are used in the main_menu function, so now I put it in ui.c files*?
int validateChoice(int start, int end);
void enter_player_name(char *name);



*/
