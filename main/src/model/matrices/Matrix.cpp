/**
 * @brief This class represents matrices and allows for matrix operations 
 * @author Michael Dias
 * @version 0.1
 */

#include "../../../include/model/matrices/Matrix.h"

/**
 * @brief Construct a new Matrix will given values
 * @param input the 2D set of values to assign to the new Matrix
 */
Matrix::Matrix(std::vector<std::vector<double>> input) {
    matrix = input;
}

/**
 * @brief operator overload of + symbol to allow matrix addition
 * @param other the matrix to be added to the current one
 * @return Matrix the resulting matrix from adding this matrix + other matrix 
 */
Matrix Matrix::operator+(const Matrix &other) {
    if (matrix.size() == other.matrix.size() && matrix[0].size() == other.matrix[0].size()) {
        // Matrix sizes are compatable; add matrices
        std::vector<std::vector<double>> result = matrix;
        for (int row = 0; row < matrix.size(); row++) {
            for (int col = 0; col < matrix[0].size(); col++)
                result[row][col] += other.matrix[row][col];
        }
        return Matrix(result);
    } else
        throw std::runtime_error("matrix dimensions are incompatable for this operation");
}

/**
 * @brief operator overload of - symbol to allow matrix subtraction
 * @param other the matrix to be subtracted from the current one
 * @return Matrix the resulting matrix from subtracting other matrix from this matrix
 */
Matrix Matrix::operator-(const Matrix &other) {
    if (matrix.size() == other.matrix.size() && matrix[0].size() == other.matrix[0].size()) {
        // Matrix sizes are compatable; subtract matrices
        std::vector<std::vector<double>> result = matrix;
        for (int row = 0; row < matrix.size(); row++) {
            for (int col = 0; col < matrix[0].size(); col++)
                result[row][col] -= other.matrix[row][col];
        }
        return Matrix(result);
    } else
        throw std::runtime_error("matrix dimensions are incompatable for this operation");
}

/**
 * @brief operator overload of * symbol to allow matrix multiplication
 * @param other the matrix to be multiplied with the current one
 * @return Matrix the resulting matrix from this matrix dot producted with other matrix 
 */
Matrix Matrix::operator*(const Matrix &other) {
    if (matrix.size() == other.matrix[0].size() && matrix[0].size() == other.matrix.size()) {
        // Matrix sizes are compatable; multiply matrices
        std::vector<std::vector<double>> result;
        result.resize(matrix.size(), std::vector<double>(other.matrix[0].size()));
        int num_terms = matrix[0].size();
        int current_element = 0;
        for (int row = 0; row < matrix.size(); row++) {
            for (int col = 0; col < other.matrix[0].size(); col++) {
                current_element = 0;
                for (int k = 0; k < num_terms; k++)
                    current_element += matrix[row][k] * other.matrix[k][col];
                result[row][col] = current_element;
            }
        }
        return Matrix(result);
    } else
        throw std::runtime_error("matrix dimensions are incompatable for this operation");
}

/**
 * @brief transposes the current matrix
 * @return true if successful. else false
 */
Matrix Matrix::transpose() {
    if (!isSquare())
        throw std::runtime_error("can not transpose non square matrix");
    std::vector<std::vector<double>> result;
    result.resize(matrix.size(), std::vector<double>(matrix[0].size()));
    for (int row = 0; row < matrix.size(); row++) {
        for (int col = 0; col < matrix[0].size(); col++)
            result[row][col] = matrix[col][row];
    }
    return Matrix(result);
}


/**
 * @brief scaler multiplies the current matrix
 * @param scaler the scaler to multiply the matrix by 
 */
Matrix Matrix::scalarMulitply(double scaler) {
    std::vector<std::vector<double>> result;
    result.resize(matrix.size(), std::vector<double>(matrix[0].size()));
    for (int row = 0; row < matrix.size(); row++) {
        for (int col = 0; col < matrix[0].size(); col++)
            result[row][col] = matrix[row][col] * scaler;
    }
    return Matrix(result);
}

/**
 * @brief finds the cofactor of the current matrix at the given index
 * @details computes cofactor of 3x3 matrix on the spot. Cofactor and determinate 
 * functions work together to recursively compute larger matrices 
 * @return the cofactor of the matrix at the given index
 */
double Matrix::cofactor(int row, int col) {
    if (!isSquare())
        throw std::runtime_error("can not compute cofactor of non square matrix");
    if (matrix.size() < 3)
        throw std::runtime_error("can not compute cofactor of matrix smaller than 3x3");
    row--;
    col--;   //convert row and col so that it matches vector indices
    // Get the sub matrix of matrix defined by elements in different rows and columns than row, col 
    std::vector<std::vector<double>> sub_matrix;
    sub_matrix.resize(matrix.size() - 1, std::vector<double>(matrix[0].size() - 1));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (i != row && j != col) {
                if (i > row) {
                    if (j > col)
                        sub_matrix[i - 1][j - 1] = matrix[i][j];
                    else
                        sub_matrix[i - 1][j] = matrix[i][j];
                } else {
                    if (j > col)
                        sub_matrix[i][j - 1] = matrix[i][j];
                    else
                        sub_matrix[i][j] = matrix[i][j];
                }
            }
        }
    }
    // Compute the determinant of the sub matrix 
    double det = Matrix(sub_matrix).determinant();
    // Multiply determinant by proper sign to get the cofactor
    double cofactor = ((row + col) % 2 == 0) ? det : -1 * det;
    return cofactor;
}

/**
 * @brief finds the determinate of the current matrix
 * @details computes determinate of 2x2 matrix on the spot. Cofactor and determinate 
 * functions work together to recursively compute larger matrices 
 * @return the determinate of the matrix
 */
