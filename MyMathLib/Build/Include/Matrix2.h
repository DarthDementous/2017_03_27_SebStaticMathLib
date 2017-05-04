#pragma once
#include "Vector2.h"
#include "DLL.h"
template <class T>

///Matrix2 = 2D Matrix with no translation
 class LIBRARY_API Matrix2
{
public:
	///Constructors
	Matrix2();

	Matrix2(Matrix2 &a_rhs);                      //Copy constructor, copy information from Matrix into the other

	Matrix2(float *a_ptr);                          //Construct from list of floats

	Matrix2(float a_m11, float a_m12, float a_m21, float a_m22);
	///Variables
	union
	{
		struct { T m11, m12, m21, m22; };
		struct { T m[4]; };
		struct { T mm[2][2]; };
		struct { Vector2<T> v[2]; };               //Array of vectors (reads each row like a vector, do not use this to modify an axis!)
	};
#pragma region Base Operators
	Matrix2 operator * (const Matrix2 &a_rhs) const;

	Vector2<T> operator * (const Vector2<T> &a_rhs) const;           //Because we're not in the Vector2 template class, we need to specify what type it is in all uses.

	Matrix2 operator = (const Matrix2 &a_rhs);
#pragma endregion
//Operators that rely on base operators
#pragma region Advanced Operators
	Matrix2& operator *=(const Matrix2 &a_rhs);
#pragma endregion

#pragma region Functions
	///Created out of the lhs
	static Matrix2 createIdentity();                                      //Return default matrix

	static Matrix2 createRotationZ(float a_rot);                         //Return rotated Matrix2

	static Matrix2 createScale(float a_xScale, float a_yScale);           //Return scaled Matrix2
	///Setters
	void set(float a_m11, float a_m12, float a_m21, float a_m22);   	// rebuild the matrix

	void set(float *a_ptr);                                        	// rebuild the matrix - expects pointer to array of 4 floats

	void setRotateZ(float a_rot);                                 // Rotate Matrix2 on the z axis circle

	void setScale(float a_scaleX, float a_scaleY);                 // Scale matrix by given values
#pragma endregion
	//Casts matrix to float pointer
	explicit operator T* () { return m; }                   //Return start of matrix memory address
	Vector2<T> & operator [] (unsigned int index) { return v[index]; } //Return vector at specified index
};


