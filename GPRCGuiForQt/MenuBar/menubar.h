#ifndef MENUBAR_H
#define MENUBAR_H

#include <QMenuBar>


class QMenu;
class QAction;
class MainWindowModel;


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
public:
    QMenu *menuFile = nullptr;
    QAction *actionConnect = nullptr;
    QAction *actionExit = nullptr;

    MainWindowModel *model = nullptr;
};

#endif // MENUBAR_H
