///////////////////////////////////////////////////////////////////////////////
//	File:    Matrix.cpp
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////


#include "stdafx.h"
#include "Matrix.h"
#include <memory.h>


//initialized to identity matrix
Matrix::Matrix()
{
	memset(this,0,sizeof(Matrix));
	_11 = _22 = _33 = _44 = 1.0f;
}

Matrix::Matrix(const Matrix& mat)
{
	memcpy(this,&mat,sizeof(Matrix));
}
