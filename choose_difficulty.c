/* Determine which file to read */
#include "all_functions.h"

void choose_difficulty(chosen_difficulty *file_set)
{
    /* Edits file_set given */
    char *difficulty;
    int rletter;
    /* TODO: Print difficulty details, player input to choose difficulty */
    printf("Please choose a difficulty. \n - 1: 4-5 letters \n - 2: 4-6 letters\n - 3: 5-7 letters");
    fgets(difficulty, 6, stdin);
    /* TODO: Change random's seed using time function */
    srand(time(NULL));
    /* TODO: Switch case based on difficulty chosen, choose random int between range */
    /* Easy: 4-5, Medium: 4-6, Hard: 5-7 */
    switch ((int)*difficulty)
    {
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
    /* TODO: Switch case based on rand_int chosen */
    switch (rletter)
    {
    case 0:
        file_set->filename = "4_letter_words.txt";
        break;
    case 1:
        file_set->filename = "5_letter_words.txt";
        break;
    case 2:
        file_set->filename = "6_letter_words.txt";
        break;
    case 3:
        file_set->filename = "7_letter_words.txt";
        break;
    }
    file_set->word_len = rletter + 4;
}