#pragma once
#include "Vector4.h"
#include "DLL.h"
template <class T>

///Matrix4 = 2D Matrix with no translation
class LIBRARY_API Matrix4
{
public:
	///Constructors
	Matrix4();

	Matrix4(Matrix4 &a_rhs);                      //Copy constructor, copy information from Matrix into the other

	Matrix4(float *a_ptr);                          //Construct from list of floats

	Matrix4(T a_m11, T a_m12, T a_m13, T a_m14,
		T a_m21, T a_m22, T a_m23, T a_m24,
		T a_m31, T a_m32, T a_m33, T a_m34,
		T a_m41, T a_m42, T a_m43, T a_m44);
	///Variables
	union
	{
		struct {
			T   m11, m12, m13, m14,
				m21, m22, m23, m24,
				m31, m32, m33, m34,
				m41, m42, m43, m44;
		};
		struct { T m[16]; };
		struct { T mm[4][4]; };
		struct { Vector4<T> v[4]; };               //Array of vectors (reads each row like a vector, do not use this to modify an axis!)
	};
#pragma region Base Operators
	Matrix4 operator * (const Matrix4 &a_rhs) const;

	Vector4<T> operator * (const Vector4<T> &a_rhs) const;           //Because we're not in the Vector4 template class, we need to specify what type it is in all uses.

	Matrix4 operator = (const Matrix4 &a_rhs);
#pragma endregion
	//Operators that rely on base operators
#pragma region Advanced Operators
	Matrix4& operator *=(const Matrix4 &a_rhs);
#pragma endregion

#pragma region Functions
	///Created out of the lhs
	static Matrix4 createIdentity();                                      //Return default matrix

	static Matrix4 createRotationX(float a_rot);

	static Matrix4 createRotationY(float a_rot);

	static Matrix4 createRotationZ(float a_rot);                         //Return rotated Matrix4

	static Matrix4 createScale(float a_xScale, float a_yScale, float a_zScale);           //Return scaled Matrix4
																						  ///Setters
	void set(float a_m11, float a_m12, float a_m21, float a_m22);   	// rebuild the matrix

	void set(float *a_ptr);                                        	// rebuild the matrix - expects pointer to array of 4 floats

	void setRotateX(float a_rot);

	void setRotateY(float a_rot);

	void setRotateZ(float a_rot);                                 // Rotate Matrix4 on the z axis circle

	void setScale(float a_scaleX, float a_scaleY, float a_scaleZ);                 // Scale matrix by given values

	void setTranslate(float a_transX, float a_transY, float a_transZ);

	Vector4 getTranslation();

	T getRotation(char a_axis);
#pragma endregion
	//Casts matrix to float pointer
	explicit operator T* () { return m; }                   //Return start of matrix memory address
	Vector4<T> & operator [] (unsigned int index) { return v[index]; } //Return vector at specified index
};


