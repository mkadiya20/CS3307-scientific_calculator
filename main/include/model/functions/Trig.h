/**
 * @brief This class stores a trig function
 *
 * @details The Trig class stores a trig type and input to allow trig operations to be performed
 *
 * @author Mihir Kadiya
 * @author Brandon Howe
 * @version 1.0
 */

#ifndef TRIG_H
#define TRIG_H

#include <iostream>
#include <cmath>
#include "../../../include/model/functions/Function.h"
#include "../../../include/model/utilities/Utilities.h"

class Trig: public Function {
private:
    const double PI = atan(1) * 4;
    Node *nodeInput;
    double valueInput;
    double coef;
    double power;
    std::string trigType;
public:
    Trig(Node*, std::string, double, double);
    Trig(double, std::string, double, double);
    ~Trig() = default;

    std::string getTrigType();
    bool isInputConstant() override;
    Node *getNodeInput();
    double getValueInput() const;
    void setValue(double) override;

    double getCoef() override;
    double getPower() override;
    void setCoef(double) override;
    void setPower(double) override;

    double getValue() override;

    Function* add(Function*) override;
    Function* subtract(Function*) override;
    Function* multiply(Function*) override;
    Function* pow(Function*) override;

    std::string toString() override;
};

#endif //TRIG_H