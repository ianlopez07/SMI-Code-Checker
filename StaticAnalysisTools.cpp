#include "StaticAnalysisTools.h"


StaticAnalysisTool::StaticAnalysisTool(std::string name, std::string setVersion, std::string format) {
    toolName = name;
    version = setVersion;
    outputFormat = format;
}
 


CPPCheckTool::CPPCheckTool(std::string name, std::string setVersion, std::string format) : StaticAnalysisTool(name, setVersion, format) {

}

Flawfinder::Flawfinder(std::string name, std::string setVersion, std::string format) : StaticAnalysisTool(name, setVersion, format){

}

GCCAnalyzer::GCCAnalyzer(std::string name, std::string setVersion, std::string format) : StaticAnalysisTool(name, setVersion, format){

}