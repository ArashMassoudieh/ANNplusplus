#pragma once
#include <vector>
#include "Node.h"
#include "Link.h"
#include "Vector.h"
#include "Matrix.h"
#include "BTCSet.h"

using namespace std;
class ANN_class
{
public:
	ANN_class();
	ANN_class(vector<int> n_nodes, CNode::activationfunc act = CNode::activationfunc::sigmoid);
	~ANN_class();
	CNode* node(string id);
	Link* link(string id);
	CNode* node(int layer, int num);
	ANN_class& operator=(const ANN_class &m);
	ANN_class(const ANN_class &m);
	vector<double> calc_output(const vector<double> &input);
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
	CBTC output();
	CVector train(const double &tol);
	bool Append(CNode& node);
	bool Append(Link& link);
	bool SetPointers();
private:
	vector<CNode> Nodes;
	vector<Link> Links;
	vector<vector<CNode*>> layers;
};

