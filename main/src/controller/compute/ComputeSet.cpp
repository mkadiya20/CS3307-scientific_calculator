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
#include "../../../include/controller/compute/ComputeSet.h"
#include "../../../include/model/utilities/Utilities.h"

/**
 * @brief performs specified operations on the two sets
 * @param set1 data of the first set
 * @param set2 data of the second set
 * @param operation operation to be pergormed between the two sets 
 * @return the string representation of the set obtained from performing operation on set1 and set2
 */
std::string ComputeSet::solve(const std::vector<double>& set1, const std::vector<double>& set2,
                              const std::string& operation) {
    try {
        std::vector<double> res;
        std::string result;
        if (operation == "\342\210\252") {
            res = Sets::Union(set1, set2);
        } else if (operation == "\342\210\251") {
            res = Sets::intersection(set1, set2);
        } else if (operation == "-") {
            res = Sets::Subtraction(set1, set2);
        } 
        for (int i = 0; i < res.size(); i++) {
            result.append(Utilities::removeTrailingZeros(res.at(i)));
            if (i + 1 != res.size())
                result.append(", ");
        }
        return result;
    } catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }
}