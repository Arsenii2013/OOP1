class Complex {
public:
  Complex();
  Complex(double re, double im = 0);
  Complex(const Complex& val);

  void Re(double re);
  void Im(double im);
  double Re() const;
  double Im() const;
  double Abs() const;
  double Arg() const;
  static Complex Polar(double modulus, double argument = 0);

  Complex& operator=(double re);
  Complex& operator+=(double re);
  Complex& operator-=(double re);
  Complex& operator*=(double re);
  Complex& operator/=(double re);

  Complex& operator= (const Complex& val);
  Complex& operator+=(const Complex& val);
  Complex& operator-=(const Complex& val);
  Complex& operator*=(const Complex& val);
  Complex& operator/=(const Complex& val);

  bool operator==(const Complex& right) const;
  bool operator!=(const Complex& right) const;

  Complex operator+(const Complex &right) const;
  Complex operator-(const Complex &right) const;
  Complex operator*(const Complex &right) const;
  Complex operator/(const Complex &right) const;
  Complex sqrt() const;
  Complex pow(int pow) const;

protected:
  double _re;
  double _im;
private:

};
