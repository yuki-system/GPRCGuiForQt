#ifndef CENTRALVIEW_H
#define CENTRALVIEW_H

#include <QWidget>
#include <array>
class QGridLayout;
class QTextEdit;
class QLineEdit;
class QPushButton;
class GPRCButton;
#include "commandmodel.h"
class CommandModel;


/**
 * @namespace CentralButton
 * @brief GUI中心のボタン群の識別に関する値
 */
namespace CentralButton
{
    /**
     * @enum Button
     * @brief ボタンの識別enum
     * @details
     * GPRCはUI上の各ボタンの表記やTooltip、意味する動作を自由に定義できるフレームワークであるが、
     * 初期値として便宜的に電卓状の配列を施してある。
     * 内部識別子もこれに従う
     */
    using Button = enum {
        Num0,   /// Button 0
        Num1,   /// Button 1
        Num2,
        Num3,
        Num4,
        Num5,
        Num6,
        Num7,
        Num8,
        Num9,
        Point,  /// Button .(point)
        Equal,  /// Nutton =(equal)
        Plus,
        Minus,
        Multiply,
        Divide,
        BackSpace,
        Red,
        Green,
        Blue,
        Yellow,
        Centinel,   // 番兵
    };

    using ButtonInitializeTuple = struct {
        Button buttonEnum;
        QString gboxText;
        QString buttonText;
        QString buttonTooltip;
    };
}

class CentralView : public QWidget
{
    Q_OBJECT
public:
    explicit CentralView(CommandModel *argCommod, QWidget *parent = nullptr);


signals:

public slots:
private:
    CommandModel *commod = nullptr;
    QGridLayout *layout = nullptr;  /// 全体レイアウト
public:
    QTextEdit *teViewer = nullptr;  /// 文字表示器
    using ArrayButton =
    std::array<GPRCButton*, CentralButton::Centinel>;
    ArrayButton button; /// ボタン配列
    QLineEdit *leInput = nullptr;   /// 文字入力エリア
    QPushButton *bEnter = nullptr;  /// 文字入力反映ボタン

};


#endif // CENTRALVIEW_H
