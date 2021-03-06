#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>

#include "Vector.h"
#include "Vector_arma.h"
#include "Matrix.h"
#include "Matrix_arma.h"
#include "NormalDist.h"


#ifdef Q_version
    #include <QStringList>
#endif


using namespace std;

namespace aquiutils
{
	int corresponding_parenthesis(string S, int i);
	bool parantheses_balance(string S);
	bool contains(const string& s, const string& s1);
	string left(const string& s, int i);
	string right(const string& s, int i);
	int count(const string& s, const string& s1);
	int lookup(const vector<string>& s, const string& s1);
	int lookup(const vector<int>& s, const int& s1);
	int lookup(const vector<vector<int> >& s, const vector<int>& s1);
	void remove(string& s, unsigned int i);
	void remove(string& s, unsigned int pos, unsigned int len);
	bool isnumber(char S);
	bool isnumber(string S);
	bool isintegernumber(string S);
	double atof(const string& S);
	double atoi(const string& S);
	string trim(const string& s);
	void push_back(vector<string>& s, const vector<string>& s1);
	void replace(string& s, unsigned int i, string p);
	void replace(string& s, unsigned int i, unsigned int j, string p);
	bool replace(string& s, string s1, string s2);
	bool remove(string& s, string s1);
	void insert(string& s, unsigned int pos, string s1);
	vector<string> split(const string& s, char del);
	vector<string> getline(ifstream& file);
	vector<string> getline(ifstream& file, char del1);
	vector<vector<string>> getline_op(ifstream& file, char del1);
	vector<vector<string>> getline_op(ifstream& file, vector<char> del1);
	vector<vector<string>> getline_op_eqplus(ifstream& file);
	vector<string> split(const string& s, const vector<char>& del);
	vector<string> split(const string& s, char del);
	vector<string> split_curly_semicolon(string s);
	vector<int> look_up(string s, char del);  //Returns a vector with indices of "del"
	vector<int> ATOI(vector<string> ii);
	vector<double> ATOF(vector<string> ii);
	string tolower(const string& S);
	vector<string> tolower(const vector<string>& S);
	void writeline(ofstream& f, vector<string> s, string del);
	void writeline(ofstream& f, vector<vector<string>> s, string del, string del2);
	void writestring(ofstream& f, string s);
	void writestring(string filename, string s);
	void writenumber(ofstream& f, double s);
	void writeendl(ofstream& f);
	double Heavyside(double x);
	double Pos(double x);
	string numbertostring(double x);
    string tail(string const& source, size_t const length);
	string numbertostring(int x);
	string tabs(int i);
	bool And(vector<bool> x);
	double max(vector<double> x);
	int max(vector<int> x);
    vector<int> random_vector(int min_range, int max_range, unsigned int number);

#ifdef Q_version
    QString vec2Qstring(vector<double> &v);
    QString vec2Qstring(CVector &v);
    QString vec2Qstring(CVector_arma &v);
    QString mat2Qstring(CMatrix_arma &m);
    QString mat2Qstring(CMatrix &m);
#endif

};


#endif // UTILS_H
