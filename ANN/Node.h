#pragma once
#include <string>

using namespace std;

class CNode
{
public:
	CNode();
	~CNode();
	CNode::CNode(const CNode &m);
	CNode& CNode::operator=(const CNode &m);
	string activation_function;
	double out(double input);
	void out();
	double input_val; 
	double output_val;
};

