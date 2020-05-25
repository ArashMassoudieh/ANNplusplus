/********************************************************************************
** Form generated from reading UI file 'plotterwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTTERWIDGET_H
#define UI_PLOTTERWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlotterWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *PlotterWidget)
    {
        if (PlotterWidget->objectName().isEmpty())
            PlotterWidget->setObjectName(QStringLiteral("PlotterWidget"));
        PlotterWidget->resize(521, 294);
        horizontalLayout = new QHBoxLayout(PlotterWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(PlotterWidget);

        QMetaObject::connectSlotsByName(PlotterWidget);
    } // setupUi

    void retranslateUi(QWidget *PlotterWidget)
    {
        PlotterWidget->setWindowTitle(QApplication::translate("PlotterWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlotterWidget: public Ui_PlotterWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTTERWIDGET_H
