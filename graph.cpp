#include "graph.h"

void Graph::add_edge(const std::string& from, const std::string& to, double weight) {
    adj[from].push_back({to, weight});
}


std::unordered_map<std::string, std::vector<Edge>>& Graph::get_adjacency_list() {
    return adj;
}