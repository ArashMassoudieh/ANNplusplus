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
    for (unsigned int i = 0; i < Nodes.size(); i++)
		if (Nodes[i].GetID() == id)
			return &Nodes[i];
	return nullptr;
}

Link* ANN_class::link(string id)
{
    for (unsigned int i = 0; i < Links.size(); i++)
		if (Links[i].GetID() == id)
			return &Links[i];
	return nullptr;
}

CNode* ANN_class::node(int layer, int num)
{
    for (unsigned int i = 0; i < Nodes.size(); i++)
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
    unsigned long n_layers = n_nodes.size();
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
			CNode n = CNode(aquiutils::numbertostring(int(i)) + "," + aquiutils::numbertostring(int(j)), actfun);
			n.layerno = i;
			n.numinlayer = j;
			Append(n);
		}

	}

	for (unsigned int i = 0; i < n_layers; i++)
		for (unsigned int j = 0; j < n_nodes[i]; j++)
			layers[i].push_back(node(aquiutils::numbertostring(int(i)) + "," + aquiutils::numbertostring(int(j))));

	for (unsigned int i = 0; i < n_layers - 1; i++)
	{
		for (unsigned int j = 0; j < n_nodes[i]; j++)
		{
			for (unsigned int k = 0; k < n_nodes[i + 1]; k++)
			{
				Link l = Link(aquiutils::numbertostring(int(i)) + "," + aquiutils::numbertostring(int(j)) + "-" + aquiutils::numbertostring(int(i + 1)) + "," + aquiutils::numbertostring(int(k)), node(i, j)->GetID(), node(i+1, k)->GetID());
				Append(l);
			}
		}
		for (unsigned int k = 0; k < n_nodes[i + 1]; k++)
		{
			Link l = Link("intercept-" + aquiutils::numbertostring(int(i + 1)) + "," + aquiutils::numbertostring(int(k)), "", node(i+1, k)->GetID());
			Append(l);
		}
	}
	SetLinkNodeParents();
	SetPointers();
    RMSGradient = CVector(Links.size());
}


double ANN_class::calc_error(CTimeSeriesSet *input,CTimeSeriesSet *output)
{
    double sum=0;
    if (input->BTC[0].n != output->BTC[0].n)
    {
        errorhandler.AppendError(string("calc_error"),1001,"The number of data points in the input [" + aquiutils::numbertostring(input->BTC[0].n) + "] is not equal to the number of datapoints in the output dataset [" + aquiutils::numbertostring(output->BTC[0].n));
        return 0;
    }
    for (int i=0; i<input->BTC[0].n; i++)
    {
        vector<double> input_vec = input->getrow(i);
        CVector predicted = CVector(calc_output(input_vec));
        CVector measured = CVector(output->getrow(i));
        sum += (predicted-measured).norm2();
    }
    return sum;
}


CVector ANN_class::Gradient_error_direct(CTimeSeriesSet *input,CTimeSeriesSet *output)
{
    Vector w0 = weights_to_vector();
    CVector gradient;
    double base_error = calc_error(input,output);
    for (unsigned int i=0; i<w0.num; i++)
    {
        Vector w = w0;
        w[i] += derivative_purturbation;
        ApplyWeights(w);
        double purturbed_error = calc_error(input,output);
        gradient.append((purturbed_error-base_error)/derivative_purturbation);
    }
    ApplyWeights(w0);
    gradient = gradient/gradient.norm2();
    RMSGradient = twicking_params.gamma*RMSGradient + (1.0-twicking_params.gamma)*gradient.Pow(2);
    return gradient;
}

vector<double> ANN_class::calc_output(const vector<double> &input)
{
    for (unsigned int j = 0; j < layers[0].size(); j++)
	{
		layers[0][j]->input_val = input[j];
		layers[0][j]->out();
	}
    for (unsigned int i = 1; i < layers.size(); i++)
	{
        for (unsigned int j = 0; j < layers[i].size(); j++)
		{
			double sum = 0;
            for (unsigned int k = 0; k < layers[i][j]->linksto.size(); k++)
			{
				if (layers[i][j]->linksto[k]->GetSource()==nullptr)
					sum += layers[i][j]->linksto[k]->GetWeight();
				else
					sum += layers[i][j]->linksto[k]->GetWeight() * layers[i][j]->linksto[k]->GetSource()->output_val;

			}

			layers[i][j]->input_val = sum;
			layers[i][j]->out();
		}
	}

	vector<double> X(layers[layers.size() - 1].size());
    for (unsigned int i = 0; i < layers[layers.size() - 1].size(); i++)
		X[i] = layers[layers.size() - 1][i]->output_val;

	return X;
}


bool ANN_class::applyinput(CBTCSet* _input)
{
	if (layers[0].size() != _input->nvars)
	{
        errorhandler.AppendError("applyinput",1002, "Number of inputs should be equal to the number of nodes in the first layer!");
		return false;
	}
	else
        for (unsigned int i = 0; i < layers[0].size(); i++)
			layers[0][i]->input = &_input->BTC[i];
}

bool ANN_class::setparams(const CVector &X)
{
	if (X.num != Links.size())
	{
        errorhandler.AppendError("setparams",1003, "Vector size must be the same as the number of links!");
		return false;
	}

	for (int i = 0; i<Links.size(); i++)
		Links[i].SetWeight(X[i]);

	return true;
}

CVector ANN_class::weights_to_vector()
{
	CVector X;
    for (unsigned int i = 0; i < Links.size(); i++)
		X.append(Links[i].GetWeight());
	return X;
}

