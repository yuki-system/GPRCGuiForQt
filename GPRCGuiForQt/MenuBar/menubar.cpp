#include "menubar.h"

#include <QMenu>
#include <QAction>
#include "../mainwindowmodel.h"
#include "../ConnectWidget/connectview.h"


MenuBar::MenuBar(MainWindowModel *argModel, QWidget *parent) :
    QMenuBar(parent),
    menuFile(new QMenu(QObject::tr("File"), this)),
    actionConnect(new QAction(QObject::tr("Connect"), menuFile)),
    actionExit(new QAction(QObject::tr("Exit"), menuFile)),
    model(argModel)
{
    // メニュ階層の記述
    this->addMenu(menuFile);
    menuFile->addAction(actionConnect);
    menuFile->addAction(actionExit);

    // メニュ・アクションクリック時の機能記述
    connect(actionExit, &QAction::triggered,
            model, &MainWindowModel::slotExit);
    connect(actionConnect, &QAction::triggered,
            this, &MenuBar::slotOpenConnectView);
}

void MenuBar::slotOpenConnectView(bool)
{
    ConnectView conView;
    conView.exec();
}
