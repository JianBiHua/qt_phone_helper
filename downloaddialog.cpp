#include "downloaddialog.h"
#include "ui_downloaddialog.h"
#include <qDebug>
#include <QDesktopServices>
#include <QProcess>
#include <QUrl>

DownLoadDialog::DownLoadDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DownLoadDialog)
{
    ui->setupUi(this);
    // 不显示状态栏
    // 设置窗体标题栏隐藏和窗口是否有任务栏图标
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);

    //
    ui->lbTitle->setStyleSheet ("color:#FFFFFF");

    //
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/images/LoginBK.jpg")));
    this->setPalette (palette);

    QPalette palette2;
    palette2.setColor(QPalette::Background, QColor(0xFD,0xFD,0xFD));
    ui->bottomWidget->setPalette (palette2);

    //
    optionToolButton (ui->tbGoOn, QIcon(":/images/LoginBK.jpg"), tr("继续所有任务"));
    optionToolButton (ui->tbClear, QIcon(":/images/LoginBK.jpg"), tr("清除所有任务"));
    // 关闭按钮
    ui->pbClose->setStyleSheet (QString("border-image: url(:/images/icon_close.png)"));
    // 图标
    ui->icon->setStyleSheet ("border-image: url(:/images/icon.png)");

    //
    optionTableWidget ();
}

DownLoadDialog::~DownLoadDialog()
{
    delete ui;
}

void DownLoadDialog::on_pbClose_clicked()
{
    this->close ();
}

void DownLoadDialog::on_tbGoOn_clicked()
{

}

void DownLoadDialog::optionToolButton (QToolButton * tb, QIcon icon, QString text) {
    QAction *pAction = new QAction(this);
    pAction->setText(text);
    pAction->setIcon(icon);
    tb->setIconSize(QSize(48, 48));
    tb->setDefaultAction(pAction);
    tb->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tb->setProperty ("download", true);
}

void DownLoadDialog::optionTableWidget () {
    QStringList header;
    ui->tableWidget->setRowCount(2);     //设置行数为10
    ui->tableWidget->setColumnCount(5);   //设置列数为5

    header<<""<<"任务名称"<<"大小"<<"进度"<<"操作";
    ui->tableWidget->setHorizontalHeaderLabels(header);
//    ui->tableWidget->setItem(0,0,new QTableWidgetItem("Jan"));
//    ui->tableWidget->setItem(1,0,new QTableWidgetItem("Feb"));
//    ui->tableWidget->setItem(2,0,new QTableWidgetItem("Mar"));

//    ui->tableWidget->setItem(0,1,new QTableWidgetItem(QIcon("images/IED.png"), "Jan's month"));
//    ui->tableWidget->setItem(1,1,new QTableWidgetItem(QIcon("images/IED.png"), "Feb's month"));
//    ui->tableWidget->setItem(2,1,new QTableWidgetItem(QIcon("images/IED.png"), "Mar's month"));

    ui->tableWidget->setEditTriggers ( QAbstractItemView::NoEditTriggers );//表格不可编辑
    ui->tableWidget->setColumnWidth(0, 30);
    ui->tableWidget->setColumnWidth(1, 150);
    ui->tableWidget->setColumnWidth(2, 80);
    ui->tableWidget->setColumnWidth(3, 279);
    ui->tableWidget->setColumnWidth(4, 110);
    ui->tableWidget->setShowGrid(true); //设置显示格子线
    ui->tableWidget->verticalHeader ()->hide ();

    //复选框
    for (int i = 0; i < ui->tableWidget->columnCount (); i++) {
        QTableWidgetItem *check=new QTableWidgetItem;
        check->setCheckState (Qt::Checked);
        ui->tableWidget->setItem(i,0,check); //插入复选框

        // 设置行高
        ui->tableWidget->setRowHeight (i, 60);
        ui->tableWidget->setCellWidget (i, 1, cellWidget1());
        ui->tableWidget->setCellWidget (i, 2, cellWidget2());
        ui->tableWidget->setCellWidget (i, 3, cellWidget3());
        ui->tableWidget->setCellWidget (i, 4, cellWidget4());
    }
}

