#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>

struct Edge {
    std::string to;
    double weight;
};

class Graph {
public:
    std::unordered_map<std::string, std::vector<Edge>> adj;

    void add_edge(const std::string& from, const std::string& to, double weight);

    std::unordered_map<std::string, std::vector<Edge>>& get_adjacency_list();
};

#endif
