/**
 * @file SetsGUI.cpp
 * @author Nieve Wong
 * @brief This class represents the "sets" tab of the main window GUI.
 * 
 * Provides an interface for users to input set problems 
 * and to display the corresponding solution + steps
 * 
 * @version 1.0
 */

#include "../../include/view/SetsGUI.h"

/**
 * @brief Construct a new SetsGUI object.
 * 
 * Calls QWidget constructor and initializes all data members
 * 
 * @param parent Parent widget. Allows for parent-child relationships with set.
 */
SetsGUI::SetsGUI(QWidget *parent) : QWidget(parent) {
    //make labels for input, output, and brackets
    auto *inputLabel = new QLabel("Input:");
    auto *outputLabel = new QLabel("Output:");
    auto *leftBracketO = new QLabel(R"({)");
    auto *rightBracketO = new QLabel(R"(})");
    auto *leftBracketT = new QLabel(R"({)");
    auto *rightBracketT = new QLabel(R"(})");

    //make input Button box, its horizontal layout, and operation buttons
    auto *buttonBox = new QGroupBox();
    auto *buttonLayout = new QHBoxLayout;
    unionButton = new QPushButton("\342\210\252");
    connect(unionButton, &QPushButton::clicked, this, &SetsGUI::operatorClicked);
    intersectButton = new QPushButton("\342\210\251");
    connect(intersectButton, &QPushButton::clicked, this, &SetsGUI::operatorClicked);
    minusButton = new QPushButton("-");
    connect(minusButton, &QPushButton::clicked, this, &SetsGUI::operatorClicked);

    //add operation buttons to Button layout
    buttonLayout->addWidget(unionButton);
    buttonLayout->addWidget(intersectButton);
    buttonLayout->addWidget(minusButton);

    //set Button box to the horizontal layout
    buttonBox->setLayout(buttonLayout);

    //make input digit Button box and its horizontal layout
    auto *digitBox = new QGroupBox();
    auto *digitLayout = new QHBoxLayout;

    //create digit, and comma buttons and add them to digit layout 
    for (int i = 0; i < 10; ++i) {
        digitButtons[i] = new QPushButton(tr("%1").arg(i));
        connect(digitButtons[i], &QPushButton::clicked, this, &SetsGUI::digitClicked);
        digitLayout->addWidget(digitButtons[i]);
    }
    commaButton = new QPushButton(",");
    pointButton = new QPushButton(".");
    connect(commaButton, &QPushButton::clicked, this, &SetsGUI::digitClicked);
    connect(pointButton, &QPushButton::clicked, this, &SetsGUI::digitClicked);
    digitLayout->addWidget(pointButton);
    digitLayout->addWidget(commaButton);

    //set digit box to its horizontal layout
    digitBox->setLayout(digitLayout);

    //make input box, its horizontal layout, and add input lines
    auto *inputBox = new QGroupBox();
    auto *inputLayout = new QHBoxLayout;
    firstSet = new QLineEdit;
    secondSet = new QLineEdit;
    operators = new QLineEdit;
    firstSet->setReadOnly(true);
    secondSet->setReadOnly(true);
    operators->setReadOnly(true);

    firstSet->setMaximumHeight(40);
    secondSet->setMaximumHeight(40);
    operators->setMaximumHeight(30);
    operators->setMaximumWidth(15);

    //add input widgets to input layout
    inputLayout->addWidget(leftBracketO);
    inputLayout->addWidget(firstSet);
    inputLayout->addWidget(rightBracketO);
    inputLayout->addWidget(operators);
    inputLayout->addWidget(leftBracketT);
    inputLayout->addWidget(secondSet);
    inputLayout->addWidget(rightBracketT);

    //set the input box to its horizontal layout
    inputBox->setLayout(inputLayout);

    //make output box and buttons to trigger solving, clearing set input and changing between sets input
    outputBox = new QLineEdit;
    outputBox->setReadOnly(true);
    outputBox->setMinimumHeight(60);
    //make solve Button 
    solveButton = new QPushButton("Solve");
    connect(solveButton, &QPushButton::clicked, this, &SetsGUI::solveClicked);
    //make change set Button and clear set Button
    clearSetButton = new QPushButton("Clear Set");
    connect(clearSetButton, &QPushButton::clicked, this, &SetsGUI::clearSetClicked);
    changeSetButton = new QPushButton("Change Set");
    connect(changeSetButton, &QPushButton::clicked, this, &SetsGUI::changeSetClicked);
    isFirstSet = true; //default to first set input box 

    //make main vertical layout and add widgets to the layout
    auto *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(buttonBox);
    mainLayout->addWidget(digitBox);
    mainLayout->addWidget(changeSetButton);
    mainLayout->addWidget(clearSetButton);
    mainLayout->addWidget(inputLabel);
    mainLayout->addWidget(inputBox);
    mainLayout->addWidget(solveButton);
    mainLayout->addWidget(outputLabel);
    mainLayout->addWidget(outputBox);
    //set main set tab to the main layout
    setLayout(mainLayout);
}

