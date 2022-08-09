/**
 * @brief This class stores a logarithm function
 *
 * @details The Log class stores a base and input to allow logarithms to be performed
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */


#include "../../../include/model/functions/Log.h"
#include "../../../include/model/functions/Trig.h"
#include "../../../include/model/functions/Fraction.h"
#include "../../../include/model/functions/Polynomial.h"

/**
 * parameterised constructor for inputs involving variables
 * @param input the subtree expression as an inner function
 * @param base the base of the logarithm
 * @param coef the coefficient of the logarithm
 * @param power the power of the logarithm
 */
Log::Log(Node *input, double base, double coef, double power) {
    Function::type = "Log";
    Log::nodeInput = input;
    Log::base = base;
    Log::coef = coef;
    Log::power = power;

    // value input should not matter if node input is defined
    valueInput = 0;
}


/**
 * parameterised constructor for inputs involving constants
 * @param input a constant value input
 * @param base the base of the logarithm
 * @param coef the coefficient of the logarithm
 * @param power the power of the logarithm
 */
Log::Log(double input, double base, double coef, double power) {
    Function::type = "Log";
    Log::valueInput = input;
    Log::base = base;
    Log::coef = coef;
    Log::power = power;

    // node input should not matter if value input is defined
    Log::nodeInput = nullptr;
}


/**
 * check if the inner function of log is constant
 * @return true if input is a constant value, false otherwise
 */
bool Log::isInputConstant() {
    if (Log::nodeInput) {
        return false;
    }
    return true;
}


/**
 * getter method for constant value input
 * @return the constant value
 */
double Log::getValueInput() const {
    return Log::valueInput;
}


/**
 * getter method for node value input
 * @return the node input
 */
Node *Log::getNodeInput() {
    return Log::nodeInput;
}


/**
 * getter method for coefficient of the function
 * @return the coefficient of the logarithm
 */
double Log::getCoef() {
    return Log::coef;
}


/**
 * getter method for power of the function
 * @return the power
 */
double Log::getPower() {
    return Log::power;
}


/**
 * getter method for base of the function
 * @return the base
 */
double Log::getBase() const {
    return Log::base;
}


/**
 * getter method for the logarithm of constant value
 * @return the log(constant)
 */
double Log::getValue() {
    return log(getValueInput()) / log(getBase());
}


/**
 * setter method for constant value
 * @param value the constant value
 */
void Log::setValue(double value) {
    Log::valueInput = value;
    Log::nodeInput = nullptr;
}


/**
 * setter method for coefficient
 * @param coef the coefficient
 */
void Log::setCoef(double coef) {
    Log::coef = coef;
}


/**
 * setter method for power
 * @param power the power
 */
void Log::setPower(double power) {
    Log::power = power;
}


/**
 * add method for adding various functions into the log functions
 * @param f a function pointer
 * @return a function after addition is done, nullptr if functions cannot be added
 */
Function *Log::add(Function *f) {
    // check if function is log
    if (auto *l = dynamic_cast<Log *>(f)) {
        // check if inner functions are both constant
        if (!nodeInput && !l->getNodeInput()) {
            double val = getValue() + l->getValue();
            Function *c = new Constant(val);
            return c;
        } else {
            bool flag = true;

            // if the base are not the same
            if (getBase() != l->getBase()) {
                flag = false;
            }

            // if subtrees are not the same
            if (!Utilities::equalTrees(getNodeInput(), l->getNodeInput())) {
                flag = false;
            }

            // if exponents are not the same
            if (getPower() != l->getPower()) {
                flag = false;
            }

            // if condition passes, functions can be added
            if (flag) {
                Function *log = new Log(getNodeInput(), getBase(),
                                        getCoef() + l->getCoef(), getPower());
                return log;
            } else {
                return nullptr;
            }
        }
    }

    // check if the function is a polynomial
    if (auto *p = dynamic_cast<Polynomial *>(f)) {
        if (!nodeInput) {
            p->getCoeffArray()[0] += getValue();
            return p;
        }
    }

    // check if function is a trig
    if (auto *t = dynamic_cast<Trig *>(f)) {
        if (!nodeInput && !t->getNodeInput()) {
            double val = getValue() + t->getValue();
            Function *c = new Constant(val);
            return c;
        }
    }

    // check if function is a constant
    if (auto *c = dynamic_cast<Constant *>(f)) {
        // ensure that input is a value input, not node input
        if (!nodeInput) {
            double newConst = getValue() + c->getValue();
            Function *newF = new Constant(newConst);
            return newF;
        }
    }

    if (auto *frac = dynamic_cast<Fraction *>(f)) {
        if (!nodeInput) {
            Function *lToF = Fraction::to_fraction(this);
            return *lToF + *frac;
        }
    }

    return nullptr;
}


/**
 * add method for subtracting various functions from the log function
 * @param f a function pointer
 * @return a function after subtraction is done, nullptr if functions cannot be subtracted
 */
