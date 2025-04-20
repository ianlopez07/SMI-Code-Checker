#ifndef REPORT_H
#define REPORT_H

#include <QWidget>
#include "AnalysisResult.h"

namespace Ui {
class Report;
}

class Report : public QWidget
{
    Q_OBJECT

public:
    explicit Report(ProjectPage* ppage, QWidget *parent = nullptr);
    ~Report();

public:
    Ui::Report *ui;
private slots:

private:
    ProjectPage* m_ppage;
    AnalysisResult* gcc_res = nullptr;
};

#endif // REPORT_H
