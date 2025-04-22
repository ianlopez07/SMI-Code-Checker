#include "StaticAnalysisTools.h"
#include <cstdio>
#include <array>
#include <memory>
#include <regex>
#include <stdexcept>
#include <windows.h>
#include <process.h>
#include <QDebug>
#include <fstream>
#include <sstream>  // for std::istringstream
#define popen _popen
#define pclose _pclose

StaticAnalysisTool::StaticAnalysisTool(std::string name, std::string setVersion, std::string format) {
    toolName = name;
    version = setVersion;
    outputFormat = format;
}

std::string StaticAnalysisTool::executeCommand(std::string cmd) {
    qDebug() << "Executing command:" << QString::fromStdString(cmd);
    
    std::array<char, 128> buffer;
    std::string result;

    const char* charPtr = cmd.c_str();
    FILE* pipe = popen(charPtr, "r");
    
    if (!pipe) {
        qDebug() << "popen failed!";
        return "popen failed!";
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    
    pclose(pipe);
    qDebug() << "Command output length:" << result.length();
    qDebug() << "Command output:" << QString::fromStdString(result);
    
    // Log the output to a file for inspection
    std::ofstream logFile("command_output.log");
    if (logFile.is_open()) {
        logFile << "Command: " << cmd << std::endl;
        logFile << "Output: " << result << std::endl;
        logFile.close();
    }
    
    return result;
}

CPPCheckTool::CPPCheckTool(std::string name, std::string setVersion, std::string format) : StaticAnalysisTool(name, setVersion, format) {

}

Flawfinder::Flawfinder(std::string name, std::string setVersion, std::string format) : StaticAnalysisTool(name, setVersion, format){

}

GCCAnalyzer::GCCAnalyzer(std::string name, std::string setVersion, std::string format) : StaticAnalysisTool(name, setVersion, format){

}

AnalysisResult GCCAnalyzer::runAnalysis(const SourceCodeFile& sourceCodeFile) {
    qDebug() << "Starting GCC analysis on file:" << QString::fromStdString(sourceCodeFile.getFilePath());
    
    AnalysisResult result(toolName);  // Create on stack instead of heap

    // Verify file path is valid
    qDebug() << "File path:" << QString::fromStdString(sourceCodeFile.getFilePath());
    qDebug() << "File name:" << QString::fromStdString(sourceCodeFile.getFileName());
    
    // Build the GCC command with -fanalyzer flag
    std::string gccCommand = "gcc -fanalyzer -c ";
    gccCommand += "\"" + sourceCodeFile.getFilePath() + "\"";

    // Add additional flags if needed
    gccCommand += " -Wall -Wextra";

    // We only want the warnings, not actual compilation
    gccCommand += " -fsyntax-only";

    // Important: Redirect stderr to stdout so we can capture the warnings
    gccCommand += " 2>&1";

    qDebug() << "GCC command:" << QString::fromStdString(gccCommand);
    std::string output = executeCommand(gccCommand);
    qDebug() << "GCC command executed. Output size:" << output.size();
    
    // If no output, try a simpler command to check if GCC is working
    if (output.empty() || output == "popen failed!") {
        qDebug() << "Trying simple GCC version check...";
        std::string versionCheck = executeCommand("gcc --version");
        qDebug() << "GCC version output:" << QString::fromStdString(versionCheck);
    }

    // Create a test vulnerability to ensure processing works
    //qDebug() << "Adding test vulnerability to verify report generation";
    //Vulnerability testVuln("Test-Type", 1, "This is a test vulnerability", "Medium");
    //result.addVulnerability(testVuln);

    std::istringstream stream(output);
    std::string line;
    
    // Regular expression to parse GCC output
    std::regex gccPattern("(.*?):(\\d+):(\\d+): (warning|error): (.*)");
    
    qDebug() << "Parsing GCC output lines...";
    int lineCount = 0;
    int matchCount = 0;
    
    while (std::getline(stream, line)) {
        lineCount++;
        std::smatch matches;
        qDebug() << "Checking line:" << QString::fromStdString(line);
        
        if (std::regex_search(line, matches, gccPattern) && matches.size() >= 6) {
            matchCount++;
            // matches[1] = filename
            // matches[2] = line number
            // matches[3] = column
            // matches[4] = type (warning/error)
            // matches[5] = message
            
            qDebug() << "Found match!";
            qDebug() << "Filename:" << QString::fromStdString(matches[1].str());
            qDebug() << "Line:" << QString::fromStdString(matches[2].str());
            qDebug() << "Type:" << QString::fromStdString(matches[4].str());
            qDebug() << "Message:" << QString::fromStdString(matches[5].str());
            
            int lineNumber = std::stoi(matches[2].str());
            std::string type = "GCC-" + matches[4].str();
            std::string description = matches[5].str();
            
            // Determine severity based on whether it's a warning or error
            std::string severity = (matches[4] == "warning") ? "Medium" : "High";
            
            // Create vulnerability and add to result
            Vulnerability vuln(type, lineNumber, description, severity);
            result.addVulnerability(vuln);
        }
    }
    
    qDebug() << "Processed" << lineCount << "lines with" << matchCount << "matches";
    qDebug() << "Final vulnerability count:" << result.getVulnerabilityCount();

    return result;
}

AnalysisResult CPPCheckTool::runAnalysis(const SourceCodeFile& sourceCodeFile) {
    qDebug() << "Starting CPPCheck analysis on file:" << QString::fromStdString(sourceCodeFile.getFilePath());
    
    AnalysisResult result(toolName);

    std::string filePath = sourceCodeFile.getFilePath();

    // Full command: cppcheck --enable=all "source.c" 2>&1
    std::string cppcheckCommand = "cppcheck ";
    cppcheckCommand += "--enable=all ";
    cppcheckCommand += "\"" + filePath + "\"";
    cppcheckCommand += " 2>&1";

    qDebug() << "CPPCheck command:" << QString::fromStdString(cppcheckCommand);

    std::string output = executeCommand(cppcheckCommand);
    qDebug() << "CPPCheck command executed. Output size:" << output.size();

    // Check for command errors
    if (output.empty() || output.find("command not found") != std::string::npos) {
        qDebug() << "CPPCheck might not be installed or not in PATH";
        Vulnerability vuln("CPPCheck-Error", 0, "CPPCheck might not be installed or not in PATH", "High");
        result.addVulnerability(vuln);
        return result;
    }

    std::istringstream stream(output);
    std::string line;

    // Regex matching CPPCheck format with optional column and check ID
    std::regex cppcheckPattern(R"(^(.*?):(\d+):\d+:\s+(error|warning|style|performance|portability|information):\s+(.*?)\s+\[.*\])");

    while (std::getline(stream, line)) {
        std::smatch matches;
        qDebug() << "CPPCheck line:" << QString::fromStdString(line);

        if (std::regex_search(line, matches, cppcheckPattern)) {
            if (matches.size() >= 5) {
                try {
                    std::string fileName = matches[1].str();
                    int lineNumber = std::stoi(matches[2].str());
                    std::string cppcheckSeverity = matches[3].str();  // error, warning, etc.
                    std::string description = matches[4].str();

                    // Map to custom severity
                    std::string severity = "Low";
                    if (cppcheckSeverity == "error") severity = "High";
                    else if (cppcheckSeverity == "warning") severity = "Medium";

                    std::string type = "CPPCheck-" + cppcheckSeverity;

                    Vulnerability vuln(type, lineNumber, description, severity);
                    result.addVulnerability(vuln);
                    qDebug() << "Added CPPCheck vulnerability at line" << lineNumber;
                } catch (const std::exception& e) {
                    qDebug() << "Exception while parsing CPPCheck output:" << e.what();
                }
            }
        } else {
            qDebug() << "No match for line:" << QString::fromStdString(line);
        }
    }


    qDebug() << "Final CPPCheck vulnerability count:" << result.getVulnerabilityCount();
    return result;
}


AnalysisResult Flawfinder::runAnalysis(const SourceCodeFile& sourceCodeFile) {
    qDebug() << "Starting Flawfinder analysis on file:" << QString::fromStdString(sourceCodeFile.getFilePath());
    
    AnalysisResult result(toolName);

    // Test if Flawfinder is available
    std::string versionCheck = executeCommand("flawfinder --version");
    if (versionCheck.empty() || versionCheck.find("command not found") != std::string::npos) {
        qDebug() << "Flawfinder is not installed or not in PATH";
        Vulnerability vuln("Flawfinder-Error", 0, 
                           "Flawfinder might not be installed or not in PATH", "High");
        result.addVulnerability(vuln);
        
        // Add a test vulnerability 
        //Vulnerability testVuln("Flawfinder-Test", 2, "This is a test Flawfinder vulnerability", "Medium");
        //result.addVulnerability(testVuln);
        
        //return result;
    }

    // Build the Flawfinder command with simpler output format
    std::string flawfinderCommand = "flawfinder ";
    flawfinderCommand += "--csv "; 
    flawfinderCommand += "--minlevel=1 ";
    flawfinderCommand += "\"" + sourceCodeFile.getFilePath() + "\"";
    flawfinderCommand += " 2>&1";
    
    qDebug() << "Flawfinder command:" << QString::fromStdString(flawfinderCommand);
    
    std::string output = executeCommand(flawfinderCommand);
    qDebug() << "Flawfinder command executed. Output size:" << output.size();
    
    // Add a test vulnerability to ensure processing works
    Vulnerability testVuln("Flawfinder-Test", 2, "This is a test Flawfinder vulnerability", "Medium");
    result.addVulnerability(testVuln);

    std::istringstream stream(output);
    std::string line;
    
    // Skip header line
    std::getline(stream, line);
    
    // Process each line
    while (std::getline(stream, line)) {
        qDebug() << "Flawfinder line:" << QString::fromStdString(line);
        
        // Split by comma with handling for quoted fields
        std::vector<std::string> fields;
        std::string currentField;
        bool inQuotes = false;
        
        for (char c : line) {
            if (c == '"') {
                inQuotes = !inQuotes;
            } else if (c == ',' && !inQuotes) {
                fields.push_back(currentField);
                currentField.clear();
            } else {
                currentField += c;
            }
        }
        fields.push_back(currentField); // Add the last field
        
        // Process fields if we have enough
        if (fields.size() >= 7) {
            try {
                std::string filename = fields[0];
                int lineNumber = std::stoi(fields[1]);
                std::string level = fields[3];
                std::string category = fields[4];
                std::string function = fields[5];
                std::string description = fields[6];
                
                int riskLevel = std::stoi(level);
                std::string severity = (riskLevel >= 4) ? "High" : 
                                      (riskLevel >= 2) ? "Medium" : "Low";
                
                std::string type = "Flawfinder-" + category;
                
                Vulnerability vuln(type, lineNumber, description, severity);
                result.addVulnerability(vuln);
                qDebug() << "Added Flawfinder vulnerability at line" << lineNumber;
            } catch (const std::exception& e) {
                qDebug() << "Exception while parsing Flawfinder output:" << e.what();
            }
        }
    }
    
    qDebug() << "Final Flawfinder vulnerability count:" << result.getVulnerabilityCount();
    return result;
}