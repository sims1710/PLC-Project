# Code Documentation
This file contains the code documentation of the following files: [`main.c`](https://github.com/sims1710/PLC-Project/blob/main/main.c), [`game_functions.c`](https://github.com/sims1710/PLC-Project/blob/main/game_functions.c), [`game_modes.c`](https://github.com/sims1710/PLC-Project/blob/main/game_modes.c), [`ui.c`](https://github.com/sims1710/PLC-Project/blob/main/ui.c), [`leaderboard.c`](https://github.com/sims1710/PLC-Project/blob/main/leaderboard.c) and [`clear_functions.c`]() for the revamped Hangman Game Project.

## [main.c](https://github.com/sims1710/PLC-Project/blob/main/main.c):
This file is the backbone of the code. It orchestrates a text-based hangman game, managing game setup, player input, gameplay mechanics such as word guessing and hint usage, score tracking, and interaction with other modules for UI display and leaderboard management. Its equivalent .h file is [game_structure.h](https://github.com/sims1710/PLC-Project/blob/main/game_structures.h) which has structures storing information related to game difficulty and progression, including details about word files, word lengths, current levels, and game difficulty settings.

#### 1. Choice (enum structure):

This typedef enum defines different choices available in the game menu.
    Players can select options like starting a new game, entering multiplayer mode,
    checking the leaderboard, attacking in a game, viewing game rules, going back to the main menu,
    or ending the game.

    Values:
    - NEW_GAME: Represents starting a new game (value = 1).
    - MULTIPLAYER: Represents entering multiplayer mode (value = 2).
    - LEADERBOARD: Represents checking the leaderboard (value = 3).
    - ATTACK: Represents attacking in a game (value = 4).
    - GAMERULE: Represents viewing game rules (value = 5).
    - MAIN_MENU: Represents going back to the main menu (value = 6).
    - END: Represents ending the game (value = 0).

#### 2. Difficulty (enum structure):

This typedef enum defines different difficulty levels available in the game.
    Players can choose between easy, medium, and hard difficulty levels.

    Values:
    - EASY: Represents the easy difficulty level (value = 1).
    - MEDIUM: Represents the medium difficulty level (value = 2).
    - HARD: Represents the hard difficulty level (value = 3).

#### 3. int main function:

This main function controls the execution flow of a Hangman game program. It includes game initialization, memory allocation, menu handling, gameplay logic, and resource deallocation.

    @param argc: The number of command-line arguments.
           argv: An array of strings representing the command-line arguments.
           
    @return Returns 0 on successful execution, or 1 if memory allocation fails.

**Functions used in main:**

1. void display_rules() : Display the rules of the hangman game.
2. void main_menu(int *currentState, game_level *game_levels, char *name) : Display the main menu and handle user input.
3. void load_game_state(int *lives, int *score, char *guessed_letters, char *chosen_word, int difficulty, int *hints_given) : Load a saved game state if available.
4. void get_word(struct difficultyLevel *chosenDiff, char *chosen_word) : Get a random word based on the chosen difficulty level.
5. void display_hangman(char *chosen_word, char *hidden_word, int *lives, int word_len, char *hint_char, int *hint_integer, int *hints_given, int *score) : Display the hangman interface with the hidden word, guessed letters, hangman status, etc.
6. void clear_stdin() : Clear input buffer.
7. void suggest_hint(char *chosen_word, char *guessed_letters, game_level *game_levels, int *hints_given, int *score, int *hint_integer, char *hint_char) : Provide a hint to the player based on the chosen word and guessed letters.
8. void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *score) : Process player input during the game.
9. void score_tracker(int *score, int *lives) : Track the player's score and remaining lives.
10. void update_game_level(game_level *game_levels) : Update the game level after successfully guessing a word.
11. void updateLeaderboard(char *name, int score, int difficulty) : Update the leaderboard with the player's name, score, and difficulty level.
12. void displayLeaderboard() : Display the leaderboard.
13. void time_attack_mode(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *score) : Start the time attack mode where the player has a time limit to guess a word.
14. void choose_difficulty(game_level *game_levels) : Choose the difficulty level for the game.
15. void multiplayer_mode() : Multiplayer mode functionality.
16. void addToLeaderboard(char *name, int score, int difficulty) : Add player's score to the leaderboard.

## [game_functions.c:](https://github.com/sims1710/PLC-Project/blob/main/game_functions.c)
The functions in the file manage game setup, gameplay mechanics like player input and word updates, and also handle cheat/hint functionalities such as revealing letters and managing player scores. Additionally, there are utility functions for generating random integers and tracking game progress, including challenge completion and leaderboard display. The function prototypes are defined in [game_functions.h](https://github.com/sims1710/PLC-Project/blob/main/game_functions.h).

#### 1. State (enum structure):

The State enum represents different states or phases in the game's logic or workflow.

    Values:
    - START: Initial state or starting point of a particular process or action.
    - CHECK_LETTER: State for checking a letter, such as verifying if a guessed letter is correct.
    - UPDATE_LETTER: State for updating a letter, typically used after confirming a correct guess.
    - CONTINUE_SEARCH: State for continuing the search or iteration process, often used in loops or sequential checks.
    - END: Final state or endpoint of a process or action, marking its completion or termination.

These states are used to manage the flow of operations and decision-making within the game or program.

#### 2. void choose_difficulty(game_level *game_levels):

It allows the player to select a difficulty level for the game. It displays the available difficulties (Easy, Medium, Hard) and prompts the player to choose one by entering a corresponding number.

    @param game_levels: A pointer to the game_level structure where the chosen difficulty will be stored.
    
    @return void - The function does not return anything but updates the game_levels structure.

#### 3. void update_game_level(game_level *game_levels):

The function updates the current level of the game based on the difficulty mode selected by the player. It determines the sequence of words to be guessed according to the chosen difficulty level.

    @param game_levels: A pointer to the game_level structure containing the current level and difficulty.
    
    @return void - The function does not return anything but updates the game_levels structure with the new level and word length.

#### 4. void get_word(chosen_difficulty *file_set, char *chosen_word):

The get_word function retrieves a word from a specified file based on the chosen difficulty level and word length.

    @param file_set: A pointer to the chosen_difficulty structure containing the filename and word length information.
           chosen_word: A pointer to the character array where the retrieved word will be stored.
           
    @return void - The function does not return anything but updates the chosen_word array with the retrieved word.

#### 5. void player_input(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *score):

The function handles player input during the game, checking for validity, updating hidden word, and managing lives.

    @param chosen_word: A pointer to the chosen word in the game.
           hidden_word: A pointer to the hidden word where guessed letters are updated.
           guessed_letters: A pointer to an array containing guessed letters.
           lives: A pointer to the player's remaining lives.
           word_len: The length of the word to be guessed.
           score: A pointer to the player's score.
        
    @return void - The function does not return anything but updates game parameters based on player input.

#### 6. void update_hidden_word(char *hidden_word, char *chosen_word, char input_letter):

It updates the hidden word based on the player's input letter and the chosen word.

    @param hidden_word: A pointer to the hidden word where guessed letters are updated.
           chosen_word: A pointer to the chosen word in the game.
           input_letter: The letter input by the player.
           
    @return void - The function does not return anything but updates the hidden_word array.

#### 7. void link_number(int *hint_integer):

The link_number function generates random numbers linked to letters for hints implementation.

    @param hint_integer: A pointer to an integer array where the random numbers will be stored.
    
    @return void - The function does not return anything but updates the hint_integer array.

#### 8. void suggest_hint(char *chosen_word, char *guessed_letters, game_level *game_levels, int *hints_given, int *player_points, int *hint_integer, char *hint_char):

It suggests a hint to the player during the game, revealing a letter in the word.

    @param chosen_word: A pointer to the chosen word in the game.
           guessed_letters: A pointer to an array containing guessed letters.
           game_levels: A pointer to the game_level structure containing difficulty information.
           hints_given: A pointer to the number of hints given to the player.
           player_points: A pointer to the player's points.
           hint_integer: A pointer to an integer array containing random numbers linked to letters.
           hint_char: A pointer to a character array where the hint letter will be stored.
           
    @return void - The function does not return anything but updates game parameters.

#### 9. void score_tracker(int *score, int *lives):

The function tracks the player's score and manages game challenges.

    @param score: A pointer to the player's score.
           lives: A pointer to the player's remaining lives.
           
    @return void - The function does not return anything but manages score and challenges.

## [game_modes.c](https://github.com/sims1710/PLC-Project/blob/main/game_modes.c)
Here, the functions facilitate gameplay modes including a time-limited word guessing mode, gathering player names, and orchestrating a multiplayer word guessing game with lives and scoring, all within turn-based mechanics. The file [game_modes.h](https://github.com/sims1710/PLC-Project/blob/main/game_modes.h) houses the function prototypes for game_modes.c.

#### 1. void time_attack_mode(char *chosen_word, char *hidden_word, char *guessed_letters, int *lives, int word_len, int *scores):

The time_attack_mode function implements a time-limited guessing game mode, where the player has a fixed time (4 minutes) to guess a word. If the player guesses the word within the time limit, they win; otherwise, they lose either by running out of time or lives.

    @param chosen_word: The word that the player needs to guess.
           hidden_word: The hidden version of the word that displays guessed letters.
           guessed_letters: An array of characters representing letters guessed by the player.
           lives: A pointer to the player's remaining lives.
           word_len: The length of the word to be guessed.
           scores: A pointer to the player's scores.

    @return This function does not return any value. It continues to loop until either the time or lives run out.

#### 2. void enter_name(char name[]):

The enter_name function prompts the user to enter their name and reads the input from stdin.

    @param name: An array to store the user's name.

    @return This function does not return any value. It updates the 'name' array with the user's input.

#### 3. void multiplayer_mode(void):

The multiplayer_mode function implements a two-player word guessing game mode where players take turns guessing a word. The game continues until one of the players runs out of lives.

    @param None.

    @return This function does not return any value. It displays game prompts and messages during gameplay.

## [ui.c](https://github.com/sims1710/PLC-Project/blob/main/ui.c):
The functions in ui.c validate user input, manage the game menu, display game rules in HTML, and print the hangman screen in the console during gameplay. The function prototypes are declared in [ui.h](https://github.com/sims1710/PLC-Project/blob/main/ui.h).

#### 1. The Choice and Difficulty enums:

They are the same enum as declared in main.c.

#### 2. int validateChoice(int start, int end):

It validates user input to ensure it falls within a specified range.

    @param start: The start of the range for valid input.
           end: The end of the range for valid input.
    
    @return The validated user choice within the specified range.

#### 3. void enter_player_name(char *name):
The function prompts the player to enter their name.

    @param name: Pointer to store the entered player name.

    @return This function does not return any value.

#### 4. void main_menu(int *current_state, game_level *game_levels, char *name):

The main_menu function Displays the main menu of the game and processes user input for menu choices.

    @param current_state: Pointer to the current state of the game.
           game_levels: Pointer to the game levels structure.
           name: Pointer to store the player's name.

    @return This function does not return any value.

#### 5. void display_rules(void):

It creates and displays the game rules in an HTML format.

    Note: This function also opens the rules in the default web browser.

    @return This function does not return any value.

#### 6. void display_hangman(char *chosen_word, char *hidden_word, int *lives, int word_len, char *hint_letter, int *hint_code, int *hints_given, int *score):

The function prints the hangman screen with game-related information.

    @param chosen_word: The word to be guessed by the player.
           hidden_word: The player's progress in guessing the word.
           lives: Pointer to the player's remaining lives.
           word_len: The length of the word to be guessed.
           hint_letter: The hint letter given to the player.
           hint_code: An array representing the hint code for each letter in the word.
           hints_given: Pointer to the number of hints given to the player.
           score: Pointer to the player's score.

    @return This function does not return any value.

## [leaderboard.c](https://github.com/sims1710/PLC-Project/blob/main/leaderboard.c): 
The functions manage a game leaderboard by adding entries, sorting them, generating HTML for display, and updating scores. They also include platform-specific code to open the leaderboard in the default web browser. The file [leaderboard.h](https://github.com/sims1710/PLC-Project/blob/main/leaderboard.h) has the function prototypes of the aforementioned functions.

#### 



