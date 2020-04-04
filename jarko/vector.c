#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

typedef struct vector {
    ll     *data;
    size_t  current;
    size_t  limit;
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

void push_back(Vector *vector, ll value) {
    if (vector->current == vector->limit) {
        ll *new_data = (ll *) malloc(2 * vector->limit * sizeof(ll));
        for (int i = 0; i < vector->current; i++)
            new_data[i] = vector->data[i];
        free(vector->data);
        vector->data = new_data;
        vector->limit *= 2;
    }
    vector->data[vector->current] = value;
    vector->current++;
}

void pop_back(Vector *vector) {
    assert(vector->current > 0);
    vector->current--;
    if (4 * vector->current == vector->limit) {
        ll *new_data = (ll *) malloc(2 * vector->current * sizeof(ll));
        for (int i = 0; i < vector->current; i++)
            new_data[i] = vector->data[i];
        free(vector->data);
        vector->data = new_data;
        vector->limit /= 2;
    }
}

ll back(Vector *vector) {
    assert(vector->current > 0);
    return vector->data[vector->current - 1];
}

int main() {
    int n;
    scanf("%d", &n);

    // allocate memory and read input
    int *h = (int *) malloc(n * sizeof(int));
    int *v = (int *) malloc(n * sizeof(int));
    ll *res = (ll *) malloc(n * sizeof(ll));
    for (int i = 0; i < n; i++)
        scanf("%d %d", &h[i], &v[i]);
    memset(res, 0, n * sizeof(ll));

    // moos from left to right
    Vector *vector = createVector();
    for (int i = 0; i < n; i++) {
        while (vector->current > 0 && h[back(vector)] < h[i]) {
            res[i] += v[back(vector)];
            pop_back(vector);
        }
        push_back(vector, i);
    }
    deleteVector(vector);

    // moos from right to left
    vector = createVector();
    for (int i = n-1; i >= 0; i--) {
        while (vector->current > 0 && h[back(vector)] < h[i]) {
            res[i] += v[back(vector)];
            pop_back(vector);
        }
        push_back(vector, i);
    }
    deleteList(vector);
    long long maxi = 0;
    for (int i = 0; i < n; i++)
        maxi = (res[i] > maxi ? res[i] : maxi);
    printf("%lld\n", maxi);
    
    // deallocate memory and return success (code 0)
    free(h);
    free(v);
    free(res);
    return 0;
}