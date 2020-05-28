#include "multiplotwindow.h"
#include "ui_multiplotwindow.h"
#include "customplotwidget.h"


MultiPlotWindow::MultiPlotWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultiPlotWindow)
{
    ui->setupUi(this);


}

MultiPlotWindow::MultiPlotWindow(int n_panels, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MultiPlotWindow)
{
    ui->setupUi(this);
    for (int i=0; i<n_panels; i++)
    {
        CustomPlotWidget *plot = new CustomPlotWidget(this);
        ui->verticalLayout->addWidget(plot);
        plot->setObjectName(QStringLiteral("customPlot"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(2);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(plot->sizePolicy().hasHeightForWidth());
        plot->setSizePolicy(sizePolicy2);
        plot->Plot()->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes | QCP::iSelectLegend | QCP::iSelectPlottables);
        plots.push_back(plot);

    }

}


MultiPlotWindow::~MultiPlotWindow()
{
    delete ui;
}
