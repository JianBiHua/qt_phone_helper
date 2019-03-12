#include "filemanagerdialog.h"
#include "ui_filemanagerdialog.h"
#include <QSplitter>
#include <QTreeWidget>
#include <QTableWidget>

FileManagerDialog::FileManagerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileManagerDialog)
{
    ui->setupUi(this);

    // 不显示状态栏
    // 设置窗体标题栏隐藏和窗口是否有任务栏图标
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);

    //
    ui->title->setStyleSheet ("color:#FFFFFF");

    optionMainWidget ();
    optionToolButtons ();
    optionTreeWidget ();
    optionTableWidget ();

    //
    ui->top->setStyleSheet (QString("background-color: rgb(66, 183, 106)"));
    ui->tools->setStyleSheet ("background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #F1F1F1, stop:1 #FDFDFD");

    // 关闭按钮
    ui->pbClose->setStyleSheet (QString("border-image: url(:/images/icon_close.png)"));
    // 图标
    ui->icon->setStyleSheet ("border-image: url(:/images/icon.png)");
}

FileManagerDialog::~FileManagerDialog()
{
    delete ui;
}

void FileManagerDialog::optionMainWidget () {
    //创建主分割窗口 设置方向为水平分割窗口
    QSplitter *mainSplitter = new QSplitter(Qt::Horizontal, 0);
//    QList<int> widgetSizes;
//    widgetSizes << 190 << 520;
//    mainSplitter->setSizes(widgetSizes);
//    mainSplitter->setStretchFactor(0,1);
//    mainSplitter->setStretchFactor(1,2);  //这个地方无法生效

    //
    treeWidget= new QTreeWidget(mainSplitter);
    treeWidget->setMinimumWidth (190);
    //tree->setFixedWidth (190);

    tableWidget = new QTableWidget (mainSplitter);
    tableWidget->setMinimumWidth (190);

    ui->horizontalLayout->addWidget (mainSplitter);
}

void FileManagerDialog::on_pbClose_clicked()
{
    this->close ();
}

void FileManagerDialog::optionToolButtons () {
    optionToolButton (ui->tbShangceng, QIcon(":/images/icon_shangceng_s.png"), "返回上一级");
    optionToolButton (ui->tbXinjian, QIcon(":/images/icon_tianjia_s.png"), "新建文件夹");
    optionToolButton (ui->tbShangchuan, QIcon(":/images/icon_tianjia_s.png"), "上传到手机");
    optionToolButton (ui->tbFasong, QIcon(":/images/icon_fasong_s.png"), "发送到电脑");
    optionToolButton (ui->tbShanchu, QIcon(":/images/icon_shanchu_s.png"), "删除");
    optionToolButton (ui->tbFuzhi, QIcon(":/images/icon_fuzhi_s.png"), "复制");
    optionToolButton (ui->tbZhantie, QIcon(":/images/icon_zhantie_s.png"), "粘贴");
    optionToolButton (ui->tbShuaXin, QIcon(":/images/icon_shuaxin_s.png"), "刷新");
}

void FileManagerDialog::optionToolButton (QToolButton * tb, QIcon icon, QString text) {
    QAction *pAction = new QAction(this);
    pAction->setText(text);
    pAction->setIcon(icon);
    tb->setIconSize(QSize(20, 20));
    tb->setDefaultAction(pAction);
    tb->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    tb->setStyleSheet ("border:none;");
}

void FileManagerDialog::optionTreeWidget () {
    treeWidget->setFocusPolicy(Qt::NoFocus);
    treeWidget->setHeaderHidden (true);
    treeWidget->setColumnCount(1); //设置列数

//    treeWidget->setHeaderLabel(tr("图像选择")); //设置头的标题
//    QTreeWidgetItem *root = new QTreeWidgetItem(treeWidget,QStringList(QString("")));

    QTreeWidgetItem *camera = new QTreeWidgetItem(treeWidget,QStringList(QString("照片")));
    camera->setIcon(0,QIcon(":/images/icon_camera_s.png"));
    //treeWidget->addTopLevelItem (camera);
    QTreeWidgetItem *music = new QTreeWidgetItem(treeWidget,QStringList(QString("音乐")));
    music->setIcon(0,QIcon(":/images/icon_music_s.png"));
    //treeWidget->addTopLevelItem (music);
    QTreeWidgetItem *sysFiles = new QTreeWidgetItem(treeWidget,QStringList(QString("系统文件")));
    sysFiles->setIcon(0,QIcon(":/images/icon_phone_s.png"));
  //  treeWidget->addTopLevelItem (sysFiles);
    QTreeWidgetItem *sdcard = new QTreeWidgetItem(treeWidget,QStringList(QString("内置SD卡")));
    sdcard->setIcon(0,QIcon(":/images/icon_sdcard_s.png"));
    //treeWidget->addChild (sdcard);
//    treeWidget->addTopLevelItem (sdcard);

    treeWidget->expandAll(); //结点全部展开
}

void FileManagerDialog::optionTableWidget () {
    QStringList header;
    tableWidget->setFocusPolicy(Qt::NoFocus);
    tableWidget->setRowCount(2);     //设置行数为10
    tableWidget->setColumnCount(4);

    header<<"名称"<<"大小"<<"日期"<<"类型";
    tableWidget->setHorizontalHeaderLabels(header);

    tableWidget->setEditTriggers ( QAbstractItemView::NoEditTriggers );//表格不可编辑
    tableWidget->setColumnWidth(0, 350);
    tableWidget->setColumnWidth(1, 100);
    tableWidget->setColumnWidth(2, 100);
    tableWidget->setColumnWidth(3, 100);
    tableWidget->setShowGrid(false); //设置显示格子线
    tableWidget->verticalHeader ()->hide ();

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
