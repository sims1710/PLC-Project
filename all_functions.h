/* Define all planned functions here, include in all c files (TEMPORARY)*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Fixed Values */
#define MAX_LIVES 7
#define ALPHABET_COUNT 26

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
void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len);

/* Display the Hangman menu in console */
void display_hangman(char *hidden_word, int *lives, int word_len);

/* Clear console screen */
void clear_screen();

/* Clear stdin (Input stream) */
void clear_stdin();

/* Generate random number for the hints */
int* random_number(char* chosen_word, int word_len);

/* Function to suggest hints */
int suggest_hint(char* chosen_word, int word_len, int* numbers_hint, int difficulty, int* hints_given, int* player_points);
