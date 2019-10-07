#ifndef  LINK_H
#define LINK_H

#include <string>

using namespace std; 

class CNode;

class Link
{
private:
	CNode* Source; 
	CNode* Target;
	double weight; 
	string ID; 
public:
	string SourceID, TargetID;
	CNode* GetSource() { return Source; }
	CNode* GetTarget() { return Target; }
	void SetSource(CNode *source) { Source = source; }
	void SetTarget(CNode *target) { Target = target; }
	double GetSourceVal(); 
	void SetWeight(double w) { weight = w; }
	double GetWeight() { return weight; }
	string GetID() { return ID; }
	bool SetID(string id) { ID = id;  }
	double Val();
	Link(const Link& m);
	Link(string s, string sourceID, string targetID);
	Link& operator=(const Link& m);

};

#endif // ! Link_H
