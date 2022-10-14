#pragma once

#ifdef _WIN64
#define CLEAR() system("cls");
#define PRINTREDTOKEN() printf(" \033[0;31m%c%c\033[0m ", 219, 219);
#define PRINTYELLOWTOKEN() printf(" \033[0;33m%c%c\033[0m ", 219, 219);
#define STARTSCREEN()                                                          \
  CLEAR();                                                                     \
  int a = 177;                                                                 \
  char b[MAX_INPUT_LENGTH];                                                    \
  printf("-------------------------------------------------------------------" \
         "------\n\n\n\n");                                                    \
  printf("                                                                   " \
         "\033[0;31m%c%c%c%c\033[0m  \n",                                      \
         a, a, a, a);                                                          \
  printf("                                                                  "  \
         "\033[0;31m%c%c %c%c\033[0m  \n",                                     \
         a, a, a, a);                                                          \
  printf("  %c%c%c%c%c   %c%c%c%c%c   %c%c%c    %c%c  %c%c%c    %c%c  "        \
         "%c%c%c%c%c   %c%c%c%c%c  %c%c%c%c%c%c    \033[0;31m%c%c  "           \
         "%c%c\033[0m  \n",                                                    \
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,  \
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a);                   \
  printf(" %c%c      %c%c   %c%c  %c%c %c   %c%c  %c%c %c   %c%c  %c%c     "   \
         "%c%c        %c%c     \033[0;31m%c%c   %c%c\033[0m  \n",              \
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,  \
         a, a, a);                                                             \
  printf(" %c%c      %c%c   %c%c  %c%c  %c  %c%c  %c%c  %c  %c%c  %c%c%c%c%c " \
         " %c%c        %c%c    \033[0;31m%c%c    %c%c\033[0m  \n",             \
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,  \
         a, a, a, a, a, a);                                                    \
  printf(" %c%c      %c%c   %c%c  %c%c   %c %c%c  %c%c   %c %c%c  %c%c     "   \
         "%c%c        %c%c   \033[0;31m%c%c     %c%c\033[0m  \n",              \
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,  \
         a, a, a);                                                             \
  printf("  %c%c%c%c%c   %c%c%c%c%c   %c%c    %c%c%c  %c%c    %c%c%c  "        \
         "%c%c%c%c%c   %c%c%c%c%c    %c%c  "                                   \
         "\033[0;31m%c%c%c%c%c%c%c%c%c%c%c%c\033[0m\n",                        \
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a,  \
         a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a, a);       \
  printf("                                                                   " \
         "  \033[0;31m%c%c\033[0m  \n",                                        \
         a, a);                                                                \
  printf("                                                         "           \
         "\033[0;33mBitsNBytes\033[0m  \033[0;31m%c%c\033[0m  \n\n",           \
         a, a);                                                                \
  printf("                         \033[0;34mPress enter to continue\033[0m  " \
         "                       \n\n");                                       \
  printf("-------------------------------------------------------------------" \
         "------\n");                                                          \
  fgets(b, MAX_INPUT_LENGTH, stdin);                                           \
  CLEAR();
#else
#define CLEAR() system("clear");
#define PRINTREDTOKEN() printf(" \033[0;31m%s\033[0m ", "██");
#define PRINTYELLOWTOKEN() printf(" \033[0;33m%s\033[0m ", "██");
#define STARTSCREEN()                                                          \
  CLEAR();                                                                     \
  char b[MAX_INPUT_LENGTH];                                                    \
  printf("-------------------------------------------------------------------" \
         "------\n\n\n\n");                                                    \
  printf("                                                                   " \
         "\033[0;31m%s\033[0m  \n",                                            \
         "▒▒▒▒");                                                              \
  printf("                                                                  "  \
         "\033[0;31m%s %s\033[0m  \n",                                         \
         "▒▒", "▒▒");                                                          \
  printf("  %s   %s   %s    %s  %s    %s  %s   %s  %s    \033[0;31m%s  "       \
         "%s\033[0m  \n",                                                      \
         "▒▒▒▒▒", "▒▒▒▒▒", "▒▒▒", "▒▒", "▒▒▒", "▒▒", "▒▒▒▒▒", "▒▒▒▒▒",         \
         "▒▒▒▒▒▒", "▒▒", "▒▒");                                                \
  printf(" %s      %s   %s  %s %s   %s  %s %s   %s  %s     %s        %s     "  \
         "\033[0;31m%s   %s\033[0m  \n",                                       \
         "▒▒", "▒▒", "▒▒", "▒▒", "▒", "▒▒", "▒▒", "▒", "▒▒", "▒▒", "▒▒", "▒▒", \
         "▒▒", "▒▒");                                                          \
  printf(" %s      %s   %s  %s  %s  %s  %s  %s  %s  %s  %s        %s    "      \
         "\033[0;31m%s    %s\033[0m  \n",                                      \
         "▒▒", "▒▒", "▒▒", "▒▒", "▒", "▒▒", "▒▒", "▒", "▒▒", "▒▒▒▒▒", "▒▒",    \
         "▒▒", "▒▒", "▒▒");                                                    \
  printf(" %s      %s   %s  %s   %s %s  %s   %s %s  %s     %s        %s   "    \
         "\033[0;31m%s     %s\033[0m  \n",                                     \
         "▒▒", "▒▒", "▒▒", "▒▒", "▒", "▒▒", "▒▒", "▒", "▒▒", "▒▒", "▒▒", "▒▒", \
         "▒▒", "▒▒");                                                          \
  printf(                                                                      \
      "  %s   %s   %s    %s  %s    %s  %s   %s    %s  \033[0;31m%s\033[0m\n",  \
      "▒▒▒▒▒", "▒▒▒▒▒", "▒▒", "▒▒▒", "▒▒", "▒▒▒", "▒▒▒▒▒", "▒▒▒▒▒", "▒▒",      \
      "▒▒▒▒▒▒▒▒▒▒▒▒");                                                         \
  printf("                                                                   " \
         "  \033[0;31m%s\033[0m  \n",                                        \
         "▒▒");                                                                \
  printf("                                                         "           \
         "\033[0;33mBitsNBytes\033[0m  \033[0;31m%s\033[0m  \n\n",           \
         "▒▒");                                                                \
  printf("                         \033[0;34mPress enter to continue\033[0m  " \
         "                       \n\n");                                       \
  printf("-------------------------------------------------------------------" \
         "------\n");                                                          \
  fgets(b, MAX_INPUT_LENGTH, stdin);                                           \
  CLEAR();
#endif