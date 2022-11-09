#include "../include/Strategies.h"
#include <stdio.h>

int strategy_random(Game *game) {
  int possibilities_length = 0;
  int possibilities[COL_NUM];

  for (int x = 0; x < COL_NUM; x++) {
    if (game->grid[ROW_NUM - 1][x] == EMPTY) {
      possibilities[possibilities_length] = x;
      possibilities_length++;
    }
  }

  int index = rand() % possibilities_length;
  return possibilities[index];
}

int strategy_user_input(Game *game) {
  int input;
  while (true) {
    input = take_valid_input();
    if ((input <= 0) || (input > COL_NUM)) {
      printf("Column %d does not exist, please choose another column: ", input);
      continue;
    }
    if (game->grid[ROW_NUM - 1][input - 1] != EMPTY) {
      printf("Column %d is full, please choose another column: ", input);
      continue;
    }
    break;
  }
  return input - 1;
}

int strategy_always_first(Game *game) {
  int possibilities_length = 0;
  int possibilities[COL_NUM];

  for (int x = 0; x < COL_NUM; x++) {
    if (game->grid[ROW_NUM - 1][x] == EMPTY) {
      possibilities[possibilities_length] = x;
      possibilities_length++;
    }
  }

  return possibilities[0];
}

int strategy_minimax(Game *game) {
  int possibilities_length = 0;
  int possibilities[COL_NUM];

  for (int x = 0; x < COL_NUM; x++) {
    if (game->grid[ROW_NUM - 1][x] == EMPTY) {
      possibilities[possibilities_length] = x;
      possibilities_length++;
    }
  }

  return possibilities[possibilities_length / 2];
}