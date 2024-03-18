# include "all_functions.h"

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
    int mode;
} LeaderboardEntry;

LeaderboardEntry leaderboard[MAX_ENTRIES];
int numEntries = 0;

void addToLeaderboard(const char *name, int score, int mode) {
    if (numEntries < MAX_ENTRIES) {
        strncpy(leaderboard[numEntries].name, name, MAX_NAME_LENGTH - 1);
        leaderboard[numEntries].name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination
        leaderboard[numEntries].score = score;
        leaderboard[numEntries].mode = mode;
        numEntries++;
    } else {
        printf("Leaderboard is full. Cannot add more entries.\n");
    }
}

void bubbleSortLeaderboard() {
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

void generateLeaderboardHTML() {
    FILE *fp = fopen("leaderboard.html", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    fprintf(fp, "<!DOCTYPE html>\n");
    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "<title>Leaderboard</title>\n");
    fprintf(fp, "<style>\n");
    fprintf(fp, "body {\n");
    fprintf(fp, "    background-image: url('background.jpg');\n"); // Change 'background.jpg' to your image file
    fprintf(fp, "    background-size: cover;\n");
    fprintf(fp, "    font-family: Arial, sans-serif;\n");
    fprintf(fp, "}\n");
    fprintf(fp, ".container {\n");
    fprintf(fp, "    max-width: 800px;\n");
    fprintf(fp, "    margin: 0 auto;\n");
    fprintf(fp, "    padding: 20px;\n");
    fprintf(fp, "}\n");
    fprintf(fp, ".logo {\n");
    fprintf(fp, "    display: block;\n");
    fprintf(fp, "    margin: 0 auto 20px;\n");
    fprintf(fp, "}\n");
    fprintf(fp, ".heading-box {\n");
    fprintf(fp, "    background-color: #f2f2f2;\n");
    fprintf(fp, "    border: 2px solid #4CAF50;\n");
    fprintf(fp, "    padding: 10px;\n");
    fprintf(fp, "    text-align: center;\n");
    fprintf(fp, "}\n");
    fprintf(fp, "table {\n");
    fprintf(fp, "    width: %s;\n", "100%");
    fprintf(fp, "    border-collapse: collapse;\n");
    fprintf(fp, "}\n");
    fprintf(fp, "th, td {\n");
    fprintf(fp, "    padding: 8px;\n");
    fprintf(fp, "    text-align: left;\n");
    fprintf(fp, "}\n");
    fprintf(fp, "th {\n");
    fprintf(fp, "    background-color: #4CAF50;\n");
    fprintf(fp, "    color: white;\n");
    fprintf(fp, "}\n");
    fprintf(fp, "tr:nth-child(even) {\n");
    fprintf(fp, "    background-color: #f2f2f2;\n");
    fprintf(fp, "}\n");
    fprintf(fp, "</style>\n");
    fprintf(fp, "</head>\n");
    fprintf(fp, "<body>\n");
    fprintf(fp, "<div class='container'>\n");
    fprintf(fp, "<img src='logo.png' alt='Logo' class='logo'>\n"); // Change 'logo.png' to your logo file
    fprintf(fp, "<div class='heading-box'>\n");
    fprintf(fp, "<h1>Leaderboard</h1>\n");
    fprintf(fp, "</div>\n");

    // Generate table for each mode
    for (int mode = 1; mode <= 3; mode++) {
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

        fprintf(fp, "<div class='heading-box'>\n");
        fprintf(fp, "<h2>Mode %s</h2>\n", modeName);
        fprintf(fp, "</div>\n");
        fprintf(fp, "<table>\n");
        fprintf(fp, "<tr><th>Rank</th><th>Name</th><th>Score</th></tr>\n");

        int count = 0;
        for (int i = 0; i < numEntries && count < 10; i++) {
            if (leaderboard[i].mode == mode) {
                fprintf(fp, "<tr><td>%d</td><td>%s</td><td>%d</td></tr>\n",
                        count + 1, leaderboard[i].name, leaderboard[i].score);
                count++;
            }
        }

        // Add dummy rows if count is less than 10
        while (count < 10) {
            fprintf(fp, "<tr><td>%d</td><td>%s</td><td>%d</td></tr>\n",
                    count + 1, "Dummy", 0);
            count++;
        }

        fprintf(fp, "</table>\n");
    }

    fprintf(fp, "</div>\n");
    fprintf(fp, "</body>\n");
    fprintf(fp, "</html>\n");

    fclose(fp);
}

void updateLeaderboard(int score) {
    addToLeaderboard("Player", score, 1); // Assuming mode 1 for this example
    bubbleSortLeaderboard();
    generateLeaderboardHTML();
}

int main() {
    updateLeaderboard(0); // Example call to updateLeaderboard function with a score of 0
    printf("Leaderboard HTML file generated successfully.\n");
    return 0;
}
