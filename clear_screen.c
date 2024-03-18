/* Code empties console screen when called */
#include "all_functions.h"

void clear_screen()
{
    printf("\e[1;1H\e[2J");
}