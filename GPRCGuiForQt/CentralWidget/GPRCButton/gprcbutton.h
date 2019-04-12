#ifndef GPRCBUTTON_H
#define GPRCBUTTON_H

#include <QGroupBox>

class QPushButton;
class QVBoxLayout;

/**
 * @class GPRCButton
 * @brief QGroupBoxに囲まれたボタンを実装するクラス
 */
class GPRCButton : public QGroupBox
{
    Q_OBJECT
public:
    explicit GPRCButton(QWidget *parent = nullptr);
    GPRCButton(const QString &title, QWidget *parent = nullptr);

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

private:
    QVBoxLayout *layout = nullptr;
    QPushButton *button = nullptr;


};

#endif // GPRCBUTTON_H
