/* Print out the hangman screen on console */
#include "all_functions.h"

void display_hangman(char *hidden_word, int *lives, int word_len)
{
    int window_width, window_height, row, colomn;
    window_width = 41;
    window_height = 12;
    /* Clear terminal */
    clear_screen();
    /* Start printing in format */
    for (row = 0; row < window_height; row++)
    {
        /* Prints for start and end */
        if (row == 0 || row == window_height - 1)
        {
            for (colomn = 0; colomn < window_width; colomn++)
            {
                printf("#");
            }
        }
        else
        {
            /* Unique prints for middle */
            switch (row)
            {
            case 1:
                /* Score */
                break;
            case 2:
                printf("#                                +---+  #");
                break;
            case 3:
                /* Hint */
                break;
            case 4:
                /* Head */
                break;
            case 5:
                /* Upper */
                break;
            case 6:
                /* Middle */
                break;
            case 7:
                /* Legs */
                if (*lives == 0)
                {
                    printf("#                               / \\  |  #");
                }
                else if (*lives == 1)
                {
                    printf("#                               /    |  #");
                }
                else
                {
                    printf("#                                    |  #");
                }
                break;
            case 8:
                printf("#                                    |  #");
                break;
            case 9:
                printf("# Lives: %d                     =======  #", *lives);
                break;
            case 10:
                /* Second to last format */
                for (colomn = 0; colomn < window_width; colomn++)
                {
                    if (colomn == 0 || colomn == window_width - 1)
                    {
                        printf("#");
                    }
                    else
                    {
                        printf(" ");
                    }
                }
                break;
            default:
                printf("If this is printed, there is error in display_hangman");
                break;
            }
        }
        /* Shift to next line after printing the row */
        printf("\n");
    }
}

/* Formatting */
/*
#########################################
# Score:                                #
#                                +---+  #
#    Hint:                       |   |  #
#                                O   |  #
#                               /|\  |  #
#    _ _ _ _ _ _ _               |   |  #
#                               / \  |  #
#                                    |  #
# Lives: _                     =======  #
#                                       #
#########################################
*/