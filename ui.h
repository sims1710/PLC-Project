/* Code to open the HTML File */
#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <stdlib.h>
#endif

void displayRules();

void main_menu();

void display_hangman(char *hidden_word, int *lives, int word_len);

void clear_screen();

void clear_stdin();
