#ifndef MYSTRING_H
#define MYSTRING_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *cut_string(char *str, int start, int end);
char **split_string(char *str);
int is_in_string(char *str, char *a);
int find_next_nan(char *str, int index);
char *slice_str(char *str, int start, int end);
char *concat_strings(int argc, char **argv);
char *add_to_str(char *dest, char *src, int index);
int valid_characters(char *str, char *valid);

#endif /* MYSTRING_H */
