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

void Report::on_pdfRadioBtn_clicked()
{
    qDebug() << "PDF radio button clicked";

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

    // Check which format is selected
    if (ui->csvRadioBtn->isChecked()) {
        qDebug() << "CSV format selected";

        // Clear and fetch new results
        bool hasResults = false;

        if (gcc_res && gcc_res->getVulnerabilityCount() > 0) {
            csv_gen->addAnalysisResult(*gcc_res);
            hasResults = true;
        }

        if (cppcheck_res && cppcheck_res->getVulnerabilityCount() > 0) {
            csv_gen->addAnalysisResult(*cppcheck_res);
            hasResults = true;
        }

        if (flawfinder_res && flawfinder_res->getVulnerabilityCount() > 0) {
            csv_gen->addAnalysisResult(*flawfinder_res);
            hasResults = true;
        }

        if (!hasResults) {
            QMessageBox::warning(this, tr("Warning"), tr("No vulnerabilities found to report"));
            return;
        }

        QString savePath = QFileDialog::getSaveFileName(this,
            tr("Save CSV Report"),
            QDir::homePath(),
            tr("CSV Files (*.csv)"));

        if (!savePath.isEmpty()) {
            if (!savePath.endsWith(".csv", Qt::CaseInsensitive)) {
                savePath += ".csv";
            }

            csv_gen->exportReport(savePath.toStdString());

            QMessageBox::information(this, tr("Download Complete"),
                tr("CSV Report saved to: %1").arg(savePath));

            delete csv_gen;
            csv_gen = new ReportGenerator("CSV");
        }
    }
    else if (ui->pdfRadioBtn->isChecked()) {
        qDebug() << "PDF format selected";

        bool hasResults = false;

        if (gcc_res && gcc_res->getVulnerabilityCount() > 0) {
            pdf_gen->addAnalysisResult(*gcc_res);
            hasResults = true;
        }

        if (cppcheck_res && cppcheck_res->getVulnerabilityCount() > 0) {
            pdf_gen->addAnalysisResult(*cppcheck_res);
            hasResults = true;
        }

        if (flawfinder_res && flawfinder_res->getVulnerabilityCount() > 0) {
            pdf_gen->addAnalysisResult(*flawfinder_res);
            hasResults = true;
        }

        if (!hasResults) {
            QMessageBox::warning(this, tr("Warning"), tr("No vulnerabilities found to report"));
            return;
        }

        QString savePath = QFileDialog::getSaveFileName(this,
            tr("Save PDF Report"),
            QDir::homePath(),
            tr("PDF Files (*.pdf)"));

        if (!savePath.isEmpty()) {
            if (!savePath.endsWith(".pdf", Qt::CaseInsensitive)) {
                savePath += ".pdf";
            }

            pdf_gen->exportReport(savePath.toStdString());

            QMessageBox::information(this, tr("Download Complete"),
                tr("PDF Report saved to: %1").arg(savePath));

            delete pdf_gen;
            pdf_gen = new ReportGenerator("PDF");
        }
    }
    else {
        QMessageBox::warning(this, tr("Warning"), tr("Please select a format (.csv or .pdf)"));
    }
}
