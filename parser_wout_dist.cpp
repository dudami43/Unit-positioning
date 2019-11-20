#include <bits/stdc++.h>
#include "parser_wout_dist.h"

std::vector<int> removeDupWord(std::string& str) 
{ 
    std::string word = ""; 
    std::vector<int> numbers;
    for (int i = 0; i <= str.size(); i++) 
    {
        char x = str[i];
        if (x == ' ' || x == '\n' || x == '\0') 
        { 
            numbers.push_back(std::stoi(word));
            word = ""; 
        } 
        else
        { 
            word = word + x;
        } 
    }
    /*if (word.size() > 0)
    {
        numbers.push_back(std::stoi(word));
    }*/
    return numbers;
} 

void read_map(std::vector<std::vector<int>>& weight_matrix, std::vector<std::vector<int>>& imp_matrix, std::vector<std::vector<int>>& flags_matrix)
{
    std::ifstream file;
    std::string line;
    file.open("data/vicosa.txt");
    int V, A, WW, F;
    //Flags: 1 passa qualquer coisa 0 nao passa carro
    try
    {
        if (file.is_open())
        {
            getline(file,line);
            V = std::stoi(line);

            weight_matrix.resize(V, std::vector<int>(V, 10000000));
            imp_matrix.resize(V, std::vector<int>(V, -1));
            flags_matrix.resize(V, std::vector<int>(V, 1));

            getline(file,line);
            A = std::stoi(line);

            for(int i = 0; i < A; i++)
            {
                getline(file,line);

                std::vector<int> aux = removeDupWord(line);

                weight_matrix[aux[0] - 1][aux[1] - 1] = aux[2];
                imp_matrix[aux[0] - 1][aux[1] - 1] = aux[3];
                
                weight_matrix[aux[1] - 1][aux[0] - 1] = aux[2];
                imp_matrix[aux[1] - 1][aux[0] - 1] = aux[3];

            }
            
            getline(file,line);
            WW = std::stoi(line);

            for(int i = 0; i < WW; i++)
            {
                getline(file,line);

                std::vector<int> aux = removeDupWord(line);

                weight_matrix[aux[1] - 1][aux[0] - 1] = weight_matrix[aux[1] - 1][aux[0] - 1] * 1.5;
            }

            getline(file,line);
            F = std::stoi(line);

            for(int i = 0; i < F; i++)
            {
                getline(file,line);
                
                std::vector<int> aux = removeDupWord(line);

                flags_matrix[aux[0] - 1][aux[1] - 1] = 0;
                flags_matrix[aux[1] - 1][aux[0] - 1] = 0;

            }
        }
    }
    catch(char const* param)
    {
        std::cout << param << std::endl;
    }
}

void dijkstra(std::vector<std::vector<int>>& weights, int source)
{
    std::vector<int> dist(weights.size(), 100000000);
    std::vector<int> previous(weights.size(), -1);

    dist[source] = 0;
    using pii = std::pair<int, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> Q;
    Q.push({0, source});
    while (!Q.empty()) {
        int u = Q.top().second;
        int d_u = Q.top().first;
        Q.pop();
        if (d_u != dist[u])
            continue;

        for(int i = 0; i < weights.size(); i++)
        {
            //std::cout << i << " " << weights.size() << std::endl;
            int alt = dist[u] + weights[u][i];
            if(alt < dist[i])
            {
                dist[i] = alt;
                previous[i] = u;
                Q.push({dist[i], i});
            }
        }
    }
    for(int i = 0; i < weights.size(); i++)
    {
        weights[source][i] = dist[i];
    }
}

void shortest_path(std::vector<std::vector<int>>& weights, int n)
{
    for(int i = 0; i < weights.size(); i++)
    {
        dijkstra(weights, i);
    }
}

void floyd_warshall(std::vector<std::vector<int>>& dist, int n)
{
    for (int k = 0; k < n; k++)  
    {
        for (int i = 0; i < n; i++)  
        {
            for (int j = 0; j < n; j++)  
            {
                if(i == j) dist[i][j] = 0;
                else if (dist[i][k] + dist[k][j] < dist[i][j])  dist[i][j] = dist[i][k] + dist[k][j];  
            }  
        }  
    }
}

