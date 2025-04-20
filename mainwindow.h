#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "SourceCodeFile.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    SourceCodeFile* getFile() { return &inpFile; }

private slots:
    void on_UploadFileBtn_clicked();
    void processFile(const QString& File_name);

    void on_ProjectPageBtn_clicked();

private:
    Ui::MainWindow *ui;
    SourceCodeFile inpFile{"null"};
};
#endif // MAINWINDOW_H
