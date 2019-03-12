#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qtabbar.h>
#include <qdebug.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <QStatusBar>
#include "tbamusement.h"
#include "tbapp.h"
#include "tbfindapp.h"
#include "tbmyphone.h"
#include "tbpcgame.h"
#include "tbplaygame.h"
#include "tbsmallapp.h"
#include "tbtodaynews.h"
#include "logindialog.h"
#include "downloaddialog.h"
#include "aboutdialog.h"
#include "updatedialog.h"
#include "settingdialog.h"
#include "questiondialog.h"
#include <QLabel>

/*
* adb logcat: 获取日志
*
* if(value == 2){
        system("./bin/adb shell pm setInstallLocation 2"); // install to sdcard
    }else {
        system("./bin/adb shell pm setInstallLocation 0");	// auto install default to phone storage
    }
*/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 不显示状态栏
    // 设置窗体标题栏隐藏和窗口是否有任务栏图标
    this->setWindowFlags(Qt::FramelessWindowHint|Qt::Tool);

    //
    ui->pbLogin->setStyleSheet ("color:#FFFFFF");

    QPalette palette;
    palette.setBrush(QPalette::Background,
                     QBrush(QPixmap(":/images/icon.png").scaled( // 缩放背景图.
                             ui->icon->size(),
                             Qt::IgnoreAspectRatio,
                             Qt::SmoothTransformation)));
    ui->icon->setAutoFillBackground(true);
    ui->icon->setPalette (palette);
    // 圆形背景
    ui->iconBg->setStyleSheet ("QWidget{border-radius:20px;background-color:#FFFFFF}");


    //
    setBackgroundColor ();
    showToolBars ();
    showStackedWidget ();
    createContextMenu () ;
    //
    optionButton (ui->pbClose, ":/images/icon_close.png");
    optionButton (ui->pbMax, ":/images/icon_max.png");
    optionButton (ui->pbMin, ":/images/icon_min.png");
    optionButton (ui->pbMenu, ":/images/icon_menu.png");
    optionButton (ui->pbMessage, ":/images/icon_msg.png");
    optionButton (ui->pbDownload, ":/images/download.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::optionButton (QPushButton *pushButton, QString icon) {
    pushButton->setProperty ("mainwindow_pushbutton", true);
    pushButton->setStyleSheet (QString("background-image: url(%1)").arg (icon));
}

void MainWindow::on_pbClose_clicked() {
    // 退出
    QCoreApplication::exit();
}

void MainWindow::setBackgroundColor () {
    ui->mainWidget->setAutoFillBackground(true);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor(0xFD,0xFD,0xFD));
    ui->mainWidget->setPalette(palette);

}

void MainWindow::showStackedWidget () {
    //创建QStackedwidget控件
    stackedWidget = new QStackedWidget(this);

    stackedWidget->addWidget(new TBMyPhone);
    stackedWidget->addWidget(new TBTodayNews);
    stackedWidget->addWidget(new TBPlayGame);
    stackedWidget->addWidget(new TBFindApp);
    stackedWidget->addWidget(new TBApp);
    stackedWidget->addWidget(new TBAmusement);
    stackedWidget->addWidget(new TBSmallApp);
    stackedWidget->addWidget(new TBPCGame);

    ui->verticalLayout->addWidget (stackedWidget);
}

void MainWindow::showToolBars () {
    setTabBarIndex (0);

    optionToolButton (ui->tbMyPhone,
                      QIcon(":/images/myphone.png"),
                      tr("我的手机"));
    optionToolButton (ui->tbTodayHot,
                      QIcon(":/images/todaynews.png"),
                      tr("今日热点"));
    optionToolButton (ui->tbPlayGame,
                      QIcon(":/images/playgame.png"),
                      tr("玩游戏"));
    optionToolButton (ui->tbFindGame,
                      QIcon(":/images/findapp.png"),
                      tr("找软件"));
    optionToolButton (ui->tbApp,
                      QIcon(":/images/app.png"),
                      tr("应用圈"));
    optionToolButton (ui->tbAmusement,
                      QIcon(":/images/yule.png"),
                      tr("娱乐"));
    optionToolButton (ui->tbSmallApp,
                      QIcon(":/images/smallapp.png"),
                      tr("小程序"));
    optionToolButton (ui->tbPcGame,
                      QIcon(":/images/pcgame.png"),
                      tr("电脑玩游戏"));
    optionToolButton (ui->tbPcApp,
                      QIcon(":/images/pcapp.png"),
                      tr("电脑软件"));
}

