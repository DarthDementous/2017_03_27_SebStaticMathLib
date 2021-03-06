#include "Matrix4.h"
#include <cassert>
#include <math.h>

///Constructors
template<class T>
Matrix4<T>::Matrix4() : m11(1), m12(0), m13(0), m14(0),                                                       //Identity by default
m21(0), m22(1), m23(0), m24(0),
m31(0), m32(0), m33(1), m34(0),
m41(0), m42(0), m43(0), m44(1) {}

template<class T>
Matrix4<T>::Matrix4(const Matrix4 &a_rhs) : m11(a_rhs.m11), m12(a_rhs.m12), m13(a_rhs.m13), m14(a_rhs.m14),    //Copy constructor, copy information from Matrix into the other
m21(a_rhs.m21), m22(a_rhs.m22), m23(a_rhs.m23), m24(a_rhs.m24),
m31(a_rhs.m31), m32(a_rhs.m32), m33(a_rhs.m33), m34(a_rhs.m34),
m41(a_rhs.m41), m42(a_rhs.m42), m43(a_rhs.m43), m44(a_rhs.m44) {}

template<class T>
Matrix4<T>::Matrix4(T *a_ptr) : m11(a_ptr[0]), m12(a_ptr[1]), m13(a_ptr[2]), m14(a_ptr[3]),                       //Construct from list of type T
m21(a_ptr[4]), m22(a_ptr[5]), m23(a_ptr[6]), m24(a_ptr[7]),
m31(a_ptr[8]), m32(a_ptr[9]), m33(a_ptr[10]), m34(a_ptr[11]),
m41(a_ptr[12]), m42(a_ptr[13]), m43(a_ptr[14]), m44(a_ptr[15]) {}

template<class T>
Matrix4<T>::Matrix4(T a_m11, T a_m12, T a_m13, T a_m14,
	T a_m21, T a_m22, T a_m23, T a_m24,
	T a_m31, T a_m32, T a_m33, T a_m34,
	T a_m41, T a_m42, T a_m43, T a_m44) : m11(a_m11), m12(a_m12), m13(a_m13), m14(a_m14),
	m21(a_m21), m22(a_m22), m23(a_m23), m24(a_m24),
	m31(a_m31), m32(a_m32), m33(a_m33), m34(a_m34),
	m41(a_m41), m42(a_m42), m43(a_m43), m44(a_m44) {}

#pragma region Base Operators
template<class T>
Matrix4<T> Matrix4<T>::operator * (const Matrix4 &a_rhs) const {
	/*
	[m11, m12, m13, m14]      *     [a_m11, a_m12, a_m13, a_m14]
	[m21, m22, m23, m24]            [a_m21, a_m22, a_m23, a_m24]
	[m31, m32, m33, m34]			[a_m31, a_m32, a_m33, a_m34]
	[m41, m42, m43, m44]            [a_m41, a_m42, a_m43, a_m44]
	*/
	Matrix4<T> tmp;
	//Do the matrix multiplication process in a for-loop for readability
	for (auto r = 0; r < 4; r++) {
		for (auto c = 0; c < 4; c++) {
			tmp.mm[r][c] = (mm[0][c] * a_rhs.mm[r][0] +                    //For each position, find the value for the equivalent position and it to the new Matrix
				mm[1][c] * a_rhs.mm[r][1] +
				mm[2][c] * a_rhs.mm[r][2] +
				mm[3][c] * a_rhs.mm[r][3]);
		}
	}
	return tmp;
}

