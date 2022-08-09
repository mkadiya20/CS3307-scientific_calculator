/**
 * @file GraphGUI.cpp
 * @author Nieve Wong
 * @brief This class represents the "graph" tab of the main GUI.
 * @version 0.1
 */

#include "../../include/model/utilities/Utilities.h"
#include "../../include/view/GraphGUI.h"

/**
* @brief Construct a new graph GUI object
*
* Calls QWidget constructor and initializes all data members.
*
* @param parent Allows for parent-child relationships with matrix.
*/
GraphGUI::GraphGUI(QWidget *parent)
        : QWidget(parent) {
    //main vertical layout and function input line
    auto *mainLayout = new QVBoxLayout;
    inputLine = new QLineEdit;
    inputLine->setMaxLength(50);

    //manage font of input box
    QFont font = inputLine->font();
    font.setPointSize(font.pointSize() + 8);
    inputLine->setFont(font);

    //create digit buttons for input
    for (int i = 0; i < 10; ++i)
        digitButtons[i] = createButton(QString::number(i), SLOT(digitClicked()));

    //create non-digit buttons for input
    toggleButton = new QPushButton("Alphabet");
    connect(toggleButton, &QPushButton::clicked, this, &GraphGUI::toggleClicked);
    clearButton = new QPushButton("Clear");
    connect(clearButton, &QPushButton::clicked, this, &GraphGUI::clear);
    graphButton = new QPushButton("Graph");
    connect(graphButton, &QPushButton::clicked, this, &GraphGUI::graphClicked);
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

    //range input
    QLabel *rangeLabel = new QLabel("Range:");
    range1 = new QLineEdit;
    range2 = new QLineEdit;

    //box and grid layout for input buttons
    auto *buttonsBox = new QGroupBox();
    auto *buttonsLayout = new QGridLayout();

    //add clear, toggle, and graph buttons to grid layout
    buttonsLayout->setSizeConstraint(QLayout::SetNoConstraint);
    buttonsLayout->addWidget(clearButton, 1, 0, 1, 2);
    buttonsLayout->addWidget(toggleButton, 1, 2, 1, 2);
    buttonsLayout->addWidget(graphButton, 1, 4, 1, 2);

    //add digit buttons to grid layout
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

    //add non-digit buttons to grid layout
    buttonsLayout->addWidget(pointButton, 5, 1);
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
    buttonsLayout->addWidget(equalButton, 6, 1);
    buttonsLayout->addWidget(exclamButton, 6, 2);
    buttonsLayout->addWidget(rangeLabel, 6, 3);
    buttonsLayout->addWidget(range1, 6, 4);
    buttonsLayout->addWidget(range2, 6, 5);

    buttonsBox->setLayout(buttonsLayout);

    //create graph
    customPlot = new QCustomPlot();

    //add input line, buttons and output graph to main layout
    mainLayout->addWidget(inputLine);
    mainLayout->addWidget(buttonsBox);
    mainLayout->addWidget(customPlot);

    setLayout(mainLayout);

}

/**
 * @brief Appends clicked digit to input text.
 *
 * Called when a digit Button on the graph GUI is clicked.
 */
void GraphGUI::digitClicked() {
    auto *clickedButton = qobject_cast<Button *>(sender());
    QString clickedDigit = clickedButton->text();

    //If there is no display text and the Button pressed is "0", "0" is not appended.
    if (inputLine->text() == "" && clickedDigit == "0")
        return;

    inputLine->setText(inputLine->text() + clickedDigit);
}

/**
 * @brief Switches Buttons between alphabet and digits.
 *
 * Called when "Alphabet" on the graph GUI is clicked.
 */
void GraphGUI::toggleClicked() {
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
        squareRootButton->setText("Sqrt");
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
 * @brief Appends clicked operator text to input text
 *
 * Called when an operator or special character on the graph GUI is clicked.
 */
void GraphGUI::operatorClicked() {
    auto *clickedButton = qobject_cast<Button *>(sender());
    QString clickedOperator = clickedButton->text();

    //if else cases are for transforming input into program-readable form
    if (clickedOperator == "\303\227") {
        inputLine->setText(inputLine->text() + "*");
    } else if (clickedOperator == "\303\267") {
        inputLine->setText(inputLine->text() + "/");
    } else if (clickedOperator == "\317\200") {
        inputLine->setText(inputLine->text() + "pi");
    } else {
        inputLine->setText(inputLine->text() + clickedOperator);
    }

}

/**
 * @brief Clears all input display text.
 *
 * Called when "clear" on the graph GUI is clicked.
 */
void GraphGUI::clear() {
    inputLine->clear();
}

/**
 * @brief triggers the plotting of the function.
 *
 * Called when "graph" on the graph GUI is clicked.
 */
void GraphGUI::graphClicked() {
    std::string function = inputLine->text().toStdString();

//    double yValue = ButtonResponder::solveGraphButtonResponse(function,
    QString firstRange = range1->text();
    QString secondRange = range2->text();
    int first;
    int second;
    int size;

    if (firstRange == "") {
        first = -500;
    } else if (secondRange == "") {
        second = 500;
    } else {
        first = firstRange.toInt();
        second = secondRange.toInt();
    }

    size = abs(first) + abs(second) + 1;
    try {
        QVector<double> x(size), y(size);
        for (int i = 0; i < size; i++) {
            x[i] = first++;
            y[i] = ButtonResponder::solveGraphButtonResponse(function, Utilities::removeTrailingZeros(x[i]));
            customPlot->addGraph();
            customPlot->graph(0)->setData(x, y); //adding data points to graph
            // give axes some labels
            customPlot->xAxis->setLabel("x");
            customPlot->yAxis->setLabel("y");
            // axes ranges are rescaled accordingly
            customPlot->graph(0)->rescaleAxes();
            customPlot->replot();
        }
    } catch (std::exception &e) {
        auto *error = new QErrorMessage();
        error->showMessage(QString::fromStdString(e.what()));
    }

}

/**
 * @brief Creates new Button.
 *
 * Called from GraphGUI constructor.
 *
 * @param text The Button text.
 * @param member SLOT - function called in response to Button's clicked() SIGNAL.
 * @return Button* Button to be used in the calculator GUI.
 */
Button *GraphGUI::createButton(const QString &text, const char *member) {
    auto *newButton = new Button(text);
    connect(newButton, SIGNAL(clicked()), this, member);
    return newButton;
}

