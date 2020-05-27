

#include "Expression.h"
//#include "utility_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cmath>
#include <iostream>
#include <StateVariable.h>
#include <ExternalForcing.h>
#include <ControlParameter.h>
#include <fstream>
#include <sstream>
#include "System.h"
#include "utils.h"


using namespace aquiutils;

Expression::Expression(void)
{
	funcs.push_back("_min");
	funcs.push_back("_max");
	funcs.push_back("_exp");
	funcs.push_back("_log");
	funcs.push_back("_abs");
	funcs.push_back("_sqr");
	funcs.push_back("_pos");
	funcs.push_back("_hsd");
	opts.push_back("+");
	opts.push_back("-");
	opts.push_back("*");
	opts.push_back(";");
	opts.push_back("/");
	opts.push_back("^");

}

Expression::Expression(const string &_S, System *sys)
{
	string S = _S;
	text = S;
	#ifdef Debug_mode
	//cout<<text<<endl;
	#endif // Debug_mode

	funcs.push_back("_min");
	funcs.push_back("_max");
	funcs.push_back("_exp");
	funcs.push_back("_log");
	funcs.push_back("_abs");
	funcs.push_back("_sqr");
	funcs.push_back("_pos");
	funcs.push_back("_hsd");
	opts.push_back("+");
	opts.push_back("-");
	opts.push_back("*");
	opts.push_back(";");
	opts.push_back("/");
	opts.push_back("^");

	vector<string> out;
	//bool inside_quote = false;
	unsigned int paranthesis_level = 0;
	unsigned int last_operator_location = -1;
	if (!parantheses_balance(S))
	{
		_errors.push_back("Parentheses do not match in" + S);
		return;
	}
	if (lookup(funcs,left(S,4))!=-1)
	{
		function = right(left(S,4),3);
		S = right(S, S.size() - 4);
	}
	if (left(S,1) == "(")
	{
		if (corresponding_parenthesis(S,0) == -1 )
		{
			_errors.push_back("Parentheses do not match in" + S);
		}
		else if (corresponding_parenthesis(S,0) == int(S.size()-1))
		{
			remove(S,0);
			remove(S,S.size() - 1);
			//if (opts.contains(S.left(1)))
			//	terms.append(CExpression("0"));
			if (lookup(funcs,left(S,4))!=-1)
			{
				function = right(left(S,4),3);
			}

		}
	}
	if (isnumber(S))
	{
		param_constant_expression = "constant";
		constant = atof(S);
	}
	else
	{
		if (contains(S,"(") || contains(S,")") || contains(S,"+") || contains(S,"-") || contains(S,"*") || contains(S,"/") || contains(S,"^") || contains(S,";"))
		{
			param_constant_expression = "expression";
			for (unsigned int i = 0; i < S.size(); i++)
			{
				if (S.substr(i, 1) == "(")
					paranthesis_level++;

				if (S.substr(i, 1) == ")")
					paranthesis_level--;

				if (paranthesis_level == 0)
					if ((S.substr(i, 1) == "+") || (S.substr(i, 1) == "-") || (S.substr(i, 1) == "*") || (S.substr(i, 1) == "/") || (S.substr(i, 1) == "^"))
					{
						operators.push_back(S.substr(i, 1));
						Expression sub_exp = Expression(trim(S.substr(last_operator_location+1, i -1- last_operator_location)),sys);
						if (sub_exp.text != "")
						{
							if (operators.size() > 1)
								sub_exp.sign = operators[operators.size() - 2];
							else
								sub_exp.sign = "+";
							terms.push_back(sub_exp);
						}
						else
						{
							sub_exp = Expression("0",sys);
							sub_exp.sign = "+";
							terms.push_back(sub_exp);
						}
						push_back(_errors,sub_exp._errors);
						last_operator_location = i;
					}
			}

			Expression sub_exp = Expression(trim(S.substr(last_operator_location+1, S.size() - last_operator_location)),sys);
			if (operators.size() > 0)
				sub_exp.sign = operators[operators.size() - 1];
			else
				sub_exp.sign = "+";
			terms.push_back(sub_exp);
			push_back(_errors,sub_exp._errors);

		}
		else
		{
			if (sys->state(S))
            {
                param_constant_expression = "state";
                parameter = S;
            }
            else if (sys->exforce(S))
            {
                param_constant_expression = "exforce";
                parameter = S;
            }
            else if (sys->control(S))
            {
                param_constant_expression = "control";
                parameter = S;
            }
            else if (sys->parameter(S))
            {
                param_constant_expression = "parameter";
                parameter = S;
            }
            else
            {
                cout<<"Variable '" + S + "' was not found";
            }
		}
	}



}

