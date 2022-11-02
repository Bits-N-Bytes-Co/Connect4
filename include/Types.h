#pragma once

#define ROW_NUM 6
#define COL_NUM 7
#define PLAYERS_NUM 2
#define CONNECTED_TOKENS_NUM 4
#define MAX_INPUT_LENGTH 50

typedef enum token { EMPTY = 0, RED = 1, YELLOW = 2 } Token;

typedef enum gameState {
  ONGOING = 0,
  RED_WINS = 1,
  YELLOW_WINS = 2,
  TIE = 3,
  RED_WON_BY_TIME = 4,
  YELLOW_WON_BY_TIME = 5
} GameState;

typedef struct player {
  char name[MAX_INPUT_LENGTH];
  Token token;
  double total_time;
} Player;

typedef struct game {
  Token grid[ROW_NUM][COL_NUM];
  Player players[PLAYERS_NUM];
  int current_player_index;
  GameState game_state;
} Game;