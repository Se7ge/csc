/*
 Вам дан класс Rational, который представляет рациональное число. 
 * В нем определены методы add, sub, mul и div, которые прибавляют к нему число, отнимают число, 
 * умножают на число и делят на число соответственно. 
 * Кроме того в нем определен метод neg, который меняет знак на противоположный. 
 * Вам нужно определить операторы +=, -=, *=, /= для класса Rational, 
 * так чтобы они могли принимать в качестве аргументов и объекты типа Rational и целые числа. 
 * Кроме того вам необходимо определить операторы унарного минуса и плюса для класса Rational.
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
    Rational operator +() {
		return Rational(numerator_, denominator_) ;
	}	
    Rational operator -() {
		Rational * r = new Rational(numerator_, denominator_) ;
		r->neg();
		return *r ;
	}
    Rational & operator +=( Rational const r ) {
		add(r);
		return * this ;
	}
    Rational & operator -=( Rational const r ) {
		sub(r);
		return * this ;
	}
    Rational & operator *=( Rational const r ) {
		mul(r);
		return * this ;
	}
    Rational & operator /=( Rational const r ) {
		div(r);
		return * this ;
	}

private:
    int numerator_;
    unsigned denominator_;
};
