#ifndef PROJECTPAGE_H
#define PROJECTPAGE_H

#include <QWidget>

namespace Ui {
class ProjectPage;
}

class ProjectPage : public QWidget
{
    Q_OBJECT

public:
    explicit ProjectPage(QWidget *parent = nullptr);
    ~ProjectPage();

public:
    Ui::ProjectPage *ui;
private slots:

    void on_AnalyizeBtn_clicked();
    void on_GCC_checkStateChanged(const Qt::CheckState &arg1);
    void on_Flawfinder_checkStateChanged(const Qt::CheckState &arg1);
    void on_CPP_checkStateChanged(const Qt::CheckState &arg1);
};

#endif // PROJECTPAGE_H
