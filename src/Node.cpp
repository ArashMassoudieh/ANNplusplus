#include "Node.h"
#include <math.h>
#include "Link.h"
#include "ANN_class.h"

CNode::CNode()
{
	activation_function = activationfunc::sigmoid;
}

CNode::CNode(string id, activationfunc actfunc)
{
	ID = id; 
	activation_function = actfunc;
}


CNode::~CNode()
{
}

double CNode::out(double input)
{
	if (activation_function == activationfunc::sigmoid)
		return 1.0 / (1.0 + exp(-input));
	if (activation_function == activationfunc::one)
		return input;
}

void CNode::out()
{
	if (activation_function == activationfunc::sigmoid)
		output_val = 1.0 / (1.0 + exp(-input_val));
	if (activation_function == activationfunc::one)
		output_val = input_val;
}

double CNode::getinputval()
{
	double sum = 0; 
	for (int i = 0; i < linksto.size(); i++)
	{
		if (linksto[i]->GetSource()!=nullptr)
			sum += linksto[i]->GetSource()->output_val * linksto[i]->GetWeight(); 
		else
			sum += linksto[i]->GetWeight();
	}
	input_val = sum; 
	return sum; 
}

double CNode::derivative(bool update)
{
	if (update)
		deriv = (out(input_val + epsilon) - out(input_val)) / epsilon;
	return deriv;
}

void CNode::set_derivatives_vs_weights()
{
	derivative_vs_weights_vals = CVector(parent->num_weights);
	derivative(true);
	for (int i = 0; i < linksto.size(); i++) set_derivatives_vs_weights(i);
}

void CNode::set_derivatives_vs_weights(int i)
{
	if (IsLinksTo(i))
	{
		derivative_vs_weights_vals[i] = derivative() * parent->link(i)->Val(); 
	}
	else
	{
		for (int j = 0; j < linksto.size(); j++)
			derivative_vs_weights_vals[i] = derivative() * linksto[j]->GetWeight() * linksto[j]->GetSource()->derivatives_vs_weights()[i];
	}
}

bool CNode::IsLinksTo(int i)
{
	for (int j = 0; j < linksto.size(); j++)
		if (parent->link(i)->GetID() == linksto[j]->GetID())
			return true; 
	return false; 
}

CNode::CNode(const CNode &m)
{
	input_val = m.input_val;
	output_val = m.output_val;
	activation_function = m.activation_function;
	ID = m.ID; 
	layerno = m.layerno;
	numinlayer = m.numinlayer;

}

CNode& CNode::operator=(const CNode &m)
{
	input_val = m.input_val;
	output_val = m.output_val;
	activation_function = m.activation_function;
	ID = m.ID; 
	layerno = m.layerno;
	numinlayer = m.numinlayer;
	return *this;
}