void MainWindow::setTabBarIndex (int index) {
    char * key = "ToolButtonTabSelected";
    ui->tbMyPhone->setProperty (key, index==0?true:false);
    updateStyle (ui->tbMyPhone) ;
    ui->tbTodayHot->setProperty (key, index==1?true:false);
    updateStyle (ui->tbTodayHot) ;
    ui->tbPlayGame->setProperty (key, index==2?true:false);
    updateStyle (ui->tbPlayGame) ;
    ui->tbFindGame->setProperty (key, index==3?true:false);
    updateStyle (ui->tbFindGame) ;
    ui->tbApp->setProperty (key, index==4?true:false);
    updateStyle (ui->tbApp) ;
    ui->tbAmusement->setProperty (key, index==5?true:false);
    updateStyle (ui->tbAmusement) ;
    ui->tbSmallApp->setProperty (key, index==6?true:false);
    updateStyle (ui->tbSmallApp) ;
    ui->tbPcGame->setProperty (key, index==7?true:false);
    updateStyle (ui->tbPcGame) ;
    ui->tbPcApp->setProperty (key, index==8?true:false);
    updateStyle (ui->tbPcApp) ;
}

void MainWindow::updateStyle (QWidget * w) {
    w->style()->unpolish(w);
    w->style()->polish(w);
    w->update ();
}

void MainWindow::optionToolButton (QToolButton * tb, QIcon icon, QString text) {
    QAction *pAction = new QAction(this);
    pAction->setText(text);
    pAction->setIcon(icon);
    tb->setIconSize(QSize(32, 32));
    tb->setDefaultAction(pAction);
    tb->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tb->setProperty ("mainwindow", true);
    //tb->setAutoRaise(true);
}

void MainWindow::on_tbMyPhone_clicked() {
    setTabBarIndex (0);
    stackedWidget->setCurrentIndex (0);
    TBMyPhone * myPhone = (TBMyPhone *) stackedWidget->widget (0);
    myPhone->reset ();
}

void MainWindow::on_tbTodayHot_clicked()
{
    setTabBarIndex (1);
    stackedWidget->setCurrentIndex (1);
}

void MainWindow::on_tbPlayGame_clicked()
{
    setTabBarIndex (2);
    stackedWidget->setCurrentIndex (2);
}

void MainWindow::on_tbFindGame_clicked()
{
    setTabBarIndex (3);
    stackedWidget->setCurrentIndex (3);
}

void MainWindow::on_tbApp_clicked()
{
    setTabBarIndex (4);
    stackedWidget->setCurrentIndex (4);
}

void MainWindow::on_tbAmusement_clicked()
{
    setTabBarIndex (5);
    stackedWidget->setCurrentIndex (5);
}

void MainWindow::on_tbSmallApp_clicked()
{
    setTabBarIndex (6);
    stackedWidget->setCurrentIndex (6);
}

void MainWindow::on_tbPcGame_clicked()
{
    setTabBarIndex (7);
    stackedWidget->setCurrentIndex (7);
}

void MainWindow::on_tbPcApp_clicked()
{
    setTabBarIndex (8);
}

void MainWindow::on_pbLogin_clicked()
{
    // 显示模态对话框.
    LoginDialog *ld = new LoginDialog();
    ld->setModal (true);
    ld->exec ();
}

