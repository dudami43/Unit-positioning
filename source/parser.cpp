#include <bits/stdc++.h>
#include "parser.h"

void read_map(std::vector<std::vector<int>>& weight_matrix, std::vector<std::vector<int>>& imp_matrix, std::vector<std::vector<int>>& flags_matrix, std::vector<std::vector<int>>& distances, int& n_units, std::string namefile)
{
    weight_matrix.clear();
    imp_matrix.clear();
    flags_matrix.clear();
    distances.clear();

    // Faz o parser das ruas
    std::ifstream file, file_floyd;
    std::string line;
    file.open(namefile);
    try
    {
        if (file.is_open())
        {
            
            getline(file, line);
            n_units = stoi(line);

            getline(file, line);
            int n_vertex = stoi(line);
            
            std::vector<int> zero_matrix;
            zero_matrix.resize(n_vertex, 0);
            
            weight_matrix.resize(n_vertex, zero_matrix);
            imp_matrix.resize(n_vertex, zero_matrix);
            flags_matrix.resize(n_vertex, zero_matrix);
            distances.resize(n_vertex, zero_matrix);
            
            getline(file, line);
            int n_edges = stoi(line);
            
            for (int i = 0; i < n_edges; i++)
            {
                int initial_vertex, final_vertex, distance, importance;

                getline(file, line);
                std::stringstream ss(line);

                ss >> initial_vertex >> final_vertex >> distance >> importance;

                weight_matrix[initial_vertex - 1][final_vertex - 1] = distance;
                weight_matrix[final_vertex - 1][initial_vertex - 1] = distance;

                imp_matrix[initial_vertex - 1][final_vertex - 1] = importance;
                imp_matrix[final_vertex - 1][initial_vertex - 1] = importance;
            }

            getline(file, line);
            int n_direction = stoi(line);

            for (int i = 0; i < n_direction; i++)
            {
                int initial_vertex, final_vertex;

                getline(file, line);
                std::stringstream ss(line);

                ss >> initial_vertex >> final_vertex;

                weight_matrix[initial_vertex - 1][final_vertex - 1] *= 1.5;
            }

            getline(file, line);
            int n_special_edges = stoi(line);

            for (int i = 0; i < n_special_edges; i++)
            {
                int initial_vertex, final_vertex;

                getline(file, line);
                std::stringstream ss(line);

                ss >> initial_vertex >> final_vertex;

                weight_matrix[initial_vertex - 1][final_vertex - 1] *= 2;
            }
        }
    }
    catch(char const* param)
    {
        std::cout << param << std::endl;
    }
    file.close();

    // Faz o parse da matriz de distancias minimas
    file_floyd.open("data/distancias_minimas.txt");
    try
    {
        if (file_floyd.is_open())
        {
            getline(file_floyd, line);
            int n_vertex = stoi(line);

            for (int i = 0; i < n_vertex; i++)
            {
                getline(file_floyd, line);
                std::stringstream ss(line);

                for (int j = 0; j < n_vertex; j++)
                {
                    ss >> distances[i][j];
                }
            }
        }
    }
    catch(char const* param)
    {
        std::cout << param << std::endl;
    }
    file_floyd.close();
}