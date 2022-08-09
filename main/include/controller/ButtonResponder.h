/**
 * @file ButtonResponder.h
 * @author Michael Dias
 * @brief this class is used to trigger the algorithm to solve the problem corresponding to the button pushed 
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef BUTTON_RESPONDER_H
#define BUTTON_RESPONDER_H

#include <string>
#include <QString>
#include "../../include/controller/compute/Compute.h"
#include "../../include/controller/compute/ComputeEquation.h"
#include "../../include/controller/compute/ComputeMatrix.h"
#include "../../include/controller/compute/ComputeSet.h"
#include "../../include/controller/compute/ComputeSysOfLinearEqn.h"
#include "../../include/controller/compute/ComputeFunction.h"

class ButtonResponder{
    public:
        static std::vector<std::vector<double>> solveMatrixButtonResponse(std::vector<std::vector<double>> matrix1, std::vector<std::vector<double>> matrix2,
                                              char operations[3], double scalar1, double scalar2);
        static std::vector<std::string> solveEquationButtonResponse(std::string equation);
        static std::vector<std::string> solveSysOfLinearEqnButtonResponse(std::vector<std::string> equations);
        static std::string solveSetButtonResponse(const std::vector<double>&, const std::vector<double>&, std::string operation);
        static double solveGraphButtonResponse(std::string function, std::string input);
};

#endif //BUTTON_RESPONDER_H