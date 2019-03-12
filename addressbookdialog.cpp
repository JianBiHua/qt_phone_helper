#include "addressbookdialog.h"
#include "ui_addressbookdialog.h"
#include <qdebug.h>
#include <QCheckBox>

AddressBookDialog::AddressBookDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddressBookDialog)
{
    ui->setupUi(this);
    oldAddressIndex = -1;

    // 不显示状态栏
    // 设置窗体标题栏隐藏和窗口是否有任务栏图标
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);

    //
    ui->title->setStyleSheet ("color:#FFFFFF");
    //
    ui->top->setStyleSheet (QString("background-color: rgb(66, 183, 106)"));
    // 关闭按钮
    ui->pbClose->setStyleSheet ("border-image: url(:/images/icon_close.png)");
    ui->tabWidget->setTabText (0, "联系人");
    ui->tabWidget->setTabText (1, "短信");
    ui->icon->setStyleSheet ("border-image: url(:/images/icon.png)");
    ui->tools->setStyleSheet ("background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #F1F1F1, stop:1 #FDFDFD");
    ui->tools2->setStyleSheet ("background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #F1F1F1, stop:1 #FDFDFD");
    ui->widget_7->setStyleSheet ("background-color: #FFFFFF");
    //
    ui->pbSms->setStyleSheet ("border-image: url(:/images/icon_sms_s.png);");
    ui->pbSend->setStyleSheet ("border: 1px solid #e1e0e0;border-radius:5px;");
    //
    ui->cardIcon->setStyleSheet ("border-image: url(:/images/icon_head.png)");
    //ui->twLianxiren->setStyleSheet ("border: 1px solid #e9e9ea;");
    ui->treeWidget->setFocusPolicy(Qt::NoFocus);
    ui->smsItemListWidget->setFocusPolicy(Qt::NoFocus);
    ui->smsListWidget->setFocusPolicy (Qt::NoFocus);
    ui->lianxirensmsListWidget->setFocusPolicy (Qt::NoFocus);

    qDebug () << "end AddressBookDialog";

    optionLianxiren ();
    optionDuanxin ();
    optionTreeWidget ();

    //测试数据
    optionSmsListWidget ();

    //测试数据
    optionLianxirenTableWidget ();

    //
    //PhoneHandler::getInstance ()->resetAddressBook ();
    // PhoneHandler::getInstance ()->resetSms ();
    connect (PhoneHandler::getInstance (), SIGNAL(onAddressBookChanged()), this, SLOT(on_addressbook_changed()));
    connect (PhoneHandler::getInstance (), SIGNAL(onSmsChanged()), this, SLOT(on_sms_changed()));

    ui->lianxirensmsListWidget->setSelectionMode (QAbstractItemView::NoSelection);
    ui->lianxirensmsListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->smsListWidget->setSelectionMode (QAbstractItemView::NoSelection);
    ui->smsListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    connect (ui->lianxirensmsListWidget,
             SIGNAL(itemClicked(QListWidgetItem*)),
             this,
             SLOT(on_lianxiren_item_clicked(QListWidgetItem*)));
    connect (ui->smsListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
             this, SLOT(on_smslistwidget_clicked(QListWidgetItem*)));
}

void AddressBookDialog::setType (int type) {
    qDebug () << "setType: " << type;
    ui->tabWidget->setCurrentIndex (type);
}

AddressBookDialog::~AddressBookDialog()
{
    delete ui;
}

void AddressBookDialog::on_pbClose_clicked()
{
    this->close ();
}

void AddressBookDialog::optionLianxiren () {
    optionToolButton (ui->tbXinjian1, QIcon(":/images/icon_xlianxiren_s.png"), "新建联系人");
    optionToolButton (ui->tbDaoruDaoChu1, QIcon(":/images/icon_daorudaochu_s.png"), "导入/导出");
    optionToolButton (ui->tbShanchu1, QIcon(":/images/icon_shanchu_s.png"), "删除");
    optionToolButton (ui->tbShaxin1, QIcon(":/images/icon_shuaxin_s.png"), "刷新");

    //
    optionToolButton (ui->tbCard, QIcon(":/images/icon_card_s.png"), "发送名片");
    optionToolButton (ui->tbEdit, QIcon(":/images/icon_edit_s.png"), "编辑");
}

