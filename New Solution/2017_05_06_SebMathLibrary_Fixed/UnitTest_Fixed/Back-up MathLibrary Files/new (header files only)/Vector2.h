#pragma once

#include <MathLib_Utility.h>
#include <DLL.h>
///Vector2 = 2D Vector with no translation capabilities

template <class T>

class LIBRARY_API Vector2
{
public:
#pragma region Constructors
	Vector2() : x(0), y(0) {}

	Vector2(T a_x, T a_y) : x(a_x), y(a_y) {}
	
	Vector2(const Vector2 & a_rhs) : x(a_rhs.x), y(a_rhs.y) {}   //Copy/reference constructor
#pragma endregion

	///Variables
	union
	{
		struct { T x, y; };
		struct { T v[2]; };
	};
#pragma region Base Operators
	
	Vector2 operator+(const Vector2 & a_rhs) const                     // V2 = V2 + V2 
	{
		return Vector2<T>(x + a_rhs.x, y + a_rhs.y);                      // To avoid unresolved externals, specify what instance of Vector2 is being constructed
	}

	Vector2 operator-(const Vector2 & a_rhs) const					// V2 = V2 - V2 
	{
		return Vector2<T>(x - a_rhs.x, y - a_rhs.y);
	}
	
	Vector2& operator=(const Vector2 & a_rhs)                     // V2 = V2
	{
		x = a_rhs.x, y = a_rhs.y;
		return *this;                                           //Return de-referenced Vector2 after operations
	}

 	Vector2 operator*(T a_scalar) const                         // V2 = V2 * T (Scalar)
	{
		return Vector2<T>(x * a_scalar, y * a_scalar);

	}

	// Technically not apart of template class, must have separate LIBRARY_API
	LIBRARY_API friend Vector2 operator*(T a_scalar, const Vector2& a_rhs) {    // V2 = V2 * T OR T * V2
		return a_rhs * a_scalar;
	}

	Vector2 operator/(T a_scalar) const                         // V2 = V2 / T
	{
		return Vector2<T>(x / a_scalar, y / a_scalar);

	}

	Vector2 operator -() const                                 // -V2
	{
		return Vector2<T>(-x, -y);                          // Return negative version of Vector2
	}

	//Casts vector to float pointer
	explicit operator T*()                               // (T*)V2
	{
		return &x;											// * Return start of memory address for Vector2
	}

	T & operator[](unsigned int index)                  // V2[index]
	{
		return v[index];                                   // Return specified axis of Vector
	}
#pragma endregion

#pragma region Advanced Operators
	
	Vector2 & operator+=(const Vector2 & a_rhs)                // V2 += V2
	{
		*this = *this + a_rhs;                                 //Call upon + operator to simplify this operator
		return *this;
	}

	Vector2 & operator-=(const Vector2 & a_rhs)                // V2 -= V2
	{
		*this = *this - a_rhs;
		return *this;
	}
	
	Vector2 & operator*=(T a_scalar)                           // V2 *= T
	{
		*this = *this * a_scalar;
		return *this;
	}
	
	Vector2 & operator/=(T a_scalar)                          // V2 /= T
	{
		*this = *this / a_scalar;
		return *this;
	}
#pragma endregion

#pragma region Conditions
	
	bool operator==(const Vector2 & a_rhs) const
	{
		if (x == a_rhs.x && y == a_rhs.y) {              
			return true;
		}
		return false;
	}

	bool operator!=(const Vector2 & a_rhs) const
	{
		if (!(*this == a_rhs)) {
			return true;                                        //Yes, the vectors are not equal
		}
		return false;                                           //No, the vectors are equal
	}
#pragma endregion

#pragma region Functions
	
	T dot(const Vector2 & a_rhs)
	{
		return ((x * a_rhs.x) + (y * a_rhs.y));
	}

	T magnitude()
	{
		return T(sqrt14((x * x) + (y * y)));                       //Square root returns a double, typecast to float
	}
	
	void normalise()
	{
		T m = magnitude();                                        //Compute magnitude only once for efficiency
		x /= m, y /= m;
	}
	
	Vector2 getNormal()
	{
		T m = magnitude();
		return Vector2<T>(x /= m, y /= m);                       //Return normalized version of lhs
	}
#pragma endregion
};
