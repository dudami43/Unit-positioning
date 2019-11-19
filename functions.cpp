#include <bits/stdc++.h>
#include "functions.h"

int closestUnit(int point, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& solution, bool verbose)
{
    int minDist = 100000000;
    int minIndex = 0;
    for(int i = 0; i < solution.size(); i++)
    {
        if(solution[i] != point)
        {
            if(verbose) std::cout << i << " " << weight_matrix[solution[i]][point] << " " << minDist << std::endl;
            if(weight_matrix[solution[i]][point] < minDist)
            {
                minDist = weight_matrix[solution[i]][point];
                minIndex = i;
                if(verbose) std::cout << "Entrei " << minDist << " " << minIndex << std::endl;
            }
        }
    }
    return minIndex;
}

int objectiveFunction(std::vector<std::vector<int>>& weight_matrix, std::vector<std::vector<int>>& imp_matrix, std::vector<int>& solution, bool use_importance, bool verbose)
{
    int totalValue = 0;
    for(int i = 0; i < weight_matrix.size(); i++)
    {
        int closest_unit = closestUnit(i, weight_matrix, solution);
        if(verbose) std::cout << "Unidade mais próxima do vertice " << i << " é " << closest_unit << std::endl;
        if(use_importance)
        {
            int vertice_importance = 0;
            for(int j = 0; j < imp_matrix.size(); j++)
            {
                if(imp_matrix[i][j] != -1)
                {
                    vertice_importance += imp_matrix[i][j];
                }
            }
            if(verbose) std::cout << "Importancia do vertice " << i << " é " << vertice_importance;
            vertice_importance = (vertice_importance==0) ? 1 : vertice_importance;
            if(verbose) std::cout << " agora é " << vertice_importance << std::endl;
            totalValue += weight_matrix[i][closest_unit]/vertice_importance;
        }
        else
        {
            totalValue += weight_matrix[i][closest_unit];
        }        
    }
    return totalValue;
}