#include <iostream>
#include <Vector2_Test.h>

void main() {
	Vec2<float> memes = Vec2<float>{ 2, 2 };
	memes.normalize();
	std::cout << memes.x << " " << memes.y << std::endl;
	system("pause");
}