#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "graph.h"
#include "dijkstra.h"
#include "json.hpp"

using json = nlohmann::json;

int main() {
    Graph g;
    std::ifstream file("data/uttarakhand_map.json");
    if (!file.is_open()) {
        std::cerr << "Cannot open JSON file!" << std::endl;
        return 1;
    }

    json j;
    file >> j;

    // Load edges (undirected)
    for (auto& edge : j["edges"]) {
        std::string from = edge["from"];
        std::string to = edge["to"];
        double weight = edge["weight"];
        g.add_edge(from, to, weight);
        g.add_edge(to, from, weight);
    }

    Dijkstra d;

    while (true) {
        std::string start, end;
        std::cout << "\n==============================\n";
        std::cout << "Enter start city (or 'exit' to quit): ";
        std::getline(std::cin, start);
        if (start == "exit") break;

        std::cout << "Enter destination city: ";
        std::getline(std::cin, end);

        std::vector<std::string> path = d.shortest_path(g, start, end);
        if (path.empty()) {
            std::cout << "\nNo path found between " << start << " and " << end << std::endl;
        } else {
            std::cout << "\nStepwise Evacuation Route:\n";
            auto& adj = g.adj;
            double total_distance = 0.0;

            for (size_t i = 0; i < path.size() - 1; ++i) {
                const std::string& u = path[i];
                const std::string& v = path[i + 1];
                double distance = 0.0;
                for (const auto& e : adj[u]) {
                    if (e.to == v) {
                        distance = e.weight;
                        break;
                    }
                }
                total_distance += distance;
                std::cout << "Step " << i + 1 << ": "
                          << std::setw(12) << std::left << u
                          << " -> "
                          << std::setw(12) << std::left << v
                          << "(" << distance << " km)" << std::endl;
            }

            std::cout << "------------------------------\n";
            std::cout << "Total Distance: " << total_distance << " km\n";
            std::cout << "==============================\n";
        }
    }

    std::cout << "\nThank you for using Smart Disaster Evacuation Planner!\n";
    return 0;
}
