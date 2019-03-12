#include "smmyvideo.h"
#include "ui_smmyvideo.h"
#include <QLabel>

SMMyVideo::SMMyVideo(QWidget *parent) :
    SMBase(parent),
    ui(new Ui::SMMyVideo)
{
    ui->setupUi(this);

    optionToolsBackGound (ui->tools);
    optionToolButtons ();

    // PhoneHandler::getInstance ()->resetVideos ();
    connect (PhoneHandler::getInstance (), SIGNAL(onVideosChanged()), this, SLOT(on_videos_changed()));
}

SMMyVideo::~SMMyVideo()
{
    delete ui;
}

void SMMyVideo::optionToolButtons () {
    optionToolButton (ui->tbShangchuan,QIcon(":/images/icon_tianjia_s.png"),"上传到手机");
    optionToolButton (ui->tbShanchu,QIcon(":/images/icon_shanchu_s.png"),"删除");
    optionToolButton (ui->tbFasong,QIcon(":/images/icon_daochu_s.png"),"发送到电脑");
    optionToolButton (ui->tbShuaxin,QIcon(":/images/icon_shuaxin_s.png"),"刷新");
 }

void SMMyVideo::optionTableWidget () {
    QStringList header;
    ui->tableWidget->setRowCount(PhoneHandler::getInstance ()->listVideos.size ());     //设置行数为10
    ui->tableWidget->setColumnCount(7);

    header<<""<<"标题"<<"位置"<<"类型"<<"长度"<<"大小"<<"添加时间";
    ui->tableWidget->setHorizontalHeaderLabels(header);

    ui->tableWidget->setEditTriggers ( QAbstractItemView::NoEditTriggers );//表格不可编辑
    ui->tableWidget->setColumnWidth(0, 30);
    ui->tableWidget->setColumnWidth(1, 200);
    ui->tableWidget->setColumnWidth(2, 50);
    ui->tableWidget->setColumnWidth(3, 80);
    ui->tableWidget->setColumnWidth(4, 80);
    ui->tableWidget->setColumnWidth(5, 50);
    ui->tableWidget->setColumnWidth(6, 200);
    ui->tableWidget->setShowGrid(false); //设置显示格子线
    ui->tableWidget->verticalHeader ()->hide ();

    //复选框
    for (int i = 0; i < PhoneHandler::getInstance ()->listVideos.size (); i++) {
        HVideoObject * audio = PhoneHandler::getInstance ()->listVideos.at (i);

        QTableWidgetItem *check=new QTableWidgetItem;
        check->setCheckState (Qt::Checked);
        ui->tableWidget->setItem(i,0,check); //插入复选框

        // 设置行高
        ui->tableWidget->setRowHeight (i, 30);

        //
        QLabel *lb = new QLabel;
        lb->setText (audio->name);
        ui->tableWidget->setCellWidget (i, 1, lb);
        lb = new QLabel;
        lb->setText ("系统");
        ui->tableWidget->setCellWidget (i, 2, lb);
        lb = new QLabel;
        lb->setText ("");
        ui->tableWidget->setCellWidget (i, 3, lb);
        lb = new QLabel;
        ui->tableWidget->setCellWidget (i, 4, lb);
        lb = new QLabel;
        lb->setText (audio->size);
        ui->tableWidget->setCellWidget (i, 5, lb);
        lb = new QLabel;
        lb->setText ("2015/01/01");
        ui->tableWidget->setCellWidget (i, 6, lb);
    }
}


void SMMyVideo::on_tbShuaxin_clicked()
{
    PhoneHandler::getInstance ()->resetVideos ();
}

void SMMyVideo::on_videos_changed () {
    ui->tableWidget->clear ();
    optionTableWidget ();
}
