/********************************************************************************
** Form generated from reading UI file 'runtimewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RUNTIMEWINDOW_H
#define UI_RUNTIMEWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RunTimeWindow
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QTextBrowser *textBrowser;
    QProgressBar *progressBar;
    QProgressBar *optprogressBar;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonStop;
    QPushButton *ShowDetails;
    QTextBrowser *textBrowserdetails;

    void setupUi(QDialog *RunTimeWindow)
    {
        if (RunTimeWindow->objectName().isEmpty())
            RunTimeWindow->setObjectName(QStringLiteral("RunTimeWindow"));
        RunTimeWindow->resize(617, 440);
        verticalLayout = new QVBoxLayout(RunTimeWindow);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        textBrowser = new QTextBrowser(RunTimeWindow);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        horizontalLayout->addWidget(textBrowser);

        horizontalLayout->setStretch(0, 1);

        verticalLayout->addLayout(horizontalLayout);

        progressBar = new QProgressBar(RunTimeWindow);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout->addWidget(progressBar);

        optprogressBar = new QProgressBar(RunTimeWindow);
        optprogressBar->setObjectName(QStringLiteral("optprogressBar"));
        optprogressBar->setValue(0);

        verticalLayout->addWidget(optprogressBar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButtonStop = new QPushButton(RunTimeWindow);
        pushButtonStop->setObjectName(QStringLiteral("pushButtonStop"));

        horizontalLayout_2->addWidget(pushButtonStop);

        ShowDetails = new QPushButton(RunTimeWindow);
        ShowDetails->setObjectName(QStringLiteral("ShowDetails"));

        horizontalLayout_2->addWidget(ShowDetails);


        verticalLayout->addLayout(horizontalLayout_2);

        textBrowserdetails = new QTextBrowser(RunTimeWindow);
        textBrowserdetails->setObjectName(QStringLiteral("textBrowserdetails"));

        verticalLayout->addWidget(textBrowserdetails);


        retranslateUi(RunTimeWindow);

        QMetaObject::connectSlotsByName(RunTimeWindow);
    } // setupUi

    void retranslateUi(QDialog *RunTimeWindow)
    {
        RunTimeWindow->setWindowTitle(QApplication::translate("RunTimeWindow", "Running Status", nullptr));
        pushButtonStop->setText(QApplication::translate("RunTimeWindow", "Stop Simulation", nullptr));
        ShowDetails->setText(QApplication::translate("RunTimeWindow", "Show details", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RunTimeWindow: public Ui_RunTimeWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RUNTIMEWINDOW_H
