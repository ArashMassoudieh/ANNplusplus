#pragma once
#include <string>
#include <vector>
#include <BTC.h>
#include "Vector.h"

using namespace std;

class Link; 
class ANN_class; 

class CNode
{
public:
	
	const double epsilon = 1e-12; 
	enum class activationfunc { sigmoid, tanh, rlu, one };
	activationfunc activation_function;
	CNode();
	CNode(string id, activationfunc actfunc);
	~CNode();
	CNode(const CNode& m);
	CNode& operator=(const CNode& m);
	double out(double input);
	void out();
	double getinputval();
	double input_val;
	double output_val;
	vector<Link*> linksto;
	vector<Link*> linksfrom;
	string GetID() { return ID; }
	void SetID(string id) { ID = id; }
	void SetValueEvaluated(bool v) { value_evaluated = v; }
	int layerno; 
	int numinlayer; 
	CTimeSeries* input; 
	double derivative(bool update = false);
	ANN_class* Parent() const { return parent; }
	void SetParent(ANN_class *p) { parent = p; }
	CVector& derivatives_vs_weights(); 
private:
	ANN_class* parent;
	void set_derivatives_vs_weights();
	void CNode::set_derivatives_vs_weights(int i);
	CVector derivative_vs_weights_vals; 
	string ID; 
	bool value_evaluated=false;
	double deriv;
	bool IsLinksTo(int i);
};

