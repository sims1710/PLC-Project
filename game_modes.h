#define MAX_NAME_LENGTH 50
#define EXIT_CHAR '0'
#define MAX_WORD_LENGTH 100
#define MAX_GUESSES 8

typedef struct {
    char name[MAX_WORD_LENGTH];
    int lives;
    int score;
} Player;

void time_attack_mode(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *scores);

void multiplayer_mode(void);

void add_new_word(void);

void endless_mode(void);

void enter_name(char name[]);


