#define MAX_LIVES 7
#define ALPHABET_COUNT 26
#define MAX_ENTRIES 100
#define MAX_NAME_LENGTH 50
#define EXIT_CHAR 0
#define MAX_LEADERBOARD_ENTRIES 10
#define MAX_GUESSES 8
#define MAX_WORD_LENGTH 100

void updateLeaderboard(int score, int mode);
void addToLeaderboard(const char *name, int score, int mode);
void bubbleSortLeaderboard(void);
void generateLeaderboardHTML(void);

int validateChoice(int start, int end);
void enter_player_name(char *name);
