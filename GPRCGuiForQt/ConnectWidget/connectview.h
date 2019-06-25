#ifndef CONNECTVIEW_H
#define CONNECTVIEW_H

#include <QDialog>
#include "connectionmodel.h"

class QTreeWidget;
class QTreeWidgetItem;
class QVBoxLayout;
class QGroupBox;
class QPushButton;
class ConnectionModel;

/**
 * @brief 接続先を検索、決定するためのUIクラス
 */
class ConnectView : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectView(ConnectionModel *arg_model, QWidget *parent = nullptr);

    QGroupBox *gboxServerList = nullptr;    /// サーバリストを囲うgroup box
    QTreeWidget *treeServerList = nullptr;  /// 検索したサーバのリストを表示する
    QPushButton *bResarch = nullptr;    /// 再検索ボタン
    QPushButton *bConnect = nullptr;    /// 接続ボタン


signals:
    void signalUdpEchoBackSearch(unsigned long);
    void signalConnect(QHostAddress, int);
public slots:
    /**
     * @brief UDPブロードキャストによるecho-backサーチを開始する
     */
    void slotSearch(bool);
    /**
     * @brief echo-backサーチの結果を反映する
     * @param 取得したサーバのリスト
     */
    void slotEchoBack(ServerList slist);
    /**
     * @brief 接続の実行
     * @details 接続ボタン押下時の挙動
     */
    void slotConnect(bool);
    void slotTreeItem(QTreeWidgetItem *item, QTreeWidgetItem*);
    void slotConnectResult(bool);
    void slotConnectError(QAbstractSocket::SocketError e, QString s);
private:
    ConnectionModel *model = nullptr;   /// サーバとのコネクションのモデル
    QVBoxLayout *layout = nullptr;  /// 全体レイアウト
    QVBoxLayout *layServerList = nullptr;   /// サーバリストのレイアウト
};

#endif // CONNECTVIEW_H
