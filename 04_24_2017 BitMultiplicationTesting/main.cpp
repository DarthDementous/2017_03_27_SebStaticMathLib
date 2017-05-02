#include <chrono>
#include <iostream>
#include <time.h>

typedef unsigned int uInt;

uInt bitwiseMultiply(uInt a, uInt b) { 
	uInt answer = 0;
	uInt currentBit = 0;

	return 0; 
}

void main() {
	srand(uInt(time(NULL)));

	uInt a = rand() % 100;
	uInt b = rand() % 100;

	uInt answer = bitwiseMultiply(a, b);

	if (answer == (a*b)) {
		std::cout << "TEST PASSED: bitshift multiplication " << a << " * " << b << " = " << answer << std::endl;
	}
	else {
		std::cout << "TEST FAILED: bitshift multiplication " << a << " * " << b << " = " << answer << " (correct answer is: " << std::endl;
	}
}