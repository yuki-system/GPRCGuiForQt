#include "mainwindowmodel.h"

#include "mainwindow.h"

MainWindowModel::MainWindowModel(MainWindow *argMainWindow, QObject *parent) :
    QObject(parent),
    mainwindow(argMainWindow)
{

}

void MainWindowModel::slotExit(void)
{
    mainwindow->close();
}
