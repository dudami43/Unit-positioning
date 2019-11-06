#include <bits/stdc++.h>
#include "parser.h"

// Para compilar com g++11: g++ -std=c++11 main.cpp parser.cpp functions.cpp

int main(int argc, char *argv[])
{
    // Inicializa a funcao randomica
    srand (time(NULL));


    // Abre o arquivo indicado
    std::ifstream file;
    std::string filename;
    file.open("data/vicosa.txt");

    // Delete referencia para o nome do arquivo

    if (file.is_open())
    {   try
        {
            
        }
        catch (char const *param)
        {
            std::cout << param << std::endl;
        }
        file.close();
    }
    else
    {
        throw "Unable to open the file";
    }
    return 0;
}