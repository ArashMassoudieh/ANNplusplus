#ifndef TINYDNNWRAPPER_H
#define TINYDNNWRAPPER_H



#include "tiny_dnn/tiny_dnn.h"
#include <string>
#include "BTCSet.h"
#include "tiny_dnn/util/util.h"

class RunTimeWindow;

using namespace std;

class tinydnnwrapper
{

public:
    tinydnnwrapper();
    bool addlayer(unsigned int n_source, unsigned int n_nodes, const string &activation_function);
    bool createnetwork(const vector<unsigned int> &nodes);
    size_t batch_size = 16;
    int epochs        = 2000;
    tiny_dnn::adamax opt;
    bool SetInput(CTimeSeriesSet &input);
    bool SetTarge(CTimeSeriesSet &input);
    bool AppendtoInput(CTimeSeriesSet &input);
    bool AppendtoTarge(CTimeSeriesSet &input);
    std::vector<tiny_dnn::vec_t> Input;
    std::vector<tiny_dnn::vec_t> Output;
    double loss();
    bool train(RunTimeWindow *rtw=nullptr);
    CTimeSeriesSet predicted();
    bool batchtrain(const std::vector<tiny_dnn::tensor_t> &inputs,
                                    const std::vector<tiny_dnn::tensor_t> &desired_outputs,
                                    size_t batch_size,
                                    int epoch,
                                    const bool reset_weights            = false,
                                    const int n_threads                 = CNN_TASK_SIZE,
                                    const std::vector<tiny_dnn::tensor_t> &t_cost = std::vector<tiny_dnn::tensor_t>());
private:
    tiny_dnn::network<tiny_dnn::sequential> net;
};

#endif // TINYDNNWRAPPER_H
