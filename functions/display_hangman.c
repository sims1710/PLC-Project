/* Print out the hangman screen on console */
#include "all_functions.h"

void display_hangman(char *chosen_word, char *hidden_word, int *lives, int word_len, char *hint_letter, int *hint_code, int hints_given, int *score)
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
                printf("# Score: %03d", *score);
                int base = 12;
                /* TODO: print out score value and  give len of score*/
                int i;
                for (i = base; i < window_width - 1; i++)
                {
                    printf(" ");
                }
                printf("#");
                break;
            case 2:
                printf("#");
                int base = 1;
                int i;
                for (i = base; i < window_width - 8; i++)
                {
                    printf(" ");
                }
                printf("+---+  #");
                break;
            case 3:
                /* Hint */
                printf("#    Hint: ");
                // int base = 11;
                switch (hints_given)
                {
                case 0:
                    printf("_  _ ");
                    break;
                case 1:
                    printf("%c  _ ", hint_letter[0]);
                    break;
                case 2:
                    printf("%c  %c ", hint_letter[0], hint_letter[1]);
                    break;
                default:
                    printf("You shouldn't see this");
                    break;
                }
                int base = 16;
                int i;
                for (i = base; i < window_width - 8; i++)
                {
                    printf(" ");
                }
                printf("|   |  #");
                break;
            case 4:
                /* Head + Hint code*/
                printf("           ");
                // int base = 11;
                printf("%02d %02d", hint_code[hint_letter[0] - 'a'], hint_code[hint_letter[1] - 'a']);
                int base = 16;
                int i;
                for (i = base; i < window_width - 8; i++)
                {
                    printf(" ");
                }
                if (*lives == MAX_LIVES)
                {
                    printf("    |  #");
                }
                else
                {
                    printf("O   |  #");
                }
                break;
            case 5:
                /* Upper */
                printf("#");
                int base = 1;
                for (i = base; i < window_width - 9; i++)
                {
                    printf(" ");
                }
                if (*lives <= 3)
                {
                    printf("/|\\  |  #");
                }
                else if (*lives == 4)
                {
                    printf("/|   |  #");
                }
                else if (*lives == 5)
                {
                    printf(" |   |  #");
                }
                else
                {
                    printf("     |  #");
                }
                break;
            case 6:
                /* Middle  + Hidden Word */
                printf("#   ");
                // int base = 4;
                // char *hidden_word must contain underscores
                int i;
                for (i = 0; i < word_len; i++)
                {
                    printf("%c  ", hidden_word[i]);
                }
                int base = 4 + (word_len * 3);
                for (i = base; i < window_width - 8; i++)
                {
                    printf(" ");
                }
                if (*lives > 2)
                {
                    printf("    |  #");
                }
                else
                {
                    printf("|   |  #");
                }
                break;
            case 7:
                /* Legs  + Number Code*/
                printf("#   ");
                // int base = 4;
                int i;
                for (i = 0; i < word_len; i++)
                {
                    printf("%02d ", hint_code[chosen_word[i] - 'a']);
                }
                int base = 4 + (word_len * 3);
                for (i = base; i < window_width - 9; i++)
                {
                    printf(" ");
                }
                if (*lives == 0)
                {
                    printf("/ \\  |  #");
                }
                else if (*lives == 1)
                {
                    printf("/    |  #");
                }
                else
                {
                    printf("     |  #");
                }
                break;
            case 8:
                printf("#");
                int base = 1;
                int i;
                for (i = base; i < window_width - 4; i++)
                {
                    printf(" ");
                }
                printf("|  #");
                break;
            case 9:
                printf("# Lives: %d", *lives);
                int base = 10;
                for (i = base; i < window_width - 10; i++)
                {
                    printf("=======  #");
                }
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
# Score: 000                            #
#                                +---+  #
#    Hint: _  _                  |   |  #
#          __ __                 O   |  #
#                               /|\  |  #
#    _  _  _  _  _  _  _         |   |  #
#    __ __ __ __ __ __ __       / \  |  #
#                                    |  #
# Lives: _                     =======  #
#                                       #
#########################################
*/
