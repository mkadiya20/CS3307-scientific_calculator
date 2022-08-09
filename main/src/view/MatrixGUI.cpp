/**
 * @file MatrixGUI.cpp
 * @author Nieve Wong
 * @brief This class represents the "matrices" tab of the main GUI.
 * @version 1.0
 */

#include "../../include/view/MatrixGUI.h"
#include "../../include/model/utilities/Utilities.h"

/**
 * @brief Construct a new MatrixGUI object.
 * 
 * Calls QWidget constructor and initializes all data members.
 * 
 * @param parent Allows for parent-child relationships with matrix.
 */
MatrixGUI::MatrixGUI(QWidget *parent)
        : QWidget(parent) {

    //make input labels and buttons 
    QLabel *outputLabel = new QLabel("Output:");
    QLabel *inputLabel = new QLabel("Input:");

    //warning label for matrix size
    warningLabel = new QLabel("*WARNING* Maximum size of matrix = 4 \303\227 4");
    warningLabel->setVisible(false);

    //matrix size input labels
    QLabel *firstSizeLabel = new QLabel("Matrix 1 size: ");
    QLabel *secondSizeLabel = new QLabel("Matrix 2 size: ");
    QLabel *firstX = new QLabel("\303\227");
    QLabel *secondX = new QLabel("\303\227");

    //input size line edits for matrix 1 and 2
    firstSizeBox = new QLineEdit;
    secondSizeBox = new QLineEdit;
    thirdSizeBox = new QLineEdit;
    fourthSizeBox = new QLineEdit;

    //configuring size line edits for matrix 1 and 2
    firstSizeBox->setMaximumHeight(25);
    firstSizeBox->setMaximumWidth(15);
    secondSizeBox->setMaximumHeight(25);
    secondSizeBox->setMaximumWidth(15);
    thirdSizeBox->setMaximumHeight(25);
    thirdSizeBox->setMaximumWidth(15);
    fourthSizeBox->setMaximumHeight(25);
    fourthSizeBox->setMaximumWidth(15);

    //set button to trigger visibility of input matrix
    setButton = new QPushButton("Set");
    connect(setButton, &QPushButton::clicked, this, &MatrixGUI::setClicked);

    //size input layout and box for matrix 1 and 2
    QGroupBox *inputBox = new QGroupBox();
    QHBoxLayout *inputLayout = new QHBoxLayout();

    inputLayout->addWidget(firstSizeLabel, 0, Qt::AlignRight);
    inputLayout->addWidget(firstSizeBox, 0, Qt::AlignRight);
    inputLayout->addWidget(firstX, 0, Qt::AlignRight);
    inputLayout->addWidget(secondSizeBox, 0, Qt::AlignRight);
    inputLayout->addStretch();
    inputLayout->addWidget(secondSizeLabel);
    inputLayout->addWidget(thirdSizeBox, 0, Qt::AlignRight);
    inputLayout->addWidget(secondX, 0, Qt::AlignRight);
    inputLayout->addWidget(fourthSizeBox, 0, Qt::AlignRight);
    inputLayout->addStretch();
    inputLayout->addWidget(setButton, 0, Qt::AlignLeft);

    inputBox->setLayout(inputLayout);

    //operation boxes for matrix 1 and 2
    QGroupBox *operationsBox = new QGroupBox();

    firstOperationsBox = new QGroupBox();
    firstOperationsBox->setVisible(false);
    QGroupBox *scalarBox1 = new QGroupBox();
    QGridLayout *scalarLayout1 = new QGridLayout();

    secondOperationsBox = new QGroupBox();
    secondOperationsBox->setVisible(false);
    QGroupBox *scalarBox2 = new QGroupBox();
    QGridLayout *scalarLayout2 = new QGridLayout();

    QHBoxLayout *operationsLayout = new QHBoxLayout();
    QVBoxLayout *firstOperationsL = new QVBoxLayout();
    QVBoxLayout *secondOperationsL = new QVBoxLayout();

    //operation box labels for matrix 1 and 2
    QLabel *firstMatrixL = new QLabel("Matrix 1 Operations");
    QLabel *secondMatrixL = new QLabel("Matrix 2 Operations");
    QLabel *firstScalarML = new QLabel("Scalar Multiply:");
    QLabel *secondScalarML = new QLabel("Scalar Multiply:");

    //operation box buttons for matrix 1 and 2
    inverse1 = new QPushButton("Inverse");
    inverse2 = new QPushButton("Inverse");
    determinant1 = new QPushButton("Determinant");
    determinant2 = new QPushButton("Determinant");
    transpose1 = new QPushButton("Transpose");
    transpose2 = new QPushButton("Transpose");
    clear1 = new QPushButton("clear");
    clear2 = new QPushButton("clear");
    addition = new QPushButton("Addition");
    addition->setVisible(false);
    subtraction = new QPushButton("Subtraction");
    subtraction->setVisible(false);
    multiplication = new QPushButton("Multiplication");
    multiplication->setVisible(false);

    //creating and setting layout for scalar multiply digit buttons in operation boxes
    for (int i = 0; i <= 9; i++) {
        QString s = QString::number(i);
        digitButtons1[i] = new QPushButton(s);
        digitButtons2[i] = new QPushButton(s);
        connect(digitButtons1[i], &QPushButton::clicked, this, &MatrixGUI::firstDigitClicked);
        connect(digitButtons2[i], &QPushButton::clicked, this, &MatrixGUI::secondDigitClicked);
    }

    int j = 0;
    for (int i = 0; i < 2; i++) {
        for (int x = 0; x < 5; x++) {
            scalarLayout1->addWidget(digitButtons1[j], i, x);
            scalarLayout2->addWidget(digitButtons2[j], i, x);
            j++;
        }
    }
    //connecting operation buttons to respective slots
    connect(inverse1, &QPushButton::clicked, this, &MatrixGUI::operationClicked);
    connect(inverse2, &QPushButton::clicked, this, &MatrixGUI::operationClicked);
    connect(determinant1, &QPushButton::clicked, this, &MatrixGUI::operationClicked);
    connect(determinant2, &QPushButton::clicked, this, &MatrixGUI::operationClicked);
    connect(transpose1, &QPushButton::clicked, this, &MatrixGUI::operationClicked);
    connect(transpose2, &QPushButton::clicked, this, &MatrixGUI::operationClicked);
    connect(clear1, &QPushButton::clicked, this, &MatrixGUI::clearClicked);
    connect(clear2, &QPushButton::clicked, this, &MatrixGUI::clearClicked);
    connect(addition, &QPushButton::clicked, this, &MatrixGUI::operationClicked);
    connect(subtraction, &QPushButton::clicked, this, &MatrixGUI::operationClicked);
    connect(multiplication, &QPushButton::clicked, this, &MatrixGUI::operationClicked);

    //adding all operation widgets to operation layouts
    firstOperationsL->addWidget(firstMatrixL);
    secondOperationsL->addWidget(secondMatrixL);

    firstOperationsL->addWidget(inverse1);
    firstOperationsL->addWidget(transpose1);
    firstOperationsL->addWidget(determinant1);
    firstOperationsL->addWidget(firstScalarML);
    firstOperationsL->addWidget(scalarBox1);
    firstOperationsL->addWidget(clear1);
    operationsLayout->addWidget(firstOperationsBox);

    operationsLayout->addWidget(addition);
    operationsLayout->addWidget(subtraction);
    operationsLayout->addWidget(multiplication);

    secondOperationsL->addWidget(inverse2);
    secondOperationsL->addWidget(transpose2);
    secondOperationsL->addWidget(determinant2);
    secondOperationsL->addWidget(secondScalarML);
    secondOperationsL->addWidget(scalarBox2);
    secondOperationsL->addWidget(clear2);
    operationsLayout->addWidget(secondOperationsBox);

    //setting layout in operation boxes for matrix 1 and 2
    firstOperationsBox->setLayout(firstOperationsL);
    secondOperationsBox->setLayout(secondOperationsL);
    operationsBox->setLayout(operationsLayout);
    scalarBox1->setLayout(scalarLayout1);
    scalarBox2->setLayout(scalarLayout2);

    //matrix output box and layout
    QGroupBox *outputMatrixBox = new QGroupBox;
    QGridLayout *outputMatrixLayout = new QGridLayout;

    //matrix input boxes for matrix 1 and 2 
    QGroupBox *firstMatrixBox = new QGroupBox();
    firstMatrixLayout = new QGridLayout();
    QGroupBox *secondMatrixBox = new QGroupBox();
    secondMatrixLayout = new QGridLayout();

    //configuring all matrices line edits for input and output
    for (int i = 0; i < 16; i++) {
        firstMatrix[i] = new QLineEdit();
        firstMatrix[i]->setMaximumHeight(25);
        firstMatrix[i]->setMaximumWidth(25);
        firstMatrix[i]->setVisible(false);
        secondMatrix[i] = new QLineEdit();
        secondMatrix[i]->setMaximumHeight(25);
        secondMatrix[i]->setMaximumWidth(25);
        secondMatrix[i]->setVisible(false);
        outputMatrix[i] = new QLineEdit();
        outputMatrix[i]->setMaximumHeight(25);
        outputMatrix[i]->setMaximumWidth(25);
        outputMatrix[i]->setVisible(false);
        outputMatrix[i]->setReadOnly(true);
    }
    //adding input and output widgets to matrices layout
    int z = 0;
    for (int i = 0; i < 4; i++) {
        for (int x = 0; x < 4; x++) {
            firstMatrixLayout->addWidget(firstMatrix[z], i, x);
            secondMatrixLayout->addWidget(secondMatrix[z], i, x);
            outputMatrixLayout->addWidget(outputMatrix[z], i, x);
            z++;
        }
    }
    //setting layout of input and output matrices
    firstMatrixBox->setLayout(firstMatrixLayout);
    secondMatrixBox->setLayout(secondMatrixLayout);
    outputMatrixBox->setLayout(outputMatrixLayout);

    //matrices input box widgets
    QGroupBox *gridsBox = new QGroupBox();
    QHBoxLayout *gridsLayout = new QHBoxLayout();

    firstOpInput = new QLineEdit;
    secondOpInput = new QLineEdit;
    thirdOpInput = new QLineEdit;
    firstOpInput->setReadOnly(true);
    secondOpInput->setReadOnly(true);
    thirdOpInput->setReadOnly(true);
    firstOpInput->setMaximumHeight(25);
    firstOpInput->setMaximumWidth(25);
    secondOpInput->setMaximumHeight(20);
    secondOpInput->setMaximumWidth(20);
    thirdOpInput->setMaximumHeight(25);
    thirdOpInput->setMaximumWidth(25);

    //adding input box widgets to input layout
    gridsLayout->addWidget(firstOpInput);
    gridsLayout->addWidget(firstMatrixBox);
    gridsLayout->addWidget(secondOpInput);
    gridsLayout->addWidget(thirdOpInput);
    gridsLayout->addWidget(secondMatrixBox);
    gridsBox->setLayout(gridsLayout);

    //solve Button
    solveButton = new QPushButton("Solve");
    connect(solveButton, &QPushButton::clicked, this, &MatrixGUI::solveClicked);

    //make main layout and add widgets to main layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(inputBox);
    mainLayout->addWidget(warningLabel);
    mainLayout->addWidget(operationsBox);
    mainLayout->addWidget(inputLabel);
    mainLayout->addWidget(gridsBox);
    mainLayout->addWidget(solveButton);
    mainLayout->addWidget(outputLabel);
    mainLayout->addWidget(outputMatrixBox);

    //set layout of main matrix tab
    setLayout(mainLayout);
}

