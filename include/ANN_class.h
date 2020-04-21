#pragma once
#include <vector>

//#ifdef Q_version
//    #include <QDebug>
//    #include <QString>
//    #define cout qDebug()
//    #define string QString
//#endif
#include "Node.h"
#include "Link.h"
#include "Vector.h"
#include "Matrix.h"
#include "BTCSet.h"
#include "ErrorHandler.h"

using namespace std;
class ANN_class
{
public:
	ANN_class();
	ANN_class(vector<int> n_nodes, CNode::activationfunc act = CNode::activationfunc::sigmoid);
	~ANN_class();
	CNode* node(string id);
    CNode* node(unsigned int i) { return &Nodes[i]; }
	Link* link(string id);
    Link* link(unsigned int i) { return &Links[i];}
	CNode* node(int layer, int num);
	ANN_class& operator=(const ANN_class &m);
	ANN_class(const ANN_class &m);
	vector<double> calc_output(const vector<double> &input);
    double calc_error(CTimeSeriesSet *input,CTimeSeriesSet *output);
    CVector calc_output_v(const CVector &weights);
	CBTCSet *input;
	bool applyinput(CBTCSet* _input);
	bool setparams(const CVector &X);
	CVector weights_to_vector();
	bool ApplyWeights(const CVector &weights);
	int num_layers();
	int num_inputs();
	int num_outputs();
	int num_weights();
	CBTCSet training_data;
    CBTCSet output();
	CVector train(const double &tol);
	bool Append(CNode& node);
	bool Append(Link& link);
	bool SetPointers();
	CMatrix Gradient(const CVector &input);
	CMatrix Gradient_direct(const CVector& input);
    CVector Gradient_error_direct(CTimeSeriesSet *input,CTimeSeriesSet *output);
	CMatrix UpdateDerivatives(const CVector& input);
    ErrorHandler* GetErrorHandler() {return &errorhandler;}
    void SetLearningRate(const double &value) {learning_rate = value;}
    double PerformSingleStepStochasticSteepestDescent(unsigned int batch_size);
    double PerformSingleStepSteepestDescent();
    CTimeSeries *ErrorSeries() {return &error_series;}
    void AppendErrVal(const double &d) {error_series.append(error_series.n,d);}
private:
	vector<CNode> Nodes;
	vector<Link> Links;
	vector<vector<CNode*>> layers;
	bool SetNodeDerivates(const CVector &input);
	void SetLinkNodeParents();
	double epsilon = 1e-6;
    ErrorHandler errorhandler;
    double derivative_purturbation = 1e-6;
    double learning_rate;
    CTimeSeries error_series;
};

