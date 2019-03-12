#include "tbmyphonemanager.h"
#include "ui_tbmyphonemanager.h"
#include "TitleObject.h"
#include <QLabel>
#include <qdebug.h>
#include "filemanagerdialog.h"
#include "addressbookdialog.h"
#include "paintwidget.h"
#include "phonehandler.h"
#include "threads/mutualthread.h"

tbMyPhoneManager::tbMyPhoneManager(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tbMyPhoneManager)
{
    ui->setupUi(this);
    //
    ui->background->setStyleSheet ("background-color: #FDFDFD");
    ui->listWidget->setStyleSheet ("border: none;");
    ui->listWidget->setSelectionMode (QAbstractItemView::NoSelection);
    ui->listWidget->setFocusPolicy(Qt::NoFocus);
    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem *)), this,
            SLOT(on_item_clicked(QListWidgetItem *)));
    oldIndex = -1;

    optionListWidget ();
    optionStackedWidget ();
}

void tbMyPhoneManager::setInitType (int type) {
    switch (type) {
    case 0:
        // 5
        ui->listWidget->itemClicked (ui->listWidget->item (5));
        break;
    case 1:
        ui->listWidget->itemClicked (ui->listWidget->item (7));
        break;
    case 2:
        ui->listWidget->itemClicked (ui->listWidget->item (9));
        break;
    case 3:
        break;
    case 4:
        ui->listWidget->itemClicked (ui->listWidget->item (14));
        break;
    case 5:
        ui->listWidget->itemClicked (ui->listWidget->item (15));
        break;
    case 6:
        ui->listWidget->itemClicked (ui->listWidget->item (13));
        break;
    case 7:
        ui->listWidget->itemClicked (ui->listWidget->item (16));
        break;
    case 8:
        break;
    case 9:
        break;
    case 10:
        break;
    }
}

tbMyPhoneManager::~tbMyPhoneManager()
{
    delete ui;
}

void tbMyPhoneManager::optionListWidget () {
    list.append (new TitleObject(nullptr, "欢迎使用", true));
    list.append (new TitleObject(nullptr, "我的首页", false, ":/images/icon_item_1_b.png"));
    list.append (new TitleObject(nullptr, "手机体检", false, ":/images/icon_item_2_b.png"));
    list.append (new TitleObject(nullptr, "微信清理", false, ":/images/icon_item_3_b.png"));
    list.append (new TitleObject(nullptr, "应用", true));
    list.append (new TitleObject(nullptr, "我的应用", false, ":/images/icon_item_4_b.png"));
    list.append (new TitleObject(nullptr, "可升级应用", false, ":/images/icon_item_5_b.png"));
    list.append (new TitleObject(nullptr, "管理预装应用", false, ":/images/icon_item_6_b.png"));
    list.append (new TitleObject(nullptr, "图片", true));
    list.append (new TitleObject(nullptr, "手机相册", false, ":/images/icon_item_7_b.png"));
    list.append (new TitleObject(nullptr, "其他图片", false, ":/images/icon_item_8_b.png"));
    list.append (new TitleObject(nullptr, "手机壁纸", false, ":/images/icon_item_9_b.png"));
    list.append (new TitleObject(nullptr, "其他", true));
    list.append (new TitleObject(nullptr, "我的视频", false, ":/images/icon_item_10_b.png"));
    list.append (new TitleObject(nullptr, "我的音乐", false, ":/images/icon_item_11_b.png"));
    list.append (new TitleObject(nullptr, "我的铃声", false, ":/images/icon_item_12_b.png"));
    list.append (new TitleObject(nullptr, "我的电子书", false, ":/images/icon_item_13_b.png"));
    list.append (new TitleObject(nullptr, "短信,联系人", false, ":/images/icon_item_14_b.png"));
    list.append (new TitleObject(nullptr, "文件管理", false, ":/images/icon_item_15_b.png"));

    // 刷新界面
    for (int i = 0; i < list.size(); ++i) {
        TitleObject* to = list.at(i);

        QListWidgetItem *item = new QListWidgetItem;
        if (to->isTitle) {
            item->setSizeHint(QSize(150, 47));  //每次改变Item的高度
            ui->listWidget->addItem (item);
            ui->listWidget->setItemWidget(item, titleListWidgetItem (to));
        } else {
            item->setSizeHint(QSize(150, 28));  //每次改变Item的高度
            ui->listWidget->addItem (item);
            ui->listWidget->setItemWidget(item, cellListWidgetItem (to));
        }
    }
}


QWidget * tbMyPhoneManager::titleListWidgetItem (TitleObject * to) {
    PaintWidget * t = new PaintWidget;
    t->setProperty ("tbMPM_title", true);
    t->setGeometry (0, 0, 150, 47);
    t->setBackgroundMode (-1);

    QLabel * title = new QLabel(t);
    title->setText (to->title);
    title->setGeometry (15, 22, 140, 20);

    return t;
}

