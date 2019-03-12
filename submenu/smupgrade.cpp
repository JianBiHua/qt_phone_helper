#include "smupgrade.h"
#include "ui_smupgrade.h"

SMUpgrade::SMUpgrade(QWidget *parent) :
    SMBase(parent),
    ui(new Ui::SMUpgrade)
{
    ui->setupUi(this);

    optionToolsBackGound (ui->tools);
    optionToolButtons ();
    optionTableWidget ();
}

SMUpgrade::~SMUpgrade()
{
    delete ui;
}

void SMUpgrade::optionToolButtons () {
    optionToolButton (ui->tbShengji,QIcon(":/images/icon_upgrade_b.png"),"升级所选应用");
    optionToolButton (ui->tbHulue,QIcon(":/images/icon_hulue_s.png"),"已忽略的应用");
    optionToolButton (ui->tbShaxin,QIcon(":/images/icon_shuaxin_s.png"),"刷新");
}

void SMUpgrade::optionTableWidget () {
    QStringList header;
    ui->tableWidget->setRowCount(2);     //设置行数为10
    ui->tableWidget->setColumnCount(5);   //设置列数为5

    header<<""<<"名称"<<"新版大小"<<"提速比例"<<"操作";
    ui->tableWidget->setHorizontalHeaderLabels(header);

    ui->tableWidget->setEditTriggers ( QAbstractItemView::NoEditTriggers );//表格不可编辑
    ui->tableWidget->setColumnWidth(0, 30);
    ui->tableWidget->setColumnWidth(1, 500);
    ui->tableWidget->setColumnWidth(2, 80);
    ui->tableWidget->setColumnWidth(3, 80);
    ui->tableWidget->setColumnWidth(4, 150);
    ui->tableWidget->setShowGrid(false); //设置显示格子线
    ui->tableWidget->verticalHeader ()->hide ();

    //复选框
//    for (int i = 0; i < ui->tableWidget->columnCount (); i++) {
//        QTableWidgetItem *check=new QTableWidgetItem;
//        check->setCheckState (Qt::Checked);
//        ui->tableWidget->setItem(i,0,check); //插入复选框

//        // 设置行高
//        ui->tableWidget->setRowHeight (i, 60);
//        ui->tableWidget->setCellWidget (i, 1, cellWidget1());
//        ui->tableWidget->setCellWidget (i, 2, cellWidget2());
//        ui->tableWidget->setCellWidget (i, 3, cellWidget3());
//        ui->tableWidget->setCellWidget (i, 4, cellWidget4());
//    }
}

