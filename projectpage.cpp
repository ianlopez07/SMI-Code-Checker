#include "projectpage.h"
#include "ui_projectpage.h"
#include "report.h"
#include "mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QMessageBox>

ProjectPage::ProjectPage(MainWindow* mainw, QWidget *parent)
    : QWidget(parent), m_mainw(mainw)
    , ui(new Ui::ProjectPage)
{
    //setting up the UI
    ui->setupUi(this);
    //When Reports page button is clicked it will open a new window to reports page
    Report *ReportForm = new Report(this, nullptr);
    connect(ui ->ReportspageBtn, SIGNAL(clicked(bool)),this, SLOT(hide()));
    connect(ui ->ReportspageBtn, SIGNAL(clicked(bool)),ReportForm, SLOT(show()));

    //Sets the progress bar, reports page button, and anaylize button's visibility to false
    ui->progressBar->setVisible(false);
    ui->ReportspageBtn->setVisible(false);
    ui->AnalyizeBtn->setVisible(false);
    ui->analysisLabel->setVisible(false);
    //if analyize button is clicked it points to the function on_AnalyizeBtn_clicked
    connect(ui->AnalyizeBtn, &QPushButton::clicked, this, &ProjectPage::on_AnalyizeBtn_clicked);

    // Get the file from MainWindow
    if (m_mainw) {
        file = m_mainw->getFile();  // Store pointer instead of copying
        qDebug() << "Got file pointer from MainWindow";
    } else {
        qDebug() << "Warning: MainWindow pointer is null";
    }
    
    // Initialize the analysis tool with more descriptive parameters
    gcc = GCCAnalyzer("GCC", "latest", "text");
    qDebug() << "GCC analyzer initialized";
}

ProjectPage::~ProjectPage()
{
    delete ui;
}

void ProjectPage::on_AnalyizeBtn_clicked()
{
    qDebug() << "Analyze button clicked";
    
    //Sets the visibility to the progress bar as true
    ui->progressBar->setVisible(true);
    //Sets the range of the progress bar from 0 to 100
    ui->progressBar->setRange(0, 100);
    //Sets the starting value of the progress bar to 0
    ui->progressBar->setValue(0);

    // Check if file is valid
    if (file) {
        qDebug() << "File is valid, path:" << QString::fromStdString(file->getFilePath());
    } else {
        qDebug() << "Error: File pointer is null";
        QMessageBox::warning(this, tr("Error"), tr("No file selected for analysis"));
        return;
    }

    //Intializes time and points to a new timer
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [this, timer]()
    {
        //Sets the porgress variabler to 0
        static int progress = 0;
        //incremenets progress by 10
        progress +=10;
        //Sets the setValue to progress
        ui->progressBar->setValue(progress);

        //If progress reaches 100 it will stop and delete the timer
        if(progress >= 100){
            timer->stop();
            timer->deleteLater();
            //Sets the progress bar's visibility to false and reports page button's visibility to true
            ui->progressBar->setVisible(false);
            ui->ReportspageBtn->setVisible(true);
        }
    });
    timer->start(500);

    // Run the selected analysis tools
    if(ui->GCC->isChecked()) {
        qDebug() << "Running GCC analysis...";
        gcc_result = gcc.runAnalysis(*file);
        qDebug() << "GCC analysis completed. Found" << gcc_result.getVulnerabilityCount() << "vulnerabilities";
        
        // Output each vulnerability for debugging
        const auto& vulns = gcc_result.getVulnerabilities();
        for (size_t i = 0; i < vulns.size(); i++) {
            qDebug() << "Vulnerability" << i + 1 << ":";
            qDebug() << "  Type:" << QString::fromStdString(vulns[i].getType());
            qDebug() << "  Line:" << vulns[i].getLine();
            qDebug() << "  Description:" << QString::fromStdString(vulns[i].getDescription());
            qDebug() << "  Severity:" << QString::fromStdString(vulns[i].getSeverity());
        }
    }
}

void ProjectPage::on_GCC_checkStateChanged(const Qt::CheckState &arg1)
{
    if(ui->GCC->isChecked()){
        ui->AnalyizeBtn->setVisible(true);
        ui->analysisLabel->setVisible(true);
    }
    else if(!(ui->GCC->isChecked())&&!(ui->Flawfinder->isChecked())&&!(ui->CPP->isChecked())){
        ui->AnalyizeBtn->setVisible(false);
        ui->analysisLabel->setVisible(false);
    }
}


void ProjectPage::on_Flawfinder_checkStateChanged(const Qt::CheckState &arg1)
{
    if(ui->Flawfinder->isChecked()){
        ui->AnalyizeBtn->setVisible(true);
        ui->analysisLabel->setVisible(true);
    }
    else if(!(ui->GCC->isChecked())&&!(ui->Flawfinder->isChecked())&&!(ui->CPP->isChecked())){
        ui->AnalyizeBtn->setVisible(false);
        ui->analysisLabel->setVisible(false);
    }
}


void ProjectPage::on_CPP_checkStateChanged(const Qt::CheckState &arg1)
{
    if(ui->CPP->isChecked()){
        ui->AnalyizeBtn->setVisible(true);
        ui->analysisLabel->setVisible(true);
    }
    else if(!(ui->GCC->isChecked())&&!(ui->Flawfinder->isChecked())&&!(ui->CPP->isChecked())){
        ui->AnalyizeBtn->setVisible(false);
        ui->analysisLabel->setVisible(false);
    }
}