/**
 * @brief sets the size of matrix 1 and 2.
 * 
 * Called when "Set" Button is clicked.
 */
void MatrixGUI::setClicked() {
    //default warming label, input matrices, and operation associated boxes to invisible
    warningLabel->setVisible(false);
    firstOperationsBox->setVisible(false);
    secondOperationsBox->setVisible(false);
    addition->setVisible(false);
    subtraction->setVisible(false);
    multiplication->setVisible(false);

    for (int i = 0; i < 16; i++) {
        firstMatrix[i]->setVisible(false);
        secondMatrix[i]->setVisible(false);
    }
    //gather matrix input size info
    int firstRows = firstSizeBox->text().toInt();
    int firstColumns = secondSizeBox->text().toInt();
    int secondRows = thirdSizeBox->text().toInt();
    int secondColumns = fourthSizeBox->text().toInt();

    //make the input matrices visible based on the user inputted sizes
    //make the appropriate operations visible
    if (firstRows <= 4 && firstColumns <= 4 && secondRows <= 4 &&
        secondColumns <= 4) { //ensures inputted size is not too large

        for (int i = 0; i < firstRows; i++) {
            for (int x = 0; x < firstColumns; x++) {
                QWidget *temp = firstMatrixLayout->itemAtPosition(i, x)->widget();
                temp->setVisible(true);
            }
        }
        for (int i = 0; i < secondRows; i++) {
            for (int x = 0; x < secondColumns; x++) {
                QWidget *temp = secondMatrixLayout->itemAtPosition(i, x)->widget();
                temp->setVisible(true);
            }
        }
        if (firstRows > 0 && firstColumns > 0) {
            firstOperationsBox->setVisible(true);
        }
        if (secondRows > 0 && secondColumns > 0) {
            secondOperationsBox->setVisible(true);
        }
        if (firstRows > 0 && firstColumns > 0 && secondRows > 0 && secondColumns > 0) {
            addition->setVisible(true);
            subtraction->setVisible(true);
            multiplication->setVisible(true);
        }

    } else {
        warningLabel->setVisible(true); //warning displayed if matrix size is too large 
    }
}