QWidget* DownLoadDialog::cellWidget1() {
    QWidget *w = new QWidget;

    QWidget *icon = new QWidget (w);
    icon->setGeometry (5, 15, 30, 30);
    icon->setStyleSheet ("background-image: url(:/images/download_icon.png)");

    QLabel *title = new QLabel (w);
    title->setText ("塔王之王");
    title->setGeometry (40, 15, 120, 30);

    return w;
}

QWidget* DownLoadDialog::cellWidget2() {
    QLabel * lb = new QLabel;
    lb->setText ("64.5M");
    lb->setAlignment (Qt::AlignVCenter);
    lb->setGeometry (0, 0, 80, 60);
    return lb;
}

QWidget* DownLoadDialog::cellWidget3() {
    QWidget *w = new QWidget;
    w->setGeometry (0, 0, 260, 60);

    QWidget *icon = new QWidget (w);
    icon->setGeometry (5, 20, 20, 20);
    icon->setStyleSheet ("background-image: url(:/images/download_success.png)");

    QLabel * lb = new QLabel(w);
    lb->setText ("文件发送成功");
    lb->setAlignment (Qt::AlignVCenter);
    lb->setGeometry (30, 0, 200, 60);

    return w;
}

QWidget * DownLoadDialog::cellWidget4() {
    QWidget *w = new QWidget;
 //   QWidget *background = new QWidget(w);
//    background->setGeometry (5, 15, 90, 30);
//    background->setStyleSheet ("background-color: #F9F9F9; border-radius: 7px; border: 1px solid #e1e0e0;");

    QPushButton *r = new QPushButton (w);
    r->setGeometry (10, 15, 30, 30);
    r->setIcon(QIcon(":/images/download_refresh.png"));
    r->setIconSize(QSize(20, 20));
    r->setStyleSheet ("border: 1px solid #e1e0e0;border-top-left-radius:5px;border-bottom-left-radius:5px;");
    connect (r, SIGNAL(clicked()), this, SLOT(on_pushbtn_clicked()));
    r->setProperty ("key", 0);
    QPushButton *c = new QPushButton (w);
    c->setGeometry (40, 15, 30, 30);
    c->setIcon(QIcon(":/images/download_close.png"));
    c->setIconSize(QSize(20, 20));
    c->setStyleSheet ("border: 1px solid #e1e0e0;");
    connect (c, SIGNAL(clicked()), this, SLOT(on_pushbtn_clicked()));
    c->setProperty ("key", 1);
    QPushButton *f = new QPushButton (w);
    f->setGeometry (70, 15, 30, 30);
    f->setIcon(QIcon(":/images/download_file.png"));
    f->setIconSize(QSize(20, 20));
    f->setProperty ("key", 2);
    f->setStyleSheet ("border: 1px solid #e1e0e0;border-top-right-radius:5px;border-bottom-right-radius:5px;");
    connect (f, SIGNAL(clicked()), this, SLOT(on_pushbtn_clicked()));

    return w;
}

void DownLoadDialog::on_pushbtn_clicked() {
    qDebug () <<"on_pushbtn_clicked: " << sender ();
    QPushButton * pb = (QPushButton *)sender ();
    qDebug () <<"property: " << pb->property ("key").toInt ();

    int index = pb->property ("key").toInt ();
    if (index == 1) {
        // 删除
        ui->tableWidget->removeRow (0);
    } else if (index == 2) {
        //打开一个路径
        QString runPath = QCoreApplication::applicationDirPath(); //获取exe路劲
        qDebug () << "打开一个路径"<<runPath;
        //QDesktopServices::openUrl(QUrl("/", QUrl::TolerantMode));
        //QString filePath = QString("/Users/Yueer/Documents/SourceCode/QTProjects/build-PhoneHandler-Desktop_Qt_5_8_0_clang_64bit-Release/");
        //qDebug () <<"QUrl::fromLocalFile(filePath): " << QUrl::fromLocalFile(filePath);
        QDesktopServices::openUrl(QUrl::fromLocalFile(runPath));
    }
}
