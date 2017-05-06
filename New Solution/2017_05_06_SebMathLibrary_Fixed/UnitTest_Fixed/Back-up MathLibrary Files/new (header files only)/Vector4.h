#pragma once

#include <MathLib_Utility.h>
#include <DLL.h>
///Vector4 = 2D Vector with no translation capabilities

template <class T>

class LIBRARY_API Vector4
{
public:
#pragma region Constructors
	
	Vector4() : x(0), y(0), z(0), w(0) {}

	
	Vector4(T a_x, T a_y, T a_z, T a_w) : x(a_x), y(a_y), z(a_z), w(a_w) {}

	
	Vector4(const Vector4 & a_rhs) : x(a_rhs.x), y(a_rhs.y), z(a_rhs.z), w(a_rhs.w) {}   //Copy/reference constructor

#pragma endregion

								   ///Variables
	union
	{
		struct { T x, y, z, w; };
		struct { T v[4]; };
	};
#pragma region Base Operators
	
	Vector4 operator+(const Vector4 & a_rhs) const                     // V2 = V2 + V2 
	{
		return Vector4<T>(x + a_rhs.x, y + a_rhs.y, z + a_rhs.z, w + a_rhs.w); //Constructing a template class, have to specify the data-type in <T>
	}

	
	Vector4 operator-(const Vector4 & a_rhs) const					// V2 = V2 - V2 
	{
		return Vector4<T>(x - a_rhs.x, y - a_rhs.y, z - a_rhs.z, w - a_rhs.w);
	}

	
	Vector4 & operator=(const Vector4 & a_rhs)
	{
		x = a_rhs.x, y = a_rhs.y, z = a_rhs.z, w = a_rhs.w;
		return *this;                                           //Return de-referenced Vector4 after operations
	}

	
	Vector4 operator*(T a_scalar) const
	{
		return Vector4<T>(x * a_scalar, y * a_scalar, z * a_scalar, w * a_scalar);

	}

	// Technically not apart of template class, must have separate LIBRARY_API
	LIBRARY_API friend Vector4 operator*(T a_scalar, const Vector4& a_rhs) {    // V4 = V4 * T OR T * V4
		return a_rhs * a_scalar;
	}

	
	Vector4 operator/(T a_scalar) const
	{
		return Vector4<T>(x / a_scalar, y / a_scalar, z / a_scalar, w / a_scalar);

	}

	
	Vector4 operator -() const
	{
		return Vector4<T>(-x, -y, -z, -w);                          // Return negative version of Vector4
	}

	
	//Casts vector to float pointer
	operator T*()
	{
		return &x;											// * Return start of memory address for Vector4
	}

	
	T & operator[](unsigned int index)
	{
		return v[index];                                   // Return specified axis of Vector
	}
#pragma endregion

#pragma region Advanced Operators
	
	Vector4 & operator+=(const Vector4 & a_rhs)
	{
		*this = *this + a_rhs;                                 //Call upon + operator to simplify this operator
		return *this;
	}

	
	Vector4 & operator-=(const Vector4 & a_rhs)
	{
		*this = *this - a_rhs;
		return *this;
	}

	
	Vector4 & operator*=(T a_scalar)
	{
		*this = *this * a_scalar;
		return *this;
	}

	
	Vector4 & operator/=(T a_scalar)
	{
		*this = *this / a_scalar;
		return *this;
	}
#pragma endregion

#pragma region Conditions
	
	bool operator==(const Vector4 & a_rhs) const
	{
		if (x == a_rhs.x && y == a_rhs.y && z == a_rhs.z && w == a_rhs.w) {              //Also compare translation points, Point != Vector
			return true;
		}
		return false;
	}

	
	bool operator!=(const Vector4 & a_rhs) const
	{
		if (!(*this == a_rhs)) {
			return true;                                        //Yes, the vectors are not equal
		}
		return false;                                           //No, the vectors are equal
	}
#pragma endregion

#pragma region Functions
	
	T dot(const Vector4 & a_rhs)
	{
		return ((x * a_rhs.x) + (y * a_rhs.y) + (z * a_rhs.z));
	}

	
	Vector4 cross(const Vector4& a_rhs) {
		/*
		x   a_x         x | y z x y | z
		y   a_y         x | y z x y | z
		z   a_z
		*/
		return Vector4<T>((y * a_rhs.z - z * a_rhs.y), (z * a_rhs.x - x * a_rhs.z), (x * a_rhs.y - y * a_rhs.x), w * a_rhs.w);
	}

	
	T magnitude()
	{
		return T(sqrt14((x * x) + (y * y) + (z * z)));                       //Square root returns a double, typecast to float
	}

	
	void normalise()
	{
		T m = magnitude();                                        //Compute magnitude only once for efficiency
		x /= m, y /= m, z /= m;
	}

	
	Vector4 getNormal()
	{
		T m = magnitude();
		return Vector4<T>(x /= m, y /= m, z /= m, w);                       //Return normalized version of lhs
	}
#pragma endregion
};