/**
 * @brief Adds clicked operator character to operator text boxes. 
 * 
 * Called when an operator Button is clicked.
 */
void MatrixGUI::operationClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());

    if (clickedButton == inverse1) {
        firstOpInput->setText("I");
    } else if (clickedButton == inverse2) {
        thirdOpInput->setText("I");
    } else if (clickedButton == determinant1) {
        firstOpInput->setText("D");
    } else if (clickedButton == determinant2) {
        thirdOpInput->setText("D");
    } else if (clickedButton == transpose1) {
        firstOpInput->setText("T");
    } else if (clickedButton == transpose2) {
        thirdOpInput->setText("T");
    } else if (clickedButton == addition) {
        secondOpInput->setText("+");
    } else if (clickedButton == multiplication) {
        secondOpInput->setText("*");
    } else if (clickedButton == subtraction) {
        secondOpInput->setText("-");
    }
}

/**
 * @brief Adds digit to operator box of matrix 1. 
 * 
 * Called when a digit is clicked in first matrix operator box.
 */
void MatrixGUI::firstDigitClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString buttonText = clickedButton->text();
    std::string inputText = firstOpInput->text().toStdString();
    if (inputText == "I" | inputText == "D" | inputText == "T" | inputText == "0") {
        firstOpInput->setText(buttonText);
    } else {
        firstOpInput->setText(firstOpInput->text() + buttonText);
    }
}

