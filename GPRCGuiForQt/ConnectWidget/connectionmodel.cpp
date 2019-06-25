#include "connectionmodel.h"
#include <QThread>  // for sleep
#include <QDataStream>

constexpr int udpSendPort = 60001;
constexpr int udpRecvPort = 60002;
constexpr int tcpPort = 60011;
#define UDP_HEADER "Magick Number "

static int toBigE(const int arg);
static bool isHostBigE(void);
ConnectionModel::ConnectionModel(QObject *parent) : QObject(parent)
{
    // echo-back用udpソケットのbind
    //udpSendSock.bind(QHostAddress::Any, udpPort, QUdpSocket::ShareAddress);

    // TCPソケットが読み込み準備完了したら、メッセージを受け取るようにする
    connect(&tcpSock, &QTcpSocket::readyRead, this, &ConnectionModel::slotRecvMessage);

    // usingした独自型を用いたSIGNAL/SLOTをする場合、必要
    qRegisterMetaType<ServerList>("ServerList");
    qRegisterMetaType<QHostAddress>("QHostAddress");
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");

}

void ConnectionModel::moveToThread(QThread *thread)
{
    udpSendSock.moveToThread(thread);
    tcpSock.moveToThread(thread);
    QObject::moveToThread(thread);
}

QByteArray ConnectionModel::getHeaderOurself(void)
{
    return UDP_HEADER;
}

void ConnectionModel::slotUDPEchoBack(unsigned long waitSec)
{
    QUdpSocket udpRecvSock;
    // 受信用udpソケットを開く
    udpRecvSock.bind(udpRecvPort, QUdpSocket::ShareAddress);
    QByteArray magicNum = UDP_HEADER;
    // マジックナンバーをブロードキャストして応答を待つ
    udpSendSock.writeDatagram(magicNum, QHostAddress::Broadcast, udpSendPort);
    QThread::sleep(waitSec);
    ServerList resultList;

    // 応答が帰ってきたら、メッセージと応答元をリストにする
    while (udpRecvSock.hasPendingDatagrams()) {
        QHostAddress serverAddr;
        QByteArray recvMes;
        recvMes.resize(static_cast<int>(udpRecvSock.pendingDatagramSize()));
        udpRecvSock.readDatagram(recvMes.data(), recvMes.size(), &serverAddr);
        resultList.append(ServerPair(recvMes, serverAddr));
        qDebug() << "host:" << serverAddr << ", mes:" << recvMes;

    }

    // リストをsignal通信
    emit signalUDPEchoBack(resultList);

}

#include <QJsonObject>
#include <QJsonDocument>
void ConnectionModel::slotTCPConnect(const QHostAddress &addr, const int waitsec)
{
    if (tcpSock.isOpen()) {
        disconnect(&tcpSock, &QTcpSocket::disconnected,
                this, &ConnectionModel::slotTCPDisconnected);
        tcpSock.close();


    }

    tcpSock.connectToHost(addr,tcpPort);

    if (!tcpSock.waitForConnected(waitsec)){
        qDebug() << "Unconnected:" << tcpSock.error();
        emit signalTCPConnectError(tcpSock.error(), tcpSock.errorString());
        return;
    }
    emit signalConnectSuccess(true);
    connect(&tcpSock, &QTcpSocket::disconnected,
            this, &ConnectionModel::slotTCPDisconnected);

    QJsonObject jsonObj;
    jsonObj["Gprc"] = "c2s";
    jsonObj["Type"] = "hello";
    QJsonDocument jsonStr(jsonObj);
    this->slotSendMessage(jsonStr.toJson());
}

void ConnectionModel::slotSendMessage(const QByteArray &data)
{
    if (!tcpSock.isOpen()) {
        emit signalTCPNoConnect();
        return;
    }
    /**
     * @todo
     * ヘッダ＋データサイズ＋データの塊を古典的な方法で送る
     * もし、QByteArrayとQTcpSocketが要求したデータ転送の完遂を保証してくれるなら、
     * ここの記述はより簡潔なものとなる。要調査。
     */
    const int datalen = data.size();
    /*
     * ヘッダを送る
     */
    char head[] = "GPRC";   // ヘッダ
    this->sendDataLoop(head, 4);
    /*
     * データの量を送る
     */
    int bigEdatalen = toBigE(datalen);
    const char *cdatalen = reinterpret_cast<const char*>(&bigEdatalen);
    this->sendDataLoop(cdatalen, 4);
    /*
     * 本データを送る
     */
    const char *cdata = data.data();
    this->sendDataLoop(cdata, datalen);
    qDebug() << data;
}

void ConnectionModel::slotRecvMessage(void)
{

    if (!tcpSock.isOpen()) {
        emit signalTCPNoConnect();
        return;
    }
    QDataStream ds(&tcpSock);
    ds.setVersion(QDataStream::Qt_5_12);
    QByteArray data = tcpSock.readAll();

    emit signalTCPRecvMessage(data);
    qDebug() << data;

}

void ConnectionModel::slotTCPDisconnected(void)
{
    qDebug() << "disconnected";
    disconnect(&tcpSock, &QTcpSocket::disconnected,
            this, &ConnectionModel::slotTCPDisconnected);
    emit signalDisconnected();
}

void ConnectionModel::slotTCPError(const QAbstractSocket::SocketError &e)
{

}

bool ConnectionModel::sendDataLoop(const char *begin, const int dsize)
{
    int rsize = dsize;
    while(rsize > 0) {
        auto ssize = tcpSock.write(&begin[dsize-rsize], rsize);
        if (ssize <= 0) {
            return false;
        }
        rsize -= ssize;
    }
    return true;
}


int toBigE(const int arg)
{
    if (isHostBigE()) {
        return arg;
    }
    int result;
    const char *cptrArg = reinterpret_cast<const char*>(&arg);
    char *cptrResult = reinterpret_cast<char *>(&result);
    cptrResult[0] = cptrArg[3];
    cptrResult[1] = cptrArg[2];
    cptrResult[2] = cptrArg[1];
    cptrResult[3] = cptrArg[0];
    return result;
}

bool isHostBigE(void)
{
    union {
        uint32_t b4;
        uint8_t b1[4];
    } bytes;
    bytes.b4 = 0x12345678;
    return (bytes.b1[0] == 0x12);
}
