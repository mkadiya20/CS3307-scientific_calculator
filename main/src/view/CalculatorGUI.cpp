/**
 * @brief This class represents the "expressions" tab of the main GUI.
 *
 * @details Provides an interface for users to input mathematical problems and
 * to display the corresponding solution + steps.
 *
 * @author Nieve Wong
 * @version 1.0
 */

#include "../../include/view/Button.h"
#include "../../include/view/CalculatorGUI.h"


/**
 * @brief Construct a new CalculatorGUI object.
 *
 * Calls QWidget constructor and initializes all data members.
 * 
 * @param parent allows for parent-child relationships with calculator 
 */
CalculatorGUI::CalculatorGUI(QWidget *parent)
        : QWidget(parent) {
    //Create boxes for input and output
    for (int i = 0; i < 50; i++) {
        display[i] = new QLineEdit();
        display[i]->setVisible(false);
        display[i]->setAlignment(Qt::AlignRight);
        display[i]->setMaxLength(50);
        display[i]->installEventFilter(this);
    }
    display[0]->setVisible(true);
    stepsDisplay = new StepsGUI();
    numLines = 1; //set num lines to deafult 1
    currLine = display[0]; //currLine points to the line the user has clicked

    //create digit buttons for input
    for (int i = 0; i < 10; ++i)
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));

    //create non-digit buttons for input
    toggleButton = new QPushButton("Alphabet");
    connect(toggleButton, &QPushButton::clicked, this, &CalculatorGUI::toggleClicked);
    clearButton = new QPushButton("Clear");
    connect(clearButton, &QPushButton::clicked, this, &CalculatorGUI::clear);
    solveButton = new QPushButton("Solve");
    connect(solveButton, &QPushButton::clicked, this, &CalculatorGUI::solveClicked);
    addLineButton = createButton(tr("Add Line"), SLOT(addLineClicked()));
    removeLineButton = createButton(tr("Remove Line"), SLOT(removeLineClicked()));
    pointButton = createButton(tr("."), SLOT(operatorClicked()));
    equalButton = createButton(tr("="), SLOT(operatorClicked()));
    divisionButton = createButton(tr("\303\267"), SLOT(operatorClicked()));
    timesButton = createButton(tr("\303\227"), SLOT(operatorClicked()));
    minusButton = createButton(tr("-"), SLOT(operatorClicked()));
    plusButton = createButton(tr("+"), SLOT(operatorClicked()));
    squareRootButton = createButton(tr("Sqrt"), SLOT(operatorClicked()));
    powerButton = createButton(tr("^"), SLOT(operatorClicked()));
    leftBracket = createButton(tr("("), SLOT(operatorClicked()));
    rightBracket = createButton(tr(")"), SLOT(operatorClicked()));
    sinButton = createButton(tr("sin"), SLOT(operatorClicked()));
    cosButton = createButton(tr("cos"), SLOT(operatorClicked()));
    tanButton = createButton(tr("tan"), SLOT(operatorClicked()));
    logButton = createButton(tr("log"), SLOT(operatorClicked()));
    eulerButton = createButton(tr("e"), SLOT(operatorClicked()));
    piButton = createButton(tr("\317\200"), SLOT(operatorClicked()));
    exclamButton = createButton(tr("!"), SLOT(operatorClicked()));

    //main layout, widgets stacked vertically
    QVBoxLayout *mainLayout = new QVBoxLayout;

    //Grid layout and box for input buttons
    QGroupBox *buttonsBox = new QGroupBox;
    QGridLayout *buttonsLayout = new QGridLayout();

    //add toggle, solve, and clear buttons to first line of buttons layout
    buttonsLayout->setSizeConstraint(QLayout::SetNoConstraint);
    buttonsLayout->addWidget(clearButton, 1, 0, 1, 2);
    buttonsLayout->addWidget(toggleButton, 1, 2, 1, 2);
    buttonsLayout->addWidget(solveButton, 1, 4, 1, 2);

    //add digit buttons to buttons layout
    buttonsLayout->addWidget(digitButtons[0], 2, 0);
    buttonsLayout->addWidget(digitButtons[1], 2, 1);
    buttonsLayout->addWidget(digitButtons[2], 2, 2);
    buttonsLayout->addWidget(digitButtons[3], 3, 0);
    buttonsLayout->addWidget(digitButtons[4], 3, 1);
    buttonsLayout->addWidget(digitButtons[5], 3, 2);
    buttonsLayout->addWidget(digitButtons[6], 4, 0);
    buttonsLayout->addWidget(digitButtons[7], 4, 1);
    buttonsLayout->addWidget(digitButtons[8], 4, 2);
    buttonsLayout->addWidget(digitButtons[9], 5, 0);

    //add non-digit buttons to buttons layout
    buttonsLayout->addWidget(pointButton, 5, 1);
    buttonsLayout->addWidget(equalButton, 6, 1);
    buttonsLayout->addWidget(divisionButton, 2, 4);
    buttonsLayout->addWidget(timesButton, 3, 4);
    buttonsLayout->addWidget(minusButton, 2, 5);
    buttonsLayout->addWidget(plusButton, 3, 5);
    buttonsLayout->addWidget(squareRootButton, 5, 5);
    buttonsLayout->addWidget(powerButton, 5, 4);
    buttonsLayout->addWidget(leftBracket, 4, 4);
    buttonsLayout->addWidget(rightBracket, 4, 5);
    buttonsLayout->addWidget(sinButton, 2, 3);
    buttonsLayout->addWidget(cosButton, 3, 3);
    buttonsLayout->addWidget(tanButton, 4, 3);
    buttonsLayout->addWidget(logButton, 5, 3);
    buttonsLayout->addWidget(eulerButton, 5, 2);
    buttonsLayout->addWidget(piButton, 6, 0);
    buttonsLayout->addWidget(exclamButton, 6, 2);
    buttonsLayout->addWidget(addLineButton, 6, 3);
    buttonsLayout->addWidget(removeLineButton, 6, 4);

    //set layout style of buttons box to grid layout for buttons
    buttonsBox->setLayout(buttonsLayout);

    //add all input lines to main layout
    for (int i = 0; i < 50; i++) {
        mainLayout->addWidget(display[i]);
    }
    //add box with all buttons and output display to main layout
    mainLayout->addWidget(buttonsBox);
    mainLayout->addWidget(stepsDisplay);
    //set the layout of the main widget to main layout
    setLayout(mainLayout);
}

