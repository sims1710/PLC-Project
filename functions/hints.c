#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "all_functions.h"

/* This function will generate random numbers for the chosen word where it will be used as a hint
   for each letter of the word, they will have distinct integer from 1 to 26, for example, h will be associated with 13
   but when the word contains same letter, the same letter will have the same integer

   @param chosen_word: is a string which is the word that the player will need to guess
          word_len: is an Integer to keep track of the word's length
   @return an array of integer, each integer is associated to each letter in the word, the length of the array is equal to the word length
*/
int* random_number(char* chosen_word, int word_len){
    int i, index;
    int letter_numbers[26] = {0};
    int* numbers_for_words = (int*)malloc(sizeof(int)*word_len);

    /*using time as the seed to generate random integer everytime*/
    srand((unsigned int)time(NULL));
    for(i=0; chosen_word[i]!= '\0'; i++){
        /*checking if no number has been generated for the particular letter */
        index = chosen_word[i] - 'a';
        if(letter_numbers[index] == 0){
            letter_numbers[index] = rand() % 26 + 1;
        }
        numbers_for_words[i] = letter_numbers[index];
    }
    return numbers_for_words;
}

 /* suggest_hint function is to allow players to use 2 hints to guess the letter
    the hints rules are as follows:
        1. First hint used doesn't require points (no point will be deducted from the player)
        2. The second hint require points to be deducted which depends on the player's game difficulty
           The cost of the hint are as follows:
                - easy and medium: 1 point
                - hard: 2 points
    
    @param chosen_word: is a string which is the word that the player will need to guess
           guessed_letters: is an array of character of the letters that had been guessed by the player
           game_levels: is a pointer to the struct GameLevels
           hints_given: is an array of integer to check how many hints that the player had used
           player_points: is an integer pointer to keep track of how many points that the players have
    @return an integer which is the random integer retreived from the function random_number and will be used as a hint for the player (hint for a letter in the word)
 */
int suggest_hint(char* chosen_word, char *guessed_letters, game_level *game_levels, int* hints_given, int* player_points){
    int i, hint;
    int* random_integers;
    int word_len;

    /*Determine the cost of the second hint used based on the difficulty level*/
    const int hint_cost = game_levels->difficulty == 3 ? 2 : 1;
    /*Getting the length of the word*/
    word_len = game_levels->chosenDiff.word_len;

    /*Getting an array of random integers according to the chosen_word*/
    random_integers = random_number(chosen_word, word_len);

    /*Check if hint is available */
    if(*hints_given >= 2){
        printf("No more hints available.\n");
        return 0; 
    }

    /*Check if this is the second hint and if the player has enough points*/
    if(*hints_given == 1 && *player_points < hint_cost){
        printf("Not enough points for a hint.\n");
        return 0; 
    }

    /*Deduct the point for using the hint*/
    if(*hints_given == 1){
        *player_points -= hint_cost;
    }

    /*Provide the hint*/
    for(i = 0; i < word_len; i++){
        if(strchr(guessed_letters, chosen_word[i]) == NULL){
            hint = random_integers[i];
            break; 
        }
    }

    (*hints_given)++; 
    return hint;
}
