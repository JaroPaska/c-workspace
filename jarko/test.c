#include <stdio.h>

#include "vector.h"

int main() {
    Vector *vector = createVector();
    insert(vector, 0, 1);
    insert(vector, 0, 4);
    insert(vector, 0, 1);
    insert(vector, 0, 3);
    for (int i = 0; i < size(vector); i++)
        printf("%d\n", get(vector, i));
}