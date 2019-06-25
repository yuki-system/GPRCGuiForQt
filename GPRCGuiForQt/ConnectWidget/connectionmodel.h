#ifndef CONNECTIONMODEL_H
#define CONNECTIONMODEL_H

#include <QObject>
#include <QUdpSocket>
#include <QTcpSocket>

#if 0
UDPを用いたecho-back
要求を入力として受け取り、接続先のリストを返す

TCPによるコネクション成立
接続先を受け取り、成否を返す。
これまで接続していたコネクションがあれば切断し、再度接続先に接続する

(JSON)テキストの送信
JSONテキストを受け取り、送信の成否を返す。

(JSON)テキストの受信
SIGNAL/SLOTにて一方的にテキストを受信する
#endif
/**
 * @brief サーバとの接続と通信を担うクラス
 * @details
 * 本クラスはQThreadによってGUIの操作とは別スレッドで動くことを想定している
 * 真にバックボーンであり、本アプリの中核であるともいえる
 */
using ServerPair = QPair<QByteArray, QHostAddress>;
using ServerList = QList<ServerPair>;

class ConnectionModel : public QObject
{
    Q_OBJECT
public:
    explicit ConnectionModel(QObject *parent = nullptr);
    void moveToThread(QThread *thread);
    QByteArray getHeaderOurself(void);

signals:
    void signalUDPEchoBack(ServerList);
    void signalTCPConnectError(QAbstractSocket::SocketError, QString);
    void signalTCPNoConnect(void);
    void signalTCPNoSend(void);
    void signalTCPRecvMessage(QByteArray);
    void signalDisconnected(void);
    void signalConnectSuccess(bool);
public slots:
    void slotUDPEchoBack(unsigned long waitSec); /// UDP通信によるecho-backなサーバ検索を開始する
    void slotTCPConnect(const QHostAddress &addr, const int waitsec); /// TCP通信を開始する
    void slotSendMessage(const QByteArray &data);   /// メッセージを送る
    void slotRecvMessage(void); /// メッセージをTCPから受け取る
    void slotTCPDisconnected(void);
    void slotTCPError(const QAbstractSocket::SocketError &e);


private:
    QUdpSocket udpSendSock;
    QTcpSocket tcpSock;
    bool sendDataLoop(const char *begin, const int dsize);

};

#endif // CONNECTIONMODEL_H