/**
 * @brief Adds digit to operator box of matrix 2. 
 * 
 * Called when a digit is clicked in second matrix operator box.
 */
void MatrixGUI::secondDigitClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    QString buttonText = clickedButton->text();
    std::string inputText = thirdOpInput->text().toStdString();
    if (inputText == "I" | inputText == "D" | inputText == "T" | inputText == "0") {
        thirdOpInput->setText(buttonText);
    } else {
        thirdOpInput->setText(thirdOpInput->text() + buttonText);
    }
}

/**
 * @brief Clears the corresponding matrix input. 
 * 
 * Called when the "Clear" Button is clicked in matrix 1 or matrix 2 operator box.
 */
void MatrixGUI::clearClicked() {
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (clickedButton == clear1) {
        firstOpInput->clear();
    } else if (clickedButton == clear2) {
        thirdOpInput->clear();
    }
}

/**
 * @brief Triggers the solving of user's matrix problem. 
 * 
 * Called when "Solve" Button on the matrix GUI is clicked.
 */
void MatrixGUI::solveClicked() {
    //get sizing of input matrices
    int rows1 = firstSizeBox->text().toInt();
    int columns1 = secondSizeBox->text().toInt();
    int rows2 = thirdSizeBox->text().toInt();
    int columns2 = fourthSizeBox->text().toInt();

    //make double vectors for matrix 1 and 2 input
    std::vector<std::vector<double>> matrix1;
    matrix1.resize(rows1, std::vector<double>(columns1));
    std::vector<std::vector<double>> matrix2;
    matrix2.resize(rows1, std::vector<double>(columns2));

    //gather matrix 1 input
    int q = 0;
    for (int i = 0; i < rows1; i++) {
        for (int x = 0; x < columns1; x++) {
            QString temp = firstMatrix[q]->text();
            double input1 = temp.toDouble();
            matrix1[i][x] = input1;
            q++;
        }
        q = q + (4 - columns1);
    }
    //gather matrix 2 input
    int r = 0;
    for (int i = 0; i < rows2; i++) {
        for (int x = 0; x < columns2; x++) {
            QString temp = secondMatrix[r]->text();
            double input2 = temp.toDouble();
            matrix2[i][x] = input2;
            r++;
        }
        r = r + (4 - columns2);
    }

    //gather the operations the user wants performed
    char operations[3];
    int scalar1 = 1, scalar2 = 1;
    std::string firstOp = firstOpInput->text().toStdString();
    std::string thirdOp = thirdOpInput->text().toStdString();
    if (firstOp.length() == 0)
        operations[0] = '0';
    else if (firstOp[0] == 'D')
        operations[0] = 'D';
    else if (firstOp[0] == 'I')
        operations[0] = 'I';
    else if (firstOp[0] == 'T')
        operations[0] = 'T';
    else {
        operations[0] = '0';
        scalar1 = firstOpInput->text().toDouble();
    }

    if (thirdOp.length() == 0)
        operations[2] = '0';
    else if (thirdOp[0] == 'D')
        operations[2] = 'D';
    else if (thirdOp[0] == 'I')
        operations[2] = 'I';
    else if (thirdOp[0] == 'T')
        operations[2] = 'T';
    else {
        operations[2] = '0';
        scalar2 = thirdOpInput->text().toDouble();
    }

    operations[1] = secondOpInput->text().toStdString()[0];

    //try-catch for error handling
    try {
        //get solution to output
        std::vector<std::vector<double>> result = ButtonResponder::solveMatrixButtonResponse(
                matrix1, matrix2, operations, scalar1, scalar2);

        // create a vector of strings of same size
        std::vector<std::vector<std::string>> stringResult(
                result.size(), std::vector<std::string>(result[0].size()));

        //remove trailing zeros from solution output
        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[0].size(); j++) {
                stringResult[i][j] = Utilities::removeTrailingZeros(result[i][j]);
            }
        }
        //setting output in output matrix
        int index = 0;
        for (int i = 0; i < result.size(); i++) {
            for (int j = 0; j < result[0].size(); j++) {
                outputMatrix[index]->setText(QString::fromStdString(stringResult[i][j]));
                outputMatrix[index]->setVisible(true);
                index++;
            }
            index += (4 - (int) result[0].size());
        }
    } catch (std::exception &e) {
        //pop-up error message
        auto *error = new QErrorMessage();
        error->showMessage(QString::fromStdString(e.what()));
    }
}