std::vector<int> get_importance(std::vector<std::vector<int>>& weight_matrix, std::vector<std::vector<int>>& imp_matrix, bool set_all_one = false, bool verbose = false);

int objectiveFunction(std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::vector<int>& solution, bool use_importance, bool verbose = false);
int closestUnit(int point, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& solution, bool verbose = false);

void greedySolution(int numberUnits, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& solution, bool verbose = false);

std::vector<int> randomGreedy(int n_units, std::vector<int>& imp_vector, float size_RCL = 0.1, bool verbose = false);

int adj_imp_sum(std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, int position);
std::vector<int> randomGreedy2(int n_units, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, float size_RCL = 0.1, bool verbose = false);

int count_non_zero(std::vector<std::vector<int>>& weight_matrix, int position);
std::vector<int> randomGreedy3(int n_units, std::vector<std::vector<int>>& weight_matrix, float size_RCL = 0.1, bool verbose = false);

void changePositions(std::vector<int>& solution, int unit, int position);
void localSearch(std::vector<std::vector<int>>& weight_matrix, std::vector<int>& imp_vector, std::vector<int>& solution, int numberUnits, bool verbose = false);
