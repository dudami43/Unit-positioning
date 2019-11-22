#include <bits/stdc++.h>
#include "functions.h"

std::vector<int> get_importance(std::vector<std::vector<int>>& weight_matrix, std::vector<std::vector<int>>& imp_matrix, bool verbose)
{
    std::vector<int> imp_vector;
    for(int i = 0; i < weight_matrix.size(); i++)
    {
        int vertice_importance = 0, count_imp = 0;
        for(int j = 0; j < imp_matrix.size(); j++)
        {
            if(imp_matrix[i][j] != -1)
            {
                vertice_importance += imp_matrix[i][j];
                count_imp++;
            }
        }
        imp_vector.push_back(vertice_importance);
        //imp_vector.push_back(vertice_importance/count_imp);
    }
    return imp_vector;
}

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

int objectiveFunction(std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::vector<int>& solution, bool use_importance, bool verbose)
{
    int totalValue = 0;
    for(int i = 0; i < weight_matrix.size(); i++)
    {
        int closest_unit = closestUnit(i, weight_matrix, solution);
        if(verbose) std::cout << "Unidade mais próxima do vertice " << i << " é " << closest_unit << std::endl;
        if(use_importance)
        {
            int vertice_importance = imp_vector[i];
            if(verbose) std::cout << "Importancia do vertice " << i << " é " << vertice_importance;
            vertice_importance = (vertice_importance == 0) ? 1 : vertice_importance;
            if(verbose) std::cout << " agora é " << vertice_importance << std::endl;
            totalValue += weight_matrix[i][closest_unit]*vertice_importance;
        }
        else
        {
            totalValue += weight_matrix[i][closest_unit];
        }        
    }
    return totalValue;
}

void greedySolution(int numberUnits, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& solution, bool verbose)
{
    int current_point = rand() % weight_matrix.size();
    for(int i = 0; i < numberUnits; i++)
    {
        int farthestDist = 100000;
        int farthestIndex = 0;
        for(int j = 0; j < weight_matrix.size(); j++)
        {
            auto it = std::find(solution.begin(), solution.end(), solution.size());
            if(weight_matrix[j][current_point] > farthestDist && it == solution.end())
            {
                farthestDist = weight_matrix[j][current_point];
                farthestIndex = j;
            }
        }
        solution.push_back(current_point);
        current_point = farthestIndex;
    }
}

std::vector<int> randomGreedy(int n_units, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, float size_RCL, bool verbose)
{
    /**
     *  Guloso randomico:
     *  Para cada policial escolhe uma localizacao aleatoria dentre as 10%
     *  com maior importancia
     */

    std::vector<int> solution;

    int real_size_RCL = imp_vector.size()*size_RCL;
    if(real_size_RCL <= n_units*2) 
    {
        real_size_RCL = (int) n_units/size_RCL;
        real_size_RCL = std::max(real_size_RCL, (int) imp_vector.size());
    }
    std::vector<int> sorted_imp_idx;
    for (int i = 0; i < imp_vector.size(); i++)
        sorted_imp_idx.push_back(i);

    // Ordena decrescentemente o vetor de indices do vetor de importancia
    // atraves da importancia daquele indice
    std::sort(sorted_imp_idx.begin(), sorted_imp_idx.end(),
            [&](int i, int j){return imp_vector[i] > imp_vector[j];});
    
    std::vector<int> choosed_locations;
    for (int i = 0; i < real_size_RCL; i++)
    {
        int location = rand() % real_size_RCL;
        while(std::find(choosed_locations.begin(), choosed_locations.end(), location) != choosed_locations.end())
            location = rand() % real_size_RCL;
        
        choosed_locations.push_back(location);
        solution.push_back(location);
    }   

    return solution; 
}

std::vector<int> randomGreedy2(int n_units, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, float size_RCL, bool verbose)
{
    /**
     *  Guloso randomico 2:
     *  Para cada policial escolhe uma localizacao aleatoria dentre as 10%
     *  com um maior numero de cidades adjacentes com grandes importancias
     */
    
    std::vector<int> solution;

    return solution; 
}

std::vector<int> randomGreedy3(int n_units, std::vector<std::vector<int>>& weight_matrix, float size_RCL, bool verbose)
{
    /**
     *  Guloso randomico 2:
     *  Para cada policial escolhe uma localizacao aleatoria dentre as 10%
     *  com um maior numero de cidades adjacentes (independente de suas importancias)
     */
    
    std::vector<int> solution;

    return solution; 
}