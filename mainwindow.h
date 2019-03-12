#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolButton>
#include <QStackedWidget>
#include <QMenu>
#include <QPushButton>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private :
    QStackedWidget * stackedWidget;
    QMenu *contextmenu;

private:
    void showToolBars ();
    void setTabBarIndex (int index);
    void showStackedWidget ();
    void setBackgroundColor ();

    void updateStyle (QWidget * w);
    void optionToolButton (QToolButton * tb, QIcon icon, QString text);
    void showContextMenu ();
    void createContextMenu () ;
    void optionButton (QPushButton * pushButton, QString icon);

private slots:
    void on_pbClose_clicked();

    void on_tbMyPhone_clicked();

    void on_tbTodayHot_clicked();

    void on_tbPlayGame_clicked();

    void on_tbFindGame_clicked();

    void on_tbApp_clicked();

    void on_tbAmusement_clicked();

    void on_tbSmallApp_clicked();

    void on_tbPcGame_clicked();

    void on_tbPcApp_clicked();

    void on_pbLogin_clicked();

    void shezhiActionSlot();
    void xiazaiguanliActionSlot();
    void guanfangweiboActionSlot();
    void guanfangwangzhanActionSlot();
    void guanfangluntanActionSlot();
    void jianchagengxinActionSlot();
    void baipishuActionSlot();
    void tijiaoyingyongActionSlot();
    void guanyuActionSlot();

    void on_pbMenu_clicked();

    void on_pbMin_clicked();

    void on_pbMax_clicked();

    void on_pbDownload_clicked();

    void on_pbMessage_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
