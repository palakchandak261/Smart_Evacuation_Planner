#include "dijkstra.h"
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>

std::vector<std::string> Dijkstra::shortest_path(const Graph& g, const std::string& start, const std::string& end) {
    using Pair = std::pair<double, std::string>;
    std::unordered_map<std::string, double> dist;
    std::unordered_map<std::string, std::string> prev;
    auto& adj = g.adj;

    // Initialize distances
    for (const auto& kv : adj) {
        dist[kv.first] = std::numeric_limits<double>::infinity();
    }
    dist[start] = 0.0;

    // Min-heap priority queue
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    pq.push({0.0, start});

    while (!pq.empty()) {
        double current_dist = pq.top().first;
        std::string u = pq.top().second;
        pq.pop();

        if (current_dist > dist[u]) continue;

        for (const auto& edge : adj.at(u)) {
            double new_dist = current_dist + edge.weight;
            if (new_dist < dist[edge.to]) {
                dist[edge.to] = new_dist;
                prev[edge.to] = u;
                pq.push({new_dist, edge.to});
            }
        }
    }

    // Reconstruct path
    std::vector<std::string> path;
    std::string u = end;
    if (prev.find(u) != prev.end() || u == start) {
        while (u != start) {
            path.push_back(u);
            u = prev[u];
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
    }
    return path;
}
