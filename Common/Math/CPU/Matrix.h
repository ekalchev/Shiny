///////////////////////////////////////////////////////////////////////////////
//	File:    Matrix.h
//	Author:	 Emil Kalchev
//  E-mail:  developer@engineer.bg
///////////////////////////////////////////////////////////////////////////////

#ifndef __MATRIX__
#define __MATRIX__

class Matrix
{
public:
	union {

		struct {
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
			float _41, _42, _43, _44;

		};
		float m[4][4];
	};
public:
	Matrix::Matrix();
	Matrix::Matrix(const Matrix& mat);
};

#endif