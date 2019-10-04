#pragma once
#include <vector>
#include "Vector.h"
#include "Matrix.h"
#include "ANN_class.h"

class CML
{
public:
	CML();
	~CML();
	CVector Obs; 
	CVector (ANN_class::*func_ann)(CVector X);
	CVector(*func)(CVector X);
	CVector CML::optimize(CVector X_0);
	CMatrix CML::Jacobian(CVector X_0);
	CVector CML::Error(CVector X_0);

	CVector CML::optimize(CVector X_0, ANN_class *ANN);
	CMatrix CML::Jacobian(CVector X_0, ANN_class *ANN);
	CVector CML::Error(CVector X_0, ANN_class *ANN);
	double epsilon;
	double tol;
};

