#include "tbtodaynews.h"
#include "ui_tbtodaynews.h"

TBTodayNews::TBTodayNews(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TBTodayNews)
{
    ui->setupUi(this);

    webview = nullptr;
    setBackgroundColor ();
    optionPushButtons ();
    //
    showUrl ("http://zsall.mobilem.360.cn/html/todayhot3.html?sdkver=0&ver=2.5.1.1630");
}

void TBTodayNews::optionPushButtons () {
    //
    optionPushButton (ui->left, ":/images/web_left.png");
    optionPushButton (ui->right, ":/images/web_right.png");
    optionPushButton (ui->fresh, ":/images/web_fresh.png");
    optionPushButton (ui->home, ":/images/web_home.png");
}

void TBTodayNews::showUrl (QString u) {
    url = u;
    createWebView ();
}

void TBTodayNews::createWebView () {
    if (webview == nullptr) {
        webview = new QWebEngineView(this);
        ui->verticalLayout->addWidget (webview);

        //
        connect(webview, SIGNAL(urlChanged(const QUrl&)), this, SLOT(on_webview_urlchanged(const QUrl&)));
    }

    webview->load(QUrl(url));
}

void TBTodayNews::setBackgroundColor () {
    ui->topWidget->setStyleSheet ("background-color:#F0F0F0;");
    ui->mainWidget->setStyleSheet ("background-color:#E0E0E0;border: 1px solid #A0A0A0");
}

void TBTodayNews::optionPushButton (QPushButton * pushButton, QString icon) {
//    QPalette palette;
//    palette.setBrush(QPalette::Background, QPixmap(icon));
//    pushButton->setAutoFillBackground(true);
//    pushButton->setPalette (palette);
     pushButton->setStyleSheet (QString("QPushButton{background-image:url(%1)}").arg (icon));
}

TBTodayNews::~TBTodayNews()
{
    delete ui;
}

void TBTodayNews::on_home_clicked()
{
    webview->load(QUrl(url));
}

void TBTodayNews::on_left_clicked()
{
    webview->back ();
}

void TBTodayNews::on_right_clicked()
{
    webview->forward ();
}

// 刷新
void TBTodayNews::on_fresh_clicked()
{
    webview->reload ();
}

void TBTodayNews::on_webview_urlchanged(const QUrl& url) {
    qDebug()<<"on_webview_urlchanged: " << url;
}
