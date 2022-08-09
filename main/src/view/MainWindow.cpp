/**
 * @file mainwindow.cpp
 * @author Nieve Wong
 * @brief This class represents the main window of the GUI.
 *
 * Main window utilized by users to interact with program.
 *
 * @version 0.1
 */

#include "../../include/view/MainWindow.h"

/**
 * @brief Construct a new mainwindow object.
 *
 * Calls QMainWindow constructor and initializes all data members.
 *
 * @param parent Allows for parent-child relationships with a main window
 */
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent) {
    tabbedWindows = new QTabWidget;
    sets = new SetsGUI();
    calculator = new CalculatorGUI();
    matrix = new MatrixGUI();
    graph = new GraphGUI();

    tabbedWindows->addTab(calculator, "Expressions");
    tabbedWindows->addTab(sets, "Sets");
    tabbedWindows->addTab(matrix, "Matrices");
    tabbedWindows->addTab(graph, "Graphs");

    setCentralWidget(tabbedWindows);
}
/**
 * Main Method of the program
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    mainWindow.resize(700, 800);

    return app.exec();
}
