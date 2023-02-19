#include <gtest/gtest.h>
#include "Complex.hpp"
#include <iostream>
#include <cmath>

#define err (1e-10)
#define PI std::acos(-1)

TEST(Base, Constructor) {
		double re = 0, im = 0;
		Complex a = Complex(re, im);
		ASSERT_EQ(re, a.Re());
		ASSERT_EQ(im, a.Im());
		re = 123;
		im = -123;
		Complex b = Complex(re, im);
		ASSERT_EQ(re, b.Re());
		ASSERT_EQ(im, b.Im());
		Complex c = Complex(b);
		ASSERT_EQ(re, c.Re());
		ASSERT_EQ(im, c.Im());
}

TEST(Base, SetGet) {
		double re = 0, im = 0;
		Complex a = Complex(re, im);
		re = 123;
		im = -123;
		a.Re(re);
		a.Im(im);
		ASSERT_EQ(re, a.Re());
		ASSERT_EQ(im, a.Im());
}


TEST(Base, AbsArg) {
		double re = 1, im = 1;
		Complex a = Complex(re, im);
		EXPECT_NEAR(sqrt(2), a.Abs(), err);
		EXPECT_NEAR(PI/4, a.Arg(), err);
		a.Re(0);
		a.Im(1);
		EXPECT_NEAR(1, a.Abs(), err);
		EXPECT_NEAR(PI/2, a.Arg(), err);
		a.Re(-1);
		a.Im(-1);
		std::cout << a.Abs() << ' ' << a.Arg();
		EXPECT_NEAR(sqrt(2), a.Abs(), err);
		EXPECT_NEAR(-3*PI/4, a.Arg(), err);
}

TEST(Base, Polar) {
		double re = 0.5, im = 1;
		Complex a = Complex(re, im);
		Complex b = Complex::Polar(a.Abs(), a.Arg());

		EXPECT_NEAR(a.Abs(), b.Abs(), err);
		EXPECT_NEAR(a.Arg(), b.Arg(), err);
		ASSERT_DOUBLE_EQ(re, b.Re());
		ASSERT_DOUBLE_EQ(im, b.Im());
}

TEST(Base, Const) {

		const Complex c(1, 1);

		ASSERT_DOUBLE_EQ(1, c.Re());
		ASSERT_DOUBLE_EQ(1, c.Im());

		EXPECT_NEAR(sqrt(2), c.Abs(), err);
		EXPECT_NEAR(PI/4, c.Arg(), err);

		const Complex a = Complex(0, 2);

		EXPECT_NEAR(1, a.sqrt().Re(), err);
		EXPECT_NEAR(1, a.sqrt().Im(), err);

		EXPECT_NEAR(0, a.pow(3).Re(), err);
		EXPECT_NEAR(-8, a.pow(3).Im(), err);
}

static bool IsValid(Complex a){
	return std::isnormal(a.Re()) && std::isnormal(a.Im());
}

TEST(Operators, Re) {
		double re = 1, im = 1;
		Complex a = Complex(re, im);
		re = 1;
		a = re;
		ASSERT_DOUBLE_EQ(re, a.Re());
		ASSERT_DOUBLE_EQ(0, a.Im());
		a.Im(im);
		a += re;
		ASSERT_DOUBLE_EQ(2 * re, a.Re());
		ASSERT_DOUBLE_EQ(im, a.Im());
		a.Im(im);
		a -= re;
		ASSERT_DOUBLE_EQ(re, a.Re());
		ASSERT_DOUBLE_EQ(im, a.Im());
		a.Im(im);
		a *= re;
		ASSERT_DOUBLE_EQ(re * re, a.Re());
		ASSERT_DOUBLE_EQ(im * re, a.Im());
		a.Im(im);
		a /= re;
		ASSERT_DOUBLE_EQ(re, a.Re());
		ASSERT_DOUBLE_EQ(im / re, a.Im());

		a /= 0;
		ASSERT_FALSE(IsValid(a));
}

TEST(Operators, AssignComplex) {
		Complex a = Complex(2, 2);
		Complex b = Complex(3, 3);
		a = b;
		ASSERT_DOUBLE_EQ(b.Re(), a.Re());
		ASSERT_DOUBLE_EQ(b.Im(), a.Im());
		a += b;
		ASSERT_DOUBLE_EQ(6, a.Re());
		ASSERT_DOUBLE_EQ(6, a.Im());
		a -= b;
		ASSERT_DOUBLE_EQ(3, a.Re());
		ASSERT_DOUBLE_EQ(3, a.Im());
		a *= b;
		ASSERT_DOUBLE_EQ(0, a.Re());
		ASSERT_DOUBLE_EQ(18, a.Im());
		a /= b;
		ASSERT_DOUBLE_EQ(3, a.Re());
		ASSERT_DOUBLE_EQ(3, a.Im());

		a /= Complex(0, 0);
		ASSERT_FALSE(IsValid(a));
}

