#include "centralview.h"
#include <QGridLayout>

#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include "GPRCButton/gprcbutton.h"

/**
 * @brief 各種ボタンの初期boxタイトル、初期テキスト、初期ツールチップ
 */
namespace CB{
    using namespace CentralButton;
    static ButtonInitializeTuple tupButtonIni[Centinel] =
    {
        {Num0, "0", "0", "0"},
        {Num1, "1", "1", "1"},
        {Num2, "2", "2", "2"},
        {Num3, "3", "3", "3"},
        {Num4, "4", "4", "4"},
        {Num5, "5", "5", "5"},
        {Num6, "6", "6", "6"},
        {Num7, "7", "7", "7"},
        {Num8, "8", "8", "8"},
        {Num9, "9", "9", "9"},
        {Point, "point", ".", "point"},
        {Equal, "equal", "=", "equal"},
        {Plus, "plus", "+", "plus"},
        {Minus, "minus", "-", "minus"},
        {Multiply, "multi", "*", "multiply"},
        {Divide, "divede", "/", "divide"},
        {BackSpace, "bs", "BS", "backspace"},
        {Red, "R", "", "red"},
        {Green, "G", "", "green"},
        {Blue, "B", "", "blue"},
        {Yellow, "Y", "", "yellow"},
    };
}


CentralView::CentralView(QWidget *parent) : QWidget(parent),
    layout(new QGridLayout(this)),
    teViewer(new QTextEdit(this)),
    leInput(new QLineEdit(this)),
    bEnter(new QPushButton(QObject::tr("Enter"), this))
{

    using namespace CentralButton;
    using sizetype = decltype(button.size());

    // ボタン初期化
    for (auto itr = button.begin(); itr != button.end(); itr++) {
        *itr = new GPRCButton(this);
    }
    // ボタン文字入力
    using namespace CB;
    for (sizetype idx = Num0;idx < Centinel; idx++) {
        button[idx]->setInitializeText(tupButtonIni[idx].gboxText,
                                       tupButtonIni[idx].buttonText,
                                       tupButtonIni[idx].buttonTooltip);
    }

    // ボタンレイアウト配置
    layout->addWidget(teViewer, 0, 0, 1, 4);
    layout->addWidget(button[Red], 1, 0, 1, 1);
    layout->addWidget(button[Green], 1, 1, 1, 1);
    layout->addWidget(button[Blue], 1, 2, 1, 1);
    layout->addWidget(button[Yellow], 1, 3, 1, 1);
    layout->addWidget(button[BackSpace], 2, 0, 1, 1);
    layout->addWidget(button[Divide], 2, 1, 1, 1);
    layout->addWidget(button[Multiply], 2, 2, 1, 1);
    layout->addWidget(button[Minus], 2, 3, 1, 1);
    layout->addWidget(button[Plus], 3, 3, 2, 1);
    layout->addWidget(button[Num7], 3, 0, 1, 1);
    layout->addWidget(button[Num8], 3, 1, 1, 1);
    layout->addWidget(button[Num9], 3, 2, 1, 1);
    layout->addWidget(button[Num4], 4, 0, 1, 1);
    layout->addWidget(button[Num5], 4, 1, 1, 1);
    layout->addWidget(button[Num6], 4, 2, 1, 1);
    layout->addWidget(button[Num1], 5, 0, 1, 1);
    layout->addWidget(button[Num2], 5, 1, 1, 1);
    layout->addWidget(button[Num3], 5, 2, 1, 1);
    layout->addWidget(button[Num0], 6, 0, 1, 2);
    layout->addWidget(button[Point], 6, 2, 1, 1);
    layout->addWidget(button[Equal], 5, 3, 2, 1);
    layout->addWidget(leInput, 7, 0, 1, 4);
    layout->addWidget(bEnter, 8, 0, 1, 4);

    // テキストビュアー書き込み禁止
    teViewer->setReadOnly(true);






}

