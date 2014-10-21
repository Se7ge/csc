/*
 * Еще одна важная группа операторов, которые полезно реализовать для класса рациональных чисел - операторы сравнения. Реализуйте операторы <, <=, >, >=, ==, != для класса Rational, так чтобы можно было сравнивать объекты класса Rational не только друг с другом, но и с целыми числами.
 * */
struct Rational
{
    Rational(int numerator = 0, int denominator = 1);

    void add(Rational rational);
    void sub(Rational rational);
    void mul(Rational rational);
    void div(Rational rational);

    void neg();
    void inv();
    double to_double() const;

    Rational& operator+=(Rational rational);
    Rational& operator-=(Rational rational);
    Rational& operator*=(Rational rational);
    Rational& operator/=(Rational rational);

    Rational operator-();
    Rational operator+();

private:
    int numerator_;
    unsigned denominator_;
};

Rational operator+(Rational lhs, Rational rhs);
Rational operator-(Rational lhs, Rational rhs);
Rational operator*(Rational lhs, Rational rhs);
Rational operator/(Rational lhs, Rational rhs);

bool operator==(Rational const & lhs, Rational const & rhs){
	return (lhs.to_double()==rhs.to_double());
}

bool operator!=(Rational const & lhs, Rational const & rhs){
	return !(lhs==rhs);
}

bool operator<(Rational const & lhs, Rational const & rhs){
	return lhs.to_double()<rhs.to_double();
}

bool operator>(Rational lhs, Rational rhs){
	return rhs<lhs;
}

bool operator<=(Rational lhs, Rational rhs){
	return !(lhs>rhs);
}

bool operator>=(Rational lhs, Rational rhs){
	return !(lhs<rhs);
}
