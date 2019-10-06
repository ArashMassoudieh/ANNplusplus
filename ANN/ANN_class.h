#pragma once
#include <vector>
#include "Node.h"
#include "Vector.h"
#include "Matrix.h"
#include "BTCSet.h"

using namespace std;
class ANN_class
{
public:
	ANN_class();
	ANN_class(vector<int> n_nodes);
	~ANN_class();
	vector<vector<CNode>> nodes;
	vector<vector<vector<double>>> weights;
	ANN_class& operator=(const ANN_class &m);
	ANN_class(const ANN_class &m);
	vector<double> calc_output(const vector<double> &input);
	CVector calc_output_v(const CVector &weights);
	CBTCSet *input;
	void setparams(const CVector &X);
	CVector weights_to_vector();
	int num_layers();
	int num_inputs();
	int num_outputs();
	int num_weights();
	CBTCSet training_data;
	CBTC output();
	CVector train(const double &tol);
};

