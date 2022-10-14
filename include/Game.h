#pragma once

#include "InputManager.h"
#include "Graphics.h"
#include <time.h>

#define ROW_NUM 6
#define COL_NUM 7
#define PLAYERS_NUM 2
#define CONNECTED_TOKENS_NUM 4

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

/**
  Checks whether Game `game` is `ONGOING`, or if a player has won
  @input:
    the coordinates of the last dropped token
  @assumes:
    that the game was ongoing before the last drop of a token
  @tested:
    Vertical, horizontal, diagonal (ascending and descending)
    More than 4 tokens get connected on one line
    More than one line of 4 tokens gets connected
    The connected tokens are on the edges of the grid (left, bottom, right, top)
  @returns:
    GameState indicating which color won or if there's a tie
*/
GameState game_check_state(Game *game, int x);

/**
Inserts token into column, returns true if it works and false otherwise
@input:
  Game `game`
  int `x` representing column that will receive token
@assumes:
  Game `game` is initialized
@returns:
  bool: `true` if column `x` was not filled, `false` otherwise
*/
bool game_put_token(Game *game, int x);

/**
Prints out the game grid to stdout
@input:
  Game `game`
@assumes:
  `game` has been initialized
*/
void game_show(Game *game);

/**
Prints the tokens each player has after flipping a coin
@input:
  Game `game`
*/
void game_players_screen(Game* game);

/**
Initializes Game `game` and asks players for their names
@input:
  Game `game`
*/
void game_init(Game *game);

/**
Runs the current player's turn and changes who's turn is next
@input:
  Game `game`
@assumes:
  Game `game` has been initialized
  `game_state` is ONGOING
*/
void game_run_turn(Game *game);

/**
Runs the Game `game` until the `game_state` is not `ONGOING`
@input:
  Game `game`
@assumes:
  Game has been initialized
*/
void game_run(Game *game);

/**
Prints which player won and displays the amount of time each of them took
@input:
  Game `game`
*/
void game_end_screen(Game *game);