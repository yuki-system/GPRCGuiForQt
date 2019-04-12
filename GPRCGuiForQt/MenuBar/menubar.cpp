#include "menubar.h"

#include <QMenu>
#include <QAction>
#include "../mainwindowmodel.h"


MenuBar::MenuBar(MainWindowModel *argModel, QWidget *parent) :
    QMenuBar(parent),
    menuFile(new QMenu(QObject::tr("File"), this)),
    actionConnect(new QAction(QObject::tr("Connect"), menuFile)),
    actionExit(new QAction(QObject::tr("Exit"), menuFile)),
    model(argModel)
{

    this->addMenu(menuFile);
    menuFile->addAction(actionConnect);
    menuFile->addAction(actionExit);

    connect(actionExit, &QAction::triggered,
            model, &MainWindowModel::slotExit);
}
