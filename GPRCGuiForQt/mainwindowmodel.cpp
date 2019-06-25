#include "mainwindowmodel.h"

#include "mainwindow.h"

MainWindowModel::MainWindowModel(MainWindow *argMainWindow, QObject *parent) :
    QObject(parent),
    mainwindow(argMainWindow),
    connection(new ConnectionModel(nullptr)),
    command(new CommandModel(connection, this)),
    thConnection(new QThread(this))
{
    connection->moveToThread(thConnection);
    connect(thConnection, &QThread::finished, connection, &ConnectionModel::deleteLater);
    thConnection->start();
}

MainWindowModel::~MainWindowModel(void)
{
    if (thConnection == nullptr) {
        return;
    }

    thConnection->exit();
    thConnection->wait();
}

ConnectionModel *MainWindowModel::getConnectionModel(void)
{
    return this->connection;
}

CommandModel *MainWindowModel::getCommandModel(void)
{
    return this->command;
}

void MainWindowModel::slotExit(void)
{
    mainwindow->close();
}
