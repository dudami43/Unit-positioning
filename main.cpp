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

    read_map(weight_matrix, imp_matrix, flags_matrix, distances);
    imp_vector = get_importance(weight_matrix, imp_matrix);

    std::vector<int> solution3;

    std::vector<int> solution1 = greedy(10, weight_matrix, imp_vector, "default");
    std::cout << objectiveFunction(distances, imp_vector, solution1, true) << " ";    
    std::cout << scatterSearch(30, 10, 0.1, distances, imp_vector) << std::endl;
}
