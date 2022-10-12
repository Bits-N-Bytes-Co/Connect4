#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_LENGTH 50

/**
 * Parses a string into a positive integer if the sting is of the right format
 * tested formats (e.g. for the int 2):
 *
 * valid: "   2   ", "000..02", "2", "\t2", "\n2"
 * invalid: "2 2", "2.2", "abc", "-2", "  2  2  "
 */
bool validate_input(char *string, int *integer);

/**
 *  removes endl char at the end of a string
 */
void remove_delimiter(char *string);

void take_valid_input(int *col);