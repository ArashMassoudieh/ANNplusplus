#include "tinydnnwrapper.h"
#include <iostream>
#include "runtimewindow.h"

using namespace std;
tinydnnwrapper::tinydnnwrapper()
{

}

bool tinydnnwrapper::addlayer(unsigned int n_source, unsigned int n_nodes, const string &activation_function)
{
    net << tiny_dnn::fully_connected_layer(n_source, n_nodes);
    net << tiny_dnn::tanh_layer();
}

bool tinydnnwrapper::createnetwork(const vector<unsigned int> &nodes)
{
    net << tiny_dnn::fully_connected_layer(nodes[0], nodes[1]);
    for (unsigned int i=1; i< nodes.size()-1; i++)
    {
        net << tiny_dnn::tanh_layer();
        net << tiny_dnn::fully_connected_layer(nodes[i], nodes[i+1]);
    }
    return true;

}

bool tinydnnwrapper::SetInput(CTimeSeriesSet &input)
{
    InputTimeSeries = input;
    Input.clear();
    for (unsigned int i=0; i<input.BTC[0].n; i++)
    {
        vector<double> values = input.getrow(i);
        tiny_dnn::vec_t t  = {float(input.BTC[0].t[i])};
        tiny_dnn::vec_t val(values.begin(),values.end());


        Input.push_back(val);
    }
    return true;
}


bool tinydnnwrapper::SetTarge(CTimeSeriesSet &input)
{
    OutputTimeSeries = input;
    Output.clear();
    for (unsigned int i=0; i<input.BTC[0].n; i++)
    {
        vector<double> values = input.getrow(i);
        tiny_dnn::vec_t t  = {float(input.BTC[0].t[i])};
        tiny_dnn::vec_t val(values.begin(),values.end());


        Output.push_back(val);
    }
    return true;
}

bool tinydnnwrapper::AppendtoInput(CTimeSeriesSet &input)
{
    for (unsigned int i=0; i<input.BTC[0].n; i++)
    {
        vector<double> values = input.getrow(i);
        tiny_dnn::vec_t t  = {float(input.BTC[0].t[i])};
        tiny_dnn::vec_t val(values.begin(),values.end());
        for (int j=0; j<input.nvars; j++)
            InputTimeSeries.BTC[j].append(input.BTC[j].t[i],values[j]);
        Input.push_back(val);
    }
    return true;
}

bool tinydnnwrapper::AppendtoInput(CVector &input)
{
    vector<double> values = input.vec;
    tiny_dnn::vec_t t  = {float(InputTimeSeries.BTC[0].n)};
    tiny_dnn::vec_t val(values.begin(),values.end());
    for (int j=0; j<input.num; j++)
       InputTimeSeries.BTC[j].append(InputTimeSeries.BTC[0].n,values[j]);
    Input.push_back(val);

    return true;
}

bool tinydnnwrapper::AppendtoTarge(CTimeSeriesSet &input)
{
    for (unsigned int i=0; i<input.BTC[0].n; i++)
    {
        vector<double> values = input.getrow(i);
        tiny_dnn::vec_t t  = {float(input.BTC[0].t[i])};
        tiny_dnn::vec_t val(values.begin(),values.end());
        for (int j=0; j<input.nvars; j++)
            OutputTimeSeries.BTC[j].append(input.BTC[j].t[i],values[j]);

        Output.push_back(val);
    }
    return true;
}

bool tinydnnwrapper::AppendtoTarge(CVector &target)
{
    vector<double> values = target.vec;
    tiny_dnn::vec_t t  = {float(OutputTimeSeries.BTC[0].n)};
    tiny_dnn::vec_t val(values.begin(),values.end());
    for (int j=0; j<target.num; j++)
       OutputTimeSeries.BTC[j].append(OutputTimeSeries.BTC[0].n,values[j]);

    Output.push_back(val);

    return true;
}

double tinydnnwrapper::loss()
{
    return net.get_loss<tiny_dnn::mse>(Input, Output);
}

bool tinydnnwrapper::train(RunTimeWindow *rtw)
{
    for (int i=0; i<epochs; i+=batch_size)
    {
        net.train_one_batch(opt,Input, Output, batch_size);
        if (i==0)
        {
            rtw->SetXRange(0,epochs);
            rtw->SetYRange(0,loss());
        }
        rtw->AddDataPoint(i,loss());
        rtw->SetProgress(double(i)/double(epochs));
        QCoreApplication::processEvents();
    }
}

bool tinydnnwrapper::trainonebatch(vector<state_value_pair> *state_value_pair ,int batch_size, RunTimeWindow *rtw)
{
    net.train_one_batch(opt,Input, Output, batch_size);
}

bool tinydnnwrapper::trainonebatch(int start, int batch_size, RunTimeWindow *rtw)
{
    net.train_one_batch(opt,Input, Output, batch_size, start);
}

CTimeSeriesSet tinydnnwrapper::predicted()
{
    CTimeSeriesSet Predicted(Output[0].size());
    for (unsigned int i = 0; i<Output.size(); i++)
    {
        tiny_dnn::vec_t t = {Input[i]};
        tiny_dnn::vec_t fPredicted  = net.predict(t);
        vector<double> value(fPredicted.begin(),fPredicted.end());
        Predicted.append(OutputTimeSeries.BTC[0].t[i],value);
    }
    return Predicted;
}

CVector tinydnnwrapper::predicted(const CVector &input)
{


    tiny_dnn::vec_t t;
    for (unsigned int i=0; i<input.num; i++)
        t.push_back(input[i]);
    tiny_dnn::vec_t fPredicted  = net.predict(t);
    vector<double> value(fPredicted.begin(),fPredicted.end());

    CVector Predicted(value);
    return Predicted;
}


bool tinydnnwrapper::batchtrain(const std::vector<tiny_dnn::tensor_t> &inputs,
                                const std::vector<tiny_dnn::tensor_t> &desired_outputs,
                                size_t batch_size, int epoch, const bool reset_weights, const int n_threads, const std::vector<tiny_dnn::tensor_t> &t_cost)
{
    //net.check_target_cost_matrix(desired_outputs, t_cost);
    //set_netphase(net_phase::train);
    //net_.setup(reset_weights);

}
