#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include "ML.h"
#include "plotter.h"
#include "multiplotwindow.h"
#include "runtimewindow.h"
#include "System.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButtontrain, SIGNAL(clicked()),this, SLOT(on_train()));
    connect(ui->pushButtonRunODEModel,SIGNAL(clicked()),this,SLOT(on_runODE()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_train()
{
    traintiny();
}

void MainWindow::on_runODE()
{
    runODE();
}


void MainWindow::runODE(model modelID)
{
    ui->textBrowser_2->append("Started Running the model");
    System *sys = new System();
    if (modelID == model::fish)
    {

        StateVariable Prey;
        Prey.SetName("Prey");
        Prey.SetValue(1,Expression::timing::both);
        StateVariable Predator;
        Predator.SetName("Predator");
        Predator.SetValue(0.2,Expression::timing::both);

        Parameter k1, k2, k3, k4, k5,harvesting_coeff;
        k1.SetName("k1"); k1.SetValue(1,Expression::timing::both); sys->AppendParameter(k1);
        k2.SetName("k2"); k2.SetValue(0.7,Expression::timing::both); sys->AppendParameter(k2);
        k3.SetName("k3"); k3.SetValue(0.05,Expression::timing::both); sys->AppendParameter(k3);
        k4.SetName("k4"); k4.SetValue(0.2,Expression::timing::both); sys->AppendParameter(k4);
        k5.SetName("k5"); k5.SetValue(0.12,Expression::timing::both); sys->AppendParameter(k5);
        harvesting_coeff.SetName("k_h"); harvesting_coeff.SetValue(0.12,Expression::timing::both); sys->AppendParameter(harvesting_coeff);

        ExternalForcing E1;
        E1.SetName("Growthrate");
        E1.TimeSeries()->readfile("/home/arash/Projects/ODE_Learn/GrowthRate.txt");
        sys->AppendState(Prey);
        sys->AppendState(Predator);
        sys->AppendExternalForcing(E1);

        Expression preyrateofchange("(k1*Prey*Growthrate) - (k2*Prey*Predator) - (k3*Prey) - (k_h*Prey)",sys);
        Expression predatorrateofchange("(k4*Predator*Prey) - (k5*Predator)",sys);
        sys->state("Prey")->SetRateOfChange(preyrateofchange);
        sys->state("Predator")->SetRateOfChange(predatorrateofchange);
        RewardFunction R1;
        R1.SetName("Harvest");

        sys->AppendReward(R1);
        sys->reward("Harvest")->SetImmediateRewardFunction("k_h*Prey");
        cout<<preyrateofchange.calc(sys,Expression::timing::past)<<endl;
        cout<<predatorrateofchange.calc(sys,Expression::timing::past)<<endl;
        sys->SetProp("tstart",0);
        sys->SetProp("tend",30);
        sys->SetProp("dt",0.01);
        sys->Solve();
        sys->Outputs.AllOutputs.writetofile("Output.txt",true);
        Plotter *plt = new Plotter(this);
        plt->AddData(sys->Outputs.AllOutputs.BTC[0]);
        plt->AddData(sys->Outputs.AllOutputs.BTC[1]);
        plt->AddData(sys->Outputs.AllOutputs.BTC[2]);
        plt->AddData(sys->Outputs.AllOutputs.BTC[3]);
        plt->show();
    }
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


