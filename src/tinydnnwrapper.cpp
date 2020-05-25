#include "tinydnnwrapper.h"
#include <iostream>


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



        Input.push_back(val);
    }
    return true;
}

bool tinydnnwrapper::AppendtoTarge(CTimeSeriesSet &input)
{
    for (unsigned int i=0; i<input.BTC[0].n; i++)
    {
        vector<double> values = input.getrow(i);
        tiny_dnn::vec_t t  = {float(input.BTC[0].t[i])};
        tiny_dnn::vec_t val(values.begin(),values.end());


        Output.push_back(val);
    }
    return true;
}

double tinydnnwrapper::loss()
{
    return net.get_loss<tiny_dnn::mse>(Input, Output);
}

bool tinydnnwrapper::train()
{
    return net.fit<tiny_dnn::mse>(opt, Input, Output, batch_size, epochs, []() {}, []() {});
}

CTimeSeriesSet tinydnnwrapper::predicted()
{
    CTimeSeriesSet Predicted(Output[0].size());
    for (unsigned int i = 0; i<Output.size(); i++)
    {
        tiny_dnn::vec_t t = {Input[i]};
        tiny_dnn::vec_t fPredicted  = net.predict(t);
        vector<double> value(fPredicted.begin(),fPredicted.end());
        Predicted.append(t[0],value);
    }
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
