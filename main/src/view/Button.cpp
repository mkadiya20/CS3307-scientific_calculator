/**
 * @file Button.cpp
 * @author Nieve Wong 
 * @brief This class represents a Button in "expressions" tab of main window GUI.
 * @version 0.1
 */

#include "../../include/view/Button.h"


/**
 * @brief Construct a new Button object
 * 
 * calls QToolButton constructor, sets the size policy of the Button and the text of the Button.
 * 
 * @param text label text of Button.
 * @param parent parent widget, Allowing for parent-child relationships with Button.
 */
Button::Button(const QString &text, QWidget *parent)
    : QToolButton(parent)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred); 
    setText(text); 
}

/*
name: sizeHint
description: reuse sizeHint of QToolButton class. Ensures text is not truncated and all buttons fit together nicely 
QSize: holds the size increment of Button.
*/

/**
 * @brief Ensures text is not truncated and all buttons fit together nicely.
 * 
 * reuse sizeHint of QToolButton class. 
 * 
 * @return QSize Holds the size increment of Button.
 */
QSize Button::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 20;  
    size.rwidth() = qMax(size.width(), size.height()); //make width component at least as much as the height
    return size;
} 

