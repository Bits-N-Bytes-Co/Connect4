#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  Takes the int* `col` representing the given column number, and if it is
  invalid, prompts to enter again.
  @input:
    int* `col` representing the given column number
*/
void take_valid_input(int *col);