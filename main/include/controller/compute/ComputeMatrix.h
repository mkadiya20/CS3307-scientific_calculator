/**
 * @file ComputeMatrix.h
 * @author Michael Dias
 * @brief This class performs operations on two matrices
 * @version 1.0
 * @date 2021-11-25
 */

#ifndef COMPUTE_MATRIX_H
#define COMPUTE_MATRIX_H

#include "Compute.h"
#include "../../../include/model/matrices/Matrix.h"

/**
 *
 */
class ComputeMatrix : public Compute{
    public:
        std::vector<std::vector<double>> solve(const std::vector<std::vector<double>>&, std::vector<std::vector<double>>&,
                        char[3], double scalar1, double scalar2) const override;
};

#endif //COMPUTE_MATRIX_H