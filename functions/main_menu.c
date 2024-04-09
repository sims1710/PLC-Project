#include "all_functions.h"

/* Enumerations for menu choices and difficulty levels */
typedef enum
{
    NEW_GAME = 1,
    SAVED_GAME = 2,
    MULTIPLAYER = 3,
    LEADERBOARD = 4,
    ATTACK = 5,
    ENDLESS = 6,
    GAMERULE = 7,
    MAIN_MENU = 8,
    END = 0
} Choice;

typedef enum
{
    EASY = 1,
    MEDIUM = 2,
    HARD = 3
} Difficulty;

/* Function to validate user input within a specified range */
int validateChoice(int start, int end)
{
    int choice;
    char input[100];

    do
    {
        printf("    Option: ");
        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            printf("Error reading input.\n");
            return 0;
        }

        // Validate data type
        if (sscanf(input, "%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        // Validate range
        if (choice < start || choice > end)
        {
            printf("Invalid choice. Please select an option between %d and %d.\n", start, end);
        }
    } while (choice < start || choice > end);

    return choice;
}

/* Function to get player's name */
void enter_player_name(char *name)
{
    printf("\n");
    printf("   *************************************************************************************************************\n");
    printf("\n");
    printf("                                           ┌──────────────────────────┐\n");
    printf("                                           │     WELCOME PLAYER 1!    │\n");
    printf("                                           └──────────────────────────┘\n");
    printf("\n");

    printf("    Please enter your name: \n");
    printf("    Name: ");
    scanf("%s", name);
}

/* Main menu function */
void main_menu(int *current_state, game_level *game_levels)
{
    int choice, choice2;
    char name[100];

    printf(
        " \n"
        "    █     █░▓█████  ██▓     ▄████▄   ▒█████   ███▄ ▄███▓▓█████    ▄▄▄█████▓ ▒█████     ▄▄▄█████▓ ██░ ██ ▓█████ \n"
        "    ▓█░ █ ░█░▓█   ▀ ▓██▒    ▒██▀ ▀█  ▒██▒  ██▒▓██▒▀█▀ ██▒▓█   ▀    ▓  ██▒ ▓▒▒██▒  ██▒   ▓  ██▒ ▓▒▓██░ ██▒▓█   ▀ \n"
        "    ▒█░ █ ░█ ▒███   ▒██░    ▒▓█    ▄ ▒██░  ██▒▓██    ▓██░▒███      ▒ ▓██░ ▒░▒██░  ██▒   ▒ ▓██░ ▒░▒██▀▀██░▒███   \n"
        "    ░█░ █ ░█ ▒▓█  ▄ ▒██░    ▒▓▓▄ ▄██▒▒██   ██░▒██    ▒██ ▒▓█  ▄    ░ ▓██▓ ░ ▒██   ██░   ░ ▓██▓ ░ ░▓█ ░██ ▒▓█  ▄  \n"
        "    ░░██▒██▓ ░▒████▒░██████▒▒ ▓███▀ ░░ ████▓▒░▒██▒   ░██▒░▒████▒     ▒██▒ ░ ░ ████▓▒░     ▒██▒ ░ ░▓█▒░██▓░▒████▒  \n"
        "    ░ ▓░▒ ▒  ░░ ▒░ ░░ ▒░▓  ░░ ░▒ ▒  ░░ ▒░▒░▒░ ░ ▒░   ░  ░░░ ▒░ ░     ▒ ░░   ░ ▒░▒░▒░      ▒ ░░    ▒ ░░▒░▒░░ ▒░ ░  \n"
        "    ▒ ░ ░   ░ ░  ░░ ░ ▒  ░  ░  ▒     ░ ▒ ▒░ ░  ░      ░ ░ ░  ░       ░      ░ ▒ ▒░        ░     ▒ ░▒░ ░ ░ ░  ░   \n"
        "    ░   ░     ░     ░ ░   ░        ░ ░ ░ ▒  ░      ░      ░        ░      ░ ░ ░ ▒       ░       ░  ░░ ░   ░      \n"
        "        ░       ░  ░    ░  ░░ ░          ░ ░         ░      ░  ░                ░ ░               ░  ░  ░   ░  ░   \n"
        "                            ░                                                                                      \n"
        "    ██░ ██  ▄▄▄       ███▄    █   ▄████  ███▄ ▄███▓ ▄▄▄       ███▄    █      ▄████  ▄▄▄       ███▄ ▄███▓▓█████    \n"
        "    ▓██░ ██▒▒████▄     ██ ▀█   █  ██▒ ▀█▒▓██▒▀█▀ ██▒▒████▄     ██ ▀█   █     ██▒ ▀█▒▒████▄    ▓██▒▀█▀ ██▒▓█   ▀    \n"
        "    ▒██▀▀██░▒██  ▀█▄  ▓██  ▀█ ██▒▒██░▄▄▄░▓██    ▓██░▒██  ▀█▄  ▓██  ▀█ ██▒   ▒██░▄▄▄░▒██  ▀█▄  ▓██    ▓██░▒███      \n"
        "    ░▓█ ░██ ░██▄▄▄▄██ ▓██▒  ▐▌██▒░▓█  ██▓▒██    ▒██ ░██▄▄▄▄██ ▓██▒  ▐▌██▒   ░▓█  ██▓░██▄▄▄▄██ ▒██    ▒██ ▒▓█  ▄    \n"
        "    ░▓█▒░██▓ ▓█   ▓██▒▒██░   ▓██░░▒▓███▀▒▒██▒   ░██▒ ▓█   ▓██▒▒██░   ▓██░   ░▒▓███▀▒ ▓█   ▓██▒▒██▒   ░██▒░▒████▒   \n"
        "    ▒ ░░▒░▒ ▒▒   ▓▒█░░ ▒░   ▒ ▒  ░▒   ▒ ░ ▒░   ░  ░ ▒▒   ▓▒█░░ ▒░   ▒ ▒     ░▒   ▒  ▒▒   ▓▒█░░ ▒░   ░  ░░░ ▒░ ░   \n"
        "    ▒ ░▒░ ░  ▒   ▒▒ ░░ ░░   ░ ▒░  ░   ░ ░  ░      ░  ▒   ▒▒ ░░ ░░   ░ ▒░     ░   ░   ▒   ▒▒ ░░  ░      ░ ░ ░  ░   \n"
        "    ░  ░░ ░  ░   ▒      ░   ░ ░ ░ ░   ░ ░      ░     ░   ▒      ░   ░ ░    ░ ░   ░   ░   ▒   ░      ░      ░      \n"
        "    ░  ░  ░      ░  ░         ░       ░        ░         ░  ░         ░          ░       ░  ░       ░      ░  ░   \n"
        "                                                                                                                     \n");
    printf("                   ┌────────────┐     ┌────────────┐     ┌─────────────┐     ┌─────────────┐\n");
    printf("                   │  New Game  │     │ Saved Game │     │ Multiplayer │     │ Leaderboard │\n");
    printf("                   └────────────┘     └────────────┘     └─────────────┘     └─────────────┘\n");
    printf("                             ┌────────────┐     ┌────────────┐     ┌─────────────┐          \n");
    printf("                             │Time Attack │     │   Endless  │     │  Game Rules │          \n");
    printf("                             └────────────┘     └────────────┘     └─────────────┘          \n");
    printf("\n");

    printf("\n");
    printf("    Please select an option (by inputing 1\\2\\3\\4\\5\\6\\7\\0): \n");
    printf("    1. New Game\n");
    printf("    2. Saved Game\n");
    printf("    3. Multiplayer\n");
    printf("    4. Leaderboard\n");
    printf("    5. Time Attack Mode\n");
    printf("    6. Endless Mode\n");
    printf("    7. Game Rules\n");
    printf("    Enter the number 0 if you want to exit\n");
    printf("\n");

    choice = validateChoice(0, 7); // Validate the main menu choice

    printf("\n");

    switch (choice)
    {
    case NEW_GAME:
        current_state = NEW_GAME;
        printf("   *************************************************************************************************************\n");
        printf("\n");
        printf("\n");
        printf("                       ███▄    █ ▓█████  █     █░     ▄████  ▄▄▄       ███▄ ▄███▓▓█████\n");
        printf("                       ██ ▀█   █ ▓█   ▀ ▓█░ █ ░█░    ██▒ ▀█▒▒████▄    ▓██▒▀█▀ ██▒▓█   ▀\n");
        printf("                       ▓██  ▀█ ██▒▒███   ▒█░ █ ░█    ▒██░▄▄▄░▒██  ▀█▄  ▓██    ▓██░▒███\n");
        printf("                       ▓██▒  ▐▌██▒▒▓█  ▄ ░█░ █ ░█    ░▓█  ██▓░██▄▄▄▄██ ▒██    ▒██ ▒▓█  ▄\n");
        printf("                       ▒██░   ▓██░░▒████▒░░██▒██▓    ░▒▓███▀▒ ▓█   ▓██▒▒██▒   ░██▒░▒████▒\n");
        printf("                       ░ ▒░   ▒ ▒ ░░ ▒░ ░░ ▓░▒ ▒      ░▒   ▒  ▒▒   ▓▒█░░ ▒░   ░  ░░░ ▒░ ░\n");
        printf("                       ░ ░░   ░ ▒░ ░ ░  ░  ▒ ░ ░       ░   ░   ▒   ▒▒ ░░  ░      ░ ░ ░  ░\n");
        printf("                          ░   ░ ░    ░     ░   ░     ░ ░   ░   ░   ▒   ░      ░      ░   \n");
        printf("                                ░    ░  ░    ░             ░       ░  ░       ░      ░  ░\n");
        printf("\n");

        printf("                                  ┌─────────┐     ┌──────────┐     ┌────────┐\n");
        printf("                                  │  Easy   │     │  Medium  │     │  Hard  │\n");
        printf("                                  └─────────┘     └──────────┘     └────────┘\n");

        printf("\n");
        printf("    Please select a difficulty (by inputing 1\\2\\3): \n");
        printf("    1. Easy\n");
        printf("    2. Medium\n");
        printf("    3. Hard\n");
        printf("\n");

        choice2 = validateChoice(1, 3); // Validate the difficulty choice
        switch (choice2)
        {
        case EASY:
            game_levels->difficulty = EASY;
            printf("    You have selected Easy.\n");
            printf("    Good luck!\n");
            enter_player_name(name);
            printf("\n");
            printf("    There you go, %s!\n", name);
            printf("    Launching easy mode!\n");
            printf("\n");
            printf("   *************************************************************************************************************\n");
            printf("\n");
            printf(
                "                       ▓█████ ▄▄▄        ██████▓██   ██▓    ███▄ ▄███▓ ▒█████  ▓█████▄ ▓█████\n"
                "                       ▓█   ▀▒████▄    ▒██    ▒ ▒██  ██▒   ▓██▒▀█▀ ██▒▒██▒  ██▒▒██▀ ██▌▓█   ▀\n"
                "                       ▒███  ▒██  ▀█▄  ░ ▓██▄    ▒██ ██░   ▓██    ▓██░▒██░  ██▒░██   █▌▒███\n"
                "                       ▒▓█  ▄░██▄▄▄▄██   ▒   ██▒ ░ ▐██▓░   ▒██    ▒██ ▒██   ██░░▓█▄   ▌▒▓█  ▄\n"
                "                       ░▒████▒▓█   ▓██▒▒██████▒▒ ░ ██▒▓░   ▒██▒   ░██▒░ ████▓▒░░▒████▓ ░▒████▒\n"
                "                       ░░ ▒░ ░▒▒   ▓▒█░▒ ▒▓▒ ▒ ░  ██▒▒▒    ░ ▒░   ░  ░░ ▒░▒░▒░  ▒▒▓  ▒ ░░ ▒░ ░\n"
                "                        ░ ░  ░ ▒   ▒▒ ░░ ░▒  ░ ░▓██ ░▒░    ░  ░      ░  ░ ▒ ▒░  ░ ▒  ▒  ░ ░  ░\n"
                "                          ░    ░   ▒   ░  ░  ░  ▒ ▒ ░░     ░      ░   ░ ░ ░ ▒   ░ ░  ░    ░   \n"
                "                          ░  ░     ░  ░      ░  ░ ░               ░       ░ ░     ░       ░  ░\n"
                "                                                ░ ░                             ░              \n");
            printf("\n");
            printf("    Challenge 1:");
            break;

        case MEDIUM:
            game_levels->difficulty = MEDIUM;
            printf("    You have selected Medium.\n");
            printf("    Good luck!\n");
            enter_player_name(name);
            printf("\n");
            printf("    There you go, %s!\n", name);
            printf("    Launching medium mode!\n");
            printf("\n");
            printf("   *************************************************************************************************************\n");
            printf("\n");
            printf(
                "            ███▄ ▄███▓▓█████ ▓█████▄  ██▓ █    ██  ███▄ ▄███▓    ███▄ ▄███▓ ▒█████  ▓█████▄ ▓█████ \n"
                "            ▓██▒▀█▀ ██▒▓█   ▀ ▒██▀ ██▌▓██▒ ██  ▓██▒▓██▒▀█▀ ██▒   ▓██▒▀█▀ ██▒▒██▒  ██▒▒██▀ ██▌▓█   ▀ \n"
                "            ▓██    ▓██░▒███   ░██   █▌▒██▒▓██  ▒██░▓██    ▓██░   ▓██    ▓██░▒██░  ██▒░██   █▌▒███   \n"
                "            ▒██    ▒██ ▒▓█  ▄ ░▓█▄   ▌░██░▓▓█  ░██░▒██    ▒██    ▒██    ▒██ ▒██   ██░░▓█▄   ▌▒▓█  ▄ \n"
                "            ▒██▒   ░██▒░▒████▒░▒████▓ ░██░▒▒█████▓ ▒██▒   ░██▒   ▒██▒   ░██▒░ ████▓▒░░▒████▓ ░▒████▒\n"
                "            ░ ▒░   ░  ░░░ ▒░ ░ ▒▒▓  ▒ ░▓  ░▒▓▒ ▒ ▒ ░ ▒░   ░  ░   ░ ▒░   ░  ░░ ▒░▒░▒░  ▒▒▓  ▒ ░░ ▒░ ░\n"
                "            ░  ░      ░ ░ ░  ░ ░ ▒  ▒  ▒ ░░░▒░ ░ ░ ░  ░      ░   ░  ░      ░  ░ ▒ ▒░  ░ ▒  ▒  ░ ░  ░\n"
                "            ░      ░      ░    ░ ░  ░  ▒ ░ ░░░ ░ ░ ░      ░      ░      ░   ░ ░ ░ ▒   ░ ░  ░    ░   \n"
                "                   ░      ░  ░   ░     ░     ░            ░             ░       ░ ░     ░       ░  ░\n"
                "                               ░                                                      ░             \n");
            printf("\n");
            printf("    Challenge 1:");
            break;

        case HARD:
            game_levels->difficulty = HARD;
            printf("    You have selected Hard.\n");
            printf("    Good luck!\n");
            enter_player_name(name);
            printf("\n");
            printf("    There you go, %s!\n", name);
            printf("    Launching hard mode!\n");
            printf("\n");
            printf("   *************************************************************************************************************\n");
            printf("\n");
            printf("                    ██░ ██  ▄▄▄       ██▀███  ▓█████▄     ███▄ ▄███▓ ▒█████  ▓█████▄ ▓█████\n");
            printf("                    ▓██░ ██▒▒████▄    ▓██ ▒ ██▒▒██▀ ██▌   ▓██▒▀█▀ ██▒▒██▒  ██▒▒██▀ ██▌▓█   ▀\n");
            printf("                    ▒██▀▀██░▒██  ▀█▄  ▓██ ░▄█ ▒░██   █▌   ▓██    ▓██░▒██░  ██▒░██   █▌▒███\n");
            printf("                    ░▓█ ░██ ░██▄▄▄▄██ ▒██▀▀█▄  ░▓█▄   ▌   ▒██    ▒██ ▒██   ██░░▓█▄   ▌▒▓█  ▄\n");
            printf("                    ░▓█▒░██▓ ▓█   ▓██▒░██▓ ▒██▒░▒████▓    ▒██▒   ░██▒░ ████▓▒░░▒████▓ ░▒████▒\n");
            printf("                     ▒ ░░▒░▒ ▒▒   ▓▒█░░ ▒▓ ░▒▓░ ▒▒▓  ▒    ░ ▒░   ░  ░░ ▒░▒░▒░  ▒▒▓  ▒ ░░ ▒░ ░\n");
            printf("                     ▒ ░▒░ ░  ▒   ▒▒ ░  ░▒ ░ ▒░ ░ ▒  ▒    ░  ░      ░  ░ ▒ ▒░  ░ ▒  ▒  ░ ░  ░\n");
            printf("                     ░  ░░ ░  ░   ▒     ░░   ░  ░ ░  ░    ░      ░   ░ ░ ░ ▒   ░ ░  ░    ░   \n");
            printf("                     ░  ░  ░      ░  ░   ░        ░              ░       ░ ░     ░       ░  ░\n");
            printf("                                                ░                              ░             \n");
            printf("\n");
            printf("    Challenge 1:");
            break;

        default:
            break;
        }
        break;
    case SAVED_GAME:
        current_state = SAVED_GAME;
        printf("    You have selected Saved Game.\n");
        printf("    Loading saved game...\n");
        break;

    case MULTIPLAYER:
        current_state = MULTIPLAYER;
        printf("    You have selected Multiplayer.\n");
        printf("    Loading multiplayer mode...\n");

        break;

    case LEADERBOARD:
        current_state = LEADERBOARD;
        printf("    You have selected Leaderboard.\n");
        printf("    Loading leaderboard...\n");
        // updateLeaderboard(0);
        break;

    case ATTACK:
        current_state = ATTACK;
        printf("    You have selected Time Attack Mode.\n");
        printf("    Loading Time Attack Mode...\n");
        break;

    case ENDLESS:
        current_state = ENDLESS;
        printf("    You have selected Endless Mode.\n");
        printf("    Loading Endless Mode...\n");
        break;

    case GAMERULE:
        current_state = GAMERULE;
        printf("    You have selected Game Rules.\n");
        printf("    Loading Game Rules...\n");
        break;

    case END:
        current_state = END;
        exit(0);
        break;

    default:
        break;
    }
}

// int main(){

//     while (currentState != END) {
//         main_menu();
//     }

//     return 0;
// }
