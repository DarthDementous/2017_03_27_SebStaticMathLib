#include <iostream>
#include <Vector2.h>

#define Vector2 Vector2<float>

void main() {
	// vector addition
	Vector2 v2a(13.5f, -48.23f), v2b(5, 3.99f), v2c;
	v2c = v2a + v2b;
	// vector subtraction
	v2a = Vector2(13.5f, -48.23f); v2b = Vector2(5, 3.99f);
	v2c = v2a - v2b;

	// vector post-scale
	v2a = Vector2(13.5f, -48.23f);
	v2c = v2a * 2.482f;

	// vector pre-scale
	v2a = Vector2(13.5f, -48.23f);
	v2c = 2.482f * v2a;

	// vector dot product
	v2a = Vector2(13.5f, -48.23f); v2b = Vector2(5, 3.99f);
	float dot2 = v2a.dot(v2b);

	// vector magnitude
	v2a = Vector2(13.5f, -48.23f);
	float mag2 = v2a.magnitude();

	// vector normalise
	v2a = Vector2(-13.5f, -48.23f);
	v2a.normalise();

	// Non unit-tests
	v2a *= 1.5f;
	v2a /= 1.5f;
	v2a += Vector2(1, 1);
	v2a -= Vector2(1, 1);
	system("pause");
}