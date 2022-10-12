#include "../include/Game.h"

int main() {
  Game *game = malloc(sizeof(Game));
  game_init(game);
  game_run(game);
  free(game);
  return 0;
}
