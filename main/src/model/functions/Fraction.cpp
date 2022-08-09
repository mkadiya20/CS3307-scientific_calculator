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

#include <iostream>
#include <cmath>
#include <numeric>
#include "../../../include/model/functions/Fraction.h"
#include "../../../include/model/functions/Constant.h"
#include "../../../include/model/functions/Polynomial.h"
#include "../../../include/model/functions/Trig.h"
#include "../../../include/model/functions/Log.h"
#include "../../../include/model/utilities/Utilities.h"

/**
 * parameterised constructor
 * @param numerator the numerator part of fraction
 * @param denominator the denominator part of fraction
 */
Fraction::Fraction(Function *numerator, Function *denominator) {
    Fraction::numerator = numerator;
    Fraction::denominator = denominator;
    Function::type = "Fraction";

    // denominator should not be 0
    if (Fraction::denominator->toString() == "0") {
        throw std::runtime_error("Denominator cannot be 0");
    }

    // move the minus sign to numerator
    // also removes double minus sign
    // only works for constant functions
    if (Fraction::numerator->isInputConstant() && Fraction::denominator->isInputConstant() &&
        Fraction::denominator->getValue() < 0) {
        Fraction::numerator->setValue(Fraction::numerator->getValue() * -1);
        Fraction::denominator->setValue(Fraction::denominator->getValue() * -1);
    }
}


/**
 * convert the double to fraction
 * @param number the number to covert to fraction
 * @return the fraction representation of the number
 */
Function *Fraction::to_fraction(Function *f) {
    double number = f->getValue();
    // get the integer part
    double integer = std::floor(number);

    // get the decimal part
    double decimal = number - integer;

    // set the precision for calculations
    const long precision = 1000000000;

    // get GCD of integral equivalent of decimal part and precision
    const long value = gcd(std::round(decimal * precision), precision);

    double numerator = std::round(decimal * precision) / value;
    double denominator = precision / value;

    numerator = (integer * denominator) + numerator;

    Function *n = new Constant(numerator);
    Function *d = new Constant(denominator);

    Function *func = new Fraction(n, d);
    return func;
}


/**
 * simply the fraction to the most reduced form
 *
 * 1. Compare the coefficients, minimize them
 * 2. Check if both functions are same types
 * 3. Check if inner functions are the same
 * 4. If (2) & (3) are true,  Compare the powers, minimize them
 * 5. If either power is now 0, make that a constant function of 1
 */
void Fraction::simplify() {
    if (numerator->isInputConstant() && denominator->isInputConstant()) {
        // get the multiple and divide it with numerator and denominator
        int multiple = commonMultiple();
        if (multiple > 0) {
            numerator->setValue(numerator->getValue() / multiple);
            denominator->setValue(denominator->getValue() / multiple);
        }
    } else {
        double numeratorCoef = numerator->getCoef();
        double denominatorCoef = denominator->getCoef();
        if (trunc(numeratorCoef) == numeratorCoef && trunc(denominatorCoef) == denominatorCoef) {
            int numeratorCoefInt = (int) numeratorCoef;
            int denominatorCoefInt = (int) denominatorCoef;
            //int lcmCoef = std::gcf((int) numeratorCoef, (int) denominatorCoef);
            int gcfCoef = 1;
            for (int i = 1; i <= numeratorCoefInt && i <= denominatorCoefInt; i++) {
                if (numeratorCoefInt % i == 0 && denominatorCoefInt % i == 0) {
                    gcfCoef = i;
                }
            }

            if (auto *pNum = dynamic_cast<Polynomial *>(numerator)) {
                pNum->minimizeCoef(gcfCoef);
            } else {
                numerator->setCoef(numeratorCoef / gcfCoef);
            }
            if (auto *pDem = dynamic_cast<Polynomial *>(denominator)) {
                pDem->minimizeCoef(gcfCoef);
            } else {
                denominator->setCoef(denominatorCoef / gcfCoef);
            }
        }


        if (numerator->getType() == denominator->getType()) {
            if (auto *tNum = dynamic_cast<Trig *>(numerator)) {
                if (auto *tDen = dynamic_cast<Trig *>(denominator)) {
                    if (tNum->getTrigType() == tDen->getTrigType()) {
                        if (Utilities::equalTrees(tNum->getNodeInput(), tDen->getNodeInput())) {
                            double numPower = tNum->getPower();
                            double denPower = tDen->getPower();
                            double minPower = std::min(numPower, denPower);

                            tNum->setPower(numPower - minPower);
                            tDen->setPower(denPower - minPower);

                            if (tNum->getPower() == 0) {
                                numerator = new Constant(tNum->getCoef());
                            }
                            if (tDen->getPower() == 0) {
                                denominator = new Constant(tDen->getCoef());
                            }
                        }
                    }
                }
            }

            if (auto *lNum = dynamic_cast<Log *>(numerator)) {
                if (auto *lDen = dynamic_cast<Log *>(denominator)) {
                    if (Utilities::equalTrees(lNum->getNodeInput(), lDen->getNodeInput())) {
                        double numPower = lNum->getPower();
                        double denPower = lDen->getPower();
                        double minPower = std::min(numPower, denPower);

                        lNum->setPower(numPower - minPower);
                        lDen->setPower(denPower - minPower);

                        if (lNum->getPower() == 0) {
                            numerator = new Constant(lNum->getCoef());
                        }
                        if (lDen->getPower() == 0) {
                            denominator = new Constant(lDen->getCoef());
                        }
                    }
                }
            }

            if (auto *pNum = dynamic_cast<Polynomial *>(numerator)) {
                if (auto *pDen = dynamic_cast<Polynomial *>(denominator)) {
                    int numPower = (int) pNum->getPower();
                    int denPower = (int) pDen->getPower();
                    int minPower = std::min(numPower, denPower);

                    pNum->shiftPower(minPower);
                    pDen->shiftPower(minPower);

                    if (pNum->getPower() == 0) {
                        numerator = new Constant(pNum->getCoeffArray()[0]);
                    }
                    if (pDen->getPower() == 0) {
                        denominator = new Constant(pDen->getCoeffArray()[0]);
                    }
                }
            }
        }
    }
}

