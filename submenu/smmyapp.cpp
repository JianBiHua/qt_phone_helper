#include "smmyapp.h"
#include "ui_smmyapp.h"
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QPushButton>
#include "apptablewidget.h"

SMMyApp::SMMyApp(QWidget *parent) :
    SMBase(parent),
    ui(new Ui::SMMyApp)
{
    ui->setupUi(this);

    optionToolsBackGound (ui->tools);
    optionToolButtons ();
    optionTableWidget ();

//    PhoneHandler::getInstance ()->resetApps ();
    connect (PhoneHandler::getInstance (), SIGNAL(onAppsChanged()), this, SLOT(on_apps_changed()));
}

SMMyApp::~SMMyApp()
{
    delete ui;
}

void SMMyApp::optionToolButtons () {
    optionToolButton (ui->tbDaochu,QIcon(":/images/icon_daochu_s.png"),"导出应用");
    optionToolButton (ui->tbXiezai,QIcon(":/images/icon_shanchu_s.png"),"卸载应用");
    optionToolButton (ui->tbAnzhuang,QIcon(":/images/icon_tianjia_s.png"),"安装本地应用");
    optionToolButton (ui->tbSdcard,QIcon(":/images/icon_sdcard2_s.png"),"移到SD卡");
    optionToolButton (ui->tbShuaxin,QIcon(":/images/icon_shuaxin_s.png"),"刷新");
 }

void SMMyApp::optionTableWidget () {
    QStringList header;
    ui->tableWidget->setRowCount(PhoneHandler::getInstance ()->listApps.size ());     //设置行数为10
    ui->tableWidget->setColumnCount(5);   //设置列数为5
    ui->tableWidget->setSelectionBehavior ( QAbstractItemView::SelectRows); //设置选择行为，以行为单位
    ui->tableWidget->setSelectionMode ( QAbstractItemView::SingleSelection); //设置选择模式，选择单行

    header<<""<<"名称"<<"大小"<<"位置"<<"操作";
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
    for (int i = 0; i < PhoneHandler::getInstance ()->listApps.size (); i++) {
        HAppObject * app = PhoneHandler::getInstance ()->listApps.at (i);

        QTableWidgetItem *check=new QTableWidgetItem;
        check->setCheckState (Qt::Checked);
        ui->tableWidget->setItem(i,0,check); //插入复选框

        // 设置行高
        ui->tableWidget->setRowHeight (i, 30);

        //
        QLabel *lb = new QLabel;
        lb->setText (app->name);
        ui->tableWidget->setCellWidget (i, 1, lb);
        lb = new QLabel;
        lb->setText (app->size);
        ui->tableWidget->setCellWidget (i, 2, lb);
        lb = new QLabel;
        lb->setText (app->location);
        ui->tableWidget->setCellWidget (i, 3, lb);
        QWidget * w = new QWidget;

        QPushButton * pb = new QPushButton(w);
        pb->setGeometry (0, 0, 150, 30);
        pb->setText (tr("卸载应用"));
        pb->setProperty ("index", i);
        //pb->setGeometry ("index", i);
        ui->tableWidget->setCellWidget (i, 4, w);
        connect (pb, SIGNAL(clicked(bool)), this, SLOT(on_uninstall_pb_clicked(bool)));
    }
}

void SMMyApp::on_tbShuaxin_clicked()
{
    PhoneHandler::getInstance ()->resetApps ();
}

void SMMyApp::on_apps_changed () {
    ui->tableWidget->clear ();

    optionTableWidget ();
}


void SMMyApp::on_tbAnzhuang_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Apk"), ".", tr("安卓应用(*.apk)"));
    if(path.length() == 0) {

        // QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    } else {
        PhoneHandler::getInstance ()->install (path);
        // QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path);
        qDebug () << "package.install: " << path;
        //
        PhoneHandler::getInstance ()->resetApps ();
    }
}

void SMMyApp::on_uninstall_pb_clicked(bool b) {
    QPushButton * pb = (QPushButton *) sender ();

    HAppObject * app = PhoneHandler::getInstance ()->listApps.at (pb->property ("index").toInt ());
    // 卸载应用
    PhoneHandler::getInstance ()->uninstall (app->package);
    qDebug () << "package.uninstall: " << app->package;
    //
    PhoneHandler::getInstance ()->resetApps ();
}
