# include "all_functions.h"

/* Function to add a new word upon winning */ 
void add_new_word()
{
    FILE *fp;
    char new_word[MAX_NAME_LENGTH];
    char filename[] = "words.txt";
    int word_len;

    /* Open file in append mode */ 
    fp = fopen(filename, "a");

    /* Check if file is opened */ 
    if (fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    /* Get new word from player */ 
    do {
        printf("Enter a new word: ");
        scanf("%s", new_word);

        /* Check if word is valid */ 
        word_len = strlen(new_word);
        if (word_len < 4 || word_len > 7) {
            printf("Word must be between 4 and 7 characters long\n");
        }
    } while (word_len < 4 || word_len > 7);

    /* Write word to file */ 
    fprintf(fp, "%s\n", new_word);

    fclose(fp);
}