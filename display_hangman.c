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
                printf("# Score:");
                int base = 8;
                /* TODO: print out score value and  give len of score*/
                int score_len;
                int i;
                for (i = base + score_len; i < window_width - 1; i++)
                {
                    printf(" ");
                }
                printf("#");
                break;
            case 2:
                printf("#                                +---+  #");
                break;
            case 3:
                /* Hint */
                int hint_len;
                printf("#    Hint: ");
                break;
            case 4:
                /* Head + Hint code*/
                break;
            case 5:
                /* Upper */
                if (*lives <= 3)
                {
                    printf("#                               /|\\  |  #");
                }
                else if (*lives == 4)
                {
                    printf("#                               /|   |  #");
                }
                else if (*lives == 5)
                {
                    printf("#                                |   |  #");
                }
                else
                {
                    printf("#                                    |  #");
                }
                break;
            case 6:
                /* Middle  + Hidden Word */
                if (*lives > 2)
                {
                    /* no middle */
                }
                else
                {
                    /* have middle */
                }
                break;
            case 7:
                /* Legs  + Number Code*/
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
#    Hint: _  _  _               |   |  #
#          __ __ __              O   |  #
#                               /|\  |  #
#    _  _  _  _  _  _  _         |   |  #
#    __ __ __ __ __ __ __       / \  |  #
#                                    |  #
# Lives: _                     =======  #
#                                       #
#########################################
*/
