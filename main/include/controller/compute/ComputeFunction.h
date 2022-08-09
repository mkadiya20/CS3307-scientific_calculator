/**
 * @file ComputeMatrix.h
 * @author Mihir Kadiya
 * @brief This class takes a function and an x input and computes the y value
 * @version 1.0
 * @date 2021-12-01
 */

#ifndef GROUP29_COMPUTEFUNCTION_H
#define GROUP29_COMPUTEFUNCTION_H

#include "Compute.h"

class ComputeFunction : public Compute {
public:
    double solve(const std::string&, const std::string&) override;
};

#endif //GROUP29_COMPUTEFUNCTION_H
