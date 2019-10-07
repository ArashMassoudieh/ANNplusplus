#include "ANN_class.h"
#include "ML.h"
#include "utils.h"
#include <vector>

using namespace std;



ANN_class::ANN_class()
{
}


ANN_class::~ANN_class()
{
}

CNode* ANN_class::node(string id)
{
	for (int i = 0; i < Nodes.size(); i++)
		if (Nodes[i].GetID() == id)
			return &Nodes[i];
	return nullptr;
}

Link* ANN_class::link(string id)
{
	for (int i = 0; i < Links.size(); i++)
		if (Links[i].GetID() == id)
			return &Links[i];
	return nullptr;
}

CNode* ANN_class::node(int layer, int num)
{
	for (int i = 0; i < Nodes.size(); i++)
	{
		if (Nodes[i].layerno == layer && Nodes[i].numinlayer == num)
			return &Nodes[i];
	}
	return nullptr;
}


ANN_class& ANN_class::operator=(const ANN_class &m)
{
	Links = m.Links; 
	Nodes = m.Nodes; 
	input = m.input;

	return *this;

}
ANN_class::ANN_class(const ANN_class &m)
{
	Links = m.Links;
	Nodes = m.Nodes;
	input = m.input;
}

ANN_class::ANN_class(vector<int> n_nodes, CNode::activationfunc act)
{
	int n_layers = n_nodes.size();
	layers.resize(n_layers);
	for (unsigned int i = 0; i < n_layers; i++)
	{
		CNode::activationfunc actfun; 
		if (i == 0) 
			actfun = CNode::activationfunc::one;
		else
			actfun = act;
		for (unsigned int j = 0; j < n_nodes[i]; j++)
		{
			CNode n = CNode(aquiutils::numbertostring(int(i)) + "," + aquiutils::numbertostring(int(j)), act);
			n.layerno = i;
			n.numinlayer = j;
			Append(n);
			layers[i].push_back(node(aquiutils::numbertostring(int(i)) + "," + aquiutils::numbertostring(int(j))));
		}

	}

	for (unsigned int i = 0; i < n_layers - 1; i++)
	{
		for (unsigned int j = 0; j < n_nodes[i]; j++)
		{
			for (unsigned int k = 0; k < n_nodes[i + 1]; k++)
			{
				Link l = Link(aquiutils::numbertostring(int(i)) + "," + aquiutils::numbertostring(int(j)) + "-" + aquiutils::numbertostring(int(i + 1)) + "," + aquiutils::numbertostring(int(k)), node(i, j)->GetID(), node(i, k)->GetID());
				Append(l);
			}
		}
		for (unsigned int k = 0; k < n_nodes[i + 1]; k++)
		{
			Link l = Link("intercept-" + aquiutils::numbertostring(int(i + 1)) + "," + aquiutils::numbertostring(int(k)), nullptr, node(i, k)->GetID());
			Append(l);
		}
	}
	SetPointers(); 

}

vector<double> ANN_class::calc_output(const vector<double> &input)
{
	for (int j = 0; j < nodes[0].size(); j++)
	{
		if (j==0)
			nodes[0][j].input_val = 1;
		else
			nodes[0][j].input_val = input[j-1];

		nodes[0][j].out();
	}
	for (int i = 1; i < nodes.size(); i++)
	{
		for (int j = 0; j < nodes[i].size(); j++)
		{
			double sum = 0;
			for (int k = 0; k < nodes[i - 1].size(); k++)
				sum += nodes[i - 1][k].output_val*weights[i-1][k][j];

			nodes[i][j].input_val = sum;
			nodes[i][j].out();
		}
	}

	vector<double> X(nodes[nodes.size() - 1].size()-1);
	for (int i = 1; i < nodes[nodes.size() - 1].size(); i++)
		X[i-1] = nodes[nodes.size() - 1][i].output_val;

	return X;
}


bool ANN_class::applyinput(CBTCSet* _input)
{
	if (layers[0].size != _input->nvars)
	{
		cout << "Number of inputs should be equal to the number of nodes in the first layer!" << endl;
		return false;
	}
	else
		for (int i = 0; i < layers[0].size(); i++)
			layers[0][i]->input = &_input->BTC[i];
}

bool ANN_class::setparams(const CVector &X)
{
	if (X.num != Links.size())
	{
		cout << "Vector size must be the same as the number of links!" << endl;
		return false;
	}

	for (int i = 0; i<Links.size(); i++)
		Links[i].SetWeight(X[i]);
	
	return true; 
}

CVector ANN_class::weights_to_vector()
{
	CVector X;
	for (int i = 0; i < Links.size(); i++)
		X.append(Links[i].GetWeight());
	return X;
}


CVector ANN_class::train(const double &tol)
{
	CML ML;
	ML.epsilon = 1e-6;
	ML.tol = tol;
	ML.Obs = CVector(training_data.toBTC().C);
	ML.func_ann = &ANN_class::calc_output_v;
	CVector optimized_parameters = ML.optimize(weights_to_vector(),this);
	return optimized_parameters;

}

bool ANN_class::Append(CNode& _node)
{
	if (node(_node.GetID()) != nullptr)
		cout << "Node " + _node.GetID() + " Already exists!" << endl;
	else
		Nodes.push_back(_node);
}

bool ANN_class::Append(Link& _link)
{
	if (link(_link.GetID()) != nullptr)
		cout << "Link " + _link.GetID() + " Already exists!" << endl;
	else
		Links.push_back(_link);
}

bool ANN_class::SetPointers()
{
	for (int i = 0; i < Links.size(); i++)
	{
		if (node(Links[i].SourceID) != nullptr)
		{
			node(Links[i].SourceID)->linksfrom.push_back(&Links[i]);
			Links[i].SetSource = node(Links[i].SourceID); 
		}
		if (node(Links[i].TargetID) != nullptr)
		{
			node(Links[i].TargetID)->linksto.push_back(&Links[i]);
			Links[i].SetTarget = node(Links[i].TargetID);
		}
		
	}


}

CVector ANN_class::calc_output_v(const CVector &weights)
{
	setparams(weights);
	CVector out;
	for (int i = 0; i < input->BTC[0].n; i++)
	{
		CVector out1 = calc_output(input->getrow(i));
		out.append(out1);
	}
	return out;

}

int ANN_class::num_layers()
{
	return layers.size();
}
int ANN_class::num_inputs()
{
	return layers[0].size();
}
int ANN_class::num_outputs()
{
	return layers[num_layers() - 1].size();
}

int ANN_class::num_weights()
{
	return Links.size(); 
}


CBTC ANN_class::output()
{
	CBTC BTC(num_inputs());
	for (int i = 0; i < input->BTC[0].n; i++)
	{
		CVector out(calc_output(input->getrow(i)));
		for (int j = 0; j < out.num; j++)
			BTC.append(input->BTC[0].t[i], out.vec[j]);
	}

	return BTC;

}
