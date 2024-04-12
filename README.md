# Revamped Hangman Game in C

## Game Overview

Our revamped Hangman game aims to provide an engaging and immersive experience by introducing new features and mechanics. Players can personalize their experience by choosing different game modes, difficulty levels, and participating in special modes like multiplayer and time-attack challenges. The game incorporates efficient file handling, robust parsing, and state machines to ensure smooth gameplay and user interaction.

## Code Structure and Libraries

The codebase consists of C files (.c), header files (.h), and text files for word storage. Libraries required include standard C libraries for file handling, time measurement, and console manipulation. The primary code files include `main.c`, `game_functions.c`, `game_modes.c`, `ui.c`, `leaderboard.c`, `clear_functions.c`, and `utility.c`, each responsible for specific aspects of the game logic and user interface.

You can read the Code Documentation [here](). 

### How to Install C Library and Run the Program

#### Windows:
1. **Install MinGW**:
   - Download and install MinGW from the official website.
   - During installation, select the C compiler and necessary development tools.

2. **Compile and Run**:
   - Open Command Prompt.
   - Navigate to the directory containing your C files.
   - Compile using `gcc` command: `gcc main.c game_functions.c ... -o hangman.exe`.
   - Run the executable: `hangman.exe`.

#### Linux (Debian/Ubuntu):
1. **Install GCC**:
   - Open Terminal.
   - Run command: `sudo apt install gcc`.

2. **Compile and Run**:
   - Navigate to the directory containing your C files.
   - Compile using `gcc` command: `gcc main.c game_functions.c ... -o hangman`.
   - Run the executable: `./hangman`.

#### macOS:
1. **Install Xcode Command Line Tools**:
   - Open Terminal.
   - Run command: `xcode-select --install`.

2. **Install Homebrew (optional but recommended)**:
   - Run command: `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"`.

3. **Install GCC** (via Homebrew):
   - Run command: `brew install gcc`.

4. **Compile and Run**:
   - Navigate to the directory containing your C files.
   - Compile using `gcc` command: `gcc main.c game_functions.c ... -o hangman`.
   - Run the executable: `./hangman`.

These steps should help you set up and run the Hangman game on Windows, Linux, and macOS systems.

Here's the revised section:

## How to Run the Application

To run the game, compile the C files using a C compiler like GCC or Clang, linking any required libraries. You can use the following command:

```bash
gcc main.c -o hangman game_functions.c clear_functions.c game_modes.c game_state.c leaderboard.c ui.c -ansi -pedantic -Wall -Werror
```

Make sure the text files containing words are accessible in the same directory as the compiled executable. After compiling, run the executable file using the command:

```bash
./hangman
```

This will start the game, and you can then follow the on-screen prompts to navigate menus, select game modes, and play Hangman.

## Planned But Unimplemented Features
These are features that were meant to be part of the final project but in the end, they were unsuccessfully implemented due to time constraints and fruitless debugging efforts. They can be viewed in the `incomplete` directory.

#### Game State Saving:
- **Functionality**: Allow players to save their progress mid-game.
- **Implementation**: Dynamically alter a text file (`input.txt`) to save game states (player name, mode, level) for later resumption.

#### Endless Mode:
- **Functionality**: Most relaxed mode, unlimited guesses, player-created challenges from previous winners.
- **Implementation**: Use a text file (`words.txt`) to store player-inputted words for endless mode challenges.

#### Cheat Code:
- **Functionality**: Fun codes offering privileges (e.g., "LIVEFULL" replenishes lives).
- **Implementation**: Implement as an FSM, accessible to top 10 leaderboard players in any difficulty mode.

#### Main Menu as a FSM:
- **Functionality**: Formalize main menu structure with an FSM for better state management.
- **Implementation**: Define states and transitions in a state transition table for the main menu.

## Roadmap and Project Status

The project is currently in a functional state, offering multiple game modes, difficulty levels, and special challenges. Future roadmap goals may include:


1. **Improve the Ranking System**:
   Incorporate a timer to rank players not just based on correctness but also on speed. Faster solving times could lead to higher rankings in case of ties.

2. **Enhance Challenges**:
   Introduce more diverse challenges such as phrases or combinations of words (e.g., "The Great Wall of China") to add variety and complexity.

3. **Transition to GUI**:
   Develop a graphical user interface (GUI) version to enhance user experience, simplify navigation (e.g., main menu), and allow for easier mid-game exits.

4. **Implement Planned Features**:
   - **Endless Mode**: Introduce a relaxed mode with unlimited guesses and player-created challenges.
   - **Save Function**: Enable players to save their progress mid-game, allowing for seamless resume and enhanced gaming experience.

These proposed improvements aim to make the game more engaging, diverse, and user-friendly while incorporating planned features that were previously unimplemented.

The project is currently considered complete.

## Additional Details:

### Textfiles:

The textfiles of words were manually created on a .xlxs file which were later conveted to .txt files. The words were sourced from the following websites:

1. https://wordsrated.com/tools/wordsfinder-results/

2. https://wordunscrambler.me/

You can take a look of our excel sheet [here](https://docs.google.com/spreadsheets/d/1GQKYnOnWui16u_4IJz51kWDBPCT58oWs-QywsA4kuk4/edit?usp=sharing).

### ASCII Word Art
The ASCII Word Art used in the code was generated from this [website](https://patorjk.com/software/taag/#p=display&f=Graffiti&t=Type%20Something%20).

Content before the tabs.

### [Tab A](#tab/tab-a)
Tab A content.

### [Tab B](#tab/tab-b)
Tab B content.
***

Content after the tabs.
