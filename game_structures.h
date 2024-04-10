typedef struct {
    char* filename;
    int word_len;
} chosen_difficulty;

typedef struct {
    int current_level;
    int difficulty;
    chosen_difficulty chosenDiff;
} game_level;
