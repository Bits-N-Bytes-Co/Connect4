#pragma once

#include "Types.h"

/**
  Clears the terminal screen
*/
void clear_screen();

/**
  Prints the start screen to stdout
*/
void print_start_screen();

/**
  Prints each player's information to stdout
  @input:
    Game `game`
  @assumes:
    `game` and its players has been initialized
*/
void game_players_screen(Game *game);

/**
  Prints the game grid to stdout
  @input:
    Game `game`
  @assumes:
    `game` has been initialized
*/
void print_grid(Game *game);

/**
  Prints the end screen to stdout
  @input:
    Game `game`
  @assumes:
    `game` has been initialized
*/
void print_end_screen(Game *game);

/**
  Prints the different game modes to stdout
*/
void game_mode_screen();

/**
  Prints the difficulty levels to stdout
*/
void difficulty_screen();

#ifdef _WIN32
#define PRINTREDTOKEN() printf(" \033[0;31m%c%c\033[0m ", 219, 219);
#define PRINTYELLOWTOKEN() printf(" \033[0;33m%c%c\033[0m ", 219, 219);
#else
#define PRINTREDTOKEN() printf(" \033[0;31m%s\033[0m ", "██");
#define PRINTYELLOWTOKEN() printf(" \033[0;33m%s\033[0m ", "██");
#endif
