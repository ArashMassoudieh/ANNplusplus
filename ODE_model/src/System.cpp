#include "System.h"
#include <iostream>
#include "Vector_arma.h"
#include "Matrix_arma.h"
#include "utils.h"
#include "runtimewindow.h"

using namespace std;
System::System()
{
    //ctor
}

System::~System()
{
    //dtor
}

System::System(const System& other)
{
    statevariables = other.statevariables;
    externalforcings = other.externalforcings;
    controlparameters = other.controlparameters;
    parameters = other.parameters;
    rewards = other.rewards;
}

System& System::operator=(const System& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    statevariables = rhs.statevariables;
    externalforcings = rhs.externalforcings;
    controlparameters = rhs.controlparameters;
    parameters = rhs.parameters;
    rewards = rhs.rewards;
    return *this;
}

Object* System::object(const string &s)
{
    for (unsigned int i=0; i<statevariables.size(); i++)
        if (statevariables[i].GetName() == s)
            return &statevariables[i];

    for (unsigned int i=0; i<externalforcings.size(); i++)
        if (externalforcings[i].GetName() == s)
            return &externalforcings[i];

    for (unsigned int i=0; i<controlparameters.size(); i++)
        if (controlparameters[i].GetName() == s)
            return &controlparameters[i];

    for (unsigned int i=0; i<parameters.size(); i++)
        if (parameters[i].GetName() == s)
            return &parameters[i];

    for (unsigned int i=0; i<rewards.size(); i++)
        if (rewards[i].GetName() == s)
            return &rewards[i];

    return nullptr;
}

void System::SetAllParents()
{
    for (unsigned int i=0; i<statevariables.size(); i++)
        statevariables[i].SetParent(this);

    for (unsigned int i=0; i<externalforcings.size(); i++)
        externalforcings[i].SetParent(this);

    for (unsigned int i=0; i<controlparameters.size(); i++)
        controlparameters[i].SetParent(this);

    for (unsigned int i=0; i<parameters.size(); i++)
        parameters[i].SetParent(this);

}


object_type System::GetType(const string &param)
{
    for (unsigned int i=0; i<statevariables.size(); i++)
        if (statevariables[i].GetName() == param)
            return object_type::state;

    for (unsigned int i=0; i<externalforcings.size(); i++)
        if (externalforcings[i].GetName() == param)
            return object_type::exforce;

    for (unsigned int i=0; i<controlparameters.size(); i++)
        if (controlparameters[i].GetName() == param)
            return object_type::control;

    for (unsigned int i=0; i<parameters.size(); i++)
        if (parameters[i].GetName() == param)
            return object_type::parameter;

    return object_type::not_found;
}

StateVariable* System::state(const string &s)
{
    for (unsigned int i=0; i<statevariables.size(); i++)
        if (statevariables[i].GetName() == s)
            return &statevariables[i];

    return nullptr;
}

ControlParameter* System::control(const string &s)
{
    for (unsigned int i=0; i<controlparameters.size(); i++)
        if (controlparameters[i].GetName() == s)
            return &controlparameters[i];

    return nullptr;
}

ExternalForcing* System::exforce(const string &s)
{
    for (unsigned int i=0; i<externalforcings.size(); i++)
        if (externalforcings[i].GetName() == s)
            return &externalforcings[i];
    return nullptr;
}

Parameter* System::parameter(const string &s)
{
    for (unsigned int i=0; i<parameters.size(); i++)
        if (parameters[i].GetName() == s)
            return &parameters[i];
    return nullptr;
}

RewardFunction* System::reward(const string &s)
{
    for (unsigned int i=0; i<rewards.size(); i++)
        if (rewards[i].GetName() == s)
            return &rewards[i];
    return nullptr;
}


double System::GetValue(const string &param, Expression::timing tmg)
{
    if (GetType(param) == object_type::state)
        return state(param)->GetValue(tmg);

    if (GetType(param) == object_type::control)
        return control(param)->GetValue(tmg);

    if (GetType(param) == object_type::exforce)
        return exforce(param)->Object::GetValue(tmg);

    if (GetType(param) == object_type::parameter)
        return parameter(param)->Object::GetValue(tmg);
}

