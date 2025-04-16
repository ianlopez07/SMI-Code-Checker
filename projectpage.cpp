#include "projectpage.h"
#include "ui_projectpage.h"

Projectpage::Projectpage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Projectpage)
{
    ui->setupUi(this);
}

Projectpage::~Projectpage()
{
    delete ui;
}
