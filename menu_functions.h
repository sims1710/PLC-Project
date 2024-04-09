/* Code to open the HTML File */
#ifdef _WIN32
#include <windows.h>
#elif __APPLE__
#include <stdlib.h>
#endif

#define MAX_LIVES 7
#define ALPHABET_COUNT 26
#define MAX_ENTRIES 100
#define MAX_NAME_LENGTH 50
#define EXIT_CHAR 'E'
#define MAX_LEADERBOARD_ENTRIES 10
#define MAX_GUESSES 8
#define MAX_WORD_LENGTH 100

void updateLeaderboard(int score, int mode);
void addToLeaderboard(const char *name, int score, int mode);
void bubbleSortLeaderboard();
void generateLeaderboardHTML();

int validateChoice(int start, int end);
void enter_player_name(char *name);
