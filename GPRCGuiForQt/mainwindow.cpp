#include "mainwindow.h"

#include "CentralWidget/centralview.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      center(new CentralView(this))
{
    this->setCentralWidget(center);
}

MainWindow::~MainWindow()
{

}
