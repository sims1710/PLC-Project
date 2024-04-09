#include <stdio.h>
#include "all_functions.h"
/*#include <Windows.h>*/

/*
current game states:
lives: 0-7
score: positive int
lettersGuessed: list of chars
word: list of chars
gameOver: if 1, do not scan other game state, else scan other game state
*/

void save_game_state(int lives, int score, char* lettersGuessed, char* word, int gameOver, char * difficulty, time_t start) {
    FILE* file = fopen("input.txt", "w");
    time_t time;
    if (file == NULL) {
        printf("Error opening file!\n");
    }

    time =  end_time(start);

    fprintf(file, "game_over: %d\n", gameOver);
    fprintf(file, "lives: %d\n", lives);
    fprintf(file, "score: %d\n", score);
    fprintf(file, "letters_guessed: %s\n", lettersGuessed);
    fprintf(file, "word: %s\n", word);
    fprintf(file, "level: %s\n", difficulty);
    fprintf(file, "time: %d\n", time);

    fclose(file);
}

void load_game_state(int* lives, int* score, char* lettersGuessed, char* word, int* gameOver, char * difficulty, time_t time) {
    int i;

    FILE* file = fopen("input.txt", "r");

    if (file == NULL) {
        printf("No saved game found!\n");
        Sleep(1);
        /* calls the start of a new game */
        clear_screen();
        main_menu();
    }
    else{

        fscanf(file, "game_over: %d\n", gameOver);

        /* reload the game into the main gameplay function */
        if (*gameOver != 1){
            printf("Saved game found! Loading...\n");
            fscanf(file, "lives: %d\n", lives);
            fscanf(file, "score: %d\n", score);
            fscanf(file, "letters_guessed: %s\n", lettersGuessed);
            fscanf(file, "word: %s\n", word);
            fscanf(file, "difficulty: %s\n", difficulty);
            fscanf(file, "time: %d\n", time);

            i = 0;
            while(*word != '\0'){
                i++;
            }
            /* main gameplay function */
            Sleep(2);
            clear_screen();
            display_hangman(word, lives, i);
        }
        /* new game*/
        else{
            printf("No saved game found!\n");
            Sleep(2);
            clear_screen();
            main_menu();
        }
        
    }

    fclose(file);
}