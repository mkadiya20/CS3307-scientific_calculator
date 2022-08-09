/**
 * @brief This class is the parent class of all functions
 *
 * @details The Function class is used as a parent of all types of functions, storing shared information of functions
 * and allowing operations between different functions to be handled through overrided methods
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */

#ifndef FUNCTION_H
#define FUNCTION_H

#include <iostream>

class Function {
protected:
    std::string type;
public:
    Function();
    ~Function() = default;

    std::string getType();

    virtual bool isInputConstant() { return true; };
    virtual double getValue() { return -1; };
    virtual void setValue(double) {};
    virtual double getCoef() { return -1; };
    virtual double getPower() { return -1; };
    virtual void setCoef(double) {};
    virtual void setPower(double) {};

    virtual Function *add(Function *) { return nullptr; };
    virtual Function *subtract(Function *) { return nullptr; };
    virtual Function *multiply(Function *) { return nullptr; };
    virtual Function *pow(Function *) { return nullptr; };
    virtual std::string toString() { return ""; };
};

Function *operator+(Function &f1, Function &f2);
Function *operator-(Function &f1, Function &f2);
Function *operator*(Function &f1, Function &f2);

#endif //FUNCTION_H