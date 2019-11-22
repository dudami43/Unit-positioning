#include <bits/stdc++.h>
#include "functions.h"

std::vector<int> get_importance(std::vector<std::vector<int>>& weight_matrix, std::vector<std::vector<int>>& imp_matrix, bool set_all_one, bool verbose)
{
    std::vector<int> imp_vector;
    if(set_all_one){
        for(int i = 0; i < weight_matrix.size(); i++)
            imp_vector.push_back(1);
    }else{
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
            auto it = std::find(solution.begin(), solution.end(), j);
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

std::vector<int> randomGreedy(int n_units, std::vector<int>& imp_vector, float size_RCL, bool verbose)
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
    for (int i = 0; i < n_units; i++)
    {
        int location = rand() % real_size_RCL;
        while(std::find(choosed_locations.begin(), choosed_locations.end(), location) != choosed_locations.end())
            location = rand() % real_size_RCL;
        
        choosed_locations.push_back(location);
        solution.push_back(location);
    }   

    return solution; 
}

int adj_imp_sum(std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, int position)
{
    int adj_sum = 0;
    for (int i = 0; i < weight_matrix[position].size(); i++)
    {
        if(weight_matrix[position][i] != 0)
            adj_sum += imp_vector[i];
    }
        
    return adj_sum;
}

std::vector<int> randomGreedy2(int n_units, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, float size_RCL, bool verbose)
{
    /**
     *  Guloso randomico 2:
     *  Para cada policial escolhe uma localizacao aleatoria dentre as 10%
     *  com uma maior soma de importancia das cidades adjacentes
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
            [&](int i, int j){return adj_imp_sum(weight_matrix, imp_vector, i) > adj_imp_sum(weight_matrix, imp_vector, j);});

    std::vector<int> choosed_locations;
    for (int i = 0; i < n_units; i++)
    {
        int location = rand() % real_size_RCL;
        while(std::find(choosed_locations.begin(), choosed_locations.end(), location) != choosed_locations.end())
            location = rand() % real_size_RCL;
        
        choosed_locations.push_back(location);
        solution.push_back(location);
    }   

    return solution; 
}

int count_non_zero(std::vector<std::vector<int>>& weight_matrix, int position)
{
    int non_zero = 0;
    for (int i = 0; i < weight_matrix[position].size(); i++)
        if(weight_matrix[position][i] != 0) non_zero++;
    return non_zero;
}

std::vector<int> randomGreedy3(int n_units, std::vector<std::vector<int>>& weight_matrix, float size_RCL, bool verbose)
{
    /**
     *  Guloso randomico 2:
     *  Para cada policial escolhe uma localizacao aleatoria dentre as 10%
     *  com um maior numero de cidades adjacentes (independente de suas importancias)
     */
    
    std::vector<int> solution;

    int real_size_RCL = weight_matrix.size()*size_RCL;
    if(real_size_RCL <= n_units*2) 
    {
        real_size_RCL = (int) n_units/size_RCL;
        real_size_RCL = std::max(real_size_RCL, (int) weight_matrix.size());
    }
    std::vector<int> sorted_imp_idx;
    for (int i = 0; i < weight_matrix.size(); i++)
        sorted_imp_idx.push_back(i);

    // Ordena decrescentemente o vetor de indices do vetor de importancia
    // atraves da importancia daquele indice
    std::sort(sorted_imp_idx.begin(), sorted_imp_idx.end(),
            [&](int i, int j){return count_non_zero(weight_matrix, i) > count_non_zero(weight_matrix, j);});
    
    std::vector<int> choosed_locations;
    for (int i = 0; i < n_units; i++)
    {
        int location = rand() % real_size_RCL;
        while(std::find(choosed_locations.begin(), choosed_locations.end(), location) != choosed_locations.end())
            location = rand() % real_size_RCL;
        
        choosed_locations.push_back(location);
        solution.push_back(location);
    }   

    return solution;  
}

/*
 * Vizinhanças 
 */
void changePositions(std::vector<int>& solution, int unit, int position)
{
    solution[unit] = position;
}

void localSearch(std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::vector<int>& solution, int numberUnits, bool verbose)
{
    std::vector<int> previous_solution = solution;
    std::vector<int> current_solution = solution;

    int imax = 100;
    int current_value = objectiveFunction(weight_matrix, imp_vector, current_solution, true);
    int best_value = current_value;
    bool foundit = false;
    for(int iter = 0; iter < imax; iter++)
    {
        for(int i = 0; i < numberUnits; i++)
        {
            for(int j = 0; j < weight_matrix.size(); j++)
            {
                previous_solution = current_solution;
                auto it = std::find(current_solution.begin(), current_solution.end(), j);

                if(it != current_solution.end())
                {
                    continue;
                }

                changePositions(current_solution, i, j);
                current_value = objectiveFunction(weight_matrix, imp_vector, current_solution, true);
            
                if(current_value < best_value)
                {
                    if(verbose) std::cout << "Coloquei a unidade " << i << " em " << j << std::endl;
                    if(verbose) std::cout << best_value << " " << current_value << std::endl;
                    best_value = current_value;
                    foundit = true;
                    break;
                }
                else
                {
                    current_solution = previous_solution;
                    foundit = false;
                }
            }
            if(foundit) break;
        }
    }
    solution = current_solution;
}