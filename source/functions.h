std::vector<int> get_importance(std::vector<std::vector<int>>& weight_matrix, std::vector<std::vector<int>>& imp_matrix, bool set_all_one = false, bool verbose = false);

int objectiveFunction(std::vector<std::vector<int>>& distances, std::vector<int>& imp_vector, std::vector<int>& solution, bool use_importance, bool verbose = false);
int closestUnit(int point, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& solution, bool verbose = false);

int adj_imp_sum(std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, int position);
int count_non_zero(std::vector<std::vector<int>>& weight_matrix, int position);

std::vector<int> greedy(int n_units, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::string method, float size_RCL = 0.1, bool verbose = false);
void greedySolution(int numberUnits, std::vector<std::vector<int>>& weight_matrix, std::vector<std::vector<int>>& imp_matrix, std::vector<int>& solution, bool verbose = false);


void changePositions(std::vector<int>& solution, int unit, int position);
void localSearch(std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::vector<int>& solution, int numberUnits, bool verbose = false);

void initialPopulation(int popSize, int n_units, float size_RCL, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::vector<std::vector<int>>& population);
int scatterSearch(int popSize, int n_units, float size_RCL, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, int gRS = 5, int rRS = 5, int imax = 10, bool verbose = false);

// GA
std::pair<std::vector<int>, int> evaluatePopulation(std::vector<std::vector<int>>& distances, std::vector<int>& imp_vector, std::vector<std::vector<int>> population, bool verbose = false);
std::vector<std::vector<int>> selection(std::vector<std::vector<int>> population, std::vector<int> evaluate_p, int n_selected, bool verbose = false);
std::pair<std::vector<int>, std::vector<int>> crossover(std::vector<int> individual_1, std::vector<int> individual_2, bool verbose = false);
void mutation(std::vector<std::vector<int>>& population, float chance, int n_places, bool verbose = false);
std::vector<std::vector<int>> reproduction(std::vector<std::vector<int>> parents, bool verbose = false);
void replace(std::vector<std::vector<int>>& population, std::vector<std::vector<int>>& new_generation, bool verbose = false);
int genetic_algorithm(std::vector<std::vector<int>>& distances, std::vector<int>& imp_vector, int n_units = 20, int pop_size = 100, int imax = 10, float size_RCL = 0.1, bool verbose = false);