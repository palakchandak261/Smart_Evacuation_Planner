#include "risk_manager.h"
#include <iostream>
#include <fstream>
#include "json.hpp"
#include <cstdlib>
#include <ctime>

using json = nlohmann::json;

RiskManager::RiskManager() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void RiskManager::update_node_risk() {
    for (auto &kv : node_risk) {
        const std::string &node = kv.first;
        fire_risk[node]       = (std::rand() % 100) / 100.0;
        flood_risk[node]      = (std::rand() % 100) / 100.0;
        earthquake_risk[node] = (std::rand() % 100) / 100.0;
        landslide_risk[node]  = (std::rand() % 100) / 100.0;
        node_risk[node] = (fire_risk[node] + flood_risk[node] + earthquake_risk[node] + landslide_risk[node])/4.0;
        if (node_risk[node] > 1.0) node_risk[node] = 1.0;
    }
}

void RiskManager::update_single_node_risk(const std::string &node, double value) {
    fire_risk[node]       = value;
    flood_risk[node]      = value;
    earthquake_risk[node] = value;
    landslide_risk[node]  = value;
    node_risk[node]       = value * 4;
    if (node_risk[node] > 1.0) node_risk[node] = 1.0;
}

double RiskManager::getTotalRisk(const std::string &node) const {
    auto it = node_risk.find(node);
    if (it != node_risk.end()) return it->second;
    return 0.0;
}

void RiskManager::displayRisks() const {
    for (auto &kv : node_risk) {
        const std::string &node = kv.first;
        std::cout << node << " -> "
                  << "fire: " << fire_risk.at(node)
                  << ", flood: " << flood_risk.at(node)
                  << ", earthquake: " << earthquake_risk.at(node)
                  << ", landslide: " << landslide_risk.at(node)
                  << ", total: " << kv.second
                  << "\n";
    }
}

void RiskManager::save_risk_to_file(const std::string &filename) const {
    json j;
    for (auto &kv : node_risk) {
        const std::string &node = kv.first;
        j[node]["fire"]       = fire_risk.at(node);
        j[node]["flood"]      = flood_risk.at(node);
        j[node]["earthquake"] = earthquake_risk.at(node);
        j[node]["landslide"]  = landslide_risk.at(node);
        j[node]["total"]      = kv.second;
    }
    std::ofstream file(filename);
    if (file.is_open()) {
        file << j.dump(4);
        file.close();
    }
}
