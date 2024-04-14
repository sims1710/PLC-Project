CC = gcc
CFLAGS = -ansi -pedantic -Wall -Werror
SRCS = main.c game_functions.c clear_functions.c game_modes.c leaderboard.c ui.c
TARGET = hangman
$(TARGET): $(SRCS)
$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
.PHONY: clean
clean:
rm -f $(TARGET)
