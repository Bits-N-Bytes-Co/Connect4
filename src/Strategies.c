#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/InputManager.h"
#include "../include/Strategies.h"
#include "../include/Types.h"
#include "../include/Utils.h"

Token self;

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
  Player current_player = game->players[game->current_player_index];
  printf("\033[0;%dm%s's\033[0m turn: ",
         (current_player.token == RED) ? 31 : 33, current_player.name);

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

bool put_token(Token ***grid, Token token, int col) {
  if (col < 0 || col >= COL_NUM)
    return false;
  for (int y = 0; y < ROW_NUM; y++) {
    if ((*grid)[y][col] == EMPTY) {
      (*grid)[y][col] = token;
      return true;
    }
  }
  return false;
}

bool remove_token(Token ***grid, Token token, int col) {
  if (col < 0 || col >= COL_NUM)
    return false;
  for (int y = ROW_NUM - 1; y >= 0; y--) {
    if ((*grid)[y][col] != EMPTY) {
      (*grid)[y][col] = EMPTY;
      return true;
    }
  }
  return false;
}

void grid_show(Token **grid) {
  printf("| -- + -- + -- + -- + -- + -- + -- |\n");
  for (int y = ROW_NUM - 1; y >= 0; y--) {
    printf("|");
    for (int x = 0; x < COL_NUM; x++) {
      if (grid[y][x] == RED) {
        printf(" RR |");
      } else if (grid[y][x] == YELLOW) {
        printf(" YY |");
      } else {
        printf("    |");
      }
    }
    printf("\n");
    printf("| -- + -- + -- + -- + -- + -- + -- |\n");
  }
}

bool grid_check_tie(Token ***grid) {
  for (int temp_x = 0; temp_x < COL_NUM; temp_x++) {
    if ((*grid)[ROW_NUM - 1][temp_x] == EMPTY) {
      return false;
    }
  }
  return true;
}

bool move_is_valid(Token ***grid, int col) {
  return (*grid)[ROW_NUM - 1][col] == EMPTY;
}

bool move_is_win(Token ***grid, Token token, int x) {
  if (!put_token(grid, token, x)) {
    printf("ERROR: in put_token\n");
    exit(1);
  }

  int y = 0;
  while (y < ROW_NUM && (*grid)[y][x] != EMPTY) {
    y++;
  }
  y--;

  Token lastDroppedToken = (*grid)[y][x];
  // Check vertical
  int vertical_counter = 0;
  for (int temp_y = y; (temp_y > y - CONNECTED_TOKENS_NUM) && (temp_y >= 0);
       temp_y--) {
    if ((*grid)[temp_y][x] == lastDroppedToken) {
      vertical_counter++;
    } else {
      break;
    }
  }
  if (vertical_counter == CONNECTED_TOKENS_NUM) {
    if (!remove_token(grid, token, x)) {
      printf("ERROR: in remove_token\n");
      exit(1);
    }
    return true;
  }

  // Check horizontal
  int horizontal_counter = 0;
  for (int temp_x = 0; temp_x < COL_NUM; temp_x++) {
    if ((*grid)[y][temp_x] == lastDroppedToken) {
      horizontal_counter++;
    } else {
      horizontal_counter = 0;
    }
    if (horizontal_counter == CONNECTED_TOKENS_NUM) {
      if (!remove_token(grid, token, x)) {
        printf("ERROR: in remove_token\n");
        exit(1);
      }
      return true;
    }
  }

  // Check diagonal
  int counter_asc = 0;
  int counter_des = 0;
  Token diagonallyAdjacentToken;
  bool notOutOfBounds; // to make sure that the index does not wrap around
  for (int temp = -CONNECTED_TOKENS_NUM + 1; temp <= CONNECTED_TOKENS_NUM - 1;
       temp++) {
    // Ascending diagonal
    notOutOfBounds = (y + temp >= 0) && (y + temp < ROW_NUM) &&
                     (x + temp >= 0) && (x + temp < COL_NUM);
    if (notOutOfBounds && ((*grid)[y + temp][x + temp] == lastDroppedToken)) {
      counter_asc++;
    } else {
      counter_asc = 0;
    }

    // Descending diagonal
    notOutOfBounds = (y + temp >= 0) && (y + temp < ROW_NUM) &&
                     (x - temp >= 0) && (x - temp < COL_NUM);
    if (notOutOfBounds && ((*grid)[y + temp][x - temp] == lastDroppedToken)) {
      counter_des++;
    } else {
      counter_des = 0;
    }

    if (counter_asc == CONNECTED_TOKENS_NUM ||
        counter_des == CONNECTED_TOKENS_NUM) {
      if (!remove_token(grid, token, x)) {
        printf("ERROR: in remove_token\n");
        exit(1);
      }
      return true;
    }
  }

  if (!remove_token(grid, token, x)) {
    printf("ERROR: in remove_token\n");
    exit(1);
  }
  return false;
}

