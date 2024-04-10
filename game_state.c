#include <stdio.h>
#include <time.h>
#include "game_state.h"

/*
current game states:
lives: 0-7
score: positive int
lettersGuessed: list of chars
word: list of chars
gameOver: if 1, do not scan other game state, else scan other game state
*/

void save_game_state(int* lives, int* score, char* lettersGuessed, char* word, char difficulty, int * hints_given) {
    FILE* file = fopen("input.txt", "w");
    time_t time;
    if (file == NULL) {
        printf("Error opening file!\n");
    }

    fprintf(file, "lives: %d\n", lives);
    fprintf(file, "score: %d\n", score);
    fprintf(file, "letters_guessed: %s\n", lettersGuessed);
    fprintf(file, "word: %s\n", word);
    fprintf(file, "level: %s\n", difficulty);
    fprintf(file, "hints_given: %d\n", hints_given);

    fclose(file);
}

void load_game_state(int* lives, int* score, char* lettersGuessed, char* word, char difficulty, int * hints_given) {
    int i;

    FILE* file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("No saved game found!\n");
    }
    else{
        /* reload the game into the main gameplay function */
        if (lives > 0){
            printf("Saved game found! Loading...\n");
            fscanf(file, "lives: %d\n", lives);
            fscanf(file, "score: %d\n", score);
            fscanf(file, "letters_guessed: %s\n", lettersGuessed);
            fscanf(file, "word: %s\n", word);
            fscanf(file, "difficulty: %s\n", difficulty);
            fscanf(file, "hints_given: %d\n", hints_given);

        }
        /* new game*/
        else{
            printf("No saved game found!\n");
        }
        
    }

    fclose(file);
}
