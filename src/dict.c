#include "dict.h"

dict_t *new_dict(int max_size)
{
	dict_t *d = malloc(sizeof(dict_t));
	d->max_size = max_size;
	d->len = 0;
	d->words = malloc(sizeof(word_t) * max_size);
	return d;
}

word_t new_word(char *w)
{
	word_t word;
	word.letters = malloc(sizeof(char) * strlen(w));
	strcpy(word.letters, w);
	word.len = strlen(w);
	return word;
}

dict_t *resize_dict(dict_t *d, int new_size)
{
	if (new_size < d->max_size)
		return d;
	d->max_size = new_size;
	d->words = realloc(d->words, new_size * sizeof(word_t));
	return d;
}

dict_t *add_word(dict_t *d, char *w)
{
	if (d->len + 1 == d->max_size)
		d = resize_dict(d, d->max_size + 10);

	d->words[d->len] = new_word(w);
	d->len++;
	return d;
}

shelf_t *new_shelf(int max_size)
{

	shelf_t *s = malloc(sizeof(shelf_t));
	s->d = malloc(sizeof(dict_t *) * max_size);
	s->max_size = max_size;
	s->len = 0;
	return s;
}

shelf_t *resize_shelf(shelf_t *s, int new_size)
{
	if (new_size < s->max_size)
		return s;

	s->max_size = new_size;
	s->d = realloc(s->d, new_size * sizeof(dict_t *));
	return s;
}

shelf_t *add_dict(shelf_t *s, dict_t *d)
{
	if (s->len + 1 == s->max_size)
		s = resize_shelf(s, s->max_size + 10);
	s->d[s->len] = d;
	s->len++;
	return s;
}