double Matrix::determinant() {
    if (!isSquare()) {
        throw std::runtime_error("can not compute determinant of non square matrix");
    }
    if (matrix.size() == 2)
        return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]);
    else {
        int sum = 0;
        for (int i = 0; i < matrix[0].size(); i++) {
            sum += matrix[0][i] * cofactor(1, i + 1);
        }
        return sum;
    }
}

/**
 * @brief finds the inverse of the current matrix
 * @return the inverse matrix of the current matrix
 */
Matrix Matrix::inverse() {
    double det = determinant();
    if (det == 0)
        throw std::runtime_error("The inverse does not exist for this matrix");
    else {
        //Get Adjoint Matrix
        std::vector<std::vector<double>> adj;
        adj.resize(matrix.size(), std::vector<double>(matrix[0].size()));
        for (int row = 0; row < matrix.size(); row++) {
            for (int col = 0; col < matrix[0].size(); col++)
                adj[row][col] = cofactor(row + 1, col + 1);
        }
        Matrix adjoint = Matrix(adj);
        //Scalar  multiply adjoint matrix by 1/determinant to get inverse
        Matrix inverse = adjoint.scalarMulitply(1 / det);
        return inverse;
    }
}

/**
 * @brief ERO for swapping rows. swaps the two specified row
 * 
 * @param first_row the index of the row to be swapped with the second row
 * @param second_row the index of the row to be swapped with the first row
 */
void Matrix::swapRows(int first_row, int second_row) {
    std::vector<double> temp = matrix[first_row];
    matrix[first_row] = matrix[second_row];
    matrix[second_row] = temp;
}

/**
 * @brief ERO for swapping rows. swaps the two specified row
 * 
 * @param row the index of the row to be scalar multiplied
 * @param scalar the number to multiply the row by
 */
void Matrix::scalarMulitplyRow(int row, double scalar) {
    for (int i = 0; i < matrix[0].size(); i++) {
        matrix[row][i] *= scalar;
        if (std::abs(matrix[row][i]) < 0.0001) matrix[row][i] = 0;
    }
}

/**
 * @brief ERO for swapping rows. swaps the two specified row
 * 
 * @param row the index of the row to be scalar multiplied
 * @param scalar the number to multiply the row by
 */
void Matrix::AddScalarMulitpleOfOtherRow(int current_row, int other_row, double multiple) {
    for (int i = 0; i < matrix[0].size(); i++) {
        matrix[current_row][i] += matrix[other_row][i] * multiple;
        if (std::abs(matrix[current_row][i]) < 0.0001) matrix[current_row][i] = 0;
    }
}

/**
 * @brief reduces the current matrix to row-reduced echelon form
 * 
 */
void Matrix::reduceToRREF() {
    int max;
    int max_index;
    int temp;
    double multiple;
    int pivot_row = 0;   //initialize to top row
    int pivot_col = 0;   //initialize to leftmost col

    //Reduce to REF
    while (pivot_row < matrix.size() && pivot_col < matrix[0].size()) {
        // Find leftmost non-zero column
        max = 0;
        // Get highest absolute value in pivot_col under pivot_row
        for (int i = pivot_row; i < matrix.size(); i++) {
            if (abs(matrix[i][pivot_col]) > max) {
                max = abs(matrix[i][pivot_col]);
                max_index = i;
            }
        }
        if (max == 0)    // Column entries under pivot_row are all zero. Go to next Col
            pivot_col++;
        else {
            // Put the row with highest value in current pivot_col to top (of unreduced rows) by swapping
            swapRows(pivot_row, max_index);
            // Make entries in pivot_col below pivot_row = 0 by subtracting appropratiate multiple of pivot_row
            for (int i = pivot_row + 1; i < matrix.size(); i++) {
                multiple = -(matrix[i][pivot_col] / matrix[pivot_row][pivot_col]);
                AddScalarMulitpleOfOtherRow(i, pivot_row, multiple);
            }
            pivot_row++;
            pivot_col++;
        }
    }

    // Reduce to RREF
    double leading_entry;
    int leading_indeces[matrix.size()];
    // Initialize leading indeces to -1 to represent no leading enttry in the row (found yet)
    for (int i = 0; i < matrix.size(); i++) leading_indeces[i] = -1;

    // Multiply rows such that all leading entries are 1
    for (int i = 0; i < matrix.size(); i++) {
        leading_entry = 0;
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] != 0) {
                leading_entry = matrix[i][j];
                leading_indeces[i] = j;
                break;
            }
        }
        if (leading_entry != 0)
            scalarMulitplyRow(i, 1 / leading_entry);
    }

    pivot_row = matrix.size() - 1;   //initialize to bottom row
    pivot_col = matrix[0].size() - 1;   //initialize to rightmost col
    // Make entries in pivot_col above pivot_row 0 by subtracting appropratiate multiple of pivot_row
    while (pivot_row > 0 && pivot_col > 0) {
        // Find rightmost column contatining leading 1
        if (leading_indeces[pivot_row] == -1) //0 row
            pivot_row--;
        else {
            pivot_col = leading_indeces[pivot_row];
            for (int i = 0; i < pivot_row; i++) {
                multiple = -(matrix[i][pivot_col]);
                AddScalarMulitpleOfOtherRow(i, pivot_row, multiple);
            }
            pivot_row--;
            pivot_col--;
        }
    }

    // Fix -0's
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            if (matrix[i][j] == -0)
                matrix[i][j] = 0;
        }
    }
}

/**
 * @brief returns the values of the matrix 
 * @return true if this matrix is square; false otherwise
 */
bool Matrix::isSquare() {
    return (matrix.size() == matrix[0].size());
}

/**
 * @brief returns the values of the matrix 
 * @return values of the matrix
 */
std::vector<std::vector<double>> Matrix::getValues() {
    return matrix;
}