/**
 * @brief Appends clicked digit to display text.
 *
 * Called when a digit on the calculator GUI is clicked. 
 */
void CalculatorGUI::digitClicked() {
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedDigit = clickedButton->text();

    //If there is no display text and the Button pressed is "0", "0" is not appended.
    if (currLine->text() == "" && clickedDigit == "0")
        return;

    currLine->setText(currLine->text() + clickedDigit);
}

/**
 * @brief Switches Buttons between alphabet and digits.
 *
 * Called when "Alphabet" on the calculator GUI is clicked.
 */
void CalculatorGUI::toggleClicked() {
    if (digitButtons[0]->text() == "0") {
        digitButtons[0]->setText("a");
        digitButtons[1]->setText("b");
        digitButtons[2]->setText("c");
        digitButtons[3]->setText("h");
        digitButtons[4]->setText("i");
        digitButtons[5]->setText("j");
        digitButtons[6]->setText("n");
        digitButtons[7]->setText("o");
        digitButtons[8]->setText("p");
        digitButtons[9]->setText("t");
        pointButton->setText("u");
        divisionButton->setText("f");
        timesButton->setText("l");
        minusButton->setText("g");
        plusButton->setText("m");
        squareRootButton->setText("y");
        powerButton->setText("x");
        leftBracket->setText("r");
        rightBracket->setText("s");
        sinButton->setText("d");
        cosButton->setText("k");
        tanButton->setText("q");
        logButton->setText("w");
        eulerButton->setText("v");
        piButton->setText("z");

    } else {
        for (int i = 0; i < 10; ++i)
            digitButtons[i]->setText(QString::number(i));

        pointButton->setText(".");
        divisionButton->setText("\303\267");
        timesButton->setText("\303\227");
        minusButton->setText("-");
        plusButton->setText("+");
        squareRootButton->setText("sqrt");
        powerButton->setText("^");
        leftBracket->setText("(");
        rightBracket->setText(")");
        sinButton->setText("sin");
        cosButton->setText("cos");
        tanButton->setText("tan");
        logButton->setText("log");
        eulerButton->setText("e");
        piButton->setText("\317\200");
    }
}

