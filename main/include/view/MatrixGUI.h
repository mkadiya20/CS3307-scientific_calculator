/**
 * @file MatrixGUI.cpp
 * @author Nieve Wong
 * @brief This class represents the "matrices" tab of the main GUI.
 * @version 1.0
 */

#ifndef MATRIXGUI_H
#define MATRIXGUI_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QGridLayout>
#include <QLayoutItem>
#include <QVBoxLayout>
#include <QErrorMessage>
#include <string>
#include "../../include/controller/ButtonResponder.h"

class MatrixGUI : public QWidget {
Q_OBJECT

public:
    MatrixGUI(QWidget *parent = nullptr);

    ~MatrixGUI() = default;

private slots:

    void setClicked();

    void operationClicked();

    void firstDigitClicked();

    void secondDigitClicked();

    void clearClicked();

    void solveClicked();

private:

    QLabel *warningLabel;

    QPushButton *solveButton;
    QPushButton *setButton;
    QPushButton *inverse1;
    QPushButton *inverse2;
    QPushButton *transpose1;
    QPushButton *transpose2;
    QPushButton *determinant1;
    QPushButton *determinant2;
    QPushButton *addition;
    QPushButton *subtraction;
    QPushButton *multiplication;
    QPushButton *digitButtons1[10];
    QPushButton *digitButtons2[10];
    QPushButton *clear1;
    QPushButton *clear2;

    QGridLayout *firstMatrixLayout;
    QGridLayout *secondMatrixLayout;
    QGridLayout *outputMatrixLayout;

    QGroupBox *firstOperationsBox;
    QGroupBox *secondOperationsBox;

    QLineEdit *firstSizeBox;
    QLineEdit *secondSizeBox;
    QLineEdit *thirdSizeBox;
    QLineEdit *fourthSizeBox;

    QLineEdit *firstOpInput;
    QLineEdit *secondOpInput;
    QLineEdit *thirdOpInput;

    QLineEdit *firstMatrix[16];
    QLineEdit *secondMatrix[16];
    QLineEdit *outputMatrix[16];

};

#endif // Matrix_H

