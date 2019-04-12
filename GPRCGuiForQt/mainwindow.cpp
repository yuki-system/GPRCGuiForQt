#include "mainwindow.h"

#include "CentralWidget/centralview.h"
#include "MenuBar/menubar.h"
#include "mainwindowmodel.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      model(new MainWindowModel(this, this)),
      menuBar(new MenuBar(model, this)),
      center(new CentralView(this))
{
    this->setMenuBar(menuBar);
    this->setCentralWidget(center);
}

MainWindow::~MainWindow()
{

}
