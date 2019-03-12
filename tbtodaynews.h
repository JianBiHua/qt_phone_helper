#ifndef TBTODAYNEWS_H
#define TBTODAYNEWS_H

#include <QWidget>
#include <QPushButton>
#include <QtWebEngineWidgets>

namespace Ui {
class TBTodayNews;
}

class TBTodayNews : public QWidget
{
    Q_OBJECT

public:
    explicit TBTodayNews(QWidget *parent = 0);
    ~TBTodayNews();

private slots:
    void on_home_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_fresh_clicked();

    void on_webview_urlchanged(const QUrl& url);

private:
    Ui::TBTodayNews *ui;

private:
    void optionPushButtons ();
    void optionPushButton (QPushButton * pushButton, QString icon);
    void setBackgroundColor ();
    void createWebView ();

public:
    void showUrl (QString u);

private:
    QWebEngineView * webview;
    QString url;
};

#endif // TBTODAYNEWS_H
