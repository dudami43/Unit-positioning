#include <bits/stdc++.h>
#include "parser.h"
#include "functions.h"

#define TMAX 0.3
#define SPEED 60
#define UNITS 15

int main()
{
    std::vector<std::vector<int>> weight_matrix;
    std::vector<std::vector<int>> imp_matrix;
    std::vector<std::vector<int>> flags_matrix;
    std::vector<std::vector<int>> distances;
    read_map(weight_matrix, imp_matrix, flags_matrix, distances);
   
    std::vector<int> solution;

    for(int i = 0; i < 10; i++)
    {
        solution.push_back(i);
    }
    std::cout << "Criei a solução\n";
    std::cout << "Com as importâncias\n" << objectiveFunction(weight_matrix, imp_matrix, solution, true) << std::endl;
    //std::cout << "Sem as importâncias\n" << objectiveFunction(weight_matrix, imp_matrix, solution, false) << std::endl;
}
