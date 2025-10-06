#ifndef MATCHING_H
#define MATCHING_H

#include <stdlib.h>

typedef struct {
    int m; // number of servers
    int n; // number of users
    int **server_preference; // server preference lists [m][n]
    int **user_preference;   // user preference lists [n][m]
    int *server_slots;       // slots per server [m]
    int *user_matching;      // user->server assignment [n]
} Matching;

// Functions
Matching *create_matching(int m, int n, int **server_pref, int **user_pref, int *slots);
Matching *create_matching_copy(Matching *data);
void free_matching(Matching *match);
int total_server_slots(Matching *match);
void print_matching(Matching *match);

#endif
