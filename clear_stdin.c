/* Empty the stdin */
#include "all_functions.h"

void clear_stdin()
{
    while ((getchar()) != '\n')
        ;
}
