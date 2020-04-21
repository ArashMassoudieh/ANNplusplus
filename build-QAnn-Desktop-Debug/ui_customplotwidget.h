/********************************************************************************
** Form generated from reading UI file 'customplotwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMPLOTWIDGET_H
#define UI_CUSTOMPLOTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CustomPlotWidget
{
public:
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *CustomPlotWidget)
    {
        if (CustomPlotWidget->objectName().isEmpty())
            CustomPlotWidget->setObjectName(QStringLiteral("CustomPlotWidget"));
        CustomPlotWidget->resize(548, 300);
        horizontalLayout = new QHBoxLayout(CustomPlotWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));

        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(CustomPlotWidget);

        QMetaObject::connectSlotsByName(CustomPlotWidget);
    } // setupUi

    void retranslateUi(QWidget *CustomPlotWidget)
    {
        CustomPlotWidget->setWindowTitle(QApplication::translate("CustomPlotWidget", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CustomPlotWidget: public Ui_CustomPlotWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMPLOTWIDGET_H
