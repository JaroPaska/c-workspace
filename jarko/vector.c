#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct vector {
    ll *data;
    size_t current;
    size_t limit;
} Vector;

Vector* createVector() {
    Vector *vector = (Vector *) malloc(sizeof(Vector));
    vector->data = (ll *) malloc(sizeof(ll));
    vector->current = 0;
    vector->limit = 1;
    return vector;
}

void deleteVector(Vector *vector) {
    free(vector->data);
    vector->data = NULL;
    free(vector);
    vector = NULL;
}

int is_empty(Vector *vector) {
    return vector->current == 0 ? 1 : 0;
}

void upsize(Vector *vector) {
    ll *new_data = (ll *) malloc(2 * vector->limit * sizeof(ll));
    for (int i = 0; i < vector->current; i++)
        new_data[i] = vector->data[i];
    free(vector->data);
    vector->data = new_data;
    vector->limit *= 2;
}

void downsize(Vector *vector) {
    ll *new_data = (ll *) malloc(2 * vector->current * sizeof(ll));
    for (int i = 0; i < vector->current; i++)
        new_data[i] = vector->data[i];
    free(vector->data);
    vector->data = new_data;
    vector->limit /= 2;
}

void push_back(Vector *vector, ll value) {
    if (vector->current == vector->limit)
        upsize(vector);
    vector->data[vector->current] = value;
    vector->current++;
}

void pop_back(Vector *vector) {
    assert(!is_empty(vector));
    vector->current--;
    if (4 * vector->current == vector->limit)
        downsize(vector);
}

void insert(Vector *vector, int index, ll value) {
    if (vector->current == vector->limit)
        upsize(vector);
    for (int i = vector->current; i > index; i--)
        vector->data[i] = vector->data[i - 1];
    vector->data[index] = value;
    vector->current++;
}

void erase(Vector *vector, int index) {
    assert(!is_empty(vector));
    vector->current--;
    for (int i = index; i < vector->current; i++)
        vector->data[i] = vector->data[i + 1];
    if (4 * vector->current == vector->limit)
        downsize(vector);
}

ll back(Vector *vector) {
    assert(!is_empty(vector));
    return vector->data[vector->current - 1];
}

int main() {
    Vector *vector = createVector();
    push_back(vector, 3);
    push_back(vector, 1);
    push_back(vector, 1);
    insert(vector, 2, 4);
    erase(vector, 0);
    for (int i = 0; i < 4; i++)
        printf("%d ", vector->data[i]);
    deleteVector(vector);
    return 0;
}