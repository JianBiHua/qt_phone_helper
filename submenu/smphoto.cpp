#include "smphoto.h"
#include "ui_smphoto.h"

SMPhoto::SMPhoto(QWidget *parent) :
    SMBase(parent),
    ui(new Ui::SMPhoto)
{
    ui->setupUi(this);

    optionToolsBackGound (ui->tools);
    optionToolButtons ();

    connect (PhoneHandler::getInstance (), SIGNAL(onPhotosChanged()), this, SLOT(on_photos_changed()));
}

SMPhoto::~SMPhoto()
{
    delete ui;
}

void SMPhoto::optionToolButtons () {
    optionToolButton (ui->tbDaochu,QIcon(":/images/icon_daochu_s.png"),"导出选中图片");
    optionToolButton (ui->tbShanchu,QIcon(":/images/icon_shanchu_s.png"),"删除");
    optionToolButton (ui->tbTianjia,QIcon(":/images/icon_tianjia_s.png"),"添加图片到手机");
    optionToolButton (ui->tbShaxin,QIcon(":/images/icon_shuaxin_s.png"),"刷新");
 }

void SMPhoto::on_tbShaxin_clicked()
{
    PhoneHandler::getInstance ()->resetPhotos ();
}

void SMPhoto::on_photos_changed () {

}
