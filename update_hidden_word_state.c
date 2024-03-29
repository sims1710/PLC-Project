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
    int length = strlen(chosen_word); // Get the length once to improve efficiency

    while (currentState != END) {
        switch (currentState) {
            case START:
                i = 0; // Initialize the index
                currentState = CHECK_LETTER;
                break;
            case CHECK_LETTER:
                if (i >= length) {
                    currentState = END; // End if all letters have been checked
                } else if (chosen_word[i] == input_letter) {
                    currentState = UPDATE_LETTER; // Match found, update the letter
                } else {
                    currentState = CONTINUE_SEARCH; // No match, move to the next letter
                }
                break;
            case UPDATE_LETTER:
                hidden_word[i] = input_letter; // Update the hidden word with the input letter
                currentState = CONTINUE_SEARCH; // Continue search after updating
                break;
            case CONTINUE_SEARCH:
                i++; // Move to the next character
                currentState = CHECK_LETTER; // Check the next letter
                break;
            case END:
                // Exit the loop
                break;
        }
    }
}
