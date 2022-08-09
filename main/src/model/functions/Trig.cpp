/**
 * @brief This class stores a trig function
 *
 * @details The Trig class stores a trig type and input to allow trig operations to be performed
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */


#include <cmath>

#include "../../../include/model/functions/Trig.h"
#include "../../../include/model/functions/Log.h"
#include "../../../include/model/functions/Fraction.h"
#include "../../../include/model/functions/Constant.h"
#include "../../../include/model/functions/Polynomial.h"


/**
 * parameterised constructor for inputs involving variables
 * @param input the subtree expression as an inner function
 * @param base the base of the trig
 * @param coef the coefficient of the trig
 * @param power the power of the trig
 */
Trig::Trig(Node *nodeInput, std::string trigType, double coef = 1, double power = 1) {
    Function::type = "Trig";
    Trig::trigType = trigType;
    Trig::nodeInput = nodeInput;
    Trig::coef = coef;
    Trig::power = power;
}


/**
 * parameterised constructor for inputs involving constants
 * @param input a constant value input
 * @param base the base of the trig
 * @param coef the coefficient of the trig
 * @param power the power of the trig
 */
Trig::Trig(double valueInput, std::string trigType, double coef = 1, double power = 1) {
    Function::type = "Trig";
    Trig::trigType = trigType;
    Trig::valueInput = valueInput * PI / 180;
    Trig::coef = coef;
    Trig::power = power;
    Trig::nodeInput = nullptr;

}


/**
 * getter method for type of trig function
 * @return "sin", "cos", "tan"
 */
std::string Trig::getTrigType() {
    return trigType;
}


/**
 * check if the inner function of trig is constant
 * @return true if input is a constant value, false otherwise
 */
bool Trig::isInputConstant() {
    if (nodeInput) {
        return false;
    }
    return true;
}


/**
 * getter method for node value input
 * @return the node input
 */
Node *Trig::getNodeInput() {
    return Trig::nodeInput;
}


/**
 * getter method for constant value input
 * @return the constant value
 */
double Trig::getValueInput() const {
    return Trig::valueInput;
}


/**
 * setter method for constant value
 * @param value the constant value
 */
void Trig::setValue(double newInput) {
    Trig::valueInput = newInput * PI / 180;
    Trig::nodeInput = nullptr;
}


/**
 * getter method for coefficient of the function
 * @return the coefficient of the logarithm
 */
double Trig::getCoef() {
    return Trig::coef;
}


/**
 * getter method for power of the function
 * @return the power
 */
double Trig::getPower() {
    return Trig::power;
}


/**
 * setter method for coefficient
 * @param coef the coefficient
 */
void Trig::setCoef(double newCoef) {
    Trig::coef = newCoef;
}


/**
 * setter method for power
 * @param power the power
 */
void Trig::setPower(double newPower) {
    Trig::power = newPower;
}


/**
 * getter method for the trig of constant value
 * @return the trig(constant)
 */
double Trig::getValue() {
    if (getTrigType() == "sin") {
        return sin(getValueInput() * getCoef());
    } else if (getTrigType() == "cos") {
        return cos(getValueInput() * getCoef());
    } else {
        return tan(getValueInput() * getCoef());
    }
}


/**
 * add method for adding various functions into the log functions
 * @param f a function pointer
 * @return a function after addition is done, nullptr if functions cannot be added
 */
