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
    SourceCodeFile(const std::string& path);
    ~SourceCodeFile() = default;
    
    bool validateFile() const; // Validates C/C++ file
    
    void setFilePath(const std::string& path);
    const std::string& getFileName() const { return fileName; }
    const std::string& getFilePath() const { return filePathS; }
    const std::string& getFileContent() const { return fileContent; }
};