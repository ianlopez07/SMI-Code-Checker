#pragma once
#include <string>
#include <vector>
#include <map>
#include "Vulnerability.h"

class AnalysisResult {
private:
    std::vector<Vulnerability> vulnerabilities;
    std::string toolName;
    std::map<std::string, std::string> riskLevels;
    
public:
    AnalysisResult(std::string toolName);
    ~AnalysisResult() = default;
    
    void addVulnerability(const Vulnerability& vuln);
    void setRiskLevel(const std::string& vulnType, const std::string& level);
    
    const std::vector<Vulnerability>& getVulnerabilities() const { return vulnerabilities; }
    std::string getToolName() const { return toolName; }
    std::string getRiskLevel(const std::string& vulnType) const;
    
    // Statistics
    int getVulnerabilityCount() const { return vulnerabilities.size(); }
    int getVulnerabilityCountBySeverity(const std::string& severity) const;

    std::vector<std::string> getUniqueVulnerabilityTypes() const;
    std::map<std::string, int> getVulnerabilityCountByType() const;
    std::map<int, std::vector<Vulnerability>> getVulnerabilitiesByLine() const;
    void mergeWith(const AnalysisResult& other);
    std::vector<Vulnerability> getVulnerabilitiesBySeverity(const std::string& severity) const;
};