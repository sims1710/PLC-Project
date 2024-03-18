# include "all_functions.h"

void score_tracker(int *score, int *lives) {
    static int challenges_completed = 0;

    if (*lives == 0) {
        printf("You have run out of lives! Your score is %d\n", *score);
        leaderboard(*score);
        challenges_completed = 0;  // Reset challenges completed
    } else {
        printf("Your score is %d\n", *score);
        challenges_completed++;
        if (challenges_completed >= 20) {
            printf("Congratulations! You have completed 20 challenges.\n");
            leaderboard(*score);  // Display leaderboard after completing 20 challenges
            challenges_completed = 0;  // Reset challenges completed
        }
    }
}
