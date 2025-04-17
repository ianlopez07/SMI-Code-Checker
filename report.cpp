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

