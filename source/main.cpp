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
    /*for(auto x: distances)
    {
        for(auto y: x)
        {
            std::cout << y << " ";
        }
        std::cout << "\n";
    }*/
    std::cout << "READ IT\n";
    imp_vector = get_importance(weight_matrix, imp_matrix);
    std::cout << "GOT IT\n";
    //std::vector<int> solution3;
    //greedySolution(n_units, distances, imp_matrix, solution3, false);
    //std::cout << "GREEDY\n";
    //std::cout << objectiveFunction(distances, imp_vector, solution3, true) << " ";    
    std::vector<int> solution1 = greedy(n_units, distances, imp_vector, "default");
    std::cout << "GREEDY\n";
    std::cout << objectiveFunction(distances, imp_vector, solution1, true, false) << " ";    
    //std::cout << scatterSearch(30, n_units, 0.1, distances, imp_vector, 5, 5, 10, true) << std::endl;
}
