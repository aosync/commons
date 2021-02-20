#include <stdlib.h>
#include <string.h>

struct vec {
	size_t	msize;
	size_t	len;
	size_t	cap;
	void	*arr;
};

void vec_init(struct vec *, size_t);
void vec_get(struct vec *, size_t, void *);
void vec_set(struct vec *, void *, size_t);
void vec_push(struct vec *, void *);
void vec_pop(struct vec *, void *);
void vec_insert(struct vec *, void *, size_t);
void vec_erase(struct vec *, size_t);
void vec_finish(struct vec *);