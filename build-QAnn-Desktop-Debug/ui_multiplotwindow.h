/********************************************************************************
** Form generated from reading UI file 'multiplotwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MULTIPLOTWINDOW_H
#define UI_MULTIPLOTWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_MultiPlotWindow
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *MultiPlotWindow)
    {
        if (MultiPlotWindow->objectName().isEmpty())
            MultiPlotWindow->setObjectName(QStringLiteral("MultiPlotWindow"));
        MultiPlotWindow->resize(789, 556);
        verticalLayout_2 = new QVBoxLayout(MultiPlotWindow);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(MultiPlotWindow);

        QMetaObject::connectSlotsByName(MultiPlotWindow);
    } // setupUi

    void retranslateUi(QDialog *MultiPlotWindow)
    {
        MultiPlotWindow->setWindowTitle(QApplication::translate("MultiPlotWindow", "Dialog", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MultiPlotWindow: public Ui_MultiPlotWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MULTIPLOTWINDOW_H