QWidget * tbMyPhoneManager::cellListWidgetItem (TitleObject * to) {
    PaintWidget * t = new PaintWidget;
    t->setProperty ("tbMPM_item", true);
    t->setGeometry (0, 0, 150, 28);
    t->setBackgroundMode (0);

    QWidget * icon = new QWidget(t);
    icon->setGeometry (15, 4, 20, 20);
    icon->setStyleSheet (QString("border-image: url(%1)").arg(to->userInfo));

    QLabel * title = new QLabel(t);
    title->setText (to->title);
    title->setGeometry (45, 4, 140, 20);

    return t;
}

void tbMyPhoneManager::on_item_clicked(QListWidgetItem * item){
    int row = ui->listWidget->row (item);
    qDebug () << "on_item_clicked:: " << row;

    if (row == 1) {

        emit onBackHome ();
        return ;
    } else if (row == 17) {
        // 联系人
        showAddressBook ();
        return ;
    } else if (row == 18) {
        //文件管理.
        showFileDialog ();
        return ;
    }

    TitleObject *to = (TitleObject *) list.at (row);
    if (!to->isTitle) {
        PaintWidget * w = (PaintWidget *) ui->listWidget->itemWidget (item);
        w->setStyleSheet ("color: #FFFFFF");
        w->setBackgroundMode (1);
        ((QWidget *)w->children ().at (0))->setStyleSheet (QString("border-image: url(:/images/icon_item_%1_w.png)").arg(indexOf(row)));;
        //w->ch

        if (oldIndex != -1 && oldIndex != row) {
            w = (PaintWidget *) ui->listWidget->itemWidget (ui->listWidget->item (oldIndex));
            w->setStyleSheet ("color: #000000");
            w->setBackgroundMode (0);
            ((QWidget *)w->children ().at (0))->setStyleSheet (QString("border-image: url(:/images/icon_item_%1_b.png)").arg(indexOf(oldIndex)));;
        }
        oldIndex = row;
    }

    //
    setTabWidgetCurrentIndex (row);
}

void tbMyPhoneManager::setTabWidgetCurrentIndex (int type) {
    switch (type) {
    case 1:
        break;
    case 2:
    case 3:
        qDebug () << "setTabWidgetCurrentIndex: " << (type-2);
        stackedWidget->setCurrentIndex (type-2);
        break;
    case 5:
    case 6:
    case 7:
        stackedWidget->setCurrentIndex (type-3);
        break;
    case 9:
    case 10:
    case 11:
        stackedWidget->setCurrentIndex (type-4);
        break;
    case 13:
    case 14:
    case 15:
    case 16:
        stackedWidget->setCurrentIndex (type-5);
        break;
    }
}

int tbMyPhoneManager::indexOf (int row) {
    switch (row) {
    case 1:
    case 2:
    case 3:
        qDebug () << "row: " << row << " indexOf: " << row;
        return row;
    case 5:
    case 6:
    case 7:
        qDebug () << "row: " << row << " indexOf: " << (row-1);

        return row-1;
    case 9:
    case 10:
    case 11:
        qDebug () << "row: " << row << " indexOf: " << (row-2);

        return row-2;
    case 13:
    case 14:
    case 15:
    case 16:
        qDebug () << "row: " << row << " indexOf: " << (row-3);

        return row-3;
    }
}

void tbMyPhoneManager::optionStackedWidget () {
    stackedWidget = new QStackedWidget;
    stackedWidget->addWidget(new SMTest);
    stackedWidget->addWidget(new SMClear);
    myApp = new SMMyApp;
    stackedWidget->addWidget(myApp);
    stackedWidget->addWidget(new SMUpgrade);
    sysApp = new SMSysApp;
    stackedWidget->addWidget(sysApp);
    photo = new SMPhoto;
    stackedWidget->addWidget(photo);
    stackedWidget->addWidget(new SMOtherPhoto);
    stackedWidget->addWidget(new SMWallpaper);
    video = new SMMyVideo;
    stackedWidget->addWidget(video);
    music = new SMMyMusic;
    stackedWidget->addWidget(music);
    stackedWidget->addWidget(new SMMyRing);
    stackedWidget->addWidget(new SMMyBook);

    ui->horizontalLayout->addWidget (stackedWidget);
}

void tbMyPhoneManager::showFileDialog () {
    FileManagerDialog * fd = new FileManagerDialog;
    fd->exec ();
}

void tbMyPhoneManager::showAddressBook () {
    AddressBookDialog * fd = new AddressBookDialog;
    fd->exec ();
}


