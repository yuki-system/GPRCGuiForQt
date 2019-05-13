#ifndef CONNECTVIEW_H
#define CONNECTVIEW_H

#include <QDialog>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>

class QTreeWidget;
class QTreeWidgetItem;
class QVBoxLayout;
class QGroupBox;
class QPushButton;

class ConnectView : public QDialog
{
    Q_OBJECT
public:
    explicit ConnectView(QWidget *parent = nullptr);

    QGroupBox *gboxServerList = nullptr;
    QTreeWidget *treeServerList = nullptr;
    QPushButton *bResarch = nullptr;
    QPushButton *bConnect = nullptr;


signals:

public slots:
private:
    QVBoxLayout *layout = nullptr;
    QVBoxLayout *layServerList = nullptr;
};

#endif // CONNECTVIEW_H
