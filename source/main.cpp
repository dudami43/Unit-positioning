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
    for(int i = 30; i < 100; i++)
    {
        std::string file = "instances/vicosa" + std::to_string(i) + ".txt";
        std::cout << file << std::endl;
        read_map(weight_matrix, imp_matrix, flags_matrix, distances, n_units, file);
        std::cout << "Li o mapa\n";
        imp_vector = get_importance(weight_matrix, imp_matrix);
        std::cout << "Peguei as importancias\n";
        std::cout << "Resultado scatter search de " << n_units << " unidades: " << scatterSearch(30, n_units, 0.05, distances, imp_vector, 9, 6, 10, false) << std::endl;
    }
    
}
