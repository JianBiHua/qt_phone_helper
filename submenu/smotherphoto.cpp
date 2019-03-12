#include "smotherphoto.h"
#include "ui_smotherphoto.h"

SMOtherPhoto::SMOtherPhoto(QWidget *parent) :
    SMBase(parent),
    ui(new Ui::SMOtherPhoto)
{
    ui->setupUi(this);

    optionToolsBackGound (ui->tools);
    optionToolButtons ();
}

SMOtherPhoto::~SMOtherPhoto()
{
    delete ui;
}

void SMOtherPhoto::optionToolButtons () {
    optionToolButton (ui->tbDaochu,QIcon(":/images/icon_daochu_s.png"),"导出选中图片");
    optionToolButton (ui->tbShanchu,QIcon(":/images/icon_shanchu_s.png"),"删除");
    optionToolButton (ui->tbTianjia,QIcon(":/images/icon_tianjia_s.png"),"添加图片到手机");
    optionToolButton (ui->tbShaxin,QIcon(":/images/icon_shuaxin_s.png"),"刷新");
 }
