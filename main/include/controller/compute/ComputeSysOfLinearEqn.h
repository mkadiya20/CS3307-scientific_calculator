/**
 * @file ComputeMatrix.h
 * @author Michael Dias
 * @brief This class takes two sets of doubles and performs a set operation on them to obtain a new set
 * @version 1.0
 * @date 2021-11-25
 */

#ifndef COMPUTE_SLE_H
#define COMPUTE_SLE_H

#include "Compute.h"
#include "../../../include/model/matrices/Matrix.h"
#include <algorithm>
#include <map>

class ComputeSysOfLinearEqn : public Compute{
    public:
        std::vector<std::string> solve(const std::vector<std::string>&) const override ;
};

#endif //COMPUTE_SLE_H