/**
 * @brief Adds operator character to operator text box. 
 * 
 * Called when an operator on the set GUI is clicked.
 * 
 */
void SetsGUI::operatorClicked() {
    auto *clickedButton = qobject_cast<QPushButton *>(sender());
    QString clickedOperator = clickedButton->text();
    operators->setText(clickedOperator);
}

/**
 * @brief Appends Button character to proper set text box.
 * 
 * Called when a digit or comma on the set GUI is clicked.
 */
void SetsGUI::digitClicked() {
    auto *clickedButton = qobject_cast<QPushButton *>(sender());
    QString clickedDigit = clickedButton->text();

    if (isFirstSet) {
        firstSet->setText(firstSet->text() + clickedDigit);
    } else if (!isFirstSet) {
        secondSet->setText(secondSet->text() + clickedDigit);
    }

}

/**
 * @brief changes which set input text is sent to. 
 * 
 * Called when "Change Set" on the set GUI is clicked.
 * changes the boolean value of isFirstSet to indicate if Button text should append to first or second set text box.
*/
void SetsGUI::changeSetClicked() {
    if (isFirstSet) {
        isFirstSet = false;
    } else if (!isFirstSet) {
        isFirstSet = true;
    }
}

/**
 * @brief Clear the text of appropriate set box.
 * 
 * Called when "Clear" Button on the set GUI is clicked.
 * Clear the set text depending or boolean value of isFirstSet
 */
void SetsGUI::clearSetClicked() {
    if (isFirstSet) {
        firstSet->clear();
    } else if (!isFirstSet) {
        secondSet->clear();
    }
}

/**
 * @brief Triggers the solving of the set problem. 
 * 
 * Called when "Solve" Button on the set GUI is clicked.
 */
void SetsGUI::solveClicked() {
    // get the strings from text boxes
    std::string set1 = firstSet->text().toStdString();
    std::string set2 = secondSet->text().toStdString();
    std::string op = operators->text().toStdString();

    try {
        // check if an operator was selected
        if (op.empty()) {
            throw std::runtime_error("Operator not selected");
        }

        // convert the string into vectors of double
        std::vector<double> set_1 = SetsGUI::getSetValues(set1);
        std::vector<double> set_2 = SetsGUI::getSetValues(set2);


        // pass the sets in the Button responder
        std::string result = ButtonResponder::solveSetButtonResponse(set_1, set_2, op);


        result = "{" + result + "}";

        // set the result
        outputBox->setText(QString::fromStdString(result));
    } catch (std::exception &e) {
        auto *error = new QErrorMessage();
        error->showMessage(QString::fromStdString(e.what()));
    }
}


/**
 * extracts the numbers from a comma-seperated string
 * using an in-place algorithm
 * @param set the string
 * @return a vector of type double
 */
std::vector<double> SetsGUI::getSetValues(std::string set) {
    std::vector<double> v;
    std::string delimiter = ",";
    size_t pos;
    std::string token;

    while ((pos = set.find(delimiter)) != std::string::npos) {
        token = set.substr(0, pos);
        v.push_back(std::stod(token, nullptr));
        set.erase(0, pos + delimiter.length());
    }
    // last value is inserted here
    v.push_back(std::stod(set, nullptr));

    return v;
}
