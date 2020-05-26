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
    for (double x = -1; x<=1; x+=0.1f)
        for (double y = -1; y<=1; y+=0.1f)
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

void MainWindow::train()
{
    vector<int> layers(3);
    layers[0] = 1;
    layers[1] = 1;
    layers[2] = 1;
    ANN_class ANN(layers,CNode::activationfunc::sigmoid);
    vector<double> input(1);
    input[0] = 1;

    CVector weights;
    for (int i = 0; i < ANN.num_weights(); i++)
        weights.append(1);



    ANN.ApplyWeights(weights);
    vector<double> out = ANN.calc_output(input);
    ui->textBrowser->append(aquiutils::vec2Qstring(out));
    CMatrix X = ANN.UpdateDerivatives(input);

    CMatrix X1 = ANN.Gradient_direct(input);
    CBTCSet input_ts(1);
    for (int i = 0; i < 200; i++)
        input_ts.BTC[0].append(i,(i-100.0)/100.0);

    ANN.input = &input_ts;
    CVector OBS = ANN.calc_output_v(weights);
    CBTCSet OBS_BTC;
    OBS_BTC.append(CTimeSeries(OBS));

    ANN.training_data = OBS_BTC;
    weights = 0.2;
    ANN.ApplyWeights(weights);

    CBTC(OBS).writefile("observed.txt");

    ANN.SetLearningRate(0.01);
    Plotter *plotter = new Plotter(this);
    for (int i=0; i<1000; i++)
    {
        double err = ANN.PerformSingleStepSteepestDescent();
        double errall = ANN.calc_error(&input_ts,&ANN.training_data);
        ui->textBrowser->append( QString::fromStdString(ANN.weights_to_vector().toString()) + ", Err = " + QString::number(err) + ", Err All = " + QString::number(errall));
    }

    CTimeSeriesSet output=ANN.output();
    output.setname(0,"predicted");
    ANN.training_data.setname(0,"mesured");
    plotter->AddData(*ANN.ErrorSeries());
    //plotter->AddData(output.BTC[0]);
    //plotter->AddData(ANN.training_data.BTC[0]);
    plotter->show();
    weights = 0;
    MultiPlotWindow *multiplot = new MultiPlotWindow(4,this);
    multiplot->show();

    ANN.setparams(weights);

}
