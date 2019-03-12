#include "tbplaygame.h"
#include "ui_tbplaygame.h"
#include <qvariant.h>

TBPlayGame::TBPlayGame(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TBPlayGame)
{
    ui->setupUi(this);

    //
    ui->mainWidget->showUrl ("http://zsall.mobilem.360.cn/index/game/search/1/?sdkver=0&ver=2.5.1.1630");
    ui->listWidget->setFocusPolicy(Qt::NoFocus);

    QVector<TitleObject*> list;
    list.append (new TitleObject(nullptr, "安卓游戏", true, ""));
    list.append (new TitleObject(nullptr, "游戏首页", false, "http://zsall.mobilem.360.cn/index/game?isnew=1&sdkver=0&ver=2.5.1.1630"));
    list.append (new TitleObject(nullptr, "排行榜", false, "http://zsall.mobilem.360.cn/html/game-rank-v2.html?ver=2.5.1.1630"));
    list.append (new TitleObject(nullptr, "游戏分类", false, "http://openbox.mobilem.360.cn/app/list/cid/2/order/weekpure/?ver=2.5.1.1630"));
    list.append (new TitleObject(nullptr, "活动专区", true, ""));
    list.append (new TitleObject(nullptr, "热血江湖", false, "http://huodong.mobilem.360.cn/html/rxjhpcyy/0221.html?from=mp_rxjh0221&ver=2.5.1.1630"));
    list.append (new TitleObject(nullptr, "先行赔付", false, "http://zhushou.360.cn/peifu?ver=2.5.1.1630"));

    showListWidget (list);
}

void TBPlayGame::showListWidget (QVector<TitleObject*> list) {
    ui->listWidget->show (list);
    connect(ui->listWidget, SIGNAL(onHListWidgetItemPress (TitleObject *)), this,
            SLOT(on_hlistwidget_item_clicked(TitleObject *)));
}

TBPlayGame::~TBPlayGame()
{
    delete ui;
}

void TBPlayGame::on_hlistwidget_item_clicked(TitleObject * to) {
    //
    ui->mainWidget->showUrl (to->userInfo);
}
