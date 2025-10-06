#include "matching.h"
#include <stdio.h>
#include <stdlib.h>

Matching *create_matching(int m, int n, int **server_pref, int **user_pref, int *slots) {
    Matching *match = malloc(sizeof(Matching));
    match->m = m;
    match->n = n;
    match->server_preference = server_pref;
    match->user_preference = user_pref;
    match->server_slots = slots;
    match->user_matching = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++)
        match->user_matching[i] = -1;
    return match;
}

Matching *create_matching_copy(Matching *data) {
    Matching *copy = malloc(sizeof(Matching));
    copy->m = data->m;
    copy->n = data->n;
    copy->server_preference = data->server_preference;
    copy->user_preference = data->user_preference;
    copy->server_slots = data->server_slots;
    copy->user_matching = malloc(copy->n * sizeof(int));
    for (int i = 0; i < copy->n; i++)
        copy->user_matching[i] = data->user_matching[i];
    return copy;
}

void free_matching(Matching *match) {
    free(match->user_matching);
    free(match);
}

int total_server_slots(Matching *match) {
    int total = 0;
    for (int i = 0; i < match->m; i++)
        total += match->server_slots[i];
    return total;
}

void print_matching(Matching *match) {
    printf("m=%d n=%d\n", match->m, match->n);
    for (int i = 0; i < match->n; i++)
        printf("User %d Server %d\n", i, match->user_matching[i]);
}
