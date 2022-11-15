#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "../include/Game.h"

int main() {
  srand((unsigned int)time(NULL));
  Game *game = malloc(sizeof(Game));
  game_init(game);
  game_run(game);
  free(game);
  return 0;
}