bool System::AppendState(const StateVariable &stt)
{
    if (object(stt.GetName())!=nullptr)
    {
        cout<<"Object '" + stt.GetName() + "' already exists!";
        return false;
    }
    else
    {
        statevariables.push_back(stt);
        state(stt.GetName())->SetParent(this);
        return true;
    }

}

bool System::AppendControlParameter(const ControlParameter &ctr)
{
    if (object(ctr.GetName())!=nullptr)
    {
        cout<<"Object '" + ctr.GetName() + "' already exists!";
        return false;
    }
    else
    {
        controlparameters.push_back(ctr);
        control(ctr.GetName())->SetParent(this);
        return true;
    }
}

bool System::AppendReward(const RewardFunction &rwd)
{
    if (object(rwd.GetName())!=nullptr)
    {
        cout<<"Object '" + rwd.GetName() + "' already exists!";
        return false;
    }
    else
    {
        rewards.push_back(rwd);
        reward(rwd.GetName())->SetParent(this);
        return true;
    }
}

bool System::AppendExternalForcing(const ExternalForcing &extforce)
{
    if (object(extforce.GetName())!=nullptr)
    {
        cout<<"Object '" + extforce.GetName() + "' already exists!";
        return false;
    }
    else
    {
        externalforcings.push_back(extforce);
        exforce(extforce.GetName())->SetParent(this);
        return true;
    }
}

bool System::AppendParameter(const Parameter &param)
{
    if (object(param.GetName())!=nullptr)
    {
        cout<<"Object '" + param.GetName() + "' already exists!";
        return false;
    }
    else
    {
        parameters.push_back(param);
        parameter(param.GetName())->SetParent(this);
        return true;
    }
}


bool System::OneStepSolve()
{
    CVector_arma X_past = GetStateVariables(Expression::timing::past);
    Renew();

    CVector_arma X = GetStateVariables(Expression::timing::past);
    CVector_arma F = GetResiduals(X);

    double err_ini = F.norm2();
    double err;
    double err_p = err = err_ini;
    SolverTempVars.numiterations = 0;
    bool switchvartonegpos = true;
    int attempts = 0;
    while (attempts<2 && switchvartonegpos)
    {
        while (err/err_ini>SolverSettings.NRtolerance && err>1e-12)
        {
            SolverTempVars.numiterations++;
            if (SolverTempVars.updatejacobian)
            {
                CMatrix_arma M = Jacobian(X);
                SolverTempVars.Inverse_Jacobian = Invert(M);
                SolverTempVars.updatejacobian = false;
                SolverTempVars.NR_coefficient = 1;
            }
            X = X - SolverTempVars.NR_coefficient*SolverTempVars.Inverse_Jacobian*F;
            F = GetResiduals(X);
            err_p = err;
            err = F.norm2();

            #ifdef Debug_mode
                ShowMessage(numbertostring(err));
            #endif // Debug_mode
            if (err>err_p)
            {
                SolverTempVars.NR_coefficient*=SolverSettings.NR_coeff_reduction_factor;
                X = X_past;
                F = GetResiduals(X);
            }                //else
            //    SolverTempVars.NR_coefficient/=SolverSettings.NR_coeff_reduction_factor;
            if (SolverTempVars.numiterations>SolverSettings.NR_niteration_max)
            {
                SetStateVariables(X_past,Expression::timing::past);
                return false;
            }
        }
        switchvartonegpos = false;
    }

	#ifdef Debug_mode
//	CMatrix_arma M = Jacobian("Storage",X);
//	M.writetofile("M.txt");
	#endif // Debug_mode
	return true;
}

bool System::Renew()
{
	bool out = true;
	for (unsigned int i = 0; i < statevariables.size(); i++)
		statevariables[i].Renew();

	return out;
}

