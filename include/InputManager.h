#pragma once

#include "../include/Types.h"
#include <stdbool.h>

/**
  Parses the char* `string` into a positive integer if `string` is of the right
  format, and puts it in int* `integer`, else it returns `false`
  @input:
    char* `string`
    int* `integer`
  @tested:
    valid: "   2   ", "000..02", "2", "\t2", "\n2"
    invalid: "2 2", "2.2", "abc", "-2", "  2  2  "
  @returns:
    bool: false if input is invalid, true if it is valid
*/
bool validate_input(char *string, int *integer);

/**
  Removes the endl char at the end of the char* string
  @input:
    char* `string`
*/
void remove_delimiter(char *string);

/**
  Takes input from stdin, while the input is invalid (not a single positive
  integer), prompts to enter again.
  @returns:
    An `int` representing a vald int
*/
int take_valid_input();