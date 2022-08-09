/**
 * @brief This class stores a logarithm function
 *
 * @details The Log class stores a base and input to allow logarithms to be performed
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */

#ifndef LOG_H
#define LOG_H

#include <cmath>
#include "../../../include/model/functions/Function.h"
#include "../../../include/model/functions/Constant.h"
#include "../../../include/model/utilities/Utilities.h"

class Log: public Function {
private:
    Node *nodeInput;
    double valueInput;
    double coef;
    double power;
    double base;
public:
    Log(Node*, double, double, double);
    Log(double, double, double, double);
    ~Log() = default;

    bool isInputConstant() override;
    double getValueInput() const;
    Node *getNodeInput();
    double getCoef() override;
    double getPower() override;
    double getBase() const;
    double getValue() override;
    void setValue(double) override;
    void setCoef(double) override;
    void setPower(double) override;

    Function* add(Function*) override;
    Function* subtract(Function*) override;
    Function* multiply(Function*) override;
    Function* pow(Function*) override;

    std::string toString() override;
};
#endif
