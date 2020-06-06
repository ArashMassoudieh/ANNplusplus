#include "rewardfunction.h"

#include "System.h"
#include "utils.h"


RewardFunction::RewardFunction()
{
    //ctor
}

RewardFunction::~RewardFunction()
{
    //dtor
}

RewardFunction& RewardFunction::operator=(const RewardFunction& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    immediatereward = rhs.immediatereward;
    Object::operator=(rhs);
    return *this;
}

RewardFunction::RewardFunction(const RewardFunction& other) :Object::Object(other)
{
    immediatereward = other.immediatereward;
}


double RewardFunction::CalculateImmediateReward(const Expression::timing &tm)
{
    if (Parent())
        return immediatereward.calc(Object::Parent(), tm);
    else {
        return 0;
    }
}


