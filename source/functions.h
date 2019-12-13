std::vector<int> get_importance(std::vector<std::vector<int>>& weight_matrix, std::vector<std::vector<int>>& imp_matrix, bool set_all_one = false, bool verbose = false);

int objectiveFunction(std::vector<std::vector<int>>& distances, std::vector<int>& imp_vector, std::vector<int>& solution, bool use_importance = true, bool verbose = false);
int closestUnit(int point, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& solution, bool verbose = false);

int adj_imp_sum(std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, int position);
int count_non_zero(std::vector<std::vector<int>>& weight_matrix, int position);

std::vector<int> greedy(int n_units, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::string method, float size_RCL = 0.1, bool verbose = false);

void changePositions(std::vector<int>& solution, int unit, int position);
void localSearch(std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::vector<int>& solution, int numberUnits, bool verbose = false);

void initialPopulation(int popSize, int n_units, float size_RCL, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::vector<std::vector<int>>& population);
int scatterSearch(int popSize, int n_subsets, int n_units, float size_RCL, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, int gRS = 5, int rRS = 5, int imax = 10, bool verbose = false);

// ILS
void disturbe(std::vector<int> solution, double disturbe_size, int n_units, int n_places, bool verbose = false);
int ILS(std::vector<std::vector<int>>& distances, std::vector<int>& imp_vector, int n_units, int imax, double disturbe_size, double accept_chance, bool verbose = false);