bool ANN_class::ApplyWeights(const CVector &weights)
{
    if (weights.num != int(Links.size()))
	{
        errorhandler.AppendError("ApplyWeights",1004, "The size of the weight vector is different than the number of links");
		return false;
	}
	else
	{
        for (unsigned int i = 0; i < Links.size(); i++)
			Links[i].SetWeight(weights[i]);
		return true;
	}
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
	{
        errorhandler.AppendError("Append",1005, "Node " + _node.GetID() + " Already exists!");
		return false;
	}
	else
	{
		Nodes.push_back(_node);
		node(_node.GetID())->SetParent(this);
		return true;
	}
}

bool ANN_class::Append(Link& _link)
{
	if (link(_link.GetID()) != nullptr)
	{
        errorhandler.AppendError("Append",1006, "Link " + _link.GetID() + " Already exists!");
		return false;
	}
	else
	{
		Links.push_back(_link);
		link(_link.GetID())->SetParent(this);
		return true;
	}
}

bool ANN_class::SetPointers()
{
    for (unsigned int i = 0; i < Links.size(); i++)
	{
		if (node(Links[i].SourceID) != nullptr)
		{
			node(Links[i].SourceID)->linksfrom.push_back(&Links[i]);
			Links[i].SetSource(node(Links[i].SourceID));
		}
		else
			Links[i].SetSource(nullptr);
		if (node(Links[i].TargetID) != nullptr)
		{
			node(Links[i].TargetID)->linksto.push_back(&Links[i]);
			Links[i].SetTarget(node(Links[i].TargetID));
		}
		else
			Links[i].SetTarget(nullptr);

	}
	return true;

}

double ANN_class::PerformSingleStepStochasticSteepestDescent(unsigned int batch_size)
{
    vector<int> selecteddatapoints = aquiutils::random_vector(0,input->BTC[0].n, batch_size);
    CTimeSeriesSet sampled_input = input->random_draw_plus_last(selecteddatapoints);
    CTimeSeriesSet sampled_output = training_data.random_draw_plus_last(selecteddatapoints);
    CVector weights = weights_to_vector();
    double err0 = calc_error(&sampled_input,&sampled_output);
    AppendErrVal(err0);
    CVector gradient = Gradient_error_direct(&sampled_input,&sampled_output);
    weights -= twicking_params.learning_rate*(gradient/((RMSGradient+twicking_params.epsilon).Sqrt()));
    ApplyWeights(weights);
    double err1 = calc_error(&sampled_input,&sampled_output);
    return err1;
}

double ANN_class::PerformSingleStepSteepestDescent()
{
    CVector weights = weights_to_vector();
    double err0 = calc_error(input,&training_data);
    AppendErrVal(err0);
    CVector gradient = Gradient_error_direct(input,&training_data);
    weights -= twicking_params.learning_rate*(gradient/((RMSGradient+twicking_params.epsilon).Sqrt()));
    ApplyWeights(weights);
    double err1 = calc_error(input,&training_data);
    return err1;
}


CMatrix ANN_class::Gradient(const CVector& input)
{
	CMatrix M(num_outputs(), num_weights());
    for (unsigned int i = 0; i < num_layers(); i++)
	{

	}
	return M; 
}

CMatrix ANN_class::Gradient_direct(const CVector& input)
{
	
	CVector weights_0 = weights_to_vector();
	CVector weights_purt = weights_0; 
	ApplyWeights(weights_0);
	CVector F0 = calc_output(input.vec);
	CMatrix M(num_weights(),num_outputs());
	for (int i = 0; i < weights_0.getsize(); i++)
	{
		weights_purt[i] = weights_0[i] + epsilon;
		ApplyWeights(weights_purt);
		CVector F1 = calc_output(input.vec);
		M[i] = (F1 - F0) / epsilon;
	}
	ApplyWeights(weights_0);
	return Transpose(M); 

}

CMatrix ANN_class::UpdateDerivatives(const CVector &input)
{
	SetNodeDerivates(input); 
	CMatrix Gradient(layers[layers.size() - 1].size(), Links.size());
	for (int i = 0; i < layers.size(); i++)
	{
		for (int j = 0; j < layers[i].size(); j++)
			layers[i][j]->derivatives_vs_weights(true);
	}
	for (int i = 0; i < layers[layers.size() - 1].size(); i++)
		Gradient[i] = layers[layers.size() - 1][i]->derivatives_vs_weights(true);

	return Gradient;
}

bool ANN_class::SetNodeDerivates(const CVector& input)
{
	if (input.num != num_inputs())
	{
        errorhandler.AppendError("SetNodeDerivates", 1007, "Input vector size (" + aquiutils::numbertostring(input.num) + ")  is inconsistent with the number of nodes in the input layer (" + aquiutils::numbertostring(num_inputs()) + ")");
		return false; 
	}
	else
	{
		calc_output(input.vec);
		for (int i = 0; i < layers.size(); i++)
			for (int j = 0; j < layers[i].size(); j++)
				layers[i][j]->derivative(true); 
	}
	return true; 
}

void ANN_class::SetLinkNodeParents()
{
    for (unsigned int i = 0; i < Nodes.size(); i++)
		Nodes[i].SetParent(this);
    for (unsigned int i = 0; i < Links.size(); i++)
		Links[i].SetParent(this);
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


CBTCSet ANN_class::output()
{
    CBTCSet outts(num_outputs());
	for (int i = 0; i < input->BTC[0].n; i++)
	{
		CVector out(calc_output(input->getrow(i)));
        outts.append(input->BTC[0].t[i], out.vec);
	}

    return outts;

}
