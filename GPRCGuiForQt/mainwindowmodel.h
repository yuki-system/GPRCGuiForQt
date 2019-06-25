#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include <QObject>
#include "ConnectWidget/connectionmodel.h"
#include "CentralWidget/commandmodel.h"
#include <QThread>

class MainWindow;

/**
 * @brief メイン画面の(ひいてはこのGUIすべてを包含する)モデルクラス
 */
class MainWindowModel : public QObject
{
    Q_OBJECT
public:
    explicit MainWindowModel(MainWindow *argMainWindow, QObject *parent = nullptr);
    ~MainWindowModel(void);
    /**
     * @brief 接続モデルの取得
     * @return 接続モデルオブジェクト
     */
    ConnectionModel *getConnectionModel(void);
    CommandModel *getCommandModel(void);


signals:

public slots:
    void slotExit(void);

private:
    MainWindow *mainwindow = nullptr;   // mainwindowUI
    ConnectionModel *connection = nullptr;  // connection model
    CommandModel *command = nullptr;    // command model
    /**
     * @note
     * connectionは別スレッドに移動することに留意
     * commandはMainWindowと同じスレッドの為、command-connection間は
     * SIGNAL/SLOTを経由する必要がある
     */
    QThread *thConnection = nullptr;    // connection用スレッド
};

#endif // MAINWINDOWMODEL_H
