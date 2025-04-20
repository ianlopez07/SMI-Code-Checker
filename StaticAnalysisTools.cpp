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
    qDebug() << "Adding test vulnerability to verify report generation";
    Vulnerability testVuln("Test-Type", 1, "This is a test vulnerability", "Medium");
    result.addVulnerability(testVuln);

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