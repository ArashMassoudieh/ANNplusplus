#include "Node.h"
#include <math.h>


CNode::CNode()
{
	activation_function = activationfunc::sigmoid;
}


CNode::~CNode()
{
}

double CNode::out(double input)
{
	if (activation_function == activationfunc::sigmoid)
		return 1.0 / (1.0 + exp(-input));
	if (activation_function == activationfunc::one)
		return 1.0;
}

void CNode::out()
{
	if (activation_function == activationfunc::sigmoid)
		output_val = 1.0 / (1.0 + exp(-input_val));
	if (activation_function == activationfunc::one)
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
