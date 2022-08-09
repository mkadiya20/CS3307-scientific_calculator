/**
 * @file GraphGUI.cpp
 * @author Nieve Wong
 * @brief This class represents the "graph" tab of the main GUI.
 * @version 0.1
 */
#ifndef GRAPHS_H
#define GRAPHS_H

#include <QWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QErrorMessage>
#include "../../include/controller/ButtonResponder.h"
#include "Button.h"
#include "qcustomplot.h"

class GraphGUI : public QWidget {
Q_OBJECT

public:
    explicit GraphGUI(QWidget *parent = nullptr);

    ~GraphGUI() = default;

private slots:

    void digitClicked();

    void toggleClicked();

    void operatorClicked();

    void clear();

    void graphClicked();

private:
    QPushButton *toggleButton;
    QPushButton *clearButton;
    QPushButton *graphButton;
    QLineEdit *inputLine;
    QCustomPlot *customPlot;

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
    Button *digitButtons[10]{};
    QLineEdit *range1;
    QLineEdit *range2;

    Button *createButton(const QString &text, const char *member);


};

#endif