#pragma once
#include <string>
#include <vector>
#include <BTC.h>

using namespace std;

class Link; 


class CNode
{
public:
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
private:
	string ID; 
	bool value_evaluated=false;
	
};

