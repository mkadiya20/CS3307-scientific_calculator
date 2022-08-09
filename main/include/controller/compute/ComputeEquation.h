/**
 * @file ComputeEquation.h
 * @author Michael Dias
 * @brief This class performs the steps to solve an equation
 * @version 1.0
 * @date 2021-11-25
 */

#ifndef COMPUTE_EQUATION_H
#define COMPUTE_EQUATION_H

#include "Compute.h"

class ComputeEquation : public Compute {
    public:
        std::vector<std::string> solve(const std::string&) const override;
};

#endif //COMPUTE_EQUATION_H