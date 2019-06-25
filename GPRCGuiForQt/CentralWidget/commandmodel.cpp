#include "commandmodel.h"

CommandModel::CommandModel(ConnectionModel *argconmod, QObject *parent)
    : QObject(parent),
      conmod(argconmod)
{
    connect(this, &CommandModel::signalSendMessage,
            conmod, &ConnectionModel::slotSendMessage);
}

#include <QJsonObject>
#include <QJsonDocument>

void CommandModel::pushButton(const QString &buttonType)
{
    QJsonObject jsonObj;
    jsonObj["Gprc"] = "c2s";
    jsonObj["Type"] = "button";
    jsonObj["Button"] = buttonType;
    QJsonDocument jsonStr(jsonObj);
    qDebug() << jsonStr.toJson();
    emit signalSendMessage(jsonStr.toJson());
}
