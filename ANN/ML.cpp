#include "ML.h"



CML::CML()
{
}


CML::~CML()
{
}


CVector CML::optimize(CVector X_0)
{
	CVector X = X_0;
	double err_nrm = Error(X_0).norm2();
	CMatrix J = Jacobian(X);
	double err_nrm_dev = (J*Error(X_0)).norm2();
	double lambda = 1;
	while (err_nrm_dev > tol)
	{
		CMatrix J = Jacobian(X);
		CVector error = Error(X);
		err_nrm = error.norm2();
		CVector numerator = J*error;
		CMatrix denum1 = J*Transpose(J);
		CMatrix denum2 = diag_mat(J*Transpose(J));
		CVector dx = numerator / (denum1 + lambda*denum2);
		if (Error(X - dx).norm2() > err_nrm)
			lambda *= 2;
		else
		{
			X -= dx;
			if (Error(X - dx).norm2()/ err_nrm>0.9) lambda/=2;
		}
		err_nrm_dev = (J*Error(X_0)).norm2();
	}
	return X; 
}


CMatrix CML::Jacobian(CVector X_0)
{
	CMatrix J;
	CVector F_base = (*func)(X_0);
	for (int i = 0; i < X_0.getsize(); i++)
	{
		CVector X = X_0;
		X[i] += epsilon;
		CVector F2 = (*func)(X);
		J.matr.push_back((F2 - F_base) / epsilon);
	}
	J.setnumcolrows();
	return J;

}

CVector CML::Error(CVector X_0)
{
	return (*func)(X_0) - Obs;
	
}

CVector CML::optimize(CVector X_0, ANN_class *ANN)
{
	CVector X = X_0;
	double err_nrm = Error(X_0, ANN).norm2();
	double lambda = 1;
	while (err_nrm > tol)
	{
		CMatrix J = Jacobian(X, ANN);
		CVector error = Error(X, ANN);
		err_nrm = error.norm2();
		CVector numerator = J*error;
		CMatrix denum1 = J*Transpose(J);
		CMatrix denum2 = diag_mat(max(J*Transpose(J),1));
		CVector dx = numerator / (denum1 + lambda*denum2);
		if (Error(X - dx, ANN).norm2() > err_nrm)
			lambda *= 2;
		else
		{
			X -= dx;
			if (Error(X - dx, ANN).norm2() / err_nrm>0.9) lambda /= 2;
		}
	}
	return X;
}


CMatrix CML::Jacobian(CVector X_0, ANN_class *ANN)
{
	CMatrix J;
	CVector F_base = (*ANN.*func_ann)(X_0); 
	for (int i = 0; i < X_0.getsize(); i++)
	{
		CVector X = X_0;
		X[i] += epsilon;
		CVector F2 = (*ANN.*func_ann)(X);
		J.matr.push_back((F2 - F_base) / epsilon);
	}
	J.setnumcolrows();
	return J;

}

CVector CML::Error(CVector X_0, ANN_class *ANN)
{
	return (*ANN.*func_ann)(X_0) - Obs;

}



