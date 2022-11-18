#include <stdio.h>
#include <stdlib.h>

#include "../include/OutputManager.h"

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

void clear_screen() { system(CLEAR_COMMAND); }

void print_end_screen(Game *game) {
  printf("-----------------------------------------------------------------"
         "\n\n\n\n\n");
  switch (game->game_state) {
  case ONGOING:
    printf(
        "                 ERROR: the game is not over yet                 \n");
    break;
  case RED_WINS:
    printf("                            \033[0;31mRED WON!\033[0m              "
           "               \n");
    break;
  case YELLOW_WINS:
    printf("                         \033[0;33mYELLOW WON!\033[0m              "
           "             \n");
    break;
  case TIE:
    printf("                            \033[0;32mTIE!\033[0m                  "
           "             \n");
    break;
  case RED_WON_BY_TIME:
    printf("                            \033[0;31mRED WON BY TIME!\033[0m      "
           "                         \n");
    break;
  case YELLOW_WON_BY_TIME:
    printf(
        "                            \033[0;33mYELLOW WON BY TIME!\033[0m      "
        "                         \n");
    break;
  default:
    break;
  }
  printf("\n");
  for (int player_num = 0; player_num < PLAYERS_NUM; player_num++) {
    printf("                      \033[0;%dm%s\033[0m: %.3f seconds        "
           "          \n",
           (game->players[player_num].token == RED) ? 31 : 33,
           game->players[player_num].name,
           game->players[player_num].total_time);
  }
  printf("\n\n\n\n\n-----------------------------------------------------------"
         "------\n");
}

