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

#ifndef SETS_H
#define SETS_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QErrorMessage>
#include "../../include/controller/ButtonResponder.h"


class SetsGUI : public QWidget {
Q_OBJECT

public:
    explicit SetsGUI(QWidget *parent = nullptr);

    ~SetsGUI() = default;

private slots:

    void operatorClicked();

    void digitClicked();

    void changeSetClicked();

    void clearSetClicked();

    void solveClicked();

private:
    static std::vector<double> getSetValues(std::string);

    QLineEdit *outputBox;
    QLineEdit *firstSet;
    QLineEdit *secondSet;
    QLineEdit *operators;
    QPushButton *unionButton;
    QPushButton *intersectButton;
    QPushButton *minusButton;
    QPushButton *changeSetButton;
    QPushButton *clearSetButton;
    QPushButton *solveButton;
    QPushButton *digitButtons[10]{};
    QPushButton *commaButton;
    QPushButton *pointButton;
    bool isFirstSet;
};

#endif