/**
 * @brief Appends clicked operator to display text.
 * 
 * Called when an operator or special character on the calculator GUI is clicked.
 */
void CalculatorGUI::operatorClicked() {
    Button *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();

    //if else cases are for transforming input into program-readable form
    if (clickedOperator == "\303\227") {
        currLine->setText(currLine->text() + "*");
    } else if (clickedOperator == "\303\267") {
        currLine->setText(currLine->text() + "/");
    } else if (clickedOperator == "\317\200") {
        currLine->setText(currLine->text() + "3.14");
    } else {
        currLine->setText(currLine->text() + clickedOperator);
    }

}

/**
 * @brief Adds line edit below existing ones.
 * 
 * Called when "Add Line" on calculator GUI is clicked.
 */
void CalculatorGUI::addLineClicked() {
    display[numLines - 1]->setVisible(true);
    numLines++;
}

/**
 * @brief removes the most recently added line edit.
 * 
 * Called when "Remove Line" on calculator GUI is clicked.
 */
void CalculatorGUI::removeLineClicked() {
    if (numLines > 1) {
        display[numLines - 1]->setVisible(false);
        numLines--;
    }

}

/**
 * @brief changes line-to-edit to the clicked input line.
 * 
 * Called when one of the input line edits are clicked. 
 * Updates current line to the line clicked.
 */
void CalculatorGUI::lineClicked() {
    QLineEdit *clickedLine = qobject_cast<QLineEdit *>(sender());
    clickedLine->setVisible(false);
}


/**
 * @brief Clears all display text of the current line.
 * 
 * Called when "clear" on the calculator GUI is clicked.
 */
void CalculatorGUI::clear() {
    currLine->clear();
}


/**
 * @brief Triggers the solving of user's expression.
 * 
 * Called when "Solve" Button on the calculator GUI is clicked.
 */
void CalculatorGUI::solveClicked() {
    //Get input from GUI
    std::vector<std::string> equations;
    int i = 0;
    while (display[i]->text() != "") {
        equations.push_back(display[i]->text().toStdString());
        ++i;
    }

    try {
        if (equations.size() == 1) {
            std::vector<std::string> result = ButtonResponder::solveEquationButtonResponse(equations.at(0));
            result[0] = "Expression: " + equations[0];
            stepsDisplay->updateSteps(result);

        } else {
            std::vector<std::string> v = ButtonResponder::solveSysOfLinearEqnButtonResponse(equations);
            stepsDisplay->updateSteps(v);
        }
    } catch (std::exception &e) {
        // catch any error and throw it again
//        std::cout << "error thrown in calculator GUI" << std::endl;
        auto *error = new QErrorMessage();
        error->showMessage(QString::fromStdString(e.what()));

    }
}

/**
 * @brief reimplementation of eventFilter function.
 * 
 * when a input line is clicked, the current line to send
 * input to is changed to the clicked line.
 * 
 * @param object QObject experiencing the event
 * @param event the event passed by the QObject
 * @return true the event is not handled further
 * @return false continue handing the event 
 */
bool CalculatorGUI::eventFilter(QObject *object, QEvent *event) {
    if (event->type() == QEvent::MouseButtonPress) {
        currLine = qobject_cast<QLineEdit *>(object);
        return true;
    } else {
        return false;
    }
}

/**
 * @brief Creates new Button.
 *
 * Called from CalculatorGUI constructor.
 *
 * @param text The Button text.
 * @param member SLOT - function called in response to Button's clicked() SIGNAL.
 * @return Button* Button to be used in the calculator GUI.
 */
Button *CalculatorGUI::createButton(const QString &text, const char *member) {
    Button *newButton = new Button(text);
    connect(newButton, SIGNAL(clicked()), this, member);
    return newButton;
}

