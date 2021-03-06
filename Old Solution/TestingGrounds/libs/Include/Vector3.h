#pragma once

#include <MathLib_Utility.h>
#include <DLL.h>
///Vector3 = 2D Vector with no translation capabilities

template <class T>

class LIBRARY_API Vector3
{
public:
	///Constructor
	Vector3();
	Vector3(T a_x, T a_y, T a_z);
	Vector3(const Vector3& a_rhs); //Copy/reference constructor

								   ///Variables
	union
	{
		struct { T x, y, z; };
		struct { T v[3]; };
	};
#pragma region Base Operators
	Vector3 operator + (const Vector3& a_rhs) const;

	Vector3 operator - (const Vector3& a_rhs) const;

	Vector3& operator = (const Vector3& a_rhs);

	template <typename S>       //Scalar
	Vector3 operator * (S a_scalar) const;

	//Friends require treating the declaration like the definition (using class with <T>)
	template <class T, typename S>
	friend Vector3<T> operator * (S a_scalar, const Vector3<T>& a_rhs);

	Vector3 operator -() const;
	///Conditions
	bool operator == (const Vector3 &a_rhs) const;

	bool operator != (const Vector3 &a_rhs) const;

#pragma endregion
	//Operators that rely on the base operators
#pragma region Advanced Operators
	Vector3& operator += (const Vector3& a_rhs);

	Vector3& operator -= (const Vector3& a_rhs);

	template <typename S>
	Vector3& operator *= (S a_scalar);

	template <typename S>
	Vector3& operator /= (S a_scalar);
#pragma endregion

#pragma region Functions
	T dot(const Vector3& a_rhs);										// dot product, checks if vectors cast a shadow

	Vector3 cross(const Vector3& a_rhs);                               // Returns vector perpendicular to the two vectors

	T magnitude();                                                  // magnitude, get length of vector

	void normalise();                                               // divide by magnitude

	Vector3 getNormal();
#pragma endregion
	//Casts vector to float pointer
	explicit operator T* ();

	T & operator [] (unsigned int index);
};



