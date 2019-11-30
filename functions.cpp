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

int objectiveFunction(std::vector<std::vector<int>>& distances, std::vector<int>& imp_vector, std::vector<int>& solution, bool use_importance, bool verbose)
{
    int totalValue = 0;
    for(int i = 0; i < distances.size(); i++)
    {
        int closest_unit = closestUnit(i, distances, solution);
        if(verbose) std::cout << "Unidade mais próxima do vertice " << i << " é " << closest_unit << std::endl;
        if(use_importance)
        {
            int vertice_importance = imp_vector[i];
            if(verbose) std::cout << "Importancia do vertice " << i << " é " << vertice_importance;
            vertice_importance = (vertice_importance == 0) ? 1 : vertice_importance;
            if(verbose) std::cout << " agora é " << vertice_importance << std::endl;
            totalValue += distances[i][closest_unit]*vertice_importance;
        }
        else
        {
            totalValue += distances[i][closest_unit];
        }        
    }
    return totalValue;
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

int count_non_zero(std::vector<std::vector<int>>& weight_matrix, int position)
{
    int non_zero = 0;
    for (int i = 0; i < weight_matrix[position].size(); i++)
        if(weight_matrix[position][i] != 0) non_zero++;
    return non_zero;
}

std::vector<int> greedy(int n_units, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::string method, float size_RCL, bool verbose)
{
    if(method.compare("default") == 0)
    {
        std::vector<int> solution;
            
        std::vector<int> sorted_imp_idx;
        for (int i = 0; i < weight_matrix.size(); i++)
            sorted_imp_idx.push_back(i);

        // Ordena decrescentemente o vetor de indices do vetor de importancia
        // atraves da importancia daquele indice
        std::sort(sorted_imp_idx.begin(), sorted_imp_idx.end(),
                [&](int i, int j){return adj_imp_sum(weight_matrix, imp_vector, i) > adj_imp_sum(weight_matrix, imp_vector, j);});
        
        for (int i = 0; i < n_units; i++)
        {
            solution.push_back(sorted_imp_idx[i]);
        }

        return solution;
    }
    else
    {
        std::vector<int> solution;

        int real_size_RCL = weight_matrix.size()*size_RCL;
        if(real_size_RCL <= n_units*2) 
            real_size_RCL = std::min(n_units*2, (int) weight_matrix.size());
            
        std::vector<int> sorted_imp_idx;
        for (int i = 0; i < weight_matrix.size(); i++)
            sorted_imp_idx.push_back(i);

        if(method.compare("random_1") == 0)
        {
            // Ordena decrescentemente o vetor de indices do vetor de importancia
            // atraves da importancia daquele indice
            std::sort(sorted_imp_idx.begin(), sorted_imp_idx.end(),
                    [&](int i, int j){return imp_vector[i] > imp_vector[j];});
        }
        else if(method.compare("random_2") == 0)
        {
            // Ordena decrescentemente o vetor de indices do vetor de importancia
            // atraves da importancia dos locais adjacentes a ele
            std::sort(sorted_imp_idx.begin(), sorted_imp_idx.end(),
                    [&](int i, int j){return adj_imp_sum(weight_matrix, imp_vector, i) > adj_imp_sum(weight_matrix, imp_vector, j);});
        }
        else if(method.compare("random_3") == 0)
        {
            // Ordena decrescentemente o vetor de indices do vetor de importancia
            // atraves do numero de locais adjacentes
            std::sort(sorted_imp_idx.begin(), sorted_imp_idx.end(),
                    [&](int i, int j){return count_non_zero(weight_matrix, i) > count_non_zero(weight_matrix, j);});
        }else
        {
            throw "Metodo invalido para o guloso.";
        }
        
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

}

void changePositions(std::vector<int>& solution, int unit, int position)
{
    solution[unit] = position;
}

void localSearch(std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::vector<int>& solution, int numberUnits, bool verbose)
{
    std::vector<int> previous_solution = solution;
    std::vector<int> current_solution = solution;

    int imax = 10;
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

void initialPopulation(int popSize, int n_units, float size_RCL, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::vector<std::vector<int>>& population)
{    
    for(int i = 0; i < popSize; i++)
    {
        int method = (rand() % 3) + 1;
        population.push_back(greedy(n_units, weight_matrix, imp_vector, "random_" + std::to_string(method), size_RCL));
    }
}

void goodRefSet(std::vector<std::vector<int>>& population, std::vector<std::vector<int>>& refset, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector)
{
    int worst_value = objectiveFunction(weight_matrix, imp_vector, population[0], true);
    int worst_index = 0;
    int cur_value;
    for(int i = 0; i < 5; i++)
    {
        cur_value = objectiveFunction(weight_matrix, imp_vector, population[i], true);
        if(cur_value > worst_value)
        {
            worst_value = cur_value;
            worst_index = i;
        }
        refset.push_back(population[i]);
    }
    for(int i = 5; i < population.size(); i++)
    {
        cur_value = objectiveFunction(weight_matrix, imp_vector, population[i], true);
        if(cur_value < worst_value)
        {
            refset[worst_index] = population[i];
        }
        worst_value = cur_value;
        for(int j = 0; j < refset.size(); j++)
        {
            cur_value = objectiveFunction(weight_matrix, imp_vector, refset[j], true);
            if(cur_value >= worst_value)
            {
                worst_value = cur_value;
                worst_index = j;
            }
        }
    }
}

void randomRefSet(std::vector<std::vector<int>>& population, std::vector<std::vector<int>>& refset, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector)
{
    for(int i = 0; i < 5; i++)
    {
        int item = rand() % population.size();
        refset.push_back(population[item]);
    }
} 

void genSubsets(std::vector<std::pair<std::vector<int>, std::vector<int>>>& subsets, std::vector<std::vector<int>>& refset)
{
    for(int i = 0; i < refset.size(); i++)
    {
        for(int j = i; j < refset.size(); j++)
        {
            subsets.push_back(std::make_pair(refset[i], refset[j]));
        }
    }
}

std::vector<int> combineSolutions(std::vector<int>& sol1, std::vector<int>& sol2)
{
    std::vector<int> aux;
    for(int i = 0; i < sol1.size()/2; i++)
    {
        aux.push_back(sol1[i]);
    }
    for(int i = sol1.size()/2; i < sol1.size(); i++)
    {
        aux.push_back(sol2[i]);
    }

    for(int i = 0; i < aux.size(); i++)
    {
        if(count(aux.begin(),aux.end(),aux[i]) > 1)
        {
            for(int j = 0; j < sol1.size(); j++)
            {
                auto it = std::find (aux.begin(), aux.end(), sol1[j]);
                if (it == aux.end())
                {
                    aux[i] = sol1[j];
                    break;
                }
            }
        }
    }
    return aux;
}

int scatterSearch(int popSize, int n_units, float size_RCL, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, bool verbose)
{
    int imax = 10;
    std::vector<std::vector<int>> population;
    //Diversification generation method
    initialPopulation(popSize, n_units, size_RCL, weight_matrix, imp_vector, population);
    
    //Improvement method
    for(int i = 0; i < popSize; i++)
    {
        localSearch(weight_matrix, imp_vector, population[i], n_units, false);
    }

    std::vector<std::vector<int>> refset;
    //Reference set update method
    goodRefSet(population, refset, weight_matrix, imp_vector);
    randomRefSet(population, refset, weight_matrix, imp_vector);
    
    if(verbose) std::cout << "Created 1st refset\n";
    for(int iter = 0; iter < imax; iter++)
    {
        std::vector<std::vector<int>> new_population;

        //Subset generation method
        std::vector<std::pair<std::vector<int>, std::vector<int>>> subsets;
        genSubsets(subsets, refset);
        if(verbose) std::cout << "Generated subsets\n";
        //Solution combination method
        int is = 0;
        while(!subsets.empty() && is < 10)
        {
            std::pair<std::vector<int>, std::vector<int>> subset = subsets.back();
            subsets.pop_back();
            std::vector<int> child = combineSolutions(subset.first, subset.second);
            localSearch(weight_matrix, imp_vector, child, n_units, false);
            new_population.push_back(child);
            is++;
        }
        if(verbose) std::cout << "Created new pop\n";
        population.clear();
        population = new_population;
        for(int i = 0; i < refset.size(); i++)
        {
            population.push_back(refset[i]);
        }
        refset.clear();

        goodRefSet(population, refset, weight_matrix, imp_vector);
        randomRefSet(population, refset, weight_matrix, imp_vector);
    }

    int best_value = objectiveFunction(weight_matrix, imp_vector, population[0], true);
    int cur_value;
    for(int i = 0; i < population.size(); i++)
    {
        cur_value = objectiveFunction(weight_matrix, imp_vector, population[i], true);
        if(cur_value < best_value)
        {
            best_value = cur_value;
        }
    }
    return best_value;
}

// GA

std::pair<std::vector<int>, int> evaluatePopulation(std::vector<std::vector<int>>& distance, std::vector<int>& imp_vector, std::vector<std::vector<int>> population, bool verbose)
{
    if (verbose) std::cout << "Inicio da avaliacao" << std::endl;

    // Adquire a avaliacao media da populacao
    std::vector<int> evaluate_p;
    evaluate_p.reserve(population.size());

    int best_solution_idx = 0;
    evaluate_p.push_back(objectiveFunction(distance, imp_vector, population[0], true));
    for (int i = 1; i < population.size(); i++)
    {
        if (verbose) std::cout << i << "/" << population.size() << std::endl;

        int value = objectiveFunction(distance, imp_vector, population[i], true);

        if (verbose) std::cout << "Avaliou o individuo em: " << value << std::endl;

        evaluate_p.push_back(value);

        if (verbose) std::cout << "Adicionou o valor do individuo no vector de valores" << std::endl;

        if (value < evaluate_p[best_solution_idx])
        {
            if (verbose) std::cout << "Setou o individuo como o melhor ate o momento" << value << std::endl;
            best_solution_idx = i;
        }
        if (verbose) std::cout << std::endl;
    }

    if (verbose) std::cout << "Avaliacao finalizada" << std::endl;

    return std::make_pair(evaluate_p, best_solution_idx);
}

std::vector<std::vector<int>> selection(std::vector<std::vector<int>> population, std::vector<int> evaluate_p, int n_selected, bool verbose)
{
    if (verbose) std::cout << "Comecou o metodo SUS" << std::endl;

    // Stochastic Universal Sampling (SUS)
    std::vector<int> roulette_numbers;
    roulette_numbers.reserve(evaluate_p.size());

    int normalized_value = (int) evaluate_p[0]/100000;
    int total_value = normalized_value;
    roulette_numbers.push_back(normalized_value);
    for (int i = 1; i < evaluate_p.size(); i++)
    {
        normalized_value = (int) evaluate_p[i]/100000;
        roulette_numbers.push_back(normalized_value + evaluate_p[i-1]);
        total_value += normalized_value;
    }

    if (verbose) std::cout << "Adquiriu os "<< roulette_numbers.size() << " valores da roleta" << std::endl;

    int pointer_distance = (int) total_value/n_selected;

    int first_pointer = rand() % total_value;
    int actual_pointer = first_pointer;

    std::vector<std::vector<int>> selected;
    std::vector<int> choosed;
    selected.reserve(n_selected);
    choosed.reserve(n_selected);

    for(int i = 0; i < n_selected; i++)
    {
        auto it = std::lower_bound(roulette_numbers.begin(), roulette_numbers.end(), actual_pointer);
        int solution_pos = std::distance(roulette_numbers.begin(), it);

        while(std::find(choosed.begin(), choosed.end(), solution_pos) != choosed.end())
            solution_pos = (solution_pos + 1) % population.size();

        selected.push_back(population[solution_pos]);
        choosed.push_back(solution_pos);
        
        actual_pointer = (actual_pointer + pointer_distance) % population.size();
    }

    if (verbose) std::cout << "Finalizou o metodo SUS com " << selected.size() << " de " << n_selected << " individuos selecionados" << std::endl;

    if (verbose) return selected;
}

std::pair<std::vector<int>, std::vector<int>> crossover(std::vector<int> individual_1, std::vector<int> individual_2, bool verbose)
{
    if (verbose) std::cout << "Comecou o metodo crossover" << std::endl;

    std::vector<int> new_individual_1, new_individual_2;

    new_individual_1.reserve(individual_1.size());
    new_individual_2.reserve(individual_2.size());

    std::vector<int> exclusive_1, exclusive_2;
    int count = 0;
    for (int i = 0; i < individual_1.size(); i++)
    {
        if(find(individual_2.begin(), individual_2.end(), individual_1[i]) != individual_2.end())
        {
            count++;
            new_individual_1.push_back(individual_1[i]);
            new_individual_2.push_back(individual_1[i]);
        }
        else
        {
            exclusive_1.push_back(individual_1[i]);
        }

        if(find(individual_1.begin(), individual_1.end(), individual_2[i]) == individual_1.end())
        {
            exclusive_2.push_back(individual_2[i]);
        }
    }

    std::cout << new_individual_1.size() << " " << new_individual_2.size() << " --- " << count << " --- ";

    for (int i = 0; i < exclusive_1.size()/2; i++)
    {
            new_individual_1.push_back(exclusive_1[i]);
    }

    for (int i = exclusive_1.size()/2; i < exclusive_1.size(); i++)
    {
            new_individual_2.push_back(exclusive_2[i]);
    }

    for (int i = 0; i < exclusive_2.size()/2; i++)
    {
            new_individual_1.push_back(exclusive_2[i]);
    }

    for (int i = exclusive_2.size()/2; i < exclusive_2.size(); i++)
    {
            new_individual_2.push_back(exclusive_2[i]);
    }

    if (verbose) std::cout << "Finalizou o crossover" << std::endl;

    std::cout << new_individual_1.size() << " " << new_individual_2.size() << std::endl;

    return std::make_pair(new_individual_1, new_individual_2);
}

void mutation(std::vector<std::vector<int>>& population, float chance, int n_places, bool verbose)
{
    if (verbose) std::cout << "Comecou a mutacao" << std::endl;

    int total = 1;
    while(chance < 1)
    {
        total *= 10;
        chance *= 10;
    }

    int mutation_result;
    for (int i = 0; i < population.size(); i++)
    {
        mutation_result = rand() % total;
        if (mutation_result < chance)
        {
            int histone = rand() % population[i].size();
            int new_value = rand() % n_places;
            while (find(population[i].begin(), population[i].end(), new_value) != population[i].end()) new_value = rand() % n_places;
            population[i][histone] = new_value;
        }
    }

    if (verbose) std::cout << "Finalizou a mutacao" << std::endl;
}

std::vector<std::vector<int>> reproduction(std::vector<std::vector<int>> parents, int n_places, bool verbose)
{
    if (verbose) std::cout << "Comecou a reproducao" << std::endl;

    std::vector<std::vector<int>> new_population;
    new_population.reserve(parents.size());

    // Crossover
    std::pair<std::vector<int>, std::vector<int>> new_individuals;
    for(int i = 0; i < parents.size()/2; i++)
    {
        new_individuals = crossover(parents[i], parents[(parents.size() - 1) - i], verbose);
        new_population.push_back(new_individuals.first);
        new_population.push_back(new_individuals.second);
    }

    // Mutacao
    mutation(new_population, 0.01, n_places, verbose);

    if (verbose) std::cout << "Terminou a reproducao com " << new_population.size() << " individuos" << std::endl;

    return new_population;
}

void replace(std::vector<std::vector<int>>& population, std::vector<std::vector<int>>& new_generation, bool verbose)
{
    new_generation.reserve(population.size());

    std::vector<int> choosed;
    for (int i = 0; i < population.size(); i++)
    {
        int position = rand() % population.size();
        while(std::find(choosed.begin(), choosed.end(), position) != choosed.end()) position = rand() % population.size();
        choosed.push_back(position);

        population[position] = new_generation[i];
    }
}

int genetic_algorithm(std::vector<std::vector<int>>& distances, std::vector<int>& imp_vector, int n_units, int pop_size, int imax, float size_RCL, bool verbose)
{
    std::vector<std::vector<int>> population;

    // Diversification generation method
    initialPopulation(pop_size, n_units, size_RCL, distances, imp_vector, population);

    if(verbose) std::cout << "Gerou a populacao inicial com tamanho " << population.size() << std::endl;

    // Evaluate population
    std::pair<std::vector<int>, int> evaluate_p = evaluatePopulation(distances, imp_vector, population);

    if(verbose) std::cout << "Avaliou a populacao inicial e o melhor individuo obteve " << evaluate_p.first[evaluate_p.second] << std::endl << std::endl;

    std::vector<int> best_solution = population[evaluate_p.second];
    int best_solution_value = evaluate_p.first[evaluate_p.second];

    for (int i = 0; i < imax; i++)
    {
        std::cout << "iteracao " << i << std::endl;
        // Generate new population
        std::vector<std::vector<int>> new_generation = reproduction(selection(population, evaluate_p.first, population.size()/2, false), imp_vector.size(), false);

        if(verbose) std::cout << "Aplicou selecao e reproducao" << std::endl;

        // Evaluate generation
        std::pair<std::vector<int>, int> evaluate_new_p = evaluatePopulation(distances, imp_vector, population);
        
        if(verbose) std::cout << "A nova geracao teve seu melhor individuo avaliado em " << evaluate_new_p.first[evaluate_new_p.second] << std::endl;

        if (evaluate_new_p.first[evaluate_new_p.second] < best_solution_value)
        {
            best_solution = population[evaluate_new_p.second];
            best_solution_value = evaluate_new_p.first[evaluate_new_p.second];
        }

        replace(population, new_generation, verbose);
        
        if(verbose) std::cout << "Nova populacao gerada com " << population.size() << " individuos" << std::endl;

        // Evaluate new population
        std::pair<std::vector<int>, int> evaluate_p = evaluatePopulation(distances, imp_vector, population, true);
        if(verbose) std::cout << "A nova populacao teve seu melhor individuo avaliado em " << evaluate_p.first[evaluate_p.second] << std::endl << std::endl;
    }

    return best_solution_value;
}