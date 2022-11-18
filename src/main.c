#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../include/Game.h"

int main() {
  srand((unsigned int)time(NULL));
  Game *game = malloc(sizeof(Game));
  game_init(game);
  // int y;
  // for (y = 0; y < 3; y++) {
  //   for (int x = 0; x < 6; x++) {
  //     game->grid[y][x] = ((x % 2) == 0) ? RED : YELLOW;
  //   }
  //   game->grid[y][6] = ((y % 2) == 0) ? RED : YELLOW;
  // }
  // y = 3;
  // for (int x = 0; x < 7; x++) {
  //   game->grid[y][x] = ((x % 2) == 0) ? YELLOW : RED;
  // }

  game_run(game);
  free(game);
  return 0;
}
