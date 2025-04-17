#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "projectpage.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QFile>
#include <Qlabel>
#include <QTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //setting up the UI
    ui->setupUi(this);
    //When Project page button is clicked it will open a new window to project page
   ProjectPage *FormForm = new ProjectPage;
   connect(ui ->ProjectPageBtn, SIGNAL(clicked(bool)),this, SLOT(hide()));
   connect(ui ->ProjectPageBtn, SIGNAL(clicked(bool)),FormForm, SLOT(show()));

//Sets project page button and the go project page label to visibilty to false
    ui->ProjectPageBtn->setVisible(false);
    ui->GoprojectPage->setVisible(false);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_UploadFileBtn_clicked()
{
    //When Upload file button is clicked it will open the file explorer
    QString File_name = QFileDialog::getOpenFileName(this, "Upload File", QDir::homePath());
    QMessageBox::information(this, "...", File_name);

    //If the file that the user uploads is empty display "no file selected"
    if (!File_name.isEmpty()) {
        //If the file exists or the user has uploaded a file it will display "file has ben successfully uploaded"
        if (QFile::exists(File_name)) {
            // File exists, process it
            processFile(File_name);
            QMessageBox::information(this, "File has been Successfully uploaded", File_name);
            ui->GoprojectPage->setVisible(true);
            ui->ProjectPageBtn->setVisible(true);

        } else { //If file doesn't exit then it will display "File not found"
            // File does not exist
            QMessageBox::warning(this, tr("Error"), tr("File not found!"));
        }
    } else {
        // No file selected
        QMessageBox::information(this, tr("Info"), tr("No file selected."));
    }

}
void MainWindow::processFile(const QString& File_name) {
    //Reads the file
    QFile file(File_name);
    //if the file is not text it will display "could not open file"
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        file.close();
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Could not open file!"));
    }
}


void MainWindow::on_ProjectPageBtn_clicked()
{

}

