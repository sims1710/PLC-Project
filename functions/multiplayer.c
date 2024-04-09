# include "all_functions.h"

typedef struct {
    char name[MAX_WORD_LENGTH];
    int lives;
    int score;
} Player;

int main() {
    char guessed_letters[MAX_WORD_LENGTH];
    char hidden_word[MAX_WORD_LENGTH];
    char *chosen_word;
    Player player1, player2;
    int level = 1;
    int word_len;

    // Initialize players
    enter_player_name(player1.name);
    strcpy(player2.name, "Player 2");  // Default name for player 2
    player1.lives = player2.lives = MAX_GUESSES;
    player1.score = player2.score = 0;
    word_len = strlen(chosen_word);

    // Main game loop
    while (level <= 20) {
        printf("\n\nLevel %d\n\n", level);

        // Get a word based on difficulty (filename)
        chosen_word = get_word("easy_words.txt");  // Example filename, replace with actual filename

        // Initialize guessed letters
        strcpy(guessed_letters, "");

        // Initialize hidden word display
        memset(hidden_word, '_', strlen(chosen_word));
        hidden_word[strlen(chosen_word)] = '\0';

        // Loop for a single level
        while (player1.lives > 0 && player2.lives > 0) {
            printf("\n%s's turn\n\n", player1.name);
            printf("Hidden Word: %s\n", hidden_word);
            printf("Guessed Letters: %s\n", guessed_letters);
            player_input(chosen_word, hidden_word, guessed_letters,  &player1.lives, word_len ,&player1.score);
            if (strcmp(hidden_word, chosen_word) == 0) {
                printf("\nCongratulations, %s! You guessed the word.\n", player1.name);
                score_tracker(&player1.score, &player1.lives);
                add_new_word();  // Add a new word to the file upon winning
                level++;
                break;  // Move to the next level
            }

            printf("\n%s's turn\n\n", player2.name);
            printf("Hidden Word: %s\n", hidden_word);
            printf("Guessed Letters: %s\n", guessed_letters);
            player_input(chosen_word, hidden_word, guessed_letters,  &player2.lives, word_len ,&player2.score);
            if (strcmp(hidden_word, chosen_word) == 0) {
                printf("\nCongratulations, %s! You guessed the word.\n", player2.name);
                score_tracker(&player2.score, &player2.lives);
                add_new_word();  // Add a new word to the file upon winning
                level++;
                break;  // Move to the next level
            }
        }

        if (player1.lives <= 0 || player2.lives <= 0) {
            printf("\nGame Over! You ran out of lives.\n");
            break;  // End the game if lives are exhausted
        }
    }

    // Display final scores
    printf("\nFinal Scores:\n");
    printf("%s's Score: %d\n", player1.name, player1.score);
    printf("%s's Score: %d\n", player2.name, player2.score);

    return 0;
}