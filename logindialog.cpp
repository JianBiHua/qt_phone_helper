#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDesktopServices>
#include <QUrl>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    // 不显示状态栏
    // 设置窗体标题栏隐藏和窗口是否有任务栏图标
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);

    //
    ui->topWidget->setAutoFillBackground(true);
    ui->mainWidget->setAutoFillBackground(true);

    //
    ui->lbTitle->setStyleSheet ("color:#FFFFFF");

    //
//    ui->topWidget->setStyleSheet (QString("background-color: rgb(66, 183, 106)"));
    ui->topWidget->setStyleSheet (QString("background-image: url(:/images/LoginBanner.png)"));
    //
    QPalette palette2;
    palette2.setColor(QPalette::Background, QColor(0xFD,0xFD,0xFD));
    ui->mainWidget->setPalette (palette2);

    // 关闭按钮
    ui->pbClose->setStyleSheet (QString("border-image: url(:/images/icon_close.png)"));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pbLogin_clicked()
{
    this->close ();
}

void LoginDialog::on_pbClose_clicked()
{
    this->close ();
}

void LoginDialog::on_pbRegister_clicked()
{
    const QUrl url("http://i.360.cn/reg?src=360zhushou&mid=4bf713720bc3e781be1a94f8ee88fff5");
    QDesktopServices::openUrl(url);
}

void LoginDialog::on_pbFindPsw_clicked()
{
    const QUrl url("http://i.360.cn/findpwd/?src=360zhushou&mid=4bf713720bc3e781be1a94f8ee88fff5");
    QDesktopServices::openUrl(url);
}
