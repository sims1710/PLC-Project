/* Update the pointer for the hidden word display */
#include <string.h>
#include "all_functions.h"

typedef enum{
    START,
    CHECK_LETTER,
    UPDATE_LETTER,
    CONTINUE_SEARCH,
    END
}State;

void update_hidden_word(char *hidden_word, char *chosen_word, char input_letter)
{
    State currentState = START;
    int i = 0;
    int length = strlen(chosen_word); 

    while (currentState != END) {
        switch (currentState) {
            case START:
                i = 0; 
                currentState = CHECK_LETTER;
                break;
            case CHECK_LETTER:
                if (i >= length) {
                    /*End if all letters have been checked*/
                    currentState = END; 
                } else if (chosen_word[i] == input_letter) {
                    /*Match found, update the letter*/
                    currentState = UPDATE_LETTER; 
                } else {
                    /*No match, move to the next letter*/
                    currentState = CONTINUE_SEARCH; 
                }
                break;
            case UPDATE_LETTER:
                /*Update the hidden word with the input letter*/
                hidden_word[i] = input_letter; 
                /*Continue search after updating*/
                currentState = CONTINUE_SEARCH; 
                break;
            case CONTINUE_SEARCH:
                i++; 
                /*Check the next letter*/
                currentState = CHECK_LETTER; 
                break;
            case END:
                /*Exit the loop*/
                break;
        }
    }
}
