#include "mainwindow.h"
#include "./ui_mainwindow.h"
//#include "projectpage.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <Qlabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
   // ui->setupUi(this);
    //Projectpage *FormForm = new Projectpage;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString File_name = QFileDialog::getOpenFileName(this, "Upload File", QDir::homePath());
    QMessageBox::information(this, "...", File_name);

    if (!File_name.isEmpty()) {
        if (QFile::exists(File_name)) {
            // File exists, process it
            processFile(File_name);
            //QMessageBox::information(this, "File has been Successfully uploaded", File_name);
            QLabel *Upload = new QLabel(this);
            Upload->setText("File has been Successfully uploaded");
        } else {
            // File does not exist
            QMessageBox::warning(this, tr("Error"), tr("File not found!"));
        }
    } else {
        // No file selected
        QMessageBox::information(this, tr("Info"), tr("No file selected."));
    }
}
void MainWindow::processFile(const QString& File_name) {
    QFile file(File_name);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        file.close();
        // Do something with the file content
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file!"));
    }


}



