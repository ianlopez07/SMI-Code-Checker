#include "report.h"
#include "ui_report.h"

Report::Report(QWidget *parent)
    : QWidget(parent)
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

}


void Report::on_jsonRadioBtn_clicked()
{

}


void Report::on_DownloadBtn_clicked()
{

}

