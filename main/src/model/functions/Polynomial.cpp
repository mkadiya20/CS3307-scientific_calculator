/**
 * @brief This class represents a polynomial function.
 *
 * @details A polynomial is represented using an array and the
 * degree. Basic operations [+,-,*] are overloaded for
 * simplicity.
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */

#include <string>
#include <numeric>

#include "../../../include/model/functions/Polynomial.h"
#include "../../../include/model/functions/Constant.h"
#include "../../../include/model/functions/Trig.h"
#include "../../../include/model/functions/Log.h"


/**
 * parameterised constructor
 * @param arr the array that representing coefficients
 * @param size the size of the array
 */
Polynomial::Polynomial(const double arr[], int size, char variable) {
//    Polynomial::coeff[size];
    Function::type = "Polynomial";
    Polynomial::variable = variable;

    // copy the array to coeff vector
    for (int i = 0; i < size; i++) {
        degree = i;
        coeff.push_back(arr[i]);
    }

    // reduce to get the proper degree
    reduce();
}


/**
 * parameterised constructor for single polynomial
 * @param coefficient the coefficient of polynomial
 * @param variable the variable of polynomial
 * @param degree the degree of polynomial
 */
Polynomial::Polynomial(double coefficient, char variable, int degree) {
    Function::type = "Polynomial";
    Polynomial::degree = degree;
    Polynomial::variable = variable;

    // all values up until the index of degree are 0
    for (int i = 0; i < degree; i++) {
        coeff.push_back(0);
    }

    // put the coefficient at index 'degree'
    coeff.push_back(coefficient);

    // reduce to get the proper degree
    reduce();
}

/**
 * getter method for polynomial variable
 * @return the variable
 */
char Polynomial::getVariable() const {
    return variable;
}

/**
 * Tells whether this type of function can be evaluated to a constant
 * @return false, polynomials can never be constants through a get value
 */
bool Polynomial::isInputConstant() {
    return false;
}

/**
 * getter method for coefficient vector
 * @return the coeff vector
 */
std::vector<double> Polynomial::getCoeffArray() {
    return coeff;
}


double Polynomial::getCoef() {
    int index = 0;
    while (coeff.at(index) == 0) {
        index++;
    }
    int currLCM = (int) coeff.at(index);
    for (int i = index + 1; i <= degree; i++) {
        if (coeff.at(i) != 0) {
            // currLCM = std::lcm(currLCM, (int)coeff.at(i));
        }
    }
    return currLCM;
}

double Polynomial::getPower() {
    for (int i = 0; i <= degree; i++) {
        if (coeff.at(i) != 0) {
            return i;
        }
    }
    return 0;
}

void Polynomial::minimizeCoef(double coef) {
    for (int i = 0; i <= degree; i++) {
        coeff.at(i) /= coef;
    }
}

void Polynomial::shiftPower(int shiftAmount) {
    for (int i = shiftAmount; i <= degree; i++) {
        coeff.at(i - shiftAmount) = coeff.at(i);
        coeff.at(i) = 0;
    }
    reduce();
}

/**
 * add two polynomial functions
 * @param p the polynomial to be added
 * @return the polynomial after addition
 */
Function *Polynomial::add(Function *f) {
    // check if function is a polynomial
    if (auto *p = dynamic_cast<Polynomial *>(f)) {
        // check if both polynomials have the same variable
        if (variable != p->variable) {
            return nullptr;
        }

        // get the higher degree between the two polynomials
        int n = std::max(degree, p->degree);

        std::vector<double> arr(n + 1);

        // add the coefficients of this polynomial
        for (int i = 0; i <= degree; i++) {
            arr.at(i) += coeff.at(i);
        }

        // add the coefficients of p polynomial
        for (int i = 0; i <= p->degree; i++) {
            arr.at(i) += p->coeff.at(i);
        }

        // create the object and reduce it
        Function *ans = new Polynomial(arr.data(), n + 1, variable);
//        ans.reduce();
        return ans;
    }

    // check if function is a trig
    if (auto *t = dynamic_cast<Trig *>(f)) {
        // if trig has constant inner function
        if (!t->getNodeInput()) {
            this->coeff[0] += t->getValue();
            this->reduce();
            return this;
        }
    }

    // check if function is a log
    if (auto *l = dynamic_cast<Log *>(f)) {
        // if log has constant inner function
        if (!l->getNodeInput()) {
            this->coeff[0] += l->getValue();
            this->reduce();
            return this;
        }
    }

    // check if function is a constant
    if (auto *c = dynamic_cast<Constant *>(f)) {
        this->coeff[0] += c->getValue();
        this->reduce();
        return this;
    }

    return nullptr;
}

/**
 * subtract two polynomial functions
 * @param p the polynomial to subtract
 * @return the polynomial after subtraction
 */
Function *Polynomial::subtract(Function *f) {
    if (auto *p = dynamic_cast<Polynomial *>(f)) {
        // check if both polynomials have the same variable
        if (variable != p->variable) {
            return nullptr;
        }

        // get the max degree
        int n = std::max(degree, p->degree);

        std::vector<double> arr(n + 1);

        // add this polynomial
        for (int i = 0; i <= degree; i++) {
            arr.at(i) += coeff.at(i);
        }

        // subtract polynomial p from "this" polynomial
        for (int i = 0; i <= p->degree; i++) {
            arr.at(i) -= p->coeff.at(i);
        }

        // create the object and reduce it
        Function *ans = new Polynomial(arr.data(), n + 1, variable);
//        ans.reduce();
        return ans;
    }

    // check if function is a trig
    if (auto *t = dynamic_cast<Trig *>(f)) {
        // if trig has constant inner function
        if (!t->getNodeInput()) {
            this->coeff[0] -= t->getValue();
            this->reduce();
            return this;
        }
    }

    // check if function is a log
    if (auto *l = dynamic_cast<Log *>(f)) {
        // if log has constant inner function
        if (!l->getNodeInput()) {
            this->coeff[0] -= l->getValue();
            this->reduce();
            return this;
        }
    }

    // check if function is a constant
    if (auto *c = dynamic_cast<Constant *>(f)) {
        this->coeff[0] -= c->getValue();
        this->reduce();
        return this;
    }

    return nullptr;
}


