/**
 * @brief This class represents a polynomial function.
 *
 * @details A polynomial is represented using an array and the
 * degree. Basic operations [+,-,*,<<] are overloaded for
 * simplicity.
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */

#ifndef GROUP29_POLYNOMIAL_H
#define GROUP29_POLYNOMIAL_H

#include <iostream>
#include <array>
#include <vector>
#include "../../../include/model/functions/Function.h"
#include "../../../include/model/utilities/Utilities.h"

class Polynomial : public Function {
public:
    explicit Polynomial(const double arr[], int size, char variable);
    Polynomial(double coefficient, char variable, int degree);
    ~Polynomial() = default;
    char getVariable() const;

    bool isInputConstant() override;

    std::vector<double> getCoeffArray();
    double getCoef() override;
    double getPower() override;
    void minimizeCoef(double);
    void shiftPower(int);

    Function* add(Function*) override;
    Function* subtract(Function*) override;
    Function* multiply(Function*) override;
    Function* pow(Function*) override;

    Function* scalarMultiply(double n) const;
    Polynomial differentiate() const;
    std::string toString() override;

private:
    std::vector<double> coeff;
    int degree;
    char variable;

    void reduce();

};

std::ostream &operator<<(std::ostream &os, Polynomial p);

Polynomial operator*(double n, Polynomial &p1);
Polynomial operator*(Polynomial &p1, double n);

#endif //GROUP29_POLYNOMIAL_H
