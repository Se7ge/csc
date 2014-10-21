/*
 * Определите для класса Rational операторы сложения, вычитания, умножения и деления, так чтобы объекты типа Rational можно было складывать (вычитать, умножать и делить) не только друг с другом но и с целыми числами.
 */
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

Rational operator +( Rational r1 , Rational const & r2 ) {
	return r1 += r2 ;
}

Rational operator -( Rational r1 , Rational const & r2 ) {
	return r1 -= r2 ;
}

Rational operator *( Rational r1 , Rational const & r2 ) {
	return r1 *= r2 ;
}

Rational operator /( Rational r1 , Rational const & r2 ) {
	return r1 /= r2 ;
}