Function *Log::subtract(Function *f) {
    // check if function is log
    if (auto *l = dynamic_cast<Log *>(f)) {
        // check if inner functions are both constant
        if (!nodeInput && !l->getNodeInput()) {
            double val = getValue() - l->getValue();
            Function *c = new Constant(val);
            return c;
        } else {
            bool flag = true;

            // if the base are not the same
            if (getBase() != l->getBase()) {
                flag = false;
            }

            // if subtrees are not the same
            if (!Utilities::equalTrees(getNodeInput(), l->getNodeInput())) {
                flag = false;
            }

            // if exponents are not the same
            if (getPower() != l->getPower()) {
                flag = false;
            }

            // if condition passes, functions can be added
            if (flag) {
                if (getCoef() - l->getCoef() != 0) {
                    Function *log = new Log(getNodeInput(), getBase(),
                                            getCoef() - l->getCoef(), getPower());
                    return log;
                } else {
                    Function *c = new Constant(0);
                    return c;
                }
            } else {
                return nullptr;
            }
        }
    }

    // check if the function is a polynomial
    if (auto *p = dynamic_cast<Polynomial *>(f)) {
        if (!nodeInput) {
            p->getCoeffArray()[0] -= getValue();
            return p;
        }
    }

    // check if function is a trig
    if (auto *t = dynamic_cast<Trig *>(f)) {
        if (!nodeInput && !t->getNodeInput()) {
            double val = getValue() - t->getValue();
            Function *c = new Constant(val);
            return c;
        }
    }

    // check if function is a constant
    if (auto *c = dynamic_cast<Constant *>(f)) {
        // ensure that input is a value input, not node input
        if (!nodeInput) {
            double newConst = getValue() - c->getValue();
            Function *newF = new Constant(newConst);
            return newF;
        }
    }

    if (auto *frac = dynamic_cast<Fraction *>(f)) {
        if (!nodeInput) {
            Function *lToF = Fraction::to_fraction(this);
            return *lToF - *frac;
        }
    }

    return nullptr;
}


/**
 * multiply method for multiplying various functions into the log functions
 * @param f a function pointer
 * @return a function after multiplication is done, nullptr if functions cannot be multiplied
 */
Function *Log::multiply(Function *f) {
    // check if function is log
    if (auto *l = dynamic_cast<Log *>(f)) {
        // check if inner functions are both constant
        if (!nodeInput && !l->getNodeInput()) {
            double val = getValue() * l->getValue();
            Function *c = new Constant(val);
            return c;
        } else {
            bool flag = true;

            // if the base are not the same
            if (getBase() != l->getBase()) {
                flag = false;
            }

            // if subtrees are not the same
            if (!Utilities::equalTrees(getNodeInput(), l->getNodeInput())) {
                flag = false;
            }

            // if condition passes, functions can be added
            if (flag) {
                Function *log = new Log(getNodeInput(), getBase(),
                                        getCoef() * l->getCoef(),
                                        getPower() + l->getPower());
                return log;
            } else {
                return nullptr;
            }
        }
    }

    // check if the function is a polynomial
    if (auto *p = dynamic_cast<Polynomial *>(f)) {
        if (!nodeInput) {
            return p->scalarMultiply(getValue());
        }
    }

    // check if function is a trig
    if (auto *t = dynamic_cast<Trig *>(f)) {
        if (!nodeInput && !t->getNodeInput()) {
            double val = getValue() * t->getValue();
            Function *c = new Constant(val);
            return c;
        }
    }

    // check if function is a constant
    if (auto *c = dynamic_cast<Constant *>(f)) {
        if (!nodeInput) {
            Function *func = new Constant(getValue() * c->getValue());
            return func;
        } else {
            Function *log = new Log(getNodeInput(), getBase(),
                                    getCoef() * c->getValue(), getPower());
            return log;
        }
    }

    // check if function is a fraction
    if (auto *frac = dynamic_cast<Fraction *>(f)) {
        if (!nodeInput) {
            Function *lToF = Fraction::to_fraction(this);
            return *lToF * *frac;
        }
    }

    return nullptr;
}


/**
 * power method for doing exponents of various functions into the log functions
 * @param f a function pointer
 * @return a function after power is done, nullptr if functions cannot be powered
 */
Function *Log::pow(Function *f) {
    // check if function is log
    if (auto *l = dynamic_cast<Log *>(f)) {
        // check if inner functions are both constant
        if (!nodeInput && !l->getNodeInput()) {
            double val = std::pow(getValue(), l->getValue());
            Function *c = new Constant(val);
            return c;
        }
    }

    // check if function is a trig
    if (auto *t = dynamic_cast<Trig *>(f)) {
        if (!nodeInput && !t->getNodeInput()) {
            double val = std::pow(getValue(), t->getValue());
            Function *c = new Constant(val);
            return c;
        }
    }

    // check if function is a constant
    if (auto *c = dynamic_cast<Constant *>(f)) {
        // ensure that input is a value input, not node input
        if (!nodeInput) {
            double newConst = std::pow(getValue(), c->getValue());
            Function *newF = new Constant(newConst);
            return newF;
        } else {
            setPower(getPower() * c->getValue());
            return this;
        }
    }

    if (auto *frac = dynamic_cast<Fraction *>(f)) {
        if (!nodeInput) {
            Function *c = new Constant(std::pow(getValue(), frac->getValue()));
            return c;
        }
    }

    return nullptr;
}


/**
 * converts the log into a string format
 * @return the string format of the function
 */
std::string Log::toString() {
    std::string result;

    if (getCoef() != 1) {
        result += Utilities::removeTrailingZeros(getCoef()) + "*";
    }

    result += "log(";

    if (nodeInput) {
        if (nodeInput->getLeft()) {
            result += nodeInput->getLeft()->toString();
        }
        result += Utilities::removeTrailingZeros(nodeInput->getValue()->value);
        if (nodeInput->getRight()) {
            result += nodeInput->getRight()->toString();
        }
    } else {
        result += Utilities::removeTrailingZeros(getValueInput());
    }

    result += ")";

    if (getPower() != 1) {
        result += "^" + Utilities::removeTrailingZeros(getPower());
    }

    return result;
}