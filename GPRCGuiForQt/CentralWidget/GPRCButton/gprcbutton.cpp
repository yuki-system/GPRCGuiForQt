#include "gprcbutton.h"
#include <QPushButton>
#include <QVBoxLayout>

GPRCButton::GPRCButton(QWidget *parent)
    : GPRCButton("", parent)
{
}

GPRCButton::GPRCButton(const QString &title, QWidget *parent)
    : QGroupBox(title, parent),
      layout(new QVBoxLayout(this)),
      button(new QPushButton(title, this))
{
    button->setToolTip(title);
    layout->addWidget(button);

    button->setMinimumSize(40, 40);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void GPRCButton::setButtonText(const QString &text)
{
    button->setText(text);
}

void GPRCButton::setButtonTooltip(const QString &text)
{
    button->setToolTip(text);
}

void GPRCButton::setInitializeText(const QString &boxText, const QString &buttonText, const QString &tooltipText)
{
    this->setTitle(boxText);
    button->setText(buttonText);
    button->setToolTip(tooltipText);
}

