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
    read_map(weight_matrix, imp_matrix, flags_matrix);
    
    floyd_warshall(weight_matrix, weight_matrix.size());
   
    std::vector<int> solution;

    for(int i = 0; i < 10; i++)
    {
        solution.push_back(i);
    }
    std::cout << "Criei a solução\n";
    //std::cout << "Com as importâncias\n" << objectiveFunction(weight_matrix, imp_matrix, solution, true) << std::endl;
    std::cout << "Sem as importâncias\n" << objectiveFunction(weight_matrix, imp_matrix, solution, false) << std::endl;

    std::vector<int> solution2;
    greedySolution(10, weight_matrix, imp_matrix, solution2);
    std::cout << "Sem as importâncias2\n" << objectiveFunction(weight_matrix, imp_matrix, solution2, false) << std::endl;

}
