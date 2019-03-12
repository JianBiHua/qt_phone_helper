#include "smsysapp.h"
#include "ui_smsysapp.h"

SMSysApp::SMSysApp(QWidget *parent) :
    SMBase(parent),
    ui(new Ui::SMSysApp)
{
    ui->setupUi(this);

    optionToolsBackGound (ui->top);
    optionToolButtons ();
    optionTableWidget ();

    //
    ui->icon->setStyleSheet ("border-image: url(:/images/icon_i.png)");
    //PhoneHandler::getInstance ()->resetSysApps ();
    connect (PhoneHandler::getInstance (), SIGNAL(onSysAppsChanged()), this, SLOT(on_sys_apps_changed()));
}

SMSysApp::~SMSysApp()
{
    delete ui;
}

void SMSysApp::optionToolButtons () {
    optionToolButton (ui->tbHuanyuan,QIcon(":/images/icon_huanyuan_s.png"),"一键还原");
    optionToolButton (ui->tbShuaxin,QIcon(":/images/icon_shuaxin_s.png"),"刷新");
}

void SMSysApp::optionTableWidget () {
    QStringList header;
    ui->tableWidget->setRowCount(PhoneHandler::getInstance ()->listSysApps.size ());     //设置行数为10
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行

    header<<"软件名称"<<"大小"<<"是否开启"<<"操作";
    ui->tableWidget->setHorizontalHeaderLabels(header);

    ui->tableWidget->setEditTriggers ( QAbstractItemView::NoEditTriggers );//表格不可编辑
    ui->tableWidget->setColumnWidth(0, 500);
    ui->tableWidget->setColumnWidth(1, 100);
    ui->tableWidget->setColumnWidth(2, 150);
    ui->tableWidget->setColumnWidth(3, 150);
    ui->tableWidget->setShowGrid(false); //设置显示格子线
    ui->tableWidget->verticalHeader ()->hide ();

    //复选框
    for (int i = 0; i < PhoneHandler::getInstance ()->listSysApps.size (); i++) {
        HAppObject * app = PhoneHandler::getInstance ()->listSysApps.at (i);

        QTableWidgetItem *check=new QTableWidgetItem;
        check->setCheckState (Qt::Checked);
        check->setText (app->name);
        ui->tableWidget->setItem(i,0,check); //插入复选框

        // 设置行高
        ui->tableWidget->setRowHeight (i, 30);

        //
        QLabel *lb = new QLabel;
        lb->setText (app->size);
        ui->tableWidget->setCellWidget (i, 1, lb);
        lb = new QLabel;
        lb->setText (app->location);
        ui->tableWidget->setCellWidget (i, 2, lb);
        lb = new QLabel;
        ui->tableWidget->setCellWidget (i, 3, lb);
    }
}

void SMSysApp::on_tbShuaxin_clicked()
{
    PhoneHandler::getInstance ()->resetSysApps ();
}

void SMSysApp::on_sys_apps_changed () {
    ui->tableWidget->clear ();
    optionTableWidget ();
}
