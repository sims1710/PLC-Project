#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "all_functions.h"

int* random_number(char* chosen_word, int word_len){
    int i, index;
    int letter_numbers[26] = {0};
    int* numbers_for_words = (int*)malloc(sizeof(int)*word_len);

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

 /* hints only given 2 times in a game 
    first hint is free, second hint need points
    the exchange as follows: 
        - difficulty easy and medium: 1 point
        - difficulty hard: 2 points  */
/* TODO: need to get the difficulty variable */
int suggest_hint(char* chosen_word, int* numbers_hint, char *guessed_letters, GameLevels *gamelevel, int* hints_given, int* player_points){
    int i, hint;
    int* random_integers;
    int word_len;
    const int hint_cost = gamelevel->difficulty == 3 ? 2 : 1;
    word_len = gamelevel->chosenDiff.word_len;

    random_integers = random_number(chosen_word, word_len);

    /*Check if hint is available */
    if(*hints_given >= 2){
        printf("No more hints available.\n");
        return 0; 
    }

    /*check if this is the second hint and if the player has enough points*/
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
