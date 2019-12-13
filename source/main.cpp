#include <bits/stdc++.h>
#include "parser.h"
#include "functions.h"

int main(int argc, char **argv)
{
    int n_units;
    srand (time(NULL));
    std::vector<std::vector<int>> weight_matrix;
    std::vector<std::vector<int>> imp_matrix;
    std::vector<std::vector<int>> flags_matrix;
    std::vector<std::vector<int>> distances;
    std::vector<int> imp_vector;

    std::string file = "instances/vicosa15.txt";

    read_map(weight_matrix, imp_matrix, flags_matrix, distances, n_units, file);
    imp_vector = get_importance(weight_matrix, imp_matrix);
    
    std::cout << n_units << " unidades: " << std::endl; 
    std::cout << "Scatter search: " << scatterSearch(30, 10, n_units, 0.05, distances, imp_vector, 9, 6, 10, false) << std::endl;
    std::cout <<"ILS: " << ILS(distances, imp_vector, n_units, 10, 0.1, 0.2, false) << std::endl;    
    
}
