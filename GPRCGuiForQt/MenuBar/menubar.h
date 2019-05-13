#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>


class QMenu;
class QAction;
class MainWindowModel;
class ConnectView;


/**
 * @brief メニューバーを実装するクラス
 */
class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    explicit MenuBar(MainWindowModel *argModel, QWidget *parent = nullptr);

private:


signals:

public slots:
    void slotOpenConnectView(bool); /// 接続画面の表示
public:
    QMenu *menuFile = nullptr;      /// ファイルメニュー
    QAction *actionConnect = nullptr;   /// 接続
    QAction *actionExit = nullptr;  /// 終了



    /**
     * @todo ふさわしいモデルの立て方を考える
     */
    MainWindowModel *model = nullptr;
};

#endif // MENUBAR_H
