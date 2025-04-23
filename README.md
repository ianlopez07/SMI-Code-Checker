# SMI Code Checker

## Overview
SMI Code Checker is a desktop application that performs static code analysis on C/C++ source files to identify potential vulnerabilities, bugs, and code quality issues. The tool integrates multiple industry-standard static analysis engines (GCC Analyzer, CPPCheck, and Flawfinder) into a single interface, allowing developers to easily scan their code and generate comprehensive vulnerability reports.

## Features
- **Multiple Analysis Engines**: Integrates GCC Analyzer, CPPCheck, and Flawfinder
- **User-Friendly Interface**: Simple Qt-based GUI for easy code scanning
- **Vulnerability Detection**: Identifies potential security issues, bugs, and code quality problems
- **Detailed Reports**: Generate reports in multiple formats (PDF, CSV)
- **Severity Classification**: Vulnerabilities are classified by severity (Critical, High, Medium, Low)
- **Line-Specific Issues**: Pinpoints the exact location of potential problems in code

## Prerequisites
To run SMI Code Checker, you'll need:
- C++17 compatible compiler
- Qt 5.15.x or newer
- CMake 3.12 or newer
- The following static analysis tools installed and available in your PATH:
  - GCC with the `-fanalyzer` flag support
  - CPPCheck
  - Flawfinder

## Installation

### Building from Source
1. Clone the repository:
   ```
   git clone https://github.com/yourusername/smi-code-checker.git
   cd smi-code-checker
   ```

2. Create a build directory and run CMake:
   ```
   mkdir build
   cd build
   cmake ..
   ```

3. Build the project:
   ```
   cmake --build .
   ```

4. Run the application:
   ```
   ./SMICodeChecker
   ```

## Usage

### Basic Workflow
1. **Upload Source Code**: Click the "Upload File" button to select a C/C++ source file.
2. **Select Analysis Tools**: Choose which analysis tools to use (GCC, CPPCheck, Flawfinder).
3. **Run Analysis**: Click the "Analyze" button to scan the code for vulnerabilities.
4. **View Results**: The application will display the progress and redirect to the report page when complete.
5. **Generate Report**: Select your preferred report format (PDF or CSV) and click "Download".

### Supported File Types
- C source files (.c)
- C++ source files (.cpp)

## Architecture
SMI Code Checker follows an object-oriented design with the following main components:

- **UI Layer**: Qt-based interface with three main screens:
  - MainWindow: File selection
  - ProjectPage: Analysis tool selection and execution
  - Report: Report generation and download

- **Core Components**:
  - `SourceCodeFile`: Represents and validates source code files
  - `Vulnerability`: Models detected vulnerabilities
  - `AnalysisResult`: Collects and organizes vulnerabilities found by tools
  - `StaticAnalysisTool`: Base class for all analysis engines
  - `ReportGenerator`: Creates formatted reports from analysis results

## Acknowledgments
- Qt framework for the GUI components
- GCC, CPPCheck, and Flawfinder developers for their incredible static analysis tools