#include "projectpage.h"
#include "ui_projectpage.h"
#include "report.h"
#include "mainwindow.h"
#include <QTimer>

ProjectPage::ProjectPage(MainWindow* mainw, QWidget *parent)
    : QWidget(parent), m_mainw(mainw)
    , ui(new Ui::ProjectPage)
{
    //setting up the UI
    ui->setupUi(this);
    //When Reports page button is clicked it will open a new window to reports page
    Report *ReportForm = new Report;
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
    }
}

ProjectPage::~ProjectPage()
{
    delete ui;
}

void ProjectPage::on_AnalyizeBtn_clicked()
{
    //Sets the visibility to the progress bar as true
    ui->progressBar->setVisible(true);
    //Sets the range of the progress bar from 0 to 100
    ui->progressBar->setRange(0, 100);
    //Sets the starting value of the progress bar to 0
    ui->progressBar->setValue(0);

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

    if(ui->GCC->isChecked()) {
        AnalysisResult gcc_result = gcc.runAnalysis(*file);
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

