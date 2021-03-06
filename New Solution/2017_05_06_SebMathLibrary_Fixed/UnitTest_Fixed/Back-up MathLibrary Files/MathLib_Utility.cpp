#include "MathLib_Utility.h"

float degToRad(float degrees)
{
	return degrees * (float)_PI_OVER_180;
}

float radToDeg(float radians)
{
	return radians * (float)_180_OVER_PI;
}

float LinearHalf(float x)
{
	return x * 0.5f;
}