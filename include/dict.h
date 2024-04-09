#ifndef DICT_H
#define DICT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

typedef struct word
{
    int len;
    char *letters;
} word_t;

typedef struct dict
{
    int len;
    int max_size;
    word_t *words;
} dict_t;

typedef struct shelf
{
    int len;
    int max_size;
    dict_t **d;
} shelf_t;

dict_t *new_dict(int max_size);
word_t new_word(char *w);
dict_t *resize_dict(dict_t *d, int new_size);
dict_t *add_word(dict_t *d, char *w);
shelf_t *new_shelf(int max_size);
shelf_t *resize_shelf(shelf_t *s, int new_size);
shelf_t *add_dict(shelf_t *s, dict_t *d);

#endif /* DICT_H */