#include "ANN_class.h"
#include "ML.h"



ANN_class::ANN_class()
{
}


ANN_class::~ANN_class()
{
}

ANN_class& ANN_class::operator=(const ANN_class &m)
{
	weights = m.weights;
	nodes = m.nodes;
	input = m.input;

	return *this;

}
ANN_class::ANN_class(const ANN_class &m)
{
	weights = m.weights;
	nodes = m.nodes;
	input = m.input;
}

ANN_class::ANN_class(vector<int> n_nodes)
{
	int n_layers = n_nodes.size();
	weights.resize(n_layers - 1);
	for (int i = 0; i < n_layers - 1; i++)
	{
		weights[i].resize(n_nodes[i]+1);
		for (int j = 0; j < n_nodes[i]+1; j++)
			weights[i][j].resize(n_nodes[i + 1]+1);

	}

	nodes.resize(n_layers);
	for (int i = 0; i < n_layers; i++)
	{
		nodes[i].resize(n_nodes[i] + 1);
		nodes[i][0].activation_function= "1";
	}
		
}

vector<double> ANN_class::calc_output(vector<double> input)
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


void ANN_class::setparams(CVector X)
{
	int counter = 0;
	for (int i = 0; i<weights.size(); i++)
		for (int j = 0; j < weights[i].size(); j++)
			for (int k = 0; k < weights[i][j].size(); k++)
			{
				weights[i][j][k] = X[counter];
				counter++;
			}

}

CVector ANN_class::weights_to_vector()
{
	int counter = 0;
	CVector X;
	for (int i = 0; i< weights.size(); i++)
		for (int j = 0; j < weights[i].size(); j++)
			for (int k = 0; k < weights[i][j].size(); k++)
			{
				X.append(weights[i][j][k]);
				counter++;
			}
	return X;
}


CVector ANN_class::train(double tol)
{
	CML ML;
	ML.epsilon = 1e-6;
	ML.tol = tol;
	ML.Obs = CVector(training_data.toBTC().C);
	ML.func_ann = &ANN_class::calc_output_v;
	CVector optimized_parameters = ML.optimize(weights_to_vector(),this);
	return optimized_parameters;
	
}

CVector ANN_class::calc_output_v(CVector weights)
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
	return nodes.size();
}
int ANN_class::num_inputs()
{
	return nodes[0].size() - 1;
}
int ANN_class::num_outputs()
{
	return nodes[num_layers() - 1].size() - 1;
}

int ANN_class::num_weights()
{
	int counter = 0;
	for (int i = 0; i<weights.size(); i++)
		for (int j = 0; j < weights[i].size(); j++)
			for (int k = 0; k < weights[i][j].size(); k++)
				counter++;
	return counter;
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