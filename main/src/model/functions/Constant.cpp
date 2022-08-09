/**
 * @brief This class stores a constant function
 *
 * @details The Constant class stores a single number in a way that
 * can be easily used by the other function subclasses
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */

#include <cmath>

#include "../../../include/model/functions/Constant.h"
#include "../../../include/model/functions/Trig.h"
#include "../../../include/model/functions/Log.h"
#include "../../../include/model/functions/Fraction.h"
#include "../../../include/model/functions/Polynomial.h"

Constant::Constant(double newValue) {
    Function::type = "Constant";
    Constant::value = newValue;
}

bool Constant::isInputConstant() {
    return true;
}


double Constant::getValue() {
    return Constant::value;
}

double Constant::getCoef() {
    return getValue();
}

double Constant::getPower() {
    return 1;
}

void Constant::setCoef(double coef) {
    value = coef;
}


void Constant::setValue(double newValue) {
    Constant::value = newValue;
}

Function* Constant::add(Function *f) {
    // if the function is a constant
    if (auto *c = dynamic_cast<Constant*>(f)) {
        double newConst = getValue() + c->getValue();
        Function *newF = new Constant(newConst);
        return newF;
    }

    // if the function is a trig
    if (auto *t = dynamic_cast<Trig*>(f)) {
        if (!t->getNodeInput()) {
            Function *c = new Constant(getValue() + t->getValue());
            return c;
        }
    }

    // if the function is a log
    if (auto *l = dynamic_cast<Log*>(f)) {
        if (!l->getNodeInput()) {
            Function *c = new Constant(getValue() + l->getValue());
            return c;
        }
    }

    // if the function is a polynomial
    if (auto *p = dynamic_cast<Polynomial*>(f)) {
        return p->add(this);
    }

    // if the function is a fraction
    if(auto *frac = dynamic_cast<Fraction*>(f)) {
        Function *cToF = Fraction::to_fraction(this);
        return *cToF + *frac;
    }

    return nullptr;
}

Function* Constant::subtract(Function *f) {
    // if the function is a constant
    if (auto *c = dynamic_cast<Constant*>(f)) {
        double newConst = getValue() - c->getValue();
        Function *newF = new Constant(newConst);
        return newF;
    }

    // if the function is a trig
    if (auto *t = dynamic_cast<Trig*>(f)) {
        if (!t->getNodeInput()) {
            Function *c = new Constant(getValue() - t->getValue());
            return c;
        }
    }

    // if the function is a log
    if (auto *l = dynamic_cast<Log*>(f)) {
        if (!l->getNodeInput()) {
            Function *c = new Constant(getValue() - l->getValue());
            return c;
        }
    }

    // if the function is a polynomial
    if (auto *p = dynamic_cast<Polynomial*>(f)) {
        Function *poly = new Polynomial(getValue(), p->getVariable(), 0);
        return poly->subtract(p);
    }

    // if the function is a fraction
    if(auto *frac = dynamic_cast<Fraction*>(f)) {
        Function *cToF = Fraction::to_fraction(this);
        return *cToF - *frac;
    }

    return nullptr;
}

Function* Constant::multiply(Function *f) {
    // if the function is a constant
    if (auto *c = dynamic_cast<Constant*>(f)) {
        double newConst = getValue() * c->getValue();
        Function *newF = new Constant(newConst);
        return newF;
    }

    // if the function is a trig
    if (auto *t = dynamic_cast<Trig*>(f)) {
        if (!t->getNodeInput()) {
            Function *c = new Constant(getValue() * t->getValue());
            return c;
        } else {
            Function *trig = new Trig(t->getNodeInput(), t->getTrigType(),
                                      getValue() * t->getCoef(), t->getPower());
            return trig;
        }
    }

    // if the function is a log
    if (auto *l = dynamic_cast<Log*>(f)) {
        if (!l->getNodeInput()) {
            Function *c = new Constant(getValue() * l->getValue());
            return c;
        } else {
            Function *log = new Log(l->getNodeInput(), l->getBase(),
                                    getValue() * l->getCoef(), l->getPower());
            return log;
        }
    }

    // if the function is a polynomial
    if (auto *p = dynamic_cast<Polynomial*>(f)) {
        return p->multiply(this);
    }

    // if the function is a fraction
    if(auto *frac = dynamic_cast<Fraction*>(f)) {
        Function *cToF = Fraction::to_fraction(this);
        return *cToF * *frac;
    }

    return nullptr;
}

Function *Constant::pow(Function *f) {
    // if the function is a constant
    if (auto *c = dynamic_cast<Constant*>(f)) {
        double newConst = std::pow(getValue(), c->getValue());
        Function *newF = new Constant(newConst);
        return newF;
    }

    // if the function is a trig
    if (auto *t = dynamic_cast<Trig*>(f)) {
        if (!t->getNodeInput()) {
            Function *c = new Constant(std::pow(getValue(), t->getValue()));
            return c;
        }
    }

    // if the function is a log
    if (auto *l = dynamic_cast<Log*>(f)) {
        if (!l->getNodeInput()) {
            Function *c = new Constant(std::pow(getValue(), l->getValue()));
            return c;
        }
    }

    // if the function is a fraction
    if (auto *frac = dynamic_cast<Fraction*>(f)) {
        Function *c = new Constant(std::pow(getValue(), frac->getValue()));
        return c;
    }

    return nullptr;
}

std::string Constant::toString() {
    return Utilities::removeTrailingZeros(getValue());
}