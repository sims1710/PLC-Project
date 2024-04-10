#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "leaderboard.h"

/* For opening the HTML files */
#ifdef _WIN32
    #include <windows.h>
#elif __APPLE__
#elif __linux__
#endif

/* Define a struct for leaderboard entries */
typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
    int mode;
} LeaderboardEntry;

LeaderboardEntry leaderboard[MAX_LEADERBOARD_ENTRIES];
int numEntries = 0;

/* Function to add an entry to the leaderboard */
void addToLeaderboard(const char *name, int score, int mode) {
    if (numEntries < MAX_LEADERBOARD_ENTRIES) {
        strncpy(leaderboard[numEntries].name, name, MAX_NAME_LENGTH - 1);
        leaderboard[numEntries].name[MAX_NAME_LENGTH - 1] = '\0'; 
        leaderboard[numEntries].score = score;
        leaderboard[numEntries].mode = mode;
        numEntries++;
    } else {
        printf("Leaderboard is full. Cannot add more entries.\n");
    }
}

/* Function to sort the leaderboard using bubble sort */
void bubbleSortLeaderboard(void) {
    int i, j;
    LeaderboardEntry temp;

    for (i = 0; i < numEntries - 1; i++) {
        for (j = 0; j < numEntries - i - 1; j++) {
            if (leaderboard[j].score < leaderboard[j + 1].score) {
                temp = leaderboard[j];
                leaderboard[j] = leaderboard[j + 1];
                leaderboard[j + 1] = temp;
            }
        }
    }
}

