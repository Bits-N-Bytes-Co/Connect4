#pragma once

#include "Types.h"

int strategy_random(Game *game);

/**
  Prompts the user to enter a choice, while the input is invalid (wrong format
  or the column is full), prompts to enter again.
  @input:
    Game* `game` representing the game
  @returns:
    An `int` representing the valid choice done by the user
*/
int strategy_user_input(Game *game);

int strategy_always_first(Game *game);

int strategy_minimax(Game *game);