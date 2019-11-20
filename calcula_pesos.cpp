#include <bits/stdc++.h>
#include "parser_wout_dist.h"

int main()
{
    std::vector<std::vector<int>> weight_matrix;
    std::vector<std::vector<int>> imp_matrix;
    std::vector<std::vector<int>> flags_matrix;
    read_map(weight_matrix, imp_matrix, flags_matrix);
    
    std::vector<std::vector<int>> distances(weight_matrix);
    floyd_warshall(distances, distances.size());
   
    std::ofstream output;
    output.open ("data/distancias_minimas.txt", std::ios::out | std::ios::trunc);
    
    output << distances.size() << "\n";
    for (int i = 0; i < distances.size(); i++)
    {
        output << distances[i][0];
        for (int j = 1; j < distances[i].size(); j++)
        {
            output << " " << distances[i][j];
        }
        output << '\n';
    }

    output.close();
}
