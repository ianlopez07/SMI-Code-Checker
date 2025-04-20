#include "report.h"
#include "ui_report.h"
#include "projectpage.h"
#include <QMessageBox>

Report::Report(ProjectPage* page, QWidget *parent)
    : QWidget(parent), ppage(page)
    , ui(new Ui::Report)
{
    ui->setupUi(this);

}

Report::~Report()
{
    delete ui;
}


void Report::on_csvRadioBtn_clicked()
{
    if (ppage->getGCCResult()) {
        gcc_res = ppage->getGCCResult();  // Store pointer instead of copying
        Vulnerability v_test{"test", 5, "test", "test"};
        gcc_res->addVulnerability(v_test);
        //QMessageBox::information(this, tr("Vuln Test"), tr(gcc_res->getToolName().c_str()));
    }
}


void Report::on_jsonRadioBtn_clicked()
{

}


void Report::on_DownloadBtn_clicked()
{
    if(ui->csvRadioBtn->isChecked()) {
        csv_gen->addAnalysisResult(*gcc_res);
        std::string outputPath = "C:/Users/iancl/OneDrive/Documents/";
        const char* c_outputPath = outputPath.c_str();
        csv_gen->exportReport(outputPath);
        QMessageBox::information(this, tr("Download Complete. File Location:"), tr(c_outputPath));
        QMessageBox::information(this, tr("Vuln Test"), tr(std::to_string(gcc_res->getVulnerabilityCount()).c_str()));
    }
}

