#pragma once

#include <MathLib_Utility.h>
#include <DLL.h>
///Vector3 = 3D Vector with no translation capabilities

template <class T>

class LIBRARY_API Vector3
{
public:
#pragma region Constructors
	
	Vector3() : x(0), y(0), z(0) {}

	
	Vector3(T a_x, T a_y, T a_z) : x(a_x), y(a_y), z(a_z) {}

	
	Vector3(const Vector3 & a_rhs) : x(a_rhs.x), y(a_rhs.y), z(a_rhs.z) {}   //Copy/reference constructor

#pragma endregion

								   ///Variables
	union
	{
		struct { T x, y, z; };
		struct { T v[3]; };
	};
#pragma region Base Operators
	
	Vector3 operator+(const Vector3 & a_rhs) const                     // V2 = V2 + V2 
	{
		return Vector3<T>(x + a_rhs.x, y + a_rhs.y, z + a_rhs.z);             //Constructing a template class, have to specify the data-type in <T>
	}

	
	Vector3 operator-(const Vector3 & a_rhs) const					// V2 = V2 - V2 
	{
		return Vector3<T>(x - a_rhs.x, y - a_rhs.y, z - a_rhs.z);
	}

	
	Vector3 & operator=(const Vector3 & a_rhs)
	{
		x = a_rhs.x, y = a_rhs.y, z = a_rhs.z;
		return *this;                                           //Return de-referenced Vector3 after operations
	}

	
	Vector3 operator*(T a_scalar) const
	{
		return Vector3<T>(x * a_scalar, y * a_scalar, z * a_scalar);

	}

	// Technically not apart of template class, must have separate LIBRARY_API
	LIBRARY_API friend Vector3 operator*(T a_scalar, const Vector3& a_rhs) {    // V3 = V3 * T OR T * V3
		return a_rhs * a_scalar;
	}
	
	Vector3 operator/(T a_scalar) const
	{
		return Vector3<T>(x / a_scalar, y / a_scalar, z / a_scalar);

	}

	
	Vector3 operator -() const
	{
		return Vector3<T>(-x, -y, -z);                          // Return negative version of vector3
	}

	
	//Casts vector to float pointer
	explicit operator T*()
	{
		return &x;											// * Return start of memory address for Vector3
	}

	
	T & operator[](unsigned int index)
	{
		return v[index];                                   // Return specified axis of Vector
	}
#pragma endregion

#pragma region Advanced Operators
	
	Vector3 & operator+=(const Vector3 & a_rhs)
	{
		*this = *this + a_rhs;                                 //Call upon + operator to simplify this operator
		return *this;
	}

	
	Vector3 & operator-=(const Vector3 & a_rhs)
	{
		*this = *this - a_rhs;
		return *this;
	}

	
	Vector3 & operator*=(T a_scalar)
	{
		*this = *this * a_scalar;
		return *this;
	}

	
	Vector3 & operator/=(T a_scalar)
	{
		*this = *this / a_scalar;
		return *this;
	}
#pragma endregion

#pragma region Conditions
	
	bool operator==(const Vector3 & a_rhs) const
	{
		if (x == a_rhs.x && y == a_rhs.y && z == a_rhs.z) {              //Also compare translation points, Point != Vector
			return true;
		}
		return false;
	}

	
	bool operator!=(const Vector3 & a_rhs) const
	{
		if (!(*this == a_rhs)) {
			return true;                                        //Yes, the vectors are not equal
		}
		return false;                                           //No, the vectors are equal
	}
#pragma endregion

#pragma region Functions
	
	T dot(const Vector3 & a_rhs)
	{
		return ((x * a_rhs.x) + (y * a_rhs.y) + (z * a_rhs.z));
	}

	
	Vector3 cross(const Vector3& a_rhs) {
		/*
		x   a_x         x | y z x y | z
		y   a_y         x | y z x y | z
		z   a_z
		*/
		return Vector3<T>((y * a_rhs.z - z * a_rhs.y), (z * a_rhs.x - x * a_rhs.z), (x * a_rhs.y - y * a_rhs.x));
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

	
	Vector3 getNormal()
	{
		T m = magnitude();
		return Vector3<T>(x /= m, y /= m, z /= m);                       //Return normalized version of lhs
	}
#pragma endregion
};


