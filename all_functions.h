/* Define all planned functions here, include in all c files (TEMPORARY)*/

/* Return filename to read from, no external input, only player input inside function */
char *choose_difficulty();

/* Return a selected word, function input is filename */
char *get_word(char *filename);

/* Update contents of pointer for hidden word, return nothing, function input is pointer to hidden word display and chosen word */
void update_hidden_word(char *hidden_word, char *chosen_word, char input_letter);

/* Check player input, invalid if number or already guessed, run if update if hit. function input is the selected word, hidden word display  */
void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives);