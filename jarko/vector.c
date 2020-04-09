#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long vector_t;

typedef struct vector {
    vector_t *data;
    size_t current;
    size_t limit;
} Vector;

Vector* createVector() {
    Vector *vector = (Vector *) malloc(sizeof(Vector));
    vector->data = (vector_t *) malloc(sizeof(vector_t));
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

int size(Vector *vector) {
    return vector->current;
}

int is_empty(Vector *vector) {
    return vector->current == 0 ? 1 : 0;
}

int is_in_range(Vector *vector, int index) {
    return index >= 0 && index < vector->current ? 1 : 0;
}

void upsize(Vector *vector) {
    vector_t *new_data = (vector_t *) malloc(2 * vector->limit * sizeof(vector_t));
    for (int i = 0; i < vector->current; i++)
        new_data[i] = vector->data[i];
    free(vector->data);
    vector->data = new_data;
    vector->limit *= 2;
}

void downsize(Vector *vector) {
    vector_t *new_data = (vector_t *) malloc(2 * vector->current * sizeof(vector_t));
    for (int i = 0; i < vector->current; i++)
        new_data[i] = vector->data[i];
    free(vector->data);
    vector->data = new_data;
    vector->limit /= 2;
}

void push_back(Vector *vector, vector_t value) {
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

void insert(Vector *vector, int index, vector_t value) {
    assert(index >= 0 && index <= vector->current);
    if (vector->current == vector->limit)
        upsize(vector);
    for (int i = vector->current; i > index; i--)
        vector->data[i] = vector->data[i - 1];
    vector->data[index] = value;
    vector->current++;
}

void erase(Vector *vector, int index) {
    assert(is_in_range(vector, index));
    vector->current--;
    for (int i = index; i < vector->current; i++)
        vector->data[i] = vector->data[i + 1];
    if (4 * vector->current == vector->limit)
        downsize(vector);
}

vector_t get(Vector *vector, int index) {
    assert(is_in_range(vector, index));
    return vector->data[index];
}

void set(Vector *vector, int index, vector_t value) {
    assert(is_in_range(vector, index));
    vector->data[index] = value;
}

vector_t back(Vector *vector) {
    assert(!is_empty(vector));
    return vector->data[vector->current - 1];
}

int find(Vector *vector, vector_t value) {
    for (int i = 0; i < vector->current; i++)
        if (vector->data[i] == value)
            return i;
    return -1;
}

int main() {
    Vector *vector = createVector();
    insert(vector, 0, 3);
    deleteVector(vector);
}