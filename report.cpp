#include "report.h"
#include "ui_report.h"
#include "projectpage.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>

Report::Report(ProjectPage* page, QWidget *parent)
    : QWidget(parent), ppage(page)
    , ui(new Ui::Report)
{
    ui->setupUi(this);
    qDebug() << "Report constructor called";
    
    // Initialize generators
    pdf_gen = new ReportGenerator("PDF");
    csv_gen = new ReportGenerator("CSV");
    qDebug() << "Report generators initialized";
}

Report::~Report()
{
    delete ui;
    delete pdf_gen;
    delete csv_gen;
}

void Report::on_csvRadioBtn_clicked()
{
    qDebug() << "CSV radio button clicked";
    
    if (ppage && ppage->getGCCResult()) {
        gcc_res = ppage->getGCCResult();  // Store pointer
        qDebug() << "Got GCC result pointer from ProjectPage";
        qDebug() << "Tool name:" << QString::fromStdString(gcc_res->getToolName());
        qDebug() << "Vulnerability count:" << gcc_res->getVulnerabilityCount();
        
        // Display vulnerabilities in debug output
        const auto& vulns = gcc_res->getVulnerabilities();
        for (size_t i = 0; i < vulns.size(); i++) {
            qDebug() << "Vulnerability" << i + 1 << ":";
            qDebug() << "  Type:" << QString::fromStdString(vulns[i].getType());
            qDebug() << "  Line:" << vulns[i].getLine();
            qDebug() << "  Description:" << QString::fromStdString(vulns[i].getDescription());
            qDebug() << "  Severity:" << QString::fromStdString(vulns[i].getSeverity());
        }
    } else {
        qDebug() << "Warning: Unable to get GCC result from ProjectPage";
    }
}

void Report::on_jsonRadioBtn_clicked()
{
    qDebug() << "JSON radio button clicked";
    // Not implemented yet
}

void Report::on_DownloadBtn_clicked()
{
    qDebug() << "Download button clicked";
    
    if(ui->csvRadioBtn->isChecked()) {
        qDebug() << "CSV format selected";
        
        if (!gcc_res) {
            qDebug() << "Error: gcc_res is null";
            QMessageBox::warning(this, tr("Error"), tr("No analysis results available"));
            return;
        }
        
        qDebug() << "Adding analysis result to CSV generator";
        qDebug() << "Vulnerability count:" << gcc_res->getVulnerabilityCount();
        
        csv_gen->addAnalysisResult(*gcc_res);
        
        // Use file dialog to get save path
        QString savePath = QFileDialog::getSaveFileName(this,
            tr("Save CSV Report"),
            QDir::homePath(),
            tr("CSV Files (*.csv)"));
            
        if (!savePath.isEmpty()) {
            qDebug() << "Selected path:" << savePath;
            std::string outputPath = savePath.toStdString();
            
            qDebug() << "Exporting report to:" << savePath;
            csv_gen->exportReport(outputPath);
            
            QMessageBox::information(this, tr("Download Complete"), 
                tr("Report saved to: %1").arg(savePath));
                
            qDebug() << "Report saved successfully";
        } else {
            qDebug() << "No save path selected";
        }
    } else if(ui->jsonRadioBtn->isChecked()) {
        QMessageBox::information(this, tr("Info"), tr("JSON export not implemented yet"));
    } else {
        QMessageBox::warning(this, tr("Warning"), tr("Please select a report format"));
    }
}