CVector_arma System::GetStateVariables(Expression::timing tmg)
{
    CVector_arma out;
    for (unsigned int i = 0; i < statevariables.size(); i++)
    {
        if (tmg == Expression::timing::past)
            out.append(statevariables[i].GetValue(Expression::timing::past));
        else
            out.append(statevariables[i].GetValue(Expression::timing::present));
    }
    return out;
}

void System::SetStateVariables(CVector_arma &X,Expression::timing tmg)
{
    for (unsigned int i = 0; i < statevariables.size(); i++)
    {
        if (tmg == Expression::timing::past)
            statevariables[i].SetValue(X[i], Expression::timing::past);
        else
            statevariables[i].SetValue(X[i],Expression::timing::present);
    }

}

CVector_arma System::GetResiduals(CVector_arma &X)
{
    CVector_arma F(statevariables.size());
    SetStateVariables(X,Expression::timing::present);

    for (unsigned int i=0; i<statevariables.size(); i++)
    {
            F[i] = (X[i]-statevariables[i].GetValue(Expression::timing::past))/dt() - statevariables[i].GetRateOfChange(Expression::timing::present);
    }

    return F;
}

CMatrix_arma System::Jacobian(CVector_arma &X)
{
    CMatrix_arma M(X.num);

    CVector_arma F0 = GetResiduals(X);
    for (int i=0; i < X.num; i++)
    {
        CVector_arma V = Jacobian(X, F0, i);
        for (int j=0; j<X.num; j++)
            M[i][j] = V[j];
    }

  return Transpose(M);
}


CVector_arma System::Jacobian(CVector_arma &V, CVector_arma &F0, int i)
{
  double epsilon;
  epsilon = -1e-6;
  CVector_arma V1(V);
  V1[i] += epsilon;
  CVector_arma F1;
  F1 = GetResiduals(V1);
  CVector_arma grad = (F1 - F0) / epsilon;
  if (grad.norm2() == 0)
  {
    epsilon = 1e-6;
    V1 = V;
    V1[i] += epsilon;
    F1 = GetResiduals(V1);
    grad = (F1 - F0) / epsilon;
  }
  return grad;

}

bool System::SetProp(const string &s, const double &val)
{
    if (s=="cn_weight")
    {   SolverSettings.C_N_weight = val; return true;}
    if (s=="nr_tolerance")
    {   SolverSettings.NRtolerance = val; return true;}
    if (s=="nr_coeff_reduction_factor")
    {   SolverSettings.NR_coeff_reduction_factor = val; return true;}
    if (s=="nr_timestep_reduction_factor")
    {   SolverSettings.NR_timestep_reduction_factor = val; return true;}
    if (s=="nr_timestep_reduction_factor_fail")
    {   SolverSettings.NR_timestep_reduction_factor_fail = val; return true;}
    if (s=="minimum_timestep")
    {   SolverSettings.minimum_timestep = val; return true;}
    if (s=="nr_niteration_lower")
    {   SolverSettings.NR_niteration_lower=int(val); return true;}
    if (s=="nr_niteration_upper")
    {   SolverSettings.NR_niteration_upper=int(val); return true;}
    if (s=="nr_niteration_max")
    {   SolverSettings.NR_niteration_max=int(val); return true;}
    if (s=="make_results_uniform")
    {   SolverSettings.makeresultsuniform = bool(val); return true;}

    if (s=="tstart")
    {   SimulationParameters.tstart = val; return true;}
    if (s=="tend")
    {   SimulationParameters.tend = val; return true;}
    if (s=="tend")
    {   SimulationParameters.dt0 = val; return true;}

    errorhandler.Append("","System","SetProp","Property '" + s + "' was not found!", 621);
    return false;
}

void System::InitiateOutputs()
{
    Outputs.AllOutputs.clear();

    for (unsigned int i=0; i<statevariables.size(); i++)
        Outputs.AllOutputs.append(CBTC(), statevariables[i].GetName());

    for (unsigned int i=0; i<controlparameters.size(); i++)
        Outputs.AllOutputs.append(CBTC(), controlparameters[i].GetName());

    for (unsigned int i=0; i<externalforcings.size(); i++)
        Outputs.AllOutputs.append(CBTC(), externalforcings[i].GetName());

    for (unsigned int i=0; i<rewards.size(); i++)
        Outputs.AllOutputs.append(CBTC(), rewards[i].GetName());

}


