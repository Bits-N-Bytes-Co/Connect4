#include "../include/Game.h"

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
    // printf("%s's time (%d): %.3fs\n", game->players[0].name,
    //        game->players[0].token, game->players[0].total_time);
    // printf("%s's time (%d): %.3fs\n", game->players[1].name,
    //        game->players[1].token, game->players[1].total_time);
    return game->players[1].token == RED ? RED_WON_BY_TIME : YELLOW_WON_BY_TIME;
  } else if (game->players[0].total_time < game->players[1].total_time) {
    // printf("%s's time (%d): %.3fs\n", game->players[0].name,
    //        game->players[0].token, game->players[0].total_time);
    // printf("%s's time (%d): %.3fs\n", game->players[1].name,
    //        game->players[1].token, game->players[1].total_time);
    return game->players[0].token == RED ? RED_WON_BY_TIME : YELLOW_WON_BY_TIME;
  } else {
    return TIE;
  }
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

void game_init(Game *game) {
  print_start_screen();

  // Initializing the grid
  for (int i = 0; i < ROW_NUM; i++) {
    for (int j = 0; j < COL_NUM; j++) {
      game->grid[i][j] = EMPTY;
    }
  }

  // Initializing the players
  srand((unsigned int)time(NULL));

  char **taken_names = malloc(sizeof(char *) * PLAYERS_NUM);
  int name_index = 0;
  bool name_valid;
  printf("Please enter your names \n");

  for (int player_num = 0; player_num < PLAYERS_NUM; player_num++) {
    do {
      name_valid = true;
      int i = 0;
      char input[MAX_INPUT_LENGTH];
      printf("Name: ");

      fgets(input, MAX_INPUT_LENGTH, stdin);
      // If the input is "\0"
      if (strlen(input) == 1) {
        printf("Invalid input. Names cannot be empty. Please try "
               "again.\n");
        name_valid = false;
        continue;
      }

      remove_delimiter(input);

      // If the input contains a space
      while (input[i] != '\0') {
        if (input[i] == ' ' || input[i] == '\t') {
          name_valid = false;
          printf("Invalid input. Names cannot contain white spaces. Please try "
                 "again.\n");
          break;
        }
        i++;
      }
      if (!name_valid) {
        continue;
      }

      // Allocating the name to game
      taken_names[name_index] = malloc(sizeof(char *));
      int j = 0;
      while (input[j] != '\0') {
        taken_names[name_index][j] = input[j];
        j++;
      }
      taken_names[name_index][j] = '\0';
      name_index++;
    } while (!name_valid);
  }

  bool taken_indexes[PLAYERS_NUM];
  for (int player_num = 0; player_num < PLAYERS_NUM; player_num++) {
    int index = rand() % PLAYERS_NUM;
    while (taken_indexes[index] == true) {
      index = (index + 1) % PLAYERS_NUM;
    }
    taken_indexes[index] = true;
    // Copies the content of taken_names[player_num] in players[index].name
    int i = 0;
    while (taken_names[player_num][i] != '\0') {
      game->players[index].name[i] = taken_names[player_num][i];
      i++;
    }
    game->players[index].name[i] = '\0';
    game->players[index].total_time = 0;
    game->players[index].token = (Token)(index + 1);
  }
  printf("\n");

  game->game_state = ONGOING;
  game->current_player_index = 0;

  for (int j = 0; j < PLAYERS_NUM; j++) {
    free(taken_names[j]);
  }
  free(taken_names);
  taken_names = NULL;

  game_players_screen(game);
}

void game_run_turn(Game *game) {
  int chosen_col = 0;
  print_grid(game);
  // Asks for input and drops the token
  game->players[game->current_player_index].token == RED
      ? printf("\033[0;31m%s's\033[0m turn. ",
               game->players[game->current_player_index].name)
      : printf("\033[0;33m%s's\033[0m turn. ",
               game->players[game->current_player_index].name);
  time_t start = time(NULL);
  take_valid_input(&chosen_col);
  chosen_col--;
  while (!game_put_token(game, chosen_col)) {
    printf("Column %d is full, please choose another column: ", chosen_col + 1);
    take_valid_input(&chosen_col);
    chosen_col--;
  };

  time_t end = time(NULL);
  double diff = end - start;
  game->players[game->current_player_index].total_time += diff;

  game->current_player_index = (game->current_player_index + 1) % PLAYERS_NUM;
  game->game_state = game_check_state(game, chosen_col);
}

void game_run(Game *game) {
  while (game->game_state == ONGOING) {
    game_run_turn(game);
  }

  print_grid(game);
  print_end_screen(game);
}
