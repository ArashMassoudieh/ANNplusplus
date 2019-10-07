#include "Node.h"
#include <math.h>
#include "Link.h"

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
