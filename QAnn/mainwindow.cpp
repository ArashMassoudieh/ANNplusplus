#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utils.h"
#include "ML.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    train();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::train()
{
    vector<int> layers(3);
    layers[0] = 1;
    layers[1] = 1;
    layers[2] = 1;
    ANN_class ANN(layers,CNode::activationfunc::one);
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
        input_ts.BTC[0].append((i-100.0)/100.0);

    ANN.input = &input_ts;

    CVector OBS = ANN.calc_output_v(weights);
    CBTCSet OBS_BTC;
    OBS_BTC.append(CTimeSeries(OBS));

    ANN.training_data = OBS_BTC;
    CBTC(OBS).writefile("observed.txt");

    ANN.SetLearningRate(0.01);
    for (int i=0; i<10000; i++)
    {
        double err = ANN.PerformSingleStepStochasticSteepestDescent(10);
        ui->textBrowser->append( QString::fromStdString(ANN.weights_to_vector().toString()) + ", Err = " + QString::number(err) );
    }

    weights = 0;

    ANN.setparams(weights);

}
