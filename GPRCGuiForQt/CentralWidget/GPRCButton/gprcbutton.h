#ifndef GPRCBUTTON_H
#define GPRCBUTTON_H

#include <QGroupBox>

class QPushButton;
class QVBoxLayout;
class CommandModel;

/**
 * @class GPRCButton
 * @brief QGroupBoxに囲まれたボタンを実装するクラス
 */
class GPRCButton : public QGroupBox
{
    Q_OBJECT
public:
    explicit GPRCButton(CommandModel *argCommod, QWidget *parent = nullptr);
    GPRCButton(const QString &title, CommandModel *argCommod, QWidget *parent = nullptr);

    /**
     * @brief ボタン表示文字の変更
     * @param text ボタン表示文字
     */
    void setButtonText(const QString &text);

    /**
     * @brief ボタンツールチップの変更
     * @param text ツールチップ文字
     */
    void setButtonTooltip(const QString &text);

    /**
     * @brief 初期化用文字列代入
     * @param QGroupBoxの文字列
     * @param ボタンの文字列
     * @param ツールチップの文字列
     */
    void setInitializeText(const QString &boxText,
                           const QString &buttonText,
                           const QString &tooltipText);



signals:

public slots:
    /**
     * @brief ボタンが押された時の挙動
     * @details
     * ボタンクリックSIGNALを、commandmodelへの命令発行に変換する
     * ボタン識別子として、GroupBoxのtitleをそのまま使う
     */
    void slotPushButtonSelf(void);
private:
    CommandModel *commod = nullptr;
    QVBoxLayout *layout = nullptr;
    QPushButton *button = nullptr;


};

#endif // GPRCBUTTON_H
