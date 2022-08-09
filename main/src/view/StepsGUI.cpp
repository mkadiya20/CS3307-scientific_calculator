/**
 * @brief The Step GUI displays the steps and an interactable history
 *
 * The Steps GUI displays the steps from the expression calculations
 * along with an interactable history. The history class is called from
 * this class to fetch or update the steps.
 *
 * @author Mihir Kadiya
 */


#include "../../include/view/StepsGUI.h"
#include "../../include/view/History.h"


/**
 * parameterised constructor, extends QWidget
 * @param parent the parent QWidget
 */
StepsGUI::StepsGUI(QWidget *parent) : QWidget(parent) {
    // create a grid layout
    gridLayout = new QGridLayout;
    gridLayout->setHorizontalSpacing(1);

    // create the steps display
    stepsDisplay = new QTextEdit();
    // make it read only
    stepsDisplay->setReadOnly(true);
    listWidget = new QListWidget();

    gridLayout->addWidget(stepsDisplay, 0, 0);
    gridLayout->addWidget(listWidget, 1, 0);

    connect(listWidget, &QListWidget::itemClicked, this, &StepsGUI::handleList);

    setLayout(gridLayout);
}


/**
 * displays the steps in the GUI and stores the steps in the History class
 * @param steps the steps to be displayed and stored
 */
void StepsGUI::updateSteps(std::vector<std::string> steps) {
    // display the steps
    displaySteps(steps);

    // add the steps to history
    auto &history = History::getInstance();
    int length = history.size();
    auto *item = new QListWidgetItem;

    item->setText(QString::fromStdString(steps.at(0)));
    listWidget->insertItem(length, item);

    history.logHistory(steps);
}


/**
 * display the steps in the GUI
 * @param steps the steps to be displayed
 */
void StepsGUI::displaySteps(std::vector<std::string> steps) {
    std::string result;
    for (std::string step: steps) {
        result += step + "\n";
    }

    stepsDisplay->setText(QString::fromStdString(result));
}


/**
 * a Qt slot which is triggered when an item in the list widget
 * is clicked. The selected item is displayed in the GUI by fetching the
 * steps from the History class.
 */
void StepsGUI::handleList() {
    // get the history object instance
    History &history = History::getInstance();

    // get the index of selected item from the list
    int index = listWidget->currentRow();

    // get history from the index
    std::vector<std::string> steps = history.retrieveHistory(index);

    // display the selected history item
    displaySteps(steps);
}