TEST(Operators, Complex) {
		Complex a = Complex(2, 2);
		Complex b = Complex(3, 3);

		a = a + b;
		ASSERT_DOUBLE_EQ(5, a.Re());
		ASSERT_DOUBLE_EQ(5, a.Im());
		a = a - b;
		ASSERT_DOUBLE_EQ(2, a.Re());
		ASSERT_DOUBLE_EQ(2, a.Im());
		a = a * b;
		ASSERT_DOUBLE_EQ(0, a.Re());
		ASSERT_DOUBLE_EQ(12, a.Im());
		a = a / b;
		ASSERT_DOUBLE_EQ(2, a.Re());
		ASSERT_DOUBLE_EQ(2, a.Im());

		a = a / Complex(0, 0);
		ASSERT_FALSE(IsValid(a));
}

TEST(Operators, EQNE) {
		Complex a = Complex(2, 2);
		Complex b = Complex(3, 3);
		ASSERT_TRUE(a != b);
		ASSERT_FALSE(a == b);
		a.Re(3);
		a.Im(3);
		ASSERT_TRUE(a == b);
		ASSERT_FALSE(a != b);
}

TEST(Operators, Const) {
		const Complex a = Complex(2, 2);
		const Complex b = Complex(3, 3);

		ASSERT_TRUE(a != b);
		ASSERT_FALSE(a == b);

		ASSERT_TRUE(Complex(5, 5) == a + b);
		ASSERT_TRUE(Complex(1, 1) == b - a);
		ASSERT_TRUE(Complex(0, 12) == a * b);
		ASSERT_TRUE(Complex((double)2/3, 0) == a / b);
}

TEST(Base, Degrees) {
		Complex a = Complex(0, 2);

		EXPECT_NEAR(1, a.sqrt().Re(), err);
		EXPECT_NEAR(1, a.sqrt().Im(), err);

		a.Re(1);
		a.Im(1);

		EXPECT_NEAR(-2, a.pow(3).Re(), err);
		EXPECT_NEAR(2, a.pow(3).Im(), err);
}


TEST(Math, QuadraticEquation)
{
/*        "Quadratic Equation\n"
        "a*x^2 + b*x + c = 0\n"
        "where:\n"
        "a = Complex(-1, 2)\n"
        "b = Complex(-3, 5)\n"
        "c = Complex(6, 1);\n"
        "Expected result r1:(-3.0699574353850347, -0.90792903343967635)\n"
        "Expected result r2:( 0.46995743538503493, 0.70792903343967650)\n"
*/
    Complex a(-1, 2);
    Complex b(-3, 5);
    Complex c(6, 1);

    Complex r1; Complex r2;
    if (a != Complex()) {
        Complex d = (b * b - a * c * 4.0).sqrt();
        r1 = (Complex{} -b + d) / (a * 2.0);
        r2 = (Complex{} -b - d) / (a * 2.0);
    }
    else if (b != Complex()) {
        r1 = (Complex{} -c) / b;
    }
    //else if (c != Complex())
    //    print_info("no roots");
    //else
    //    print_info("infinitively many roots");
    EXPECT_NEAR((a * r1 * r1 + b * r1 + c).Re(), 0.0, err);
    EXPECT_NEAR((a * r1 * r1 + b * r1 + c).Im(), 0.0, err);
    EXPECT_NEAR((a * r2 * r2 + b * r2 + c).Re(), 0.0, err);
    EXPECT_NEAR((a * r2 * r2 + b * r2 + c).Im(), 0.0, err);

    Complex expect1(-3.0699574353850347, -0.90792903343967635);
    Complex expect2( 0.46995743538503493, 0.70792903343967650);

    EXPECT_NEAR(r1.Re(), expect1.Re(), err);
    EXPECT_NEAR(r1.Im(), expect1.Im(), err);
    EXPECT_NEAR(r2.Re(), expect2.Re(), err);
    EXPECT_NEAR(r2.Im(), expect2.Im(), err);
}



