#pragma once
#include "Vector2.h"
#include "DLL.h"
template <class T>

///Matrix2 = 2D Matrix with no translation
/*
NOTE: When using template classes outside of their header file the paramater list must be provided through <T> in ALL instances.
*/
class LIBRARY_API Matrix2
{
public:
#pragma region Constructors
	Matrix2() : m11(1), m12(0),                                      //Identity by default
		m21(0), m22(1) {}

	Matrix2(Matrix2 &a_rhs) : m11(a_rhs.m11), m12(a_rhs.m12),
		m21(a_rhs.m21), m22(a_rhs.m22) {}                   //Copy constructor, copy information from Matrix into the other

	Matrix2(T *a_ptr) : m11(a_ptr[0]), m12(a_ptr[1]),                          //Construct from list of floats
		m21(a_ptr[2]), m22(a_ptr[3]) {}

	Matrix2(T a_m11, T a_m12, T a_m21, T a_m22) : m11(a_m11), m12(a_m12),
		m21(a_m21), m22(a_m22) {}
#pragma endregion
	///Variables
	union
	{
		struct { T m11, m12, m21, m22; };
		struct { T m[4]; };
		struct { T mm[2][2]; };
		struct { Vector2<T> v[2]; };               //Array of vectors (reads each row like a vector, do not use this to modify an axis!)
	};
#pragma region Base Operators
	Matrix2 operator * (const Matrix2 &a_rhs) const {          // m2 * m2
		/*
		[m11, m12]      *     [a_m11, a_m12]
		[m21, m22]            [a_m21, a_m22]
		*/
		return Matrix2<T>(
			(m11 * a_rhs.m11 + m12 * a_rhs.m21), (m11 * a_rhs.m12 + m12 * a_rhs.m22),
			(m21 * a_rhs.m11 + m22 * a_rhs.m21), (m21 * a_rhs.m12 + m22 * a_rhs.m22)
			);
	}
	
	Vector2<T> operator * (const Vector2<T> &a_rhs) const {    // m2 * v2
		/*
		[m11, m12]      *     [x,         =   [c_m11]
		[m21, m22]             y]             [c_m21]
		*/
		return Vector2<T>(
			(m11 * a_rhs.x + m21 * a_rhs.y),       //NOTE: When multiplying a matrice with a vector, it has to be treated cxr instead of rxc because the vector is
			(m12 * a_rhs.x + m22 * a_rhs.y)		   //technically a row vector, even though we're still getting the rows from the lhs and the columns from the rhs.
			);					   
	}

	Matrix2& operator = (const Matrix2 &a_rhs) {                  // m2 = m2
		m11 = a_rhs.m11, m12 = a_rhs.m12;
		m21 = a_rhs.m21, m22 = a_rhs.m22;
		return *this;
	}

	//Casts matrix to float pointer
	explicit operator T* () { return m; }                   //Return start of matrix memory address

	Vector2<T> & operator [] (unsigned int index) { return v[index]; } //Return vector at specified index
#pragma endregion
//Operators that rely on base operators
#pragma region Advanced Operators
	Matrix2& operator *=(const Matrix2 &a_rhs) {               //m2 *= m2
		*this = *this * a_rhs;                     //De-reference 'this' for multiplication
		return *this;
	}
#pragma endregion

#pragma region Functions
	static Matrix2 createIdentity() {                                      //Return default matrix
		return Matrix2<T>(
			1, 0,
			0, 1
			);
	}

	static Matrix2 createRotationZ(float a_rot) {                          //return Matrix2<T> for rotating around Z axis
		return Matrix2<T>(
			(T)cosf(a_rot), (T)sinf(a_rot),
		   -(T)sinf(a_rot), (T)cosf(a_rot)
			);
	}

	static Matrix2 createScale(T a_xScale, T a_yScale) {				  //return Matrix2<T> for scaling
		return Matrix2<T>(
			a_xScale, 0,
			0, a_yScale
			);
	}

	///Setters
	void set(T a_m11, T a_m12, T a_m21, T a_m22)   	// rebuild the matrix
	{
		m11 = a_m11, m12 = a_m12;
		m21 = a_m21, m22 = a_m22;
	}

	void set(T *a_ptr)                                        	// rebuild the matrix - expects pointer to array of 4 floats
	{
		//Assign values with for loop for readability
		auto index = 0;
		for (auto r = 0; r < 2; r++) {
			for (auto c = 0; c < 2; c++) {
				mm[r][c] = a_ptr[index];
				index++;
			}
		}
	}

	void setRotateZ(float a_rot)                                 // Rotate Matrix2 on the z axis circle
	{
		m11 = (T)cosf(a_rot), m12 = (T)sinf(a_rot);
		m21 = -(T)sinf(a_rot), m22 = (T)cosf(a_rot);
	}

	void setScale(T a_scaleX, T a_scaleY)                 // Scale matrix by given values
	{
		mm[0][0] = a_scaleX; //Xx
		mm[1][1] = a_scaleY; //Yy
	}
#pragma endregion
};
