#include "utils.h"
#include <fstream>
#include <sstream>
#include <algorithm>

#ifdef Q_version
QString aquiutils::vec2Qstring(vector<double> &v)
{
    QString s;
    s = "[";
    for (unsigned int i=0; i<v.size(); i++)
    {   s += QString::number(v[i]);
        if (i!=v.size()-1)
            s += ",";
    }
    s += "]";
    return s;
}

QString aquiutils::vec2Qstring(CVector &v)
{
    QString s;
    s = "[";
    for (int i=0; i<v.num; i++)
    {   s += QString::number(v[i]);
        if (i!=v.num-1)
            s += ",";
    }
    s += "]";
    return s;
}

QString aquiutils::vec2Qstring(CVector_arma &v)
{
    QString s;
    s = "[";
    for (int i=0; i<v.num; i++)
    {   s += QString::number(v[i]);
        if (i!=v.num-1)
            s += ",";
    }
    s += "]";
    return s;
}

QString aquiutils::mat2Qstring(CMatrix_arma &m)
{
    QString s;
    s = "[";
    for (int j=0; j<m.getnumrows(); j++ )
    {
        for (int i=0; i<m.getnumcols(); i++)
        {   s += QString::number(m(j,i));
            if (i!=m.getnumcols()-1)
                s += ",";
        }
        s += "\n";
    }
    s += "]";
    return s;
}

QString aquiutils::mat2Qstring(CMatrix &m)
{
    QString s;
    s = "[";
    for (int j=0; j<m.getnumrows(); j++ )
    {
        for (int i=0; i<m.getnumcols(); i++)
        {   s += QString::number(m[j][i]);
            if (i!=m.getnumcols()-1)
                s += ",";
        }
        s += "\n";
    }
    s += "]";
    return s;
}


#endif

int aquiutils::lookup(const vector<string> &s, const string &s1)
{
    for (unsigned int i=0; i<s.size(); i++)
        if (s[i]==s1)
            return i;
    return -1;
}

int aquiutils::lookup(const vector<int> &s, const int &s1)
{
    for (unsigned int i=0; i<s.size(); i++)
        if (s[i]==s1)
            return i;
    return -1;
}

int aquiutils::lookup(const vector<vector<int> > &s, const vector<int> &s1)
{
    for (unsigned int i=0; i<s.size(); i++)
        if (s[i]==s1)
            return i;
    return -1;
}

int aquiutils::corresponding_parenthesis(string S, int i)
{
	string s = S;
    if (S.at(i) == '(')
	{
		int paranthesis_level = 1;
		for (unsigned int j = i+1; j < S.size(); j++)
		{
            if (S.at(j) == '(')
				paranthesis_level++;
            if (S.at(j) == ')')
				paranthesis_level--;

			if (paranthesis_level == 0)
				return j;
		}
		return -1;
	}


    if (S.at(i) == ')')
	{
		int paranthesis_level = 1;
		for (int j = i-1; j > 0; j--)
		{
            if (S.at(j) == ')')
				paranthesis_level++;
            if (S.at(j) == '(')
				paranthesis_level--;

			if (paranthesis_level == 0)
				return j;
		}
		return -1;
	}
	return -1;
}

bool aquiutils::parantheses_balance(string S)
{
	if (count(S,"(") == count(S,")"))
		return true;
	else
		return false;
}

bool aquiutils::contains(const string &s, const string &s1)
{
    for (unsigned int i=0; i<s.size()-s1.size()+1; i++)
        if (s.substr(i,s1.size())==s1)
            return true;
    return false;
}

int aquiutils::count(const string &s, const string &s1)
{
    int out=0;
    for (unsigned int i=0; i<s.size()-s1.size()+1; i++)
        if (s.substr(i,s1.size())==s1)
            out++;
    return out;
}


string aquiutils::left(const string &s, int i)
{
    return s.substr(0,i);
}
string aquiutils::right(const string &s, int i)
{
    return s.substr(s.size()-i,i);
}

void aquiutils::remove(string &s,unsigned int i)
{
    string S;
    for (unsigned int j=0; j<s.size(); j++)
        if (i!=j)
            S = S + s[j];
    s = S;
}

void aquiutils::replace(string &s,unsigned int i,string p)
{
    string S;
    for (unsigned int j=0; j<s.size(); j++)
        if (i!=j)
            S = S + s[j];
        else
            S = S + p;
    s = S;
}

bool aquiutils::replace(string &s,string s1, string s2)
{

    bool found = false;
    vector<int> pos;
    unsigned int j=0;
    while (j<s.size()-s1.size()+1)
    {
        if (s.substr(j,s1.size())==s1)
        {
            pos.push_back(j);
            remove(s,j,s1.size());
            found = true;
        }
        j++;
    }
    for (unsigned int j=0; j<pos.size(); j++)
    {
        insert(s,pos[j]+j*s2.size(),s2);
    }

    return found;
}

