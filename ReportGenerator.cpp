#include "ReportGenerator.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

ReportGenerator::ReportGenerator(const std::string& format)
    : reportFormat(format) {}

void ReportGenerator::addAnalysisResult(AnalysisResult result) {
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
    std::ofstream out(outputPath);
    if (!out.is_open()) return;

    out << "=============================\n";
    out << "     Static Analysis Report  \n";
    out << "=============================\n\n";

    // Tool Summary
    out << "Tool Summary:\n\n";

    for (const auto& result : analysisResults) {
        out << "Tool: " << result.getToolName() << "\n";
        out << "Vulnerability Count: " << result.getVulnerabilityCount() << "\n";
        out << "Critical: " << result.getVulnerabilityCountBySeverity("Critical") << "\n";
        out << "High: " << result.getVulnerabilityCountBySeverity("High") << "\n";
        out << "Medium: " << result.getVulnerabilityCountBySeverity("Medium") << "\n";
        out << "Low: " << result.getVulnerabilityCountBySeverity("Low") << "\n";
        out << "-----------------------------\n";
    }

    // Detailed Vulnerabilities
    out << "\nDetailed Vulnerabilities:\n";
    out << "--------------------------------------------------------------------------------------------\n";
    out << std::left
        << std::setw(15) << "ToolName"
        << std::setw(20) << "Type"
        << std::setw(6)  << "Line"
        << std::setw(10) << "Severity"
        << "Description" << "\n";
    out << "--------------------------------------------------------------------------------------------\n";

    for (const auto& result : analysisResults) {
        for (const auto& vuln : result.getVulnerabilities()) {
            out << std::left
                << std::setw(15) << result.getToolName()
                << std::setw(20) << vuln.getType()
                << std::setw(6)  << vuln.getLine()
                << std::setw(10) << vuln.getSeverity()
                << "\"" << vuln.getDescription() << "\"" << "\n";  // Add quotes for CSV formatting
        }
    }

    out << "--------------------------------------------------------------------------------------------\n";
    out.close();
}


// PDF 
void ReportGenerator::generatePDFReport(const std::string& outputPath) const {
    std::ofstream out(outputPath);
    if (!out.is_open()) return;

    out << "=============================\n";
    out << "     Static Analysis Report  \n";
    out << "=============================\n\n";

    // Tool Summary
    out << "Tool Summary:\n\n";

    for (const auto& result : analysisResults) {
        out << "Tool: " << result.getToolName() << "\n";
        out << "Vulnerability Count: " << result.getVulnerabilityCount() << "\n";
        out << "Critical: " << result.getVulnerabilityCountBySeverity("Critical") << "\n";
        out << "High: " << result.getVulnerabilityCountBySeverity("High") << "\n";
        out << "Medium: " << result.getVulnerabilityCountBySeverity("Medium") << "\n";
        out << "Low: " << result.getVulnerabilityCountBySeverity("Low") << "\n";
        out << "-----------------------------\n";
    }

    // Detailed Vulnerabilities
    out << "\nDetailed Vulnerabilities:\n";
    out << "--------------------------------------------------------------------------------------------\n";
    out << std::left
        << std::setw(15) << "ToolName"
        << std::setw(20) << "Type"
        << std::setw(6)  << "Line"
        << std::setw(10) << "Severity"
        << "Description" << "\n";
    out << "--------------------------------------------------------------------------------------------\n";

    for (const auto& result : analysisResults) {
        for (const auto& vuln : result.getVulnerabilities()) {
            out << std::left
                << std::setw(15) << result.getToolName()
                << std::setw(20) << vuln.getType()
                << std::setw(6)  << vuln.getLine()
                << std::setw(10) << vuln.getSeverity()
                << vuln.getDescription() << "\n";
        }
    }

    out << "--------------------------------------------------------------------------------------------\n";

    out.close();
}

