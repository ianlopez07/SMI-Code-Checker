#ifndef PROJECTPAGE_H
#define PROJECTPAGE_H

#include <QWidget>
#include "StaticAnalysisTools.h"
#include "AnalysisResult.h"
#include "SourceCodeFile.h"

class MainWindow;

namespace Ui {
class ProjectPage;
}

class ProjectPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectPage(MainWindow* mainw, QWidget *parent = nullptr);
    ~ProjectPage();

    AnalysisResult* getGCCResult() { return &gcc_result; }
    AnalysisResult* getCPPCheckResult() { return &cppcheck_result; }
    AnalysisResult* getFlawfinderResult() { return &flawfinder_result; }

public:
    Ui::ProjectPage *ui;
private slots:

    void on_AnalyizeBtn_clicked();
    void on_GCC_checkStateChanged(const Qt::CheckState &arg1);
    void on_Flawfinder_checkStateChanged(const Qt::CheckState &arg1);
    void on_CPP_checkStateChanged(const Qt::CheckState &arg1);

private:
    MainWindow* m_mainw;  // Store the pointer to MainWindow
    SourceCodeFile* file = nullptr;  // Use a pointer instead of object instance
    GCCAnalyzer gcc{"GCC", "latest", "text"};
    CPPCheckTool cppcheck{"CPPCheck", "latest", "text"};
    Flawfinder flawfinder{"Flawfinder", "latest", "text"};
    AnalysisResult gcc_result{"GCC"};
    AnalysisResult cppcheck_result{"CPPCheck"};
    AnalysisResult flawfinder_result{"Flawfinder"};
};

#endif // PROJECTPAGE_H
