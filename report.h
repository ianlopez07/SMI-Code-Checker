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

    void on_csvRadioBtn_clicked();
    void on_jsonRadioBtn_clicked();
    void on_DownloadBtn_clicked();
};

#endif // REPORT_H
