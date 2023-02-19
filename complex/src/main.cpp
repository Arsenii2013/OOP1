//============================================================================
// Name        : complex.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Complex.hpp"
using namespace std;

int main() {
	Complex::Polar(0, 1);
	cout << " adf" << endl; // prints
	return 0;
}

TEST(Operators, DivByZero) {
		Complex a = Complex(2, 2);

		a /= 0;
		ASSERT_FALSE(IsValid(a));

		a = Complex(2, 2);

		a /= Complex(0, 0);
		ASSERT_FALSE(IsValid(a));

		a = Complex(2, 2);

		a = a / Complex(0, 0);
		ASSERT_FALSE(IsValid(a));
}
