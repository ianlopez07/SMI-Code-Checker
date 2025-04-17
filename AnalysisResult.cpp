AnalysisResult::AnalysisResult(std::string toolName) 
    : toolName(std::move(toolName)) {
    // Constructor implementation
}

void AnalysisResult::addVulnerability(const Vulnerability& vuln) {
    vulnerabilities.push_back(vuln);
}

void AnalysisResult::setRiskLevel(const std::string& vulnType, const std::string& level) {
    riskLevels[vulnType] = level;
}

std::string AnalysisResult::getRiskLevel(const std::string& vulnType) const {
    auto it = riskLevels.find(vulnType);
    if (it != riskLevels.end()) {
        return it->second;
    }
    return "Unknown"; // Default risk level if not specified
}

int AnalysisResult::getVulnerabilityCountBySeverity(const std::string& severity) const {
    return std::count_if(vulnerabilities.begin(), vulnerabilities.end(), 
        [&severity](const Vulnerability& v) {
            return v.getSeverity() == severity;
        });
}

// Additional utility methods that could be useful

std::vector<std::string> AnalysisResult::getUniqueVulnerabilityTypes() const {
    std::vector<std::string> types;
    for (const auto& vuln : vulnerabilities) {
        if (std::find(types.begin(), types.end(), vuln.getType()) == types.end()) {
            types.push_back(vuln.getType());
        }
    }
    return types;
}

std::map<std::string, int> AnalysisResult::getVulnerabilityCountByType() const {
    std::map<std::string, int> countByType;
    for (const auto& vuln : vulnerabilities) {
        countByType[vuln.getType()]++;
    }
    return countByType;
}

std::map<int, std::vector<Vulnerability>> AnalysisResult::getVulnerabilitiesByLine() const {
    std::map<int, std::vector<Vulnerability>> vulnsByLine;
    for (const auto& vuln : vulnerabilities) {
        vulnsByLine[vuln.getLine()].push_back(vuln);
    }
    return vulnsByLine;
}

// Helper method to merge results from multiple tools
void AnalysisResult::mergeWith(const AnalysisResult& other) {
    for (const auto& vuln : other.getVulnerabilities()) {
        // You might want to check for duplicates here
        vulnerabilities.push_back(vuln);
    }
    
    // Merge risk levels as well
    for (const auto& type : other.getUniqueVulnerabilityTypes()) {
        if (riskLevels.find(type) == riskLevels.end()) {
            riskLevels[type] = other.getRiskLevel(type);
        }
    }
}

// Method to get vulnerabilities filtered by severity
std::vector<Vulnerability> AnalysisResult::getVulnerabilitiesBySeverity(const std::string& severity) const {
    std::vector<Vulnerability> filtered;
    std::copy_if(vulnerabilities.begin(), vulnerabilities.end(), 
        std::back_inserter(filtered),
        [&severity](const Vulnerability& v) {
            return v.getSeverity() == severity;
        });
    return filtered;
}