Expression::Expression(const Expression & S)
{
	operators = S.operators;
	constant = S.constant;
	terms = S.terms;
	sign = S.sign;
	funcs = S.funcs;
	opts = S.opts;
	function = S.function;
	parameter = S.parameter;
	param_constant_expression = S.param_constant_expression;
	unit = S.unit;
	text = S.text;

}

Expression & Expression::operator=(const Expression &S)
{
	operators = S.operators;
	constant = S.constant;
	terms = S.terms;
	sign = S.sign;
	funcs = S.funcs;
	opts = S.opts;
	function = S.function;
	parameter = S.parameter;
	param_constant_expression = S.param_constant_expression;
	unit = S.unit;
	text = S.text;
	return *this;
}


Expression::~Expression(void)
{
}

vector<string> Expression::extract_operators(string s)
{
	vector<string> out;
	//bool inside_quote = false;
	int paranthesis_level = 0;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s.substr(i, 1) == "(")
			paranthesis_level++;

		if (s.substr(i, 1) == ")")
			paranthesis_level--;

		if (paranthesis_level == 0)
			if ((s.substr(i, 1) == "+") || (s.substr(i, 1) == "-") || (s.substr(i, 1) == "*") || (s.substr(i, 1) == "/") || (s.substr(i, 1) == "^")) out.push_back(s.substr(i, 1));


	}

	return out;
}

vector<string> Expression::extract_terms(string s)
{
	bool inside_quote = false;
	for (unsigned int i = 0; i < s.size(); i++)
	{
		if (s.substr(i, 1) == "'")
		{
			inside_quote = !inside_quote;
			remove(s, i);
		}
		if (inside_quote)
			if (s.substr(i, 1) == " ") replace(s, i, 1, "|");

	}
	vector<string> out = split(s,' ');
	for (unsigned int i = 0; i < out.size(); i++) replace(out[i],"|", " ");
	return out;
}


double Expression::calc(System *S, const timing &tmg, bool limit)
{
	if (!S)
	{
		cout << "Pointer is empty!" << endl;
		return 0;
	}

	term_vals.clear();
    terms_calculated.clear();
    sources.clear();

	if (param_constant_expression == "constant")
		return constant;
	if (param_constant_expression == "state" || param_constant_expression == "exforce" || param_constant_expression == "control" || param_constant_expression == "parameter")
	{
		return S->GetValue(parameter,tmg);
	}
	if (param_constant_expression == "expression")
	{

		for (unsigned int i = 0; i < terms.size(); i++)
		{
			sources.push_back(vector<int>());
			sources[i].push_back(i);
		}
		term_vals.resize(terms.size());
		for (unsigned int i = 0; i < terms.size(); i++) terms_calculated.push_back(false);

		if (operators.size()==0)
            term_vals[0] = terms[0].calc(S,tmg,limit);

		for (int i = operators.size() - 1; i >= 0; i--)
		{
			if (operators[i] == "^")
				oprt(operators[i], i, i + 1, S, tmg, limit);
		}
		for (int i = operators.size() - 1; i >= 0; i--)
		{
			if (operators[i] == "*")
				oprt(operators[i], i, i + 1, S, tmg, limit);
		}

		for (int i = operators.size() - 1; i >= 0; i--)
		{
			if (operators[i] == "/")
				oprt(operators[i], i, i + 1, S, tmg,limit);
		}

		for (int i = operators.size() - 1; i >= 0; i--)
		{
			if (operators[i] == "+")
				oprt(operators[i], i, i + 1, S, tmg,limit);

		}

		for (int i = operators.size() - 1; i >= 0; i--)
		{
			if (operators[i] == "-")
			{
				oprt(operators[i], i, i + 1, S, tmg,limit);
			}
		}

		if (function == "")
			return term_vals[0];
		else if (count_operators(";")==0)
			return func(function, term_vals[0]);
		else if (count_operators(";")==1)
			return func(function, term_vals[0], term_vals[1]);
        else if (count_operators(";")==2)
            return func(function, term_vals[0], term_vals[1], term_vals[2]);
	}


}


