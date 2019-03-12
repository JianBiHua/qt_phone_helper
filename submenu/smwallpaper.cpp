#include "smwallpaper.h"
#include "ui_smwallpaper.h"

SMWallpaper::SMWallpaper(QWidget *parent) :
    SMBase(parent),
    ui(new Ui::SMWallpaper)
{
    ui->setupUi(this);

    optionToolsBackGound (ui->tools);
    optionToolButtons ();
}

SMWallpaper::~SMWallpaper()
{
    delete ui;
}

void SMWallpaper::optionToolButtons () {
    optionToolButton (ui->tbDaochu,QIcon(":/images/icon_daochu_s.png"),"导出选中图片");
    optionToolButton (ui->tbShanchu,QIcon(":/images/icon_shanchu_s.png"),"删除");
    optionToolButton (ui->tbTianjia,QIcon(":/images/icon_tianjia_s.png"),"添加图片到手机");
    optionToolButton (ui->tbShaxin,QIcon(":/images/icon_shuaxin_s.png"),"刷新");
 }
