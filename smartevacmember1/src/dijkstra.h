#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include <string>
#include <vector>
#include <unordered_map>

class Dijkstra {
public:
    std::vector<std::string> shortest_path(const Graph& g, const std::string& start, const std::string& end);
};

#endif