double Expression::func(string &f, double val)
{

	if (f == "exp")
		return exp(val);
	if (f == "log")
		return log(val);
	if (f == "abs")
		return fabs(val);
	if (f == "sqr")
		return sqrt(val);
    if (f == "pos")
        return (val+fabs(val))/2.0;
    if (f == "hsd")
    {
        if (val>=0) return 1; else return 0;
    }
	return val;
}

double Expression::func(string &f, double val1, double val2)
{
	if (f == "min")
		return min(val1, val2);
	if (f == "max")
		return max(val1, val2);
	return val1;
}

double Expression::func(string &f, double cond, double val1, double val2)
{
	if (f == "ups")
	{
        if (cond>=0)
            return val1;
        else
            return val2;
	}

	return val1;
}


double Expression::oprt(string &f, double val1, double val2)
{
	if (f == "^") return pow(val1, val2);
	if (f == "+") return val1 + val2;
	if (f == "-") return val1 + val2;
	if (f == "/") return val1 * val2;
	if (f == "*") return val1*val2;
	return 0;
}

double Expression::oprt(string &f, unsigned int i1, unsigned int i2, System *S, const Expression::timing &tmg, bool limit)
{

	#ifdef Debug_mode
	//cout<<i1<<","<<i2<<endl;
	#endif // Debug_mode
	for (unsigned int j = 0; j < sources[i1].size(); j++)
	{
		if (sources.size() > i2)
			for (unsigned int k=0; k<sources[i2].size(); k++)
                if (aquiutils::lookup(sources[sources[i2][k]],sources[i1][j])==-1) sources[sources[i2][k]].push_back(sources[i1][j]);

	}
	if (sources.size() > i2)
	for (unsigned int j = 0; j < sources[i2].size(); j++)
	{
		for (unsigned int k = 0; k<sources[i1].size(); k++)
            if (aquiutils::lookup(sources[sources[i1][k]],sources[i2][j])==-1) sources[sources[i1][k]].push_back(sources[i2][j]);

	}

	double val1;
	double val2;
	if (terms_calculated[i1]) val1 = term_vals[i1]; else val1 = terms[i1].calc(S, tmg, limit);
	if (terms[i1].sign == "/") val1 = 1/val1;
	if (terms[i1].sign == "-") val1 = -val1;
	if (sources.size() > i2)
		if (terms_calculated[i2]) val2 = term_vals[i2]; else
		{
			val2 = terms[i2].calc(S, tmg, limit);
			if (terms[i2].sign == "/") val2 = 1 / val2;
			if (terms[i2].sign == "-") val2 = -val2;
		}
	else
	{
		val1 = 0;
		val2 = val1;
	}

	if (unit == "")
	{
		if (terms[i1].unit != "") unit = terms[i1].unit;
		else if (terms[i2].unit != "") unit = terms[i2].unit;
	}

	for (unsigned int j = 0; j<sources[i1].size(); j++)
		term_vals[sources[i1][j]] = oprt(f, val1, val2);

	terms_calculated[i1] = true;
	terms_calculated[i2] = true;

	return term_vals[sources[i1][0]];
}

int Expression::lookup_operators(const string &s)
{
    for (int i=0; i<operators.size(); i++)
        if (operators[i]==s)
            return i;
    return -1;

}

int Expression::count_operators(const string &s)
{
    int count = 0;
    for (int i=0; i<operators.size(); i++)
        if (operators[i]==s)
            count ++;
    return count;

}



string Expression::ToString()
{
    string out;
    if (param_constant_expression=="parameter")
    {
        out += parameter;
        return out;
    }
    if (param_constant_expression=="constant")
    {
        out += constant;
        return out;
    }
    if (function!="") out += function;
    out += "(";
    for (int i=0; i<terms.size();i++)
    {
        out += terms[i].ToString();
        if (i<terms.size()-1) out += operators[i];
    }
    out += ")";
    return out;
}





