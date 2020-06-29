#ifndef TINYDNNWRAPPER_H
#define TINYDNNWRAPPER_H



#include "tiny_dnn/tiny_dnn.h"
#include <string>
#include "BTCSet.h"
#include "tiny_dnn/util/util.h"

class RunTimeWindow;

struct state_value_pair
{
    double reward=0;
    double value = 0;
    CVector state;
};


using namespace std;

class tinydnnwrapper
{

public:
    tinydnnwrapper();
    bool addlayer(unsigned int n_source, unsigned int n_nodes, const string &activation_function);
    bool createnetwork(const vector<unsigned int> &nodes);
    size_t batch_size = 16;
    int epochs        = 100;
    tiny_dnn::adamax opt;
    bool SetInput(CTimeSeriesSet &input);
    bool SetTarge(CTimeSeriesSet &input);
    bool AppendtoInput(CTimeSeriesSet &input);
    bool AppendtoInput(CVector &input);
    bool AppendtoTarget(CTimeSeriesSet &input);
    bool AppendtoTarget(CVector &target);
    bool AppendtoTarget(double &target);
    std::vector<tiny_dnn::vec_t> Input;
    std::vector<tiny_dnn::vec_t> Output;
    CTimeSeriesSet InputTimeSeries;
    CTimeSeriesSet OutputTimeSeries;
    double loss();
    bool train(RunTimeWindow *rtw=nullptr);
    bool trainonebatch(vector<state_value_pair> *state_value_pair ,int batch_size, RunTimeWindow *rtw = nullptr);
    bool trainonebatch(int start, int batch_size, RunTimeWindow *rtw);
    CTimeSeriesSet predicted();
    CVector predicted(const CVector &input);
    bool batchtrain(const std::vector<tiny_dnn::tensor_t> &inputs,
                                    const std::vector<tiny_dnn::tensor_t> &desired_outputs,
                                    size_t batch_size,
                                    int epoch,
                                    const bool reset_weights            = false,
                                    const int n_threads                 = CNN_TASK_SIZE,
                                    const std::vector<tiny_dnn::tensor_t> &t_cost = std::vector<tiny_dnn::tensor_t>());
    static tiny_dnn::vec_t vec_from_TimeSeries(const CTimeSeries &C);
    static vector<tiny_dnn::vec_t> vec_from_TimeSeries(const CTimeSeriesSet &C);
    static CTimeSeries TimeSeries_from_vec(const tiny_dnn::vec_t &v);
    static CTimeSeriesSet TimeSeriesSet_from_vec(const vector<tiny_dnn::vec_t> &v);
    static vector<tiny_dnn::vec_t> randomsample(const vector<tiny_dnn::vec_t> &v, int n);
    static vector<tiny_dnn::vec_t> randomsample(const CTimeSeriesSet &C, int n);
private:
    tiny_dnn::network<tiny_dnn::sequential> net;
};

#endif // TINYDNNWRAPPER_H
