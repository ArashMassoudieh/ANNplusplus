/********************************************************************************
** Form generated from reading UI file 'plotter.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLOTTER_H
#define UI_PLOTTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Plotter
{
public:
    QAction *actionAdd_Data_File;
    QAction *actionLegend;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *Plotter)
    {
        if (Plotter->objectName().isEmpty())
            Plotter->setObjectName(QStringLiteral("Plotter"));
        Plotter->resize(783, 547);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(20);
        sizePolicy.setVerticalStretch(20);
        sizePolicy.setHeightForWidth(Plotter->sizePolicy().hasHeightForWidth());
        Plotter->setSizePolicy(sizePolicy);
        actionAdd_Data_File = new QAction(Plotter);
        actionAdd_Data_File->setObjectName(QStringLiteral("actionAdd_Data_File"));
        actionLegend = new QAction(Plotter);
        actionLegend->setObjectName(QStringLiteral("actionLegend"));
        centralWidget = new QWidget(Plotter);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout->addLayout(verticalLayout_2);

        Plotter->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Plotter);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 783, 21));
        Plotter->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Plotter);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Plotter->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Plotter);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Plotter->setStatusBar(statusBar);
        toolBar = new QToolBar(Plotter);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        Plotter->addToolBar(Qt::TopToolBarArea, toolBar);

        toolBar->addAction(actionLegend);

        retranslateUi(Plotter);

        QMetaObject::connectSlotsByName(Plotter);
    } // setupUi

    void retranslateUi(QMainWindow *Plotter)
    {
        Plotter->setWindowTitle(QApplication::translate("Plotter", "Model Results", Q_NULLPTR));
        actionAdd_Data_File->setText(QApplication::translate("Plotter", "Add Data File", Q_NULLPTR));
        actionLegend->setText(QApplication::translate("Plotter", "Legend", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        actionLegend->setToolTip(QApplication::translate("Plotter", "Legend", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        toolBar->setWindowTitle(QApplication::translate("Plotter", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Plotter: public Ui_Plotter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLOTTER_H