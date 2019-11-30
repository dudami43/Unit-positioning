#include <bits/stdc++.h>
#include "parser.h"
#include "functions.h"

int main()
{
    srand (time(NULL));
    std::vector<std::vector<int>> weight_matrix;
    std::vector<std::vector<int>> imp_matrix;
    std::vector<std::vector<int>> flags_matrix;
    std::vector<std::vector<int>> distances;
    std::vector<int> imp_vector;

    int n_units;

    read_map(weight_matrix, imp_matrix, flags_matrix, distances, n_units, "instances/vicosa49.txt");
    imp_vector = get_importance(weight_matrix, imp_matrix);

    std::vector<int> solution3;

    std::vector<int> solution1 = greedy(n_units, weight_matrix, imp_vector, "default");
    std::cout << "Guloso: " << objectiveFunction(distances, imp_vector, solution1, true) << std::endl;
    std::cout << genetic_algorithm(distances, imp_vector, n_units, 150, 150, 0.2, false) << std::endl;
}
