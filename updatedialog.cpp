#include "updatedialog.h"
#include "ui_updatedialog.h"

UpdateDialog::UpdateDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UpdateDialog)
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
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/images/LoginBanner.png")));
    ui->topWidget->setPalette (palette);
    //
    QPalette palette2;
    palette2.setColor(QPalette::Background, QColor(0xFD,0xFD,0xFD));
    ui->mainWidget->setPalette (palette2);

    // 关闭按钮
    ui->pbClose->setStyleSheet (QString("border-image: url(:/images/icon_close.png)"));
    ui->icon->setStyleSheet ("border-image: url(:/images/icon.png)");
}

UpdateDialog::~UpdateDialog()
{
    delete ui;
}

void UpdateDialog::on_pushButton_clicked()
{
    this->close ();
}

void UpdateDialog::on_pbClose_clicked()
{
    this->close ();
}
