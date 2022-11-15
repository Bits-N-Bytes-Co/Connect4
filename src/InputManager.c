#include "../include/InputManager.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validate_input(char *string, int *integer) {
  int i = 0;
  int length = strlen(string);
  char buffer[MAX_INPUT_LENGTH];
  int buffer_index = 0;

  while (isspace(string[i])) {
    i++;
  }

  if (length == i) {
    return false;
  }

  while (i < length && !isspace(string[i])) {
    if (!isdigit(string[i])) {
      return false;
    }
    buffer[buffer_index] = string[i];
    buffer_index++;
    i++;
  }

  buffer[buffer_index] = '\0';

  while (isspace(string[i])) {
    i++;
  }

  if (string[i] != '\0') {
    return false;
  }

  *integer = atoi(buffer);

  return true;
}

void remove_delimiter(char *string) {
  int i = 0;
  while (string[i] != '\0')
    i++;

  if (i > 1 && string[i - 1] == '\n') {
    string[i - 1] = '\0';
  }
}

int take_valid_input() {
  int input = 0;
  char buffer[MAX_INPUT_LENGTH];

  fgets(buffer, MAX_INPUT_LENGTH, stdin);
  while (!validate_input(buffer, &input)) {
    printf("Invalid input. Please enter a single positive integer: ");
    fgets(buffer, MAX_INPUT_LENGTH, stdin);
  }
  return input;
}
