#include "tbmyphone.h"
#include "ui_tbmyphone.h"
#include "threads/connectionthread.h"
#include <QMouseEvent>
#include "filemanagerdialog.h"
#include "addressbookdialog.h"

TBMyPhone::TBMyPhone(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TBMyPhone)
{
    ui->setupUi(this);

    //
    QFont font3;
    font3.setFamily(QString::fromUtf8("Tahoma"));
    font3.setPointSize(30);
    font3.setBold(true);
    ui->title->setFont (font3);

    QFont font4;
    font4.setFamily(QString::fromUtf8("Tahoma"));
    font4.setPointSize(50);
    ui->scores->setFont (font4);
    ui->scores->setStyleSheet ("color: #42B76A;");
    ui->subtitle->setStyleSheet ("color: #A2A3A8;");

    ui->widget_3->setStyleSheet ("border-radius: 15px;border: 1px solid #e1e0e0;");
    ui->widget->setStyleSheet ("border-image: url(:/images/connectPhone.png)");
    ui->pbConnectPhone->setStyleSheet ("border-image: url();background-color: #3F000000;color: #FFFFFF; border-radius: 10px; border: solid #e1e0e0;");
//    ui->apps->setStyleSheet ("color:#FFFFFF;  font-family: \"微软雅黑\"; font-size: 18px;font-weight:bold;  ");
//    ui->installApps->setStyleSheet ("color:#FFFFFF; background-color: #F79A32; font-family: \"微软雅黑\"; font-size: 18px;font-weight:bold;  ");
//    ui->myPhoto->setStyleSheet ("color:#FFFFFF; background-color: #72C046; font-family: \"微软雅黑\"; font-size: 18px;font-weight:bold;  ");
//    ui->files->setStyleSheet ("color:#FFFFFF; background-color: #9493E1; font-family: \"微软雅黑\"; font-size: 18px;font-weight:bold;  ");
    ui->pbTest->setProperty ("tbmyphone_test", true);
    ui->apps->setProperty ("tbmyphone_apps", true);
    ui->installApps->setProperty ("tbmyphone_installApps", true);
    ui->myPhoto->setProperty ("tbmyphone_myPhoto", true);
    ui->files->setProperty ("tbmyphone_files", true);

    ui->label->setProperty ("tbmyphone_label", true);
    ui->label_2->setProperty ("tbmyphone_label", true);
    ui->label_3->setProperty ("tbmyphone_label", true);
    ui->label_4->setProperty ("tbmyphone_label", true);

    this->setMouseTracking (true);

//    ui->apps->setAutoFillBackground(true);//这个语句很重要，没有的话，子widget背景色修改不成功
//     QPalette myPalette;
//     myPalette.setBrush(backgroundRole(),QColor(10,25,69));
//     ui->apps->setPalette(myPalette);

    optionListWidget ();

    connect (ui->widget, SIGNAL(onScreenshotConnect(bool)), this, SLOT(on_pbScreenShot_connect(bool)));

    ConnectionThread *connecttest = new ConnectionThread;
    connecttest->start();
    connect(connecttest, SIGNAL(connectionChanged(int,QString)), this, SLOT(slotConnectionChanged(int,QString)));

    //
    ui->home->setHidden (false);
    ui->next->setHidden (true);
    connect (ui->next, SIGNAL(onBackHome()), this, SLOT(on_back_home()));
}


TBMyPhone::~TBMyPhone()
{
    delete ui;
}

void TBMyPhone::optionListWidget () {
    // 用qss
    ui->listWidget->setProperty ("TBMyPhone_listwidget", true);
//    connect (ui->listWidget, SIGNAL(itemPressed(QListWidgetItem *)),
//             this, SLOT(on_listwidget_selected(QListWidgetItem *)));
    QStringList itemTexts;
    itemTexts <<"音乐"<<"铃声"<<"视频"<<"电子书"<<"短信"<<"联系人";

    for (int i = 0; i < itemTexts.size (); i++) {
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint (QSize (200, 44));

        QWidget * widget = new QWidget;
        widget->setProperty ("tbmyphone_listitem", true);

        QLabel * lb = new QLabel(widget);
        lb->setText (itemTexts.at (i));
        lb->setAlignment (Qt::AlignVCenter);
        lb->setStyleSheet ("color: #FFFFFF ");
        lb->setGeometry (25, 0, 190, 44);

        if (i != itemTexts.size ()-1) {
            QWidget * line = new QWidget(widget);
            line->setGeometry (25, 43, 190, 44);
            line->setStyleSheet ("background-color: #1FFFFFFF");
        }

        ui->listWidget->addItem (item);
        ui->listWidget->setItemWidget (item, widget);
    }

    connect (ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)),
             this, SLOT(on_listwidget_clicked(QListWidgetItem*)));
}

void TBMyPhone::on_pbFresh_clicked()
{
    // 屏幕刷新
    ui->widget->takeScreenshot ();
}


void TBMyPhone::on_pbScreenShot_clicked()
{
    // 屏幕截屏.
    ui->widget->screenshotPhoto ();
}

void TBMyPhone::on_pbScreenShot_connect(bool success) {
    qDebug () << "on_pbScreenShot_connect: " << success;
    ui->pbConnectPhone->setHidden (success);
}

void TBMyPhone::slotConnectionChanged(int type,QString msg) {
    qDebug () << "slotConnectionChanged: (" << type<<"):: " << msg;
}

void TBMyPhone::mousePressEvent(QMouseEvent *ev)
{
    if (ui->apps->geometry ().contains (ev->pos ())) {
        qDebug () << "clicked apps: ";
//        emit onMyPhoneDidSelected (0);
        ui->next->setInitType (0);
        showHome (false);
    } else if (ui->installApps->geometry ().contains (ev->pos ())) {
        qDebug () << "clicked installApps: ";
//        emit onMyPhoneDidSelected (1);
        ui->next->setInitType (1);
        showHome (false);
    } else if (ui->myPhoto->geometry ().contains (ev->pos ())) {
        qDebug () << "clicked myPhoto: ";
//        emit onMyPhoneDidSelected (2);
        ui->next->setInitType (2);
        showHome (false);
    } else if (ui->files->geometry ().contains (ev->pos ())) {
        qDebug () << "clicked files: ";
//        emit onMyPhoneDidSelected (3);
        //showHome (false);
        //
        showFileDialog ();
    }
}

void TBMyPhone::on_listwidget_clicked(QListWidgetItem* item) {
    qDebug () << "on_listwidget_clicked: " <<  (ui->listWidget->currentRow ()+4);
    // 从第四个开始
//    emit onMyPhoneDidSelected (ui->listWidget->currentRow ()+4);
    if (ui->listWidget->currentRow () < 4) {
        showHome (false);
        ui->next->setInitType (ui->listWidget->currentRow ()+4);
    } else {
        showAddressBook (!(ui->listWidget->currentRow () - 4));
    }
}

void TBMyPhone::reset () {
    showHome (true);
}

void TBMyPhone::showHome (bool s) {
    qDebug () << "showHome: " << s;
    ui->home->setVisible (s);
    ui->next->setVisible (!s);
}

void TBMyPhone::on_back_home () {
    reset ();
}

void TBMyPhone::showFileDialog () {
    FileManagerDialog * fd = new FileManagerDialog;
    fd->exec ();
}

void TBMyPhone::showAddressBook (int type) {
    AddressBookDialog * fd = new AddressBookDialog;
    // type: 0 联系人,  1: 短信
    fd->setType (type);
    fd->exec ();
}
