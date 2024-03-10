/* Update the pointer for the hidden word display */
#include <string.h>
#include "all_functions.h"

void update_hidden_word(char *hidden_word, char *chosen_word, char input_letter)
{
    int i;
    for(i=0; i<strlen(chosen_word);i++){
        if(input_letter == chosen_word[i]){
            hidden_word[i] = input_letter;
        }
    }
}