void System::PopulateOutputs()
{
    for (unsigned int i=0; i<statevariables.size(); i++)
        Outputs.AllOutputs[statevariables[i].GetName()].append(SolverTempVars.t,statevariables[i].GetValue());

    for (unsigned int i=0; i<controlparameters.size(); i++)
        Outputs.AllOutputs[controlparameters[i].GetName()].append(SolverTempVars.t,controlparameters[i].GetValue());

    for (unsigned int i=0; i<externalforcings.size(); i++)
        Outputs.AllOutputs[externalforcings[i].GetName()].append(SolverTempVars.t,externalforcings[i].Object::GetValue());

    for (unsigned int i=0; i<rewards.size(); i++)
        Outputs.AllOutputs[rewards[i].GetName()].append(SolverTempVars.t,rewards[i].Object::GetValue());

}

bool System::Solve()
{
    #ifdef QT_version
    if (LogWindow())
    {
        LogWindow()->append("Simulation started!");
    }
    #else
        ShowMessage("Simulation started!");
    #endif
    SetAllParents();
    InitiateOutputs();
    PrepareTimeSeries();
    SolverTempVars.dt_base = SimulationParameters.dt0;
    SolverTempVars.dt = SolverTempVars.dt_base;
    SolverTempVars.t = SimulationParameters.tstart;
    PopulateOutputs();
    while (SolverTempVars.t<SimulationParameters.tend+SolverTempVars.dt)
    {
        SolverTempVars.dt = min(SolverTempVars.dt_base,GetMinimumNextTimeStepSize());
        if (SolverTempVars.dt<SimulationParameters.dt0/100) SolverTempVars.dt=SimulationParameters.dt0/100;
        ShowMessage(string("t = ") + aquiutils::numbertostring(SolverTempVars.t));
        #ifdef Debug_mode
        ShowMessage(string("t = ") + aquiutils::numbertostring(SolverTempVars.t) + ", dt_base = " + numbertostring(SolverTempVars.dt_base) + ", dt = " + numbertostring(SolverTempVars.dt) + ", SolverTempVars.numiterations =" + numbertostring(SolverTempVars.numiterations));
        #endif // Debug_mode

        if (rtw)
        {
            rtw->SetProgress((SolverTempVars.t-SimulationParameters.tstart)/(SimulationParameters.tend-SimulationParameters.tstart));
            QCoreApplication::processEvents();
        }


        bool success = OneStepSolve();
        if (!success)
        {
            #ifdef Debug_mode
            ShowMessage("failed!");
            #endif // Debug_mode
            SolverTempVars.dt_base *= SolverSettings.NR_timestep_reduction_factor_fail;
            SolverTempVars.updatejacobian = true;
        }
        else
        {
            SolverTempVars.t += SolverTempVars.dt;
            if (SolverTempVars.numiterations>SolverSettings.NR_niteration_upper)
            {
                SolverTempVars.dt_base = max(SolverTempVars.dt*SolverSettings.NR_timestep_reduction_factor,SolverSettings.minimum_timestep);
                SolverTempVars.updatejacobian = true;
            }
            if (SolverTempVars.numiterations<SolverSettings.NR_niteration_lower)
                SolverTempVars.dt_base = min(SolverTempVars.dt_base/SolverSettings.NR_timestep_reduction_factor,SimulationParameters.dt0*10);
            ShowMessage("t = " + aquiutils::numbertostring(SolverTempVars.t));
            Update();
            UpdateValue();
            PopulateOutputs();

            //UpdateObjectiveFunctions(SolverTempVars.t);
        }

    }

    ShowMessage("Simulation finished!");

    return true;
}

bool System::Update()
{
	bool out = true;
	for (unsigned int i = 0; i < externalforcings.size(); i++)
		externalforcings[i].UpdateValue(SolverTempVars.t);

    for (unsigned int i = 0; i < rewards.size(); i++)
        rewards[i].UpdateValue(SolverTempVars.t);

	return out;
}

