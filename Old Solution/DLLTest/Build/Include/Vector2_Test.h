#pragma once

#include <Utility_test.h>
#include <DLL_export.h>
///Vec2 = 2D Vector with no translation capabilities

template <class T>

class LIBRARY_API Vec2
{
public:
	///Constructor
	 Vec2();
	 Vec2(T a_x, T a_y);
	 Vec2(const Vec2& a_rhs); //Copy/reference constructor

	///Variables
	union
	{
		struct { T x, y; };
		struct { T v[2]; };
	};
#pragma region Base Operators
	 Vec2 operator + (const Vec2& a_rhs) const;

	 Vec2 operator - (const Vec2& a_rhs) const;

	 Vec2& operator = (const Vec2& a_rhs);

	template <typename S>       //Scalar
	 Vec2 operator * (S a_scalar) const;

	template <typename S>
	 friend Vec2 operator * (S a_scalar, const Vec2& a_rhs);

	 Vec2 operator -() const;
	///Conditions
	 bool operator == (const Vec2 &a_rhs) const;

	 bool operator != (const Vec2 &a_rhs) const;

#pragma endregion
	//Operators that rely on the base operators
#pragma region Advanced Operators
	 Vec2& operator += (const Vec2& a_rhs);

	 Vec2& operator -= (const Vec2& a_rhs);

	template <typename S>
	 Vec2& operator *= (S a_scalar);

	template <typename S>
	 Vec2& operator /= (S a_scalar);
#pragma endregion

#pragma region Functions
	 T dot(const Vec2& a_rhs);

	 T magnitude();

	 void normalize();

	 Vec2 getNormal();
#pragma endregion
	//Casts vector to float pointer
	 explicit operator T* ();

	 T & operator [] (unsigned int index);
};



