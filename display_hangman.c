/* Print out the hangman screen on console */
#include "all_functions.h"

void display_hangman(char *hidden_word, int *lives, int word_len)
{
    /* Clear terminal */
    clear_screen();
    /* Start printing in format */
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