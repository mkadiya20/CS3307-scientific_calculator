/**
 * @file ComputeSet.cpp
 * @author Michael Dias
 * @brief This class takes two sets and performs an operation between them
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef COMPUTE_SET_H
#define COMPUTE_SET_H

#include "Compute.h"
#include "../../../include/model/sets/Sets.h"

class ComputeSet : public Compute{
    public:
        std::string solve(const std::vector<double>&, const std::vector<double>&, const std::string&) override;
};

#endif //COMPUTE_SET_H