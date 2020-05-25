#include "tinydnnwrapper.h"
#include "tiny_dnn.h"
#include <iostream>
#include <string>

using namespace std;
tinydnnwrapper::tinydnnwrapper()
{


      // create input and desired output on a period
      std::vector<tiny_dnn::vec_t> X;
      std::vector<tiny_dnn::vec_t> sinusX;
      for (float x = -3.1416f; x < 3.1416f; x += 0.2f) {
        tiny_dnn::vec_t vx    = {x};
        tiny_dnn::vec_t vsinx = {sinf(x)};

        X.push_back(vx);
        sinusX.push_back(vsinx);
      }

      // set learning parameters
      size_t batch_size = 16;    // 16 samples for each network weight update
      int epochs        = 2000;  // 2000 presentation of all samples
      tiny_dnn::adamax opt;

      // this lambda function will be called after each epoch
      int iEpoch              = 0;
      auto on_enumerate_epoch = [&]() {
        // compute loss and disp 1/100 of the time
        iEpoch++;
        if (iEpoch % 100) return;

        double loss = net.get_loss<tiny_dnn::mse>(X, sinusX);
        std::cout << "epoch=" << iEpoch << "/" << epochs << " loss=" << loss
                  << std::endl;
      };

      // learn
      std::cout << "learning the sinus function with 2000 epochs:" << std::endl;
      net.fit<tiny_dnn::mse>(opt, X, sinusX, batch_size, epochs, []() {},
                             on_enumerate_epoch);

      std::cout << std::endl
                << "Training finished, now computing prediction results:"
                << std::endl;

      // compare prediction and desired output
      float fMaxError = 0.f;
      for (float x = -3.1416f; x < 3.1416f; x += 0.2f) {
        tiny_dnn::vec_t xv = {x};
        float fPredicted   = net.predict(xv)[0];
        float fDesired     = sinf(x);

        std::cout << "x=" << x << " sinX=" << fDesired
                  << " predicted=" << fPredicted << std::endl;

        // update max error
        float fError = fabs(fPredicted - fDesired);

        if (fMaxError < fError) fMaxError = fError;
      }

      std::cout << std::endl << "max_error=" << fMaxError << std::endl;

}

bool tinydnnwrapper::addlayer(unsigned int n_source, unsigned int n_nodes, const string &activation_function)
{
    net << tiny_dnn::fully_connected_layer(n_source, n_nodes);
    net << tiny_dnn::tanh_layer();
}

bool tinydnnwrapper::createnetwork(const vector<int> &nodes)
{
    net << tiny_dnn::fully_connected_layer(nodes[0], nodes[1]);
    for (unsigned int i=1; nodes.size(); i++)
    {
        net << tiny_dnn::tanh_layer();
        net << tiny_dnn::fully_connected_layer(nodes[i], nodes[i+1]);
    }
    return true;

}


