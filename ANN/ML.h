#ifndef _CML
#define _CML

#include <vector>
#include "Vector.h"
#include "Matrix.h"
#include "ANN_class.h"

#define Matrix CMatrix
#define Vector CVector


class CML
{
public:
	CML();
	~CML();
	Vector Obs;
	Vector (ANN_class::*func_ann)(const Vector &X);
	Vector(*func)(const CVector &X);
	Vector optimize(const CVector &X_0);
	Matrix Jacobian(const CVector &X_0);
	Vector Error(const CVector &X_0);

	Vector optimize(const CVector &X_0, ANN_class *ANN);
	Matrix Jacobian(const CVector &X_0, ANN_class *ANN);
	Vector Error(const CVector &X_0, ANN_class *ANN);
	double epsilon;
	double tol;
};

#endif // _CML

