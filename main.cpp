#include <bits/stdc++.h>
#include "parser.h"
#include "functions.h"

#define TMAX 0.3
#define SPEED 60
#define UNITS 15

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
   
    std::vector<int> solution;

    for(int i = 0; i < 10; i++)
    {
        solution.push_back(i);
    }

    std::cout << "Com as importâncias, solucao de 1 a 10: \n" << objectiveFunction(distances, imp_vector, solution, true) << std::endl;
    
    std::vector<int> solution3 = randomGreedy(10, weight_matrix, imp_vector);
    std::cout << "Com as importâncias, guloso randomico:\n" << objectiveFunction(distances, imp_vector, solution3, false) << std::endl;

}
