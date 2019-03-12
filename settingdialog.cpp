#include "settingdialog.h"
#include "ui_settingdialog.h"
#include <qdebug.h>

SettingDialog::SettingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingDialog)
{
    ui->setupUi(this);

    // 不显示状态栏
    // 设置窗体标题栏隐藏和窗口是否有任务栏图标
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);

    //
    ui->topWidget->setAutoFillBackground(true);
    ui->mainWidget->setAutoFillBackground(true);

    //
    ui->title->setStyleSheet ("color:#FFFFFF");
    ui->topWidget->setStyleSheet (QString("background-color: rgb(66, 183, 106)"));
    ui->icon->setStyleSheet (QString("border-image: url(:/images/icon.png)"));
    ui->bottomWidget->setStyleSheet (QString("background-color: rgb(241, 243, 245)"));
    ui->pbClose->setStyleSheet (QString("border-image: url(:/images/icon_close.png)"));

    // 显示
    optionListWidget ();
    optionStackedWidget ();
}

void SettingDialog::optionListWidget () {

    // 用qss
    ui->listWidget->setProperty ("settingdialog", true);
    connect (ui->listWidget, SIGNAL(itemPressed(QListWidgetItem *)),
             this, SLOT(on_listwidget_selected(QListWidgetItem *)));

    QStringList itemTexts;
    itemTexts <<"常规设置"<<"目录设置";

    for (int i = 0; i < itemTexts.size (); i++) {
        QListWidgetItem *item = new QListWidgetItem(ui->listWidget);
        item->setText (itemTexts.at (i));
        item->setSizeHint (QSize (100, 35));
    }

    // 默认点击第一项.
    ui->listWidget->setCurrentRow (0);
}

void SettingDialog::optionStackedWidget () {

}

SettingDialog::~SettingDialog()
{
    delete ui;
}

void SettingDialog::on_pbClose_clicked()
{
    this->close ();
}

void SettingDialog::on_pbEnter_clicked()
{
    this->close ();
}

void SettingDialog::on_pbCancel_clicked()
{
    this->close ();
}

void SettingDialog::on_listwidget_selected (QListWidgetItem * item) {
    qDebug () << "on_listwidget_selected";
    //stackedWidget->setCurrentIndex (ui->listWidget->row (item));
}
