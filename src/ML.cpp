#include "ML.h"


double one=1;

CML::CML()
{
}


CML::~CML()
{
}


Vector CML::optimize(const Vector &X_0)
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
		CMatrix denum2 = diag_mat(denum1);
		CMatrix denum = denum1 + lambda*denum2;
		CVector dx = numerator / denum;
		if (Error(X - dx).norm2() > err_nrm)
			lambda *= 2;
		else
		{
			X -= dx;
			if (Error(X - dx).norm2()/ err_nrm>0.9) lambda/=2;
		}
		err_nrm_dev = (J*Error(X)).norm2();
		cout<<err_nrm<<","<<err_nrm_dev<<endl;
	}
	return X;
}


Matrix CML::Jacobian(const Vector &X_0)
{
	Matrix J;
	Vector F_base = (*func)(X_0);
	for (int i = 0; i < X_0.getsize(); i++)
	{
		Vector X = X_0;
		X[i] += epsilon;
		Vector F2 = (*func)(X);
		J.matr.push_back((F2 - F_base) / epsilon);
	}
	J.setnumcolrows();
	return J;

}

Vector CML::Error(const Vector &X_0)
{
	return (*func)(X_0) - Obs;

}

Vector CML::optimize(const Vector &X_0, ANN_class *ANN)
{
	CVector X = X_0;
	double err_nrm = Error(X_0, ANN).norm2();
	CMatrix J = Jacobian(X, ANN);
	double err_nrm_dev = (J*Error(X_0,ANN)).norm2();
	double lambda = 1;
	while (err_nrm_dev > tol)
	{
		J = Jacobian(X, ANN);
		Vector error = Error(X, ANN);
		err_nrm = error.norm2();
		Vector numerator = J*error;
		Matrix denum1 = J*Transpose(J);
		Matrix denum2 = diag_mat(denum1);
		Vector dx = numerator / (denum1 + lambda*denum2);
		if (Error(X - dx, ANN).norm2() > err_nrm)
			lambda *= 2;
		else
		{
			if (Error(X - dx, ANN).norm2() / err_nrm>0.9) lambda /= 2;
			X -= dx;
		}
		err_nrm_dev = (J*Error(X)).norm2();
		cout<<err_nrm<<","<<err_nrm_dev<<endl;
	}
	return X;
}


Matrix CML::Jacobian(const Vector &X_0, ANN_class *ANN)
{
	Matrix J;
	Vector F_base = (*ANN.*func_ann)(X_0);
	for (int i = 0; i < X_0.getsize(); i++)
	{
		Vector X = X_0;
		X[i] += epsilon;
		Vector F2 = (*ANN.*func_ann)(X);
		J.matr.push_back((F2 - F_base) / epsilon);
	}
	J.setnumcolrows();
	return J;

}

CVector CML::Error(const Vector &X_0, ANN_class *ANN)
{
	return (*ANN.*func_ann)(X_0) - Obs;

}