/**
 * calculate the common multiple between numerator and denominator
 * @return the highest common multiple
 */
int Fraction::commonMultiple() {
    // get the fractional representation of numerator and denominator
    Function *n = Fraction::to_fraction(numerator);
    Function *d = Fraction::to_fraction(denominator);

    // cast will always happen, no condition checks needed
    auto f1 = dynamic_cast<Fraction *>(n);
    auto f2 = dynamic_cast<Fraction *>(d);

    // divide the two fractions (cannot use operator division, infinite method calls)
    Function *num = *f1->numerator * *f2->denominator;
    Function *den = *f1->denominator * *f2->numerator;

    // set the numerator and denominator
    Fraction::numerator = num;
    Fraction::denominator = den;

    double numeratorNum = num->getValue();
    double numeratorDem = den->getValue();

    double low = numeratorNum < den->getValue() ? std::abs(numeratorNum) : std::abs(numeratorDem);
    int max = 1;

    // check if the number is divisible by both numerator and denominator
    for (int i = 2; i <= low; i++) {
        if ((int) numeratorNum % i == 0 && (int) numeratorDem % i == 0) {
            max = i;
        }
    }

    // return the highest common multiple
    return max;
}


/**
 * convert the fraction to double
 * @return the double representation of the fraction
 */
double Fraction::getValue() {
    return (double) numerator->getValue() / denominator->getValue();
}


/**
 * add two fractions
 * @param fraction the fraction to add
 * @return the fraction after addition
 */
Function *Fraction::add(Function *f) {
    if (auto *fraction = dynamic_cast<Fraction *>(f)) {
        // cross multiply and add the numerators
        Function *n1 = *numerator * *fraction->denominator;
        Function *n2 = *fraction->numerator * *denominator;

        // multiply the denominators
        Function *d = *denominator * *fraction->denominator;

        // create the fraction and simplify it
        Function *func = new Fraction(*n1 + *n2, d);

        dynamic_cast<Fraction *>(func)->simplify();

        return func;
    } else {
        Function *frac = to_fraction(f);
        return *this + *frac;
    }
    return nullptr;
}


/**
 * subtract two fractions
 * @param fraction the fraction to subtract
 * @return the fraction after subtraction
 */
Function *Fraction::subtract(Function *f) {
    if (auto *fraction = dynamic_cast<Fraction *>(f)) {
        // cross multiply and subtract the numerators
        Function *n1 = *numerator * *fraction->denominator;
        Function *n2 = *fraction->numerator * *denominator;

        // multiply the denominators
        Function *d = *denominator * *fraction->denominator;

        // create the fraction and simplify it
        Function *func = new Fraction(*n1 - *n2, d);

        dynamic_cast<Fraction *>(func)->simplify();

        return func;
    } else {
        Function *frac = to_fraction(f);
        return *this - *frac;
    }
}


/**
 * multiply two fractions
 * @param fraction the fraction to multiply
 * @return the fraction after multiplication
 */
Function *Fraction::multiply(Function *f) {
    if (auto *fraction = dynamic_cast<Fraction *>(f)) {
        // multiply numerators and denominators
        Function *n = *numerator * *fraction->numerator;
        Function *d = *denominator * *fraction->denominator;

        // create the fraction and simplify it
        Function *func = new Fraction(n, d);

        dynamic_cast<Fraction *>(func)->simplify();

        return func;
    } else {
        Function *frac = to_fraction(f);
        return *this * *frac;
    }

    return nullptr;
}


/**
 * (1/2) ^ (3/4)
 * 1^(3/4) / 2^(3/4))
 */
Function *Fraction::pow(Function *f) {
    Function *c = new Constant(std::pow(getValue(), f->getValue()));
    Function *frac = Fraction::to_fraction(c);
    dynamic_cast<Fraction *>(frac)->simplify();
    return frac;
}


std::string Fraction::toString() {
    if ((denominator->isInputConstant() && denominator->getValue() == 1) ||
        (numerator->isInputConstant() && numerator->getValue() == 0)) {
        return numerator->toString();
    } else {
        return numerator->toString() + "/" + denominator->toString();
    }
}

/**
 * calculate the Greatest Common Divisor(GCD) between two numbers
 * @param a first number
 * @param b second number
 * @return the GCD of two numbers
 */
long long Fraction::gcd(long long a, long long b) {
    if (a == 0)
        return b;
    else if (b == 0)
        return a;
    if (a < b)
        return gcd(a, b % a);
    else
        return gcd(b, a % b);
}