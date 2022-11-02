#include "../include/InputManager.h"

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

void take_valid_input(int *col) {
  bool input_is_valid = true;

  do {
    char buffer[MAX_INPUT_LENGTH];
    fgets(buffer, MAX_INPUT_LENGTH, stdin);

    input_is_valid = validate_input(buffer, col);
    input_is_valid = input_is_valid && *col > 0 && *col < 8;

    if (!input_is_valid) {
      printf("Invalid input. Please enter an integer between 1 and 7: ");
    }
  } while (!input_is_valid);
}
