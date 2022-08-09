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


#ifndef CONSTANT_H
#define CONSTANT_H

#include "../../../include/model/functions/Function.h"

class Constant: public Function {
private:
    double value;
public:
    explicit Constant(double);
    ~Constant();
    bool isInputConstant() override;
    double getValue() override;
    double getCoef() override;
    double getPower() override;
    void setCoef(double) override;
    void setValue(double) override;
    Function* add(Function*) override;
    Function* subtract(Function*) override;
    Function* multiply(Function*) override;
    Function* pow(Function*) override;
    std::string toString() override;
};

#endif //CONSTANT_H