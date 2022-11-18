#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../include/Game.h"
#include "../include/InputManager.h"
#include "../include/OutputManager.h"
#include "../include/Strategies.h"
#include "../include/Types.h"
#include "../include/Utils.h"

GameState game_check_state(Game *game, int x) {
  // rows are y and columns are x.
  int y = 0;
  while (y < ROW_NUM && game->grid[y][x] != EMPTY) {
    y++;
  }
  y--;

  Token lastDroppedToken = game->grid[y][x];

  // Check vertical
  int vertical_counter = 0;
  for (int temp_y = y; temp_y > y - CONNECTED_TOKENS_NUM; temp_y--) {
    if (game->grid[temp_y][x] == lastDroppedToken) {
      vertical_counter++;
    } else {
      break;
    }
  }
  if (vertical_counter == CONNECTED_TOKENS_NUM) {
    return (lastDroppedToken == RED) ? RED_WINS : YELLOW_WINS;
  }

  // Check horizontal
  int horizontal_counter = 0;
  for (int temp_x = 0; temp_x < COL_NUM; temp_x++) {
    if (game->grid[y][temp_x] == lastDroppedToken) {
      horizontal_counter++;
    } else {
      horizontal_counter = 0;
    }
    if (horizontal_counter == CONNECTED_TOKENS_NUM) {
      return (lastDroppedToken == RED) ? RED_WINS : YELLOW_WINS;
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
    diagonallyAdjacentToken = game->grid[y + temp][x + temp];
    notOutOfBounds = (y + temp >= 0) && (y + temp < ROW_NUM) &&
                     (x + temp >= 0) && (x + temp < COL_NUM);
    if ((diagonallyAdjacentToken == lastDroppedToken) && notOutOfBounds) {
      counter_asc++;
    } else {
      counter_asc = 0;
    }
    // Descending diagonal
    diagonallyAdjacentToken = game->grid[y + temp][x - temp];
    notOutOfBounds = (y + temp >= 0) && (y + temp < ROW_NUM) &&
                     (x - temp >= 0) && (x - temp < COL_NUM);
    if ((diagonallyAdjacentToken == lastDroppedToken) && notOutOfBounds) {
      counter_des++;
    } else {
      counter_des = 0;
    }

    if (counter_asc == CONNECTED_TOKENS_NUM ||
        counter_des == CONNECTED_TOKENS_NUM) {
      return (lastDroppedToken == RED) ? RED_WINS : YELLOW_WINS;
    }
  }

  // Check tie
  for (int temp_x = 0; temp_x < COL_NUM; temp_x++) {
    if (game->grid[ROW_NUM - 1][temp_x] == EMPTY) {
      return ONGOING;
    }
  }

  if (game->players[0].total_time > game->players[1].total_time) {
    return game->players[1].token == RED ? RED_WON_BY_TIME : YELLOW_WON_BY_TIME;
  } else if (game->players[0].total_time < game->players[1].total_time) {
    return game->players[0].token == RED ? RED_WON_BY_TIME : YELLOW_WON_BY_TIME;
  } else {
    return TIE;
  }
}

bool game_put_token(Game *game, int x) {
  if (x < 0 || x > COL_NUM - 1)
    return false;
  for (int y = 0; y < ROW_NUM; y++) {
    if (game->grid[y][x] == EMPTY) {
      game->grid[y][x] = game->players[game->current_player_index].token;
      return true;
    }
  }
  return false;
}

void game_init(Game *game) {
  print_start_screen();

  // Selecting game mode
  game_mode_screen();
  int input_game_mode = take_valid_input() - 1;
  while ((input_game_mode != SIMULATION) &&
         (input_game_mode != SINGLE_PLAYER) &&
         (input_game_mode != MULTI_PLAYER)) {
    printf("Please enter an integer from 1 to 3: ");
    input_game_mode = take_valid_input();
  }
  game->game_mode = input_game_mode;
  clear_screen();

  // Initializing the grid
  for (int i = 0; i < ROW_NUM; i++) {
    for (int j = 0; j < COL_NUM; j++) {
      game->grid[i][j] = EMPTY;
    }
  }

  // Initializing the players
  bool taken_indexes[PLAYERS_NUM];
  for (int i = 0; i < PLAYERS_NUM; i++) {
    taken_indexes[i] = false;
  }

  switch (game->game_mode) {
  case (SIMULATION):
    difficulty_screen();
    break;
  case (SINGLE_PLAYER):
    difficulty_screen();
    printf("Please enter your name: \n");
    break;
  case (MULTI_PLAYER):
    printf("Please enter your names: \n");
    break;
  }

  for (int player_num = 0; player_num < PLAYERS_NUM; player_num++) {
    bool is_user = ((player_num == 0) && (game->game_mode == SINGLE_PLAYER)) ||
                   (game->game_mode == MULTI_PLAYER);

    // Randomize index
    int index = rand() % PLAYERS_NUM;
    while (taken_indexes[index] == true) {
      index = (index + 1) % PLAYERS_NUM;
    }
    taken_indexes[index] = true;

    // Set player name
    if (is_user) {
      char input_name[MAX_INPUT_LENGTH];
      while (true) {
        printf("Name: ");
        fgets(input_name, MAX_INPUT_LENGTH, stdin);

        // If the input is "\0"
        if (strlen(input_name) == 1) {
          printf("Invalid input. Names cannot be empty. Please try "
                 "again.\n");
          continue;
        }
        remove_delimiter(input_name);

        // If the input contains a space
        int i = 0;
        while (input_name[i] != '\0') {
          if (input_name[i] == ' ' || input_name[i] == '\t') {
            printf(
                "Invalid input. Names cannot contain white spaces. Please try "
                "again.\n");
            break;
          }
          i++;
        }
        if (input_name[i] == ' ' || input_name[i] == '\t') {
          continue;
        }
        break;
      }

      // Copying the content of input_name in players[index].name
      int j = 0;
      while (input_name[j] != '\0') {
        game->players[index].name[j] = input_name[j];
        j++;
      }
      game->players[index].name[j] = '\0';
    } else {
      char bot_name[MAX_INPUT_LENGTH] = "Bot";
      int j = 0;
      while (bot_name[j] != '\0') {
        game->players[index].name[j] = bot_name[j];
        j++;
      }
      if (game->game_mode == SIMULATION) {
        game->players[index].name[j] = index + '1';
        j++;
      }
      game->players[index].name[j] = '\0';
    }

    // Set player strategy
    if (is_user) {
      game->players[index].strategy = strategy_user_input;
    } else {
      printf("Enter %s's strategy (1-3): ", game->players[index].name);
      int input_strategy = take_valid_input();
      while ((input_strategy != 1) && (input_strategy != 2) &&
             (input_strategy != 3)) {
        printf("Please enter an integer from 1 to 3: ");
        input_strategy = take_valid_input();
      }
      game->players[index].strategy = strategy_minimax;
      if (input_strategy == 1)
        depth_limit = EASY_DEPTH_LIMIT;
      if (input_strategy == 2)
        depth_limit = MEDIUM_DEPTH_LIMIT;
      if (input_strategy == 3)
        depth_limit = HARD_DEPTH_LIMIT;
    }

    game->players[index].token = (Token)(index + 1);
    game->players[index].total_time = 0;
  }
  printf("\n");

  game->game_state = ONGOING;
  game->current_player_index = 0;
  game_players_screen(game);
}

void game_run_turn(Game *game) {
  int chosen_col = 0;
  print_grid(game);

  // Asks for input and drops the token
  Player current_player = game->players[game->current_player_index];

  double start = get_time();
  chosen_col = current_player.strategy(game);
  if (!game_put_token(game, chosen_col)) {
    printf("ERROR: Column %d is invalid, the strategy function has a bug!\n",
           chosen_col + 1);
    exit(1);
  };
  double end = get_time();
  game->players[game->current_player_index].total_time += (end - start);

  game->current_player_index = (game->current_player_index + 1) % PLAYERS_NUM;
  game->game_state = game_check_state(game, chosen_col);

  while (get_time() - start < TIME_DELAY_PER_TURN)
    ;
}

void game_run(Game *game) {
  while (game->game_state == ONGOING) {
    game_run_turn(game);
  }

  print_grid(game);
  if (game->game_state == TIE)
    printf("         \033[0;32mTIE\033[0m");
  else
    printf((game->players[game->current_player_index].token == YELLOW)
               ? "         \033[0;31mRED\033[0m Connected 4"
               : "       \033[0;33mYELLOW\033[0m Connected 4");
  delay(5.5);
  clear_screen();
  print_end_screen(game);
}
