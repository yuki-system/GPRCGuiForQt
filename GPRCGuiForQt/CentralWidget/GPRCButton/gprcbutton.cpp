#include "gprcbutton.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "../commandmodel.h"


GPRCButton::GPRCButton(CommandModel *argCommod, QWidget *parent)
    : GPRCButton("", argCommod, parent)
{
}

GPRCButton::GPRCButton(const QString &title, CommandModel *argCommod, QWidget *parent)
    : QGroupBox(title, parent),
      commod(argCommod),
      layout(new QVBoxLayout(this)),
      button(new QPushButton(title, this))
{
    button->setToolTip(title);
    layout->addWidget(button);

    button->setMinimumSize(40, 40);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    connect(button, &QPushButton::clicked,
            this, &GPRCButton::slotPushButtonSelf);
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

void GPRCButton::slotPushButtonSelf(void)
{
    commod->pushButton(this->title());
}