void print_start_screen() {
  clear_screen();
  char b[MAX_INPUT_LENGTH];
  printf("-------------------------------------------------------------------"
         "------\n\n\n\n");
#ifdef _WIN32
  int a = 177;
  printf("                                                                   "
         "\033[0;31m%c%c%c%c\033[0m  \n",
         a, a, a, a);
  printf("                                                                  "
         "\033[0;31m%c%c %c%c\033[0m  \n",
         a, a, a, a);
  printf("  %c%c%c%c%c   %c%c%c%c%c   %c%c%c    %c%c  %c%c%c    %c%c  "
         "%c%c%c%c%c   %c%c%c%c%c  %c%c%c%c%c%c    \033[0;31m%c%c  "
         "%c%c\033[0m  \n",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  printf(" %c%c      %c%c   %c%c  %c%c %c   %c%c  %c%c %c   %c%c  %c%c     "
         "%c%c        %c%c     \033[0;31m%c%c   %c%c\033[0m  \n",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a);
  printf(" %c%c      %c%c   %c%c  %c%c  %c  %c%c  %c%c  %c  %c%c  %c%c%c%c%c "
         " %c%c        %c%c    \033[0;31m%c%c    %c%c\033[0m  \n",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a, a);
  printf(" %c%c      %c%c   %c%c  %c%c   %c %c%c  %c%c   %c %c%c  %c%c     "
         "%c%c        %c%c   \033[0;31m%c%c     %c%c\033[0m  \n",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a);
  printf("  %c%c%c%c%c   %c%c%c%c%c   %c%c    %c%c%c  %c%c    %c%c%c  "
         "%c%c%c%c%c   %c%c%c%c%c    %c%c  "
         "\033[0;31m%c%c%c%c%c%c%c%c%c%c%c%c\033[0m\n",
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a);
  printf("                                                                   "
         "  \033[0;31m%c%c\033[0m  \n",
         a, a);
  printf("                                                         "
         "\033[0;33mBitsNBytes\033[0m  \033[0;31m%c%c\033[0m  \n\n",
         a, a);
#else
  printf("                                                                   "
         "\033[0;31m▒▒▒▒\033[0m  \n");
  printf("                                                                  "
         "\033[0;31m▒▒ ▒▒\033[0m  \n");
  printf("  ▒▒▒▒▒   ▒▒▒▒▒   ▒▒▒    ▒▒  ▒▒▒    ▒▒  ▒▒▒▒▒   ▒▒▒▒▒  ▒▒▒▒▒▒    "
         "\033[0;31m▒▒  ▒▒\033[0m  \n");
  printf(" ▒▒      ▒▒   ▒▒  ▒▒ ▒   ▒▒  ▒▒ ▒   ▒▒  ▒▒     ▒▒        ▒▒     "
         "\033[0;31m▒▒   ▒▒\033[0m  \n");
  printf(" ▒▒      ▒▒   ▒▒  ▒▒  ▒  ▒▒  ▒▒  ▒  ▒▒  ▒▒▒▒▒  ▒▒        ▒▒    "
         "\033[0;31m▒▒    ▒▒\033[0m  \n");
  printf(" ▒▒      ▒▒   ▒▒  ▒▒   ▒ ▒▒  ▒▒   ▒ ▒▒  ▒▒     ▒▒        ▒▒   "
         "\033[0;31m▒▒     ▒▒\033[0m  \n");
  printf("  ▒▒▒▒▒   ▒▒▒▒▒   ▒▒    ▒▒▒  ▒▒    ▒▒▒  ▒▒▒▒▒   ▒▒▒▒▒    ▒▒  "
         "\033[0;31m▒▒▒▒▒▒▒▒▒▒▒▒\033[0m\n");
  printf("                                                                   "
         "  \033[0;31m▒▒\033[0m  \n");
  printf("                                                         "
         "\033[0;33mBitsNBytes\033[0m  \033[0;31m▒▒\033[0m  \n\n");
#endif
  printf("                         \033[0;34mPress enter to continue\033[0m  "
         "                       \n\n");
  printf("-------------------------------------------------------------------"
         "------\n");
  fgets(b, MAX_INPUT_LENGTH, stdin);
  clear_screen();
}

void print_grid(Game *game) {
  clear_screen();
  printf("\033[0;32mTimer\033[0m\n");
  printf("%s: %.3f s\t", game->players[0].name, game->players[0].total_time);
  printf("%s: %.3f s\n", game->players[1].name, game->players[1].total_time);
  printf("|  1 |  2 |  3 |  4 |  5 |  6 |  7 |\n");
  printf("| -- + -- + -- + -- + -- + -- + -- |\n");
  for (int y = ROW_NUM - 1; y >= 0; y--) {
    printf("|");
    for (int x = 0; x < COL_NUM; x++) {
      if (game->grid[y][x] == RED) {
        PRINTREDTOKEN();
        printf("|");
      } else if (game->grid[y][x] == YELLOW) {
        PRINTYELLOWTOKEN();
        printf("|");
      } else {
        printf("    |");
      }
    }
    printf("\n");
    printf("| -- + -- + -- + -- + -- + -- + -- |\n");
  }
}

void game_players_screen(Game *game) {
  clear_screen();
  char a[MAX_INPUT_LENGTH];

  for (int i = 0; i < PLAYERS_NUM; i++) {
    printf("Player %d:\n", (i + 1));
    printf("Name: %s\n", game->players[i].name);
    printf("Token: %s\n\n", (game->players[i].token == RED)
                                ? "\033[0;31mRED\033[0m"
                                : "\033[0;33mYELLOW\033[0m");
  }
  printf("\033[0;34mPress enter to continue\033[0m");
  fgets(a, MAX_INPUT_LENGTH, stdin);
}

void game_mode_screen() {
  printf("-----------\033[0;32mGAME MODES:\033[0m-----------\n\n");
  printf("         1) Simulation\n");
  printf("         2) Single-Player\n");
  printf("         3) Multi-Player\n\n");
  printf("---------------------------------\n");
  printf("Enter your choice (1-3): ");
}

void difficulty_screen() {
  printf("------\033[0;32mGAME DIFFICULTIES:\033[0m------\n\n");
  printf("          1) Easy\n");
  printf("          2) Medium\n");
  printf("          3) Hard\n\n");
  printf("------------------------------\n");
}