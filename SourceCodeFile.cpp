#pragma once
#include <string>
#include <iostream>
#include <filesystem>
namespace fs = std::filesystem;

class SourceCodeFile {
private:
    std::string fileName;
    fs::path filePath;
    std::string filePathS;
    std::string fileContent;

public:
    SourceCodeFile(const std::string& path) {
        filePath, filePathS = path;
        fileName = filePath.stem();
    }
    ~SourceCodeFile() = default;
    
    bool validateFile() const { // Validates C/C++ file
        if(filePathS.length() < 0) {
            return 0;
        }
        else {
            if(filePath.extension() == ".c" || filePath.extension() == ".cpp") {
                return 1;
            }
            else {
                return 0;
            }
        }
    }
    
    const std::string& getFileName() const { return fileName; }
    const std::string& getFilePath() const { return filePathS; }
    const std::string& getFileContent() const { return fileContent; }
};