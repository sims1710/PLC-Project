/* Retrieve word from file */
#include "all_functions.h"

char *get_word(chosen_difficulty *file_set)
{
    FILE *fptr;
    char *word_count;
    char *buffer;
    char *chosen_word;
    int index, iterate;
    /* TODO: Open file */
    fptr = fopen(file_set->filename, "r");
    /* TODO: Get number of words from first line, shift pointer to first word */
    fgets(word_count, 100, fptr);
    /* TODO: Change random seed using time function */
    srand(time(NULL));
    /* TODO: Get random int to get */
    index = rand() % (int)*word_count;
    iterate = 0;
    while (fgets(buffer, 100, fptr))
    {
        if (iterate == index)
        {
            fgets(chosen_word, 100, fptr);
            break;
        }
        iterate++;
    }
    return chosen_word;
}