#include "vec.h"

void
vec_init(struct vec *vec, size_t msize)
{
    vec->msize = msize;
	vec->len = 0;
	vec->cap = 0;
	vec->arr = NULL;
}

void
vec_get(struct vec *vec, size_t where, void *what)
{
    memcpy(what, vec->arr + where * vec->msize, vec->msize);
}

void
vec_set(struct vec *vec, void *what, size_t where)
{
    memcpy(vec->arr + where * vec->msize, what, vec->msize);
}

void
vec_push(struct vec *vec, void *what)
{
	if (vec->len >= vec->cap) {
		vec->cap = vec->cap ? vec->cap * 2 : 1;
		vec->arr = realloc(vec->arr, vec->cap * vec->msize);
	}
    memcpy(vec->arr + (vec->len++) * vec->msize, what, vec->msize);
}

void
vec_pop(struct vec *vec, void *where)
{
    memcpy(where, vec->arr + vec->msize*(--vec->len), vec->msize);
	if (vec->len <= vec->cap/2) {
		vec->cap /= 2;
		vec->arr = realloc(vec->arr, vec->cap * vec->msize);
	}
}

void
vec_insert(struct vec *vec, void *what, size_t where)
{
	size_t amount = (vec->len - where) * vec->msize;
	vec->len++;
	if (vec->len >= vec->cap) {
		// vec->blocks *= 2;
		vec->cap = vec->cap ? vec->cap * 2 : 1;
		vec->arr = realloc(vec->arr, vec->cap * vec->msize);
	}
	memmove(vec->arr + (where + 1) * vec->msize, vec->arr + where * vec->msize, amount);
	memcpy(vec->arr + where * vec->msize, what, vec->msize);
}

void
vec_erase(struct vec *vec, size_t where)
{
	size_t amount = (vec->len - where - 1) * vec->msize;
	vec->len--;
	memmove(vec->arr + where * vec->msize, vec->arr + (where + 1) * vec->msize, amount);
	if (vec->len <= vec->cap/2) {
		vec->cap /= 2;
		vec->arr = realloc(vec->arr, vec->cap * vec->msize);
	}
}

void vec_finish(struct vec *vec)
{
    free(vec->arr);
	vec->arr = NULL;
	vec->cap = 0;
	vec->len = 0;
}