#include <bits/stdc++.h>
#include "parser.h"
#include "functions.h"

int main(int argc, char **argv)
{
    
    double rng_seed;

    //Scatter Search
    int pop_size;
    float size_RCL;
    int gRS;
    int rRS;
    int imax;
    int n_subsets;
    float dist, acc;

    for(int i = 2; i < argc; i += 2) {
        if(strcmp(argv[i], "--seed") == 0) {
            sscanf(argv[i+1],"%lf", &rng_seed);
        }
        else if(strcmp(argv[i], "--POP_SIZE") == 0) {
            sscanf(argv[i+1],"%d", &pop_size);
        }
        else if(strcmp(argv[i], "--SIZE_RCL") == 0) {
            sscanf(argv[i+1],"%lf", &size_RCL);
        }
        else if(strcmp(argv[i], "--GRS") == 0) {
            sscanf(argv[i+1],"%d", &gRS);
        }
        else if(strcmp(argv[i], "--RRS") == 0) {
            sscanf(argv[i+1],"%d", &rRS);
        }
        else if(strcmp(argv[i], "--IMAX") == 0) {
            sscanf(argv[i+1],"%d", &imax);
        }
        else if(strcmp(argv[i], "--NSUBSETS") == 0) {
            sscanf(argv[i+1],"%d", &n_subsets);
        }
        else if(strcmp(argv[i], "--DIST") == 0) {
            sscanf(argv[i+1],"%lf", &dist);
        }
        else if(strcmp(argv[i], "--ACC") == 0) {
            sscanf(argv[i+1],"%lf", &acc);
        }
    }

    srand (rng_seed);

    int n_units;

    std::vector<std::vector<int>> weight_matrix;
    std::vector<std::vector<int>> imp_matrix;
    std::vector<std::vector<int>> flags_matrix;
    std::vector<std::vector<int>> distances;
    std::vector<int> imp_vector;

    read_map(weight_matrix, imp_matrix, flags_matrix, distances, n_units, argv[1]);
    imp_vector = get_importance(weight_matrix, imp_matrix);
    std::cout << ILS(distances, imp_vector, n_units, 10, dist, acc) << std::endl;
    //std::cout << scatterSearch(pop_size, n_subsets, n_units, size_RCL, distances, imp_vector, gRS, rRS, imax, false) << std::endl;
}