void System::ShowMessage(const string &msg) {cout<<msg<<endl;}

double System::GetMinimumNextTimeStepSize()
{
    double x=1e12;

    for (unsigned int i=0; i<externalforcings.size(); i++)
    {
        x = min(x,externalforcings[i].TimeSeries()->interpol_D(this->SolverTempVars.t));
    }
    return x;
}

void System::PrepareTimeSeries()
{
    for (unsigned int i=0; i<externalforcings.size();i++)
    {
        externalforcings[i].TimeSeries()->assign_D();
    }
}

void System::UpdateValue()
{
    state_value_pair current_state_value;
    current_state_value.state = CurrentState();
    current_state_value.reward = GetImmediateReward();
    double value_past = value_current();
    double value_current = EvaluateValue(current_state_value.state)[0];
    current_state_value.reward = GetImmediateReward();
    current_state_value.value = rlparams.discount_rate_lambda*value_past + rlparams.learning_rate_alpha_prime*(rlparams.discount_rate_lambda*value_current - value_past + current_state_value.reward );
    rltempvars.push_back(current_state_value);
    tdn.AppendtoInput(current_state_value.state);
    tdn.AppendtoTarget(current_state_value.value);
    unsigned long zero = 0;
    if (rltempvars.size()%tdn.batch_size==1)
    {
        tdn.trainonebatch(std::max(rltempvars.size()-tdn.batch_size-1,zero),int(tdn.batch_size),rtw);
    }

}

void System::TrainANN()
{

}

void System::InitiateANN(const vector<unsigned int> hiddenlayers)
{
    vector<unsigned int> layers;
    layers.push_back(NumStates());
    for (unsigned int i=0; i<hiddenlayers.size(); i++)
    {
        layers.push_back(hiddenlayers[i]);
    }
    layers.push_back(1);
    tdn.createnetwork(layers);
    state_value_pair _state_past;
    _state_past.state = CVector(NumStates());
    _state_past.value = 0;
    _state_past.reward = 0;
    rltempvars.push_back(_state_past);
}

double System::GetImmediateReward()
{
    double out = 0;
    for (unsigned int i=0; i<rewards.size(); i++)
        out += rewards[i].GetValue(SolverTempVars.t);

    return out;
}

CVector System::EvaluateValue(const CVector &state)
{
    return tdn.predicted(state);
}

CVector System::CurrentState()
{
    CVector out;
    for (unsigned int i=0; i<statevariables.size(); i++)
        out.append(statevariables[i].GetValue());

    for (unsigned int i=0; i<externalforcings.size(); i++)
        out.append(externalforcings[i].Object::GetValue());

    return out;
}

unsigned long System::NumStates()
{
    return statevariables.size()+externalforcings.size();

}

CVector& System::state_current()
{
    if (rltempvars.size()>0)
        return rltempvars[rltempvars.size()-1].state;
}
CVector& System::state_past()
{
    if (rltempvars.size()>1)
        return rltempvars[rltempvars.size()-2].state;

}
double System::reward_current()
{
    if (rltempvars.size()>0)
        return rltempvars[rltempvars.size()-1].reward;
    return 0;
}
double System::reward_past()
{
    if (rltempvars.size()>1)
        return rltempvars[rltempvars.size()-2].reward;
    return 0;
}

double System::value_current()
{
    if (rltempvars.size()>0)
        return rltempvars[rltempvars.size()-1].value;
    return 0;
}
double System::value_past()
{
    if (rltempvars.size()>1)
        return rltempvars[rltempvars.size()-1].value;
    return 0;
}

void System::Write_State_Value_pairs(const string &filename){
    ofstream file;
    file.open (filename);
    for (unsigned int i=0; i<rltempvars.size(); i++)
    {
        for (unsigned int j=0; j<rltempvars[i].state.num; j++)
        {
            file << rltempvars[i].state[j] << ",";
        }
        file << rltempvars[i].value << ",";
        file << rltempvars[i].reward << endl;
    }

    file.close();


}

