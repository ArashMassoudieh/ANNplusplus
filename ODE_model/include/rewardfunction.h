#ifndef REWARDFUNCTION_H
#define REWARDFUNCTION_H

#include "Expression.h"
#include "BTC.h"
#include "Object.h"

enum class objfunctype {Integrate, Value, Maximum, Variance};

class RewardFunction : public Object
{
    public:
        RewardFunction();
        virtual ~RewardFunction();
        RewardFunction(const RewardFunction& other);
        RewardFunction& operator=(const RewardFunction& other);
        Expression &GetExpression() {return immediatereward; }
        double CalculateImmediateReward(const Expression::timing &tm = Expression::timing::present);
        void SetImmediateRewardFunction(const string &reward) {immediatereward = Expression(reward, Parent());}
    protected:

    private:
        Expression immediatereward;
};


#endif // REWARDFUNCTION_H
