/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *UploadFileBtn;
    QLabel *label;
    QLabel *label_2;
    QLabel *GoprojectPage;
    QPushButton *ProjectPageBtn;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QString::fromUtf8(";\n"
"background-color: qlineargradient(spread:pad, x1:0.282, y1:0.324, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        UploadFileBtn = new QPushButton(centralwidget);
        UploadFileBtn->setObjectName("UploadFileBtn");
        UploadFileBtn->setGeometry(QRect(330, 210, 111, 71));
        UploadFileBtn->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(210, 150, 341, 41));
        QFont font;
        font.setPointSize(15);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 10, 631, 101));
        QFont font1;
        font1.setPointSize(26);
        font1.setBold(true);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));
        GoprojectPage = new QLabel(centralwidget);
        GoprojectPage->setObjectName("GoprojectPage");
        GoprojectPage->setGeometry(QRect(150, 290, 481, 61));
        QFont font2;
        font2.setPointSize(12);
        GoprojectPage->setFont(font2);
        GoprojectPage->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));
        GoprojectPage->setAlignment(Qt::AlignmentFlag::AlignCenter);
        ProjectPageBtn = new QPushButton(centralwidget);
        ProjectPageBtn->setObjectName("ProjectPageBtn");
        ProjectPageBtn->setGeometry(QRect(310, 370, 171, 41));
        ProjectPageBtn->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        UploadFileBtn->setText(QCoreApplication::translate("MainWindow", "UpLoad File", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", " To begin please Upload a File", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Welcome to SMI Code Checker!", nullptr));
        GoprojectPage->setText(QCoreApplication::translate("MainWindow", "Once file is uploaded please proceed to project page", nullptr));
        ProjectPageBtn->setText(QCoreApplication::translate("MainWindow", "Go to Project Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
