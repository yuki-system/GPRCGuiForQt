#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <QObject>


class MainWindow;

/**
 * @brief メイン画面の(ひいてはこのGUIすべてを包含する)モデルクラス
 */
class MainWindowModel : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowModel(MainWindow *argMainWindow, QObject *parent = nullptr);

signals:

public slots:
    void slotExit(void);

private:
    MainWindow *mainwindow = nullptr;
};

#endif // MAINWINDOWMODEL_H
