#ifndef MATRIX_H
#define MATRIX_H

#include <stdexcept>
#include <vector>
#include <cmath> 

class Matrix{ 
    public:
        Matrix(std::vector<std::vector<double>> input);
        ~Matrix() = default;
        Matrix operator+(const Matrix& other);
        Matrix operator-(const Matrix& other);
        Matrix operator*(const Matrix& other);

        Matrix transpose();
        Matrix scalarMulitply(double scaler);

        double cofactor(int row, int col);
        double determinant();
        Matrix inverse();

        void swapRows(int first_row, int second_row);
        void scalarMulitplyRow(int row, double scalar);
        void AddScalarMulitpleOfOtherRow(int current_row, int row_to_add_from, double multiple);
        void reduceToRREF();

        bool isSquare();
        std::vector<std::vector<double>> getValues();

    private:
        std::vector<std::vector<double>> matrix;
};


#endif //MATRIX_H