int strategy_minimax_helper(Token **grid, Token self, int depth, int alpha,
                            int beta) {

  Token opponent = (self == RED) ? YELLOW : RED;
  if (grid_check_tie(&grid))
    return 0;

  // if self can win
  for (int col = 0; col < COL_NUM; col++) {
    if (move_is_valid(&grid, col) && move_is_win(&grid, self, col)) {
      if (self == RED) {
        if (depth != 0)
          return (ROW_NUM * COL_NUM + 1 - depth) / 2;
        else
          return col;
      } else {
        if (depth != 0)
          return -(ROW_NUM * COL_NUM + 1 - depth) / 2;
        else
          return col;
      }
    }
  }

  if (depth >= depth_limit) {
    return 0;
  }

  int best_score = ((self == RED) ? -1 : 1) * (ROW_NUM * COL_NUM + 1);
  int best_col = -1;
  int current_score;
  for (int column = 0; column < COL_NUM; column++) {
    if (move_is_valid(&grid, column)) {
      if (!put_token(&grid, self, column)) {
        printf("ERROR: in put_token\n");
        exit(1);
      }
      current_score =
          strategy_minimax_helper(grid, opponent, depth + 1, alpha, beta);
      if (!remove_token(&grid, self, column)) {
        printf("ERROR: in remove_token\n");
        exit(1);
      }

      if ((self == RED && current_score > best_score) ||
          (self == YELLOW && current_score < best_score)) {
        best_score = current_score;
        best_col = column;
      }

      if (self == RED) {
        if (beta <= current_score)
          break;
        if (alpha < current_score)
          alpha = current_score;
      } else {
        if (alpha >= current_score)
          break;
        if (beta > current_score)
          beta = current_score;
      }
    }
  }

  if (depth == 0) {
    if (best_col == -1)
      printf("ERROR: There is a bug in minimax: no node has been visited\n");
    return best_col;
  } else
    return best_score;
}

int strategy_minimax(Game *game) {
  int total_tokens = 0;
  for (int y = 0; y < ROW_NUM; y++) {
    for (int x = 0; x < COL_NUM; x++) {
      if (game->grid[y][x] != EMPTY)
        total_tokens++;
    }
  }

  if (total_tokens % 2 == 0) {
    self = RED;
  } else if (total_tokens % 2 == 1) {
    self = YELLOW;
  }

  if (total_tokens == 0) {
    return COL_NUM / 2;
  } else if (total_tokens == 1) {
    if (game->grid[0][1] != EMPTY) {
      return 2;
    } else if (game->grid[0][COL_NUM - 2] != EMPTY) {
      return COL_NUM - 3;
    } else {
      return COL_NUM / 2;
    }
  } else if (total_tokens == 2) {
    if (game->grid[0][COL_NUM - 2] != EMPTY || game->grid[0][COL_NUM - 3] != EMPTY) {
      return 2;
    } else if (game->grid[0][2] != EMPTY || game->grid[0][1] != EMPTY) {
      return COL_NUM - 2;
    } else {
      return COL_NUM / 2;
    }
  }

  Token **grid_copy = calloc(sizeof(Token *), ROW_NUM * 100);
  for (int column = 0; column < COL_NUM; column++) {
    grid_copy[column] = calloc(sizeof(Token), COL_NUM * 100);
  }

  for (int y = 0; y < ROW_NUM; y++) {
    for (int x = 0; x < COL_NUM; x++) {
      grid_copy[y][x] = game->grid[y][x];
    }
  }

  int best_col = strategy_minimax_helper(grid_copy, self, 0, INT_MIN, INT_MAX);

  for (int column = 0; column < COL_NUM; column++) {
    free(grid_copy[column]);
  }
  free(grid_copy);
  return best_col;
}