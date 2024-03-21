/* link numbers to letters */
#include "all_functions.h"

int *link_number()
{
    int letter_index, tracker_count, number, i;
    int tracker[26];
    /* MUST FREE */
    int *output = (int *)malloc(sizeof(int) * ALPHABET_COUNT);
    tracker_count = 0;
    letter_index = 0;
    while (tracker_count < 26)
    {
        srand(time(NULL));
        number = rand() % 26;
        for (i = 0; i < tracker_count; i++)
        {
            if (number == tracker[i])
            {
                /* if match, rand again */
                continue;
            }
        }
        /* no match, assign number */
        tracker[letter_index] = number;
        output[letter_index] = number + 1;
        letter_index++;
        tracker_count++;
    }
    return output;
}