template<class T>
Vector4<T> Matrix4<T>::operator * (const Vector4<T> &a_rhs) const {                      //Because we're not in the Vector4 template class, we need to specify what type it is in all uses.
	/*
	[m11, m12, m13, m14]      *     [x,         =   [c_m11]
	[m21, m22, m23, m24]             y,             [c_m21]
	[m31, m32, m33, m34]			 z,	            [c_m31]
	[m41, m42, m43, m44]			 w]             [c_m41]
	*/
	return Vector4<T>
		((m11 * a_rhs.x + m12 * a_rhs.y + m13 * a_rhs.z + m14 * a_rhs.w), 
		 (m21 * a_rhs.x + m22 * a_rhs.y + m23 * a_rhs.z + m24 * a_rhs.w), 
		 (m31 * a_rhs.x + m32 * a_rhs.y + m33 * a_rhs.z + m34 * a_rhs.w),
		 (m41 * a_rhs.x + m42 * a_rhs.y + m43 * a_rhs.z + m44 * a_rhs.w));
}

template<class T>
Matrix4<T> Matrix4<T>::operator = (const Matrix4 &a_rhs) {
	m11 = a_rhs.m11, m12 = a_rhs.m12, m13 = a_rhs.m13, m14 = a_rhs.m14;
	m21 = a_rhs.m21, m22 = a_rhs.m22, m23 = a_rhs.m23, m24 = a_rhs.m24;
	m31 = a_rhs.m31, m32 = a_rhs.m32, m33 = a_rhs.m33, m34 = a_rhs.m34;
	m41 = a_rhs.m41, m42 = a_rhs.m42, m43 = a_rhs.m43, m44 = a_rhs.m44;
	return *this;
}
#pragma endregion
//Operators that rely on base operators
#pragma region Advanced Operators
template<class T>
Matrix4<T>& Matrix4<T>::operator *=(const Matrix4 &a_rhs) {
	*this = *this * a_rhs;
	return *this;
}
#pragma endregion

#pragma region Functions
template<class T>
Matrix4<T> Matrix4<T>::createLookAt(const Vector4<T> &a_position, const Vector4<T> &a_target, const Vector4<T> &a_worldUp)
{
	// Locate camera in world space and transform to camera space (camera is at origin looking in positive z-direction)
	// Relocate objects in world space around camera's position (origin of camera space) AND orientation
	/* METHODS TO CREATE A VIEW MATRIX
	1. V = T * Rz * Ry * Rx     (combine translation matrix with rotation matrices for each axis)
		V - View matrix
		T - Translation matrix to reposition objects in the world
		Rn - Rotation matrices that rotate objects along -x, -y and -z axis respectively

		E.g. camera position is <10, 20, 100> pointing straight down
		T - Move objects -10 on x axis, -20 on y axis and -100 on z axis
		Rn - Compensates for how much the axes of camera space are rotated out of alignment with world space by applying rotations of equal BUT negative values to models in the scene:
			Rotation matrix on the x axis -90 degrees
		V - Result of combining translation matrix with rotation matrix so that the top of objects faces the character, making it seem like the camera is above the model
	*/
#if 1
	Matrix4<T> tmp;

	Vector4<T> Zaxis = normal(a_target - a_position);           // f Front
	Vector4<T> Xaxis = normal(cross(Zaxis, a_worldUp));         // s Side
	Vector4<T> Yaxis = cross(Xaxis, Zaxis);                     // u Up

	// Column major, negative z for openGL
	tmp[0][0] = Xaxis.x;
	tmp[1][0] = Xaxis.y;
	tmp[2][0] = Xaxis.z;
	tmp[0][1] = Yaxis.x;
	tmp[1][1] = Yaxis.y;
	tmp[2][1] = Yaxis.z;
	tmp[0][2] = -Zaxis.x;
	tmp[1][2] = -Zaxis.y;
	tmp[2][2] = -Zaxis.z;
	tmp[3][0] = -dot(Xaxis, a_position);
	tmp[3][1] = -dot(Yaxis, a_position);
	tmp[3][2] = dot(Zaxis, a_position);

	return tmp;

#endif
}
// OpenGL code
template<class T>
Matrix4<T> Matrix4<T>::createPerspective(T fovY, T aspect, T zNear, T zFar)
{
	// Check if values are valid
	assert(aspect != 0);
	assert(zFar != zNear);

	T tanHalfFovY = tan(fovY / 2);

	Matrix4<T> tmp;
	tmp.mm[0][0] = 1 / (aspect * tanHalfFovY);
	tmp.mm[1][1] = 1 / (tanHalfFovY);
	tmp.mm[2][2] = -(zFar + zNear) / (zFar - zNear);
	tmp.mm[2][3] = -1;
	tmp.mm[3][2] = -(2 * zFar * zNear) / (zFar - zNear);
	
	return tmp;
}
///Created out of the lhs
template<class T>
Matrix4<T> Matrix4<T>::createIdentity() {                                      //Return default matrix
	return Matrix4<T>
		(1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1);
}

