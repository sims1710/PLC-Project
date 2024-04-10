/* Code to open the HTML File */
#ifdef _WIN32
/*Includes necessary headers for Windows-specific functionality*/
#include <windows.h>
#elif __APPLE__
/* Includes necessary headers for Apple (macOS)-specific functionality*/
#include <stdlib.h>
#elif __linux__
/*Includes necessary headers for Linux-specific functionality*/
#include <unistd.h>
#endif

#include "game_structures.h"

void display_rules(void);

/*change the parameter type of the current_state form int* into int */
void main_menu(int current_state, game_level *game_levels);

void display_hangman(char *hidden_word, int *lives, int word_len);
