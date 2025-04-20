#pragma once
#include <string>
#include <memory>
#include "SourceCodeFile.h"
#include "AnalysisResult.h"

class StaticAnalysisTool {
protected:
    std::string toolName;
    std::string version;
    std::string outputFormat;
    int exitCode = -1;
    
public:
    StaticAnalysisTool(std::string name, std::string setVersion, std::string format);
    virtual ~StaticAnalysisTool() = default;

    std::string executeCommand(std::string cmd);
    virtual AnalysisResult runAnalysis(const SourceCodeFile& sourceCodeFile) = 0;
    
    std::string getToolName() const { return toolName; }
    std::string getVersion() const { return version; }
};

class CPPCheckTool : public StaticAnalysisTool {
    public:
        CPPCheckTool(std::string name, std::string setVersion, std::string format);
        ~CPPCheckTool() override = default;

        AnalysisResult runAnalysis(const SourceCodeFile& sourceCodeFile) override;
    };

class Flawfinder : public StaticAnalysisTool {
    public:
        Flawfinder(std::string name, std::string setVersion, std::string format);
        ~Flawfinder() override = default;

        AnalysisResult runAnalysis(const SourceCodeFile& sourceCodeFile) override;
};

class GCCAnalyzer : public StaticAnalysisTool {
    public:
        GCCAnalyzer(std::string name, std::string setVersion, std::string format);
        ~GCCAnalyzer() override = default;

        AnalysisResult runAnalysis(const SourceCodeFile& sourceCodeFile) override;
};