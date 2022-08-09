/**
 * @brief This class represents a Fraction.
 *
 * @details The numerator and denominator are initialised as
 * double types. Basic [+,-,*,/,<<] operators are
 * overloaded for simplicity. This is done by declaring
 * free functions in the header class. Operator overloading
 * also supports arithmetic with a double and a fraction.
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */

#ifndef GROUP29_FRACTION_H
#define GROUP29_FRACTION_H

#include "Function.h"

class Fraction : public Function{
public:
    Function* numerator;
    Function* denominator;

    Fraction(Function* numerator, Function* denominator);
    ~Fraction() = default;
    static Function* to_fraction(Function*);

    void simplify();
    int commonMultiple();
    double getValue() override;

    Function *add(Function*) override;
    Function *subtract(Function*) override;
    Function *multiply(Function*) override;
    Function *pow(Function*) override;
//    Fraction divide(Fraction);
    std::string toString() override;
private:
    static long long gcd(long long a, long long b);
};

Fraction operator+(Fraction &f1, Fraction &f2);
Fraction operator-(Fraction &f1, Fraction &f2);
Fraction operator*(Fraction &f1, Fraction &f2);

#endif //GROUP29_FRACTION_H