bool aquiutils::remove(string &s, string s1)
{
    bool found = false;
    for (unsigned int j=0; j<s.size()-s1.size()+1; j++)
        if (s.substr(j,s1.size())==s1)
        {
            remove(s,j,s1.size());
            found = true;
        }
    return found;
}

void aquiutils::insert(string &s, unsigned int pos, string s1)
{
    string S;

    for (unsigned int i=0; i<s.size(); i++)
    {
        if (i==pos)
            S = S + s1;
        S = S + s[i];
    }
    if (pos==s.size()) S=S+s1;
    s = S;
}

void aquiutils::replace(string &s,unsigned int i, unsigned int j, string p)
{
    string S;
    for (unsigned int k=0; k<s.size(); k++)
        if (k==i)
            S = S + p;
        else if (k<i || k>=i+j)
            S = S + s[j];

    s = S;
}


void aquiutils::remove(string &s,unsigned int pos, unsigned int len)
{
    for (unsigned int i=pos; i<pos+len; i++)
        remove(s, pos);
}

bool aquiutils::isnumber(char S)
{
	if ((((int)S > 47) && ((int)S < 58)) || (S=='.'))
		return true;
	else
		return false;
}

bool aquiutils::isnumber(string S)
{
	bool res = true;
	for (unsigned int i = 0; i < S.size(); i++)
		if (!isnumber(S[i]))
			res = false;

	return res;
}


bool aquiutils::isintegernumber(string S)
{
	bool out = true;
	for (unsigned int i = 0; i < S.size(); i++)
	{
		if (((int)S[i] <= 47) || ((int)S[i] >= 58))
			out = false;
	}
	return out;
}

double aquiutils::atof(const string &S)
{
    return std::atof(S.c_str());
}
double aquiutils::atoi(const string &S)
{
    return std::atoi(S.c_str());
}

string aquiutils::trim(const string &s)
{
	if (s.find_first_not_of(' ') == string::npos) return "";

	return s.substr( s.find_first_not_of(' '), s.find_last_not_of(' ') + 1 );
}

void aquiutils::push_back(vector<string> &s, const vector<string> &s1)
{
    for (unsigned int i=0; i<s1.size(); i++)
        s.push_back(s1[i]);
}

vector<string> aquiutils::split(const string &s, char del)
{
	unsigned int lastdel=0;
	vector<string> strings;
	for (unsigned int i=0; i<s.size(); i++)
	{
		if (s[i]==del)
		{
			strings.push_back(s.substr(lastdel, i-lastdel));
			lastdel = i+1;
		}
	}
    if (lastdel<s.size() && trim(s.substr(lastdel, s.size()-lastdel))!="\r" && trim(s.substr(lastdel, s.size() - lastdel)) != "") strings.push_back(trim(s.substr(lastdel, s.size()-lastdel)));  // works w/o trim- Trim can be deleted
	for (unsigned int i=0; i<strings.size(); i++) strings[i] = trim(strings[i]);					// Trim can be deleted
	if (strings.size()==1)
        if (strings[0]=="")
            strings.pop_back();
	return strings;

}

vector<string> aquiutils::getline(ifstream& file)
{
	string line;

	while (!file.eof())
	{
		std::getline(file, line);
		return split(line,',');
	}
	vector<string> x;
	return x;
}

vector<string> aquiutils::getline(ifstream& file, char del1)
{
    string line;

	while (!file.eof())
	{
		std::getline(file, line);
		return split(line,del1);
	}
	vector<string> x;
	return x;
}

vector<vector<string>> aquiutils::getline_op(ifstream& file,char del1)
{
	string line;
	vector<vector<string>> s;
	vector<string> ss;
	while (file.good())
	{
		getline(file, line);
		ss = split(line,',');
		for (unsigned int i=0; i<ss.size(); i++)
			s.push_back(split(ss[i],del1));
	}
	return s;

}

vector<vector<string>> aquiutils::getline_op(ifstream& file,vector<char> del1)
{
		string line;
	vector<vector<string>> s;
	vector<string> ss;
	while (file.good())
	{
		getline(file, line);
		ss = split(line,',');
		for (unsigned int i=0; i<ss.size(); i++)
			s.push_back(split(ss[i],del1));
	}
	return s;
}

vector<vector<string>> aquiutils::getline_op_eqplus(ifstream& file)
{
	vector<char> del1;
	del1.push_back('=');
	del1.push_back('+');
	string line;
	vector<vector<string>> s;
	vector<string> ss;
	while (file.good())
	{
		getline(file, line);
		ss = split(line,',');
		for (unsigned int i=0; i<ss.size(); i++)
			s.push_back(split(ss[i],del1));
	}
	return s;


}

