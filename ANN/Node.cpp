#include "Node.h"



CNode::CNode()
{
	activation_function = "sigmoid";
}


CNode::~CNode()
{
}

double CNode::out(double input)
{
	if (activation_function == "sigmoid")
		return 1.0 / (1.0 + exp(-input));
	if (activation_function == "1")
		return 1.0;
}

void CNode::out()
{
	if (activation_function == "sigmoid")
		output_val = 1.0 / (1.0 + exp(-input_val));
	if (activation_function == "1")
		output_val = 1.0;
}

CNode::CNode(const CNode &m)
{
	input_val = m.input_val;
	output_val = m.output_val;
	activation_function = m.activation_function;
	
}

CNode& CNode::operator=(const CNode &m)
{
	input_val = m.input_val;
	output_val = m.output_val;
	activation_function = m.activation_function;
	return *this;
}
