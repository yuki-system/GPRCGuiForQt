#include "connectview.h"
#include <QTreeWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QProgressDialog>
#include <QDebug>


ConnectView::ConnectView(ConnectionModel *arg_model, QWidget *parent)
    : QDialog(parent),
      gboxServerList(new QGroupBox(QObject::tr("Server List:"), this)),
      treeServerList(new QTreeWidget(gboxServerList)),
      bResarch(new QPushButton(QObject::tr("re-search"), gboxServerList)),
      bConnect(new QPushButton(QObject::tr("Connect"), this)),
      model(arg_model),
      layout(new QVBoxLayout(this)),
      layServerList(new QVBoxLayout(gboxServerList))
{

    // レイアウト配置
    layout->addWidget(gboxServerList);
    layout->addWidget(bConnect);
    layServerList->addWidget(treeServerList);
    layServerList->addWidget(bResarch, 0, Qt::AlignRight);

    // 接続ボタンはデフォルトでは選択不可
    bConnect->setEnabled(false);
    connect(bResarch, &QPushButton::clicked, this, &ConnectView::slotSearch);
    connect(this, &ConnectView::signalUdpEchoBackSearch, model, &ConnectionModel::slotUDPEchoBack);
    connect(bConnect, &QPushButton::clicked, this, &ConnectView::slotConnect);
    connect(this, &ConnectView::signalConnect, model, &ConnectionModel::slotTCPConnect);
    connect(treeServerList, &QTreeWidget::currentItemChanged, this, &ConnectView::slotTreeItem);


    // リストのヘッダ記述
    QStringList headers;
    headers.append(QObject::tr("Name"));
    headers.append(QObject::tr("IP addr"));
    treeServerList->setHeaderLabels(headers);
    treeServerList->setColumnCount(2);
}

/*
 * @brief UDPブロードキャストによるecho-backサーチを開始する
 */
void ConnectView::slotSearch(bool)
{
    QProgressDialog diag;   // 進捗ダイアログ

    /*
     * modelがecho-backに成功したら、進捗ダイアログを成功裏に閉じて、slotEchoBackを呼び出す
     */
    connect(model, &ConnectionModel::signalUDPEchoBack, &diag, &QProgressDialog::accept);
    connect(model, &ConnectionModel::signalUDPEchoBack, this, &ConnectView::slotEchoBack);

    diag.setRange(0, 0);    // 自動回転する進捗ダイアログ
    emit signalUdpEchoBackSearch(1);    // modelに対し、3秒間のecho-backを依頼

    int iResult = diag.exec();  // ダイアログオープン

    /*
     * クリックにてダイアログを閉じた場合は何もしない
     */
    disconnect(model, &ConnectionModel::signalUDPEchoBack, &diag, &QProgressDialog::accept);
    if (iResult != QDialog::Accepted) {
        disconnect(model, &ConnectionModel::signalUDPEchoBack, this, &ConnectView::slotEchoBack);
        qDebug() << "reject";
    }

}


/*
 * @brief echo-backサーチの結果を反映する
 * @param 取得したサーバのリスト
 */
void ConnectView::slotEchoBack(ServerList slist)
{
    disconnect(model, &ConnectionModel::signalUDPEchoBack, this, &ConnectView::slotEchoBack);
    this->treeServerList->clear();

    for(auto itr = slist.begin();itr != slist.end();itr++) {
        QString serverName = itr->first;
        QString hostaddr = itr->second.toString();
        if (serverName == model->getHeaderOurself()) {
            continue;
        }
        QTreeWidgetItem *item = new QTreeWidgetItem(0);
        item->setText(0, serverName);
        item->setText(1, hostaddr);
        treeServerList->addTopLevelItem(item);
    }
}
void ConnectView::slotConnect(bool)
{
    QProgressDialog diag;   // 進捗ダイアログ
    QTreeWidgetItem *item = treeServerList->currentItem();
    if (item == nullptr) {
        return;
    }
    QString strAddr = item->text(1);
    QHostAddress addr(strAddr);

    connect(model, &ConnectionModel::signalConnectSuccess, &diag, &QProgressDialog::accept);
    connect(model, &ConnectionModel::signalTCPConnectError, &diag, &QProgressDialog::accept);
    connect(model, &ConnectionModel::signalConnectSuccess, this, &ConnectView::slotConnectResult);
    connect(model, &ConnectionModel::signalTCPConnectError, this, &ConnectView::slotConnectError);

    diag.setRange(0, 0);
    emit signalConnect(addr, 1000);
    int iResult = diag.exec();
    disconnect(model, &ConnectionModel::signalConnectSuccess, &diag, &QProgressDialog::accept);
    disconnect(model, &ConnectionModel::signalTCPConnectError, &diag, &QProgressDialog::accept);

    if (iResult != QDialog::Accepted) {
        disconnect(model, &ConnectionModel::signalConnectSuccess, this, &ConnectView::slotConnectResult);
        disconnect(model, &ConnectionModel::signalTCPConnectError, this, &ConnectView::slotConnectError);
    }


}

void ConnectView::slotTreeItem(QTreeWidgetItem *item, QTreeWidgetItem *)
{
    if (item == nullptr) {
        this->bConnect->setEnabled(false);
    } else {
        this->bConnect->setEnabled(true);
    }
}
#include <QMessageBox>

void ConnectView::slotConnectResult(bool)
{
    disconnect(model, &ConnectionModel::signalConnectSuccess, this, &ConnectView::slotConnectResult);
    QMessageBox mesbox;
    mesbox.setText(QObject::tr("接続しました"));
    mesbox.exec();
    this->close();
}

void ConnectView::slotConnectError(QAbstractSocket::SocketError e, QString s)
{
    disconnect(model, &ConnectionModel::signalConnectSuccess, this, &ConnectView::slotConnectResult);
    disconnect(model, &ConnectionModel::signalTCPConnectError, this, &ConnectView::slotConnectError);
    QMessageBox mesbox;
    Q_UNUSED(e)
    mesbox.setText(QObject::tr("接続に失敗しました\nError:")+s);
    mesbox.exec();
}