void MainWindow::createContextMenu () {
    QAction *shezhi = new QAction( tr("设置"), this);
    connect(shezhi, SIGNAL(triggered()), this, SLOT(shezhiActionSlot()));
    QAction *xiazaiguanli = new QAction( tr("下载管理"), this);
    connect(xiazaiguanli, SIGNAL(triggered()), this, SLOT(xiazaiguanliActionSlot()));
    QAction *guanfangweibo = new QAction( tr("官方微博"), this);
    connect(guanfangweibo, SIGNAL(triggered()), this, SLOT(guanfangweiboActionSlot()));
    QAction *guanfangwangzhan = new QAction( tr("官方网站"), this);
    connect(guanfangwangzhan, SIGNAL(triggered()), this, SLOT(guanfangwangzhanActionSlot()));
    QAction *guanfangluntan = new QAction( tr("官方论坛"), this);
    connect(guanfangluntan, SIGNAL(triggered()), this, SLOT(guanfangluntanActionSlot()));
    QAction *jianchagengxin = new QAction( tr("检查更新"), this);
    connect(jianchagengxin, SIGNAL(triggered()), this, SLOT(jianchagengxinActionSlot()));
    QAction *baipishu = new QAction( tr("隐私保护白皮书"), this);
    connect(baipishu, SIGNAL(triggered()), this, SLOT(baipishuActionSlot()));
    QAction *tijiaoyingyong = new QAction( tr("提交应用"), this);
    connect(tijiaoyingyong, SIGNAL(triggered()), this, SLOT(tijiaoyingyongActionSlot()));
    QAction *guanyu = new QAction( tr("关于"), this);
    connect(guanyu, SIGNAL(triggered()), this, SLOT(guanyuActionSlot()));

    contextmenu = new QMenu(this);
    contextmenu->addAction(shezhi);
    contextmenu->addAction(xiazaiguanli);
    contextmenu->addSeparator();
    contextmenu->addAction(guanfangweibo);
    contextmenu->addAction(guanfangwangzhan);
    contextmenu->addAction(guanfangluntan);
    contextmenu->addSeparator();
    contextmenu->addAction(jianchagengxin);
    contextmenu->addAction(baipishu);
    contextmenu->addSeparator();
    contextmenu->addAction(tijiaoyingyong);
    contextmenu->addAction(guanyu);
    //设置如何显示上下文菜单
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void MainWindow::showContextMenu ()  {

    QPoint point = ui->pbMenu->mapToGlobal (QPoint(ui->pbMenu->width ()/2,
                        ui->pbMenu->height ()));
    contextmenu->hide ();
    contextmenu->move(point); //让菜单显示的位置在鼠标的坐标上
    contextmenu->show();
}

void MainWindow::shezhiActionSlot(){
    SettingDialog * sd = new SettingDialog ();
    sd->setModal (true);
    sd->show ();
}
void MainWindow::xiazaiguanliActionSlot(){
    // 直接调用下载管理函数
    on_pbDownload_clicked();
}
void MainWindow::guanfangweiboActionSlot(){
    const QUrl url("http://weibo.com/360sjzs");
    QDesktopServices::openUrl(url);
}
void MainWindow::guanfangwangzhanActionSlot(){
    const QUrl url("http://sj.360.cn/index.html");
    QDesktopServices::openUrl(url);
}
void MainWindow::guanfangluntanActionSlot(){
    const QUrl url("http://bbs.360.cn/forum.php?mod=forumdisplay&fid=108&tj=zhushou");
    QDesktopServices::openUrl(url);
}
void MainWindow::jianchagengxinActionSlot(){
    UpdateDialog * ad = new UpdateDialog ();
    ad->setModal (true);
    ad->show ();
}
void MainWindow::baipishuActionSlot(){
    const QUrl url("http://www.360.cn/privacy/v2/index.html");
    QDesktopServices::openUrl(url);
}
void MainWindow::tijiaoyingyongActionSlot(){
    const QUrl url("http://dev.360.cn/");
    QDesktopServices::openUrl(url);
}
void MainWindow::guanyuActionSlot(){
    AboutDialog * ad = new AboutDialog ();
    ad->setModal (true);
    ad->show ();
}

void MainWindow::on_pbMenu_clicked()
{
    showContextMenu () ;
}

void MainWindow::on_pbMin_clicked()
{
    this->showMinimized();
}

void MainWindow::on_pbMax_clicked()
{
    this->showMaximized ();
}

void MainWindow::on_pbDownload_clicked()
{
    // 显示模态对话框.
    DownLoadDialog *dld = new DownLoadDialog();
    dld->setModal (true);
    dld->exec ();
}

void MainWindow::on_pbMessage_clicked()
{
    // 显示对话框.
    QuestionDialog *qd = new QuestionDialog();
    qd->setModal (false);
    qd->exec ();
}
