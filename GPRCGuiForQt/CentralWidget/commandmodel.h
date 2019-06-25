#ifndef COMMANDMODEL_H
#define COMMANDMODEL_H
#if 0
各種ボタンの挙動を、JSONにしてconnectionmodelに送る

サーバから送られてきたJSONを、各種UIに反映する(別クラスの役割？)
#endif
#include <QObject>
#include "../ConnectWidget/connectionmodel.h"

class ConnectionModel;

class CommandModel : public QObject
{
    Q_OBJECT
public:
    explicit CommandModel(ConnectionModel *argconmod, QObject *parent = nullptr);

signals:
    void signalSendMessage(QByteArray);
public slots:
    void pushButton(const QString &buttonType);
private:
    ConnectionModel *conmod = nullptr;
};

#endif // COMMANDMODEL_H
