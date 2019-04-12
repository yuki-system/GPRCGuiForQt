#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


class CentralView;
class MenuBar;
class MainWindowModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    MainWindowModel *model = nullptr;

    MenuBar *menuBar = nullptr;
    CentralView *center = nullptr;

private:

};

#endif // MAINWINDOW_H
