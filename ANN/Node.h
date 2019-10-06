#pragma once
#include <string>
#include <vector>

using namespace std;

class CNode
{
public:
	enum class activationfunc {sigmoid, tanh, rlu, one};
	activationfunc activation_function;
	CNode();
	~CNode();
	CNode(const CNode &m);
	CNode& operator=(const CNode &m);
	double out(double input);
	void out();
	double input_val;
	double output_val;
	vector<CNode*> nodesfrom;
	vector<CNode*> nodesto;
};

