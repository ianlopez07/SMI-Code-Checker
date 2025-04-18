/********************************************************************************
** Form generated from reading UI file 'projectpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTPAGE_H
#define UI_PROJECTPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectPage
{
public:
    QLabel *label;
    QCheckBox *GCC;
    QCheckBox *Flawfinder;
    QCheckBox *CPP;
    QPushButton *AnalyizeBtn;
    QLabel *analysisLabel;
    QProgressBar *progressBar;
    QPushButton *ReportspageBtn;

    void setupUi(QWidget *ProjectPage)
    {
        if (ProjectPage->objectName().isEmpty())
            ProjectPage->setObjectName("ProjectPage");
        ProjectPage->resize(639, 492);
        ProjectPage->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.282, y1:0.324, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));
        label = new QLabel(ProjectPage);
        label->setObjectName("label");
        label->setGeometry(QRect(50, 50, 541, 91));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);
        GCC = new QCheckBox(ProjectPage);
        GCC->setObjectName("GCC");
        GCC->setGeometry(QRect(220, 150, 161, 26));
        QFont font1;
        font1.setPointSize(12);
        font1.setUnderline(true);
        GCC->setFont(font1);
        GCC->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));
        Flawfinder = new QCheckBox(ProjectPage);
        Flawfinder->setObjectName("Flawfinder");
        Flawfinder->setGeometry(QRect(220, 190, 121, 26));
        Flawfinder->setFont(font1);
        Flawfinder->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));
        CPP = new QCheckBox(ProjectPage);
        CPP->setObjectName("CPP");
        CPP->setGeometry(QRect(220, 230, 161, 26));
        CPP->setFont(font1);
        CPP->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0.282, y1:0.324, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));\n"
"background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        AnalyizeBtn = new QPushButton(ProjectPage);
        AnalyizeBtn->setObjectName("AnalyizeBtn");
        AnalyizeBtn->setGeometry(QRect(230, 310, 131, 51));
        AnalyizeBtn->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));
        analysisLabel = new QLabel(ProjectPage);
        analysisLabel->setObjectName("analysisLabel");
        analysisLabel->setGeometry(QRect(190, 260, 211, 41));
        analysisLabel->setFont(font);
        analysisLabel->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));"));
        analysisLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        progressBar = new QProgressBar(ProjectPage);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(230, 370, 131, 23));
        progressBar->setAutoFillBackground(false);
        progressBar->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));
        progressBar->setValue(24);
        ReportspageBtn = new QPushButton(ProjectPage);
        ReportspageBtn->setObjectName("ReportspageBtn");
        ReportspageBtn->setGeometry(QRect(230, 410, 131, 51));
        ReportspageBtn->setStyleSheet(QString::fromUtf8("background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:1, stop:0 rgba(0, 0, 0, 0), stop:1 rgba(255, 255, 255, 0));\n"
"background-color: qlineargradient(spread:pad, x1:1, y1:1, x2:1, y2:1, stop:0.455399 rgba(0, 31, 22, 232), stop:1 rgba(144, 255, 238, 251));"));

        retranslateUi(ProjectPage);

        QMetaObject::connectSlotsByName(ProjectPage);
    } // setupUi

    void retranslateUi(QWidget *ProjectPage)
    {
        ProjectPage->setWindowTitle(QCoreApplication::translate("ProjectPage", "Form", nullptr));
        label->setText(QCoreApplication::translate("ProjectPage", "Please select which analysis tools you would like to use", nullptr));
        GCC->setText(QCoreApplication::translate("ProjectPage", "GCC -fanalyzer", nullptr));
        Flawfinder->setText(QCoreApplication::translate("ProjectPage", "Flawfinder", nullptr));
        CPP->setText(QCoreApplication::translate("ProjectPage", "CPPcheck", nullptr));
        AnalyizeBtn->setText(QCoreApplication::translate("ProjectPage", "Analyze", nullptr));
        analysisLabel->setText(QCoreApplication::translate("ProjectPage", "Click to begin analysis", nullptr));
        ReportspageBtn->setText(QCoreApplication::translate("ProjectPage", "Go to Reports Page", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectPage: public Ui_ProjectPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTPAGE_H
