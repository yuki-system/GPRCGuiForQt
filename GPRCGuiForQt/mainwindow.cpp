#include "mainwindow.h"

#include "CentralWidget/centralview.h"
#include "MenuBar/menubar.h"
#include "mainwindowmodel.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      model(new MainWindowModel(this, this)),
      menuBar(new MenuBar(model, this)),
      center(new CentralView(model->getCommandModel(), this))
{
    this->setMenuBar(menuBar);
    this->setCentralWidget(center);

    QJsonObject jobj;
    jobj["voe"] = 1;
    jobj["voda"] = "string";
    jobj["books"] = false;

    QJsonDocument jdoc(jobj);
    QString jstr = jdoc.toJson(QJsonDocument::Indented);
    QByteArray jbyte = jstr.toLocal8Bit();
    QJsonDocument jdoc2;
    jdoc2.fromJson(jbyte);
    QJsonObject jobj2 = jdoc2.object();
    qDebug() << "voe:" << jobj["voe"];
    qDebug() << "voda:" << jobj["voda"];
    qDebug() << "books" << jobj["books"];
    qDebug() << "halo" << jobj["halo"];
}

MainWindow::~MainWindow()
{

}
