#ifndef STR_H
#define STR_H

#include <stdlib.h>
#include <string.h>

size_t upper_power_of_two(size_t);
#ifndef STR_UPPER_POWER_OF_TWO_FUNC
#define STR_UPPER_POWER_OF_TWO_FUNC
size_t
upper_power_of_two(size_t v)
{
    v--;
    v |= v >> 1;
    v |= v >> 2;
    v |= v >> 4;
    v |= v >> 8;
    v |= v >> 16;
    v++;
    return v;
}
#endif

typedef struct {
	size_t 	len;
	size_t 	blocks;
	char	*arr;
} str;

static void
str_init(str *s)
{
	s->len = 0;
	s->blocks = 0;
	s->arr = NULL;
}

static void
str_from(str *s, char *cs)
{
	size_t len = strlen(cs);
	str_init(s);
	s->len = len;
	if (s->len + 1 > s->blocks) {
		s->blocks = upper_power_of_two(s->len+1);
		s->arr = realloc(s->arr, s->blocks * sizeof(char));
	}
	strcpy(s->arr, cs);
}

static void
str_append(str *s, char *cs)
{
	size_t len = strlen(cs);
	s->len = s->len + len;
	if (s->len + 1 > s->blocks) {
		s->blocks = upper_power_of_two(s->len+1);
		s->arr = realloc(s->arr, s->blocks * sizeof(char));
	}
	strcat(s->arr, cs);
}

static char
str_pop(str *s)
{
	char what;
	if (s->len == 0) return what;
	what = s->arr[--s->len - 1];
	s->arr[s->len] = '\0';
	if (s->len + 1 <= s->blocks/2) {
		s->blocks /= 2;
		s->arr = realloc(s->arr, s->blocks * sizeof(char));
	}
	return what;
}

static char
str_insert(str *s, size_t where, char what)
{
	size_t amount = (s->len - where + 1) * sizeof(char);
	s->len++;
	if (s->len + 1 >= s->blocks) {
		s->blocks = s->blocks ? s->blocks * 2 : 1;
		s->arr = realloc(s->arr, s->blocks * sizeof(char));
	}
	memmove(s->arr + where + 1, s->arr + where, amount);
	s->arr[where] = what;
	return what;
}

static char
str_erase(str *s, size_t where)
{
	size_t amount = (s->len - where) * sizeof(char);
	char what = s->arr[where];
	s->len--;
	memmove(s->arr + where, s->arr + where + 1, amount);
	if (s->len + 1 <= s->blocks/2) {
		s->blocks /= 2;
		s->arr = realloc(s->arr, s->blocks * sizeof(char));
	}
	return what;
}

static char
str_substr(str *s, str *a, size_t first)
{
	str b;
	str_from(&b, s->arr + first);
	a->blocks = b.blocks;
	a->len = b.len;
	a->arr = b.arr;
}

static void
str_free(str *s)
{
	free(s->arr);
	s->arr = NULL;
	s->blocks = 0;
	s->len = 0;
}

#endif