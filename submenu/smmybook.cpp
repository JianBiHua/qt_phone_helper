#include "smmybook.h"
#include "ui_smmybook.h"

SMMyBook::SMMyBook(QWidget *parent) :
    SMBase(parent),
    ui(new Ui::SMMyBook)
{
    ui->setupUi(this);

    optionToolsBackGound (ui->tools);
    optionToolButtons ();
}

SMMyBook::~SMMyBook()
{
    delete ui;
}

void SMMyBook::optionToolButtons () {
    optionToolButton (ui->tbShangchuan,QIcon(":/images/icon_tianjia_s.png"),"上传到手机");
    optionToolButton (ui->tbShanchu,QIcon(":/images/icon_shanchu_s.png"),"删除");
    optionToolButton (ui->tbFasong,QIcon(":/images/icon_daochu_s.png"),"发送到电脑");
    optionToolButton (ui->tbShuaxin,QIcon(":/images/icon_shuaxin_s.png"),"刷新");
 }