template<class T>
Matrix4<T> Matrix4<T>::createRotationX(float a_rot) {                          //Return rotated Matrix4
	Matrix4<T> tmp;
	//Express via indexes for readability, we only change the relevant default values.
	//Do not touch axis or values for what we're rotating with. (X and x in this case)
	tmp.mm[1][1] = (T)cosf(a_rot);    //Yy
	tmp.mm[2][1] = -(T)sinf(a_rot);    //Yz
	tmp.mm[1][2] = (T)sinf(a_rot);   //Zy
	tmp.mm[2][2] = (T)cosf(a_rot);    //Zz
	return tmp;
}

template<class T>
Matrix4<T> Matrix4<T>::createRotationY(float a_rot) {                          //Return rotated Matrix4
	Matrix4<T> tmp;
	tmp.mm[0][0] = (T)cosf(a_rot);   //Xx
	tmp.mm[2][0] = (T)sinf(a_rot);   //Xz
	tmp.mm[0][2] = -(T)sinf(a_rot);  //Zx
	tmp.mm[2][2] = (T)cosf(a_rot);   //Zz
	return tmp;
}

template<class T>
Matrix4<T> Matrix4<T>::createRotationZ(float a_rot) {                          //Return rotated Matrix4
	Matrix4<T> tmp;
	tmp.mm[0][0] = (T)cosf(a_rot);   //Xx
	tmp.mm[1][0] = -(T)sinf(a_rot);  //Xy
	tmp.mm[0][1] = (T)sinf(a_rot);   //Yx
	tmp.mm[1][1] = (T)cosf(a_rot);   //Yy
	return tmp;
}

template<class T>
Matrix4<T> Matrix4<T>::createScale(T a_xScale, T a_yScale, T a_zScale) {           //Return scaled Matrix4
	Matrix4<T> tmp;
	tmp.mm[0][0] = a_xScale;          //Xx
	tmp.mm[1][1] = a_yScale;		  //Yy
	tmp.mm[2][2] = a_zScale;	      //Zz
	return tmp;
}

template<class T>
Matrix4<T> Matrix4<T>::createTranslation(T a_transX, T a_transY, T a_transZ) {           //Return scaled Matrix4
	Matrix4<T> tmp;
	tmp.mm[0][3] = a_transX;          //Wx
	tmp.mm[1][3] = a_transY;		  //Wy
	tmp.mm[2][3] = a_transZ;	      //Wz
	return tmp;
}
///Setters
template<class T>
void Matrix4<T>::set(T a_m11, T a_m12, T a_m13, T a_m14,          // Rebuild the matrix with parameters
	T a_m21, T a_m22, T a_m23, T a_m24,
	T a_m31, T a_m32, T a_m33, T a_m34,
	T a_m41, T a_m42, T a_m43, T a_m44)  
{
	m11 = a_m11, m12 = a_m12, m13 = a_m13, m14 = a_m14;
	m21 = a_m21, m22 = a_m22, m23 = a_m23, m24 = a_m24;
	m31 = a_m31, m32 = a_m32, m33 = a_m33, m34 = a_m34;
	m41 = a_m41, m42 = a_m42, m43 = a_m43, m44 = a_m44;
}

template<class T>
void Matrix4<T>::set(T *a_ptr)                                        	// rebuild the matrix - expects pointer to array of 4 floats
{
	//Assign values with for loop for readability
	auto index = 0;
	for (auto r = 0; r < 4; r++) {
		for (auto c = 0; c < 4; c++) {
			mm[r][c] = a_ptr[index];
			index++;
		}
	}
}

