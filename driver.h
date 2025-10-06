#ifndef DRIVER_H
#define DRIVER_H

#include "matching.h"

// Functions
void parse_args(int argc, char *argv[], char **filename, int *test_gs);
Matching *parse_matching_problem(const char *filename);
void test_run(Matching *problem, int test_gs);
int is_stable(Matching *match);
Matching *stable_gale_shapley(Matching *problem);

#endif
