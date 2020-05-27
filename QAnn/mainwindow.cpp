#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include "ML.h"
#include "plotter.h"
#include "multiplotwindow.h"
#include "runtimewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    traintiny();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::traintiny()
{
    RunTimeWindow *rtw = new RunTimeWindow(this);
    rtw->show();
    tinydnnwrapper tdn;
    vector<unsigned int> config = {2,10,10,1};
    tdn.createnetwork(config);
    CTimeSeriesSet Sininput(2);
    CTimeSeriesSet Sintarget(1);
    int i = 0;
    for (double x = -1.0; x<=1; x+=0.1f)
        for (double y = -1.0; y<=1; y+=0.1f)
            {
                i++;
                bool x1 = (x>0)?1:0;
                bool y1 = (y>0)?1:0;
                Sininput.BTC[0].append(i,x);
                Sininput.BTC[1].append(i,y);
                Sintarget.BTC[0].append(i,x1!=y1);
            }
    tdn.SetInput(Sininput);
    tdn.SetTarge(Sintarget);
    tdn.epochs = 5000;
    tdn.train(rtw);
    Sintarget.setname(0, "Data");
    CTimeSeriesSet Predicted=tdn.predicted();
    Predicted.setname(0,"Predicted");
    Plotter *plt = new Plotter(this);
    plt->AddData(Sintarget.BTC[0]);
    plt->AddData(Predicted.BTC[0]);
    plt->show();


}


