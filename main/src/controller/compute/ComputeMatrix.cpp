/**
 * @author Michael Dias 
 * @brief Concrete compute class
 * @details Overrides the solve function in Compute that is meant for computing matrices
 * @version 1.0
 * @date 2021-11-23
 */

#include "../../../include/controller/compute/ComputeMatrix.h"

/**
 * @brief performs specified operations on two matrices
 * 
 * @param matrix1 2d vector of doubles containing the values of the first matrix
 * @param matrix2 2d vector of doubles containing the values of the second matrix
 * @param operations operations[0] is the unary operation to perform on matrix1. 'I', 'T', 'D', or NULL 
 *                   operations[1] is the operation between matrix1 and matrix2. '+', '-', or '*' 
 *                   operations[2] is the unary operation to perform on matrix2. 'I', 'T', 'D', or NULL 
 * @param scalar1 scalar to multiply matrix1 by
 * @param scalar2 scalar to multiply matrix2 by
 * @return the matrix obtained after performing the operations
 */
std::vector<std::vector<double>> ComputeMatrix::solve(const std::vector<std::vector<double>>& matrix1, std::vector<std::vector<double>>& matrix2,
                    char operations[3], double scalar1, double scalar2) const{

    auto *first_matrix = new Matrix(matrix1);
    auto *second_matrix = new Matrix(matrix2);
    double first_matrix_value;  //may be assigned value of determinant of first matrix
    double second_matrix_value; //may be assigned value of determinant of first matrix
    double numeric_result;  

    //Perform unimatrix operations on first matrix
    if(operations[0] == 'I') {
        *first_matrix = first_matrix->inverse();
    }
    if(operations[0] == 'T') {
        *first_matrix = first_matrix->inverse();
    }
    if(operations[0] == 'D') {
        first_matrix_value = first_matrix->determinant();
        first_matrix = nullptr;    //set matrix to nullptr to represent it has been reduced to its determinant
    }

    if(first_matrix)
        *first_matrix = first_matrix->scalarMulitply(scalar1);
    else
        first_matrix_value = first_matrix_value*scalar1;

    //Perform unimatrix operations on second matrix
    if(operations[2] == 'I') {
        *second_matrix = second_matrix->inverse();
    }
    if(operations[2] == 'T') {
        *second_matrix = second_matrix->inverse();
    }
    if(operations[2] == 'D'){
        second_matrix_value = second_matrix->determinant();
        second_matrix = nullptr;    //set matrix to nullptr to represent it has been reduced to its determinant
    }

    if(second_matrix)
        *second_matrix = second_matrix->scalarMulitply(scalar2);
    else
        second_matrix_value = second_matrix_value*scalar2;

    
    //Perform connecting operation
    if(operations[1] == '+'){
        if(!first_matrix){
            if(!second_matrix) {
                numeric_result = first_matrix_value + second_matrix_value;
                std::vector<std::vector<double>> res(1, std::vector<double>(1));
                res[0][0] = numeric_result;
                return res;
            }
            else {
                throw std::runtime_error("Error. Cannot add matrix to number");
            }
        }else{
            if(!second_matrix)
                throw std::runtime_error("Error. Cannot add number to matrix");
            else {
                Matrix res = *first_matrix + *second_matrix;
                return res.getValues();
            }
        }
    }else if(operations[1] == '-'){
        if(!first_matrix){
            if(!second_matrix) {
                numeric_result = first_matrix_value - second_matrix_value;
                std::vector<std::vector<double>> res(1, std::vector<double>(1));
                res[0][0] = numeric_result;
                return res;
            }
            else {
                throw std::runtime_error("Error. Cannot subtract number from matrix");
            }
        }else{
            if(!second_matrix)
                throw std::runtime_error("Error. Cannot subtract matrix from number");
            else {
                Matrix res = *first_matrix - *second_matrix;
                return res.getValues();
            }
        }
    }else{  //Multiplying
        if(!first_matrix){
            if(!second_matrix) {
                numeric_result = first_matrix_value * second_matrix_value;
                std::vector<std::vector<double>> res(1, std::vector<double>(1));
                res[0][0] = numeric_result;
                return res;
            }
            else {
                Matrix res = second_matrix->scalarMulitply(first_matrix_value);;
                return res.getValues();
            }
        }else {
            if(!second_matrix) {
                Matrix res = first_matrix->scalarMulitply(second_matrix_value);
                return res.getValues();
            }
            else {
                Matrix res = *first_matrix * *second_matrix;
                return res.getValues();
            }
        }
    }
}

