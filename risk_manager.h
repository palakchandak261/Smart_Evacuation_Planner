#ifndef RISK_MANAGER_H
#define RISK_MANAGER_H

#include <string>
#include <unordered_map>

class RiskManager {
public:
    std::unordered_map<std::string, double> node_risk;
    std::unordered_map<std::string, double> fire_risk;
    std::unordered_map<std::string, double> flood_risk;
    std::unordered_map<std::string, double> earthquake_risk;
    std::unordered_map<std::string, double> landslide_risk;

    RiskManager();
    void update_node_risk();
    void update_single_node_risk(const std::string &node, double value);
    double getTotalRisk(const std::string &node) const;
    void displayRisks() const;
    void save_risk_to_file(const std::string &filename) const;
};

#endif
