#include "graph.h"

// Define add_edge here (not in header)
void Graph::add_edge(const std::string& from, const std::string& to, double weight) {
    adj[from].push_back({to, weight});
}

// Define get_adjacency_list here
const std::unordered_map<std::string, std::vector<Edge>>& Graph::get_adjacency_list() const {
    return adj;
}