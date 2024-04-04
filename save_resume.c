#include <stdio.h>
#include "save_resume.h"

int main(int argc, char ** argv){
    // char lettersGuessed[5] = {'a', 'a', 'a', 'a', '\0'};
    // char word[7] = {'b', 'b', 'b', 'b', 'b', 'b', '\0'};

    // saveGameState(1,2, lettersGuessed, word, 0);
    int lives, score;
    char lettersGuessed[5]; // plus \0
    char word[7]; // plus \0
    int gameOver;

    // load game from file
    loadGameState(&lives, &score, lettersGuessed, word, &gameOver);

    // save it in variables introduced
    printf("Lives: %d\n", lives);
    printf("Score: %d\n", score);
    printf("Letters Guessed: %s\n", lettersGuessed);
    printf("Word: %s\n", word);
    printf("Game Over: %d\n", gameOver);
}

/*
current game states:
lives: 0-7
score: positive int
lettersGuessed: list of chars
word: list of chars
gameOver: if 1, do not scan other game state, else scan other game state
*/

void saveGameState(int lives, int score, char* lettersGuessed, char* word, int gameOver) {
    FILE* file = fopen("input.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
    }

    fprintf(file, "game_over: %d\n", gameOver);
    fprintf(file, "lives: %d\n", lives);
    fprintf(file, "score: %d\n", score);
    fprintf(file, "letters_guessed: %s\n", lettersGuessed);
    fprintf(file, "word: %s\n", word);
    
    fclose(file);
}

void loadGameState(int* lives, int* score, char* lettersGuessed, char* word, int* gameOver) {
    FILE* file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("No saved game found!\n");
    }

    fscanf(file, "game_over: %d\n", gameOver);

    if (*gameOver != 1){
        fscanf(file, "lives: %d\n", lives);
        fscanf(file, "score: %d\n", score);
        fscanf(file, "letters_guessed: %s\n", lettersGuessed);
        fscanf(file, "word: %s\n", word);
    }

    fclose(file);
}