# include "all_functions.h"

/* Function to play Endless Mode - Misses positioning */ 
void endless_mode()
{
    FILE *fp;
    char filename[] = "words.txt";
    char *chosen_word;
    char hidden_word[MAX_NAME_LENGTH];
    char guessed_letters[MAX_NAME_LENGTH];
    int lives = 0;
    int score = 0;
    int word_len;
    char input_letter;
    int i = 0;
    int guessed = 0;

    /*  Open file in read mode */ 
    fp = fopen(filename, "r");

    /*  Check if file is opened */ 
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    /*  Read words from file */ 
    while (fscanf(fp, "%s", chosen_word) != EOF)
    {
        word_len = strlen(chosen_word);

        for (i = 0; i < word_len; i++)
        {
            hidden_word[i] = '_';
        }
        hidden_word[i] = '\0';

        for (i = 0; i < MAX_NAME_LENGTH; i++)
        {
            guessed_letters[i] = ' ';
        }

        /*  Play game */ 
        while (guessed == 0)
        {
            printf("Word: %s\n", hidden_word);
            printf("Guessed Letters: %s\n", guessed_letters);
            player_input(chosen_word, hidden_word, guessed_letters,  &lives, word_len ,&score);

            /*  Check if player has guessed word */ 
            if (strcmp(chosen_word, hidden_word) == 0)
            {
                printf("Congratulations! You have guessed the word!\n");
                guessed = 1;
                break;
            }

            /*  Check if player wants to exit */ 
            if (input_letter == EXIT_CHAR) {
                printf("Exiting endless mode.\n");
                exit(0);
            }
        }

        /*  Update score */ 
        score_tracker(&score, &lives);
    }

    /*  Upon winning */ 
    add_new_word();
    fclose(fp);
}