/**
 * multiply two polynomial functions
 * @param p the polynomial to multiply
 * @return the polynomial after multiplication
 */
Function *Polynomial::multiply(Function *f) {
    if (auto *p = dynamic_cast<Polynomial *>(f)) {
        // check if both polynomials have the same variable
        if (variable != p->variable) {
            return nullptr;
        }

        // add two degrees, this is the new degree of polynomial
        int n = degree + p->degree;

        std::vector<double> arr(n + 1);

        // multiply both coefficients of polynomials
        for (int i = 0; i < coeff.size(); i++) {
            for (int j = 0; j < p->coeff.size(); j++) {
                arr.at(i + j) += coeff.at(i) * p->coeff.at(j);
            }
        }

        // create the object and reduce it
        Function *ans = new Polynomial(arr.data(), n + 1, variable);
//        ans.reduce();
        return ans;
    }

    // check if function is a trig
    if (auto *t = dynamic_cast<Trig *>(f)) {
        // if trig has constant inner function
        if (!t->getNodeInput()) {
            this->scalarMultiply(t->getValue());
            return this;
        }
    }

    // check if function is a log
    if (auto *l = dynamic_cast<Log *>(f)) {
        // if log has constant inner function
        if (!l->getNodeInput()) {
            this->scalarMultiply(l->getValue());
            return this;
        }
    }

    // check if function is a constant
    if (auto *c = dynamic_cast<Constant *>(f)) {
        this->scalarMultiply(c->getValue());
        return this;
    }

    return nullptr;
}


Function *Polynomial::pow(Function *f) {
    if (auto *p = dynamic_cast<Polynomial *>(f)) {
        return nullptr;
    }

    // check if function is a trig
    if (auto *t = dynamic_cast<Trig *>(f)) {
        // if trig has constant inner function
        if (!t->getNodeInput()) {
            Function *p = this;
            int val = (int) t->getValue();
            for (int i = 0; i < val; i++) {
                p = p->multiply(p);
            }
            return p;
        }
    }

    // check if function is a log
    if (auto *l = dynamic_cast<Log *>(f)) {
        // if log has constant inner function
        if (!l->getNodeInput()) {
            Function *p = this;
            int val = (int) l->getValue();
            for (int i = 0; i < val; i++) {
                p = p->multiply(p);
            }
            return p;
        }
    }

    // check if function is a constant
    if (auto *c = dynamic_cast<Constant *>(f)) {
        Function *p = this;
        int val = (int) c->getValue();
        for (int i = 0; i < val; i++) {
            p = p->multiply(p);
        }
        return p;
    }

    return nullptr;
}


/**
 * multiple a double and a polynomial
 * @param n the double to multiply
 * @return the polynomial after multiplication
 */
Function *Polynomial::scalarMultiply(double n) const {
    std::vector<double> arr(degree + 1);

    // multiply each coefficient with the double
    for (int i = 0; i <= degree; i++) {
        arr.at(i) = coeff.at(i) * n;
    }

    // create the object and reduce
    Function *ans = new Polynomial(arr.data(), degree + 1, variable);
//    ans.reduce();
    return ans;
}


/**
 * differentiate the polynomial
 * @return the polynomial after differentiation
 */
Polynomial Polynomial::differentiate() const {
    std::vector<double> arr(degree);

    // differentiate by multiplying each coefficient with its index
    for (int i = 1; i <= degree; i++) {
        arr.at(i - 1) = coeff.at(i) * i;
    }

    // create the object and reduce
    Polynomial ans(arr.data(), degree, variable);
    ans.reduce();
    return ans;
}


/**
 * display the polynomial as a string
 * @return the string representation of polynomial
 */
std::string Polynomial::toString() {
    if (degree == 0) {
        return Utilities::removeTrailingZeros(coeff.at(0));
    }
    std::string result;

    // loop backwards, the highest degree is printed first
    for (int i = coeff.size() - 1; i > 0; i--) {
        if (coeff.at(i) != 0) {
            if (coeff.at(i) == 1) {
                result += variable;
            } else if (coeff.at(i) == -1) {
                result += "-";
                result += variable;
            } else {
                // convert the double to string
                std::string s = Utilities::removeTrailingZeros(coeff.at(i));
                result += s + variable;
            }

            if (i != 1) {
                result += "^" + std::to_string(i);
            }

            if (coeff.at(i - 1) > 0) {
                result += "+";
            }
        }
    }

    if (coeff.at(0) == 0) {
        if (result[result.length() - 1] == '+') {
            result.pop_back();
        }
    } else {
        // add the coefficient at index 0, this is the last value
        result += Utilities::removeTrailingZeros(coeff.at(0));
    }

    return result;
}

/**
 * reduce the polynomial to get the highest degree
 */
void Polynomial::reduce() {
    degree = 0;
    for (int i = coeff.size() - 1; i >= 0; i--) {
        if (coeff.at(i) != 0) {
            degree = i;
            return;
        }
    }
}

/**
 * operator overload for <<
 * @param os the output stream
 * @param p the polynomial function
 * @return output the string representation of polynomial function
 */
std::ostream &operator<<(std::ostream &os, Polynomial p) {
    return os << p.toString();
}
