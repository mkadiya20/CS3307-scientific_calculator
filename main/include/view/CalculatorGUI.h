/**
 * @brief This class represents the "expressions" tab of the main GUI.
 *
 * @details Provides an interface for users to input mathematical problems and
 * to display the corresponding solution + steps.
 *
 * @author Nieve Wong
 * @version 1.0
 */


#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGroupBox>
#include <vector>
#include <string>
#include <QErrorMessage>
#include "../../include/view/Button.h"
#include "../../include/view/StepsGUI.h"
#include "../../include/controller/ButtonResponder.h"


class CalculatorGUI : public QWidget {
Q_OBJECT

public:
    CalculatorGUI(QWidget *parent = nullptr);

    ~CalculatorGUI() = default;

private slots:

    void digitClicked();

    void toggleClicked();

    void operatorClicked();

    void addLineClicked();

    void removeLineClicked();

    void lineClicked();

    void clear();

    void solveClicked();

protected:
    bool eventFilter(QObject *object, QEvent *ev) override;

private:
    QPushButton *toggleButton;
    QPushButton *clearButton;
    Button *pointButton;
    Button *divisionButton;
    Button *timesButton;
    Button *minusButton;
    Button *plusButton;
    Button *squareRootButton;
    Button *powerButton;
    Button *leftBracket;
    Button *rightBracket;
    Button *sinButton;
    Button *cosButton;
    Button *tanButton;
    Button *logButton;
    Button *eulerButton;
    Button *piButton;
    Button *equalButton;
    Button *exclamButton;
    Button *addLineButton;
    Button *removeLineButton;
    Button *digitButtons[10];
    int numLines;
    QLineEdit *currLine;
    QPushButton *solveButton;
    QLineEdit *display[50];
    StepsGUI *stepsDisplay;

    Button *createButton(const QString &text, const char *member);

};

#endif