vector<string> aquiutils::split(const string &s, const vector<char> &del)
{
	unsigned int lastdel=0;
	unsigned int j=0;
	vector<string> strings;
	for (unsigned int i=0; i<s.size(); i++)
	{
		for (unsigned int jj=0; jj<del.size(); jj++)
		if (s[i]==del[jj])
		{
			strings.push_back(s.substr(lastdel, i-lastdel));
			lastdel = i+1;
			j++;
		}
	}
	if (lastdel<s.size()) strings.push_back(trim(s.substr(lastdel, s.size()-lastdel)));
	for (unsigned int i=0; i<strings.size(); i++) strings[i] = trim(strings[i]);
	return strings;

}

vector<string> aquiutils::split_curly_semicolon(string s)
{
	vector<char> del2; del2.push_back('{'); del2.push_back('}'); del2.push_back(';');
	return split(s,del2);
}

vector<int> aquiutils::look_up(string s, char del)  //Returns a vector with indices of "del"
{
	vector<int> out;
	for (unsigned int i=0; i<s.size(); i++)
		if (s[i]==del)
			out.push_back(i);

	return out;

}

vector<int> aquiutils::ATOI(vector<string> ii)
{
	vector<int> res;
	for (unsigned int i=0; i<ii.size(); i++)
		res.push_back(atoi(ii[i].c_str()));

	return res;
}

vector<double> aquiutils::ATOF(vector<string> ii)
{
	vector<double> res;
	for (unsigned int i=0; i<ii.size(); i++)
		res.push_back(atof(ii[i].c_str()));

	return res;
}


string aquiutils::tolower(const string &S)
{
	string SS = S;
	for (unsigned int i=0; i<S.size(); i++)
	{
		SS[i] = std::tolower(S[i]);
	}
	return SS;
}

vector<string> aquiutils::tolower(const vector<string> &S)
{
	vector<string> SS = S;
	for (unsigned int i = 0; i<S.size(); i++)
	{
		SS[i] = tolower(S[i]);
	}
	return SS;
}

void aquiutils::writeline(ofstream& f, vector<string> s, string del=",")
{
	for (unsigned int i=0; i<s.size()-1; i++)
		f<<s[i]<<del;
	f<<s[s.size()-1]<<endl;
}

void aquiutils::writeline(ofstream& f, vector<vector<string>> s, string del=",", string del2="&")
{
	for (unsigned int i=0; i<s.size()-1; i++)
	{	for (unsigned int j=0; j<s[i].size()-1; j++)
			f<<s[i][j]<<del2;
		f<<s[i][s[i].size()-1]<<del;
	}
	f<<s[s.size()-1][s[s.size()-1].size()-1]<<endl;
}
void aquiutils::writestring(ofstream& f, string s)
{
	f<<s;
}

void aquiutils::writestring(string filename, string s)
{
	ofstream file(filename);
	file << s + "\n";
	file.close();

}
void aquiutils::writenumber(ofstream& f, double s)
{
	f<<s;
}

void aquiutils::writeendl(ofstream& f)
{
	f<<endl;
}

double aquiutils::Heavyside(double x)
{
	if (x>0) return 1; else return 0;
}

double aquiutils::Pos(double x)
{
	if (x>0) return x; else return 0;
}

string aquiutils::numbertostring(double x)
{
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << x;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str();
	return Result;
}

string aquiutils::numbertostring(int x)
{
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << x;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str();
	return Result;
}

string aquiutils::tail(std::string const& source, size_t const length) {
	if (length >= source.size()) { return source; }
	return source.substr(source.size() - length);
} // tail

string aquiutils::tabs(int i)
{
    string out;
    for (int j=0; j<i; j++)
        out += "\t";
    return out;
}

bool aquiutils::And(vector<bool> x) { bool out = true;  for (int i = 0; i < x.size(); i++) out &= x[i]; return out; }
double aquiutils::max(vector<double> x) { double out = -1e+24;  for (int i = 0; i < x.size(); i++) out=std::max(out, x[i]); return out; }
int aquiutils::max(vector<int> x)
{	int out = -37000;
	for (int i = 0; i < x.size(); i++)
		out=std::max(out, x[i]);
	return out;

}

vector<int> aquiutils::random_vector(int min_range, int max_range, unsigned int number)
{
    vector<int> out;
    for (unsigned int i=0; i<number; i++)
    {
        out.push_back(int(unitrandom()*(max_range-min_range)+min_range));
    }
    return out;
}
