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
   
    /*std::vector<int> solution_1_10;

    for(int i = 0; i < 10; i++)
    {
        solution_1_10.push_back(i);
    }

    std::cout << "Com as importancias, solucao de 1 a 10: \nValor: " << objectiveFunction(distances, imp_vector, solution_1_10, true) << " --- Solucao: ";
    for (auto x: solution_1_10){
        std::cout << x << " ";
    }std::cout << std::endl;
    
    std::vector<int> solution1 = randomGreedy(10, imp_vector);
    std::cout << "Com as importancias, guloso randomico:\nValor: " << objectiveFunction(distances, imp_vector, solution1, false) << " --- Solucao: ";
    for (auto x: solution1){
        std::cout << x << " ";
    }std::cout << std::endl;

    std::vector<int> solution2 = randomGreedy2(10, weight_matrix, imp_vector);
    std::cout << "Com as importancias, guloso randomico 2:\nValor: " << objectiveFunction(distances, imp_vector, solution2, false) << " --- Solucao: ";
    for (auto x: solution2){
        std::cout << x << " ";
    }std::cout << std::endl;*/

    std::vector<int> solution3 = randomGreedy3(10, weight_matrix);
    std::cout << "Com as importancias, guloso randomico 3:\nValor: " << objectiveFunction(distances, imp_vector, solution3, true) << " --- Solucao: ";
    /*for (auto x: solution3){
        std::cout << x << " ";
    }std::cout << std::endl;*/

    localSearch(distances, imp_vector, solution3, 10, true);
    for (auto x: solution3){
        std::cout << x << " ";
    }std::cout << std::endl;
}
