#include "hlistwidgettitle.h"
#include "ui_hlistwidgettitle.h"
#include <QGraphicsDropShadowEffect>

HListWidgetTitle::HListWidgetTitle(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HListWidgetTitle)
{
    ui->setupUi(this);

    //
    shadow ();
}

HListWidgetTitle::~HListWidgetTitle()
{
    delete ui;
}

void HListWidgetTitle::show (TitleObject * to) {
    ui->title->setText (to->title);
    ui->icon->setStyleSheet ("border-image: url(:/images/icon.png)");
}

void HListWidgetTitle::shadow () {
//    ui->background->setAttribute(Qt::WA_TranslucentBackground);
//    //边框阴影效果
//    QGraphicsDropShadowEffect* effect = new QGraphicsDropShadowEffect;
//    effect->setBlurRadius(6);
//    effect->setColor(Qt::black);
//    effect->setOffset(0,0);
//    ui->background->setGraphicsEffect(effect);
//    ui->background->update();
}
