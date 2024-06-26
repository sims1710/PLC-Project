/* Code to open the HTML File */
#ifdef _WIN32
/*Includes necessary headers for Windows-specific functionality*/
#include <windows.h>
#elif __APPLE__
/* Includes necessary headers for Apple (macOS)-specific functionality*/
#include <stdlib.h>
/*Includes necessary headers for Linux-specific functionality*/
#include <unistd.h>
#endif

#include "game_structures.h"

void display_rules(void);

/*change the parameter type of the current_state form int* into int */
void main_menu(int *current_state, game_level *game_levels, char *name);

void display_hangman(char *chosen_word, char *hidden_word, int *lives, int word_len, char *hint_letter, int *hint_code, int *hints_given, int *score);

