#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>
#include <vector>

class System;

using namespace std;

class Expression
{
    public:
        virtual ~Expression();
        Expression(void);
        Expression(const string &S, System *sys);
        Expression(const Expression &S);
        Expression& operator=(const Expression&);
        vector<string> operators;
        vector<Expression> terms;
        string sign;
        string function;
        string parameter;
        double constant;
        string param_constant_expression;
        vector<string> extract_operators(string s);
        vector<string> _errors;
        vector<string> extract_terms(string s);
        enum class timing {past, present, both};
        double calc(System *S, const timing &tmg, bool limit = false);
        double func(string & f, double val);
        double func(string & f, double val1, double val2);
        double func(string &f, double cond, double val1, double val2);
        double oprt(string & f, double val1, double val2);
        double oprt(string & f, unsigned int i1, unsigned int i2, System * S, const timing &tmg, bool limit=false);
        vector<string> funcs;
        string unit;
        string text;
        vector<string> opts;
        int lookup_operators(const string &s);
        int count_operators(const string &s);
        string ToString();
    protected:

    private:
        vector<double> term_vals;
        vector<bool> terms_calculated;
        vector<vector<int> > sources;


};


#endif // EXPRESSION_H
