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
    read_map(weight_matrix, imp_matrix, flags_matrix);
    /*
    auto start = std::chrono::high_resolution_clock::now(); 
    shortest_path(weight_matrix, weight_matrix.size());
    auto end = std::chrono::high_resolution_clock::now();
    double time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
    time_taken *= 1e-9;
    std::cout << "DIJKSTRA " << std::fixed  << time_taken << std::setprecision(9) << std::endl;

    start = std::chrono::high_resolution_clock::now();*/ 
    floyd_warshall(weight_matrix, weight_matrix.size());
    /*end = std::chrono::high_resolution_clock::now();
    time_taken = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count(); 
    time_taken *= 1e-9;
    std::cout << "FLOYDWARSHALL " << std::fixed  << time_taken << std::setprecision(9) << std::endl;
    
    */
    for(auto y: weight_matrix)
    {
        for(auto x: y)
        {
            std::cout << x << " ";
        }
        std::cout << std::endl;
    }
    std::cout << " A unidade na posição 1 consegue cobrir o ponto 5 em Tmax? " << coversPoint(1, 5, TMAX, SPEED, weight_matrix) << std::endl;
    /*
     * Uma unidade é alocada para um vértice
     * Uma aresta é coberta por uma unidade em um tempo 
     * Colocar unidades em vértices
     * Cada unidade cobre um raio R
     * Solução = Vetor de posição das unidades
     * Objetivo: maximizar Z = somatório de 1 até |E| (lucro de cobrir uma aresta * a aresta é coberta por alguma unidade em Tmax)
     */
}
