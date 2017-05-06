#include <Vector2_Test.h>

/*When dealing with multiple template variables the template definitions MUST be on separate lines unless its a friend:
CLASS:
template <class T>
template <typename S>

FRIEND:
template <class T, typename S>
*/

#pragma region Constructors
template<class T>
Vec2<T>::Vec2() : x(0), y(0) {}

template<class T>
Vec2<T>::Vec2(T a_x, T a_y) : x(a_x), y(a_y) {}

template<class T>
Vec2<T>::Vec2(const Vec2 & a_rhs) : x(a_rhs.x), y(a_rhs.y) {}   //Copy/reference constructor

#pragma endregion

#pragma region Base Operators
template<class T>
Vec2<T> Vec2<T>::operator+(const Vec2 & a_rhs) const                     // V2 = V2 + V2 
{
	return Vec2<T>(x + a_rhs.x, y + a_rhs.y);             //Constructing a template class, have to specify the data-type in <T>
}

template<class T>
Vec2<T> Vec2<T>::operator-(const Vec2 & a_rhs) const					// V2 = V2 - V2 
{
	return Vec2<T>(x - a_rhs.x, y - a_rhs.y);
}

template<class T>
Vec2<T> & Vec2<T>::operator=(const Vec2 & a_rhs)
{
	x = a_rhs.x, y = a_rhs.y;
	return *this;                                           //Return de-referenced Vec2 after operations
}

template<class T>
template<typename S>
Vec2<T> Vec2<T>::operator*(S a_scalar) const
{
	return Vec2<T>(x * a_scalar, y * a_scalar);

}

template<class T, typename S>  //Scalar
//If its not a friend, the left hand side will HAVE to be a Vec2 when that's not necessarily always the case.
Vec2<T> operator*(S a_scalar, const Vec2<T> & a_rhs)
{
	return Vec2<T>(a_scalar * a_rhs.x, a_scalar * a_rhs.y);      //Return a Vec2 which concatenates the scalar and the right hand side
}

template<class T>
Vec2<T> Vec2<T>::operator -() const
{
	return Vec2<T>(-x, -y);                          // Return negative version of Vec2
}

template<class T>
//Casts vector to float pointer
Vec2<T>::operator T*()
{
	return &x;											// * Return start of memory address for Vec2
}

template<class T>
T & Vec2<T>::operator[](unsigned int index)
{
	return v[index];                                   // Return specified axis of Vector
}
#pragma endregion

#pragma region Advanced Operators
template<class T>
Vec2<T> & Vec2<T>::operator+=(const Vec2 & a_rhs)
{
	*this = *this + a_rhs;                                 //Call upon + operator to simplify this operator
	return *this;
}

template<class T>
Vec2<T> & Vec2<T>::operator-=(const Vec2 & a_rhs)
{
	*this = *this - a_rhs;
	return *this;
}

template<class T>
template<typename S>
Vec2<T> & Vec2<T>::operator*=(S a_scalar)
{
	*this = *this * a_scalar;
	return *this;
}

template<class T>
template<typename S>
Vec2<T> & Vec2<T>::operator/=(S a_scalar)
{
	*this = *this / a_scalar;
}
#pragma endregion

#pragma region Conditions
template<class T>
bool Vec2<T>::operator==(const Vec2 & a_rhs) const
{
	if (x == a_rhs.x && y == a_rhs.y) {              //Also compare translation points, Point != Vector
		return true;
	}
	return false;
}

template<class T>
bool Vec2<T>::operator!=(const Vec2 & a_rhs) const
{
	if (!(*this == a_rhs)) {
		return true;                                        //Yes, the vectors are not equal
	}
	return false;                                           //No, the vectors are equal
}
#pragma endregion

#pragma region Functions
template<class T>
T Vec2<T>::dot(const Vec2 & a_rhs)
{
	return ((x * a_rhs.x) + (y * a_rhs.y));
}

template<class T>
T Vec2<T>::magnitude()
{
	return T(sqrt14((x * x) + (y * y)));                       //Square root returns a double, typecast to float
}

template<class T>
void Vec2<T>::normalize()
{
	T m = magnitude();                                        //Compute magnitude only once for efficiency
	x /= m, y /= m;
}

template<class T>
Vec2<T> Vec2<T>::getNormal()
{
	T m = magnitude();
	return Vec2<T>(x /= m, y /= m);                       //Return normalized version of lhs
}
#pragma endregion

///Explicit instantiation required for template classes

EXPIMP_TEMPLATE template class LIBRARY_API Vec2<int>;
EXPIMP_TEMPLATE template class LIBRARY_API Vec2<short>;
EXPIMP_TEMPLATE template class LIBRARY_API Vec2<double>;
EXPIMP_TEMPLATE template class LIBRARY_API Vec2<float>;
