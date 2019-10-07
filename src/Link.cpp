
#include "Link.h"
#include "Node.h"

double Link::GetSourceVal()
{
	return Source->output_val;
}

double Link::Val()
{
	return GetSourceVal(); 
}

Link::Link(const Link& m)
{
	ID = m.GetID; 
	weight = m.weight; 
	SourceID = m.SourceID;
	TargetID = m.TargetID;

}

Link::Link(string s, string _sourceID, string _targetID)
{
	ID = s; 
	SourceID = _sourceID; 
	TargetID = _targetID;
}

Link& Link::operator=(const Link& m)
{
	ID = m.ID;
	weight = weight;
	SourceID = m.SourceID;
	TargetID = m.TargetID; 
}
