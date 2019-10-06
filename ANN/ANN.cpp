// ANN.cpp : Defines the entry point for the console application.
//

#include "ANN_class.h"
#include "ML.h"

CVector poly(const CVector &params)
{
	CVector out;
	for (double x = 0; x < 2; x += 0.1)
	{
		double sum = 0;
		for (int j = 0; j < params.getsize(); j++)
			sum += params[j] * pow(x, j);
		out.append(sum);
	}
	return out;

}

int main()
{
	/*vector<int> layers(3);
	layers[0] = 1;
	layers[1] = 3;
	layers[2] = 1;
	ANN_class ANN(layers);
	vector<double> input(1);
	input[0] = 1;
	vector<double> out = ANN.calc_output(input);
	CVector weights;
	for (int i = 0; i < ANN.num_weights(); i++)
		weights.append(0.2*i*pow(-1,i));

	CBTCSet input_ts(1);
	for (int i = 0; i < 200; i++)
		input_ts.BTC[0].append((i-100.0)/100.0);

	ANN.input = &input_ts;

	CVector OBS = ANN.calc_output_v(weights);
	CBTCSet OBS_BTC;
	OBS_BTC.append(CBTC(OBS));

	ANN.training_data = OBS_BTC;
	CBTC(OBS).writefile("observed.txt");

	weights = 0;

	ANN.setparams(weights);

	CVector estimated_weights = ANN.train(0.0001);
	CBTC(ANN.calc_output_v(estimated_weights)).writefile("modeled.txt");*/

	CVector params(4); params[0] = 2; params[1] = 0.1; params[2] = 0.03; params[3] = 0.001;
	CVector Y_obs = poly(params);
	CML ML;
	ML.epsilon = 1e-6;
	ML.tol = 1e-4;
	ML.func = &poly;
	ML.Obs = Y_obs;
	CVector params_0(4);

	CVector p_best = ML.optimize(params_0);
	cout<<p_best.toString()<<endl;


	return 0;
}

