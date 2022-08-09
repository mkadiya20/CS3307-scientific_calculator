/**
 * @file mainwindow.cpp
 * @author Nieve Wong
 * @brief This class represents the main window of the GUI.
 *
 * Main window utilized by users to interact with program.
 *
 * @version 0.1
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTabWidget>
#include "../../include/view/SetsGUI.h"
#include "../../include/view/CalculatorGUI.h"
#include "../../include/view/MatrixGUI.h"
#include "../../include/view/GraphGUI.h"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() = default;

private slots:

private:
    QTabWidget *tabbedWindows;
    SetsGUI *sets;
    CalculatorGUI *calculator;
    MatrixGUI *matrix;
    GraphGUI *graph;
};

#endif
