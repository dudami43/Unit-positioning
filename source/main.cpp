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
    for(int i = 1800; i < 2500; i+=10)
    {
        std::string file = "instances/vicosa15.txt";
        //std::cout << file << std::endl;
        read_map(weight_matrix, imp_matrix, flags_matrix, distances, n_units, file);
        //std::cout << "Li o mapa\n";
        imp_vector = get_importance(weight_matrix, imp_matrix);
        n_units = i;
        //std::cout << "Peguei as importancias\n";
        std::cout << n_units << " unidades: " << std::endl; 
        //std::cout << genetic_algorithm(distances, imp_vector, n_units, 10, 10, 0.05, 0.5, false) << std::endl;
        std::vector<int> a = greedy (n_units, distances, imp_vector, "default", 0.06);
        std::cout << "Greedy: " << objectiveFunction(distances, imp_vector, a, true) << std::endl;
        //std::cout << "Scatter search: " << scatterSearch(30, 10, n_units, 0.05, distances, imp_vector, 9, 6, 10, false) << std::endl;
    }
    
}