Function *Trig::add(Function *f) {
    // check if function is a trig
    if (auto *t = dynamic_cast<Trig *>(f)) {

        // check if the inner function is a constant
        // inner function is always the most reduced form
        //if (get)

        if (!nodeInput && !t->nodeInput) {
            double combined = getValue() + f->getValue();
            Function *c = new Constant(combined);
            return c;
        } else {
            bool flag = true;
            // both trig types must be same to perform any operations
            if (getTrigType() != t->getTrigType()) {
                flag = false;
            }

            // if subtrees are not the same
            if (!Utilities::equalTrees(getNodeInput(), t->getNodeInput())) {
                flag = false;
            }

            // if exponents are not the same
            if (power != t->getPower()) {
                flag = false;
            }

            if (flag) {
                // Can Combine
                Function *trig = new Trig(getNodeInput(), getTrigType(),
                                          this->getCoef() + t->getCoef(), getPower());
                return trig;
            } else {
                // Can't combine
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

    // check if the functions is a log
    if (auto *l = dynamic_cast<Log *>(f)) {
        // check if both functions have constant inner functions
        if (!nodeInput && !l->getNodeInput()) {
            double val = getValue() + l->getValue();
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

    // if the function is a fraction
    if (auto *frac = dynamic_cast<Fraction *>(f)) {
        if (!nodeInput) {
            Function *tToF = Fraction::to_fraction(this);
            return *tToF + *frac;
        }
    }

    return nullptr;
}


/**
 * add method for subtracting various functions from the log function
 * @param f a function pointer
 * @return a function after subtraction is done, nullptr if functions cannot be subtracted
 */
Function *Trig::subtract(Function *f) {
    if (auto *t = dynamic_cast<Trig *>(f)) {

        // check if the inner function is a constant
        // inner function is always the most reduced form

        if (!nodeInput && !t->nodeInput) {
            double combined = getValue() - f->getValue();
            Function *c = new Constant(combined);
            return c;
        } else {
            bool flag = true;
            // both trig types must be same to perform any operations
            if (getTrigType() != t->getTrigType()) {
                flag = false;
            }

            // if subtrees are not the same
            if (!Utilities::equalTrees(getNodeInput(), t->getNodeInput())) {
                flag = false;
            }

            // if exponents are not the same
            if (power != t->getPower()) {
                flag = false;
            }

            if (flag) {
                // Can Combine
                if (this->getCoef() - t->getCoef() != 0) {
                    Function *trig = new Trig(getNodeInput(), getTrigType(),
                                              this->getCoef() - t->getCoef(), getPower());
                    return trig;
                } else {
                    Function *c = new Constant(0);
                    return c;
                }
            } else {
                // Can't combine
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

    // check if the functions is a log
    if (auto *l = dynamic_cast<Log *>(f)) {
        // check if both functions have constant inner functions
        if (!nodeInput && !l->getNodeInput()) {
            double val = getValue() - l->getValue();
            Function *c = new Constant(val);
            return c;
        }
    }

    // check if function is a constant
    if (auto *c = dynamic_cast<Constant *>(f)) {
        if (!nodeInput) {
            double newConst = getValue() - c->getValue();
            Function *newF = new Constant(newConst);
            return newF;
        }
    }

    // if the function is a fraction
    if (auto *frac = dynamic_cast<Fraction *>(f)) {
        if (!nodeInput) {
            Function *tToF = Fraction::to_fraction(this);
            return *tToF - *frac;
        }
    }

    return nullptr;
}


/**
 * multiply method for multiplying various functions into the log functions
 * @param f a function pointer
 * @return a function after multiplication is done, nullptr if functions cannot be multiplied
 */
Function *Trig::multiply(Function *f) {
    // if cast is valid, then both functions are trig
    if (auto *t = dynamic_cast<Trig *>(f)) {

        // check if the inner function is a constant
        // inner function is always the most reduced form
        if (t && !nodeInput && !t->nodeInput) {
            double combined = getValue() * f->getValue();
            Function *c = new Constant(combined);
            return c;
        } else {
            bool flag = true;
            // both trig types must be same to perform any operations
            if (getTrigType() != t->getTrigType()) {
                flag = false;
            }

            // if subtrees are not the same
            if (!Utilities::equalTrees(getNodeInput(), t->getNodeInput())) {
                flag = false;
            }

            if (flag) {
                // Can Combine
                Function *trig = new Trig(getNodeInput(), getTrigType(),
                                          getCoef() * t->getCoef(), getPower() + t->getPower());
                return trig;
            } else {
                // Can't combine
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

    // check if the functions is a log
    if (auto *l = dynamic_cast<Log *>(f)) {
        // check if both functions have constant inner functions
        if (!nodeInput && !l->getNodeInput()) {
            double val = getValue() * l->getValue();
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
            Function *trig = new Trig(getNodeInput(), getTrigType(),
                                      getCoef() * c->getValue(), getPower());
            return trig;
        }
    }

    // if the function is a fraction
    if (auto *frac = dynamic_cast<Fraction *>(f)) {
        if (!nodeInput) {
            Function *tToF = Fraction::to_fraction(this);
            return *tToF * *frac;
        }
    }

    return nullptr;
}


/**
 * power method for doing exponents of various functions into the log functions
 * @param f a function pointer
 * @return a function after power is done, nullptr if functions cannot be powered
 */
Function *Trig::pow(Function *f) {
    if (auto *t = dynamic_cast<Trig *>(f)) {

        // check if the inner function is a constant
        // inner function is always the most reduced form
        if (!nodeInput && !t->nodeInput) {
            double combined = std::pow(getValue(), f->getValue());
            Function *c = new Constant(combined);
            return c;
        }
    }

    // check if the functions is a log
    if (auto *l = dynamic_cast<Log *>(f)) {
        // check if both functions have constant inner functions
        if (!nodeInput && !l->getNodeInput()) {
            double val = std::pow(getValue(), l->getValue());
            Function *c = new Constant(val);
            return c;
        }
    }

    // check if function is a constant
    if (auto *c = dynamic_cast<Constant *>(f)) {
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
 * converts the trig into a string format
 * @return the string format of the function
 */
std::string Trig::toString() {
    std::string result;

    if (getCoef() != 1) {
        result += Utilities::removeTrailingZeros(getCoef()) + "*";
    }

    result += getTrigType() + "(";

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