#include <stdlib.h>
#include <string.h>

#ifndef L
#error hash.h: L not defined
#endif

#define TPL_(type, name) type ## name
#define TPL(type, name) TPL_(type, name)

typedef struct {
	char	*key;
	L		val;
} TPL(L, he_);

#define T TPL(L, he_)

typedef struct TPL(T, ll__) {
	T					val;
	struct TPL(T, ll__)	*next;
} TPL(T, ll_);

typedef struct {
	TPL(T, ll_) *head;
	TPL(T, ll_) *back;
} TPL(T, ll);

static void
TPL(T, ll_init)(TPL(T, ll) *ll)
{
	ll->head = NULL;
	ll->back = NULL;
}

static T
TPL(T, ll_insert)(TPL(T, ll) *ll, T what)
{
	TPL(T, ll_) *n = malloc(sizeof(TPL(T, ll_)));
	n->val = what;
	n->next = ll->head;
	if (ll->back == NULL) ll->back = n;
	ll->head = n;
	return what;
}

static T
TPL(T, ll_insert_back)(TPL(T, ll) *ll, T what)
{
	TPL(T, ll_) *n = malloc(sizeof(TPL(T, ll_)));
	n->val = what;
	n->next = NULL;
	if (ll->back) ll->back->next = n;
	ll->back = n;
	if (ll->head == NULL) ll->head = n;
	return what;
}

static T
TPL(T, ll_insert_after)(TPL(T, ll) *ll, TPL(T, ll_) *after, T what)
{
	TPL(T, ll_) *n = malloc(sizeof(TPL(T, ll_)));
	n->val = what;
	n->next = after->next;
	after->next = n;
	return what;
}

static TPL(T, ll_) *
TPL(T, ll_lookup)(TPL(T, ll) *ll, char *what)
{
	TPL(T, ll_) *next = ll->head;
	while (next) {
		if (!strcmp(next->val.key, what)) return next;
		next = next->next;
	}
	return NULL;
}

static void
TPL(T, ll_free)(TPL(T, ll) *ll)
{
	TPL(T, ll_) *tmp;
	TPL(T, ll_) *next = ll->head;
	while (next) {
		tmp = next->next;
		free(next);
		next = tmp;
	}
	ll->head = NULL;
	ll->back = NULL;
}

// --

size_t hash(unsigned char *);
#ifndef HASH_HASH_FUNC
#define HASH_HASH_FUNC
size_t
hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash;
}
#endif

typedef struct {
	size_t			len;
	TPL(L, he_ll)	*arr;
} TPL(L, h);

static void
TPL(L, h_init)(TPL(L, h) *h, size_t len)
{
	h->len = len;
	h->arr = malloc(sizeof(TPL(L, he_ll)) * len);
	for (int i = 0; i < len; i++) {
		TPL(L, he_ll_init)(h->arr + i);
	}
}

static void
TPL(L, h_set)(TPL(L, h) *h, char *key, L what)
{
	size_t hashnum = hash(key) % h->len;
	TPL(L, he_ll_) *el = TPL(L, he_ll_lookup)(h->arr + hashnum, key);
	if (el) {
		el->val.val = what;
	} else {
		TPL(L, he_) newel;
		newel.key = key;
		newel.val = what;
		TPL(L, he_ll_insert)(h->arr + hashnum, newel);
	}
}

static L *
TPL(L, h_get)(TPL(L, h) *h, char *key)
{
	size_t hashnum = hash(key) % h->len;
	TPL(L, he_ll_) *el = TPL(L, he_ll_lookup)(h->arr + hashnum, key);
	if (el) {
		return &el->val.val;
	}
	return NULL;
}

static int
TPL(L, h_del)(TPL(L, h) *h, char *key)
{
	size_t hashnum = hash(key) % h->len;
	TPL(L, he_ll_) *pel = h->arr[hashnum].head;
	TPL(L, he_ll_) *el = pel;
	while (el) {
		if (!strcmp(el->val.key, key)) {
			if (el == h->arr[hashnum].head)
				h->arr[hashnum].head = el->next;
			else
				pel->next = el->next;
			free(el);
			return 1;
		}
		pel = el;
		el = el->next;
	}
	return 0;
}

static void
TPL(L, h_free)(TPL(L, h) *h)
{
	for (int i = 0; i < h->len; i++) {
		TPL(L, he_ll_free)(h->arr + i);
	}
	free(h->arr);
	h->arr = NULL;
	h->len = 0;
}

#undef T
#undef L