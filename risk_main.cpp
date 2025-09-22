#include <iostream>
#include <fstream>
#include <set>
#include "graph.h"
#include "risk_manager.h"
#include "json.hpp"

using json = nlohmann::json;

int main() {
    Graph g;
    std::ifstream file("uttarakhand_map.json");
    if (!file.is_open()) return 1;
    json j; file >> j; file.close();

    for (auto &edge : j["edges"]) {
        std::string from = edge["from"];
        std::string to = edge["to"];
        double weight = edge["weight"];
        g.add_edge(from, to, weight);
        g.add_edge(to, from, weight);
    }

    RiskManager rm;
    for (auto &kv : g.get_adjacency_list()) rm.node_risk[kv.first] = 0.0;

    rm.update_node_risk();

    std::cout << "\n--- Node Risk Details ---\n";
    rm.displayRisks();

    for (auto &kv : g.adj) {
        for (auto &edge : kv.second) {
            double risk_from = rm.getTotalRisk(kv.first);
            double risk_to   = rm.getTotalRisk(edge.to);
            edge.weight = edge.weight * (1 + 0.5 * risk_from + 0.5 * risk_to);
        }
    }

    std::cout << "\nAdjusted Edge Weights (Unique Undirected Edges):\n";
    std::set<std::pair<std::string, std::string>> printed;
    for (auto &kv : g.adj) {
        const std::string &from = kv.first;
        for (auto &edge : kv.second) {
            std::string a = from;
            std::string b = edge.to;
            if (a > b) std::swap(a, b);
            if (printed.find({a, b}) == printed.end()) {
                printed.insert({a, b});
                std::cout << a << " -> " << b
                          << " | Adjusted weight = " << edge.weight << "\n";
            }
        }
    }

    rm.save_risk_to_file("risk_data.json");
    return 0;
}
