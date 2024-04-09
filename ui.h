/* Code to open the HTML File */
#ifdef _WIN32
// Includes necessary headers for Windows-specific functionality
#include <windows.h>
#elif __APPLE__
// Includes necessary headers for Apple (macOS)-specific functionality
#include <stdlib.h>
#elif __linux__
// Includes necessary headers for Linux-specific functionality
#include <unistd.h>
#endif

void displayRules();

void main_menu();

void display_hangman(char *hidden_word, int *lives, int word_len);

/*void clear_screen();

void clear_stdin();*/
