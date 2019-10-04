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
	ANN_class& ANN_class::operator=(const ANN_class &m);
	ANN_class::ANN_class(const ANN_class &m);
	vector<double> ANN_class::calc_output(vector<double> input);
	CVector ANN_class::calc_output_v(CVector weights);
	CBTCSet *input; 
	void ANN_class::setparams(CVector X);
	CVector ANN_class::weights_to_vector();
	int num_layers();
	int num_inputs();
	int num_outputs();
	int ANN_class::num_weights();
	CBTCSet training_data;
	CBTC output();
	CVector ANN_class::train(double tol);
};

