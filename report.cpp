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
    
    if (ppage) {
        gcc_res = ppage->getGCCResult();
        cppcheck_res = ppage->getCPPCheckResult();
        flawfinder_res = ppage->getFlawfinderResult();
        
        qDebug() << "Results obtained from ProjectPage:";
        qDebug() << "- GCC: " << (gcc_res ? gcc_res->getVulnerabilityCount() : 0) << " vulnerabilities";
        qDebug() << "- CPPCheck: " << (cppcheck_res ? cppcheck_res->getVulnerabilityCount() : 0) << " vulnerabilities";
        qDebug() << "- Flawfinder: " << (flawfinder_res ? flawfinder_res->getVulnerabilityCount() : 0) << " vulnerabilities";
    } else {
        qDebug() << "Warning: ProjectPage pointer is null";
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
        
        // Add all available results
        bool hasResults = false;
        
        if (gcc_res && gcc_res->getVulnerabilityCount() > 0) {
            csv_gen->addAnalysisResult(*gcc_res);
            hasResults = true;
            qDebug() << "Added" << gcc_res->getVulnerabilityCount() << "GCC vulnerabilities";
        }

        if (flawfinder_res && flawfinder_res->getVulnerabilityCount() > 0) {
            csv_gen->addAnalysisResult(*flawfinder_res);
            hasResults = true;
            qDebug() << "Added" << flawfinder_res->getVulnerabilityCount() << "Flawfinder vulnerabilities";
        }
        
        if (cppcheck_res && cppcheck_res->getVulnerabilityCount() > 0) {
            csv_gen->addAnalysisResult(*cppcheck_res);
            hasResults = true;
            qDebug() << "Added" << cppcheck_res->getVulnerabilityCount() << "CPPCheck vulnerabilities";
        }
        
        if (!hasResults) {
            QMessageBox::warning(this, tr("Warning"), tr("No vulnerabilities found to report"));
            return;
        }
        
        // Use file dialog to get save path
        QString savePath = QFileDialog::getSaveFileName(this,
            tr("Save CSV Report"),
            QDir::homePath(),
            tr("CSV Files (*.csv)"));
            
        if (!savePath.isEmpty()) {
            // Make sure the path has .csv extension
            if (!savePath.endsWith(".csv", Qt::CaseInsensitive)) {
                savePath += ".csv";
            }
            
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
    }
}