/* Determine which file to read */
#include "all_functions.h"

void choose_difficulty(game_level *game_levels) {
    char difficulty;
    int rletter, valid;

    printf("The following difficulties are available: \nEasy: 4-5 letter words \nMedium: 4-6 letter words \nHard: 5-7 letter words \n");
    printf("Please choose a difficulty. \n - 1: Easy \n - 2: Medium\n - 3: Hard\n");
    
    valid = 0;
    while (valid == 0) {
        difficulty = fgetc(stdin);
        if (difficulty > '0' && difficulty < '4') {
            valid = 1;
        } else {
            printf("Error: user input is not 1, 2, or 3. Please try again.\n");
        }
    }
    /*Clear input stream here for cleanliness*/
    clear_stdin();

    /*Change random's seed using time function*/
    srand(time(NULL));

    /*Store the chosen difficulty in the GameLevels struct*/
    game_levels->difficulty = difficulty - '0';

    /*Calculate the word length based on difficulty chosen*/
    switch (game_levels->difficulty) {
        case 1:
            rletter = rand() % 2;
            break;
        case 2:
            rletter = rand() % 3;
            break;
        case 3:
            rletter = (rand() % 3) + 1;
            break;
    }

    /*Assign the filename based on the random letter count*/
    switch (rletter) {
        case 0:
            game_levels->chosenDiff.filename = "4_letter_words.txt";
            break;
        case 1:
            game_levels->chosenDiff.filename = "5_letter_words.txt";
            break;
        case 2:
            game_levels->chosenDiff.filename = "6_letter_words.txt";
            break;
        case 3:
            game_levels->chosenDiff.filename = "7_letter_words.txt";
            break;
    }
    game_levels->chosenDiff.word_len = rletter + 4;
}

/*for easy mode: first 12 words to be guessed are 4 letters and the 8 words to be guessed are 5 letters
for medium mode: first 8 words are 4 letters, 6 words next are 5 letters and 6 words next are 6 letters
for hard mode: first 6 words are 5 letters, next 6 words are 6 letters and next 8 words are 7 letters
help me implement the function*/
void update_game_level(game_level *game_levels) {
    /*Increase current_level*/
    game_levels->current_level++;

    /*Determine the word length based on the current level and difficulty*/
    int level = game_levels->current_level;
    switch (game_levels->difficulty) {
        case 1: /*Easy*/
            if (level <= 12) {
                game_levels->chosenDiff.filename = "4_letter_words.txt";
                game_levels->chosenDiff.word_len = 4;
            } else {
                game_levels->chosenDiff.filename = "5_letter_words.txt";
                game_levels->chosenDiff.word_len = 5;
            }
            break;
        case 2: /*Medium*/
            if (level <= 8) {
                game_levels->chosenDiff.filename = "4_letter_words.txt";
                game_levels->chosenDiff.word_len = 4;
            } else if (level <= 14) {
                game_levels->chosenDiff.filename = "5_letter_words.txt";
                game_levels->chosenDiff.word_len = 5;
            } else {
                game_levels->chosenDiff.filename = "6_letter_words.txt";
                game_levels->chosenDiff.word_len = 6;
            }
            break;
        case 3: /*Hard*/
            if (level <= 6) {
                game_levels->chosenDiff.filename = "5_letter_words.txt";
                game_levels->chosenDiff.word_len = 5;
            } else if (level <= 12) {
                game_levels->chosenDiff.filename = "6_letter_words.txt";
                game_levels->chosenDiff.word_len = 6;
            } else {
                game_levels->chosenDiff.filename = "7_letter_words.txt";
                game_levels->chosenDiff.word_len = 7;
            }
            break;
        default:
            printf("Invalid difficulty level\n");
    }
}

