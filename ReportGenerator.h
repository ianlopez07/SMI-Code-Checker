// ReportGenerator.h
#pragma once
#include <string>
#include <vector>
#include <memory>
#include "AnalysisResult.h"

class ReportGenerator {
private:
    std::string reportFormat;  // PDF, JSON, CSV
    std::vector<AnalysisResult> analysisResults;
    
    void generatePDFReport(const std::string& outputPath) const;
    void generateJSONReport(const std::string& outputPath) const;
    void generateCSVReport(const std::string& outputPath) const;
    
public:
    ReportGenerator(const std::string& format);
    ~ReportGenerator() = default;
    
    void addAnalysisResult(AnalysisResult result);
    std::string generateReport(const std::string& outputPath) const;
    void exportReport(const std::string& outputPath) const;

};
