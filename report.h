#ifndef REPORT_H
#define REPORT_H

#include <QWidget>

namespace Ui {
class Report;
}

class Report : public QWidget
{
    Q_OBJECT

public:
    explicit Report(QWidget *parent = nullptr);
    ~Report();

public:
    Ui::Report *ui;
private slots:

};

#endif // REPORT_H