void AddressBookDialog::optionDuanxin () {
    optionToolButton (ui->tbXinjian, QIcon(":/images/icon_xduanxin_s.png"), "新建短信");
    optionToolButton (ui->tbDaoru, QIcon(":/images/icon_daoru_s.png"), "导入");
    optionToolButton (ui->tbDaochu, QIcon(":/images/icon_daochu_s.png"), "导出");
    optionToolButton (ui->tbShanchu, QIcon(":/images/icon_shanchu_s.png"), "删除");
    optionToolButton (ui->tbShaxin, QIcon(":/images/icon_shuaxin_s.png"), "刷新");
}

void AddressBookDialog::optionToolButton (QToolButton * tb, QIcon icon, QString text) {
    QAction *pAction = new QAction(this);
    pAction->setText(text);
    pAction->setIcon(icon);
    tb->setIconSize(QSize(20, 20));
    tb->setDefaultAction(pAction);
    tb->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tb->setStyleSheet ("border:none;");
}

void AddressBookDialog::optionTreeWidget () {
    ui->treeWidget->setHeaderHidden (true);
    ui->treeWidget->setColumnCount(1); //设置列数

    QTreeWidgetItem *root = new QTreeWidgetItem(ui->treeWidget,QStringList(QString("全部联系人")));

    QTreeWidgetItem *phone = new QTreeWidgetItem(root,QStringList(QString("PHONE")));
    root->addChild (phone);

    QTreeWidgetItem *group = new QTreeWidgetItem(phone,QStringList(QString("未分组")));
    phone->addChild (group);

    QTreeWidgetItem *newGroup = new QTreeWidgetItem(phone,QStringList(QString("新建分组...")));
    newGroup->addChild (group);

    ui->treeWidget->expandAll(); //结点全部展开
}

void AddressBookDialog::optionLianxirenTableWidget () {
    //头
    QListWidgetItem *head = new QListWidgetItem;
    head->setSizeHint (QSize (359, 30));

    QWidget * widget = new QWidget;
    QWidget * background = new QWidget(widget);
    background->setGeometry (0, 0, 359, 30);

    QCheckBox * cb = new QCheckBox(widget) ;
    cb->setGeometry (10, 5, 359, 20);
    cb->setText ("名称");
    cb->setChecked (true);
    background->setStyleSheet ("border: 1px solid #e1e0e0;");

    ui->lianxirensmsListWidget->addItem (head);
    ui->lianxirensmsListWidget->setItemWidget (head, widget);

    //
    for (int i = 0; i < PhoneHandler::getInstance ()->listAddresss.size (); i++) {
        HAddressObject * ao = PhoneHandler::getInstance ()->listAddresss.at (i);
        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint (QSize (359, 40));

        ui->lianxirensmsListWidget->addItem (item);
        ui->lianxirensmsListWidget->setItemWidget (item, getLianxirenCell (ao));
    }
}

QWidget * AddressBookDialog::getLianxirenCell (HAddressObject * ao) {

    QWidget * w = new QWidget ();
    w->setGeometry (0, 0, 359, 40);

    QCheckBox *cb = new QCheckBox (w);
    cb->setGeometry (10, 10, 20, 20);

    QWidget *icon = new QWidget (w);
    icon->setGeometry (40, 5, 30, 30);
    icon->setStyleSheet ("border-image: url(:/images/icon_head.png)");

    QLabel * title = new QLabel (w);
    title->setGeometry (80, 5, 200, 15);
    title->setText (ao->name);

    QLabel * subtitle = new QLabel (w);
    subtitle->setGeometry (80, 20, 200, 15);
    subtitle->setText (ao->phone);

    return w;
}

void AddressBookDialog::on_lianxiren_item_clicked(QListWidgetItem* item) {
    int index = ui->lianxirensmsListWidget->row (item);
    if (index >= 1 ){
        //改变背景色
        QWidget * w = (QWidget *) ui->lianxirensmsListWidget->itemWidget (item);
        w->setStyleSheet ("background-color:#69C282");
        if (oldAddressIndex != -1 && oldAddressIndex != index) {
            // 清空历史项状态
            w = (QWidget *) ui->lianxirensmsListWidget->itemWidget (ui->lianxirensmsListWidget->item (oldAddressIndex));
            w->setStyleSheet ("background-color:#FFFFFF");
        }
        //
        oldAddressIndex = index;
        // 去掉头的位置
        updateAddressInfo (PhoneHandler::getInstance ()->listAddresss.at (index-1));
    }
}

void AddressBookDialog::updateAddressInfo (HAddressObject * ao) {

    qDebug () << "updateAddressInfo: " << ao;
    ui->lbName->setText (ao->name);
    ui->lbGroup->setText ("");
    ui->lbPhone->setText (ao->phone);
    ui->lbUserName->setText ("");

}

