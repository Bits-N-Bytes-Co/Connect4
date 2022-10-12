#pragma once

#include "InputManager.h"

#define ROW_NUM 6
#define COL_NUM 7
#define PLAYERS_NUM 2
#define CONNECTED_TOKENS_NUM 4

typedef enum token { EMPTY = 0, RED = 1, YELLOW = 2 } Token;

typedef enum gameState {
  ONGOING = 0,
  RED_WINS = 1,
  YELLOW_WINS = 2,
  TIE = 3
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

/**
  Takes as an input the coordinates of the last dropped token
  Assumes that the game was ongoing before the last drop of a token
*/
GameState game_check_state(Game *game, int x);

/**
  Adds the token to the column, returns true if it works
*/
bool game_put_token(Game *game, int x);

void game_show(Game *game);

void game_init(Game *game);

void game_run_turn(Game *game);

void game_run(Game *game);