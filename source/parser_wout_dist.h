std::vector<int> removeDupWord(std::string& str); 
void read_map(std::vector<std::vector<int>>& weight_matrix, std::vector<std::vector<int>>& imp_matrix, std::vector<std::vector<int>>& flags_matrix);
void dijkstra(std::vector<std::vector<int>>& weights, int source);
void shortest_path(std::vector<std::vector<int>>& weights, int n);
void floyd_warshall(std::vector<std::vector<int>>& dist, int n);
