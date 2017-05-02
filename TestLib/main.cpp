#include "unittest.h"
#include <iostream>

/*
Exercises - Dot and Cross Product

1. degrees * Pi/180
a) 0.52
b) 0.79
c) 1.26

2. radians * 180/Pi
a) 85.94
b) 270                             (3PI)/2 = third quadrant of circle = 90 * 3
c) 114.59

3. ax * bx + ay * by + az * bz
a) -3 = opposite directions
b) 0 = perpendicular
c) 18 = opposite directions
d) 11 = opposite directions
e) 0 = perpendicular

4. normalize, sec(dot product)
a) a_m = (sqrt)(3^2 + 4^2) = 5
a_nv = {3/5, 4/5}
b_m = (sqrt)(-5^2 + 3^2) = 5.83
b_nv = {-5/5.83, 3/5.83}

angle = -cos(3/5 * -5/5.83 + 4/5 * 3/5.83)
      = -cos(-0.10)
	  = 95.91 * Pi/180
	  = 1.67 Radians

*/

int main() {

	if (runUnitTests() == false) {
		std::cout << "Unit test failed!" << std::endl;
		system("pause");
		return -1;
	}
	std::cout << "All tests passed successfully." << std::endl;

	system("pause");

	return EXIT_SUCCESS;
}