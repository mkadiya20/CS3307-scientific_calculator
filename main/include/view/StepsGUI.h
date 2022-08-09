/**
 * @brief The Step GUI displays the steps and an interactable history
 *
 * The Steps GUI displays the steps from the expression calculations
 * along with an interactable history. The history class is called from
 * this class to fetch or update the steps.
 *
 * @author Mihir Kadiya
 */


#ifndef STEPSGUI_H
#define STEPSGUI_H

#include <vector>

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>

#include <QApplication>

class StepsGUI : public QWidget {
Q_OBJECT

public:
    explicit StepsGUI(QWidget *parent = nullptr);

    ~StepsGUI() override = default;

    void updateSteps(std::vector<std::string> steps);

    void displaySteps(std::vector<std::string> steps);

private:
    QGridLayout *gridLayout;
    QTextEdit *stepsDisplay;
    QListWidget *listWidget;

private slots:

    void handleList();
};

#endif