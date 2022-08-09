/**
 * @file ButtonResponder.cpp
 * @author Michael Dias
 * @brief this class is used to trigger the algorithm to solve the problem corresponding to the button pushed 
 * @version 0.1
 * @date 2021-12-01
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../include/controller/ButtonResponder.h"

/**
 * @brief response to solve matrices
 * @param matrix1 2d vector of doubles containing the values of the first matrix
 * @param matrix2 2d vector of doubles containing the values of the first matrix
 * @param operations list of operations to be performed
 * @param scalar1 the scalar to multiply matrix1 by
 * @param scalar2 the scalar to multiply matrix2 by
 * @return the matrix obtained after performing the operations
 */
std::vector<std::vector<double>> ButtonResponder::solveMatrixButtonResponse(std::vector<std::vector<double>> matrix1,
                                                                            std::vector<std::vector<double>> matrix2,
                                                                            char operations[3], double scalar1,
                                                                            double scalar2) {
    try {
        std::vector<std::vector<double>> result;
        Compute *c = new ComputeMatrix();
        return c->solve(matrix1, matrix2, operations, scalar1, scalar2);
    } catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }
}

/**
 * @brief response to solve an equation
 * @param equation the string representation of the equation to be solved
 * @return the solved equation
 */
std::vector<std::string> ButtonResponder::solveEquationButtonResponse(std::string equation) {
    try {
        Compute *c = new ComputeEquation();
        return c->solve(equation);
    } catch (std::exception &e) {
        // catch any error and throw it again
        throw std::runtime_error(e.what());
    }
}

/**
 * @brief response to solve a system of linear equations
 * @param equations the equations of the system
 * @return the solutions to the system of linear equations
 */
std::vector<std::string> ButtonResponder::solveSysOfLinearEqnButtonResponse(std::vector<std::string> equations) {
    try {
        //Get problem input from GUI
        std::vector<std::string> result;
        Compute *c = new ComputeSysOfLinearEqn();
        return c->solve(equations);
    } catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }
}

/**
 * @brief response to solve sets problem
 * @param set1 data of the first set
 * @param set2 data of the second set
 * @param operation opertion to be performed between the two sets
 * @return the string representation of the set obtained from performing operation on set1 and set2
 */
std::string ButtonResponder::solveSetButtonResponse(const std::vector<double> &set1, const std::vector<double> &set2,
                                                    std::string operation) {
    try {
        //Get problem input from GUI
        Compute *c = new ComputeSet();
        return c->solve(set1, set2, operation);
    } catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }
}

/**
 * @brief response to get a y value to graph
 * @param function the function to use to compute a value
 * @param input the x value (input to function)
 * @return the y value from function(input)
 */
double ButtonResponder::solveGraphButtonResponse(std::string function, std::string input) {
    try {
        Compute *c = new ComputeFunction();
        return c->solve(function, input);
    } catch (std::exception &e) {
        throw std::runtime_error(e.what());
    }
}
