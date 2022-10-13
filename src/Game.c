#include "../include/Game.h"
#include <stdio.h>

/**
  Takes as an input the coordinates of the last dropped token
  Assumes that the game was ongoing before the last drop of a token
*/
GameState game_check_state(Game *game, int x) {
  int y = 0;
  while (y < ROW_NUM && game->grid[y][x] != EMPTY) {
    y++;
  }
  y--;

  // Check vertical
  int vertical_counter = 0;
  for (int temp_y = y; temp_y > y - CONNECTED_TOKENS_NUM; temp_y--) {
    if (game->grid[temp_y][x] == game->grid[y][x]) {
      vertical_counter++;
    } else {
      break;
    }
  }
  if (vertical_counter == CONNECTED_TOKENS_NUM) {
    return (game->grid[y][x] == RED) ? RED_WINS : YELLOW_WINS;
  }

  // Check horizontal
  int horizontal_counter = 0;
  for (int temp_x = 0; temp_x < COL_NUM; temp_x++) {
    if (game->grid[y][temp_x] == game->grid[y][x]) {
      horizontal_counter++;
    } else {
      horizontal_counter = 0;
    }
    if (horizontal_counter == CONNECTED_TOKENS_NUM) {
      return (game->grid[y][x] == RED) ? RED_WINS : YELLOW_WINS;
    }
  }

  // Check diagonal
  int counter_asc = 0;
  int counter_des = 0;
   // Ascending diagonal
  for (int temp = -CONNECTED_TOKENS_NUM + 1; temp <= CONNECTED_TOKENS_NUM - 1;
       temp++) {
    if (game->grid[y + temp][x + temp] == game->grid[y][x] && (y + temp >= 0) &&
        (y + temp < ROW_NUM) && (x + temp >= 0) && (x + temp < COL_NUM)) {      //to make sure that the index does not wrap around 
      counter_asc++;
    } else {
      
      counter_asc = 0;
    }
    // Descending diagonal
    if (game->grid[y + temp][x - temp] == game->grid[y][x] && (y + temp >= 0) &&
        (y + temp < COL_NUM) && (x - temp >= 0) && (x - temp < ROW_NUM)) {
      
      counter_des++;
    } else {
      counter_des = 0;
    } 
    
    if (counter_asc == CONNECTED_TOKENS_NUM ||
        counter_des == CONNECTED_TOKENS_NUM) {
      return (game->grid[y][x] == RED) ? RED_WINS : YELLOW_WINS;
    }
  }

  // Check tie
  for (int temp_x = 0; temp_x < COL_NUM; temp_x++) {
    if (game->grid[ROW_NUM - 1][temp_x] == EMPTY) {
      return ONGOING;
    }
  }
  return TIE;
}

bool game_put_token(Game *game, int x) {
  for (int y = 0; y < ROW_NUM; y++) {
    if (game->grid[y][x] == EMPTY) {
      game->grid[y][x] = game->players[game->current_player_index].token;
      return true;
    }
  }
  return false;
}

void game_show(Game *game) {
  printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");
  printf("| - + - + - + - + - + - + - |\n");
  for (int y = ROW_NUM - 1; y >= 0; y--) {
    printf("|");
    for (int x = 0; x < COL_NUM; x++) {
      printf(" %d |", game->grid[y][x]);
    }
    printf("\n");
    printf("| - + - + - + - + - + - + - |\n");
  }
}

void game_init(Game *game) {
  printf("--------/Welcome to Connect 4/--------\n\n");

  // Initializing the grid
  for (int i = 0; i < ROW_NUM; i++) {
    for (int j = 0; j < COL_NUM; j++) {
      game->grid[i][j] = EMPTY;
    }
  }

  // Initializing the players
  for (int player_num = 1; player_num <= PLAYERS_NUM; player_num++) {
    game->players[player_num - 1].total_time = 0;
    printf("Player %d, please enter your name: ", player_num);
    fgets(game->players[player_num - 1].name, MAX_INPUT_LENGTH, stdin);
    remove_delimiter(game->players[player_num - 1].name);
    game->players[player_num - 1].token = (Token)player_num;
  }
  printf("\n");

  game->game_state = ONGOING;
  game->current_player_index = 0;
}

void game_run_turn(Game *game) {
  int chosen_col = 0;
  game_show(game);
  // Asks for input and drops the token
  printf("%s's turn.", game->players[game->current_player_index].name);
  take_valid_input(&chosen_col);
  chosen_col--;
  while (!game_put_token(game, chosen_col)) {
    printf("Column %d is full, please choose another column: ", chosen_col + 1);
    take_valid_input(&chosen_col);
    chosen_col--;
  };
  game->current_player_index = (game->current_player_index + 1) % PLAYERS_NUM;
  game->game_state = game_check_state(game, chosen_col);
}

void game_run(Game *game) {
  while (game->game_state == ONGOING) {
    game_run_turn(game);
  }

  game_show(game);
  switch (game->game_state) {
  case ONGOING:
    printf("ERROR: the game is not over yet\n");
    break;
  case RED_WINS:
    printf("RED WON!\n");
    break;
  case YELLOW_WINS:
    printf("YELLOW WON!\n");
    break;
  case TIE:
    printf("TIE!\n");
    break;
  }
}
