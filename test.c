#include "vec.h"

#include <stdio.h>

int main() {
    int i;
    struct vec vec;
    vec_init(&vec, sizeof(int));
    for (int a = 0; a < 1000000000; a++) {
        //printf("%d\n", a);
        vec_push(&vec, &a);
    }
    for (int a = 0; a < vec.len; a++) {
        //vec_get(&vec, a, &i);
        //printf("%d\n", i);
    }
    vec_finish(&vec);
    return 0;
}