void AddressBookDialog::optionSmsListWidget () {
    //头
    QListWidgetItem *head = new QListWidgetItem;
    head->setSizeHint (QSize (199, 30));

    QWidget * widget = new QWidget;
    QWidget * background = new QWidget(widget);
    background->setGeometry (0, 0, 199, 30);

    QCheckBox * cb = new QCheckBox(widget) ;
    cb->setGeometry (10, 5, 199, 20);
    cb->setText ("短信");
    cb->setChecked (true);
    background->setStyleSheet ("border: 1px solid #e1e0e0;");

    ui->smsListWidget->addItem (head);
    ui->smsListWidget->setItemWidget (head, widget);

    //
    for (int i = 0; i < PhoneHandler::getInstance ()->listSms.size (); i++) {
        HSmsObject * so = PhoneHandler::getInstance ()->listSms.at (i);

        QListWidgetItem *item = new QListWidgetItem;
        item->setSizeHint (QSize (199, 30));

        QWidget * widget = new QWidget;

        QCheckBox * cb = new QCheckBox(widget) ;
        cb->setGeometry (10, 5, 20, 20);
        cb->setChecked (false);
        cb->setCheckable (false);

        QLabel *lb = new QLabel (widget);
        lb->setText (QString(so->phone+"(%1)").arg (so->subSms.size ()));
        lb->setGeometry (40, 5, 160, 20);

        ui->smsListWidget->addItem (item);
        ui->smsListWidget->setItemWidget (item, widget);
    }
}

void AddressBookDialog::optionsmsItemListWidget (int row) {


    for (int i = 0; i < PhoneHandler::getInstance ()->listSms.at (row)->subSms.size (); i++) {
        HSmsObject * so = PhoneHandler::getInstance ()->listSms.at (row)->subSms.at (i);

        QListWidgetItem *item = new QListWidgetItem;

        QWidget * widget = new QWidget;

        QLabel * lb = new QLabel(widget) ;
        lb->setWordWrap(true);
        lb->adjustSize();
        lb->setAlignment(Qt::AlignVCenter);
        lb->setText (so->body);
        QSize size = labelSize (lb);

        int max = 350;
        int unitH = 30;
        if (so->type == "接收") {
            lb->setStyleSheet ("background-color: #00BFFF");
            if (size.width () < max) {
                item->setSizeHint (QSize (650, unitH));
                lb->setGeometry (10, 5, size.width ()+20, unitH);
            } else {
                item->setSizeHint (QSize (650, unitH*(size.width () / max + 1)));
                lb->setGeometry (10, 5, max, unitH*(size.width () / max + 1));
            }
        } else {
            lb->setStyleSheet ("background-color: #3CB385");
            if (size.width () < max) {
                item->setSizeHint (QSize (650, unitH));
                lb->setGeometry (640-size.width ()-20, 5, size.width ()+20, unitH);
            } else {
                item->setSizeHint (QSize (650, unitH*(size.width () / max + 1)));
                lb->setGeometry (290, 5, max, unitH*(size.width () / max + 1));
            }
        }

        qDebug () << "size: " << size;

        ui->smsItemListWidget->addItem (item);
        ui->smsItemListWidget->setItemWidget (item, widget);
    }
}

QSize AddressBookDialog::labelSize (QLabel * lb) {
    QFont wordfont = lb->font ();
    wordfont.setWeight (350);
    QFontMetrics fm(wordfont);

    QRect rec = fm.boundingRect(lb->text ());
    return rec.size ();
}

void AddressBookDialog::on_smslistwidget_clicked(QListWidgetItem* item) {
    qDebug () << "on_smslistwidget_clicked";
    ui->smsItemListWidget->clear ();
    int index = ui->smsListWidget->row (item);
    qDebug () << "on_smslistwidget_clicked: " << index;
    if (index > 0) {
        optionsmsItemListWidget (index-1);
    }
}

void AddressBookDialog::on_tbShaxin1_clicked()
{
    PhoneHandler::getInstance ()->resetAddressBook ();
}

void AddressBookDialog::on_tbShaxin_clicked()
{
    PhoneHandler::getInstance ()->resetSms ();
}

void AddressBookDialog::on_addressbook_changed () {
    ui->lianxirensmsListWidget->clear ();
    optionLianxirenTableWidget ();
}

void AddressBookDialog::on_sms_changed () {
    ui->smsListWidget->clear ();
    optionSmsListWidget ();
}
