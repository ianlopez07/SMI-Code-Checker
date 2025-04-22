#ifndef REPORT_H
#define REPORT_H


#include <QWidget>
#include "AnalysisResult.h"
#include "ReportGenerator.h"


class ProjectPage;


namespace Ui {
class Report;
}


class Report : public QWidget
{
    Q_OBJECT


public:
    explicit Report(ProjectPage* page, QWidget *parent = nullptr);
    ~Report();


public:
    Ui::Report *ui;
private slots:


    void on_csvRadioBtn_clicked();
    void on_pdfRadioBtn_clicked();
    void on_jsonRadioBtn_clicked();
    void on_DownloadBtn_clicked();


private:
    ProjectPage* ppage;
    AnalysisResult* gcc_res = nullptr;
    AnalysisResult* cppcheck_res = nullptr;
    AnalysisResult* flawfinder_res = nullptr;
    ReportGenerator* pdf_gen = new ReportGenerator("PDF");
    ReportGenerator* csv_gen = new ReportGenerator("CSV");
};


#endif // REPORT_H
