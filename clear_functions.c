#include <stdio.h>
#include "clear_functions.h"

/* Code empties console screen when called */
void clear_screen(void)
{   
    /*using octal notation*/
    printf("\033[1;1H\033[2J");
    /*printf("\e[1;1H\e[2J");*/
}

/* Empty the stdin */
void clear_stdin(void)
{
    while ((getchar()) != '\n');
}
