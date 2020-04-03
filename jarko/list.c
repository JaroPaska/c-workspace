#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef long long ll;

typedef struct list {
    ll     *data;
    size_t  current;
    size_t  limit;
} List;

void create(List *l) {
    l = (List *) malloc(sizeof(List));
    l->data = (ll *) malloc(sizeof(ll));
    l->current = 0;
    l->limit = 1;
}

void delete(List *l) {
    free(l->data);
    free(l);
}

void push_back(List *l, ll value) {
    if (l->current == l->limit) {
        ll *new_data = (ll *) malloc(2 * l->limit * sizeof(ll));
        for (int i = 0; i < l->current; i++)
            new_data[i] = l->data[i];
        free(l->data);
        l->data = new_data;
        l->limit *= 2;
    }
    l->data[l->current] = value;
    l->current++;
}

void pop_back(List *l) {
    assert(l->current > 0);
    l->current--;
    if (4 * l->current == l->limit) {
        ll *new_data = (ll *) malloc(2 * l->current * sizeof(ll));
        for (ll i = 0; i < l->current; i++)
            new_data[i] = l->data[i];
        free(l->data);
        l->data = new_data;
        l->limit /= 2;
    }
}

ll back(List *l) {
    assert(l->current > 0);
    return l->data[l->current - 1];
}

int main() {
    int n;
    scanf("%d", &n);

    int h[50100], v[50100];
    long long res[50100];
    for (int i = 0; i < n; i++)
        res[i] = 0;
    for (int i = 0; i < n; i++)
        scanf("%d %d", &h[i], &v[i]);

    List *s;
    create(s);
    for (int i = 0; i < n; i++) {
        while (s->current > 0 && h[back(s)] < h[i]) {
            res[i] += v[back(s)];
            pop_back(s);
        }
        push_back(s, i);
    }
    delete(s);

    create(s);
    for (int i = n-1; i >= 0; i--) {
        while (s->current > 0 && h[back(s)] < h[i]) {
            res[i] += v[back(s)];
            pop_back(s);
        }
        push_back(s, i);
    }
    delete(s);

    long long maxi = 0;
    for (int i = 0; i < n; i++)
        maxi = (res[i] > maxi ? res[i] : maxi);
    printf("%lld\n", maxi);
}