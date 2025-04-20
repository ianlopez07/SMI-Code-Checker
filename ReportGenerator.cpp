#include "ReportGenerator.h"
#include <fstream>
#include <iostream>
#include <sstream>
//#include <nlohmann/json.hpp> // I think I need this for json file generation  

ReportGenerator::ReportGenerator(const std::string& format)
    : reportFormat(format) {}

void ReportGenerator::addAnalysisResult(std::shared_ptr<AnalysisResult> result) {
    analysisResults.push_back(result);
}

std::string ReportGenerator::generateReport(const std::string& outputPath) const {
    if (reportFormat == "PDF") {
        generatePDFReport(outputPath);
    } /*else if (reportFormat == "JSON") {
        generateJSONReport(outputPath);
    }*/ else if (reportFormat == "CSV") {
        generateCSVReport(outputPath);
    } else {
        std::cerr << "Unsupported format: " << reportFormat << std::endl;
        return "Unsupported format";
    }
    return "Report generated at: " + outputPath;
}

void ReportGenerator::exportReport(const std::string& outputPath) const {
    generateReport(outputPath);
}

// CSV 
void ReportGenerator::generateCSVReport(const std::string& outputPath) const {
    std::ofstream out(outputPath + "Report.csv");
    out << "ToolName,VulnerabilityType,Line,Description,Severity\n";

    for (const auto& result : analysisResults) {
        for (const auto& vuln : result->getVulnerabilities()) {
            out << result->getToolName() << ","
                << vuln.getType() << ","
                << vuln.getLine() << ","
                << "\"" << vuln.getDescription() << "\","
                << vuln.getSeverity() << "\n";
        }
    }

    out.close();
}

// JSON ??
/*void ReportGenerator::generateJSONReport(const std::string& outputPath) const {
    nlohmann::json j;

    for (const auto& result : analysisResults) {
        nlohmann::json toolReport;
        toolReport["tool"] = result->getToolName();
        for (const auto& vuln : result->getVulnerabilities()) {
            toolReport["vulnerabilities"].push_back({
                {"type", vuln.getType()},
                {"line", vuln.getLine()},
                {"description", vuln.getDescription()},
                {"severity", vuln.getSeverity()}
            });
        }
        j["reports"].push_back(toolReport);
    }

    std::ofstream out(outputPath);
    out << j.dump(4);  
    out.close();
}*/

// MPDF generation
void ReportGenerator::generatePDFReport(const std::string& outputPath) const {
    std::ofstream out(outputPath);
    out << "=== Static Analysis Report ===\n\n";

    for (const auto& result : analysisResults) {
        out << "Tool: " << result->getToolName() << "\n";
        for (const auto& vuln : result->getVulnerabilities()) {
            out << "Line " << vuln.getLine() << ": "
                << vuln.getType() << " - "
                << vuln.getSeverity() << "\n"
                << "Description: " << vuln.getDescription() << "\n\n";
        }
        out << "-------------------------------------\n";
    }

    out.close();
}
