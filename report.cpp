#include "report.h"
#include "ui_report.h"
#include "projectpage.h"

Report::Report(ProjectPage* page, QWidget *parent)
    : QWidget(parent), ppage(page)
    , ui(new Ui::Report)
{
    ui->setupUi(this);

    if (ppage->getGCCResult()) {
        gcc_res = ppage->getGCCResult();  // Store pointer instead of copying
    }
}

Report::~Report()
{
    delete ui;
}


void Report::on_csvRadioBtn_clicked()
{

}


void Report::on_jsonRadioBtn_clicked()
{

}


void Report::on_DownloadBtn_clicked()
{
    if(ui->csvRadioBtn->isChecked()) {
        csv_gen->exportReport("C:/Users/iancl/OneDrive/Documents/");
    }
}

