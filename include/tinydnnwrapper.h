#ifndef TINYDNNWRAPPER_H
#define TINYDNNWRAPPER_H

#include "tiny_dnn.h"
#include <string>

using namespace std;

class tinydnnwrapper
{
public:
    tinydnnwrapper();
    bool addlayer(unsigned int n_source, unsigned int n_nodes, const string &activation_function);
    bool createnetwork(const vector<int> &nodes);
private:
    tiny_dnn::network<tiny_dnn::sequential> net;
};

#endif // TINYDNNWRAPPER_H
