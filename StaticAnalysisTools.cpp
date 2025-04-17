#include "StaticAnalysisTools.h"
#include <cstdio>
#include <array>
#include <memory>
#include <stdexcept>
#include <windows.h>
#include <process.h>
#define popen _popen
#define pclose _pclose

StaticAnalysisTool::StaticAnalysisTool(std::string name, std::string setVersion, std::string format) {
    toolName = name;
    version = setVersion;
    outputFormat = format;
}

std::string StaticAnalysisTool::executeCommand(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    FILE* pipe = popen(cmd, "r");
    
    if (!pipe) {
        return "popen failed!";
    }
    
    while (fgets(buffer.data(), buffer.size(), pipe) != nullptr) {
        result += buffer.data();
    }
    
    pclose(pipe);
    return result;
}

CPPCheckTool::CPPCheckTool(std::string name, std::string setVersion, std::string format) : StaticAnalysisTool(name, setVersion, format) {

}

Flawfinder::Flawfinder(std::string name, std::string setVersion, std::string format) : StaticAnalysisTool(name, setVersion, format){

}

GCCAnalyzer::GCCAnalyzer(std::string name, std::string setVersion, std::string format) : StaticAnalysisTool(name, setVersion, format){

}

AnalysisResult GCCAnalyzer::runAnalysis(const SourceCodeFile& sourceCodeFile) override {
    AnalysisResult *result = new AnalysisResult();

    // Build the GCC command with -fanalyzer flag
    std::string gccCommand = "gcc -fanalyzer -c ";
    gccCommand += "\"" + sourceCodeFile.getFilePath() + "\"";
    
    // Add additional flags if needed
    gccCommand += " -Wall -Wextra";
    
    // We only want the warnings, not actual compilation
    gccCommand += " -fsyntax-only";

    std::string output = executeCommand(gccCommand);

    std::istringstream stream(output);
    std::string line;
    
    // Regular expression to parse GCC output
    std::regex gccPattern("(.*?):(\\d+):(\\d+): (warning|error): (.*)");
    
    while (std::getline(stream, line)) {
        std::smatch matches;
        if (std::regex_search(line, matches, gccPattern) && matches.size() >= 6) {
            // matches[1] = filename
            // matches[2] = line number
            // matches[3] = column
            // matches[4] = type (warning/error)
            // matches[5] = message
            
            int lineNumber = std::stoi(matches[2].str());
            std::string type = "GCC-" + matches[4].str();
            std::string description = matches[5].str();
            
            // Determine severity based on whether it's a warning or error
            std::string severity = (matches[4] == "warning") ? "Medium" : "High";
            
            // Create vulnerability and add to result
            Vulnerability vuln(type, lineNumber, description, severity);
            result->addVulnerability(vuln);
        }
    }
}