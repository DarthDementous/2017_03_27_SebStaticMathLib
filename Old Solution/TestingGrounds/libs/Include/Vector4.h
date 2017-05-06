#pragma once

#include <MathLib_Utility.h>
#include <DLL.h>
///Vector4 = 2D Vector with no translation capabilities

template <class T>

class LIBRARY_API Vector4
{
public:
	///Constructor
	Vector4();
	Vector4(T a_x, T a_y, T a_z, T a_w);
	Vector4(const Vector4& a_rhs); //Copy/reference constructor

								   ///Variables
	union
	{
		struct { T x, y, z, w; };
		struct { T v[4]; };
	};
#pragma region Base Operators
	Vector4 operator + (const Vector4& a_rhs) const;

	Vector4 operator - (const Vector4& a_rhs) const;

	Vector4& operator = (const Vector4& a_rhs);

	template <typename S>       //Scalar
	Vector4 operator * (S a_scalar) const;

	//Friends require treating the declaration like the definition (using class with <T>)
	template <class T, typename S>
	friend Vector4<T> operator * (S a_scalar, const Vector4<T>& a_rhs);

	Vector4 operator -() const;
	///Conditions
	bool operator == (const Vector4 &a_rhs) const;

	bool operator != (const Vector4 &a_rhs) const;

#pragma endregion
	//Operators that rely on the base operators
#pragma region Advanced Operators
	Vector4& operator += (const Vector4& a_rhs);

	Vector4& operator -= (const Vector4& a_rhs);

	template <typename S>
	Vector4& operator *= (S a_scalar);

	template <typename S>
	Vector4& operator /= (S a_scalar);
#pragma endregion

#pragma region Functions
	T dot(const Vector4& a_rhs);										// dot product, checks if vectors cast a shadow

	Vector4 cross(const Vector4& a_rhs);                               // Returns vector perpendicular to the two vectors

	T magnitude();                                                  // magnitude, get length of vector

	void normalise();                                               // divide by magnitude

	Vector4 getNormal();
#pragma endregion
	//Casts vector to float pointer
	explicit operator T* ();

	T & operator [] (unsigned int index);
};



