#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROW_NUM 6
#define COL_NUM 7
#define MAX_NAME_LENGTH 50
#define PLAYERS_NUM 2
#define CONNECTED_TOKENS_NUM 4
#define BUFFER_SIZE 1000

typedef enum Token { EMPTY = 0, RED = 1, YELLOW = 2 } Token;

typedef enum GameState {
  ONGOING = 0,
  RED_WINS = 1,
  YELLOW_WINS = 2,
  TIE = 3
} GameState;

typedef struct Player {
  char name[MAX_NAME_LENGTH];
  Token token;
  double total_time;
} Player;

typedef struct Game {
  Token grid[ROW_NUM][COL_NUM];
  Player players[PLAYERS_NUM];
  int current_player_index;
  GameState game_state;
} Game;

//parses a string into a positive integer if the sting is of the right format
/**
* tested formats (e.g. for the int 2):
* 
* valid: "   2   ", "000..02", "2", "\t2", "\n2"
* invalid: "2 2", "2.2", "abc", "-2", "  2  2  "
*/
bool validate_input(char *string, int *integer) {
  int i = 0;
  int length = strlen(string);
  char buffer[BUFFER_SIZE];
  int buffer_index = 0;

  while(isspace(string[i])) {
    i++;
  }

  if(length == i) {
   return false;
  }

  while(i<length && !isspace(string[i])) {
    if(!isdigit(string[i])) {
      return false;
    }
    buffer[buffer_index]=string[i];
    buffer_index++;
    i++;
  }

  buffer[buffer_index] = '\0';

  while(isspace(string[i])) {
    i++;
  }

  if(string[i]!='\0') {
    return false;
  }

  *integer = atoi(buffer);

  return true;
}

//removes endl char at the end of a string
void remove_delimiter(char *string){
  int i=0;
  while(string[i]!='\0')
    i++;
  
  if(i>1 && string[i-1]=='\n'){
    string[i-1]='\0';
  }
}

void take_valid_input(int *col){
  bool input_is_valid = true;

  do {
    char buffer[BUFFER_SIZE];
    fgets(buffer, BUFFER_SIZE, stdin);

    input_is_valid = validate_input(buffer, col);
    input_is_valid = input_is_valid && *col>0 && *col<8;

    if(!input_is_valid) {
      printf("Invalid input. Please enter an integer between 1 and 7: ");
    }    
  } while(!input_is_valid);
}

// Takes as an input the coordinates of the last dropped token
// Assumes that the game was ongoing before the last drop of a token
GameState game_check_state(Game *game, int x) {
  int y = 0;
  while (y < ROW_NUM - 1 && game->grid[y][x] != EMPTY) {
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
  for (int temp = -CONNECTED_TOKENS_NUM + 1; temp <= CONNECTED_TOKENS_NUM - 1;
       temp++) {
    if (game->grid[y + temp][x + temp] == game->grid[y][x]) {
      counter_asc++;
    } else {
      counter_asc = 0;
    }
    if (game->grid[y + temp][x - temp] == game->grid[y][x]) {
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
  for (int temp_x; temp_x < COL_NUM; temp_x++) {
    if (game->grid[ROW_NUM - 1][temp_x] == EMPTY) {
      return ONGOING;
    }
  }
  return TIE;
}

// will add the token, returns true if it works
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
    fgets(game->players[player_num - 1].name, MAX_NAME_LENGTH, stdin);
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

int main() {
  Game *game = calloc(1, sizeof(Game));
  game_init(game);
  game_run(game);
  free(game);
  return 0;
}