/* Function to generate HTML for the leaderboard */
void generateLeaderboardHTML(void) {
    int count = 0;
    int i;
    int mode;

    FILE *fp = fopen("leaderboard.html", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    /* HTML code for styling and leaderboard structure */
    fprintf(fp, "<!DOCTYPE html>\n");
    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "<title>Leaderboard</title>\n");
    fprintf(fp, "<link rel=\"icon\" href=\"hangman.webp\" type=\"image/webp\">\n");
    fprintf(fp, "<style>\n");
    fprintf(fp, "body {\n");
    fprintf(fp, "    background-image: url('/background.png') !important;\n");
    fprintf(fp, "    font-family: Arial, sans-serif;\n");
    fprintf(fp, "    background-size: cover;\n");
    fprintf(fp, "    background-size: 80%%; /* Adjust the percentages as needed */\n");
    fprintf(fp, "}\n");
    fprintf(fp, ".heading-box {\n");
    fprintf(fp, "    padding: 10px;\n");
    fprintf(fp, "    text-align: center;\n");
    fprintf(fp, "}\n");
    fprintf(fp, ".heading-text {\n");
    fprintf(fp, "    font-size: 48px;\n");
    fprintf(fp, "    display: inline-block;\n");
    fprintf(fp, "    animation: changeColor 3s infinite;\n");
    fprintf(fp, "}\n");
    fprintf(fp, "@keyframes changeColor {\n");
    fprintf(fp, "    0%% { color: red; }\n");
    fprintf(fp, "    25%% { color: green; }\n");
    fprintf(fp, "    50%% { color: blue; }\n");
    fprintf(fp, "    75%% { color: yellow; }\n");
    fprintf(fp, "    100%% { color: orange; }\n");
    fprintf(fp, "}\n");
    fprintf(fp, ".container {\n");
    fprintf(fp, "    width: 800px;\n");
    fprintf(fp, "    margin: 0 auto;\n");
    fprintf(fp, "    padding: 20px;\n");
    fprintf(fp, "}\n");
    fprintf(fp, ".logo {\n");
    fprintf(fp, "    display: block;\n");
    fprintf(fp, "    margin: 0 auto 20px;\n");
    fprintf(fp, "}\n");
    fprintf(fp, ".heading-box {\n");
    fprintf(fp, "    background-color: #000000;\n");
    fprintf(fp, "    padding: 10px;\n");
    fprintf(fp, "    text-align: center;\n");
    fprintf(fp, "}\n");
    fprintf(fp, ".mode-heading-box {\n");
    fprintf(fp, "    background-color: #000000;\n");
    fprintf(fp, "    color: #ffffff;\n");
    fprintf(fp, "    padding: 10px;\n");
    fprintf(fp, "    text-align: left;\n");
    fprintf(fp, "}\n");
    fprintf(fp, ".glow-text {\n");
    fprintf(fp, "    color: #ffffff;\n");
    fprintf(fp, "    animation: glow 2s ease-in-out infinite alternate;\n");
    fprintf(fp, "}\n");
    fprintf(fp, "@keyframes glow {\n");
    fprintf(fp, "    0%% { text-shadow: 0 0 10px #ffffff, 0 0 20px #ffffff, 0 0 30px #ffffff, 0 0 40px #ffffff, 0 0 70px #ffffff, 0 0 80px #ffffff, 0 0 100px #ffffff, 0 0 150px #ffffff; }\n");
    fprintf(fp, "    50%% { text-shadow: 0 0 5px #ffffff, 0 0 10px #ffffff, 0 0 15px #ffffff, 0 0 20px #ffffff, 0 0 35px #ffffff, 0 0 40px #ffffff, 0 0 50px #ffffff, 0 0 75px #ffffff; }\n");
    fprintf(fp, "    100%% { text-shadow: 0 0 20px #ffffff, 0 0 30px #ffffff, 0 0 40px #ffffff, 0 0 80px #ffffff, 0 0 100px #ffffff, 0 0 150px #ffffff, 0 0 200px #ffffff, 0 0 300px #ffffff; }\n");
    fprintf(fp, "}\n");
    fprintf(fp, "table {\n");
    fprintf(fp, "    width: 100%%;\n");
    fprintf(fp, "    border-collapse: collapse;\n");
    fprintf(fp, "}\n");
    fprintf(fp, "th, td {\n");
    fprintf(fp, "    padding: 8px;\n");
    fprintf(fp, "    text-align: left;\n");
    fprintf(fp, "}\n");
    fprintf(fp, "th {\n");
    fprintf(fp, "    background-color: #ffffff; /* White background for headers */\n");
    fprintf(fp, "    color: #000000; /* Black text for headers */\n");
    fprintf(fp, "    transition: background-color 0.3s, color 0.3s; /* Smooth transition effect */\n");
    fprintf(fp, "}\n");
    fprintf(fp, "tr:nth-child(even) {\n");
    fprintf(fp, "    background-color: #e5e5e5; /* Paler black background for even rows */\n");
    fprintf(fp, "    transition: background-color 0.3s; /* Smooth transition effect */\n");
    fprintf(fp, "}\n");
    fprintf(fp, "tr:nth-child(odd) {\n");
    fprintf(fp, "    background-color: #cccccc; /* Slightly darker paler black background for odd rows */\n");
    fprintf(fp, "    transition: background-color 0.3s; /* Smooth transition effect */\n");
    fprintf(fp, "}\n");
    fprintf(fp, "tr:hover {\n");
    fprintf(fp, "    background-color: #808080; /* Grey background on hover for rows */\n");
    fprintf(fp, "}\n");
    fprintf(fp, "tr:hover td {\n");
    fprintf(fp, "    color: #000000; /* Black text on hover for rows */\n");
    fprintf(fp, "}\n");
    fprintf(fp, "</style>\n");
    fprintf(fp, "</head>\n");
    fprintf(fp, "<body>\n");
    fprintf(fp, "<div class='container'>\n");
    fprintf(fp, "<div class='heading-box'>\n");
    fprintf(fp, "<h1 class=\"heading-text\">Leaderboard</h1>\n");
    fprintf(fp, "</div>\n");
    fprintf(fp, "</div>\n");

    fprintf(fp, "<div style='display: flex; flex-direction: column; align-items: center;'>\n");

    /* Generate table for each mode */ 
    for (mode = 1; mode <= 3; mode++) {
        const char *modeName;
        switch (mode) {
            case 1:
                modeName = "Easy";
                break;
            case 2:
                modeName = "Medium";
                break;
            case 3:
                modeName = "Hard";
                break;
            default:
                modeName = "Unknown";
                break;
        }
        fprintf(fp, "<div class='container'>\n");
        fprintf(fp, "<div class='mode-heading-box'>\n");
        fprintf(fp, "<h2 class='glow-text' style='padding: 20px;'>Mode %s</h2>\n", modeName);
        fprintf(fp, "</div>\n");
        fprintf(fp, "<table>\n");
        fprintf(fp, "<tr><th>RANK</th><th>NAME</th><th>SCORE</th></tr>\n");

        
        for (i = 0; i < numEntries && count < 10; i++) {
            if (leaderboard[i].mode == mode) {
                fprintf(fp, "<tr><td>%d</td><td>%s</td><td>%d</td></tr>\n",
                        count + 1, leaderboard[i].name, leaderboard[i].score);
                count++;
            }
        }

        /* Add dummy rows if count is less than 10 */
        while (count < 10) {
            fprintf(fp, "<tr><td>%d</td><td>%s</td><td>%d</td></tr>\n",
                    count + 1, "Dummy", 0);
            count++;
        }

        fprintf(fp, "</table>\n");
        fprintf(fp, "</div>\n"); 
    }

    fprintf(fp, "</div>\n"); 
    fprintf(fp, "</body>\n");
    fprintf(fp, "</html>\n");


    fclose(fp);
}

void displayLeaderboard(void) {
    #ifdef _WIN32
        /* Open the HTML file using the default web browser on Windows */
        ShellExecute(NULL, "open", "leaderboard.html", NULL, NULL, SW_SHOWNORMAL);
    #elif __APPLE__
        /* Open the HTML file using the default web browser on macOS */
        system("open leaderboard.html");
    #elif __linux__
        /* Open the HTML file using the default web browser on Linux */
        system("xdg-open leaderboard.html");
    #endif
}

/* Function to update the leaderboard with a new score for a specific mode */
void updateLeaderboard(int score, int mode) {
    addToLeaderboard("Player", score, mode); /* Assuming mode 1 for this example */
    bubbleSortLeaderboard();
    generateLeaderboardHTML();
}
