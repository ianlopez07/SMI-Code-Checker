#include "report.h"
#include "ui_report.h"
#include "projectpage.h"

Report::Report(ProjectPage* ppage, QWidget *parent)
    : QWidget(parent), m_ppage(ppage),
    , ui(new Ui::Report)
{
    ui->setupUi(this);

    if (m_ppage->gcc_result) {
        gcc_res = m_ppage->gcc_result;
    }
}

Report::~Report()
{
    delete ui;
}

