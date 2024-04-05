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

/* Using the State struct to keep track of the letter guessed by the player
   this function will end (when reach the END state) when all of the letters have been checked
   and it will check the input letter when it reach the CHECK_LETTER state 
   
   @param hidden_word: is a string that is the player that need to guess and will updated the guess letter into this string
          chosen_word: is a string which is the word that the player need to guess and will be used to check against hidden_word
          input_letter: is a character that the player inputs
   @return return nothing because it is updating the hidden_word string character upon successful guess*/
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
