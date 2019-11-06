#include <bits/stdc++.h>

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
            imp_matrix.resize(V, std::vector<int>(V));
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

int main()
{
    std::vector<std::vector<int>> weight_matrix;
    std::vector<std::vector<int>> imp_matrix;
    std::vector<std::vector<int>> flags_matrix;
    read_map(weight_matrix, imp_matrix, flags_matrix);
    for(auto i: flags_matrix)
    {
        for(auto j: i)
        {
            std::cout << j << " ";
        }
        std::cout << std::endl;
    }
}