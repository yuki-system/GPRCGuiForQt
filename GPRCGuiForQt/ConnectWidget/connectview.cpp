#include "connectview.h"
#include <QTreeWidget>

ConnectView::ConnectView(QWidget *parent)
    : QDialog(parent),
      gboxServerList(new QGroupBox(QObject::tr("Server List:"), this)),
      treeServerList(new QTreeWidget(gboxServerList)),
      bResarch(new QPushButton(QObject::tr("re-search"), gboxServerList)),
      bConnect(new QPushButton(QObject::tr("Connect"), this)),
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


    // リストのヘッダ記述
    QStringList headers;
    headers.append(QObject::tr("Name"));
    headers.append(QObject::tr("IP addr"));
    treeServerList->setHeaderLabels(headers);
    treeServerList->setColumnCount(2);
}
