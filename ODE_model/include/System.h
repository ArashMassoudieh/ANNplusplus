#ifndef SYSTEM_H
#define SYSTEM_H

#include "StateVariable.h"
#include "ControlParameter.h"
#include "ExternalForcing.h"
#include "Parameter.h"
#include <vector>
#include "Vector_arma.h"
#include "BTCSet.h"
#include "ErrorHandler.h"
#include "rewardfunction.h"
#include "tinydnnwrapper.h"
#define CVector_arma CVector
#define CMatrix_arma CMatrix

using namespace std;

class RunTimeWindow;

enum class object_type {state, control, exforce, parameter, not_found};

struct solversettings
{
    double C_N_weight; //Crank-Nicholson Weight
    double NRtolerance = 1e-6; //Newton Raphson Tolerance
    double NR_coeff_reduction_factor = 0.8; //The coefficient to reduce the Newton-Raphson coefficient
    double NR_timestep_reduction_factor = 0.75;
    double NR_timestep_reduction_factor_fail = 0.3;
    double minimum_timestep = 1e-7;
    int NR_niteration_lower=20;
    int NR_niteration_upper=40;
    int NR_niteration_max=100;
    bool makeresultsuniform = false;
};

struct _RL_params
{
    double learning_rate_alpha_prime;
    double discount_rate_lambda;
    double epoch_size;
};


struct outputs
{
    CBTCSet AllOutputs;
    CBTCSet ObservedOutputs;
};

struct solvertemporaryvars
{
    CMatrix_arma Inverse_Jacobian;
    double NR_coefficient = 1;
    bool updatejacobian = true;
    int numiterations;
    int epoch_count=0;
    string fail_reason;
    double t;
    double dt;
    double dt_base;
};

struct simulationparameters
{
    double tstart = 0; //start time of simulation
    double tend = 1; //end time of simulation
    double dt0 = 0.01; // initial time-step size
};

struct _directories
{
    string inputpath;
    string outputpath;
};


class System
{
    public:
        System();
        virtual ~System();
        System(const System& other);
        System& operator=(const System& other);
        Object *object(const string &s);
        StateVariable *state(const string &s);
        ControlParameter *control(const string &s);
        ExternalForcing *exforce(const string &s);
        Parameter *parameter(const string &s);
        RewardFunction* reward(const string &s);
        double GetValue(const string &param, Expression::timing tmg=Expression::timing::present);
        object_type GetType(const string &param);
        bool AppendState(const StateVariable &stt);
        bool AppendControlParameter(const ControlParameter &ctr);
        bool AppendExternalForcing(const ExternalForcing &extforce);
        bool AppendParameter(const Parameter &param);
        bool AppendReward(const RewardFunction &rwd);
        bool OneStepSolve();
        double dt() {return SolverTempVars.dt;}
        bool SetProp(const string &s, const double &val);
        ErrorHandler errorhandler;
        outputs Outputs;
        bool Solve();
        void ShowMessage(const string &msg);
        tinydnnwrapper *ann() {return &tdn;}
        void UpdateValue();
        void TrainANN();
        void InitiateANN(const vector<unsigned int> hiddenlayers);
        _RL_params rlparams;
        vector<state_value_pair> rltempvars;
        CVector& state_current();
        CVector& state_past();
        double value_current();
        double value_past();
        double reward_current();
        double reward_past();
        CVector EvaluateValue(const CVector &state);
        CVector CurrentState();
        unsigned long NumStates();
        double GetImmediateReward();
        RunTimeWindow *rtw = nullptr;
        void Write_State_Value_pairs(const string &filename);
    protected:

    private:
        void InitiateOutputs();
        void PopulateOutputs();
        void PrepareTimeSeries();
        void SetAllParents();
        vector<StateVariable> statevariables;
        vector<ControlParameter> controlparameters;
        vector<ExternalForcing> externalforcings;
        vector<Parameter> parameters;
        vector<RewardFunction> rewards;
        CVector_arma GetStateVariables(Expression::timing tmg);
        CVector_arma GetResiduals(CVector_arma &X);
        bool Renew();
        void SetStateVariables(CVector_arma &X,Expression::timing tmg = Expression::timing::present);
        solvertemporaryvars SolverTempVars;
        solversettings SolverSettings;
        simulationparameters SimulationParameters;
        CMatrix_arma Jacobian(CVector_arma &X);
        CVector_arma Jacobian(CVector_arma &V, CVector_arma &F0, int i);
        bool Update();
        double GetMinimumNextTimeStepSize();
        tinydnnwrapper tdn;
};

#endif // SYSTEM_H
