#include "Complex.hpp"
#include <cmath>

Complex::Complex(){
	_re = 0;
	_im = 0;
}

Complex::Complex(double re, double im){
	_re = re;
	_im = im;
}

Complex::Complex(const Complex& val){
	_re = val._re;
	_im = val._im;
}


void Complex::Re(double re){
	_re = re;
}
void Complex::Im(double im){
	_im = im;
}
double Complex::Re() const{
	return _re;
}
double Complex::Im() const{
	return _im;
}


double Complex::Abs() const{
	return hypot(_re, _im);
}
double Complex::Arg() const{
	return atan2(_im, _re);
}


Complex Complex::Polar(double modulus, double argument){
	return Complex(modulus * cos(argument), modulus * sin(argument));
}

Complex& Complex::operator=(double re){
	_re = re;
	_im = 0;
	return *this;
}
Complex& Complex::operator+=(double re){
	_re += re;
	return *this;
}
Complex& Complex::operator-=(double re){
	_re -= re;
	return *this;
}
Complex& Complex::operator*=(double re){
	_re *= re;
	_im *= re;
	return *this;
}
Complex& Complex::operator/=(double re){
	_re /= re;
	_im /= re;
	return *this;
}


Complex& Complex::operator=(const Complex& val){
	_re = val._re;
	_im = val._im;
	return *this;
}
Complex& Complex::operator+=(const Complex& val){
	_re += val._re;
	_im += val._im;
	return *this;
}
Complex& Complex::operator-=(const Complex& val){
	_re -= val._re;
	_im -= val._im;
	return *this;
}
Complex& Complex::operator*=(const Complex& val){
	double re = _re;
	_re = _re * val._re - _im * val._im;
	_im = re * val._im + _im * val._re;
	return *this;
}
Complex& Complex::operator/=(const Complex& val){
	double re = _re;
	_re = (_re * val._re + _im * val._im)/(val._re * val._re + val._im * val._im);
	_im = (-re * val._im + _im * val._re)/(val._re * val._re + val._im * val._im);
	return *this;
}


bool Complex::operator==(const Complex& right) const{
	return _re == right._re && _im == right._im;
}
bool Complex::operator!=(const Complex& right) const{
	return !(*this == right);
}


Complex Complex::operator+(const Complex &right) const{
	Complex complex(*this);
	complex += right;
	return complex;
}

Complex Complex::operator-(const Complex &right) const{
	Complex complex(*this);
	complex -= right;
	return complex;
}

Complex Complex::operator*(const Complex &right) const{
	Complex complex(*this);
	complex *= right;
	return complex;
}

Complex Complex::operator/(const Complex &right) const{
	Complex complex(*this);
	complex /= right;
	return complex;
}


Complex Complex::sqrt() const{
	return Polar(std::sqrt(Abs()), Arg()/2);
}

Complex Complex::pow(int pow) const{
	return Polar(std::pow(Abs(), pow), Arg() * pow);
}



