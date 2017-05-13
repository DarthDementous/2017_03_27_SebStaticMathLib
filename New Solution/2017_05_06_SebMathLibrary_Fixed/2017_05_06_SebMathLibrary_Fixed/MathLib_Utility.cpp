#include "MathLib_Utility.h"

float degToRad(float degrees)
{
	return degrees * (float)_PI_OVER_180;
}

float radToDeg(float radians)
{
	return radians * (float)_180_OVER_PI;
}

// Get center point between two points (Vector3s)
Vector4<float> LinearHalf(Vector4<float> a_vec1, Vector4<float> a_vec2)
{
	// Create a vector between two points and halve it
	return Vector4<float>((a_vec2 - a_vec1) / 2);
}

