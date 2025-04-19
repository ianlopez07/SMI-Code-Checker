#include "SourceCodeFile.h"

SourceCodeFile::SourceCodeFile(const std::string& path) {
    filePath, filePathS = path;
    fileName = filePath.stem();
}
    
bool SourceCodeFile::validateFile() const { // Validates C/C++ file
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

void setFilePath(const std::string& path) {
    filePath, filePathS = path;
    fileName = filePath.stem();
}