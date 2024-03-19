/* Determine which file to read */
#include "all_functions.h"

void choose_difficulty(chosen_difficulty *file_set)
{
    /* Edits file_set given */
    char difficulty;
    int rletter, d, valid;
    /* TODO: Print difficulty details, player input to choose difficulty */
    printf("The following difficulties are available: \nEasy: 4-5 letter words \nMedium: 4-6 letter words \nHard: 5-7 letter words \n");
    printf("Please choose a difficulty. \n - 1: Easy \n - 2: Medium\n - 3: Hard\n");
    valid = 0;
    while (valid == 0)
    {
        difficulty = fgetc(stdin);
        if (difficulty > '0' && difficulty < '4')
        {
            valid = 1;
        }
        else
        {
            printf("Error: user input is not 1, 2, or 3. Please try again.\n");
        }
    }
    /* Clear input stream here for cleanliness */
    clear_stdin();
    /* TODO: Change random's seed using time function */
    srand(time(NULL));
    /* TODO: Switch case based on difficulty chosen, choose random int between range */
    /* Easy: 4-5, Medium: 4-6, Hard: 5-7 */
    /* Switch case cannot take 6 letter expression */
    d = (int)(difficulty - '0');
    switch (d)
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