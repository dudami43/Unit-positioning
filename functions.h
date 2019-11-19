int objectiveFunction(std::vector<std::vector<int>>& weight_matrix, std::vector<std::vector<int>>& imp_matrix, std::vector<int>& solution, bool use_importance, bool verbose = false);
int closestUnit(int point, std::vector<std::vector<int>>& weight_matrix, std::vector<int>& solution, bool verbose = false);

void greedySolution(int numberUnits, std::vector<std::vector<int>>& weight_matrix, std::vector<std::vector<int>>& imp_matrix, std::vector<int>& solution, bool verbose = false);