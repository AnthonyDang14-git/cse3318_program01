#include "driver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void usage() {
    fprintf(stderr, "usage: driver [-g] <filename>\n");
    fprintf(stderr, "\t-g\tTest Gale-Shapley server optimal implementation\n");
    exit(1);
}

void parse_args(int argc, char *argv[], char **filename, int *test_gs) {
    *filename = NULL;
    *test_gs = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-g") == 0) *test_gs = 1;
        else if (argv[i][0] != '-') *filename = argv[i];
        else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            usage();
        }
    }

    if (*filename == NULL) usage();
    
    *test_gs = 1;
}

// Utility: Read 1D array
int *read_int_array(FILE *fp, int len) {
    int *arr = malloc(len * sizeof(int));
    for (int i = 0; i < len; i++) {
        if (fscanf(fp, "%d", &arr[i]) != 1) {
            fprintf(stderr, "Error reading array\n");
            exit(1);
        }
    }
    return arr;
}

// Utility: Read 2D array
int **read_int_matrix(FILE *fp, int rows, int cols) {
    int **matrix = malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++)
        matrix[i] = read_int_array(fp, cols);
    return matrix;
}

// Parse the problem file
Matching *parse_matching_problem(const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return NULL;
    }

    int m, n;
    if (fscanf(fp, "%d %d", &m, &n) != 2) {
        fprintf(stderr, "Error reading problem sizes\n");
        fclose(fp);
        return NULL;
    }

    int *server_slots = read_int_array(fp, m);
    int *user_times = read_int_array(fp, n);

    int **proximities = read_int_matrix(fp, n, m);
    int **user_jobs = read_int_matrix(fp, n, m);

    // Compute user preferences: closest proximities first
    int **user_pref = malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        user_pref[i] = malloc(m * sizeof(int));

        int temp[m];
        for (int j = 0; j < m; j++) temp[j] = j;

        for (int j = 0; j < m-1; j++) {
            for (int k = j+1; k < m; k++) {
                int pj = proximities[i][temp[j]];
                int pk = proximities[i][temp[k]];
                if (pk < pj ) {
                    int tmp = temp[j]; temp[j] = temp[k]; temp[k] = tmp;
                }
            }
        }
        for (int j = 0; j < m; j++)
            user_pref[i][j] = temp[j];
    }

    // Compute server preferences
    int **server_pref = malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) {
        server_pref[i] = malloc(n * sizeof(int));
        int temp[n];
        int score[n];
        for (int j = 0; j < n; j++) {
            score[j] = 30 * user_jobs[j][i] + 70 * proximities[j][i];
            temp[j] = j;
        }
        
        for (int j = 0; j < n-1; j++) {
            int min_idx = j;
            for (int k = j+1; k < n; k++) {
                if (score[k] < score[min_idx] || (score[k] == score[min_idx] && user_times[k] < user_times[min_idx]))
                    min_idx = k;
            }
            int tmp = score[j]; score[j] = score[min_idx]; score[min_idx] = tmp;
            int tmp2 = temp[j]; temp[j] = temp[min_idx]; temp[min_idx] = tmp2;
        }
        for (int j = 0; j < n; j++)
            server_pref[i][j] = temp[j];
    }

    Matching *match = create_matching(m, n, server_pref, user_pref, server_slots);

    fclose(fp);
    return match;
}

// Get index of value in array
int index_of(int *arr, int len, int val) {
    for (int i = 0; i < len; i++)
        if (arr[i] == val) return i;
    return -1;
}

// Gale-Shapley
Matching *stable_gale_shapley(Matching *problem) {
    //TODO implement
    return problem;
}

int is_stable(Matching *match) {
   //TODO Implement
    return 1;
}

void test_run(Matching *problem, int test_gs) {
    if (test_gs) {
        stable_gale_shapley(problem);
        printf("Gale-Shapley Matching:\n");
        print_matching(problem);
        printf("\n");
        int stable = is_stable(problem);
        printf("Stable? %s\n\n", stable ? "true" : "false");
    }
}


int main(int argc, char *argv[]) {
    char *filename;
    int test_gs;
    parse_args(argc, argv, &filename, &test_gs);

    Matching *problem = parse_matching_problem(filename);
    if (!problem) return 1;

    test_run(problem, test_gs);
    free_matching(problem);
    return 0;
}