template<class T>
void Matrix4<T>::setRotateX(float a_rot)                                 // Rotate Matrix4 on the z axis circle
{
	//Express via indexes for readability, we only change the relevant values. 
	//Do not touch axis or values for what we're rotating with. (X and x in this case)
	mm[1][1] = (T)cosf(a_rot);    //Yy
	mm[2][1] = -(T)sinf(a_rot);    //Yz
	mm[1][2] = (T)sinf(a_rot);   //Zy
	mm[2][2] = (T)cosf(a_rot);    //Zz
}

template<class T>
void Matrix4<T>::setRotateY(float a_rot)                                 // Rotate Matrix4 on the z axis circle
{
	mm[0][0] = (T)cosf(a_rot);   //Xx
	mm[2][0] = (T)sinf(a_rot);   //Xz
	mm[0][2] = -(T)sinf(a_rot);  //Zx
	mm[2][2] = (T)cosf(a_rot);   //Zz
}

template<class T>
void Matrix4<T>::setRotateZ(float a_rot)                                 // Rotate Matrix4 on the z axis circle
{
	mm[0][0] = (T)cosf(a_rot);   //Xx
	mm[1][0] = -(T)sinf(a_rot);  //Xy
	mm[0][1] = (T)sinf(a_rot);   //Yx
	mm[1][1] = (T)cosf(a_rot);   //Yy
}

template<class T>
void Matrix4<T>::setScale(T a_scaleX, T a_scaleY, T a_scaleZ)                 // Scale matrix by given values
{
	mm[0][0] = a_scaleX; //Xx
	mm[1][1] = a_scaleY; //Yy
	mm[2][2] = a_scaleZ; //Zz
}

template<class T>
void Matrix4<T>::setTranslate(T a_transX, T a_transY, T a_transZ)
{
	mm[0][3] = a_transX; //Wx
	mm[1][3] = a_transY; //Wy
	mm[2][3] = a_transZ; //Wz

}

template<class T>
Vector4<T> Matrix4<T>::getTranslation() const {
	return Vector4<T>{mm[0][3], mm[1][3], mm[2][3], mm[3][3]};         //Matrix4 is a 3D Matrix with translation capabilities, return translation axis
}

template<class T>
Vector4<T> Matrix4<T>::getRotation() {
	// Calculate euler angles by reversing calculations used to create rotation

	T x = atan2(m32, m22);     //Yz / Yy
	
	T y = atan2(m31, m11);	   //Xz / Xx

	T z = atan2(m21, m11);	   //Xy / Xx

	return Vector4<T>(x, y, z, 0);
}

template<class T>
Vector4<T> Matrix4<T>::getScale() const {
	return Vector4<T>(mm[0][0], mm[1][1], mm[2][2], 0);
}

template<class T>
glm::mat4x4 Matrix4<T>::convertToOpenGL()
{
	glm::mat4x4 tmp;
	for (auto r = 0; r < 4; r++) {
		for (auto c = 0; c < 4; c++) {
			tmp[r][c] = mm[r][c];
		}
	}
	return tmp;
}

template<class T>
Matrix4<T>& Matrix4<T>::convertFromOpenGL(glm::mat4x4 &a_mat) {
	for (auto r = 0; r < 4; r++) {
		for (auto c = 0; c < 4; c++) {
			mm[r][c] = a_mat[r][c];
		}
	}
	return *this;
}
#pragma endregion
//Casts matrix to float pointer
template<class T>
Matrix4<T>::operator T* () { return m; }                   //Return start of matrix memory address

template<class T>
Vector4<T> & Matrix4<T>::operator [] (unsigned int index) { return v[index]; } //Return vector at specified index

 template class Matrix4<int>;
 template class Matrix4<short>;
 template class Matrix4<double>;
 template class Matrix4<float>;


