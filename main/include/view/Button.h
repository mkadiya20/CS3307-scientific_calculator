/**
 * @file Button.cpp
 * @author Nieve Wong
 * @brief This class represents a Button in "expressions" tab of main window GUI.
 * @version 0.1
 */

#ifndef BUTTON_H
#define BUTTON_H

#include <QToolButton>

class Button : public QToolButton {
Q_OBJECT

public:
    explicit Button(const QString &text, QWidget *parent = nullptr);

    ~Button() = default;

    QSize sizeHint() const override;
};

#endif
